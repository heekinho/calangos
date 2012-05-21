/*
 * playerHealth.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef PLAYERHEALTH_H
#define PLAYERHEALTH_H

#include "simdunas.h"
#include "referenceCount.h"

/*! Se tornará um facade depois? Fazer uso dos simuladores? */
class PlayerHealth : public ReferenceCount {
public:
	PlayerHealth();
	virtual ~PlayerHealth();

	void load_health(const Filename &path);




	float temperature;

//protected:
	/* Valores configuraveis */
	float ideal_temperature;
	float max_temperature;
	float min_temperature;
	float temperature_tolerance;
	float max_hours_without_food;
	float max_hours_with_low_hidration;
	/* Parece ser o limiar a partir da onde a umidade começa a afetar a hidratação.
	 * Ex.: = 40.0  ->  umidade do ambiente acima disso não tem efeito de decaimento */
	float humidity_affects_hidration;

	/* O que é isso? */
	float humidity_param; // moisture?
	float min_hydration;
	float min_energy; // stamina?
	float energy_cost_low_temperature;
	float energy_cost_high_temperature;
	float thermal_equilibrium_speed;
};

#endif /* PLAYERHEALTH_H */
