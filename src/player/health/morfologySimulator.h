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

	float get_min_size();
	float get_max_size();
	float get_size();

	/*! Atualiza o tamanho real do lagarto, além de atualizar várias variáveis
	 *  importantes da dinâmica interna do lagarto.
	 *  Este evento é chamado mensalmente.
	 *
	 *  A dinâmica de crescimento do lagarto envolve basicamente em verificar os níveis de energia
	 *  mensal para determinar a taxa de crescimento do lagarto.
	 *  - Um lagarto adulto pode variar de X a Y no jogo.
	 *  - O tamanho de um lagarto adulto de tamanho X, começa a vida com 20% do seu tamanho final.
	 *
	 *  @param month_energy_avery indica a média de energia mensal, dada de 0 a 100.
	 */
	void update_size(float month_energy_average){
		/* Obtem a taxa de crescimento de 0 a 1 */
		float growing_rate = month_energy_average * 0.01;

		/* Acima de 90% já deixamos 100% de crescimento */
		if(growing_rate >= 0.9) growing_rate = 1.0;

		/* Obtem o crescimento ideal e real */
		float ideal_grow_size = (_max_size - _min_size) / _ideal_months_to_max_size;
		float real_grow_size = ideal_grow_size * growing_rate;

		/* Enfim atualiza o valor do tamanho */
		_size = _size + real_grow_size;
	}

	// Mouth size
protected:


private:
	/*! Quantidade de meses que o lagarto leva para atingir seu tamanho máximo idealmente */
	int _ideal_months_to_max_size;

	/*! Tamanho mínimo e máximo (em cm) do lagarto */
	float _min_size;
	float _max_size;

	/*! Tamanho (em cm) do lagarto */
	float _size;

};

#endif /* MORFOLOGYSIMULATOR_H */
