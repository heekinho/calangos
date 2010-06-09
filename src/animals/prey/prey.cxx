#include "prey.h"

#include "groupPrey.h"
#include "spider.h"
#include "world.h"
#include "terrain.h"
#include "modelRepository.h"

Prey::Prey(NodePath node) : Animal(node) {
	this->living_tree = NULL;
	this->radius_thr = 1.5;
	this->fleing = false;
	set_velocity(0.085);
};


void Prey::load_prey(){
		nout << "Carregando Aranhas..." << endl;
		//Spider::load_spiders(1000);
		load_prey_specie("aranha", 100, 0.0002, 20, 3, 3.5);

		nout << "Carregando Besouros..." << endl;
		load_prey_specie("besouro", 140, 0.0002, 70, 4, 4.5);

		nout << "Carregando Cupins..." << endl;
		load_prey_specie("cupim", 130/10, 0.0001, 100, 5, 2.5, true, 10);

		nout << "Carregando Formigas..." << endl;
		//load_prey_specie("formiga", 150, 0.0002, 80, 2, 2.5);
		load_prey_specie("formiga", 150/12, 0.0002, 80, 2, 2.5, true, 12);

		nout << "Carregando Grilo..." << endl;
		load_prey_specie("grilo", 60, 0.0002, 60, 3, 4);

		nout << "Carregando Larvas..." << endl;
		load_prey_specie("larva", 80/5, 0.0002, 100, 7, 5.5, true, 5);
}


void Prey::configure_prey_model(const string name, double scale){
	ModelRepository::get_instance()->get_animated_model(name)->get_anim_control()->loop("character", false);
	ModelRepository::get_instance()->get_animated_model(name)->set_scale(scale);
	ModelRepository::get_instance()->get_model(name)->set_scale(scale);
}

void Prey::configure_prey(const string name, int living_tree_prob, float nutricional, float hidratacao){
	ModelRepository::get_instance()->get_animated_model(name)->instance_to(*this);

	/* Guarda a informação para uso na troca de modelo animado/não-animado */
	set_tag("model_name", name);

	/* Configurações de valor nutritivo e hidratação */
	set_valor_nutricional(nutricional);
	set_valor_hidratacao(hidratacao);

	/* Gera localização aleatória. */
	LPoint3f point = World::get_default_world()->get_terrain()->get_random_point();
	set_pos(point);
	set_h(rand()%360);

	/* Adiciona os animais ao mundo. */
	World::get_default_world()->get_terrain()->add_animal((PT(Animal)) this);

	/* Dependendo da caracteristica, atribui ou não uma árvore para o npc */
	if((rand() % 100) < living_tree_prob){
		set_has_living_tree(true);
		set_random_living_tree();
	}
	else set_has_living_tree(false);

	/* Finalmente o torna disponível pra visualização. */
	reparent_to(Simdunas::get_window()->get_render());
	continue_animation();
}

/*! Carrega cada tipo diferente de presa: aranha, grilo... */
void Prey::load_prey_specie(const string name, int qtd, double scale, int living_tree_prob, float nutricional, float hidratacao, bool comp_group, int n){
	Prey::configure_prey_model(name, scale);
	for(int i = 0; i < qtd; i++){
		/* Cria nova instância de cada Presa. */
		PT(Prey) npc = new Prey(NodePath("Prey PlaceHolder"));
		npc->configure_prey(name, living_tree_prob, nutricional, hidratacao);

		//=====================================================//
		if(comp_group){
			npc->group = new GroupPrey();
			npc->group->add_prey(npc);

			PT(Prey) last_leader = npc; // Começa com o líder!

			for(int j = 0; j < n; j++){
				PT(Prey) c_npc = new Prey(NodePath("Prey PlaceHolder"));

				c_npc->configure_prey(name, 0, nutricional, hidratacao);
				c_npc->set_pos(last_leader->get_x(), last_leader->get_y()+ 0.1, 0);
				c_npc->look_at(*last_leader);

				last_leader = c_npc;
				npc->group->add_prey(c_npc);
				c_npc->group = npc->group;
			}
			npc->group->calc_leaders();
		}
		else {
			npc->group = NULL;
		}
		//=====================================================//

	}
}

void Prey::migrate_prey(vector<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to){
	vector<PT(ObjetoJogo)>* the_copy = new vector<PT(ObjetoJogo)>(*vect);


	while(the_copy->size() > 0){
		int to = rand() % sectors_to->size();
		Prey::migrate_prey(the_copy->back(), sectors_to->at(to));
		the_copy->erase(the_copy->end());
	}
}

void Prey::migrate_prey(PT(ObjetoJogo) theanimal, PT(Setor) sector_to){
	PT(Prey) theprey = (PT(Prey))(Prey*)(ObjetoJogo*) theanimal;

	if(theprey->group == NULL) {
		Animal::migrate_animal(theanimal, sector_to);
		return;
	}

	theprey->was_redistributed();
	if(theprey->is_master_leader()){
		LPoint2d random_pos = sector_to->get_random_pos_inside();
		theprey->set_pos(random_pos.get_x(), random_pos.get_y(), 0);

		PT(Prey) last_leader = theprey;
		for (list<PT(Prey)>::iterator it = theprey->group->get_array()->begin(); it != theprey->group->get_array()->end(); ++it){
			(*it)->set_pos(last_leader->get_x(), last_leader->get_y()+0.1, 0);
			(*it)->look_at(*last_leader);
			last_leader = *it;
		}

	}
}


//void Prey::change_sector(PT(Setor) new_sector){
//	Animal::change_sector(new_sector);
//	set_random_living_tree();
//}


void Prey::was_redistributed(){
	set_random_living_tree();
}

void Prey::group_behavior(){
	float dist_max = 0.1;

	if(get_distance(*get_leader()) > dist_max){
		look_at(*get_leader());
//		set_h(*this, rand()%40 - 20);
		move(get_velocity());
		continue_animation();
	}
	else Animal::act();
}

/*! Define o comportamento padrão das presas. */
void Prey::act(){
	if(fleing) flee();
	else if(get_leader() != NULL) group_behavior();
	else if(get_has_living_tree() && living_tree != NULL && get_distance(*living_tree) > radius_thr){
		look_at(*living_tree);
		move(get_velocity());
		continue_animation();
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
		//TODO: Colocar sorteio de posição aqui?
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
