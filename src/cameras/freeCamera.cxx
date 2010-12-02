#include "freeCamera.h"

FreeCamera::FreeCamera(PT(Camera) camera) : CameraNode(camera){
}

void FreeCamera::activate(){
	this->CameraNode::activate();
	Simdunas::get_window()->setup_trackball();

	Simdunas::get_window()->center_trackball(*object);
}

void FreeCamera::deactivate(){

}

void FreeCamera::update() {

}
