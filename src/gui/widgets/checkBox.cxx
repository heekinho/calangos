/*
 *  checkBox.cxx
 *  Created on: 22/04/2011
 *  Author: heekinho
 */

#include "checkBox.h"

#include "eventHandler.h"
#include "mouseButton.h"
#include "fontPool.h"

CheckBox::CheckBox(bool checked) : Button("checkbox", ""){
	set_checked(checked);

	/* Configura o evento de mouse para mudar de estado */
	EventHandler::get_global_event_handler()->add_hook(get_click_event(MouseButton::one()), toogle, this);
}

/*! Recebe o evento de mudança de estado */
void CheckBox::toogle(const Event*, void* data){
	((CheckBox*)data)->toogle();
}

/*! Muda o estado do checkbox */
bool CheckBox::toogle(){
	set_checked(!is_checked());
	return is_checked();
}

/*! Define o estado do checkbox */
void CheckBox::set_checked(bool checked){
	_checked = checked;
	setup((_checked ? "Sim" : "Não"), 0);
}

/*! Retorna o estado do checkbox */
bool CheckBox::is_checked() const {
	return _checked;
}

