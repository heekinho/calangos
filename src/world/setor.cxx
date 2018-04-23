#include "setor.h"

#include "player.h"
#include "world.h"
#include "terrain.h"
#include "boundingBox.h"

TypeHandle Setor::_type_handle;

Setor::Setor(LPoint2d inicio, LPoint2d fim, int indice){
	this->_pos_start = inicio;
	this->_pos_end = fim;
	this->_indice = indice;
	this->_player_sector_neighbor = false;
	this->_player_closest_sector = false;

//	_vegetals = NodePath("sectorVegetals");
//	_vegetals.reparent_to(Vegetal::visible_vegetals_placeholder);

	//	// Deve receber eventos de movimento de npc, para atualizar setores por exemplo.
	//	std::stringstream npc_moving_name;
	//	npc_moving_name << "ev_npc_moving_on_sector_" << _indice;
	//	event_handler->add_hook(npc_moving_name.str(), npc_moving, this);

	/* Deve gerar eventos indicando proximidade do player, para npc se movimentar, por exemplo. */
	std::stringstream sector_event_name;
	sector_event_name << "ev_player_next_to_sector_" << indice;
	EV_player_next = sector_event_name.str();

	/* Quando o player deixa de ser vizinho, é preciso lançar um evento. */
	std::stringstream not_next_event_name;
	not_next_event_name << "ev_player_not_next_to_sector_" << indice;
	EV_player_not_next = sector_event_name.str();

	/* Nomeia o setor de acordo */
	std::stringstream sector_name;
	sector_name << "Sector " << indice;
	_root = render.attach_new_node(sector_name.str());
	_root.stash();

//	/* Fixa o bounding box dos setores para evitar ficar recalculando */
//	PT(BoundingBox) bounding_box = new BoundingBox(LPoint3(inicio[0], inicio[1], -10), LPoint3(fim[0], fim[1], 50));
//	_root.node()->set_bounds_type(BoundingVolume::BT_box);
//	_root.node()->set_bounds(bounding_box);
////	_root.show_tight_bounds();
////	_root.show_bounds();
////	_root.node()->set_final(true);

	_animal_list = SectorItems<PT(Animal)>(this);
	_prey_list = SectorItems<PT(Prey)>(this);
	_predator_list = SectorItems<PT(Predator)>(this);
	_vegetal_list = SectorItems<PT(Vegetal)>(this);
	_edible_vegetal_list = SectorItems<PT(EdibleVegetal)>(this);
	_lizard_list = SectorItems<PT(Lizard)>(this);
	_toca_list = SectorItems<PT(ObjetoJogo)>(this);

	_animal_list.get_root().reparent_to(_root);
	_prey_list.get_root().reparent_to(_root);
	_predator_list.get_root().reparent_to(_root);
	_vegetal_list.get_root().reparent_to(_root);
	_edible_vegetal_list.get_root().reparent_to(_root);
	_lizard_list.get_root().reparent_to(_root);
	_toca_list.get_root().reparent_to(_root);

	//event_handler->add_hook(TimeControl::EV_pass_frame, optimize_display_sector, this);
}

//Setor::Setor(){}

Setor::~Setor() {
//	_vegetals.remove_node();
	_root.remove_node();
	event_handler->remove_hooks_with(this);
}

///*! Lançado na movimentação dos NPCs */
//void Setor::npc_moving(const Event* evt, void *data){
//	Setor* this_sector = (Setor*) data;
//	Animal *obj = (Animal*) evt->get_receiver();
//	//this_sector->update_object_sector( (PT(ObjetoJogo)) obj);
//}
NodePath Setor::get_root(){
	return _root;
}

/*! Atualiza o setor do objeto, se este mudou de setor */
void Setor::update_object_sector(PT(ObjetoJogo) object){
	LPoint2d pos = LPoint2d((int)object->get_x(), (int)object->get_y());
	Setor *new_sector = World::get_world()->get_terrain()->get_setor_from_pos(pos);

	if(object->get_setor() == NULL) object->change_sector(new_sector);
	else if(object->get_setor()->get_indice() != new_sector->get_indice()) object->change_sector(new_sector);
}

/*! Retorna se este setor é vizinho do setor no qual o player se encontra */
bool Setor::is_player_neighbor(){
	return _player_sector_neighbor;
}

/*! Define se este setor é vizinho do player.
 * Se for, adiciona um hook para que se lance um evento (player_next) a cada frame */
