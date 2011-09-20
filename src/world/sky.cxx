
#include <cmath>
#include <assert.h>

#include "nodePath.h"


#include "sky.h"


#include "simdunas.h"
#include "timeControl.h"

#include "texture.h"
#include "texturePool.h"
#include "textureStageCollection.h"
#include "textureStage.h"

#include "lvecBase4.h"
#include "timeControl.h"
#include "terrain.h"

float Sky::aux = -180;
float Sky::z = -10;
float Sky::seta = 1.0;//variável que vai auxiliar no fade das texturas
PT(Sky)  Sky::sky=NULL;
bool Sky::flag_sol=false;
int Sky::hora_atual=0;
int Sky::hora_anterior=0;
 int Sky::minuto_atual=0;
 int Sky::minuto_anterior=0;
 float Sky::limite=0.0;
 int Sky::minuto_anterior_sombra=0;
 int Sky::minuto_atual_sombra=0;

const int Sky::STATUS_DAY = 0;
const int Sky::STATUS_NIGHT = 1;
int Sky::current_status = 0;

TypeHandle Sky::_type_handle;
Sky::Sky(const string &model) :
NodePath(window->load_model(render, model)) {
	set_bin("background", 10);
	set_depth_write(false);
	set_depth_test(false);
	set_light_off();

	next_sky_stage = new TextureStage("next_sky_stage");
	current_sky_stage = new TextureStage("current_sky_stage");

	this->skies = new TextureCollection();

	//ATENTION: Verificar ENUM ao mudar aki.
	this->skies->add_texture(TexturePool::load_texture("models/skies/amanhecer.jpg"));
	this->skies->add_texture(TexturePool::load_texture("models/skies/tarde.jpg"));
	this->skies->add_texture(TexturePool::load_texture("models/skies/entardecer.jpg"));
	this->skies->add_texture(TexturePool::load_texture("models/skies/noite.jpg"));
	this->skies->add_texture(TexturePool::load_texture("models/skies/nublado.jpg"));
	this->skies->add_texture(TexturePool::load_texture("models/skies/chuvoso.jpg"));

	/* Configuração Inicial */
	int hora = TimeControl::get_instance()->get_hora();
	if ((hora >= 19 && hora <= 23) || (hora >= 0 && hora < 6)) {
		if (ClimaTempo::get_instance()->get_chuva_today() != 0) //verificando se o dia vai ser chovoso
		change_sky(CHUVOSO, NOITE);
		else change_sky(AMANHECER, NOITE);
	}
	else if (hora >= 6 && hora < 8) {
		if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//verificando se o dia vai ser chovoso
			change_sky(CHUVOSO, NOITE);//se o dia for chuvoso o dia amanhece 7 horas
		}
		else change_sky(TARDE, AMANHECER);
	}
	else if (hora >= 8 && hora <= 17) {

		if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//verificando se o dia vai ser chovoso
			change_sky(NOITE, CHUVOSO);
		}
		else if (hora == 17) { //caso especial da tarde
			change_sky(NOITE, ENTARDECER);
		}
		else
		change_sky(ENTARDECER, TARDE);
	}
	else if (hora >= 18 && hora < 19) {

		if (ClimaTempo::get_instance()->get_chuva_today() != 0) //verificando se o dia vai ser chovoso
		change_sky(NOITE, CHUVOSO);
		else change_sky(NOITE, ENTARDECER);
	}

	//modo de combinação das texturas (interpolate)
	next_sky_stage->set_combine_rgb(TextureStage::CM_interpolate,
			TextureStage::CS_previous, TextureStage::CO_src_color,
			TextureStage::CS_texture, TextureStage::CO_src_color,
			TextureStage::CS_constant, TextureStage::CO_src_alpha);

	//a cada evento de minuto do jogo será atualizada a posição do sol
	event_handler->add_hook(TimeControl::EV_pass_minute, update_sol, this);

	x = 0;
	y = 0;

	sol = window->load_model(render, "models/skies/sol.png");
	sol.set_scale(10);
	sol.set_pos(x, y, z);
	sol.set_billboard_point_eye(0);
	sol.hide();

	//iluminação do sol
	//AmbientLight *amb = new AmbientLight("sol");
	//amb->set_color(LVecBase4f(1, 0.8, 0, 1));
	//sol.set_light(amb); /* Que é isso? Atribuindo iluminação só ao sol? */

	//condição inicial do ambiente (noite)
	//aplicando a luz na raiz da cena (todos os objetos da cena serão atingidos)
	this->noite = new AmbientLight("noite");
	render.set_light(this->noite);

	//verificando se a hora de início é dia ou noite para setar a luz do ambiente
	if ((hora >= 19 && hora <= 23) || (hora >= 0 && hora < 6)) {
		this->noite->set_color(LVecBase4f(0, 0.18, 0.25, 1));
	}
	else if (hora >= 6 && hora < 19) {
		if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//se for chuvoso
			if (hora <= 7) {//se o dia for chuvoso até 7 horas ainda vai ta tudo escuro
				this->noite->set_color(LVecBase4f(0, 0.18, 0.25, 1));
			}
			else this->noite->set_color(LVecBase4f(0.5, 0.68, 0.75, 1));
		}
		else this->noite->set_color(LVecBase4f(1, 1, 1, 1));
	}

	event_handler->add_hook(TimeControl::EV_pass_frame, update_transform, this);
}

