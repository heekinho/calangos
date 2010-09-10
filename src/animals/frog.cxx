#include "frog.h"

#include "modelRepository.h"
#include "terrain.h"

/*! Construtor padrão dos sapos */
Frog::Frog(NodePath node) : Animal(node){

}

PT(Frog) frog;

/*! Carrega todos os sapos */
void Frog::load_frogs(){
	//ModelRepository::get_instance()->get_model("sapo")->set_scale(1);

	frog = new Frog(NodePath("Prey PlaceHolder"));
	frog->reparent_to(Simdunas::get_window()->get_render());
	frog->set_pos(256, 256, 0);
	//ModelRepository::get_instance()->get_model("sapo")->instance_to(*frog);
}

/*! Realiza mudança de setores */
void Frog::change_sector(PT(Setor) new_sector){
//	get_setor()->preys()->remove(dynamic_cast<Prey*>(this));
//	new_sector->preys()->push_back(dynamic_cast<Prey*>(this));
}

//void Frog::act(){
//	move(get_velocity());
//}
