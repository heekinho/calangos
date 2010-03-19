#ifndef SETOR_H
#define SETOR_H

#include "pandaFramework.h"
#include "objetoJogo.h"
#include "animal.h"
#include "vegetal.h"
#include "lizard.h"
#include "predator.h"

#include "referenceCount.h"
#include <list>
#include <vector>

class Setor : public TypedReferenceCount{
public:
	Setor();
	Setor(LPoint2d inicio, LPoint2d fim, int indice);

	~Setor();
	void unload_sector();


	static void npc_moving(const Event* evt, void *data);
	void update_object_sector(PT(ObjetoJogo) object);

	/*! Operações de vizinhança */
	string EV_player_next;
	string EV_player_not_next;
	bool is_player_neighbor();
	void set_player_neighbor(bool n);
	static void event_player_next(const Event*, void *data);

	//void init_setor();
	bool has_inside(LPoint2d point);


	static void add_lizard (PT(Lizard) lizard, PT(Setor) setor);
	void remove_lizard(PT(Lizard) lizard);
	void remove_lizards();
	vector<PT(Lizard)>* get_lizards();

	static void add_animal (PT(Animal) animal, PT(Setor) setor);
	void remove_animal(PT(Animal) animal);
	void remove_animals();
	vector<PT(Animal)>* get_animals();

	static void add_predator (PT(Predator) predator, PT(Setor) setor);
	void remove_predator(PT(Predator) animal);
	void remove_predators();
	vector<PT(Predator)>* get_predators();

	//TODO: Reference Counting e vector*
	static void add_vegetal(PT(Vegetal) vegetal, PT(Setor) setor);
	void remove_vegetals();
	vector<PT(Vegetal)>* get_vegetals();
	PT(Vegetal) get_closest_vegetal_to(PT(ObjetoJogo) object);
	
	static void add_edible_vegetal(PT(EdibleVegetal) vegetal, PT(Setor) setor);
	void remove_edible_vegetals();
	vector<PT(EdibleVegetal)>* get_edible_vegetals();
	PT(EdibleVegetal) get_closest_edible_vegetal_to(PT(ObjetoJogo) object);

	void hide_vegetals();
	void show_vegetals();

	static void add_toca (PT(ObjetoJogo) toca, PT(Setor) setor);
	vector<PT(ObjetoJogo)>* get_tocas();
	void remove_tocas();

	int get_indice();
	LPoint2d get_pos_start();
	LPoint2d get_pos_end();
	LPoint2d get_random_pos_inside();

	// Typed Object
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "Setor"); }

private:

	vector<PT(Lizard)> lizard_list;
	vector<PT(Animal)> animal_list;
	vector<PT(Vegetal)> vegetal_list;
	vector<PT(Predator)> predator_list;
	vector<PT(EdibleVegetal)> edible_vegetal_list;
	vector<PT(ObjetoJogo)> toca_list;

	LPoint2d pos_start;
	LPoint2d pos_end;

	int indice;

	bool player_sector_neighbor;
	static TypeHandle _type_handle;
};

#endif
