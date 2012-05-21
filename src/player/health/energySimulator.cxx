/*
 * energySimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "energySimulator.h"

EnergySimulator::EnergySimulator(PT(PlayerHealth) health) : Simulator(health) {
	_initial_energy = 50;

	_energy = _initial_energy;
	_food_energy_buffer = 0.0;

	_basal_cost = 0.0;
	_moviment_cost = 0.0;
	_temperature_cost = 0.0;
	_total_cost = 0.0;
}

EnergySimulator::~EnergySimulator(){

}

/*! Realiza a simulação atualizando os gastos de energia */
void EnergySimulator::update(float updates_per_hour, float size_factor){
	update_basal_cost(updates_per_hour, size_factor);
	update_moviment_cost();
	update_temperature_cost();
	update_total_cost();
}

void EnergySimulator::update_energy(){
	/* Energia de alimento está sendo consumida instantaneamente */
//	_energy = _energy - _total_cost + _food_energy_buffer;

	_energy = _energy - _total_cost;
	_energy = clamp(0, 100, _energy);

	/* Consome a energia do alimento */
	_food_energy_buffer = 0.0;
}

/*! Atualiza o gasto basal do lagarto */
void EnergySimulator::update_basal_cost(float updates_per_hour, float size_factor){
//		if (Session::get_instance()->get_level() > 1) {
//			gasto_basal = (ENERGIA_INIT/(num_horas_alimento*atualizacoes_phora))*(1+(5*get_absolute_size_factor()));
//		} else {
//			this->gasto_basal = (ENERGIA_INIT/(num_horas_alimento*atualizacoes_phora))*(1+(5*this->tamanho_lagarto_base/100));
//		}

	float food_factor = (_initial_energy / (health->max_hours_without_food * updates_per_hour));
	size_factor = (1 + (5 * size_factor));

	_basal_cost = food_factor * size_factor;
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

/*! Adiciona energia proveniente de algum alimento. */
void EnergySimulator::add_food_energy(float food_energy){
	_food_energy_buffer += food_energy;

	/* A energia é consumida instantaneamente, o buffer é só pra o vetor */
	_energy += food_energy;
}
