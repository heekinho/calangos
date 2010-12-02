#include "cameraControl.h"

#include "cameraNode.h"

// Verificar esses includes
#include "playerControl.h"
#include "terrain.h"
#include "player.h"
#include "simdunas.h"

#include "camera.h"

// Inclui as Cameras
#include "nearCamera.h"
#include "closeCamera.h"
#include "farCamera.h"
#include "povCamera.h"
#include "topCamera.h"
#include "tocaCamera.h"
#include "freeCamera.h"


/* Controle Singleton */
PT(CameraControl) CameraControl::single = NULL;

/* Controle de Reference Counting */
TypeHandle CameraControl::_type_handle;

/*! Obtém o Controle de Camera */
PT(CameraControl) CameraControl::get_instance(){
	if(!single) {
		/* Qual a forma de passar atributos antes da primeira chamada no Singleton? */
        single = new CameraControl((PT(ObjetoJogo)) Player::get_instance());
    }
    return single;
}

/*! Constrói o Controle de Cameras. Este controle é responsável pela criação e ativação
 * das cameras, bem como no mapeamento das teclas das cameras. */
CameraControl::CameraControl(PT(ObjetoJogo) object){
	this->object = object;
	this->object->set_transparency(TransparencyAttrib::M_alpha);

	this->current_camera = 2;

	this->display_region = Simdunas::get_window()->get_graphics_window()->get_active_display_region(0);
	this->display_region->set_clear_color(Colorf(0,0,0,1));


	// Define a tecla responsável pela mudança de camera.
	Simdunas::get_framework()->define_key("1", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("2", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("3", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("4", "Change Camera", set_active_camera, this);
	Simdunas::get_framework()->define_key("5", "Change Camera", set_active_camera, this);

	// Mudança incremental de camera.
	Simdunas::get_framework()->define_key("c", "Change Camera", change_camera, this);
	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_enter_toca, toca_camera, this);
	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_outof_toca, return_camera, this);

	this->create_cameras();

	// Define e ativa a primeira camera
	this->set_active_camera(current_camera);
}

/*! Destrói o Controle de Cameras */
CameraControl::~CameraControl(){
	for(int i = 0; i < cameras.size(); i++){
		cameras[i]->remove_node();
	}

	cameras.clear();
	display_region = NULL;
	object = NULL;

	//Simdunas::get_window()->get_camera_group().remove_node();
	//TODO: É necessário remover os eventos da fila do Panda?
	Simdunas::get_evt_handler()->remove_hooks_with(this);
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
	this->cameras.push_back(new FreeCamera(Simdunas::get_window()->get_camera(0)));
	this->cameras.push_back(new TocaCamera(new Camera("toca_camera")));
}

PT(CameraNode) CameraControl::get_current_camera(){
	return cameras[current_camera];
}

/*! Recebe o evento do teclado (numeros) e converte isso para uma determinada camera */
void CameraControl::set_active_camera(const Event* evt, void *data){
	CameraControl* cc = (CameraControl*) data;

	// Verifica o evento (obtem o nome dele)
	int icamera;
	stringstream myStream(evt->get_name());

	// Define a camera atual a partir do evento em questão.
	if (myStream >> icamera) cc->set_active_camera(icamera - 1);
}


/*! Define qual camera será posta em uso. */
void CameraControl::set_active_camera(int icamera){
	// Antes de tudo, executa a desativação da camera anterior.
	cameras.at(current_camera)->deactivate();

	// Define a camera atual a partir do evento em questão,
	// % cameras.size() por segurança.
	current_camera = icamera % (cameras.size() - 1);

	// Define e ativa a camera
	display_region->set_camera(*cameras.at(current_camera));
	cameras.at(current_camera)->activate();
}


/*! Muda a camera de forma incremental */
void CameraControl::change_camera(const Event* evt, void *data){
	CameraControl* cc = (CameraControl*)data;

	cc->set_active_camera(cc->current_camera + 1);
}

/*! Muda a camera para Toca (primeira pessoa) */
void CameraControl::toca_camera(const Event* evt, void *data){
	CameraControl* cc = (CameraControl*)data;
	cc->cameras.at(cc->current_camera)->deactivate();
	cc->display_region->set_camera(*cc->cameras.at(5));
	cc->cameras.at(5)->activate();
	Simdunas::get_framework()->get_event_handler().remove_hook("1", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().remove_hook("2", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().remove_hook("3", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().remove_hook("4", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().remove_hook("5", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().remove_hook("c", change_camera, cc);
}

/*! Retorna à camera que estava antes de entrar na toca */
void CameraControl::return_camera(const Event* evt, void *data){
	CameraControl* cc = (CameraControl*)data;
	cc->cameras.at(5)->deactivate();
	cc->set_active_camera(cc->current_camera);
	Simdunas::get_framework()->get_event_handler().add_hook("1", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().add_hook("2", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().add_hook("3", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().add_hook("4", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().add_hook("5", set_active_camera, cc);
	Simdunas::get_framework()->get_event_handler().add_hook("c", change_camera, cc);
}
