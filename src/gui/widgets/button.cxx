/*
 *  button.cxx
 *  Created on: 08/02/2011
 *  Author: heekinho
 */

#include "button.h"

Button::Button(const string &name, const string &text, PT(TextFont) font) : PGButton(name){
	/* Configura o texto */
	tnode = new TextNode("buttonText");
	tnode->set_font(font);
	tnode->set_encoding(TextNode::E_utf8);
	tnode->set_text(text);

	/* Adicionando sombra ao texto */
	tnode->set_shadow(0.05, 0.05);
	tnode->set_shadow_color(0, 0, 0, 1);

	/* Configura os diferentes tipos de estados do botão */
	NodePath btn_normal = NodePath(tnode->generate());
	btn_normal.set_scale(0.126);
	btn_normal.set_x(-tnode->get_width()*btn_normal.get_sx()*0.5);
	btn_normal.flatten_light();

	NodePath btn_hover = btn_normal.copy_to(NodePath());
	btn_hover.set_color_scale(0.75, 0.75, 0.75, 1.0);

	NodePath btn_depressed = btn_normal.copy_to(NodePath());
	btn_depressed.set_color_scale(0.5, 0.5, 0.5, 1.0);

	/* Gera o comportamento padrão */
	setup(btn_normal, btn_depressed, btn_hover);
}

Button::~Button(){

}

float Button::get_text_width(){
	return tnode->get_width();
}
