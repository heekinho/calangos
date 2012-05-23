/*
 * hydrationSimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef HYDRATIONSIMULATOR_H
#define HYDRATIONSIMULATOR_H

#include "playerHealthSimulator.h"

class HydrationSimulator : public Simulator {
public:
	HydrationSimulator(PT(PlayerHealth) health);
	virtual ~HydrationSimulator();

	float get_hydration() const;

	void add_food_hydration(float food_hydration);

	void update_hydration(float relative_humitidy_of_sector, float updates_per_hour);

private:
	void update_humidity_factor(float relative_humitidy_of_sector, float updates_per_hour);

	/*! Hidratação do lagarto. Varia de 0 a 100. */
	float _hydration;

	/*! Armazena em quanto o valor da hidratacao vai cair a cada atualizacao de variaveis
	 *  com base no valor da umidade relativa da microregiao em que o lagarto se encontra */
	float _humidity_factor;

	/*! Inclinacao da reta do cálculo fator umidade, que dependerá da constante: NUM_HORAS_HIDRATACAO */
	float _humidity_factor_a;

	/*! Offset  da reta */
	float _humidity_factor_b;

	/*! Ao consumir alimentos ele vai acumulando no buffer e só então é consumida.
	 *  Importante pois o processo de atualização dos gráficos pode também estar
	 *  interessada nessa informação.
	 *  NOTA: Não estava sendo utilizada */
	float _food_hydration_buffer;
};

#endif /* HYDRATIONSIMULATOR_H */
