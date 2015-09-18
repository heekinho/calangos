/*
 * languageOptionsScreen.cpp
 *
 *  Created on: 27/07/2015
 *      Author: crystal
 */
#include "languageOptionsScreen.h"
#include "fontPool.h"
#include "load_prc_file.h"

#include "mouseButton.h"
#include "textNode.h"
#include "nodePath.h"
#include "simdunas.h"
#include "calangosMenuManager.h"

int esco = 0;

LanguageOptionsScreen::LanguageOptionsScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

LanguageOptionsScreen::~LanguageOptionsScreen() {

}

void LanguageOptionsScreen::load(){
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

    //botões de escolha da linguagem e mudança para o menu principal  by:Crystal
    default_button_config(btn_portugues, np_portugues, "portugues", LVecBase3f(0, 0, 0.1), portugues_action);
    default_button_config(btn_ingles, np_ingles, "english", LVecBase3f(0, 0, -0.1), ingles_action);
    default_button_config(btn_espanhol, np_espanhol, "español", LVecBase3f(0, 0, -0.3), espanhol_action);
}
void LanguageOptionsScreen::show(){
	Screen::show();
	np_lagarto.unstash();

}
void LanguageOptionsScreen::hide(){
	Screen::hide();
	np_lagarto.stash();

}

void LanguageOptionsScreen::portugues_action(){
	simdunas_cat.debug() << "Carregando Menu..." << endl;
	if(load_prc_file("config/language-portugues.prc") != NULL){
			cout << "Carregando Lingua..." << endl;

	}
	else
			cout << "Arquivo nao carregado..." << endl;
	esco = 1;
	manager->create_menus();
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_main_menu());

}
void LanguageOptionsScreen::ingles_action(){
	simdunas_cat.debug() << "Carregando Menu..." << endl;
	if(load_prc_file("config/language-english.prc") != NULL){
		cout << "Carregando Lingua..." << endl;

	}
	else
		cout << "Arquivo nao carregado..." << endl;
	esco = 1;
	manager->create_menus();
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_main_menu());

}
void LanguageOptionsScreen::espanhol_action(){
	simdunas_cat.debug() << "Carregando Menu..." << endl;
	if(load_prc_file("config/language-espanol.prc") != NULL){
		cout << "Carregando Lingua..." << endl;

	}
	else
		cout << "Arquivo nao carregado..." << endl;
	esco = 1;
	manager->create_menus();
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_main_menu());

}

