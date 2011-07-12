/*
 *  toggleButton.h
 *  Created on: 11/07/2011
 *  Author: heekinho
 */

#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include "button.h"

/*TODO: Herança de Button cairia bem...? */
class ToggleButton : public ReferenceCount {
public:
	ToggleButton(const string &name, const string &text_on, const string &text_off, bool state,
			const NodePath &parent, float valign, PT(TextFont) font, float text_size);

	~ToggleButton();

	void set_state(bool state);
	bool get_state() const;
	static void toggle(const Event*, void* data);

//private:
	PT(Button) _button;
	NodePath _np_button;

	string _text_on;
	string _text_off;

	bool _state;
};


#endif /* TOGGLEBUTTON_H */
