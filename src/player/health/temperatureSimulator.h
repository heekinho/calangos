/*
 * temperatureSimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef TEMPERATURESIMULATOR_H
#define TEMPERATURESIMULATOR_H

#include "playerHealthSimulator.h"
#include "playerHealth.h"

class TemperatureSimulator : public Simulator {
public:
	TemperatureSimulator(PT(PlayerHealth) health);

	void update_thermal_equilibrium_speed(float relative_size);

	float perceived_temperature();

	float get_temperature() const;
	float get_temperature_cost();

	float get_lethargy() const;


	/*! Atualiza a temperatura interna do lagarto */
	void update_temperature();
	void update_lethargy();

private:
	/*! Temperatura interna do lagarto */
	float _temperature;

	float _lethargy;

	/*! Velocidade que o lagarto demora para atingir o equilíbrio.
	 *  Depende do tamanho do lagarto. Quanto maior o lagarto menor a velocidade */
	float _current_thermal_equilibrium_speed;

};

#endif /* TEMPERATURESIMULATOR_H */