/*! Atualiza a posição do skybox em relação à camera */
void Sky::update_transform(const Event* evt, void* data){
	PT(Sky) this_sky = ((PT(Sky))(Sky*)data);
	PT(CameraNode) camera = CameraControl::get_instance()->get_current_camera();

	/* Com reparent_to e compass dá quase certo, mais assim funciona totalmente */
	this_sky->set_pos(camera->get_pos(render));
	this_sky->set_z(-50);
}

PT(Sky) Sky::get_default_sky(){
    if(sky==NULL){
		nout << "Criando Ceu..." << endl;
		sky = new Sky("models/skybox");
		sky->set_scale(512);
        //sky->set_pos(256.0,256.0,-300.0);
        return sky;
    }
    else
	return sky;
}


void Sky::update_sol(const Event*, void *data) {
	Sky *the_sky = (Sky*) data;
	int hora = TimeControl::get_instance()->get_hora();
	int minuto = TimeControl::get_instance()->get_minuto();
	minuto_anterior = minuto_atual;
	minuto_atual = minuto;

	if (hora >= 5 && hora < 12) {

		//colocando de fato o sol na cena
		if (hora >= 5 && !flag_sol && ClimaTempo::get_instance()->get_chuva_today() == 0) {
			the_sky->sol.show();
			flag_sol = true;

		}

//		if ((int) fabs((float) minuto_atual - (float) minuto_anterior) < 40) {
		if (minuto_atual > minuto_anterior) {
			z = z + (minuto_atual - minuto_anterior);
			aux = aux + (minuto_atual - minuto_anterior);
			the_sky->anda_sol(aux);
		}

		if (hora >= 5 && hora < 6) {//dia amanhecendo
			current_status = STATUS_DAY;
			the_sky->fade(minuto, hora);//chamando o método de interpolação das texturas
		}

		if (hora >= 7 && hora < 8) {//dia amanhece totalmente
			the_sky->fade(minuto, hora);//chamando o método de interpolação das texturas
		}

	}

	else if (hora >= 12 && hora < 20) {
		//if ((int) fabs((float) minuto_atual - (float) minuto_anterior) < 40) {
		if (minuto_atual > minuto_anterior) {
			z = z - (minuto_atual - minuto_anterior);//depois do meio dia a variável z decrementa para o sol se por
			aux = aux + (minuto_atual - minuto_anterior);
			the_sky->anda_sol(aux);
		}

		if (hora >= 16 && hora < 17) {//entardecendo
			the_sky->fade(minuto, hora);//chamando o método de mudança de textura
		}
		if (hora >= 18 && hora < 19) {//escurece completamente
			current_status = STATUS_NIGHT;
			the_sky->fade(minuto, hora);//chamando o método de mudança de textura
		}

	}
	else if (hora >= 20 && flag_sol) {
		z = -10;
		aux = -180;
		the_sky->sol.hide();//retirando o sol da cena
		flag_sol = false;

	}

}

void Sky::anda_sol(double pos) {
	this->x = pos;
	this->y = pos;

	sol.set_pos(x, y, z);

}

