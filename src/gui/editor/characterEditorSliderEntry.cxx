/*
 *  characterEditorSliderEntry.cxx
 *  Created on: 17/06/2011
 *  Author: heekinho
 */

#include "characterEditorSliderEntry.h"

CharacterEditorEntrySlider::CharacterEditorEntrySlider(const NodePath &parent, const string &name){
	this->parent = parent.attach_new_node(name);
}

void CharacterEditorEntrySlider::setup_label(const string &text, PT(TextNode) text_generator, float align){
	text_generator->set_text(text);
	np_label = parent.attach_new_node(text_generator->generate());
	np_label.set_scale(0.06);
	np_label.set_x(align);
}

void CharacterEditorEntrySlider::setup_control(float min, float max, float default_value){
	control = new PGSliderBar("slider");
	control->set_range(min, max);
	control->setup_slider(false, 0.5, 0.05, 0.0f);
	control->set_value(default_value);

	np_control = parent.attach_new_node(control);
	np_control.set_x(0.3);
	np_control.set_z(np_control.get_z() + 0.025);

	event_handler->add_hook(control->get_adjust_event(), adjust_value, this);
	adjust_value();
}

void CharacterEditorEntrySlider::setup_value(const string &unit, PT(TextNode) text_generator){
	/* Configurando campo de valor */
	value_postfix = unit;

	value = new TextNode("value");
	value->set_font(text_generator->get_font());

	np_value = parent.attach_new_node(value);
	np_value.set_scale(0.06);
	np_value.set_x(-0.4);
}
