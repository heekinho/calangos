/*
 *  button.h
 *  Created on: 08/02/2011
 *  Author: heekinho
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "pgButton.h"
#include "textFont.h"
#include "genericAsyncTask.h"

class Button : public PGButton {
public:
	Button(const string &name, const string &text, PT(TextFont) font = TextNode::get_default_font(), float scale = 0.126);
	~Button();

	static void enter_event(const Event*, void *data);
	static void click_event(const Event*, void *data);

	static AsyncTask::DoneStatus reactivate_button_sounds(GenericAsyncTask* task, void* data);

	static bool play_button;

	PT(TextNode) get_text_node() const;

	/* Ações por conveniencia. Delegadas para o TextNode */
	void set_text(const string &text);
	string get_text() const;
	float get_text_width() const;

private:
	PT(TextNode) tnode;

	NodePath np_btn_normal;
	NodePath np_btn_hover;
	NodePath np_btn_depressed;
};

#endif
