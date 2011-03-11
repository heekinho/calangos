/*
 *  instructionsScreen.cxx
 *  Created on: 05/03/2011
 *  Author: jonatas
 */

#include "instructionsScreen.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"
#include "calangosMenuManager.h"

/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
InstructionsScreen::InstructionsScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

InstructionsScreen::~InstructionsScreen(){}

void InstructionsScreen::load(){
	PT(TextFont) font = manager->get_default_font();

	default_button_config(btn_controles, np_btn_controles, "Controles", 0.1, controles_action);
	default_button_config(btn_indicadores, np_btn_indicadores, "Indicadores", -0.1, indicadores_action);
	default_button_config(btn_voltar, np_btn_voltar, "<< Voltar", -0.9, voltar_action);
	np_btn_voltar.set_x(-0.9);
}

void InstructionsScreen::unload() {
	np_btn_controles.remove_node();
	np_btn_indicadores.remove_node();
	np_btn_voltar.remove_node();
	btn_controles = NULL;
	btn_indicadores = NULL;
	btn_voltar = NULL;
}

/*! Configura um botão dado os parametros para este menu */
void InstructionsScreen::default_button_config(PT(Button) button, NodePath &np,
		const string &text, float z, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, manager->get_default_font());
	np = get_root().attach_new_node(button);
	np.set_z(z);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
}

void InstructionsScreen::show() {
	np_btn_controles.show();
	np_btn_indicadores.show();
	np_btn_voltar.show();
}

void InstructionsScreen::hide() {
	np_btn_controles.hide();
	np_btn_indicadores.hide();
	np_btn_voltar.hide();
}

void InstructionsScreen::controles_action(){
	nout << "Tela de intruções de controles..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_key_instructions_screen());
}

void InstructionsScreen::indicadores_action(){
	nout << "Tela de instruções sobre os indicadores..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_indicators_screen());
}

void InstructionsScreen::voltar_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_main_menu());
}
