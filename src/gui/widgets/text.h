/*
 *  text.cxx
 *  Created on: Sep 06, 2012
 *  Author: Jônatas
 */

#ifndef TEXT_H
#define TEXT_H

#include "simdunas.h"
#include "pgButton.h"
#include "textFont.h"
#include "genericAsyncTask.h"

class Text : public PGButton {
public:
	Text(const string &name, const string &text, NodePath parent, PT(TextFont) font = TextNode::get_default_font(), float scale = 0.126);
	~Text();

	PT(TextNode) get_text_node() const;

	/* Ações por conveniencia. Delegadas para o TextNode */
	void set_text(const string &text);
	string get_text() const;
	float get_text_width() const;
	void set_pos(float x, float y, float z);
	NodePath get_np();

private:
	PT(TextNode) tnode;

	NodePath np;
	NodePath np_lb_normal;
	NodePath np_lb_hover;
};

#endif
