/*
 * dietSlider.cxx
 * Created on: 05/09/2012
 * Author: heekinho
 */

#include "dietSlider.h"

#include "dietComponent.h"
#include "characterEditor.h"

DietSlider::DietSlider(const string &name, DietComponent* diet, int id) : PGSliderBar(name){
	_id = id;
	_diet = diet;
}

/*! Chamado quando se clica (solta o botão do mouse) na barra */
void DietSlider::release(const MouseWatcherParameter &param, bool background){
	PGSliderBar::release(param, background);
	update_value();
}

/*! Chamado quando se clica (solta o botão do mouse) no botão da barra */
void DietSlider::item_release(PGItem *item, const MouseWatcherParameter &param){
	PGSliderBar::item_release(item, param);
	update_value();
}

/*! Verifica se é possível que este slider assuma o valor que o usuário
 *  colocou. Se não for possível, move para o maior valor possível */
void DietSlider::update_value(){
	int a = _diet->components[(_id + 1) % 3]->get_value();
	int b = _diet->components[(_id + 2) % 3]->get_value();

	int available_points = DietComponent::total_points - (a + b);

	if(get_value() > available_points) set_value(available_points);

	set_value(int(get_value()));
}

