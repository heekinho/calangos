#ifndef MODELREPOSITORY_H
#define MODELREPOSITORY_H

#include <string>
#include <vector>

#include "nodePathCollection.h"

#include "objetoJogo.h"
#include "animatedObjetoJogo.h"

#include "player.h"


/*! Um ModelRepository armazena os modelos e abstrai o recurso de instancing do Panda3D */
class ModelRepository {
public:
	// Singleton
	static ModelRepository* get_instance();
	~ModelRepository();

	void add_model(const string &name, const string &path);
	void add_animated_model(const string &name, const string &path, const string &model, const string &filetype = "", //".egg"
			int num_anims = 0, string anims[] = NULL);

	PT(ObjetoJogo) get_model(const string &name);
	PT(ObjetoJogo) get_model_instance(const string &name);

	PT(AnimatedObjetoJogo) get_animated_model(const string &name);
	PT(AnimatedObjetoJogo) get_animated_model_instance(const string &name);


	void load_player_models(const string &lizard_name);
        void load_models();
private:
	/* Controle do Singleton */
	static bool instanceFlag;
	static ModelRepository *single;

	ModelRepository();
	
	void load_vegetals();
	void palettize_mod();

	map<string, PT(ObjetoJogo)> models;
	map<string, PT(AnimatedObjetoJogo)> animated_models;

	
};

#endif
