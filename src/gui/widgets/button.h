/*
 *  button.h
 *  Created on: 08/02/2011
 *  Author: heekinho
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "pgButton.h"
#include "textFont.h"

class Button : public PGButton {
public:
	Button(const string &name, const string &text, PT(TextFont) font);
	~Button();

	float get_text_width();
private:
	PT(TextNode) tnode;
};

#endif
