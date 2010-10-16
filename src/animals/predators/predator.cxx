#include "predator.h"
#include "player.h"

#include "modelRepository.h"
#include "redLegged.h"
#include "fox.h"

#include "collision.h"

/*! Constrói um Predador */
Predator::Predator(NodePath node) : Animal(node){
	set_velocity(200.0);
	//adiciona solido de colisão aos predadores (ficou legal esses valores para altura e raio)
	collision::get_instance()->collisionNpcFast(&node, 0, 0, 20, 10);
}

Predator::~Predator(){}

/*! Carrega todos os predadores do jogo */
void Predator::load_predators(){
	RedLegged::load_redleggeds(30);
	//Fox::load_foxes(1);
	Predator::load_predator("raposa", 40, 0.01, -1);
	Predator::load_predator("gato", 200, 0.01, -1);
}


/*! Carrega uma quantidade de predadores com comportamento padrão, de determinado tipo */
void Predator::load_predator(const string &model, int qtd, float scale, int orientation){
	ModelRepository::get_instance()->get_animated_model(model)->set_scale(scale);

	PT(Terrain) terrain = World::get_world()->get_terrain();
	for(int i = 0; i < qtd; i++){
		/* Carrega e cria uma cópia (deep) do modelo */
		NodePath base_predator = ModelRepository::get_instance()->get_animated_model(model)->copy_to(NodePath());
		PT(Predator) predator = new Predator(base_predator);
		predator->bind_anims(predator->node());

		/* Define localização e orientação aleatórias */
		predator->set_h(rand()%360);
		predator->set_pos(terrain->get_random_point());
		predator->set_orientation(orientation);

		/* Adiciona o predator ao terreno e ao render */
		terrain->add_predator(predator);
		predator->reparent_to(Simdunas::get_window()->get_render());

		/* Roda a animação */
		predator->get_anim_control()->loop("andar", false);
	}
}


/*! Roda o comportamento de ações do predador.
 * O predador basicamente perambula, e ao encontrar o lagarto dentro de uma
 * certa distância ele parte para o ataque */
void Predator::act(){
	float distance = 10;
	PT(Player) player = Player::get_instance();
	LVector3f predator_to_player = this->get_pos() - player->get_pos();

	if(predator_to_player.length() < distance){
		//nout << predator_to_player.length() << endl;
		if (predator_to_player.length() < 0.3){
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

/*! Muda o Predador de setor */
void Predator::change_sector(PT(Setor) new_sector){
	get_setor()->predators()->remove(this);
	new_sector->predators()->push_back(this);

	//mudando de nodepath
	this->reparent_to(Terrain::create_default_terrain()->no_setores[new_sector->get_indice()]);
}

/*! Roda comportamento de perseguição */
void Predator::pursuit(){
	if(!this->get_anim_control()->is_playing("comer")){
		if(!get_anim_control()->is_playing("andar")) get_anim_control()->play("andar");

		PT(Player) player = Player::get_instance();
		look_at(*player);

		move(get_velocity());
	}
}

/*! Roda comportamento de mordida/comer */
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

/*! Pausa a nimação */
void Predator::pause_animation(){
	get_anim_control()->stop_all();
	//get_anim_control()->pose("andar", 7);
	get_anim_control()->loop("stand", false);
}

/*! Retoma a animação */
void Predator::continue_animation(){
	if(!get_anim_control()->is_playing("andar")) get_anim_control()->play("andar");
}


