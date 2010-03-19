#include "setor.h"

#include "player.h"
TypeHandle Setor::_type_handle;

Setor::Setor(LPoint2d inicio, LPoint2d fim, int indice){
	this->pos_start = inicio;
	this->pos_end = fim;
	this->indice = indice;
	this->player_sector_neighbor = false;

	// Deve receber eventos de movimento de npc, para atualizar setores por exemplo.
	std::stringstream npc_moving_name;
	npc_moving_name << "ev_npc_moving_on_sector_" << indice;
	Simdunas::get_evt_handler()->add_hook(npc_moving_name.str(), npc_moving, this);

	// Deve gerar eventos indicando proximidade do player, para npc se movimentar, por exemplo.
	std::stringstream sector_event_name;
	sector_event_name << "ev_player_next_to_sector_" << indice;
	EV_player_next = sector_event_name.str();

	// Quando o player deixa de ser vizinho, é preciso lançar um evento.
	std::stringstream not_next_event_name;
	sector_event_name << "ev_player_not_next_to_sector_" << indice;
	EV_player_not_next = sector_event_name.str();
}

Setor::Setor(){}

Setor::~Setor() {}

/*! Lançado na movimentação dos NPCs */
void Setor::npc_moving(const Event* evt, void *data){
	Setor* this_sector = (Setor*) data;
	Animal *obj = (Animal*) evt->get_receiver();
	//this_sector->update_object_sector( (PT(ObjetoJogo)) obj);
}

/*! Atualiza o setor do objeto, se este mudou de setor */
void Setor::update_object_sector(PT(ObjetoJogo) object){
	LPoint2d pos = LPoint2d((int)object->get_x(), (int)object->get_y());
	Setor *new_sector = World::get_default_world()->get_terrain()->get_setor_from_pos(pos);

	// C++ não funciona com if em curto circuito??? Com && não deu certo.
	if(object->get_setor() == NULL) object->change_sector(new_sector);
	else if(object->get_setor()->get_indice() != new_sector->get_indice()) object->change_sector(new_sector);
}

/*! Retorna se este setor é vizinho do setor no qual o player se encontra */
bool Setor::is_player_neighbor(){
	return player_sector_neighbor;
}

/*! Define se este setor é vizinho do player.
 * Se for, adiciona um hook para que se lance um evento (player_next) a cada frame */
void Setor::set_player_neighbor(bool is_neighbor){
	if(is_neighbor == true){
		player_sector_neighbor = true;
		//Simdunas::get_evt_handler()->add_hook(TimeControl::get_instance()->EV_pass_frame, event_player_next, this);
		Simdunas::get_evt_queue()->queue_event(new Event(this->EV_player_next));
	}
	else {
		player_sector_neighbor = false;
		// Este setor para de ouvir eventos pois o player não faz parte da vizinhança.
		//Simdunas::get_evt_handler()->remove_hook(TimeControl::get_instance()->EV_pass_frame, event_player_next, this);

		// Lança um evento para avisar aos npcs do setor que o player não é mais vizinho.
		Simdunas::get_evt_queue()->queue_event(new Event(this->EV_player_not_next));
	}
}

///*! Lança um evento informando que o player está próximo
// * A identificação é feita pelo nome do evento. */
//void Setor::event_player_next(const Event*, void *data){
//	Setor *this_sector = (Setor*) data;
//	const Event *ev_player_next = new Event(this_sector->EV_player_next);
//	Simdunas::get_evt_queue()->queue_event(ev_player_next);
//}


//TODO: Fazer overload
bool Setor::has_inside(LPoint2d point){
	// Interessante o point.compare_to, olhar depois
	// Interessante a implementao de operadores...
	return (point.get_x() >= pos_start.get_x() && point.get_x() <= pos_end.get_x())
		&& (point.get_y() >= pos_start.get_y() && point.get_y() <= pos_end.get_y());
}


// Métodos de vegetais do setor

/*! Adiciona um vegetal ao setor */
void Setor::add_vegetal(PT(Vegetal) vegetal, PT(Setor) setor){
	vegetal->set_setor(setor);
	setor->vegetal_list.push_back(vegetal);
}

void Setor::remove_vegetals() {
	vegetal_list.clear();
}

/*! Obtém o vetor dos vegetais que estão no setor */
vector<PT(Vegetal)>* Setor::get_vegetals(){
	return &vegetal_list;
}


/*! Obtém o vegetal do setor mais próximo de determinado objeto */
PT(Vegetal) Setor::get_closest_vegetal_to(PT(ObjetoJogo) object){
	float dist = 100000000;
	PT(Vegetal) v;

	if(vegetal_list.size() > 0){
		for (vector<PT(Vegetal)>::iterator it = vegetal_list.begin(); it != vegetal_list.end(); ++it) {
			float new_dist = (*it)->get_distance(*object);
			if(new_dist < dist) {
				dist = new_dist;
				v = *it;
			}
		}
		return v;
	}
	return NULL;
}

// Métodos de vegetais comestiveis do setor
/*! Adiciona um vegetal comestivel ao setor */
void Setor::add_edible_vegetal(PT(EdibleVegetal) vegetal, PT(Setor) setor){
	vegetal->set_setor(setor);
	setor->edible_vegetal_list.push_back(vegetal);
}

void Setor::remove_edible_vegetals() {
	vector<PT(EdibleVegetal)>::iterator veg = edible_vegetal_list.begin();
	while( veg != edible_vegetal_list.end()) {
		*veg = NULL;
		veg++;
	}
	edible_vegetal_list.clear();
}

/*! Obtém o vetor dos vegetais comestiveis que estão no setor */
vector<PT(EdibleVegetal)>* Setor::get_edible_vegetals(){
	return &edible_vegetal_list;
}

