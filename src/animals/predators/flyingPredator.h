#ifndef FLYINGPREDATOR_H
#define FLYINGPREDATOR_H

#include "predator.h"

class FlyingPredator : public Predator {
public:
	FlyingPredator(NodePath node);
	~FlyingPredator();

	static void load_predators();
	static void load_predator(const string &model, int qtd, float scale, int orientation = -1);

	virtual void act();
};

#endif
