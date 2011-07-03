/*
 * hint.h
 *
 *  Created on: Nov 26, 2010
 *      Author: jonatas
 */

#ifndef HINT_H
#define HINT_H

#include "pandaFramework.h"
#include "pgButton.h"

class Hint : public ReferenceCount {

public:
	Hint(NodePath parent, NodePath reference_node, string name, string msg);
	Hint(NodePath parent, PGButton* hintable_btn, NodePath reference_node, string name, string msg);
	~Hint();

	void buildHint(string msg);
	static void enter_event(const Event*, void *data);
	static AsyncTask::DoneStatus show_hint(GenericAsyncTask* task, void* data);
	static void exit_event(const Event*, void *data);


private:
	PT(PGButton) btn; // serve para mapear a área do reference_node e capturar os eventos do mouse
	NodePath np_btn;
	PT(TextNode) text;
	NodePath np_text;
	NodePath np_reference;
	float width;
	float height;
	bool mouse_in;

};

#endif /* HINT_H */
