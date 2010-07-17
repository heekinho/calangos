#ifndef SETOR_H
#define SETOR_H

#include "pandaFramework.h"
#include "objetoJogo.h"
#include "animal.h"
#include "vegetal.h"
#include "lizard.h"
#include "predator.h"
#include "prey.h"

#include "referenceCount.h"

#include "sectorItems.h"

class Setor : public TypedReferenceCount {
public:
	Setor(LPoint2d inicio, LPoint2d fim, int indice);

	~Setor();
	void unload_sector();

//	static void npc_moving(const Event* evt, void *data);
	void update_object_sector(PT(ObjetoJogo) object);

	/*! Caracteristicas do setor */
	int get_indice();
	LPoint2d get_pos_start();
	LPoint2d get_pos_end();
	LPoint2d get_random_pos_inside();

	/*! Operações de vizinhança */
	string EV_player_next;
	string EV_player_not_next;
	bool is_player_neighbor();
	void set_player_neighbor(bool n);
	static void event_player_next(const Event*, void *data);

	//void init_setor();
	bool has_inside(LPoint2d point);

	NodePath _vegetals;

	void hide_vegetals();
	void show_vegetals();

	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "Setor"); }

	SectorItems<PT(Prey)>* preys(){ return &_prey_list; };
	SectorItems<PT(Predator)>* predators(){ return &_predator_list; };
	SectorItems<PT(Vegetal)>* vegetals(){ return &_vegetal_list; };
	SectorItems<PT(EdibleVegetal)>* edible_vegetals(){ return &_edible_vegetal_list; };
	SectorItems<PT(Lizard)>* lizards(){ return &_lizard_list; };
	SectorItems<PT(ObjetoJogo)>* tocas(){ return &_toca_list; };
private:
	SectorItems<PT(Prey)> _prey_list;
	SectorItems<PT(Predator)> _predator_list;
	SectorItems<PT(Vegetal)> _vegetal_list;
	SectorItems<PT(EdibleVegetal)> _edible_vegetal_list;
	SectorItems<PT(Lizard)> _lizard_list;
	SectorItems<PT(ObjetoJogo)> _toca_list;

	LPoint2d _pos_start;
	LPoint2d _pos_end;

	int _indice;

	bool _player_sector_neighbor;
	static TypeHandle _type_handle;
};

#endif
