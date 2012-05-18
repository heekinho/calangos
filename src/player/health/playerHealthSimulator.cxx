/*
 * playerHealthSimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "playerHealthSimulator.h"

#include "timeControl.h"

PlayerHealthSimulator::PlayerHealthSimulator(PT(PlayerHealth) health) {
	_health = health;

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

}

/*! No evento de passagem do dia, esse método será chamado */
void PlayerHealthSimulator::event_pass_day(const Event *, void * data){

}

/*! No evento de passagem do dia, esse método será chamado */
void PlayerHealthSimulator::event_pass_month(const Event *, void * data){

}

void PlayerHealthSimulator::configure_events(){

}

double PlayerHealthSimulator::get_energy() const {
    return _energy;
}

void PlayerHealthSimulator::set_energy(double energy){
    this->_energy = energy;
}


