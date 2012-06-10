#ifndef SKY_H
#define SKY_H

#include "pandaFramework.h"
#include "texture.h"
#include "textureCollection.h"
#include "texturePool.h"
#include "ambientLight.h"
#include "referenceCount.h"

class Sky : public NodePath,  public TypedReferenceCount {
public:
    Sky(const string &model);
    virtual ~Sky();

    /* Tipos de texturas possíveis para o céu */
	enum SkyTexture {
		ST_amanhecer,
		ST_tarde,
		ST_entardecer,
		ST_noite,
		ST_nublado,
		ST_chuvoso
	};

	enum SkyStatus {
		SS_day,
		SS_rainy_day,
		SS_night,
		SS_rainy_night
	};

	static void update_transform(const Event* evt, void* data);

	void update_sun();
	static void update_sun(const Event*, void *data);

	void update_sun_pos(double);
	void change_sky(int new_sky, int next_sky);
	void fade(int minuto, int hora);

//    static void unload_skybox();

	/* Resolvendo ambiguidades */
    static TypeHandle get_class_type() { return NodePath::get_class_type(); }
	static void init_type() { NodePath::init_type(); }
private:
	SkyStatus _current_status;

	TextureCollection skies;

	/* Nós precisamos de dois estágios para fazer o cross fading */
	PT(TextureStage) next_sky_stage;
	PT(TextureStage) current_sky_stage;

	int next_sky;
	int current_sky;

    float seta;
    PT(AmbientLight) _ambient_light;


	/* private */
	NodePath sol;
	float x, y;
	float aux;
	float z;

	bool flag_sol;				//flag para ajudar a controlar o aparecimento do sol
	int hora_atual;				//hora_atual e hora_anterior vão ajudar no fade das texturas
	int hora_anterior;
	int minuto_atual;			//ajudar a controlar o deslocamento do sol pelo ceu
	int minuto_anterior;
	float limite;
	int minuto_atual_sombra;		//ajudar a controlar a sombra
	int minuto_anterior_sombra;

};

#endif