void Sky::change_sky(int new_sky, int previous_sky) {
	//troca a textura atual pela próxima
	set_texture(current_sky_stage, skies->get_texture(previous_sky));
	set_texture(next_sky_stage, skies->get_texture(new_sky));

}

void Sky::fade(int minuto, int hora) {

    

    hora_anterior = hora_atual;
    hora_atual = hora;
    minuto_anterior_sombra = minuto_atual_sombra;
    minuto_atual_sombra = minuto;

    limite = abs(minuto_atual_sombra - minuto_anterior_sombra);//diferença de minutos para setar na sombra, ficando assim indepedente do minuto virtual
	if(limite>50)limite=0.0;
	


    if (hora_anterior != hora_atual) {//se forem diferentes é hora de mudar de textura ficando indepedente do minuto virtual
        limite = 0.0;
        if (hora == 5) {
            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia não está  chovoso
                change_sky(AMANHECER, NOITE);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }

        } else if (hora == 7) {
            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia não está  chovoso
                change_sky(TARDE, AMANHECER);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            } else {
                change_sky(CHUVOSO, NOITE); //caso esteja chuvoso o dia  só nasce as sete horas
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }


        } else if (hora == 16) {
            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia está  chovoso
                change_sky(ENTARDECER, TARDE);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }
        } else if (hora == 18) {

            if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//verificando se o dia está  chovoso
                change_sky(NOITE, ENTARDECER);
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }
            else {
                change_sky(NOITE, CHUVOSO); //caso esteja chuvoso
                seta = 1.0; //a variável volta ao esado inicial para o próximo
            }

        }

    }
    if (hora >= 18 && hora < 19) {//anoitecendo... escurecendo o ambiente

        if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//se tiver chuvendo....vai ja vai ta um pouco escuro


            if (seta < 0.5) {
                noite->set_color(LVecBase4f(seta, seta + 0.18, seta + 0.25, 1));
            }

            //retirando as sombras das arvores a noite

			Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(0.01 * limite);
            Terrain::get_default_terrain()->get_shadows()->update_shadows();
            
        } else
            noite->set_color(LVecBase4f(seta, seta + 0.18, seta + 0.25, 1));

        //retirando as sombras das arvores a noite
        Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(0.01 * limite);
        Terrain::get_default_terrain()->get_shadows()->update_shadows();
      
    }
    else if (hora >= 5 && hora < 6) {//amanhecendo....clariando novamente o ambiente

        if (ClimaTempo::get_instance()->get_chuva_today() == 0) {//só clareia as 5 se não tiver chuvendo

            if (minuto > 1) {//para não escurecer totalmente antes de começar a clariar
                noite->set_color(LVecBase4f(minuto * 0.0166, 0.18 + (minuto * 0.0166), 0.25 + (minuto * 0.0166), 1));
                //colocando as sombras de volta
               
                    Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(-0.01 * limite);
                    Terrain::get_default_terrain()->get_shadows()->update_shadows();
                    
                

            }
        }
    }
    else if (hora >= 7 && hora < 8) {
        if (ClimaTempo::get_instance()->get_chuva_today() != 0) {//se tiver chuvendo.....amanhece as 7 e não vai clariar tudo
			
            float aux = minuto * 0.0166;
            if (aux < 0.5 && minuto > 1) {//para não escurecer totalmente antes de começar a clariar
                noite->set_color(LVecBase4f(minuto * 0.0166, 0.18 + (minuto * 0.0166), 0.25 + (minuto * 0.0166), 1));

            }
            //colocando as sombras de volta
            if (TimeControl::get_instance()->get_dia() > 1) {//se não for o primeiro dia
                
                    Terrain::get_default_terrain()->get_shadows()->add_transparency_to_shadows(-0.01 * limite);
                    Terrain::get_default_terrain()->get_shadows()->update_shadows();
                    
                
            }
        }

    }


    //cout<<"Hora: "<<TimeControl::get_instance()->get_hora()<<"Minuto : "<<TimeControl::get_instance()->get_minuto()<<endl;
    //cout<<"Seta: "<<seta<<endl;
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


void Sky::unload_skybox(){
    sky = NULL;
}

 Sky::~Sky(){
     this->sol.remove_node();
     this->remove_node();
}
