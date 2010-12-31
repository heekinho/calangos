#ifndef PREY_H
#define PREY_H

#include "animal.h"
#include "vegetal.h"
#include "edible.h"

class GroupPrey;
class Prey;
class PreyRedistributer;
#include "preyRedistributer.h"

class Prey : public Animal, public Edible {
public:
	Prey(NodePath node);
	static void load_prey();

	static void load_prey_specie(const string name, int qtd, double scale, int living_tree_prob, float nutricional, float hidratacao, bool comp_group = false, int n = 0);
	static void load(){};
	virtual void configure_prey(const string name, int living_tree_prob, float nutricional, float hidratacao);
	static void configure_prey_model(const string name, double scale);

	virtual void act();

	virtual void pause_animation();
	virtual void continue_animation();

	/*! Relacionados ao comportamento de fuga */
	virtual void flee();
	void set_fleing(bool fleing){ this->fleing = fleing; };
	bool get_fleing(){ return this->fleing; };
	static void stop_flee(const Event *theEvent, void *data);

	/*! Relacionados à redistribuição */
	virtual void change_sector(PT(Setor) new_sector);
	virtual void was_redistributed();
	static void migrate_prey(vector<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to);
	static void migrate_prey(PT(ObjetoJogo) theanimal, PT(Setor) sector_to);

	/*! Relacionados ao comportamento territorialista */
	void set_living_tree(PT(Vegetal) living_tree);
	PT(Vegetal) get_living_tree();
	void set_random_living_tree();
	void set_has_living_tree(bool has_living_tree){ this->has_living_tree = has_living_tree; };
	bool get_has_living_tree(){ return has_living_tree; };
	PT(Vegetal) chose_new_living_tree();

	/*! Relacionados ao comportamento em grupo */
	bool is_master_leader(){ if(leader == NULL) return true; return false; };
	void set_leader(PT(Prey) leader){ this->leader = leader; };
	PT(Prey) get_leader(){ return this->leader; };
	void group_behavior();

	/*! Relacionado ao novo sistema de redistribuição */
	static PreyRedistributer* redistributer;

protected:
	bool fleing;

	PT(Vegetal) living_tree;
	float radius_thr;
	bool has_living_tree;
public:
	GroupPrey* _group;
	PT(Prey) leader;
};

#endif

