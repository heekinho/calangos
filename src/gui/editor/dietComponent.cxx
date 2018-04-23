/*
 * dietComponent.cxx
 * Created on: 05/09/2012
 * Author: heekinho
 */

#include "dietComponent.h"

#include "dietSlider.h"

DietComponent::DietComponent(){
	for(int i = 0; i < 3; i++){
		PT(PGSliderBar) control = new DietSlider("slider_"+i, this, i);
		control->set_range(0, total_points);
		control->setup_slider(false, 0.5, 0.05, 0.0f);
		control->set_value(0);
		control->set_page_size(1.0);

		components[i] = control;
	}
}

float DietComponent::get_used_points(){
	return components[0]->get_value() + components[1]->get_value() + components[2]->get_value();
}
