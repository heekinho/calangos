#include "spider.h"

#include "simdunas.h"
#include "timeControl.h"

#include "modelRepository.h"

#define MAXDEGREE 100
#define VELOCITY 1.0
#define NORVEL 0.07
#define PROBTHR 80
#define RADIUSTHR 100

NodePath Spider::spiders_placeholder = NodePath("Spiders Placeholder");

/*! Aranhas basicamente ficam perambulando ao redor de uma determinada árvore */
Spider::Spider(NodePath node) : Prey(node){
	init();
}

/*! "Construtor" comum */
void Spider::init(){
	set_acting(false); hide(); // Mover para Animal
	this->living_tree = NULL;
	this->radius_thr = 1;
	this->velocity = 0.2;
}

/*! Destroi o objeto Aranha */
Spider::~Spider(){
	//nout << "ARANHA SENDO DELETADA!" << endl;
	spiders_placeholder.remove_node();
	living_tree = NULL;
}

/*! Carrega os NPCs do jogo. */
void Spider::load_spiders(int qtd){
	Spider::spiders_placeholder = Animal::animals_placeholder.attach_new_node("Spiders Placeholder");
	// Tamanho do terreno para delimitar a area
	int terrain_x_size = World::get_default_world()->get_terrain()->get_x_size();
	int terrain_y_size = World::get_default_world()->get_terrain()->get_y_size();

	ModelRepository::get_instance()->get_animated_model("aranha")->get_anim_control()->loop("character", false);
	ModelRepository::get_instance()->get_animated_model("aranha")->set_scale(0.0003);
	ModelRepository::get_instance()->get_model("aranha")->set_scale(0.0003);

	Setor* my_sector;
	//Testando o funcionamento da classe Spider
	// Geral 100 aranhas aleatóriamente ao redor do terreno.
	int x=0,y=0;
	for (int i = 0, cerror = 0, max_error = 100; i < qtd; i++, cerror = 0) {
		// Cria a aranha e coloca-a no grafo de cena
		//npc->reparent_to(Simdunas::get_window()->get_render());

		// Coloca a aranha no setor correto
		do {
			// Gera localização aleatória.
			x = rand() % terrain_x_size;
			y = rand() % terrain_y_size;
			//nout << "x,y (aranha) " << x <<","<< y << endl;
			// Obtem o setor daquela posição e atualiza o npc
			my_sector = World::get_default_world()->get_terrain()->get_setor_from_pos(LPoint2d(x, y));
			cerror++;
		}
		while ((my_sector->get_vegetals()->size() == 0) && (cerror < max_error));
		if(cerror < max_error){
			PT(Spider) npc = new Spider(NodePath("Aranha Placeholder"));
			ModelRepository::get_instance()->get_animated_model_instance("aranha")->instance_to(*npc);
			npc->set_tag("model_name", "aranha");
			npc->reparent_to(Simdunas::get_window()->get_render());

//			npc->set_scale(0.1);
//			if(rand()%3 == 1) npc->get_anim_control()->stop_all();
//			npc->reparent_to(spiders_placeholder);

			npc->set_pos(x, y, 0);
			World::get_default_world()->get_terrain()->add_animal((PT(Animal)) npc);
			//my_sector->add_animal( (PT(Animal)) npc);
			// Adiciona o animal ao setor definindo a arvore em que a aranha vai ficar
			//nout << "buscando vegetal mais proximo " << endl;
			PT(Vegetal) veg=npc->get_setor()->get_closest_vegetal_to((PT(ObjetoJogo)) npc);
			if(veg!=NULL){
				//nout << "alocando aranha " << endl;
				npc->set_living_tree(veg);
				npc->set_pos(npc->get_living_tree()->get_pos());
				//nout << "SETOR DO ANIMAL (aranha) " << i << " - " << npc->get_setor()->get_indice() << endl;
			} else nout << "ERRO: NAO ACHOU VEGETAL!!!!!!!!!" <<endl;
		}


	}
}

/* Implementação do método da classe Animal */
void Spider::act(){
	if(is_acting()){
		if(living_tree){
			if(!stay_quiet()){
				surround_tree();
			}
		}
		// Fica andando até achar uma arvore... A implementar
		else this->Animal::act();
	}
}


/* Movimento padrão executado pelas aranhas */
void Spider::surround_tree(){
	double distance = (living_tree->get_pos() - get_pos()).length();
	if(distance < radius_thr){
		/* Cria aleatoriedade no movimento da aranha */
		if(rand()%PROBTHR == 34) set_h(*this, rand()%MAXDEGREE - (MAXDEGREE/2));
	}
	else look_at(*living_tree);

	move(get_velocity());
}

/* Define o vegetal sobre o qual a aranha atua */
void Spider::set_living_tree(PT(Vegetal) living_tree){
	this->living_tree = living_tree;
}

/* Obtém o vegetal sobre o qual a aranha atua */
PT(Vegetal) Spider::get_living_tree(){
	return this->living_tree;
}