/*! Obtém o vegetal comestivel do setor mais próximo de determinado objeto */
PT(EdibleVegetal) Setor::get_closest_edible_vegetal_to(PT(ObjetoJogo) object){
	float dist = 100000000;
	PT(EdibleVegetal) v;

	if(edible_vegetal_list.size() > 0){
		for (vector<PT(EdibleVegetal)>::iterator it = edible_vegetal_list.begin(); it != edible_vegetal_list.end(); ++it) {
			float new_dist = (*it)->get_distance(*object);
			if(new_dist < dist) {
				dist = new_dist;
				v = *it;
			}
		}
		return v;
	}
	return NULL;
}

/*! esconde vegetais */
void Setor::hide_vegetals()
{
	if(vegetal_list.size() > 0 && !(vegetal_list[0]->is_hidden()) ) {

		vector<PT(Vegetal)>::iterator vegetal = vegetal_list.begin();
		while( vegetal != vegetal_list.end() ) {
			(*vegetal)->hide();
			vegetal++;
		}

		vector<PT(EdibleVegetal)>::iterator edible_vegetal = edible_vegetal_list.begin();
		while( edible_vegetal != edible_vegetal_list.end() ) {
			(*edible_vegetal)->hide();
			edible_vegetal++;
		}

	}
	World::get_default_world()->get_terrain()->get_shadows()->update_active_shadows(this);
}

/*! mostra vegetais */
void Setor::show_vegetals()
{
	if(vegetal_list.size() > 0 && vegetal_list[0]->is_hidden()) {

		vector<PT(Vegetal)>::iterator vegetal = vegetal_list.begin();

		while( vegetal != vegetal_list.end() ) {
			(*vegetal)->show();
			vegetal++;
		}

		vector<PT(EdibleVegetal)>::iterator edible_vegetal = edible_vegetal_list.begin();
		while( edible_vegetal != edible_vegetal_list.end() ) {
			(*edible_vegetal)->show();
			edible_vegetal++;
		}
	}
	World::get_default_world()->get_terrain()->get_shadows()->update_active_shadows(this);
}



void Setor::add_lizard(PT(Lizard) lizard, PT(Setor) setor){
	lizard->set_setor(setor);
	setor->lizard_list.push_back(lizard);
}

vector<PT(Lizard)>* Setor::get_lizards(){
	return &lizard_list;
}

void Setor::remove_lizard(PT(Lizard) lizard){
	for(int i = 0; i < lizard_list.size(); i++){
		if(*lizard_list.at(i) == *lizard) {
			lizard_list.erase(lizard_list.begin() + i);
		}
	}
}

void Setor::remove_lizards(){
	lizard_list.clear();
}





void Setor::add_predator(PT(Predator) predator, PT(Setor) setor){
	predator->set_setor(setor);
	setor->predator_list.push_back(predator);
}

vector<PT(Predator)>* Setor::get_predators(){
	return &predator_list;
}

void Setor::remove_predator(PT(Predator) predator){
	for(int i = 0; i < predator_list.size(); i++){
		if(*predator_list.at(i) == *predator) {
			predator_list.erase(predator_list.begin() + i);
		}
	}
}

void Setor::remove_predators(){
	predator_list.clear();
}



// Métodos de animais do setor
/*! Adiciona um animal ao setor */
void Setor::add_animal(PT(Animal) animal, PT(Setor) setor){
	animal->set_setor(setor);
	setor->animal_list.push_back(animal);
	//nout << "Adicionado Animal: " << "Setor: " << indice << " _ " << animal_list.size() << endl;
}

/*! Obtém o vetor dos animais que estão no setor */
//TODO: Não deveria retornar uma referência do vetor de setores?
vector<PT(Animal)>* Setor::get_animals(){
	return &animal_list;
}

//TODO: Verificar iteração com list
/*! Remove determinado Animal da lista de Animais do setor */
void Setor::remove_animal(PT(Animal) animal){
	//if(animal_list.size() > 0) nout << "Removendo Animal do Setor: " << indice << ". Agora o setor tem: " << animal_list.size() << endl;
	for(int i = 0; i < animal_list.size(); i++){
		if(*animal_list.at(i) == *animal) {
			animal_list.erase(animal_list.begin() + i);
		}
	}
}

void Setor::remove_animals(){
	animal_list.clear();
}


// Métodos de tocas do setor
/*! Adiciona uma toca ao setor */
void Setor::add_toca(PT(ObjetoJogo) toca, PT(Setor) setor){
	toca->set_setor(setor);
	setor->toca_list.push_back(toca);
}

/*! Obtém o vetor das tocas que estão no setor */
vector<PT(ObjetoJogo)>* Setor::get_tocas(){
	return &toca_list;
}

void Setor::remove_tocas() {
	toca_list.clear();
}


/*! Obtém o indice (id) do setor */
int Setor::get_indice(){
	return indice;
}

/*! Obtém o ponto onde começa o setor */
LPoint2d Setor::get_pos_start(){
	return pos_start;
}

/*! Obtém o ponto onde termina o setor */
LPoint2d Setor::get_pos_end(){
	return pos_end;
}

/*! Obtém uma posição aleatória dentro do setor */
LPoint2d Setor::get_random_pos_inside(){
	double x = (rand() % (int)(pos_end.get_x() - pos_start.get_x())) + pos_start.get_x();
	double y = (rand() % (int)(pos_end.get_y() - pos_start.get_y())) + pos_start.get_y();
	return LPoint2d(x, y);
}


void Setor::unload_sector(){
	Simdunas::get_evt_handler()->remove_hooks_with(this);
}
