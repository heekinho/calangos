#include "redLegged.h"

#include "modelRepository.h"
#include "simdunas.h"

#define NORVEL 0.5

NodePath RedLegged::redleggeds_placeholder = NodePath("RedLeggeds Placeholder");


/*! Constrói uma Aranha baseado no recurso de Instancing
 * Basta passar um ponteiro para o modelo a ser instanciado */
RedLegged::RedLegged(PT(AnimatedObjetoJogo) base_object) : Predator(base_object) {
	base_object->instance_to(*this);
	init();
}


/*! "Construtor" comum */
void RedLegged::init(){
	bind_anims(this->node());
	set_acting(false);
	hide(); // Mover para Animal
}


/*! Destroi o objeto Seriema */
RedLegged::~RedLegged(){}

/*! Carrega os NPCs do jogo. */
void RedLegged::load_redleggeds(int qtd){
	RedLegged::redleggeds_placeholder = Animal::animals_placeholder.attach_new_node("RedLeggeds Placeholder");

	// Tamanho do terreno para delimitar a area
	int terrain_x_size = World::get_default_world()->get_terrain()->get_x_size();
	int terrain_y_size = World::get_default_world()->get_terrain()->get_y_size();

	ModelRepository::get_instance()->get_animated_model("siriema")->get_anim_control()->loop("andar", false);
	ModelRepository::get_instance()->get_animated_model("siriema")->set_scale(0.003);
	ModelRepository::get_instance()->get_animated_model("siriema")->set_hpr(180,0,0);

	for (int i = 0; i < qtd; i++) {
		// Cria a aranha e coloca-a no grafo de cena
		PT(RedLegged) npc = new RedLegged( (PT(AnimatedObjetoJogo)) ModelRepository::get_instance()->get_animated_model("siriema"));

		int x = rand() % terrain_x_size;
		int y = rand() % terrain_y_size;

		npc->set_pos(x, y, 0);
		World::get_default_world()->get_terrain()->add_animal((PT(Animal)) npc);
	}
}


/* Implementação do método da classe Animal */
void RedLegged::act(){
	Predator::act();
}

