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
	Button(const string &name, const string &text, PT(TextFont) font, float scale = 0.126);
	~Button();

	float get_text_width();
private:
	void build(const string &name, const string &text, PT(TextFont) font, float scale);

	PT(TextNode) tnode;
};

#endif
