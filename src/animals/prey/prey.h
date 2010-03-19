#ifndef PREY_H
#define PREY_H

#include "animal.h"

class Prey : public Animal {
public:
	Prey(NodePath node);
	static void load_prey();

	static void load_prey_specie(const string name, int qtd, double scale);

	virtual void act();

	virtual void pause_animation();
	virtual void continue_animation();
};


#endif

