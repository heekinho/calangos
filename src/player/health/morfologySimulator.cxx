/*
 * morfologySimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "morfologySimulator.h"

MorfologySimulator::MorfologySimulator(PT(PlayerHealth) health) : Simulator(health) {
	_ideal_months_to_max_size = 36; //TODO: Configuração
	_child_size_factor = 0.2; //TODO: Configuração

	_max_size = Player::properties.body_size;
	_size = _max_size * _child_size_factor;

	update_relative_size();
}

MorfologySimulator::~MorfologySimulator(){

}


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
void MorfologySimulator::update_size(float month_energy_average){
	/* Obtem a taxa de crescimento de 0 a 1 */
	float growing_rate = month_energy_average * 0.01;

	/* Acima de 90% já deixamos 100% de crescimento */
	if(growing_rate >= 0.9) growing_rate = 1.0;

	/* Obtem o crescimento ideal e real */
	//float ideal_grow_size = (_max_size - _min_size) / _ideal_months_to_max_size;
	float min_size = _max_size * _child_size_factor;
	float ideal_grow_size = (_max_size - min_size) / _ideal_months_to_max_size;
	float real_grow_size = ideal_grow_size * growing_rate;

	/* Enfim atualiza o valor do tamanho */
	_size = _size + real_grow_size;
	_size = clamp(0, _max_size, _size);

	/* Agora atualiza o tamanho relativo do lagarto */
	update_relative_size();
}


float MorfologySimulator::calculate_relative_size(float lizard_size) const {
	float a = health->min_lizard_size * _child_size_factor;
	float b = health->max_lizard_size;
	return compress_range(a, b, _size);
}

/*! Atualiza o tamanho relativo do lagarto, de 0 a 1, que varia do menor tamanho de lagarto
 *  possível (ie. _min_lizard_size * _child_size_factor) e o tamanho máximo de lagarto
 *  (ie. _max_lizard_size), de forma normalizada, é claro. [0, 1].
 *  Esse update é uma forma de cache apenas. */
float MorfologySimulator::update_relative_size(){
	_relative_size = calculate_relative_size(_size);
}


float MorfologySimulator::get_relative_size(){
	return _relative_size;
}

float MorfologySimulator::get_size(){
	return _size;
}

float MorfologySimulator::get_max_size(){
	return _max_size;
}
