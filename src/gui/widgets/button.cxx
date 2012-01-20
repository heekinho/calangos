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
#include "videoManager.h"

bool Button::play_button = true;

Button::Button(const string &name, const string &text, PT(TextFont) font, float scale) : PGButton(name){
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
	np_btn_normal = NodePath(tnode);
	np_btn_normal.set_scale(scale);
	np_btn_normal.set_x(-tnode->get_width()*np_btn_normal.get_sx()*0.5);
	//np_btn_normal.flatten_light();

	np_btn_hover = np_btn_normal.copy_to(NodePath());
	np_btn_hover.set_color_scale(0.75, 0.75, 0.75, 1.0);
	np_btn_hover.set_alpha_scale(1, 10);

	np_btn_depressed = np_btn_normal.copy_to(NodePath());
	np_btn_depressed.set_color_scale(0.5, 0.5, 0.5, 1.0);
	np_btn_depressed.set_alpha_scale(1, 10);

	/* Gera o comportamento padrão */
	setup(np_btn_normal, np_btn_depressed, np_btn_hover);

	event_handler->add_hook(this->get_enter_event(), enter_event, this);
	event_handler->add_hook(this->get_exit_event(), exit_event, this);
	event_handler->add_hook(this->get_click_event(MouseButton::one()), click_event, this);
}

Button::~Button(){
	PlayerControl::mouse_on_button = false;
}

/*! Retorna o TextNode associado ao botão */
PT(TextNode) Button::get_text_node() const {
	return tnode;
}

/*! Define o texto do botão. Delegada para TextNode */
void Button::set_text(const string &text){
//	tnode->set_text(text);
	DCAST(TextNode, np_btn_normal.node())->set_text(text);
	DCAST(TextNode, np_btn_hover.node())->set_text(text);
	DCAST(TextNode, np_btn_depressed.node())->set_text(text);
}

/* Obtém o texto do botão. Delegada para o TextNode */
string Button::get_text() const {
	return tnode->get_text();
}

/*! Obtém a largura o texto */
float Button::get_text_width() const {
	return tnode->get_width();
}

/*! Evento chamado quando o mouse passa por cima */
void Button::enter_event(const Event*, void *data) {
	PlayerControl::mouse_on_button = true;
	if(Button::play_button) AudioController::get_instance()->only_play(AudioRepository::MOUSE_ON);
}

void Button::exit_event(const Event*, void *data) {
	PlayerControl::mouse_on_button = false;
}

/*! Evento chamado quanto há um click de mouse */
void Button::click_event(const Event*, void *data) {
	if (VideoManager::is_playing()) return;
	AudioController::get_instance()->only_play(AudioRepository::MOUSE_CLICK);
}

/*! Reativa sons do botão depois de transição da tela */
AsyncTask::DoneStatus Button::reactivate_button_sounds(GenericAsyncTask* task, void* data){
	Button::play_button = true;
    return AsyncTask::DS_done;
}
