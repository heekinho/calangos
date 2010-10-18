#include "animal.h"

#include "modelRepository.h"
#include "terrain.h"
#include "simdunas.h"

/* Animais a serem carregados */
#include "prey.h"
#include "spider.h"
#include "frog.h"
#include "redLegged.h"
#include "lizard.h"

#define MAXDEGREE 100
#define PROBTHR 80

#define DEBUG_ANIMAL 1

NodePath Animal::animals_placeholder = NodePath("Animals Placeholder");

/*! Copy Constructor */
Animal::Animal(NodePath node) : AnimatedObjetoJogo(node) {
//	set_acting(true);
	this->velocity = 0.01;
	this->stay_x_frame_stoped = 0;
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, act, this);
}


/*! Destroi o Animal */
Animal::~Animal(){
//	if(parent_sector != NULL){
//		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_next, start_acting, this);
//		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_not_next, stop_acting, this);
//	}
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, act, this);
}

/*! Carrega os NPCs do jogo. */
void Animal::load_animals(){
	Animal::animals_placeholder = Simdunas::get_window()->get_render().attach_new_node("Animals Placeholder");

	Prey::load_prey();
	Predator::load_predators();
	Lizard::load_lizards();
	Frog::load_frogs();
}

/*! Exclui e remove do grafo de cena todos os animais, liberando memória. */
//TODO: Descarregar outros tipos de animais aqui?
void Animal::unload_animals(){
	for (int cont = 0; cont < Terrain::MAX_SETORES; cont++){
		World::get_world()->get_terrain()->get_setor(cont)->preys()->clear();
	}

	animals_placeholder.remove_node();
}

/*! Recebe um evento do sistema de eventos a cada *frame* e repassa para um método
 * virtual, que deve ser sobreescrito nas classes derivadas */
void Animal::act(const Event*, void *data){
	Animal* this_animal = (Animal*)data;
	this_animal->act();
}

/*! Onde as ações de comportamento dos animais realmente se encontram */
void Animal::act(){
	if(stay_quiet() <= 0){
		if(rand()%PROBTHR == 34) set_h(*this, rand()%MAXDEGREE - (MAXDEGREE/2));

		move(get_velocity());
	}
}

/*! Define uma quantidade de frames para o animal ficar parado */
void Animal::set_frames_stopped(int frames){
	stay_x_frame_stoped = frames;
}

/*! Neste comportamento o animal faz um sorteio para ver se ele vai ficar
 * por algum instante parado. Um valor é guardado, informando quantos frames
 * o animal deve ficar parado. Se ao entrar neste comportamento o valor for
 * maior que zero, este é então decrementado. */
int Animal::stay_quiet(){
	if(stay_x_frame_stoped > 0){
		if(get_num_children() != 0) pause_animation();
		stay_x_frame_stoped--;
		return stay_x_frame_stoped;
	}

	// Ficar parado...
	if(rand()%250 == 50) stay_x_frame_stoped = 100;
	if(stay_x_frame_stoped <= 0) continue_animation();

	return stay_x_frame_stoped;
}

///*! Define o setor no qual o animal está inserido
// * Sobrescreve set_setor de objeto jogo, para adicionar o esquema de evento. */
////@overhide
//void Animal::set_setor(PT(Setor) setor){
//	if(parent_sector != NULL){
//		// Remove a escuta dos "eventos de borda" da proximidade do player do setor antigo
//		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_next, start_acting, this);
//		Simdunas::get_evt_handler()->remove_hook(parent_sector->EV_player_not_next, stop_acting, this);
//	}
//	parent_sector = setor;
//	// Adiciona a escuta dos "eventos de borda" de proximidade do player do setor atual
//	Simdunas::get_evt_handler()->add_hook(parent_sector->EV_player_next, start_acting, this);
//	Simdunas::get_evt_handler()->add_hook(parent_sector->EV_player_not_next, stop_acting, this);
//	//set_acting(setor->is_player_neighbor());
//}

///*! Sobreescreve a ação de mudança de setor, pois precisa-se colocar os "animais" no
// * respectivo vetor. Classes derivadas devem sobreescrever este comportamento. */
////TODO: Fazer pure virtual, já que coloquei preys() e talz.
//void Animal::change_sector(PT(Setor) new_sector){
//	this->get_setor()->preys()->remove(this);
//	new_sector->preys()->push_back(this);
//
////	this->get_setor()->remove_animal(this);
////	Setor::add_animal(this, new_sector);
//}


/*! Redistribui os animais em setores mais próximos do player. */
void Animal::redistribute_animals(){
	#if(DEBUG_ANIMAL)
		nout << endl << "Redistribuindo Animais";
	#endif

	PT(Player) player = Player::get_instance();
	PT(Terrain) terrain = World::get_world()->get_terrain();
	int max_sectors = terrain->MAX_SETORES;

	/* Obtém os setores adjacentes (player_sector exclusive) */
	vector<PT(Setor)> *all_neighbors = terrain->get_adjacent_sectors();

//	/* Pequeno hack para tirar o próprio setor dos vizinhos */
//	vector<PT(Setor)> *player_neighborhood;
//	for(int i; i < terrain->get_adjacent_sectors()->size(); i++){
//		if(!terrain->get_adjacent_sectors()->at(i)->get_indice() == player->get_setor()->get_indice())
//			player_neighborhood->push_back(terrain->get_adjacent_sectors()->at(i));
//	}

	/* Ao invés de obter os setores adjacentes, não adjacentes, faz-se a verificação e em
	 * seguida já redistribui */

	for (int i = 0; i < max_sectors; ++i) {
		PT(Setor) sector = terrain->get_setor(i);
		/* Se o setor não for considerado vizinho do player, os animais são realocados */
		if(!sector->is_player_neighbor() && sector->get_indice() != player->get_setor()->get_indice()){
			/* Tem que fazer com todos os vetores de animais. */
			Animal::migrate_animals((list<PT(ObjetoJogo)>*) sector->lizards(), sector, all_neighbors);
			Animal::migrate_animals((list<PT(ObjetoJogo)>*) sector->predators(), sector, all_neighbors);
			Animal::migrate_animals((list<PT(ObjetoJogo)>*) sector->animals(), sector, all_neighbors);
		}
	}
}


/*! Migra animais de um setor para outro */
void Animal::migrate_animals(list<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to){
	while(vect->size() > 0){
		int to = rand() % sectors_to->size();
		Animal::migrate_animal(vect->back(), sectors_to->at(to));
	}
}


/*! Migra um animal de um setor para outro, escolhendo aleatóriamente dentre os setores de
 * destino especificados. */
void Animal::migrate_animal(PT(ObjetoJogo) theanimal, PT(Setor) sector_to){
	/* TODO: Ao invés de chamar um método para gerar uma localização aleatória, chamar um
	 * método que gere uma localização inicial a depender do tipo de animal. Um exemplo
	 * seria uma aranha, que teria um algoritmo de localização inicial: perto de árvores. */
	LPoint2d random_pos = sector_to->get_random_pos_inside();
	theanimal->set_pos(random_pos.get_x(), random_pos.get_y(), 0);

	theanimal->was_redistributed();
}
