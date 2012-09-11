/*
 * dietComponent.h
 * Created on: 05/09/2012
 * Author: heekinho
 */

#ifndef DIETCOMPONENT_H
#define DIETCOMPONENT_H

#include "pgSliderBar.h"

class DietComponent {
public:

	DietComponent();
	float get_used_points();

	static const int total_points = 100;
	PT(PGSliderBar) components[3];
};


#endif /* DIETCOMPONENT_H */
