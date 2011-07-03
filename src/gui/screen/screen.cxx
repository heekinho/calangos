/*
 *  screen.cxx
 *  Created on: 19/02/2011
 *  Author: heekinho
 */

#include "screen.h"
#include "screenManager.h"

#include "simdunas.h"

/*! Classe que representa uma tela no jogo.
 *  Geralmente Menus, esta classe deve usar o *mediator* ScreenManager passado
 *  no construtor como forma de se comunicar com outras telas, transferindo a
 *  responsabilidade de carregar/descarregar/localizar telas para tal. */
Screen::Screen(PT(ScreenManager) manager){
	this->manager = manager;
	root = aspect2d.attach_new_node("Menu Screen");
	np_btn_back = NodePath("No Back Button Yet");
}

/*! Efetua alguma limpeza necessária */
Screen::~Screen(){
	nout << "Destruindo Screen" << endl;
}


/*! Nó raiz onde os itens são adicionados para aparecer. As manipulações de
 *	esconder/mostrar e relacionadas são feitas nesse nó. */
NodePath Screen::get_root(){
	return root;
}

void Screen::set_root(NodePath new_root) {
	root = new_root;
}

#include "button.h"

/*! Mostra o menu */
void Screen::show(){
	Button::play_button = false;
	root.show();
	TimeControl::get_instance()->notify("reactivate button sounds", Button::reactivate_button_sounds, this, 0.05);
}

/*! Esconde o menu */
void Screen::hide(){
	root.hide();
}

/*! Define algumas características básicas do NodePath. Note que ao deixar
 *  alguma opção sem marcar, um valor default será atribuído. Este método é
 *  chamado, na maioria das vezes, assim que um NodePath é criado */
void Screen::configure_component(NodePath &np, const LVecBase3f &size,
		const LPoint3f &pos, const LVecBase3f &hpr, const Colorf &color){
	np.set_scale(size);
	np.set_pos(pos);
	np.set_hpr(hpr);
	np.set_color(color);
}

/*! Configura um botão dado os parametros para este menu */
void Screen::default_button_config(PT(Button) button, NodePath &np,
		const string &text, LVecBase3f pos, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, manager->get_default_font());
	np = get_root().attach_new_node(button);
	np.set_pos(pos);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
}

/*! Obtém a tela anterior (cadastrada manualmente por set_previous_screen) */
PT(Screen) Screen::get_previous_screen(){
	return previous;
}

/*! Define a tela principal para as ações de voltar */
void Screen::set_previous_screen(PT(Screen) previous){
	this->previous = previous;
}

/*! Ação de voltar */
void Screen::back_action(const Event*, void* data){
	((Screen*)data)->manager->open_screen(((Screen*)data)->previous);
}

/*! Configura um botão voltar padrão, sem necessidade de recriar em cada classe
 *  Força a passagem do método para evitar esquecer de setar previous */
void Screen::configure_default_back_button(PT(Screen) previous){
	set_previous_screen(previous);
	default_button_config(btn_back, np_btn_back, "<< Voltar", LVecBase3f(-0.9, 0, -0.9), back_action);
}
