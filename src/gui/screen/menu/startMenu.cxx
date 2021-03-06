/*
 *  startMenu.cxx
 *  Created on: 21/02/2011
 *  Author: heekinho
 */

#include "startMenu.h"
#include "fontPool.h"

#include "mouseButton.h"
#include "textNode.h"
#include "nodePath.h"
#include "simdunas.h"
#include "calangosMenuManager.h"



/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
StartMenu::StartMenu(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

StartMenu::~StartMenu() {
}

/*! Carrega o menu principal */
void StartMenu::load(){
	window->set_background_type(WindowFramework::BT_black);

	//carregando animação inicial da Tela principal
	np_lagarto = window->load_model(render, "models/lizards/cnemidophorus/male/model");
	np_lagarto.set_scale(0.08, 0.08, 0.08);
	np_lagarto.set_pos(0, 35, -2);
	np_lagarto.set_h(45);
	np_lagarto.set_p(20);

	// Animação
	window->load_model(np_lagarto, "models/lizards/cnemidophorus/male/walk");
	auto_bind(np_lagarto.node(), anims, PartGroup::HMF_ok_part_extra |
			PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
	anims.loop_all(false);

    ///imagem do logo
    np_logo = window->load_model(get_root(), "models/calangos.png");
    np_logo.set_scale(0.1);
    np_logo.set_pos(0.0, 0, 0.6);



    //textos das opções do menu inicial
	default_button_config(btn_play, np_play, ConfigVariableString("msg-jogar", "Jogar"), LVecBase3f(0, 0, 0.1), play_action);
	default_button_config(btn_options, np_options, ConfigVariableString("msg-config", "Configurações"), LVecBase3f(0, 0, -0.1), options_action);
	default_button_config(btn_instructions, np_instructions, ConfigVariableString("msg-inst", "Instruções"), LVecBase3f(0, 0, -0.3), instructions_action);
	default_button_config(btn_language, np_language, ConfigVariableString("msg-idioma", "Idioma"), LVecBase3f(0, 0, -0.5), language_action);
	default_button_config(btn_credits, np_credits, ConfigVariableString("msg-cred", "Créditos"), LVecBase3f(0, 0, -0.7), credits_action);
	default_button_config(btn_exit, np_exit, ConfigVariableString("msg-sair", "Sair"), LVecBase3f(0, 0, -0.9), exit_action);







}

void StartMenu::show() {
	Screen::show();
	np_lagarto.unstash();
}

void StartMenu::hide() {
	Screen::hide();
	np_lagarto.stash();
}

/*! Ação do botão jogar */
void StartMenu::play_action(){
	simdunas_cat.debug() << "Carregando Jogo..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_level_selection_screen());
	//Simdunas::set_play_clicked(true);
}

/*! Carrega menu de opções */
void StartMenu::options_action(){
	simdunas_cat.debug() << "Carregando Opções..." << endl;
	//manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_options_screen());
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_game_options_screen());
}

/*! Carrega menu de instruções */
void StartMenu::instructions_action(){
	simdunas_cat.debug() << "Carregando Instruções..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_instructions_screen());
}
/*! Carrega o menu de idiomas novamente  */
void StartMenu::language_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_language_menu());
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
