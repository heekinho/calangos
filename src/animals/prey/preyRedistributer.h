/*
 *  preyRedistributer.h
 *
 *  Created on: 30/12/2010
 *  Author: heekinho
 */

#ifndef PREYREDISTRIBUTER_H
#define PREYREDISTRIBUTER_H

#include "simdunas.h"
#include "referenceCount.h"

class Prey;

class PreyRedistributer : public ReferenceCount {
public:
	PreyRedistributer(list<PT(Prey)> preys);
	virtual ~PreyRedistributer();

	static void update_redistribution(const Event* evt, void* data){
		((PreyRedistributer*) data)->update_redistribution();
	}
	void update_redistribution();

	void realoc_prey(PT(Prey) prey, LPoint3f ref);

	static const float dist_min;// = 5.0;
	static const float dist_mid;// = 6.0;
	static const float dist_max;// = 10.0;

	LPoint2f generate_distribution_point();
	static float random(float lower, float higher);
private:
	list<PT(Prey)> _preys;
};

#endif
