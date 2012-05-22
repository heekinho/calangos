/*
 * temperatureSimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "temperatureSimulator.h"

TemperatureSimulator::TemperatureSimulator(PT(PlayerHealth) health) : Simulator(health) {
	_temperature = 40; //TODO: Initial temperature
	_current_thermal_equilibrium_speed = health->thermal_equilibrium_speed;
}

/*! Atualiza a velocidade de equilibrio da temperatura. Varia de acordo com
 *  o tamanho do lagarto */
void TemperatureSimulator::update_thermal_equilibrium_speed(float relative_size){
	float size_factor = health->thermal_equilibrium_speed * relative_size * 0.8;
	_current_thermal_equilibrium_speed = health->thermal_equilibrium_speed - size_factor;
}

/*! Obtem a temperatura externa percebida pelo organismo */
float TemperatureSimulator::perceived_temperature(){
	if(/*in_toca*/1) return MicroClima::get_instance()->get_temp_toca_sector();
	return MicroClima::get_instance()->get_temp_solo_sector();
}



/*! Atualiza a temperatura interna do lagarto */
void TemperatureSimulator::update_temperature(){
	/* Obtém a diferença de temperatura entre o lagarto e o ambiente (toca, solo etc) */
	float temperature_diff = perceived_temperature() - _temperature;

	/* Se tiver enterrado diminui a inércia térmica */
	float decrease_inertia_factor = player->is_buried() ? 1.8 : 1.0;

	/* Calcula a variação de temperatura aplicando-se a velocidade de equilibrio */
	float dt = (_current_thermal_equilibrium_speed * decrease_inertia_factor) * temperature_diff;

	/* Aplica-se a nova temperatura interna do lagarto */
	_temperature = _temperature + dt;


	//AudioController::get_instance()->warning_temp(_temperature, perceived_temperature(),
	//		health->min_temperature, health->max_temperature);
	//AudioController::get_instance()->warning_temp(temp_interna, temp_toca, temp_interna_minlimite, temp_interna_maxlimite);
	//AudioController::get_instance()->warning_temp(temp_interna, temp_solo, temp_interna_minlimite, temp_interna_maxlimite);
}

/*! Calcula a letargia do lagarto
 * 0 - Nenhuma letargia (temperatura interna maior que a ideal)
 * 1 - Total letargia - culmina na morte do lagarto */
/* |________________________________________________|
 * 15C            ^        ^        ^              50C
 *                li-------i--------hi
 *                xxxxxxxxxxxxxxxxxxxx
 *  ##############   <- Faixa de atuação letargia
 *  1<-----------0
 */
void TemperatureSimulator::update_lethargy(){

	float min_ideal_temperature = health->ideal_temperature - health->temperature_tolerance;

	if(_temperature > min_ideal_temperature) _lethargy = 0.0;
	else if(_temperature < health->min_temperature) _lethargy = 1.0;
	else _lethargy = 1.0 - compress_range(health->min_temperature, min_ideal_temperature, _temperature);
}


float TemperatureSimulator::get_temperature_cost(){
//	/* Se a temperatura interna estiver abaixo da faixa de tolerância */
//	if(temp_interna < (this->temp_interna_ideal  - this->variacao_temp_interna)) {
//		this->gasto_temp = 1/(1+((this->temp_interna_ideal  - this->variacao_temp_interna) - (this->temp_interna))*this->gasto_baixa_temp);
//	}
//	else {
//		/* Se a temperatura interna estiver acima da faixa de tolerância */
//		if(temp_interna > (this->temp_interna_ideal  + this->variacao_temp_interna)){
//			this->gasto_temp = 1+(this->temp_interna - (this->temp_interna_ideal  + this->variacao_temp_interna))*this->gasto_alta_temp;
//		}
//		else {
//			/* Temperatura na faixa de tolerância */
//			this->gasto_temp = 1;
//		}
//	}

	/* Aplica tolerância à faixa de temperatura */
	float min_range_limit = (health->ideal_temperature - health->temperature_tolerance);
	float max_range_limit = (health->ideal_temperature + health->temperature_tolerance);

	if(_temperature < min_range_limit){
		/* Temperatura abaixo da faixa de tolerância */
		float exceeded_temperature = min_range_limit - _temperature;
		return 1.0 + (health->energy_cost_low_temperature * exceeded_temperature);
	}
	else if(_temperature > max_range_limit){
		/* Temperatura acima da faixa de tolerância */
		float exceeded_temperature = _temperature - max_range_limit;
		return 1.0 + (health->energy_cost_high_temperature * exceeded_temperature);
	}
	else {
		/* Temperatura na faixa de tolerância */
		return 1.0;
	}
}
