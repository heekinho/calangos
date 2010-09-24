#include "frog.h"

#include "modelRepository.h"
#include "terrain.h"

/*! Construtor padrão dos sapos */
Frog::Frog(NodePath node) : Animal(node){
	jumps = 0;
	jumping = false;
}

PT(Frog) frog;

/*! Carrega todos os sapos */
void Frog::load_frogs(){

	ModelRepository::get_instance()->get_model("sapo")->set_scale(0.001);


	frog = new Frog(NodePath("Prey PlaceHolder"));
	frog->reparent_to(Simdunas::get_window()->get_render());
	frog->set_pos(256, 256, 0);
	ModelRepository::get_instance()->get_model("sapo")->instance_to(*frog);

	frog->set_velocity(5);
	frog->bind_anims(ModelRepository::get_instance()->get_model("sapo")->node());
	//frog->get_anim_control()->loop("character", false);
}

/*! Realiza mudança de setores */
void Frog::change_sector(PT(Setor) new_sector){
//	get_setor()->preys()->remove(dynamic_cast<Prey*>(this));
//	new_sector->preys()->push_back(dynamic_cast<Prey*>(this));
}

void Frog::act(){
	int frame = get_anim_control()->get_frame("character");

	if(jumping) {
		/* Para não "derrapar" no terreno */
		if(frame > 4 && frame < 28) move(get_velocity());
		if(frame == 0) jumping = false;
	}
	else if(jumps > 0){
		get_anim_control()->play("character", 1, 31);
		jumps--;
		jumping = true;
		set_h(*this, rand()%80-40);
	}
	else {
		if(rand()%80 == 34) jumps = rand()%4+1;
	}
}

void Frog::pause_animation(){
	get_anim_control()->stop_all();
}

void Frog::continue_animation(){
	frog->get_anim_control()->loop("character", false);
}
