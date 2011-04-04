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
	lb_titulo = new TextNode("txt_titulo");
	lb_titulo->set_text("Instruções");
	lb_titulo->set_font(manager->get_default_font());
	np_lb_titulo = get_root().attach_new_node(lb_titulo);
	np_lb_titulo.set_scale(0.2);
	np_lb_titulo.set_x(-lb_titulo->get_width()*np_lb_titulo.get_sx()*0.5);
	np_lb_titulo.set_z(0.7);
	np_lb_titulo.set_color(0.87, 0.72, 0.52);

	default_button_config(btn_controles, np_btn_controles, "Controles", 0.1, controles_action);
	default_button_config(btn_indicadores, np_btn_indicadores, "Indicadores", -0.1, indicadores_action);
	default_button_config(btn_voltar, np_btn_voltar, "<< Voltar", -0.9, voltar_action);
	np_btn_voltar.set_x(-0.9);
}

void InstructionsScreen::unload() {
	np_lb_titulo.remove_node();
	np_btn_controles.remove_node();
	np_btn_indicadores.remove_node();
	np_btn_voltar.remove_node();
	lb_titulo = NULL;
	btn_controles = NULL;
	btn_indicadores = NULL;
	btn_voltar = NULL;
}

void InstructionsScreen::show() {
	np_lb_titulo.show();
	np_btn_controles.show();
	np_btn_indicadores.show();
	np_btn_voltar.show();
}

void InstructionsScreen::hide() {
	np_lb_titulo.hide();
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
