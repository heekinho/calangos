/*
 * playerHealthSimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "playerHealthSimulator.h"

#include "player.h"
#include "timeControl.h"
#include "playerHealth.h"
#include "energySimulator.h"
#include "temperatureSimulator.h"
#include "morfologySimulator.h"
#include "hydrationSimulator.h"
#include "dietSimulator.h"

#include "microClima.h"

NotifyCategoryDef(player_health, "");

PlayerHealthSimulator::PlayerHealthSimulator(PT(PlayerHealth) health) {
	player_health_cat.debug() << "Constructing PlayerHealthSimulator" << endl;

	_health = health;

    /* TODO: Muito estranho isso. Podemos contar manualmente! =)
     * TODO: ISSO ESTÁ ERRADO! */
    _num_updates_per_hour = 60*((3*60.0)/(24*60));

    _energy_simulator = new EnergySimulator(_health);
    _temperature_simulator = new TemperatureSimulator(_health);
    _morfology_simulator = new MorfologySimulator(_health);
    _hydration_simulator = new HydrationSimulator(_health);
    _diet_simulator = new DietSimulator(_health);

	event_handler->add_hook(TimeControl::EV_segundo_real, event_pass_second, this);
	event_handler->add_hook(TimeControl::EV_pass_day, event_pass_day, this);
	event_handler->add_hook(TimeControl::EV_pass_month, event_pass_month, this);
}

PlayerHealthSimulator::~PlayerHealthSimulator() {
	_health = NULL;

	event_handler->remove_hook(TimeControl::EV_segundo_real, event_pass_second, this);
	event_handler->remove_hook(TimeControl::EV_pass_day, event_pass_day, this);
	event_handler->remove_hook(TimeControl::EV_pass_month, event_pass_month, this);
}

/*! Evento periódico de gasto de energia (é preciso criar) */
void PlayerHealthSimulator::event_pass_second(const Event *, void * data){
	player_health_cat.debug() << "PlayerHealthSimulator processing pass_second event" << endl;
	((PlayerHealthSimulator*) data)->pass_second();
}

/*! No evento de passagem do dia, esse método será chamado */
void PlayerHealthSimulator::event_pass_day(const Event *, void * data){
	player_health_cat.debug() << "PlayerHealthSimulator processing pass_day event" << endl;
	((PlayerHealthSimulator*) data)->pass_day();
}

/*! No evento de passagem do dia, esse método será chamado */
void PlayerHealthSimulator::event_pass_month(const Event *, void * data){
	player_health_cat.debug() << "PlayerHealthSimulator processing pass_day month" << endl;
	((PlayerHealthSimulator*) data)->pass_month();
}

/*! Evento de passagem de segundo real. A ordem de atualização pode ser importante e deve ser
 *  verificada. */
void PlayerHealthSimulator::pass_second(){
//	/* Fazer algo assim? */
//	for(int i = 0; i < simulators.size(); i++){
//		simulators[i]->update();
//	}

	_temperature_simulator->update_temperature();
	_temperature_simulator->update_lethargy();

	/* Atualiza todos os gastos de energia */
	float relative_size = _morfology_simulator->get_relative_size();
	float temperature_cost = _temperature_simulator->get_temperature_cost();
	_energy_simulator->update(_num_updates_per_hour, relative_size, temperature_cost);


	/* Atualiza hidratação do lagarto */
	float relative_humidity = MicroClima::get_instance()->get_umidade_relativa_sector();
	_hydration_simulator->update_hydration(relative_humidity, _num_updates_per_hour);
}

void PlayerHealthSimulator::pass_day(){
	_energy_simulator->update_daily_energy_average();
}

void PlayerHealthSimulator::pass_month(){
	float average_energy = _energy_simulator->update_monthly_energy_average();

	_morfology_simulator->update_size(average_energy);

	float relative_size = _morfology_simulator->get_relative_size();
	_temperature_simulator->update_thermal_equilibrium_speed(relative_size);

}

float PlayerHealthSimulator::get_num_updates_per_hour(){
	return _num_updates_per_hour;
}

//void PlayerHealthSimulator::configure_events(){
//
//}

PT(EnergySimulator) PlayerHealthSimulator::get_energy_simulator() const {
	return _energy_simulator;
}

PT(TemperatureSimulator) PlayerHealthSimulator::get_temperature_simulator() const {
	return _temperature_simulator;
}

PT(MorfologySimulator) PlayerHealthSimulator::get_morfology_simulator() const {
	return _morfology_simulator;
}

PT(HydrationSimulator) PlayerHealthSimulator::get_hydration_simulator() const {
	return _hydration_simulator;
}

PT(DietSimulator) PlayerHealthSimulator::get_diet_simulator() const {
	return _diet_simulator;
}
