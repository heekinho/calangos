/*
 * energySimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "energySimulator.h"
#include "utils.h"

EnergySimulator::EnergySimulator(PT(PlayerHealth) health) : Simulator(health) {
	_initial_energy = 50;

	_energy = _initial_energy;
	_food_energy_buffer = 0.0;

	_basal_cost = 0.0;
	_moviment_cost = 1.0;
	_temperature_cost = 1.0;
	_total_cost = 0.0;

	_num_days = 0;
	_second_update_count = 0;
	_day_energy_buffer = 0;
//	_day_energy_average = 0;

	_day_update_count = 0;
	_month_energy_buffer = 0;
	_month_energy_average = 0;
}

EnergySimulator::~EnergySimulator(){

}

/*! Realiza a simulação atualizando os gastos de energia */
void EnergySimulator::update(float updates_per_hour, float relative_size, float temperature_cost){
	update_basal_cost(updates_per_hour, relative_size);
	update_moviment_cost();
	update_temperature_cost(temperature_cost);
	update_total_cost();
	update_energy();
	_second_update_count++;
}

void EnergySimulator::update_energy(){
	/* Energia de alimento está sendo consumida instantaneamente */
//	_energy = _energy - _total_cost + _food_energy_buffer;

	_energy = _energy - _total_cost;
	_energy = clamp(0, 100, _energy);

	/* Consome a energia do alimento */
	_food_energy_buffer = 0.0;

	/* Coloca a energia do segundo no acumulador */
	_day_energy_buffer += _energy;
}

/*! Atualiza o gasto basal do lagarto */
void EnergySimulator::update_basal_cost(float updates_per_hour, float relative_size){
	float food_factor = (_initial_energy / (health->max_hours_without_food * updates_per_hour));
	float size_factor = (1 + (5 * relative_size));

	_basal_cost = food_factor * size_factor;
}

/* Atualiza o gasto por movimento do lagarto */
void EnergySimulator::update_moviment_cost(){

}

/*! Atualiza o gasto por temperatura do lagarto */
void EnergySimulator::update_temperature_cost(float temperature_cost){
	_temperature_cost = temperature_cost;
}

/*! Calcula o gasto de energia do lagarto.
 * O gasto de energia do lagarto é dado por:
 * Gasto Total = Gasto Basal * Gasto por Temperatura */
void EnergySimulator::update_total_cost(){
	_total_cost = _basal_cost * ( _temperature_cost * _moviment_cost );
}

/*! Retorna a energia do lagarto (de 0 a 100) */
float EnergySimulator::get_energy() const {
	return _energy;
}

/*! Adiciona energia ao lagarto. Note que para adicionar energia proveniente
 *  de alimentos deve-se utilizar add_food_energy pois alguns sistemas precisam
 *  obter essa informação específica (ex.: gráficos) */
void EnergySimulator::add_energy(float energy){
	_energy += energy;
}

/*! Adiciona energia proveniente de algum alimento. */
void EnergySimulator::add_food_energy(float food_energy){
	_food_energy_buffer += food_energy;

	/* A energia é consumida instantaneamente, o buffer é só pra o vetor */
	_energy += food_energy;
	if(_energy > 100){_energy = 100;}
}

/*! Retorna o consumo de alimentação no último ciclo de simulação */
float EnergySimulator::get_food_energy_buffer() const {
	return _food_energy_buffer;
}

/*! Retorna o gasto energético total do último ciclo de simulação */
float EnergySimulator::get_total_cost() const {
	return _total_cost;
}

void EnergySimulator::update_daily_energy_average(){
	_num_days++;

	float _day_energy_average = _day_energy_buffer / float(_second_update_count);
	_month_energy_buffer += _day_energy_average;

	_second_update_count = 0;
	_day_energy_buffer = 0.0;
}

float EnergySimulator::update_monthly_energy_average(){
	/* BUGFIX: Corrige para o debug quando cresce muito rápido */
	if(_day_update_count == 0) return _energy;

	float average = _month_energy_buffer / float(_day_update_count);

	_day_update_count = 0;
	_month_energy_buffer = 0.0;
	_num_days = 0;

	return average;
}
