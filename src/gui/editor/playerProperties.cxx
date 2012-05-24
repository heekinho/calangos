/*
 *  playerProperties.cxx
 *  Created on: 14/04/2011
 *  Author: heekinho
 */

#include "playerProperties.h"

/* Esses valores podem vir por configuração */

const float PlayerProperties::min_body_size = 20; /* dobro do tamanho */
const float PlayerProperties::max_body_size = 60; /* metade do tamanho */

const float PlayerProperties::min_head_size = 0.5; /* dobro do tamanho */
const float PlayerProperties::max_head_size = 2.0; /* metade do tamanho */

const float PlayerProperties::min_speed = 10;
const float PlayerProperties::max_speed = 40;

const float PlayerProperties::min_ideal_temperature = 15.0;
const float PlayerProperties::max_ideal_temperature = 50.0;

const float PlayerProperties::min_lizard_density = 15.0;
const float PlayerProperties::max_lizard_density = 100.0;

PlayerProperties::PlayerProperties(){
	/* PT(Texture) color_pattern; */

	/* Características do lagarto */
	body_size = 30.0; // Configuration.
	head_size;

	speed;
	ideal_tempature;

	/* Dieta do lagarto */
	ant_diet;
	plant_diet;
	general_diet;

	/* Outras habilidades */
	nighttime_activity = false;;
	bury_ability = false;

	lizards_density = 1000;
	lizards_aggregation = 0;
}
