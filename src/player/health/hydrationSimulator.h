/*
 * hydrationSimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef HYDRATIONSIMULATOR_H
#define HYDRATIONSIMULATOR_H

#include "playerHealthSimulator.h"

class HydrationSimulator : public Simulator {
public:
	HydrationSimulator(PT(PlayerHealth) health);

private:

};

#endif /* HYDRATIONSIMULATOR_H */
