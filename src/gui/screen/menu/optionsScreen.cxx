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

OptionsScreen::~OptionsScreen() {
	unload();
}

void OptionsScreen::load(){
	lb_titulo = new TextNode("txt_titulo");
	lb_titulo->set_text("Opções");
	lb_titulo->set_font(manager->get_default_font());
	np_lb_titulo = get_root().attach_new_node(lb_titulo);
	np_lb_titulo.set_scale(0.2);
	np_lb_titulo.set_x(-lb_titulo->get_width()*np_lb_titulo.get_sx()*0.5);
	np_lb_titulo.set_z(0.7);
	np_lb_titulo.set_color(0.87, 0.72, 0.52);

	//default_button_config(btn_video, np_btn_video, "Vídeo", LVecBase3f(0, 0, 0.1), video_action);
	//default_button_config(btn_audio, np_btn_audio, "Áudio", LVecBase3f(0, 0, -0.1), audio_action);
	default_button_config(btn_audio, np_btn_audio, "Áudio", LVecBase3f(0, 0, 0.1), audio_action);
	//default_button_config(btn_controles, np_btn_controles, "Controles", LVecBase3f(0, 0, -0.3), controles_action);
	//default_button_config(btn_jogo, np_btn_jogo, "Jogo", LVecBase3f(0, 0, -0.5), jogo_action);
	default_button_config(btn_jogo, np_btn_jogo, "Jogo", LVecBase3f(0, 0, -0.1), jogo_action);
	configure_default_back_button(((CalangosMenuManager*) manager.p())->get_main_menu());
}

void OptionsScreen::unload() {
	np_lb_titulo.remove_node();
	np_btn_audio.remove_node();
	//np_btn_controles.remove_node();
	np_btn_jogo.remove_node();
	//np_btn_video.remove_node();
	np_btn_back.remove_node();
	lb_titulo = NULL;
	btn_audio = NULL;
	//btn_controles = NULL;
	btn_jogo = NULL;
	//btn_video = NULL;
	btn_back = NULL;
}

void OptionsScreen::video_action(){
	nout << "Tela de video..." << endl;
	//manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());
}

void OptionsScreen::audio_action(){
	nout << "Tela de audio..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_audio_options_screen());
}

void OptionsScreen::controles_action(){
	nout << "Tela de controles..." << endl;
	//manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_credits_screen());
}

void OptionsScreen::jogo_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_game_options_screen());
}
