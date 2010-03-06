#ifndef PREDATOR_H
#define PREDATOR_H

#include "animatedObjetoJogo.h"
#include "animal.h"

class Predator : public Animal {
public:
	Predator(NodePath node);
	~Predator();

	static void load_predators();

	virtual void act();
	virtual void pause_animation();
	virtual void continue_animation();
private:
	void pursuit();
	void bite();
};



#endif

