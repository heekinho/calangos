
#include <cmath>
#include <assert.h>

#include "nodePath.h"


#include "sky.h"

#include "climaTempo.h"
#include "cameraControl.h"

#include "simdunas.h"
#include "timeControl.h"

#include "texture.h"
#include "texturePool.h"
#include "textureStageCollection.h"
#include "textureStage.h"

#include "lvecBase4.h"
#include "timeControl.h"
#include "terrain.h"

//TypeHandle Sky::_type_handle;
Sky::Sky(const string &model) :
NodePath(window->load_model(render, model)) {
	aux = -180;
	z = -10;
	seta = 1.0; //variável que vai auxiliar no fade das texturas
	flag_sol = false;
	hora_atual = 0;
	hora_anterior = 0;
	minuto_atual = 0;
	minuto_anterior = 0;
	limite = 0.0;
	minuto_anterior_sombra = 0;
	minuto_atual_sombra = 0;
	_current_status = SS_day;



	set_scale(512);
	set_bin("background", 10);
	set_depth_write(false);
	set_depth_test(false);
	set_light_off();

	next_sky_stage = new TextureStage("next_sky_stage");
	current_sky_stage = new TextureStage("current_sky_stage");

	skies = TextureCollection();

	//ATENTION: Verificar ENUM ao mudar aki.
	skies.add_texture(TexturePool::load_texture("models/skies/amanhecer.jpg"));
	skies.add_texture(TexturePool::load_texture("models/skies/tarde.jpg"));
	skies.add_texture(TexturePool::load_texture("models/skies/entardecer.jpg"));
	skies.add_texture(TexturePool::load_texture("models/skies/noite.jpg"));
	skies.add_texture(TexturePool::load_texture("models/skies/nublado.jpg"));
	skies.add_texture(TexturePool::load_texture("models/skies/chuvoso.jpg"));

	/* Configuração Inicial */
	int hora = TimeControl::get_instance()->get_hora();
	if ((hora >= 19 && hora <= 23) || (hora >= 0 && hora < 6)) {
		if (ClimaTempo::get_instance()->get_chuva_today() != 0) //verificando se o dia vai ser chovoso
		change_sky(ST_chuvoso, ST_noite);
		else change_sky(ST_amanhecer, ST_noite);
	}
	else if (hora >= 6 && hora < 8) {
		if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//verificando se o dia vai ser chovoso
			change_sky(ST_chuvoso, ST_noite);//se o dia for chuvoso o dia amanhece 7 horas
		}
		else change_sky(ST_tarde, ST_amanhecer);
	}
	else if (hora >= 8 && hora <= 17) {

		if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//verificando se o dia vai ser chovoso
			change_sky(ST_noite, ST_chuvoso);
		}
		else if (hora == 17) { //caso especial da tarde
			change_sky(ST_noite, ST_entardecer);
		}
		else
		change_sky(ST_entardecer, ST_tarde);
	}
	else if (hora >= 18 && hora < 19) {

		if (ClimaTempo::get_instance()->get_chuva_today() != 0) //verificando se o dia vai ser chovoso
		change_sky(ST_noite, ST_chuvoso);
		else change_sky(ST_noite, ST_entardecer);
	}

	/* Modo de combinação das texturas (interpolate) */
	next_sky_stage->set_combine_rgb(TextureStage::CM_interpolate,
			TextureStage::CS_previous, TextureStage::CO_src_color,
			TextureStage::CS_texture, TextureStage::CO_src_color,
			TextureStage::CS_constant, TextureStage::CO_src_alpha);

	/* A cada evento de minuto do jogo será atualizada a posição do sol */
	event_handler->add_hook(TimeControl::EV_pass_minute, update_sun, this);


	x = 0;
	y = 0;

	/* Configurando a posição do sol */
	sol = window->load_model(render, "models/skies/sol.png");
	sol.set_scale(10);
	sol.set_pos(x, y, z);
	sol.set_billboard_point_eye(0);
	sol.hide();


	/* aplicando a luz na raiz da cena (todos os objetos da cena serão atingidos) */
	_ambient_light = new AmbientLight("noite");
	render.set_light(NodePath(_ambient_light));

	/* Verifica se a hora de início é dia ou noite para setar a luz do ambiente */
	if ((hora >= 19 && hora <= 23) || (hora >= 0 && hora < 6)) {
		_ambient_light->set_color(LVecBase4f(0, 0.18, 0.25, 1));
	}
	else if (hora >= 6 && hora < 19) {
		if (ClimaTempo::get_instance()->get_chuva_today() != 0) {
			/* Se o dia for chuvoso até 7 horas ainda vai ta tudo escuro */
			if (hora <= 7) _ambient_light->set_color(LVecBase4f(0, 0.18, 0.25, 1));
			else _ambient_light->set_color(LVecBase4f(0.5, 0.68, 0.75, 1));
		}
		/* Se o dia não for chuvoso vai estar tudo bem claro */
		else _ambient_light->set_color(LVecBase4f(1, 1, 1, 1));
	}

	event_handler->add_hook(TimeControl::EV_pass_frame, update_transform, this);
}

