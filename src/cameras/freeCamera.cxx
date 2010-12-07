#include "freeCamera.h"

FreeCamera::FreeCamera(PT(Camera) camera) : CameraNode(camera){
}

bool FreeCamera::activate(){
	this->CameraNode::activate();
	Simdunas::get_window()->setup_trackball();

	Simdunas::get_window()->center_trackball(*object);
	return true;
}

