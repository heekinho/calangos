#include "cameraControl.h"

#include "camera.h"
#include "cameraNode.h"

#include "simdunas.h"
#include "player.h"

#include "nearCamera.h"
#include "closeCamera.h"
#include "farCamera.h"
#include "povCamera.h"
#include "topCamera.h"
#include "tocaCamera.h"
#include "freeCamera.h"

#include "eventQueue.h"

/* Controle Singleton */
PT(CameraControl) CameraControl::single = NULL;

/* Controle de Reference Counting */
TypeHandle CameraControl::_type_handle;

/*! Obtém o Controle de Camera */
PT(CameraControl) CameraControl::get_instance(){
	if(!single) {
		/* Qual a forma de passar atributos antes da primeira chamada no Singleton? */
        single = new CameraControl((PT(ObjetoJogo)) player);
    }
    return single;
}

/*! Destrói o Controle de Cameras */
CameraControl::~CameraControl(){
	for(int i = 0; i < cameras.size(); i++){
		cameras[i]->remove_node();
	}

	cameras.clear();
	display_region = NULL;
	object = NULL;

	event_handler->remove_hooks_with(this);
}

/*! Constrói o Controle de Cameras. Este controle é responsável pela criação e ativação
 * das cameras, bem como no mapeamento das teclas das cameras. */
CameraControl::CameraControl(PT(ObjetoJogo) object){
	this->object = object;
	this->object->set_transparency(TransparencyAttrib::M_alpha);

	this->current_camera = 2;
	this->accept_user_input = true;

	this->display_region = window->get_graphics_window()->get_active_display_region(0);
	this->display_region->set_clear_color(Colorf(0,0,0,1));

	this->configure_user_input();
	this->create_cameras();

	/* Define e ativa a primeira camera */
	this->set_active_camera(current_camera);

	/* Define o NodePath sobre o qual as cameras ficarão */
	this->group = render.attach_new_node("Cameras");
}

/*! Configura as entradas de teclado do usuário para o Controle */
void CameraControl::configure_user_input(){
	/* Define a tecla responsável pela mudança de camera. */
	Simdunas::get_framework()->define_key("1", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("2", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("3", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("4", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("5", "Change Camera", set_active_camera, this);

	/* Mudança incremental de camera. */
	Simdunas::get_framework()->define_key("c", "Change Camera", change_camera, this);
}


/*! Descarrega o Controle de Cameras, liberando-o para nova criação */
void CameraControl::unload(){
	single = NULL;
}


/*! Cria as camera. No momento 5:
 * - Camera em primeira pessoa
 * - Camera que acompanha de perto
 * - Camera que acompanha de longe
 * - Camera de visão geral (topo)
 * - Camera específica das tocas */
void CameraControl::create_cameras(){
	/* Adiciona as cameras */
	this->cameras.push_back(new PovCamera(new Camera("pov_camera")));
	this->cameras.push_back(new NearCamera(new Camera("near_camera")));
	this->cameras.push_back(new CloseCamera(new Camera("close_camera")));
	this->cameras.push_back(new FarCamera(new Camera("far_camera")));
	this->cameras.push_back(new TopCamera(new Camera("top_camera")));
	this->cameras.push_back(new FreeCamera(window->get_camera(0)));
	this->cameras.push_back(new TocaCamera(new Camera("toca_camera")));
}

PT(CameraNode) CameraControl::get_current_camera(){
	return cameras[current_camera];
}

/*! Recebe o evento do teclado (numeros) e converte isso para uma determinada camera */
void CameraControl::set_active_camera(const Event* evt, void *data){
	CameraControl* cc = (CameraControl*) data;

	/* Verifica se pode aceitar entradas do usuário */
	if(cc->is_user_input_enabled()){
		/* Verifica o evento (obtem o nome dele) */
		int icamera;
		stringstream stream (evt->get_name());

		/* Define a camera atual a partir do evento em questão. */
		if (stream >> icamera) cc->set_active_camera(icamera - 1);
	}
}

/*! Define a camera passada como ativa */
void CameraControl::set_active_camera(PT(CameraNode) camera){
	for(int i = 0; i < cameras.size(); i++){
		if(cameras.at(i) == camera) set_active_camera(i);
	}
}

/*! Define qual camera será posta em uso. */
void CameraControl::set_active_camera(int icamera){
	int previous_camera = current_camera;

	/* Antes de tudo, executa a desativação da camera anterior.
	 * Se não for possível, saí do método sem definir uma nova. */
	if(!cameras.at(current_camera)->deactivate()) return;

	PT(CameraNode) selected_camera;
	bool camera_activated = false;
	while(!camera_activated){
		/* Define a camera atual a partir do evento em questão,
		 * fazendo % cameras.size() por segurança. */
		current_camera = icamera % cameras.size();

		/* Define e ativa a camera */
		selected_camera = cameras.at(current_camera);
		if(selected_camera->activate()){
			display_region->set_camera(*selected_camera);
			camera_activated = true;
		}

		icamera++;
	}

	/* Ao mudar de camera, lança-se um evento */
	if(current_camera != previous_camera) event_queue->queue_event(new Event("camera-change"));
}


/*! Muda a camera de forma incremental, a partir de uma entrada do usuário */
void CameraControl::change_camera(const Event* evt, void *data){
	CameraControl* cc = (CameraControl*)data;
	if(cc->is_user_input_enabled()) cc->set_active_camera(cc->current_camera + 1);
}

/*! Verifica se entradas do usuário são aceitas */
bool CameraControl::is_user_input_enabled(){
	return accept_user_input;
}

/*! Desabilita as entradas do usuário (ex.: via teclado) para o Controle de Camera */
void CameraControl::disable_user_input(){
	accept_user_input = false;
}

/*! Habilita as entradas do usuário (ex.: via teclado) para o Controle de Camera */
void CameraControl::enable_user_input(){
	accept_user_input = true;
}
