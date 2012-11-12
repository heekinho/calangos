
#include <list>

#include "prey.h"
#include "collision.h"
#include "groupPrey.h"
#include "preyRedistributer.h"
#include "world.h"
#include "terrain.h"
#include "modelRepository.h"


PreyRedistributer* Prey::redistributer = NULL;

/*! Representa as presas do lagarto */
Prey::Prey(NodePath node) : Animal(node) {
	this->living_tree = NULL;
	this->radius_thr = 1.5;
	this->fleing = false;
	set_velocity(ConfigVariableDouble("calangos-speed-prey", 0.8));
};

Prey::~Prey(){
	simdunas_cat.debug() << "Destruindo Presa!" << endl;
	event_handler->remove_hooks_with(this);
}

/*! Realiza o carremento das presas */
void Prey::load_prey(){
	float factor = 0.0001;

	int difficulty_level = Session::get_instance()->get_difficulty_level();
	string level_name;

	if (difficulty_level == 1) {
		level_name = "easy";
	} else if (difficulty_level == 2) {
		level_name = "medium";
	} else {
		level_name = "hard";
	}

	simdunas_cat.debug() << "Carregando Aranhas..." << endl;

	int quan_aranha = ConfigVariableInt("calangos-density-aranha-" + level_name, 10);
	float nutri_aranha = ConfigVariableDouble("calangos-nutri-aranha", 3);
	float hidra_aranha  = ConfigVariableDouble("calangos-hidra-aranha", 3.5);

	load_prey_specie("aranha", quan_aranha, 2*factor, 20, nutri_aranha, hidra_aranha);

	simdunas_cat.debug() << "Carregando Besouros..." << endl;

	int quan_besouro = ConfigVariableInt("calangos-density-besouro-" + level_name, 14);
	float nutri_besouro = ConfigVariableDouble("calangos-nutri-besouro", 4);
	float hidra_besouro  = ConfigVariableDouble("calangos-hidra-besouro", 4.5);

	load_prey_specie("besouro", quan_besouro, 2*factor, 70, nutri_besouro, hidra_besouro);

	simdunas_cat.debug() << "Carregando Grilo..." << endl;

	int quan_grilo = ConfigVariableInt("calangos-density-grilo-" + level_name, 6);
	float nutri_grilo = ConfigVariableDouble("calangos-nutri-grilo", 3);
	float hidra_grilo  = ConfigVariableDouble("calangos-hidra-grilo", 4);

	load_prey_specie("grilo", quan_grilo, 2*factor, 60, nutri_grilo, hidra_grilo);

	simdunas_cat.debug() << "Carregando Cupins..." << endl;

	int grupo_cupim = ConfigVariableInt("calangos-groups-cupim", 1);
	int quan_cupim = ConfigVariableInt("calangos-density-cupim-" + level_name, 10);
	float nutri_cupim = ConfigVariableDouble("calangos-nutri-cupim", 5);
	float hidra_cupim = ConfigVariableDouble("calangos-hidra-cupim", 2.5);

	load_prey_specie("cupim", grupo_cupim, 1*factor, 100, nutri_cupim, hidra_cupim, true, quan_cupim);

	simdunas_cat.debug() << "Carregando Formigas..." << endl;

	int grupo_formiga = ConfigVariableInt("calangos-groups-formiga", 2);
	int quan_formiga = ConfigVariableInt("calangos-density-formiga-" + level_name, 12);
	float nutri_formiga = ConfigVariableDouble("calangos-nutri-formiga", 2);
	float hidra_formiga = ConfigVariableDouble("calangos-hidra-formiga", 2.5);

	load_prey_specie("formiga", grupo_formiga, 2*factor, 80, nutri_formiga, hidra_formiga, true, quan_formiga);

	simdunas_cat.debug() << "Carregando Larvas..." << endl;

	int grupo_larva = ConfigVariableInt("calangos-groups-larva", 1);
	int quan_larva = ConfigVariableInt("calangos-density-larva-" + level_name, 5);
	float nutri_larva = ConfigVariableDouble("calangos-nutri-larva", 7);
	float hidra_larva = ConfigVariableDouble("calangos-hidra-larva", 5.5);

	load_prey_specie("larva", grupo_larva, 2*factor, 100, nutri_larva, hidra_larva, true, quan_larva);

	PT(Terrain) terrain = World::get_world()->get_terrain();
	redistributer = new PreyRedistributer(terrain->list_prey);
}

