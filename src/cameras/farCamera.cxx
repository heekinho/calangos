#include "farCamera.h"



#include "simdunas.h"



//TODO: Tirar dependencia de SIMDUNAS dai de dentro.

FarCamera::FarCamera(PT(Camera) camera) : CameraNode(camera){

	this->reparent_to(Simdunas::get_window()->get_render());

	set_pos(object->get_x()+300, object->get_y()+300, object->get_z()+200);

	look_at(*object);

};



void FarCamera::activate(){

	this->CameraNode::activate();

	set_pos(*this->object, 300, 300, 200);

	this->update();

}



void FarCamera::update() {

	look_at(*object);

}