Sky::~Sky(){
     this->sol.remove_node();
     remove_node();
}

/*! Atualiza a posição do skybox em relação à camera */
void Sky::update_transform(const Event* evt, void* data){
	PT(Sky) this_sky = ((PT(Sky))(Sky*)data);
	PT(CameraNode) camera = CameraControl::get_instance()->get_current_camera();

	/* Com reparent_to e compass dá quase certo, mais assim funciona totalmente */
	this_sky->set_pos(camera->get_pos(render));
	this_sky->set_z(-50);
}

/*! Evento de atualização do sol */
void Sky::update_sun(const Event*, void *data) {
	((Sky*) data)->update_sun();
}

/*! Atualização do sol */
void Sky::update_sun(){
	int hora = TimeControl::get_instance()->get_hora();
	int minuto = TimeControl::get_instance()->get_minuto();
	minuto_anterior = minuto_atual;
	minuto_atual = minuto;

	if (hora >= 5 && hora < 12) {

		//colocando de fato o sol na cena
		if (hora >= 5 && !flag_sol && ClimaTempo::get_instance()->get_chuva_today() == 0) {
			sol.show();
			flag_sol = true;

		}

//		if ((int) fabs((float) minuto_atual - (float) minuto_anterior) < 40) {
		if (minuto_atual > minuto_anterior) {
			z = z + (minuto_atual - minuto_anterior);
			aux = aux + (minuto_atual - minuto_anterior);
			update_sun_pos(aux);
		}

		if (hora >= 5 && hora < 6) {//dia amanhecendo
			fade(minuto, hora);//chamando o método de interpolação das texturas
		}

		if (hora >= 7 && hora < 8) {//dia amanhece totalmente
			fade(minuto, hora);//chamando o método de interpolação das texturas
		}

	}

	else if (hora >= 12 && hora < 20) {
		//if ((int) fabs((float) minuto_atual - (float) minuto_anterior) < 40) {
		if (minuto_atual > minuto_anterior) {
			z = z - (minuto_atual - minuto_anterior);//depois do meio dia a variável z decrementa para o sol se por
			aux = aux + (minuto_atual - minuto_anterior);
			update_sun_pos(aux);
		}

		if (hora >= 16 && hora < 17) {//entardecendo
			fade(minuto, hora);//chamando o método de mudança de textura
		}
		if (hora >= 18 && hora < 19) {//escurece completamente
			fade(minuto, hora);//chamando o método de mudança de textura
		}

	}
	else if (hora >= 20 && flag_sol) {
		z = -10;
		aux = -180;
		sol.hide();//retirando o sol da cena
		flag_sol = false;

	}
}

/*! Atualiza a posição do sol no ambiente */
void Sky::update_sun_pos(double pos) {
	this->x = pos;
	this->y = pos;

	sol.set_pos(x, y, z);
}

/*! Após o fade troca a textura atual pela próxima */
void Sky::change_sky(int new_sky, int previous_sky) {
	set_texture(current_sky_stage, skies.get_texture(previous_sky));
	set_texture(next_sky_stage, skies.get_texture(new_sky));

}

void Sky::fade(int minuto, int hora) {
    hora_anterior = hora_atual;
    hora_atual = hora;
    minuto_anterior_sombra = minuto_atual_sombra;
    minuto_atual_sombra = minuto;

    limite = abs(minuto_atual_sombra - minuto_anterior_sombra);//diferença de minutos para setar na sombra, ficando assim indepedente do minuto virtual
	if (limite > 50) limite = 0.0;
	

    if (hora_anterior != hora_atual) {//se forem diferentes é hora de mudar de textura ficando indepedente do minuto virtual
        limite = 0.0;
        if (hora == 5) {
            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia não está  chovoso
            	_current_status = SS_day;
                change_sky(ST_amanhecer, ST_noite);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }

        } else if (hora == 7) {
            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia não está  chovoso
                change_sky(ST_tarde, ST_amanhecer);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            } else {
            	_current_status = SS_rainy_day;
                change_sky(ST_chuvoso, ST_noite); //caso esteja chuvoso o dia  só nasce as sete horas
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }


        } else if (hora == 16) {
            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia está  chovoso
                change_sky(ST_entardecer, ST_tarde);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }
        } else if (hora == 18) {

            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia está  chovoso
            	_current_status = SS_night;
                change_sky(ST_noite, ST_entardecer);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }
            else {
            	_current_status = SS_rainy_night;
                change_sky(ST_noite, ST_chuvoso); //caso esteja chuvoso
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }

        }

    }


