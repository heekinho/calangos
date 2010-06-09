#include "prey.h"

#include "spider.h"
#include "world.h"
#include "terrain.h"
#include "modelRepository.h"

Prey::Prey(NodePath node) : Animal(node) {
	this->living_tree = NULL;
	this->radius_thr = 1.5;
	this->fleing = false;
	set_velocity(85);
};


void Prey::load_prey(){
		nout << "Carregando Aranhas..." << endl;
		//Spider::load_spiders(1000);
		load_prey_specie("aranha", 100, 0.02, 20);

		nout << "Carregando Besouros..." << endl;
		load_prey_specie("besouro", 100, 0.0002, 70);

		nout << "Carregando Cupins..." << endl;
		load_prey_specie("cupim", 100, 0.0001, 100);

		nout << "Carregando Formigas..." << endl;
		load_prey_specie("formiga", 100, 0.0002, 80);

		nout << "Carregando Grilo..." << endl;
		load_prey_specie("grilo", 100, 0.0002, 60);

		nout << "Carregando Larvas..." << endl;
		load_prey_specie("larva", 100, 0.0002, 100);
}


/*! Carrega cada tipo diferente de presa: aranha, grilo... */
void Prey::load_prey_specie(const string name, int qtd, double scale, int living_tree_prob){
	// Define alguma características do modelo fixo (e não das instâncias). Obs.: Talvez isso mude de lugar mais tarde.
	ModelRepository::get_instance()->get_animated_model(name)->get_anim_control()->loop("character", false);
	ModelRepository::get_instance()->get_animated_model(name)->set_scale(scale);
	ModelRepository::get_instance()->get_model(name)->set_scale(scale);

	for(int i = 0; i < qtd; i++){
		/* Cria nova instância de cada Presa. */
		PT(Prey) npc = new Prey(NodePath("Prey PlaceHolder"));
		ModelRepository::get_instance()->get_animated_model(name)->instance_to(*npc);

		/* Guarda a informação para uso na troca de modelo animado/não-animado */
		npc->set_tag("model_name", name);

		/* Gera localização aleatória. */
		LPoint3f point = World::get_default_world()->get_terrain()->get_random_point();
		npc->set_pos(point);
		npc->set_h(rand()%360);

		/* Adiciona os animais ao mundo. */
		World::get_default_world()->get_terrain()->add_animal( (PT(Animal)) npc);

		/* Dependendo da caracteristica, atribui ou não uma árvore para o npc */
		if((rand() % 100) < living_tree_prob){
			npc->set_has_living_tree(true);
			npc->set_random_living_tree();
		}
		else npc->set_has_living_tree(false);

		/* Finalmente o torna disponível pra visualização. */
		npc->reparent_to(Simdunas::get_window()->get_render());
		npc->continue_animation();
	}
}

void Prey::change_sector(PT(Setor) new_sector){
	Animal::change_sector(new_sector);
	set_random_living_tree();
}

/*! Define o comportamento padrão das presas. */
void Prey::act(){
	if(fleing) flee();
	else if(get_has_living_tree() && living_tree != NULL && get_distance(*living_tree) > radius_thr){
		look_at(*living_tree);
		move(get_velocity());
	}
	else Animal::act();
}

void Prey::flee(){
	PT(Player) player = Player::get_instance();

	/* Comportamento */
	look_at(*player);  //TODO: Corrigir depois para não permitir muito giro.
	set_h(*this, 180); // Corrige modelo errado

	this->move(4*get_velocity());
	continue_animation();
}

void Prey::stop_flee(const Event *theEvent, void *data){
	Prey* this_prey = (Prey*) data;
	this_prey->set_fleing(false);
}

/* Define o vegetal sobre o qual a aranha atua */
void Prey::set_living_tree(PT(Vegetal) living_tree){
	this->living_tree = living_tree;
}


/* Obtém o vegetal sobre o qual a aranha atua */
PT(Vegetal) Prey::get_living_tree(){
	return this->living_tree;
}

void Prey::set_random_living_tree(){
	if(get_has_living_tree()){
		PT(Vegetal) tree = get_setor()->get_closest_vegetal_to((PT(ObjetoJogo)) this);
		set_living_tree(tree);
		float x = float(rand() % int(radius_thr*2000))/1000 - radius_thr;
		float y = float(rand() % int(radius_thr*2000))/1000 - radius_thr;
		if(get_living_tree() != NULL) set_pos(get_living_tree()->get_pos() + LPoint3f(x,y,0));
	}
}

/*! Pausa a animação, neste caso fazendo o link com o modelo não-animado */
void Prey::pause_animation(){
	node()->remove_all_children();
	ModelRepository::get_instance()->get_model(get_tag("model_name"))->instance_to(*this);
}

/*! Continua a animação, neste caso fazendo o link com o modelo animado */
void Prey::continue_animation(){
	node()->remove_all_children();
	ModelRepository::get_instance()->get_animated_model(get_tag("model_name"))->instance_to(*this);
}
