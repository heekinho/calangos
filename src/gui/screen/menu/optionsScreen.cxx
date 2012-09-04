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

/*! Evento de click no botão "Video". Abre a tela de configurações de vídeo. */
void OptionsScreen::video_action(){
	simdunas_cat.debug() << "Tela de video..." << endl;
	// ainda não implementada
}

/*! Evento de click no botão "Audio". Abre a tela de configurações de áudio. */
void OptionsScreen::audio_action(){
	simdunas_cat.debug() << "Tela de audio..." << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_audio_options_screen());
}

/*! Evento de click no botão "Controles". Abre a tela de configuração de controles */
void OptionsScreen::controles_action(){
	simdunas_cat.debug() << "Tela de controles..." << endl;
	// ainda não implementada
}

void OptionsScreen::jogo_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_game_options_screen());
}
