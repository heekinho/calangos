/*
 * energySimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "energySimulator.h"

EnergySimulator::EnergySimulator(PT(PlayerHealth) health) : Simulator(health) {
	_initial_energy = 50;
}

/*! Realiza a simulação atualizando os gastos de energia */
void EnergySimulator::update(){
	update_basal_cost();
	update_moviment_cost();
	update_temperature_cost();
	update_total_cost();
}

/*! Atualiza o gasto basal do lagarto */
void EnergySimulator::update_basal_cost(){
//		if (Session::get_instance()->get_level() > 1) {
//			gasto_basal = (ENERGIA_INIT/(num_horas_alimento*atualizacoes_phora))*(1+(5*get_absolute_size_factor()));
//		} else {
//			this->gasto_basal = (ENERGIA_INIT/(num_horas_alimento*atualizacoes_phora))*(1+(5*this->tamanho_lagarto_base/100));
//		}

//		_basal_cost =
}

/* Atualiza o gasto por movimento do lagarto */
void EnergySimulator::update_moviment_cost(){

}

/*! Atualiza o gasto por temperatura do lagarto */
void EnergySimulator::update_temperature_cost(){

}

/*! Calcula o gasto de energia do lagarto.
 * O gasto de energia do lagarto é dado por:
 * Gasto Total = Gasto Basal * Gasto por Temperatura */
void EnergySimulator::update_total_cost(){
	_total_cost = _basal_cost * ( _temperature_cost * _moviment_cost );
}
