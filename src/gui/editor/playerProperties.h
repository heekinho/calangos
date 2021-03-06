/*
 *  playerProperties.h
 *  Created on: 14/04/2011
 *  Author: heekinho
 */

#ifndef PLAYERPROPERTIES_H
#define PLAYERPROPERTIES_H

#include "lizardBase.h"

//struct PlayerProperties {
class PlayerProperties {
public:
	PlayerProperties();
//	virtual ~PlayerProperties(){};

//private:
	/* Informações do modelo do lagarto */
	//int  lizard_type;
	LizardBase::LizardSpecies species;
	LizardBase::LizardGender gender;

	/* PT(Texture) color_pattern; */

	/* Características do lagarto */
	static const float min_body_size;
	static const float max_body_size;
	float body_size;

	float head_size;
	static const float min_head_size; /* dobro do tamanho */
	static const float max_head_size; /* metade do tamanho */

	float speed;
	static const float min_speed;
	static const float max_speed;

	float ideal_tempature;
	static const float min_ideal_temperature;
	static const float max_ideal_temperature;

	/* Dieta do lagarto */
	float ant_diet;
	float plant_diet;
	float general_diet;

	/* Outras habilidades */
	bool nighttime_activity;
	bool bury_ability;

	/* Informações gerais dos lagartos */
	static const float min_lizard_density;
	static const float max_lizard_density;
	float lizards_density;
	float lizards_aggregation;

};

#endif
