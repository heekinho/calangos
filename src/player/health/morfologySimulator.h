/*
 * morfologySimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef MORFOLOGYSIMULATOR_H
#define MORFOLOGYSIMULATOR_H

#include "playerHealthSimulator.h"

class MorfologySimulator : public Simulator {
public:
	MorfologySimulator(PT(PlayerHealth) health);

};

#endif /* MORFOLOGYSIMULATOR_H */
