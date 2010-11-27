#include "frog.h"

#include "modelRepository.h"
#include "terrain.h"

/*! Construtor padrão dos sapos */
Frog::Frog(NodePath node) : Animal(node){
	jumps = 0;
	jumping = false;
}

/*! Carrega todos os sapos */
void Frog::load_frogs(){
	ModelRepository::get_instance()->get_model("sapo")->set_scale(0.0005);

	PT(Terrain) terrain = World::get_world()->get_terrain();

	int qtd = 10;
	for(int i = 0; i < qtd; i++){
		/* Cria nova instancia do sapo */
		PT(Frog) frog = new Frog((*ModelRepository::get_instance()->get_model("sapo")).copy_to(NodePath()));

		/* Define a posição e orientação aleatória, além da velocidade */
		frog->set_pos(terrain->get_random_point());
		frog->set_h(rand()%360);
		frog->set_velocity(2300);

		/* Conclui a referencia com o modelo e animação */
		//ModelRepository::get_instance()->get_model("sapo")->instance_to(*frog);
		frog->bind_anims(frog->node());

		/* Adiciona na lista de animais e o coloca para renderização */
		terrain->add_animal((PT(Animal)) frog);
		frog->reparent_to(Simdunas::get_window()->get_render());
	}
}

/*! Realiza mudança de setores */
void Frog::change_sector(PT(Setor) new_sector){
	get_setor()->animals()->remove(dynamic_cast<Animal*>(this));
	new_sector->animals()->push_back(dynamic_cast<Animal*>(this));
}

/*! O comportamento do sapo se resume a:
 *  1 - Ficar parado.
 *  2 - De vez em quando dá n saltos seguidos, mudando-se trajetória aleatóriamente.
 *  Ainda não há interação com os demais animais. */
void Frog::act(){
	int frame = get_anim_control()->get_frame("character");

	if(jumping) {
		/* Para não "derrapar" no terreno */
		if(frame > 4 && frame < 28) move(get_velocity());
		if(frame == 0) jumping = false;
	}
	else if(jumps > 0){
		if(is_activated()) get_anim_control()->play("character", 1, 31);
		jumps--;
		jumping = true;
		set_h(*this, rand()%80-40);
	}
	else {
		if(rand()%80 == 34) jumps = rand()%4+1;
	}
}

/*! Para a animação - quando o sapo fica estático */
void Frog::pause_animation(){
	deactivate_anims();
}

/*! Roda a animação do salto */
void Frog::continue_animation(){
	activate_anims();
}
