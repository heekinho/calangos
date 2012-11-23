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

const float PlayerProperties::min_speed = 1.0;
const float PlayerProperties::max_speed = 4.0;

const float PlayerProperties::min_ideal_temperature = 15.0;
const float PlayerProperties::max_ideal_temperature = 50.0;

const float PlayerProperties::min_lizard_density = 15.0;
const float PlayerProperties::max_lizard_density = 100.0;

PlayerProperties::PlayerProperties(){
	/* PT(Texture) color_pattern; */

	species = LizardBase::LS_eurolophosaurus;
	gender = LizardBase::LG_young;

	/* Características do lagarto */
	body_size = (min_body_size + max_body_size) * 0.5;
	head_size = (min_head_size + max_head_size) * 0.5;

	speed = (min_speed + max_speed) * 0.5;
	ideal_tempature = (min_ideal_temperature + max_ideal_temperature) * 0.5;

	/* Dieta do lagarto */
	ant_diet = 0.3;
	plant_diet = 0.3;
	general_diet = 0.4;

	/* Outras habilidades */
	nighttime_activity = false;;
	bury_ability = false;

//	lizards_density = 30;
	lizards_density = 200;
	lizards_aggregation = 0;

}
