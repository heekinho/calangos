/*
 *  playerProperties.h
 *  Created on: 14/04/2011
 *  Author: heekinho
 */

#ifndef PLAYERPROPERTIES_H
#define PLAYERPROPERTIES_H

//struct PlayerProperties {
class PlayerProperties {
public:
	PlayerProperties(){};
//	virtual ~PlayerProperties(){};

//private:
	/* Informações do modelo do lagarto */
	int  lizard_type;
	/* PT(Texture) color_pattern; */

	/* Características do lagarto */
	float speed;
	float body_size;
	float head_size;
	float ideal_tempature;

	/* Dieta do lagarto */
	float ant_diet;
	float plant_diet;
	float general_diet;

	/* Outras habilidades */
	bool nighttime_activity;
	bool bury_ability;

	/* Informações gerais dos lagartos */
	float lizards_density;
	float lizards_aggregation;
};

#endif
