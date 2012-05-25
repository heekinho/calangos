/*
 * dietSimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef DIETSIMULATOR_H
#define DIETSIMULATOR_H

#include "playerHealthSimulator.h"
#include "playerHealth.h"

class DietSimulator : public Simulator {
public:
	DietSimulator(PT(PlayerHealth) health);

};

#endif /* DIETSIMULATOR_H */