/*! Configura o modelo base da espécie de presa */
void Prey::configure_prey_model(const string name, double scale){
	ModelRepository::get_instance()->get_animated_model(name)->loop_anim("character");
	ModelRepository::get_instance()->get_animated_model(name)->calc_size_from_bounds();
	ModelRepository::get_instance()->get_animated_model(name)->set_length(0.03, true);
	ModelRepository::get_instance()->get_model(name)->calc_size_from_bounds();
	ModelRepository::get_instance()->get_model(name)->set_length(0.03, true);

	//ModelRepository::get_instance()->get_animated_model(name)->set_scale(scale);
	//ModelRepository::get_instance()->get_model(name)->set_scale(scale);
	//scale = ModelRepository::get_instance()->get_model(name)->get_length()/2;
}

/*! Configura a presa de acordo com os valores passados */
void Prey::configure_prey(const string name, int living_tree_prob, float nutricional, float hidratacao){
	ModelRepository::get_instance()->get_animated_model(name)->instance_to(*this);

	/* Precisa atualizar o tamanho, já que é instanciado */
	calc_size_from_bounds();

	/* Guarda a informação para uso na troca de modelo animado/não-animado */
	set_tag("model_name", name);

	/* Configurações de valor nutritivo e hidratação */
	set_nutritional_value(nutricional);
	set_hydration_value(hidratacao);


	/* Gera localização aleatória. */
	LPoint3f point = World::get_world()->get_terrain()->get_random_point();
	set_pos(point);
	set_h(rand()%360);

	/* Adiciona os animais ao mundo. */
	World::get_world()->get_terrain()->add_prey((PT(Prey)) this);

	/* Dependendo da caracteristica, atribui ou não uma árvore para o npc */
	if((rand() % 100) <= living_tree_prob){
		set_has_living_tree(true);
		set_random_living_tree();
	}
	else set_has_living_tree(false);

	/* Finalmente o torna disponível pra visualização. */
	reparent_to(get_setor()->get_root());
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
			npc->_group = new GroupPrey();
			npc->_group->add_prey(npc);

			PT(Prey) last_leader = npc; // Começa com o líder!

			for(int j = 0; j < n; j++){
				PT(Prey) c_npc = new Prey(NodePath("Prey PlaceHolder"));

				c_npc->configure_prey(name, 0, nutricional, hidratacao);
				c_npc->set_pos(last_leader->get_x(), last_leader->get_y()+ 0.1, 0);
				c_npc->look_at(*last_leader);

				last_leader = c_npc;
				npc->_group->add_prey(c_npc);
				c_npc->_group = npc->_group;
			}
			npc->_group->calc_leaders();
		}
		else {
			npc->_group = NULL;
		}
		//=====================================================//
	}
}

