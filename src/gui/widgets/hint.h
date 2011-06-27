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
	~Hint();

	static void enter_event(const Event*, void *data);
	static void show_hint(const Event*, void *data);
	static void exit_event(const Event*, void *data);


private:
	PT(PGButton) btn; // serve para mapear a área do reference_node e capturar os eventos do mouse
	NodePath np_btn;
	PT(TextNode) text;
	NodePath np_text;
	float width;
	float height;

};

#endif /* HINT_H */
