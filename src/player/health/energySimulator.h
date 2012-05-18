/*
 * energySimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef ENERGYSIMULATOR_H
#define ENERGYSIMULATOR_H

#include "playerHealthSimulator.h"

class EnergySimulator : public Simulator {
public:
	EnergySimulator(PT(PlayerHealth) health);
	void update();

	void update_basal_cost();
	void update_moviment_cost();
	void update_temperature_cost();
	void update_total_cost();

private:
	float _energy;
	float _min_energy;

	/*! Gasto metabólico basal inerente ao lagarto.
	 *  Este gasto é o considerado para levar o lagarto à morte passados "max_hours_without_food",
	 *  sem levar em conta os outros tipos de gastos */
	float _basal_cost;

	/*! Gasto por movimento. Este gasto modula o gasto basal (ex.: 1.2 aumenta o gasto em 20%) */
	float _moviment_cost;

	/*! Gasto por temperatura. Este gasto modula o gasto basal (ex.: 1.2 aumenta o gasto em 20%) */
	float _temperature_cost;

	/*! Gasto total de energia, em um update (segundo (virtual/real?)).
	 *  Corresponde à soma do gasto basal, custo de movimento e custo de temperatura */
	float _total_cost;

	/*! Energia inicial do lagarto. */
	float _initial_energy;

};

#endif /* ENERGYSIMULATOR_H */
