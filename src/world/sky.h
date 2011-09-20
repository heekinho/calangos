#ifndef SKY_H
#define SKY_H

#include "pandaFramework.h"
#include "texture.h"
#include "textureCollection.h"
#include "texturePool.h"
#include "ambientLight.h"
#include "referenceCount.h"

class Sky : public NodePath,  public TypedReferenceCount{
public:
	
    ~Sky();
	static PT(Sky) get_default_sky();

	enum {
		AMANHECER, TARDE, ENTARDECER, NOITE, NUBLADO, CHUVOSO
	};

	static void update_transform(const Event* evt, void* data);

	static void update_sol(const Event*, void *data);
	void anda_sol(double);
	void change_sky(int new_sky, int next_sky);
	void fade(int minuto, int hora);

    static void unload_skybox();

	/* private */
	NodePath sol;
	float x, y;
	static float aux;
	static float z;
        
       // Typed Object
    static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "Sky"); }

	static const int STATUS_DAY;
	static const int STATUS_NIGHT;
	static int current_status;

private:
    Sky(const string &model);
	TextureCollection *skies;
	TextureStage *next_sky_stage, *current_sky_stage;
	int current_sky, next_sky;
    static float seta;
    AmbientLight *noite;
    static PT(Sky) sky;
    static TypeHandle _type_handle;

	static bool flag_sol;				//flag para ajudar a controlar o aparecimento do sol
	static int hora_atual;				//hora_atual e hora_anterior vão ajudar no fade das texturas
	static int hora_anterior;
	static int minuto_atual;			//ajudar a controlar o deslocamento do sol pelo ceu
	static int minuto_anterior;
	static float limite;
	static int minuto_atual_sombra;		//ajudar a controlar a sombra
	static int minuto_anterior_sombra;
		

    
};

#endif
