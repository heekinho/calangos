#include "redLegged.h"

#include "modelRepository.h"
#include "simdunas.h"

NodePath RedLegged::redleggeds_placeholder = NodePath("RedLeggeds Placeholder");

RedLegged::RedLegged(NodePath node) : Predator(node){
	init();
}


/*! "Construtor" comum */
void RedLegged::init(){
	bind_anims(this->node());
	set_velocity(350.0);
}


/*! Destroi o objeto Seriema */
RedLegged::~RedLegged(){}

/*! Carrega os NPCs do jogo. */
void RedLegged::load_redleggeds(int qtd){
	RedLegged::redleggeds_placeholder = Animal::animals_placeholder.attach_new_node("RedLeggeds Placeholder");

	// Tamanho do terreno para delimitar a area
	int terrain_x_size = World::get_default_world()->get_terrain()->get_x_size();
	int terrain_y_size = World::get_default_world()->get_terrain()->get_y_size();

	ModelRepository::get_instance()->get_animated_model("siriema")->set_scale(0.03);

	for (int i = 0; i < qtd; i++) {
		// Cria a aranha e coloca-a no grafo de cena
		NodePath base_redlegged = (*ModelRepository::get_instance()->get_animated_model("siriema")).copy_to(NodePath());
		PT(RedLegged) npc = new RedLegged(base_redlegged);


		int x = rand() % terrain_x_size;
		int y = rand() % terrain_y_size;

		npc->set_pos(x, y, 0);
		npc->set_h(rand()%360);
		World::get_default_world()->get_terrain()->add_predator((PT(Predator)) npc);
		npc->get_anim_control()->loop("andar", false);
		npc->reparent_to(Simdunas::get_window()->get_render());
	}
}


/* Implementação do método da classe Animal */
void RedLegged::act(){
	Predator::act();
}

