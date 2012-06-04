#ifndef MODELREPOSITORY_H
#define MODELREPOSITORY_H

#include <string>
#include <vector>

#include "nodePathCollection.h"

#include "objetoJogo.h"
#include "animatedObjetoJogo.h"
#include "referenceCount.h"
//#include "player.h"


/*! Um ModelRepository armazena os modelos e abstrai o recurso de instancing do Panda3D */
class ModelRepository : public ReferenceCount {
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

	void set_lagarto_personalizado(PT(Texture) custom);
	PT(Texture) get_lagarto_personalizado();
         void set_nivel_camuflagem(float terreno_dia,float terreno_noite,float sombra, float folhagem);
         float get_nivel_camuflagem_terreno_dia(){
             return nivel_camuflagem_terreno_dia;
         }
         float get_nivel_camuflagem_terreno_noite(){
             return nivel_camuflagem_terreno_noite;
         }
         float get_nivel_camuflagem_sombra(){
             return nivel_camuflagem_sombra;
         }
         float get_nivel_camuflagem_folhagem(){
             return nivel_camuflagem_folhagem;
         }

private:
        //armazena os níveis de camuflagem  do player editado para variadas situações:
        float nivel_camuflagem_terreno_dia;
        float nivel_camuflagem_terreno_noite;
        float nivel_camuflagem_sombra;
        float nivel_camuflagem_folhagem;

private:
	/* Controle do Singleton */
	static bool instanceFlag;
	static ModelRepository *single;

	PT(Texture) lagartoPersonalizado;

	ModelRepository();
	
	void load_vegetals();
	void palettize_mod();

	map<string, PT(ObjetoJogo)> models;
	map<string, PT(AnimatedObjetoJogo)> animated_models;

	
};

#endif
