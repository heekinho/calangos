#include "topCamera.h"

#include "simdunas.h"
#include "timeControl.h"

TopCamera::TopCamera(PT(Camera) camera) : CameraNode(camera){
	this->min_zoom = 30;
	this->max_zoom = 1500;
	this->current_zoom = 50;

	this->arrow = window->load_model(window->get_render_2d(), "models/green_arrow.png");
	this->arrow.set_scale(0.005);
	this->arrow.set_alpha_scale(0.3);
	this->arrow.hide();

	Simdunas::get_framework()->define_key("+", "Zoom In", zoom_in, this);
	Simdunas::get_framework()->define_key("-", "Zoom Out", zoom_out, this);


	this->reparent_to(render);
	set_pos(object->get_x()+1, object->get_y()+1, object->get_z()+1);
	look_at(*object);
};


TopCamera::~TopCamera(){
	arrow.remove_node();
}

bool TopCamera::activate(){
	CameraNode::activate();
	this->arrow.show();
	return true;
}

bool TopCamera::deactivate(){
	CameraNode::deactivate();
	this->arrow.hide();
	return true;
}

void TopCamera::set_hooks(){
	event_handler->add_hook(TimeControl::EV_pass_frame, CameraNode::update, this);
}


void TopCamera::zoom_in(const Event *theEvent, void *data){
	TopCamera* this_camera = (TopCamera*) data;
	this_camera->add_zoom(-100);
}


void TopCamera::zoom_out(const Event *theEvent, void *data){
	TopCamera* this_camera = (TopCamera*) data;
	this_camera->add_zoom(100);
}

void TopCamera::add_zoom(int zoom){
	current_zoom += zoom;
	if(current_zoom > max_zoom) current_zoom = max_zoom;
	else if(current_zoom < min_zoom) current_zoom = min_zoom;
}


void TopCamera::update() {
	set_pos(object->get_x(), object->get_y(), object->get_z()+current_zoom);
	look_at(*object);

	arrow.set_r(180 - object->get_h());
}