void Setor::set_player_neighbor(bool is_neighbor){
	if(is_neighbor){
		_player_sector_neighbor = true;
		//event_handler->add_hook(TimeControl::get_instance()->EV_pass_frame, event_player_next, this);
		event_queue->queue_event(new Event(this->EV_player_next));
		if(_root.is_stashed()) _root.unstash();
	}
	else {
		_player_sector_neighbor = false;
		// Este setor para de ouvir eventos pois o player não faz parte da vizinhança.
		//event_handler->remove_hook(TimeControl::get_instance()->EV_pass_frame, event_player_next, this);

		// Lança um evento para avisar aos npcs do setor que o player não é mais vizinho.
		event_queue->queue_event(new Event(this->EV_player_not_next));
		if(!_root.is_stashed()) _root.stash();
	}
}

void Setor::optimize_display_sector(const Event*, void* data){
	((Setor*) data)->optimize_display_sector();
}

#include "cameraControl.h"
void Setor::optimize_display_sector(){
//	if(!get_root().is_stashed()){
		LPoint2 player_pos = player->get_pos(render).get_xy();
//		LVector2 player_forward = render.get_relative_vector(*player, LVector3(0, 1, 0)).get_xy();
		LVector2 player_forward = player->get_orientation(false).get_xy();
		//player_forward.normalize();

		LPoint2 v0 = LPoint2(get_pos_start()[0], get_pos_start()[1]) - player_pos;
		LPoint2 v1 = LPoint2(get_pos_end()[0], get_pos_start()[1]) - player_pos;
		LPoint2 v2 = LPoint2(get_pos_start()[0], get_pos_end()[1]) - player_pos;
		LPoint2 v3 = LPoint2(get_pos_end()[0], get_pos_end()[1]) - player_pos;
		v0.normalize();
		v1.normalize();
		v2.normalize();
		v3.normalize();

		nout << cos(deg_2_rad(CameraControl::get_instance()->get_current_camera()->get_real_camera()->get_lens()->get_fov()[0]*2.0)) << endl;
		static float thr = 0.866025*0.5;
		bool inview = (player_forward.dot(v0) > thr) || (player_forward.dot(v1) > thr)
				   || (player_forward.dot(v2) > thr)  < (player_forward.dot(v3) > thr) ;

		if(!inview && !get_root().is_stashed()) get_root().stash();
		if(inview && get_root().is_stashed()) get_root().unstash();
//	}
}
///*! Lança um evento informando que o player está próximo
// * A identificação é feita pelo nome do evento. */
//void Setor::event_player_next(const Event*, void *data){
//	Setor *this_sector = (Setor*) data;
//	const Event *ev_player_next = new Event(this_sector->EV_player_next);
//	event_queue->queue_event(ev_player_next);
//}


//TODO: Fazer overload
bool Setor::has_inside(LPoint2d point){
	// Interessante o point.compare_to, olhar depois
	// Interessante a implementao de operadores...
	return (point.get_x() >= _pos_start.get_x() && point.get_x() <= _pos_end.get_x())
				&& (point.get_y() >= _pos_start.get_y() && point.get_y() <= _pos_end.get_y());
}

/*! Obtém o _indice (id) do setor */
int Setor::get_indice(){
	return _indice;
}

/*! Obtém o ponto onde começa o setor */
LPoint2d Setor::get_pos_start(){
	return _pos_start;
}

/*! Obtém o ponto onde termina o setor */
LPoint2d Setor::get_pos_end(){
	return _pos_end;
}
/*!Se o setor estiver próximo do subsetor do player*/
void Setor::set_is_closest_sector(bool is_closest){
	_player_closest_sector = is_closest;
}
bool Setor::get_is_closest_sector(){
	return _player_closest_sector;
}

/*! Obtém uma posição aleatória dentro do setor */
// TODO: Esta posição deveria ser float, e não int.
LPoint2d Setor::get_random_pos_inside(){
	double x = (rand() % (int)(_pos_end.get_x() - _pos_start.get_x())) + _pos_start.get_x();
	double y = (rand() % (int)(_pos_end.get_y() - _pos_start.get_y())) + _pos_start.get_y();
	return LPoint2d(x, y);
}

void Setor::unload_sector(){
	event_handler->remove_hooks_with(this);

	_animal_list.deep_clear();
	_prey_list.deep_clear();
	_predator_list.deep_clear();
	_vegetal_list.deep_clear();
	_edible_vegetal_list.deep_clear();
	_lizard_list.deep_clear();
}
