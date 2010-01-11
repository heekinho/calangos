#include "animal.h"

#include "modelRepository.h"
#include "terrain.h"
#include "simdunas.h"

/* Animais a serem carregados */
#include "spider.h"
#include "redLegged.h"
#include "lizard.h"

#define MAXDEGREE 100
#define VELOCITY 0.05
#define PROBTHR 80

NodePath Animal::animals_placeholder = NodePath("Animals Placeholder");

/*! Default Constructor */
Animal::Animal(){}

/*! Copy Constructor */
Animal::Animal(NodePath node) : AnimatedObjetoJogo(node) {}

/*! Constrói um Animal carregando um modelo */
Animal::Animal(const string &model) : AnimatedObjetoJogo(model){}

/*! Constrói um Animal baseado no recurso de Instancing
 * Basta passar um ponteiro para o modelo a ser instanciado */
Animal::Animal(PT(ObjetoJogo) base_object) : AnimatedObjetoJogo(base_object) {}


/*! Constrói um Animal baseado no recurso de Instancing
 * Basta passar um ponteiro para o modelo a ser instanciado */
Animal::Animal(PT(Animal) base_animal) : AnimatedObjetoJogo(animals_placeholder.attach_new_node("Placeholder")) {
	base_animal->instance_to(*this);
}

//void Animal::init(){
//}


/*! Destroi o Animal */
Animal::~Animal(){
	if(parent_sector != NULL){
		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_next, start_acting, this);
		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_not_next, stop_acting, this);
	}
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, act, this);
}

/*! Carrega os NPCs do jogo. */
void Animal::load_animals(){
	Animal::animals_placeholder = Simdunas::get_window()->get_render().attach_new_node("Animals Placeholder");
	/* Presas */
	//load_animals("aranha", 50);
	nout << "Carregando Aranhas..." << endl;
	Spider::load_spiders(100);
	nout << "Carregando Besouros..." << endl;
	load_animals("besouro", 100, 0.0002);
	nout << "Carregando Cupins..." << endl;
	load_animals("cupim", 100 , 0.0001);
	nout << "Carregando Formigas..." << endl;
	load_animals("formiga", 100, 0.0002);
	nout << "Carregando Grilo..." << endl;
	load_animals("grilo", 100, 0.0002);
	nout << "Carregando Larvas..." << endl;
	load_animals("larva", 100, 0.0002);

	Predator::load_predators();

	Lizard::load_lizards();
	/* Predadores */
	//RedLegged::load_redleggeds(100);
}

/*! Carrega os NPCs do jogo de forma genérica. Apenas para testes. */
void Animal::load_animals(const string name, int qtd, double scale){
	// Tamanho do terreno para delimitar a area
	int width = World::get_default_world()->get_terrain()->get_x_size();
	int length = World::get_default_world()->get_terrain()->get_y_size();

	ModelRepository::get_instance()->get_animated_model(name)->get_anim_control()->loop("character", false);
	ModelRepository::get_instance()->get_animated_model(name)->set_scale(scale);

	for(int i = 0; i < qtd; i++){
		PT(Animal) current_npc = new Animal(*ModelRepository::get_instance()->get_animated_model_instance(name));
		current_npc->reparent_to(Simdunas::get_window()->get_render());

		// Gera localização aleatória.
		int x = rand() % width;
		int y = rand() % length;
		current_npc->set_pos(x, y, 0);

		//current_npc->set_acting(false);
		// Nova forma mais fácil de adicionar animais.
		World::get_default_world()->get_terrain()->add_animal( (PT(Animal)) current_npc);
	}
}

/*! Exclui e remove do grafo de cena todos os animais, liberando memória. */
void Animal::unload_animals(){
	for (int cont = 0; cont < Terrain::MAX_SETORES; cont++){
		World::get_default_world()->get_terrain()->get_setor(cont)->remove_animals();
	}

	animals_placeholder.remove_node();
}

/* Identifica se aranha está agindo */
void Animal::set_acting(bool acting){
//	if(acting) start_acting(NULL, this);
//	else stop_acting(NULL, this);

	this->acting = acting;
}

/* Identifica se aranha está agindo */
bool Animal::is_acting(){
	return acting;
}


void Animal::act(const Event*, void *data){
	Animal* this_animal = (Animal*)data;
	this_animal->act();
}

// Generic NPC
void Animal::act(){
	float elapsed = TimeControl::get_instance()->get_elapsed_time();
//	float factor = /*get_scale().get_x() *  */ elapsed * VELOCITY ;// * NORVEL;
	if(acting && !stay_quiet()){
		//nout << this->get_anim_control()->get_num_anims() << this->get_anim_control()->get_anim_name(0) << endl;
		if(rand()%PROBTHR == 34) set_h(*this, rand()%MAXDEGREE - (MAXDEGREE/2));

//		// TODO: Movimentar isso para um método move()
//		LVecBase3f forward (get_net_transform()->get_mat().get_row3(1));
//		forward.set_z(0);
//		forward.normalize();
//
//		set_pos(get_pos() + forward * factor);

		move(elapsed * VELOCITY);

	}
}


