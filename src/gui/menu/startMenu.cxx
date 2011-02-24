/*
 *  startMenu.cxx
 *  Created on: 21/02/2011
 *  Author: heekinho
 */

#include "startMenu.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"

/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
StartMenu::StartMenu(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

StartMenu::~StartMenu(){}

/*! Carrega o menu principal */
void StartMenu::load(){
	PT(TextFont) font = manager->get_default_font();

	default_button_config(btn_play, np_play, "Jogar", 0.1, play_action);
	default_button_config(btn_options, np_options, "Opções", -0.1, options_action);
	default_button_config(btn_credits, np_credits, "Créditos", -0.3, credits_action);
	default_button_config(btn_exit, np_exit, "Sair", -0.5, exit_action);
}

/*! Configura um botão dado os parametros para este menu principal */
void StartMenu::default_button_config(PT(Button) button, NodePath &np,
		const string &text, float z, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, manager->get_default_font());
	np = get_root().attach_new_node(button);
	np.set_z(z);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
}


/*! Ação do botão jogar */
void StartMenu::play_action(){
	nout << "Carregando Jogo..." << endl;
}

/*! Carrega menu de opções */
void StartMenu::options_action(){
	nout << "Carregando Opções..." << endl;
}

/*! Carraga menu de créditos */
void StartMenu::credits_action(){
	nout << "Mostrando Créditos..." << endl;
}

/*! Realiza ação de fechamento do jogo */
void StartMenu::exit_action(){
	exit(0);
}
