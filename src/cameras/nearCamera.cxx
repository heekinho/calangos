#include "nearCamera.h"



#include "simdunas.h"



NearCamera::NearCamera(PT(Camera) camera) : CameraNode(camera){

//	//this->reparent_to(Simdunas::get_window()->get_render());

//	this->reparent_to(*object);

//	set_h(*this, 180);

//	set_pos(0, 600, 100);

//	//set_pos(object->get_x(), object->get_y(), object->get_z()+100);

//	look_at(*object);

//	set_p(0.3);



	this->reparent_to(Simdunas::get_window()->get_render());

	set_pos(object->get_x()+1, object->get_y()+1, object->get_z()+1);

	look_at(*object);

}



void NearCamera::update() {

	// Definindo vetores de camera e obtendo a distancia

	LVecBase3f camvec (object->get_pos() - this->get_pos());

	camvec.set_z(0);

	float camdist (camvec.length());

	camvec.normalize();



	// Camera muito longe, encosta. Muito perto afasta.

	if(camdist > 25.0*0.02)

		this->set_pos(this->get_pos() + camvec*(camdist-(25.0*0.02)));

	if(camdist < 10.0*0.02)

		this->set_pos(this->get_pos() - camvec*((10.0*0.02)-camdist));



	//TODO: Colocar o set_z, como o ponto do terreno sob a camera

	// Manter a camera a um pé acima do terreno,

	// ou dois pés acima do objeto, o que for maior.

	World::get_default_world()->get_terrain()->update_node_z(*this);

	if((object->get_z() + (2.0*0.03)) > (this->get_z() + (1.0*0.03)))

		this->set_z(object->get_z() + (2.0*0.03));

	else

		this->set_z(this->get_z() + (1.0*0.03));



	// Camera olha para o objeto de jogo

	this->look_at(*object);

	// Olha pra cabeça, e não para os pés...

	this->set_p(*this, 10.0);

}



