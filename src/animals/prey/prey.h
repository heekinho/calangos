#ifndef PREY_H
#define PREY_H

#include "animal.h"
#include "vegetal.h"
#include "typeHandle.h"

class Prey : public Animal {
public:
	Prey(NodePath node);
	static void load_prey();

	static void load_prey_specie(const string name, int qtd, double scale);

	virtual void act();
	virtual void flee();

	virtual void pause_animation();
	virtual void continue_animation();

	void set_fleing(bool fleing){ this->fleing = fleing; };
	bool get_fleing(){ return this->fleing; };
	static void stop_flee(const Event *theEvent, void *data);

	void set_living_tree(PT(Vegetal) living_tree);
	PT(Vegetal) get_living_tree();
protected:
	bool fleing;
	PT(Vegetal) living_tree;
	float radius_thr;
};


#endif

