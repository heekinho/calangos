/*
 *  toggleButton.cxx
 *  Created on: 11/07/2011
 *  Author: heekinho
 */

#include "toggleButton.h"

#include "simdunas.h"
#include "mouseButton.h"

ToggleButton::ToggleButton(const string &name, const string &text_on, const string &text_off, bool state,
		const NodePath &parent, float valign, PT(TextFont) font, float text_size){
	/* Configurações */
	_state = state;
	_text_on = text_on;
	_text_off = text_off;

	/* Configura o botão */
	_button = new Button(name, _state ? _text_on : _text_off, font, 1.0);
	string mouse_event = _button->get_click_event(MouseButton::one());
	event_handler->add_hook(mouse_event, toggle, this);

	/* Configura o Nodepath do botão */
	_np_button = parent.attach_new_node(_button);
	_np_button.set_scale(0.06);
	_np_button.set_z(valign);
}

ToggleButton::~ToggleButton(){
	_button = NULL;
	_np_button.remove_node();
}

/*! Define o estado do botão e redefine o texto */
void ToggleButton::set_state(bool state){
	_state = state;
	_button->set_text(_state ? _text_on : _text_off);
}

/*! Retorna o estado atual */
bool ToggleButton::get_state() const {
	return _state;
}

/*! Alterna o estado do botão através de eventos */
void ToggleButton::toggle(const Event*, void* data){
	ToggleButton* button = (ToggleButton*) data;
	button->set_state(!button->_state);
}
