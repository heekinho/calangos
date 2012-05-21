/*
 * playerHealthSimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "playerHealthSimulator.h"

#include "timeControl.h"

#include "energySimulator.h"
#include "temperatureSimulator.h"
#include "morfologySimulator.h"
#include "hydrationSimulator.h"
#include "dietSimulator.h"

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
	_energy_simulator->update();


	/* Atualiza hidratação do lagarto */
	float relative_humidity = MicroClima::get_instance()->get_umidade_relativa_sector();
	_hydration_simulator->update_hydration(relative_humidity, _num_updates_per_hour);

}

void PlayerHealthSimulator::pass_day(){

}

void PlayerHealthSimulator::pass_month(){
	_morfology_simulator->update_size(1.0);
	_temperature_simulator->update_thermal_equilibrium_speed();
}

float PlayerHealthSimulator::get_num_updates_per_hour(){
	return _num_updates_per_hour;
}

//void PlayerHealthSimulator::configure_events(){
//
//}
