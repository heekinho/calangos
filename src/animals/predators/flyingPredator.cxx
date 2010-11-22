#include "flyingPredator.h"

#include "modelRepository.h"

/*! Constrói um predador voador */
FlyingPredator::FlyingPredator(NodePath node) : Predator(node){

}

/*! Destrutor de predador voador */
FlyingPredator::~FlyingPredator(){}


/*! Carrega todos os predadores voadores do jogo */
void FlyingPredator::load_predators(){
	//FlyingPredator::load_predator("coruja", 20, 0.3, -1);
}


/*! Carrega uma quantidade de predadores voadores, da espécie especificada */
void FlyingPredator::load_predator(const string &model, int qtd, float scale, int orientation){
	ModelRepository::get_instance()->get_animated_model(model)->set_scale(scale);

	PT(Terrain) terrain = World::get_world()->get_terrain();
	for(int i = 0; i < qtd; i++){
		/* Carrega e cria uma cópia (deep) do modelo */
		NodePath base_predator = ModelRepository::get_instance()->get_animated_model(model)->copy_to(NodePath());
		PT(FlyingPredator) predator = new FlyingPredator(base_predator);
		predator->bind_anims(predator->node());

		/* Define localização e orientação aleatórias */
		predator->set_h(rand()%360);
		predator->NodePath::set_pos(terrain->get_random_point());
		predator->set_offset_z(20);
		predator->set_orientation(orientation);

		/* Adiciona o predator ao terreno e ao render */
		terrain->add_predator((PT(Predator))predator);
		predator->reparent_to(Simdunas::get_window()->get_render());

		/* Roda a animação */
		predator->get_anim_control()->loop("voar", false);
	}
}


/*! Roda o comportamento de ações do predador.
 * O predador basicamente perambula, e ao encontrar o lagarto dentro de uma
 * certa distância ele parte para o ataque */
void FlyingPredator::act(){
	PT(Player) player = Player::get_instance();
	float dt = ClockObject::get_global_clock()->get_dt();

	if(!get_anim_control()->is_playing("voar")) get_anim_control()->loop("voar", false);
	if(rand()%120 == 34) set_h(*this, rand()%80 - (80/2));

	move(get_velocity());

	if((get_pos().get_xy() - player->get_pos().get_xy()).length() < 10){
		look_at(*player);

		if(get_z() - player->get_z() > 1) set_offset_z(-1*dt);
	}
}
