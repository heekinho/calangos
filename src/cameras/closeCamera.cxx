#include "closeCamera.h"

#include "simdunas.h"
#include "mouseWatcher.h"
#include "mouseButton.h"

CloseCamera::CloseCamera(PT(Camera) camera) : CameraNode(camera){
	reparent_to(Simdunas::get_window()->get_render());
	//this->reparent_to(*object);
	//set_scale(1/object->get_transform()->get_uniform_scale());

	//start_point = LPoint3f(0, 600, 100);
	activate();
}

void CloseCamera::set_hooks(){
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, this->CameraNode::update, this);
}

void CloseCamera::unset_hooks(){
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, this->CameraNode::update, this);
}

bool CloseCamera::activate(){
	this->CameraNode::activate();
//	set_pos(start_point);
//	look_at(*object);
//	set_p(0.3);

	return true;
}

bool CloseCamera::deactivate(){
	this->CameraNode::deactivate();
	this->old_x = 0;
	this->old_y = 0;

	return true;
}

#include "boundingSphere.h"
void CloseCamera::update() {
	set_pos(object->get_pos());

	float distance = 1.5;//get_bounds()->as_bounding_sphere()->get_radius();

	/* Define a posição da camera */
	set_pos(-1 * distance * object->get_orientation(false) + object->get_pos());
//	set_x(object->get_x());
//	set_y(object->get_y());
	set_z(object->get_z() + 0.25);

	/* Define a orientação da camera */
	set_h(object->get_h() + 180);
	set_p(0);
	set_r(0);

//	float mouse_x = 0;
//	float mouse_y = 0;
//
//	MouseWatcher *mwatcher = DCAST(MouseWatcher, Simdunas::get_window()->get_mouse().node());
//	if(mwatcher->has_mouse()){
//		mouse_x = old_x = mwatcher->get_mouse_x();
//		mouse_y = old_y = mwatcher->get_mouse_y();
//	}
//	else {
//		mouse_x = old_x;
//		mouse_y = old_y;
//	}
//	//----------------------------------------------------------------------------------------//
//
//
//	/* O lagarto só deve movimentar a cabeça se o botão do meio do mouse estiver pressionado */
//	if(mwatcher->is_button_down(MouseButton::three())){
//		this->set_x(start_point.get_y() * -sin(deg_2_rad(max_d_ang * mouse_x)));
//		this->set_y(start_point.get_y() * cos(deg_2_rad(max_d_ang * mouse_x)));
//
//		this->set_z(start_point.get_z() + 300 * sin(deg_2_rad(max_d_ang * ((mouse_y + 1)/2))));
//
//		look_at(*object);
//		set_p(get_p() + 10);
//	}
}
