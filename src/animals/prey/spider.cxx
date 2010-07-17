#include "spider.h"

#include "simdunas.h"
#include "timeControl.h"

#include "modelRepository.h"

#define MAXDEGREE 100
#define VELOCITY 1.0
#define PROBTHR 80
#define RADIUSTHR 100

NodePath Spider::spiders_placeholder = NodePath("Spiders Placeholder");
/*! Aranhas basicamente ficam perambulando ao redor de uma determinada árvore */
Spider::Spider(NodePath node) : Prey(node){
	init();
}

/*! "Construtor" comum */
void Spider::init(){
	this->velocity = 0.2;
}

/*! Destroi o objeto Aranha */
Spider::~Spider(){
	spiders_placeholder.remove_node();
	living_tree = NULL;
}

/*! Carrega os NPCs do jogo. */
void Spider::load_spiders(int qtd){
	Spider::spiders_placeholder = Animal::animals_placeholder.attach_new_node("Spiders Placeholder");

	ModelRepository::get_instance()->get_animated_model("aranha")->get_anim_control()->loop("character", false);
	ModelRepository::get_instance()->get_animated_model("aranha")->set_scale(0.0003);
	ModelRepository::get_instance()->get_model("aranha")->set_scale(0.0003);

	PT(Terrain) terrain = World::get_world()->get_terrain();

	for (int i = 0; i < qtd; i++) {
		/* Sorteia uma posição aleatória */
		LPoint3f random_pos = terrain->get_random_point();
		PT(Setor) my_sector = terrain->get_setor_from_pos(random_pos.get_x(), random_pos.get_y());

		/* Carrega o NPC */
		PT(Spider) npc = new Spider(NodePath("Aranha Placeholder"));
		ModelRepository::get_instance()->get_animated_model_instance("aranha")->instance_to(*npc);
		npc->set_tag("model_name", "aranha");
		npc->reparent_to(Simdunas::get_window()->get_render());

		/* Atribui Posição, adiciona no terreno e define uma árvore. */
		npc->set_pos(random_pos);
		npc->set_h(rand()%360);
		terrain->add_prey((PT(Prey)) npc);

		if(rand() % 100 < 20){
			npc->set_has_living_tree(true);
			npc->set_random_living_tree();
		}
		else npc->set_has_living_tree(false);

	}
}