//	float shadow_alpha = Terrain::get_default_terrain()->get_shadows()->get_alpha();

    if (hora >= 18 && hora < 19) {//anoitecendo... escurecendo o ambiente

        if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//se tiver chuvendo....vai ja vai ta um pouco escuro

            if (seta < 0.5) {
                _ambient_light->set_color(LVecBase4f(seta, seta + 0.18, seta + 0.25, 1));
            }

//            //retirando as sombras das arvores a noite
			Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(0.01 * limite);
            Terrain::get_default_terrain()->get_shadows()->update_shadows();
//            Terrain::get_default_terrain()->get_shadows()->set_alpha(shadow_alpha - 0.01 * limite);

            
        } else
            _ambient_light->set_color(LVecBase4f(seta, seta + 0.18, seta + 0.25, 1));

//        //retirando as sombras das arvores a noite
        Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(0.01 * limite);
        Terrain::get_default_terrain()->get_shadows()->update_shadows();
//        Terrain::get_default_terrain()->get_shadows()->set_alpha(shadow_alpha + 0.01 * limite);
      
    }
    else if (hora >= 5 && hora < 6) {//amanhecendo....clariando novamente o ambiente

        if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//só clareia as 5 se não tiver chuvendo

            if (minuto > 1) {//para não escurecer totalmente antes de começar a clariar
                _ambient_light->set_color(LVecBase4f(minuto * 0.0166, 0.18 + (minuto * 0.0166), 0.25 + (minuto * 0.0166), 1));
                //colocando as sombras de volta
               
                    Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(-0.01 * limite);
                    Terrain::get_default_terrain()->get_shadows()->update_shadows();
//                Terrain::get_default_terrain()->get_shadows()->set_alpha(shadow_alpha + 0.01 * limite);
                    
                

            }
        }
    }
    else if (hora >= 7 && hora < 8) {
        if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//se tiver chuvendo.....amanhece as 7 e não vai clariar tudo
			_current_status = SS_rainy_day;

            float aux = minuto * 0.0166;
            if (aux < 0.5 && minuto > 1) {//para não escurecer totalmente antes de começar a clariar
                _ambient_light->set_color(LVecBase4f(minuto * 0.0166, 0.18 + (minuto * 0.0166), 0.25 + (minuto * 0.0166), 1));

            }
            //colocando as sombras de volta
            if (TimeControl::get_instance()->get_dia() > 1) {//se não for o primeiro dia
                
                    Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(-0.01 * limite);
                    Terrain::get_default_terrain()->get_shadows()->update_shadows();
//            	Terrain::get_default_terrain()->get_shadows()->set_alpha(shadow_alpha + 0.01 * limite);
                    
                
            }
        }

    }


    //simdunas_cat.debug()<<"Hora: "<<TimeControl::get_instance()->get_hora()<<"Minuto : "<<TimeControl::get_instance()->get_minuto()<<endl;
    //simdunas_cat.debug()<<"Seta: "<<seta<<endl;
    if (ClimaTempo::get_instance()->get_chuva_today() != 0) {
        if (hora != 16 && hora != 5) {//se o dia tiver chuvoso só faz o fade, se a hora for diferente de 16 e 7
            seta = 1 - (0.0166 * minuto); //deixando indepedente do minuto virtual, caso de saltos de alguns minutos continua certo. Porém se saltar mais de uma hora vai da pau!!!
            next_sky_stage->set_color(LVecBase4f(0, 0, 0, seta));
        }

    } else {//caso o dia não seja chuvoso chama normalmente

        seta = 1 - (0.0166 * minuto); //deixando indepedente do minuto virtual, caso de saltos de alguns minutos continua certo. Porém se saltar mais de uma hora vai da pau!!!
        next_sky_stage->set_color(LVecBase4f(0, 0, 0, seta));
    }
}
