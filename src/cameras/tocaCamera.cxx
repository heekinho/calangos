#include "tocaCamera.h"
#include "simdunas.h"

TocaCamera::TocaCamera(PT(Camera) camera) : CameraNode(camera){
	this->reparent_to(*object);
	set_h(*this, 180);
	set_z(*this, 50);

	this->camera->get_lens()->set_near_far(0.1, 800000.0);
};

void TocaCamera::activate(){
	this->CameraNode::activate();
	this->object->set_alpha_scale(0);
}

void TocaCamera::deactivate(){
	this->CameraNode::deactivate();
	this->object->set_alpha_scale(1);
}
