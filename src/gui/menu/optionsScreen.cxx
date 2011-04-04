/*
 *  optionsScreen.cxx
 *  Created on: 05/03/2011
 *  Author: jonatas
 */

#include "optionsScreen.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"
#include "calangosMenuManager.h"

/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
OptionsScreen::OptionsScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

OptionsScreen::~OptionsScreen(){}

void OptionsScreen::load(){
	PT(TextFont) font = manager->get_default_font();

	default_button_config(btn_video, np_btn_video, "Vídeo", 0.1, video_action);
	default_button_config(btn_audio, np_btn_audio, "Áudio", -0.1, audio_action);
	default_button_config(btn_controles, np_btn_controles, "Controles", -0.3, controles_action);
	default_button_config(btn_jogo, np_btn_jogo, "Jogo", -0.5, jogo_action);
	default_button_config(btn_voltar, np_btn_voltar, "<< Voltar", -0.9, voltar_action);
	np_btn_voltar.set_x(-0.9);
}

void OptionsScreen::unload() {
	np_btn_audio.remove_node();
	np_btn_controles.remove_node();
	np_btn_jogo.remove_node();
	np_btn_video.remove_node();
	np_btn_voltar.remove_node();
	btn_audio = NULL;
	btn_controles = NULL;
	btn_jogo = NULL;
	btn_video = NULL;
	btn_voltar = NULL;
}

void OptionsScreen::show() {
	np_btn_video.show();
	np_btn_audio.show();
	np_btn_controles.show();
	np_btn_jogo.show();
	np_btn_voltar.show();
}

void OptionsScreen::hide() {
	np_btn_video.hide();
	np_btn_audio.hide();
	np_btn_controles.hide();
	np_btn_jogo.hide();
	np_btn_voltar.hide();
}

void OptionsScreen::video_action(){
	nout << "Tela de video..." << endl;
	//manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());
}

void OptionsScreen::audio_action(){
	nout << "Tela de audio..." << endl;
}

void OptionsScreen::controles_action(){
	nout << "Tela de controles..." << endl;
	//manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_credits_screen());
}

void OptionsScreen::jogo_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_game_options_screen());
}

void OptionsScreen::voltar_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_main_menu());
}
