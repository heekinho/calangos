/*
 *  pauseScreen.cxx
 *  Created on: 02/04/2011
 *  Author: jonatas
 */

#include "pauseScreen.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"
#include "inGameScreenManager.h"
#include "audioController.h"


/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
PauseScreen::PauseScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

PauseScreen::~PauseScreen() {
	unload();
}

void PauseScreen::load(){
	stopped_time = false;
	selected_video = false;
	titulo = window->load_model(get_root(), "models/buttons/pausa.png");
	titulo.set_scale(0.06);
	titulo.set_pos(0.0, 0, 0.8);

	/////////colocando nome videos
	img_videos = window->load_model(get_root(), "models/buttons/videos.png");
	img_videos.set_scale(0.025);
	img_videos.set_pos(0.0, 0, 0.55);

	//////construindo os botões dos videos
	default_button_config(btn_lagartos, np_btn_lagartos, "Lagartos", LVecBase3f(0, 0, 0.35), lagartos_action);
	default_button_config(btn_predadores, np_btn_predadores, "Predadores", LVecBase3f(0, 0, 0.15), predadores_action);
	default_button_config(btn_presas, np_btn_presas, "Presas", LVecBase3f(0, 0, -0.05), presas_action);
	default_button_config(btn_clima, np_btn_clima, "Clima", LVecBase3f(0, 0, -0.25), clima_action);
	default_button_config(btn_habitat, np_btn_habitat, "Habitat", LVecBase3f(0, 0, -0.45), habitat_action);
	///////////////////////////////////////fim dos botões de vídeos

	default_button_config(btn_continuar, np_btn_continuar, "Continuar", LVecBase3f(-0.55, 0, -0.9), continuar_action);
	default_button_config(btn_sair, np_btn_sair, "Sair", LVecBase3f(0.4, 0, -0.9), sair_action);
}

void PauseScreen::pause_event() {
	if (stopped_time) {
		TimeControl::get_instance()->set_stop_time(false); //se o jogo estiver pausado, ao pressionar esc novamente volta ao normal
		stopped_time = false;
		hide();
	} else {
		Session::get_instance()->stop_animations();
		if (!TimeControl::get_instance()->get_stop_time()) {//se o tempo ja estiver parado ele naum pausa o jogo
			load();
			Screen::show();
			TimeControl::get_instance()->set_stop_time(true);
			stopped_time = true;
		}
	}
}

void PauseScreen::unload() {
	stopped_time = false;
	titulo.remove_node();
	img_videos.remove_node();
	np_btn_clima.remove_node();
	np_btn_continuar.remove_node();
	np_btn_habitat.remove_node();
	np_btn_lagartos.remove_node();
	np_btn_predadores.remove_node();
	np_btn_presas.remove_node();
	np_btn_sair.remove_node();
	btn_continuar = NULL;
	btn_sair = NULL;
	btn_habitat = NULL;
	btn_lagartos = NULL;
	btn_predadores = NULL;
	btn_presas = NULL;
	btn_clima = NULL;
}

void PauseScreen::show() {
	pause_event();

	if (selected_video) {
		selected_video = false;
		pause_event(); // como voltou de um vídeo, chama esse evento para pausar o jogo novamente
		GuiManager::get_instance()->show_frameNode();
	}
}

void PauseScreen::hide() {
	Screen::hide();

	// se selecionou um vídeo, precisa esconder a barra de status
	if (selected_video) {
		GuiManager::get_instance()->hide_frameNode();
	}
}

bool PauseScreen::is_stopped_time() {
	return stopped_time;
}

void PauseScreen::lagartos_action() {
	selected_video = true;
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_1_lagartos_mpeg4.avi");
}

void PauseScreen::predadores_action() {
	selected_video = true;
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_2_predadores_mpeg4.avi");
}

void PauseScreen::presas_action() {
	selected_video = true;
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_3_presas_mpeg4.avi");
}

void PauseScreen::clima_action() {
	selected_video = true;
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_5_variacoes_climaticas_mpeg4.avi");
}

void PauseScreen::habitat_action() {
	selected_video = true;
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_4_habitat_mpeg4.avi");
}

void PauseScreen::continuar_action() {
	pause_event();
}

void PauseScreen::sair_action() {
	//	Session::get_instance()->end_session();

	exit(0); //saindo direto, fechando o jogo
	//na tela de inicialização ou de game over
}
