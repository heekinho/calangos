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

	/*! Tamanho máximo que o lagarto pode atingir ao fim da vida. (geral) */
	float max_lizard_size;
	/*! Tamanho mínimo que o lagarto pode atingir ao fim da vida. (geral) */
	float min_lizard_size;

	/*! Temperatura ideal do lagarto sob a qual sua saúde vai ficar ótima */
	float ideal_temperature;
	float max_temperature;
	float min_temperature;
	float temperature_tolerance;

	/*! Quantidade de horas que o lagarto vive sem alimentação */
	float max_hours_without_food;

	/*! Quantidade máxima de horas que o lagarto irá sobreviver submetido
	 *  a uma baixa umidade, definida por "humidity_param". (ex.: 48 horas) */
	float max_hours_with_low_hydration;

	/*! Limiar a partir da onde a umidade começa a afetar a hidratação.
	 *  Ex.: = 40.0  ->  umidade do ambiente acima disso não tem efeito de decaimento */
	float humidity_affects_hidration;

	/*! Parâmetro de baixa umidade usado para indicar a morte do lagarto depois de
	 *  "max_hours_with_low_hydration" (geralmente 48 horas). */
	float humidity_param;
	float min_hydration;
	float min_energy; // stamina?
	float energy_cost_low_temperature;
	float energy_cost_high_temperature;
	float thermal_equilibrium_speed;
};

#endif /* PLAYERHEALTH_H */
