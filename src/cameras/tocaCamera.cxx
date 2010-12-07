#include "tocaCamera.h"
#include "simdunas.h"

TocaCamera::TocaCamera(PT(Camera) camera) : CameraNode(camera){
	this->reparent_to(*object);
	set_h(*this, 180);
	set_z(*this, 50);

	this->camera->get_lens()->set_near_far(0.1, 800000.0);
	this->_enabled = false;
	//this->_last_camera = CameraControl::get_instance()->get_current_camera();
	this->_last_camera = NULL;

	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_enter_toca, enable_camera, this);
	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_outof_toca, disable_camera, this);
};

/*! Habilita a camera de toca. Evento é lançado pelo controle do jogador */
void TocaCamera::enable_camera(const Event* evt, void *data){
	PT(TocaCamera) camera = (PT(TocaCamera))(TocaCamera*) data;
	camera->_enabled = true;

	/* Configura o controle de camera para definir esta camera como atual */
	PT(CameraControl) cc = CameraControl::get_instance();

	/* Guarda a camera atual para quando sair da toca */
	camera->_last_camera = cc->get_current_camera();

	/* Define esta como a camera atual */
	cc->set_active_camera((PT(CameraNode)) camera);

	/* Desativa as ações de mudança de camera do usuário */
	cc->disable_user_input();
}

/*! Desabilita a camera */
void TocaCamera::disable_camera(const Event* evt, void *data){
	PT(TocaCamera) camera = (PT(TocaCamera))(TocaCamera*) data;
	camera->_enabled = false;

	/* Reativa o controle de usuário e ativa a última camera antes de toca */
	PT(CameraControl) cc = CameraControl::get_instance();
	cc->enable_user_input();
	if(camera->_last_camera != NULL) cc->set_active_camera(camera->_last_camera);
	else cc->change_camera(NULL, cc);
}

/*! Utilizado para ativar a camera. ("do_enter" de um FSM padrão). */
bool TocaCamera::activate(){
	if(!_enabled) return false;
	this->CameraNode::activate();
	this->object->hide();
	return true;
}

bool TocaCamera::deactivate(){
	/* Enquanto a camera tiver ativa, não libera para ser desativada. */
	if(_enabled) return false;
	this->CameraNode::deactivate();
	this->object->show();
	return true;
}
