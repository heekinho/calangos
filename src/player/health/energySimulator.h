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
	virtual ~EnergySimulator();

	void update(float updates_per_hour, float relative_size, float temperature_cost);

	float get_energy() const;

	void add_energy(float energy);
	void add_food_energy(float food_energy);

	void update_daily_energy_average();
	float update_monthly_energy_average();

//	void second_update();
//	void day_update();
//	void month_update();


protected:
	void update_basal_cost(float updates_per_hour, float relative_size);
	void update_moviment_cost();
	void update_temperature_cost(float temperature_cost);
	void update_total_cost();
	void update_energy();

private:
	float _energy;
//	float _min_energy;

	float _food_energy_buffer;

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


	int _num_days;
	int _second_update_count;
	float _day_energy_buffer;
//	float _day_energy_average;

	int _day_update_count;
	float _month_energy_buffer;
	float _month_energy_average;
};

#endif /* ENERGYSIMULATOR_H */
