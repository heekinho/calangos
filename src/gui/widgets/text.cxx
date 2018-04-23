/*
 *  text.cxx
 *  Created on: Sep 06, 2012
 *  Author: Jônatas
 */

#include "text.h"
#include "mouseButton.h"

Text::Text(const string &name, const string &text, NodePath parent, PT(TextFont) font, float scale) : PGButton(name){
	/* Configura o texto */
	tnode = new TextNode("Text");
	tnode->set_font(font);
	tnode->set_encoding(TextNode::E_utf8);
	tnode->set_text(text);
	tnode->set_align(TextNode::A_left);

	/* Configura os diferentes tipos de estados do botão */
	np_lb_normal = NodePath(tnode);
	np_lb_normal.set_scale(scale);
	np_lb_normal.set_color_scale(0, 0, 0, 1.0);

	np_lb_hover = np_lb_normal.copy_to(NodePath());
	np_lb_hover.set_color_scale(0.3, 0.3, 0.3, 1.0);
	np_lb_hover.set_alpha_scale(1, 10);

	/* Gera o comportamento padrão */
	setup(np_lb_normal, np_lb_hover, np_lb_hover);

	np = parent.attach_new_node(this);
}

Text::~Text(){
}

NodePath Text::get_np() {
	return np;
}

void Text::set_pos(float x, float y, float z) {
	np.set_pos(x, y, z);
}

/*! Retorna o TextNode associado ao botão */
PT(TextNode) Text::get_text_node() const {
	return tnode;
}

/*! Define o texto do botão. Delegada para TextNode */
void Text::set_text(const string &text){
//	tnode->set_text(text);
	DCAST(TextNode, np_lb_normal.node())->set_text(text);
	DCAST(TextNode, np_lb_hover.node())->set_text(text);
}

/* Obtém o texto do botão. Delegada para o TextNode */
string Text::get_text() const {
	return tnode->get_text();
}

/*! Obtém a largura o texto */
float Text::get_text_width() const {
	return tnode->get_width();
}
