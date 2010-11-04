#include "flyingPredator.h"

#include "modelRepository.h"

/*! Constrói um predador voador */
FlyingPredator::FlyingPredator(NodePath node) : Predator(node){

}

/*! Destrutor de predador voador */
FlyingPredator::~FlyingPredator(){}


/*! Carrega todos os predadores voadores do jogo */
void FlyingPredator::load_predators(){
	//Predator::load_predator("raposa", 8, 0.01, -1);
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
		predator->set_pos(terrain->get_random_point());
		predator->set_orientation(orientation);

		/* Adiciona o predator ao terreno e ao render */
		terrain->add_predator((PT(Predator))predator);
		predator->reparent_to(Simdunas::get_window()->get_render());

		/* Roda a animação */
		//predator->get_anim_control()->loop("andar", false);
	}
}


/*! Roda o comportamento de ações do predador.
 * O predador basicamente perambula, e ao encontrar o lagarto dentro de uma
 * certa distância ele parte para o ataque */
void FlyingPredator::act(){
	Animal::act();
}
