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
#include "achievementsWindow.h"
#include "videosWindow.h"
#include "guiManager.h"
#include "keyInstructionsWindow.h"

bool PauseScreen::selected_video = false;
bool PauseScreen::is_opened = false;

/*! A screen é carregada e escondida. O manager é responsável por escolher a screen */
PauseScreen::PauseScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

PauseScreen::~PauseScreen() {
}

void PauseScreen::load(){
	stopped_time = false;
//	titulo = window->load_model(get_root(), "models/buttons/pausa.png");
//	titulo.set_scale(0.06);
//	titulo.set_pos(0.0, 0, 0.8);

	lb_jogo_pausado = new TextNode("lb_jogo_pausado");
	lb_jogo_pausado->set_font(Simdunas::get_game_font());
	lb_jogo_pausado->set_text(ConfigVariableString("msg-pauselabel","Jogo Pausado!"));
	lb_jogo_pausado->set_align(TextNode::A_boxed_center);
	lb_jogo_pausado->set_shadow(0.05, 0.05);
	lb_jogo_pausado->set_shadow_color(0, 0, 0, 1);
	np_lb_jogo_pausado = get_root().attach_new_node(lb_jogo_pausado);
	np_lb_jogo_pausado.set_scale(0.2);
	np_lb_jogo_pausado.set_pos(0.0, 0, 0.7);

	/////////colocando nome videos
//	img_videos = window->load_model(get_root(), "models/buttons/videos.png");
//	img_videos.set_scale(0.025);
//	img_videos.set_pos(0.0, 0, 0.55);

	default_button_config(btn_realizacoes, np_btn_realizacoes, ConfigVariableString("msg-realiza","Realizações"), LVecBase3f(0, 0, 0.15), realizacoes_action);
	default_button_config(btn_videos, np_btn_videos, ConfigVariableString("msg-videos","Vídeos"), LVecBase3f(0, 0, -0.05), videos_action);

	default_button_config(btn_controles, np_btn_controles, ConfigVariableString("msg-controles","Controles"), LVecBase3f(0, 0, -0.25), controles_action);
	//default_button_config(btn_indicadores, np_btn_indicadores, "Indicadores", LVecBase3f(0, 0, -0.45), indicadores_action);

	//////construindo os botões dos videos
//	default_button_config(btn_lagartos, np_btn_lagartos, "Lagartos", LVecBase3f(0, 0, 0.35), lagartos_action);
//	default_button_config(btn_predadores, np_btn_predadores, "Predadores", LVecBase3f(0, 0, 0.15), predadores_action);
//	default_button_config(btn_presas, np_btn_presas, "Presas", LVecBase3f(0, 0, -0.05), presas_action);
//	default_button_config(btn_clima, np_btn_clima, "Clima", LVecBase3f(0, 0, -0.25), clima_action);
//	default_button_config(btn_habitat, np_btn_habitat, "Habitat", LVecBase3f(0, 0, -0.45), habitat_action);
	///////////////////////////////////////fim dos botões de vídeos

	default_button_config(btn_continuar, np_btn_continuar, ConfigVariableString("msg-continue","Continuar"), LVecBase3f(-0.55, 0, -0.9), continuar_action);
	default_button_config(btn_sair, np_btn_sair, ConfigVariableString("msg-sair","Sair"), LVecBase3f(0.4, 0, -0.9), sair_action);
}

/*! Controla o evento de pause, tanto para pausar quanto para despausar. */
void PauseScreen::pause_event() {
	if (stopped_time) {
		TimeControl::get_instance()->set_stop_time(false); //se o jogo estiver pausado, ao pressionar esc novamente volta ao normal
		stopped_time = false; // o tempo do jogo foi despausado
		hide(); // esconde a tela de pause
		is_opened = false; // a tela de pause já não está mais aberta
	} else {
		// o tempo não estava parado
		Session::get_instance()->stop_animations();
		if (!TimeControl::get_instance()->get_stop_time()) {//se o tempo ja estiver parado ele naum pausa o jogo
			//load();
			// mostrando tela de pause novamente
			Screen::show();
			TimeControl::get_instance()->set_stop_time(true);
			stopped_time = true;
		}

		is_opened = true; // a tela de pause está aberta
	}
}

/*! Método chamado pela classe Session quando o botão ESC é pressionado */
void PauseScreen::show() {
	/*
	 * Verifica se a janela de realizações estava aberta e se não foi selecionado vídeo algum, para poder chamar
	 * o destrutor dela. Essa verificação é feita pois, caso a pessoa tenha aberto a janela de realizações e depois
	 * tenha apertado ESC, quando ele apertar ESC novamente o que deve aparecer é apenas a tela inicial de pause.
	 * Caso o jogador tenha selecionado um vídeo com a janela de realizações aberta, então quando ele apertar ESC
	 * o vídeo será fechado, não vai entrar nesse if e, portanto, voltará para a tela de pause com a janela de
	 * realizações ainda aberta.
	 */
	if (wnd_realizacoes != NULL && !selected_video)
		wnd_realizacoes = NULL;

	// verificação feita pelo mesmo motivo explicado acima.
	if (wnd_videos != NULL && !selected_video)
		wnd_videos = NULL;

//	if(wnd_controles != NULL && !selected_video) {
//		wnd_controles = NULL;
//	}

	pause_event();

	if (selected_video) {
		selected_video = false;
		pause_event();
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

/*! Evento de click no botão "Realizações". Abre a janela de realizações. */
void PauseScreen::realizacoes_action() {
	wnd_realizacoes = new AchievementsWindow(get_root(), 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
	wnd_realizacoes->set_pos_y(0);
}

/*! Evento de click no botão "Videos". Abre a janela de vídeos. */
void PauseScreen::videos_action() {
	wnd_videos = new VideosWindow(get_root(), manager, 2, 1.3, ConfigVariableString("msg-videos","Vídeos"), -1, -0.8);
}

/*! Evento de click no botão "Continuar". Despausa o jogo e fecha a tela de pause. */
void PauseScreen::continuar_action() {
	pause_event();
}

/*! Evento de click no botão "Sair". Fecha o jogo. */
void PauseScreen::sair_action() {
	//	Session::get_instance()->end_session();

	exit(0); //saindo direto, fechando o jogo
	//na tela de inicialização ou de game over
}

void PauseScreen::controles_action() {
	wnd_controles = new KeyInstructionsWindow(get_root(), 2, 1.3, ConfigVariableString("msg-controles","Controles"), -1, -0.8);
//	img_teclas = window->load_model(get_root(), "models/gui/teclas.png");
//	img_teclas.set_scale(0.075, 0.001, 0.17);
//	img_teclas.set_pos(0.0, 0.0, 0.0);
}

//void PauseScreen::indicadores_action() {
//}

