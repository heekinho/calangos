#include "flyingPredatorCamera.h"

#include "cameraControl.h"

/*! Camera de captura do player pelo predador */
FlyingPredatorCamera::FlyingPredatorCamera(PT(Camera) camera) : CameraNode(camera){
	_enabled = false;
	_predator = NULL;
}

/*! Método chamado quando o CameraControl ativa esta camera.
 *  Faz o setup da cena de captura do player. */
bool FlyingPredatorCamera::activate(){
	if(!_enabled) return false;
	CameraNode::activate();

	NodePath render = Simdunas::get_window()->get_render();
	reparent_to(render);

	/* Obtem distancia necessária em predador para corresponder a 1u do render */
	set_pos(render, _predator->get_pos() + LPoint3f(4, 0, 0));
	set_z(render, World::get_world()->get_terrain()->get_elevation(get_x(render), get_y(render)) + 1);
	look_at(*_predator);

	return true;
}

/*! Chamado para ativar este controle de camera.
 *  É passado como argumento o predador a atacar o player.  */
bool FlyingPredatorCamera::activate(PT(FlyingPredator) predator){
	if(_enabled) return false;
	else _enabled = true;

	PT(CameraControl) cc = CameraControl::get_instance();
	this->_predator = predator;

	/* Define esta como a camera atual */
	cc->set_active_camera(/*(PT(CameraNode))*/ this);

	/* Desativa as ações de mudança de camera do usuário */
	cc->disable_user_input();
}

/*! O "comportamento" da camera, por enquanto, é ficar fixa no ponto
 *  olhando para o predador levar o player  */
void FlyingPredatorCamera::update(){
	look_at(*_predator);
}

/*! Por enquanto não se desabilita esta camera. */
bool FlyingPredatorCamera::deactivate(){
	nout << "Não implementado! Desabilitando camera" << endl;
}

/*! Define quais eventos chamará o update desta camera */
void FlyingPredatorCamera::set_hooks(){
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, this->CameraNode::update, this);
}

/*! Remove os eventos que chaman o update desta camera */
void FlyingPredatorCamera::unset_hooks(){
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, this->CameraNode::update, this);
}