//void Prey::migrate_prey(vector<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to){
//	vector<PT(ObjetoJogo)>* the_copy = new vector<PT(ObjetoJogo)>(*vect);
//
//
//	while(the_copy->size() > 0){
//		int to = rand() % sectors_to->size();
//		Prey::migrate_prey(the_copy->back(), sectors_to->at(to));
//		the_copy->erase(the_copy->end());
//	}
//}
//
//void Prey::migrate_prey(PT(ObjetoJogo) theanimal, PT(Setor) sector_to){
//	PT(Prey) theprey = (PT(Prey))(Prey*)(ObjetoJogo*) theanimal;
//
//	if(theprey->_group == NULL) {
//		Animal::migrate_animal(theanimal, sector_to);
//		return;
//	}
//
//	theprey->was_redistributed();
//	if(theprey->is_master_leader()){
//		LPoint2d random_pos = sector_to->get_random_pos_inside();
//		theprey->set_pos(random_pos.get_x(), random_pos.get_y(), 0);
//
//		PT(Prey) last_leader = theprey;
//		for (list<PT(Prey)>::iterator it = theprey->_group->get_array()->begin(); it != theprey->_group->get_array()->end(); ++it){
//			(*it)->set_pos(last_leader->get_x(), last_leader->get_y()+0.1, 0);
//			(*it)->look_at(*last_leader);
//			last_leader = *it;
//		}
//	}
//}


void Prey::change_sector(PT(Setor) new_sector){
	get_setor()->preys()->remove(this);
	new_sector->preys()->push_back(this);
	//set_random_living_tree();
	reparent_to(get_setor()->get_root());
        
}

/*! É chamado quando uma redistribuição aconteceu. Assim, é possível
 * por exemplo, definir um novo vegetal para a presa */
void Prey::was_redistributed(){
	set_random_living_tree();
}

/*! Comportamento em grupo das presas */
void Prey::group_behavior(){
	float dist_max = 0.1;

	if(get_distance_squared(*get_leader()) > dist_max*dist_max){
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
	else if(get_has_living_tree() && living_tree != NULL && get_distance_squared(*living_tree) > radius_thr*radius_thr){
		look_at(*living_tree);
		move(get_velocity());
		continue_animation();
	}
	else Animal::act();
}

/*! Comportamento de fuga das presas */
void Prey::flee(){
	/* Comportamento */
	look_at(*player);  //TODO: Corrigir depois para não permitir muito giro.
	set_h(*this, 180); // Corrige modelo errado

	this->move(4*get_velocity());
	continue_animation();
}

/*! Recebe o evento que indica a parada da fuga da presa.
 * Normalmente acontece quando o player dá uma mordida sem sucesso, fazendo com
 * que as presas fujam. Este evento é chamado para forçar a parada da fuga.*/
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

/*! Define um novo vegetal aleatório para "morar".
 *  Este código está dependente da redistribuição das presas */
void Prey::set_random_living_tree(){
	if(get_has_living_tree()){
		//TODO: Colocar sorteio de posição aqui?
		//PT(Vegetal) tree = get_setor()->get_closest_vegetal_to((PT(ObjetoJogo)) this);
		PT(Vegetal) tree = chose_new_living_tree();
		set_living_tree(tree);
		float x = float(rand() % int(radius_thr*2000))/1000 - radius_thr;
		float y = float(rand() % int(radius_thr*2000))/1000 - radius_thr;
		if(get_living_tree() != NULL) set_pos(get_living_tree()->get_pos() + LPoint3f(x,y,0));
	}
}

/*! Com toda redistribuição acontecendo, é necessário escolher um novo vegetal
 * para associar com a presa. */
/* TODO: É preciso verificar a probabilidade de determinada presa ser associada
 * à um vegetal */
PT(Vegetal) Prey::chose_new_living_tree(){
	float prey_to_vegetal_max_dist = 8.0;
	float prey_to_player_min_dist = 5.0;

	
	SectorItems<PT(Vegetal)>* vegetal_list = get_setor()->vegetals();
	SectorItems<PT(Vegetal)>::iterator it;
	for (it = vegetal_list->begin(); it != vegetal_list->end(); ++it) {
		float dist_to_player = (*it)->get_distance(*player);
		float dist_to_prey = (*it)->get_distance(*this);
		if(dist_to_player > prey_to_player_min_dist && dist_to_prey < prey_to_vegetal_max_dist){
			return *it;
		}
	}
	return NULL;
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
