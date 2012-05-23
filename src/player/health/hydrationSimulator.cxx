/*
 * hydrationSimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "hydrationSimulator.h"

HydrationSimulator::HydrationSimulator(PT(PlayerHealth) health) : Simulator(health) {
	float initial_hydration = 50.0;

	_humidity_factor = 0.0;
	_humidity_factor_a = -(initial_hydration / health->max_hours_with_low_hydration) / (health->humidity_affects_hidration - health->humidity_param);
	_humidity_factor_b = -(_humidity_factor_a * (health->humidity_affects_hidration));

	_hydration = initial_hydration;
	_food_hydration_buffer = 0.0;
}

HydrationSimulator::~HydrationSimulator(){

}


/* Retorna a hidratação do lagarto */
float HydrationSimulator::get_hydration() const {
	return _hydration;
}


/*! Calcula a hidratação do lagarto, sendo dada por:
 *  hidratação = hidratação - fatorUmidade + hidratacaoAlimento */
void HydrationSimulator::update_hydration(float relative_humitidy_of_sector, float updates_per_hour){
	update_humidity_factor(relative_humitidy_of_sector, updates_per_hour);

	_hydration = _hydration - _humidity_factor + _food_hydration_buffer;
	_hydration = clamp(0, 100, _hydration);

	/* Hidratação já consumida */
	_food_hydration_buffer = 0;

	//AudioController::get_instance()->warning_hydrat(hidratacao, hidratacao_minlimite);
}


/*! Calcula o fator umidade. Armazena em quanto o valor da hidratação vai cair a cada atualização de variáveis
 *  com base no valor da umidade relativa da microregião em que o lagarto se encontra. */
void HydrationSimulator::update_humidity_factor(float relative_humitidy_of_sector, float updates_per_hour){
	/* Calcula o valor de decaímento caso as atualizações fossem de hora em hora */
	float humidity_factor_y = (_humidity_factor_a * relative_humitidy_of_sector) + _humidity_factor_b;
	if(relative_humitidy_of_sector >= 40.0) humidity_factor_y = 0.0;

	_humidity_factor = humidity_factor_y / updates_per_hour;
}

/*! Adiciona hidratação proveniente do consumo de alimento */
void HydrationSimulator::add_food_hydration(float food_hydration){
	_food_hydration_buffer += food_hydration;
}
