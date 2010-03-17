#include "predator.h"
#include "player.h"

#include "redLegged.h"

Predator::Predator(NodePath node) : Animal(node){
	set_blend(true, true, PartBundle::BT_normalized_linear);
	set_control_effect("andar", 1.0);
	set_control_effect("comer", 0);
	set_velocity(200.0);
}

Predator::~Predator(){}


void Predator::load_predators(){
	RedLegged::load_redleggeds(40);
}


void Predator::act(){

	float distance = 25; // Ajustar
	PT(Player) player = Player::get_instance();
	LVector3f predator_to_player = this->get_pos() - player->get_pos();

	if(predator_to_player.length() < distance){

		if (predator_to_player.length() < 0.1){
			bite();
			//cout << "ESTAH MORDENDO!" << endl;
		}
		else{
			PT(Setor) setor = World::get_default_world()->get_terrain()->
					get_setor_from_pos(player->get_x(), player->get_y());
			vector<PT(Vegetal)>* vegetal_list = setor->get_vegetals();

			for (unsigned int i = 0; i < vegetal_list->size(); i++){
					PT(Vegetal) vegetal = vegetal_list->at(i);
					LVector3f player_to_vegetal = player->get_pos() - vegetal->get_pos();
					if (player_to_vegetal.length() < 3.5){
						//continua andando
						Animal::act();
						return;
					}
			 }
			//PERSEGUE
			pursuit();
		}
	}
	else
		Animal::act();
}


void Predator::pursuit(){
	PT(Player) player = Player::get_instance();
	look_at(*player);

	move(get_velocity());
}


void Predator::bite(){
	if(!this->get_anim_control()->is_playing("comer")){
		this->get_anim_control()->play("comer");
		this->set_control_effect("andar", 0);
		this->set_control_effect("comer", 1.0);

		/* Diminui energia do player */
		Player::get_instance()->be_bited();
		Player::get_instance()->add_energia_alimento(-1.0);
		GuiManager::get_instance()->piscar_life();
	}
}

void Predator::pause_animation(){
	get_anim_control()->stop_all();
}

void Predator::continue_animation(){
	if(!get_anim_control()->is_playing("andar")) get_anim_control()->play("andar");
}


