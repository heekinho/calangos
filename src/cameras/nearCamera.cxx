#include "nearCamera.h"
#include "simdunas.h"

NearCamera::NearCamera(PT(Camera) camera) : CameraNode(camera){
	this->reparent_to(Simdunas::get_window()->get_render());
	set_pos(object->get_x()+1, object->get_y()+1, object->get_z()+1);
	look_at(*object);
}

void NearCamera::update() {
	float normalizacao = object->get_sx() * 2600;
	//nout << normalizacao << endl;

	// Definindo vetores de camera e obtendo a distancia
	LVecBase3f camvec (object->get_pos() - this->get_pos());
	camvec.set_z(0);
	float camdist (camvec.length());
	camvec.normalize();

	// Camera muito longe, encosta. Muito perto afasta.
	float mindist = 0.2 * normalizacao;
	float maxdist = 0.5 * normalizacao;

	if(camdist > maxdist) this->set_pos(this->get_pos() + camvec*(camdist-maxdist));
	if(camdist < mindist) this->set_pos(this->get_pos() - camvec*(mindist-camdist));


	//TODO: Colocar o set_z, como o ponto do terreno sob a camera
	// Manter a camera a um pé acima do terreno,
	// ou dois pés acima do objeto, o que for maior.
	normalizacao *= 0.1;
	World::get_default_world()->get_terrain()->update_node_z(*this);
	if((object->get_z() + normalizacao) > (this->get_z() + (normalizacao/2))) this->set_z(object->get_z() + (normalizacao));
	else this->set_z(this->get_z() + normalizacao);

	// Camera olha para o objeto de jogo
	this->look_at(*object);

	// Olha pra cabeça, e não para os pés...
	this->set_p(*this, 10.0);
}



