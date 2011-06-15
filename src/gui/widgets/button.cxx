/*
 *  button.cxx
 *  Created on: 08/02/2011
 *  Author: heekinho
 */

#include "button.h"
#include "simdunas.h"
#include "audioRepository.h"
#include "audioController.h"
#include "mouseButton.h"
#include "timeControl.h"

bool Button::play_button = true;

Button::Button(const string &name, const string &text, PT(TextFont) font, float scale) : PGButton(name){
	build(name, text, font, scale);
}

void Button::build(const string &name, const string &text, PT(TextFont) font, float scale) {
	/* Configura o texto */
	tnode = new TextNode("buttonText");
	tnode->set_font(font);
	tnode->set_encoding(TextNode::E_utf8);
	tnode->set_text(text);
	tnode->set_align(TextNode::A_boxed_center);

	/* Adicionando sombra ao texto */
	tnode->set_shadow(0.05, 0.05);
	tnode->set_shadow_color(0, 0, 0, 1);

	/* Configura os diferentes tipos de estados do botão */
	NodePath btn_normal = NodePath(tnode->generate());
	btn_normal.set_scale(scale);
	btn_normal.set_x(-tnode->get_width()*btn_normal.get_sx()*0.5);
	btn_normal.flatten_light();

	NodePath btn_hover = btn_normal.copy_to(NodePath());
	btn_hover.set_color_scale(0.75, 0.75, 0.75, 1.0);
	btn_hover.set_alpha_scale(1, 10);

	NodePath btn_depressed = btn_normal.copy_to(NodePath());
	btn_depressed.set_color_scale(0.5, 0.5, 0.5, 1.0);
	btn_depressed.set_alpha_scale(1, 10);

	/* Gera o comportamento padrão */
	setup(btn_normal, btn_depressed, btn_hover);

	Simdunas::get_evt_handler()->add_hook(this->get_enter_event(), enter_event, this);
	Simdunas::get_evt_handler()->add_hook(this->get_click_event(MouseButton::one()), click_event, this);
}


Button::~Button(){

}

float Button::get_text_width(){
	return tnode->get_width();
}

void Button::enter_event(const Event*, void *data) {
	if(Button::play_button) AudioController::get_instance()->only_play(AudioRepository::MOUSE_ON);
}

void Button::click_event(const Event*, void *data) {
	AudioController::get_instance()->only_play(AudioRepository::MOUSE_CLICK);
}


/*! Reativa sons do botão depois de transição da tela */
AsyncTask::DoneStatus Button::reactivate_button_sounds(GenericAsyncTask* task, void* data){
	Button::play_button = true;
    return AsyncTask::DS_done;
}
