#include "predator.h"
#include "player.h"

#include "redLegged.h"
#include "fox.h"

#include "collision.h"

Predator::Predator(NodePath node) : Animal(node){
	set_velocity(200.0);
            //adiciona solido de colisão aos predadores (ficou legal esses valores para altura e raio)
        collision::get_instance()->collisionNpcFast(&node, 0, 0, 20, 10);
}

Predator::~Predator(){}


void Predator::load_predators(){
	RedLegged::load_redleggeds(30);
	Fox::load_foxes(1);
}


void Predator::act(){
	float distance = 10;
	PT(Player) player = Player::get_instance();
	LVector3f predator_to_player = this->get_pos() - player->get_pos();

	if(predator_to_player.length() < distance){
		if (predator_to_player.length() < 0.1){
			bite();
		}
		else{
			PT(Setor) setor = World::get_world()->get_terrain()->get_setor_from_pos(player->get_x(), player->get_y());
			SectorItems<PT(Vegetal)>* vegetal_list = setor->vegetals();
			SectorItems<PT(Vegetal)>::iterator it;
			for (it = vegetal_list->begin(); it != vegetal_list->end(); ++it){
				PT(Vegetal) vegetal = *it;
				LVector3f player_to_vegetal = player->get_pos() - vegetal->get_pos();
				if (player_to_vegetal.length() < 3.5 || player->is_in_toca()){
					if(!this->get_anim_control()->is_playing("comer") && !get_anim_control()->is_playing("andar"))
						get_anim_control()->play("andar");
					Animal::act();
					return;
				}
			}
			pursuit();
		}
	}
	else {
		if(!get_anim_control()->is_playing("andar")) get_anim_control()->play("andar");
		Animal::act();
	}

}

void Predator::change_sector(PT(Setor) new_sector){
	get_setor()->predators()->remove(this);
	new_sector->predators()->push_back(this);

        //mudando de nodepath
        this->reparent_to(Terrain::create_default_terrain()->no_setores[new_sector->get_indice()]);
}


void Predator::pursuit(){
	if(!this->get_anim_control()->is_playing("comer")){
		if(!get_anim_control()->is_playing("andar")) get_anim_control()->play("andar");

		PT(Player) player = Player::get_instance();
		look_at(*player);

		move(get_velocity());
	}
}


void Predator::bite(){
	if(!this->get_anim_control()->is_playing("comer")){
		get_anim_control()->stop_all();
		this->get_anim_control()->play("comer");

		/* Diminui energia do player */
		Player::get_instance()->be_bited();
		Player::get_instance()->add_energia_alimento(-1.0);
		GuiManager::get_instance()->piscar_life();
	}
}

void Predator::pause_animation(){
	get_anim_control()->stop_all();
	get_anim_control()->pose("andar", 7);
}

void Predator::continue_animation(){
	if(!get_anim_control()->is_playing("andar")) get_anim_control()->play("andar");
}


