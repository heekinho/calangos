#include "freeCamera.h"



FreeCamera::FreeCamera(PT(Camera) camera) : CameraNode(camera){

}



bool FreeCamera::activate(){

	this->CameraNode::activate();

	window->setup_trackball();



	window->center_trackball(*object);

	return true;

}



