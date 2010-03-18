#include "povCamera.h"

#include "simdunas.h"
#include "mouseWatcher.h"
#include "mouseButton.h"

PovCamera::PovCamera(PT(Camera) camera) : CameraNode(camera){
	this->reparent_to(*object);

	clear_transform(*object);
	set_h(*this, 180);
	set_z(*this, 100);
	set_scale(1/object->get_transform()->get_uniform_scale());

	this->camera->get_lens()->set_near_far(0.005, 2000);

	dummy = new NodePath("DummyNode");
	// Debug ----------------------------------------------------//
	//dummy = new ObjetoJogo("models/broccoli.egg");
	//dummy->reparent_to(Simdunas::get_window()->get_render());
	// Debug ----------------------------------------------------//

	dummy->set_pos(*object, 0, -50 * 5, 0);
	dummy->set_scale(0.05);
	World::get_default_world()->get_terrain()->update_node_z(*dummy);
}

void PovCamera::activate(){
	this->CameraNode::activate();
	//this->object->set_alpha_scale(0);
}

void PovCamera::deactivate(){
	this->CameraNode::deactivate();
	this->object->set_alpha_scale(1);
	this->old_x = 0;
	this->old_y = 0;
}


void PovCamera::set_hooks(){
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, this->CameraNode::update, this);
}

void PovCamera::unset_hooks(){
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, this->CameraNode::update, this);
}

void PovCamera::update() {
	//----------------------------------------------------------------------------------------//
	float mouse_x = 0;
	float mouse_y = 0;

	MouseWatcher *mwatcher = DCAST(MouseWatcher, Simdunas::get_window()->get_mouse().node());
	if(mwatcher->has_mouse()){
		mouse_x = old_x = mwatcher->get_mouse_x();
		mouse_y = old_y = mwatcher->get_mouse_y();
	}
	else {
		mouse_x = old_x;
		mouse_y = old_y;
	}
	//----------------------------------------------------------------------------------------//

	/* O lagarto só deve movimentar a cabeça se o botão do meio do mouse estiver pressionado */
	if(mwatcher->is_button_down(MouseButton::three())){
		World::get_default_world()->get_terrain()->update_node_z(*dummy);
		dummy->set_pos(*object, mouse_x * -50*5, -50*5, dummy->get_z() + mouse_y * 50*5);
		look_at(*dummy);
	}
}

