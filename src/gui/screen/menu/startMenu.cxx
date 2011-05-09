/*
 *  startMenu.cxx
 *  Created on: 21/02/2011
 *  Author: heekinho
 */

#include "startMenu.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"
#include "menu.h"
#include "calangosMenuManager.h"

/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
StartMenu::StartMenu(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

StartMenu::~StartMenu(){}

/*! Carrega o menu principal */
void StartMenu::load(){
	Simdunas::get_window()->set_background_type(WindowFramework::BT_black);

	//carregando animação inicial da Tela principal
	np_lagarto = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/cnemidophorus/male/model");
	np_lagarto.set_scale(0.08, 0.08, 0.08);
	np_lagarto.set_pos(0, 35, -2);
	np_lagarto.set_h(45);
	np_lagarto.set_p(20);

	// Animação
	Simdunas::get_window()->load_model(np_lagarto, "models/lizards/cnemidophorus/male/walk");
	auto_bind(np_lagarto.node(), anims, PartGroup::HMF_ok_part_extra |
			PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
	anims.loop_all(false);

    ///imagem do logo
    np_logo = Simdunas::get_window()->load_model(get_root(), "models/calangos.png");
    np_logo.set_scale(0.1);
    np_logo.set_pos(0.0, 0, 0.6);

	default_button_config(btn_play, np_play, "Jogar", LVecBase3f(0, 0, 0.1), play_action);
	default_button_config(btn_options, np_options, "Opções", LVecBase3f(0, 0, -0.1), options_action);
	default_button_config(btn_instructions, np_instructions, "Instruções", LVecBase3f(0, 0, -0.3), instructions_action);
	default_button_config(btn_credits, np_credits, "Créditos", LVecBase3f(0, 0, -0.5), credits_action);
	default_button_config(btn_exit, np_exit, "Sair", LVecBase3f(0, 0, -0.7), exit_action);
}

void StartMenu::show() {
	Screen::show();
	np_lagarto.show();
}

void StartMenu::hide() {
	Screen::hide();
	np_lagarto.hide();
}

/*! Ação do botão jogar */
void StartMenu::play_action(){
	nout << "Carregando Jogo..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_level_selection_screen());
	//Simdunas::set_play_clicked(true);
}

/*! Carrega menu de opções */
void StartMenu::options_action(){
	nout << "Carregando Opções..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_options_screen());
}

/*! Carrega menu de instruções */
void StartMenu::instructions_action(){
	nout << "Carregando Instruções..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_instructions_screen());
}

/*! Carraga menu de créditos */
void StartMenu::credits_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_credits_screen());
}

/*! Realiza ação de fechamento do jogo */
void StartMenu::exit_action(){
	exit(0);
}

NodePath StartMenu::get_np_options() {
	return np_options;
}

NodePath StartMenu::get_np_play() {
	return np_play;
}
