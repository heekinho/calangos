/*
 * morfologySimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef MORFOLOGYSIMULATOR_H
#define MORFOLOGYSIMULATOR_H

#include "playerHealthSimulator.h"

class MorfologySimulator : public Simulator {
public:
	MorfologySimulator(PT(PlayerHealth) health);
	virtual ~MorfologySimulator();

//	float get_min_size();
	float get_max_size();
	float get_size();

	float get_relative_size();
	void update_size(float month_energy_average);

	// Mouth size
protected:
	float update_relative_size();

private:
	/*! Quantidade de meses que o lagarto leva para atingir seu tamanho máximo idealmente */
	int _ideal_months_to_max_size;

	/*! Indica a porcentagem do tamanho do lagarto em relação ao seu tamanho adulto.
	 *  Ex.: 0.2 indica que um lagarto de 40cm adulto terá 4cm no seu primeiro mês. */
	float _child_size_factor;

	/*! Indica o tamanho relativo do lagarto, de 0 a 1, que varia do menor tamanho de lagarto
	 *  possível (ie. _min_lizard_size * _child_size_factor) e o tamanho máximo de lagarto
	 *  (ie. _max_lizard_size), de forma normalizada, é claro. [0, 1] */
	float _relative_size;

	/*! Tamanho mínimo e máximo (em cm) do lagarto */
//	float _min_size;

	/*! Obtem o tamanho máximo (em cm) que este lagarto pode atingir */
	float _max_size;

	/*! Tamanho (em cm) do lagarto */
	float _size;

};

#endif /* MORFOLOGYSIMULATOR_H */