int Animal::stay_quiet(){
	if(stay_x_frame_stoped > 0){
		//stop_animation();
		return --stay_x_frame_stoped;
	}

	//Teste: Ficar parado...
	if(rand()%250 == 50) stay_x_frame_stoped = 100;
	if(stay_x_frame_stoped == 0) {
		//continue_animation();
	}
	return stay_x_frame_stoped;
}





/*! Define o momento de desativação de ação do NPC, geralmente quando recebe uma notificação
 * do terreno, informando que o player já não está próximo */
void Animal::stop_acting(const Event*, void *data){
	Animal *this_animal = (Animal*) data;
	this_animal->hide();

	this_animal->set_acting(false);
	// Desativa o acting
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, act, this_animal);
}

/*! Define o momento de ativação de ação do NPC, geralmente quando recebe uma notificação
 * do terreno, informando que o player está próximo */
void Animal::start_acting(const Event*, void *data){
	Animal *this_animal = (Animal*) data;
	this_animal->show();

	this_animal->set_acting(true);
	// Ativa o acting
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, act, this_animal);
}


/*! Define o setor no qual o animal está inserido
 * Sobrescreve set_setor de objeto jogo, para adicionar o esquema de evento. */
//@overhide
void Animal::set_setor(PT(Setor) setor){
	if(parent_sector != NULL){
		// Remove a escuta dos "eventos de borda" da proximidade do player do setor antigo
		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_next, start_acting, this);
		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_not_next, stop_acting, this);
	}
	parent_sector = setor;
	// Adiciona a escuta dos "eventos de borda" de proximidade do player do setor atual
	Simdunas::get_evt_handler()->add_hook(parent_sector->EV_player_next, start_acting, this);
	Simdunas::get_evt_handler()->add_hook(parent_sector->EV_player_not_next, stop_acting, this);
	//set_acting(setor->is_player_neighbor());
}

//void Animal::has_moved(){
//	nout << "Chamando has_moved de Animal" << endl;
//}

void Animal::change_sector(PT(Setor) new_sector){
	//nout << "Change Sector de Animal" << endl;
	this->get_setor()->remove_animal(this);
	Setor::add_animal(this, new_sector);
}


/*! Redistribui os animais em setores mais próximos do player. */
void Animal::redistribute_animals(){
	#ifdef DEBUG
		cout << endl << "Redistribuindo Animais";
	#endif

	PT(Player) player = Player::get_instance();
	PT(Terrain) terrain = World::get_default_world()->get_terrain();
	int max_sectors = terrain->MAX_SETORES;

	/* Obtém os setores adjacentes (player_sector exclusive) */
	vector<PT(Setor)> *all_neighbors = terrain->get_adjacent_sectors();

//	/* Pequeno hack para tirar o próprio setor dos vizinhos */
//	vector<PT(Setor)> *player_neighborhood;
//	for(int i; i < terrain->get_adjacent_sectors()->size(); i++){
//		if(!terrain->get_adjacent_sectors()->at(i)->get_indice() == player->get_setor()->get_indice())
//			player_neighborhood->push_back(terrain->get_adjacent_sectors()->at(i));
//	}

	nout << endl;
	/* Ao invés de obter os setores adjacentes, não adjacentes, faz-se a verificação e em
	 * seguida já redistribui */

	for (int i = 0; i < max_sectors; ++i) {
		PT(Setor) sector = terrain->get_setor(i);
		/* Se o setor não for considerado vizinho do player, os animais são realocados */
		if(!sector->is_player_neighbor() && sector->get_indice() != player->get_setor()->get_indice()){
			Animal::migrate_animals((vector<PT(ObjetoJogo)>*) sector->get_animals(), sector, all_neighbors);
			Animal::migrate_animals((vector<PT(ObjetoJogo)>*) sector->get_lizards(), sector, all_neighbors);
		}
	}
	//nout << "Número de Animais no setor do Player depois: " << Player::get_instance()->get_setor()->get_animals()->size() << endl;
}


/*! Migra animais de um setor para outro */
void Animal::migrate_animals(vector<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to){
	while(vect->size() > 0){
		int to = rand() % sectors_to->size();
		Animal::migrate_animal(vect->back(), sectors_to->at(to));
	}
}


/*! Migra um animal de um setor para outro, escolhendo aleatóriamente dentre os setores de
 * destino especificados. */
void Animal::migrate_animal(PT(ObjetoJogo) theanimal, PT(Setor) sector_to){
	theanimal->change_sector(sector_to);
	/* TODO: Ao invés de chamar um método para gerar uma localização aleatória, chamar um
	 * método que gere uma localização inicial a depender do tipo de animal. Um exemplo
	 * seria uma aranha, que teria um algoritmo de localização inicial: perto de árvores. */
	//nout << "SECTOR TO: " << sector_to->get_indice();
	LPoint2d random_pos = sector_to->get_random_pos_inside();
	theanimal->set_pos(random_pos.get_x(), random_pos.get_y(), 0);
}
