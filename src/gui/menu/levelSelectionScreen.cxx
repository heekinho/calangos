/*
 *  levelSelectionScreen.cxx
 *  Created on: 03/04/2011
 *  Author: heekinho
 */

#include "levelSelectionScreen.h"
#include "calangosMenuManager.h"
#include "simdunas.h"

LevelSelectionScreen::LevelSelectionScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

LevelSelectionScreen::~LevelSelectionScreen(){}

void LevelSelectionScreen::load(){
	PT(TextFont) font = manager->get_default_font();

	default_button_config(btn_level_one, np_btn_level_one, "Fase 1", 0.1, level_one_action);
	default_button_config(btn_level_two, np_btn_level_two, "Fase 2", -0.1, level_two_action);
	default_button_config(btn_back, np_btn_back, "<< Voltar", -0.9, back_action);
	np_btn_back.set_x(-0.9);
}

void LevelSelectionScreen::unload() {

}

/*! Aciona carregamento da fase 1 */
void LevelSelectionScreen::level_one_action(){
	nout << "Carregando Fase 1" << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());
	Simdunas::set_play_clicked(true);
}

void LevelSelectionScreen::level_two_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_character_editor());
}

void LevelSelectionScreen::back_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_main_menu());
}
