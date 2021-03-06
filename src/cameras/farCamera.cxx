#include "farCamera.h"

#include "simdunas.h"


FarCamera::FarCamera(PT(Camera) camera) : CameraNode(camera){
	this->reparent_to(render);
	set_pos(object->get_x()+300, object->get_y()+300, object->get_z()+200);
	look_at(*object);
};


bool FarCamera::activate(){
	this->CameraNode::activate();
	set_pos(*this->object, 300, 300, 200);
	this->update();

	return true;
}


void FarCamera::update() {
	look_at(*object);
}
