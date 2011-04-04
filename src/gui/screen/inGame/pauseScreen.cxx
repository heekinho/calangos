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


/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
PauseScreen::PauseScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

PauseScreen::~PauseScreen(){}

void PauseScreen::load(){
	stopped_time = false;
	titulo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/pausa.png");
	titulo.set_scale(0.06);
	titulo.set_pos(0.0, 0, 0.8);

	/////////colocando nome videos
	img_videos = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/videos.png");
	img_videos.set_scale(0.025);
	img_videos.set_pos(0.0, 0, 0.55);

	//////construindo os botões dos videos
	default_button_config(btn_lagartos, np_btn_lagartos, "Lagartos", 0.35, lagartos_action);
	default_button_config(btn_predadores, np_btn_predadores, "Predadores", 0.15, predadores_action);
	default_button_config(btn_presas, np_btn_presas, "Presas", -0.05, presas_action);
	default_button_config(btn_clima, np_btn_clima, "Clima", -0.25, clima_action);
	default_button_config(btn_habitat, np_btn_habitat, "Habitat", -0.45, habitat_action);
	///////////////////////////////////////fim dos botões de vídeos

	button_config(btn_continuar, np_btn_continuar, "Continuar", -0.55, -0.9, continuar_action);
	button_config(btn_sair, np_btn_sair, "Sair", 0.4, -0.9, sair_action);

	//			////adicionando os eventos na fila
	//			Simdunas::get_evt_handler()->add_hook(botao_voltar_jogo->get_click_event(MouseButton::one()), chama_pause_game, this);
	//			Simdunas::get_evt_handler()->add_hook(btn_lagartos->get_click_event(MouseButton::one()), btn_lagartos_action, this);
	//			Simdunas::get_evt_handler()->add_hook(predadores->get_click_event(MouseButton::one()), predadores_play, this);
	//			Simdunas::get_evt_handler()->add_hook(presas->get_click_event(MouseButton::one()), presas_play, this);
	//			Simdunas::get_evt_handler()->add_hook(habitat->get_click_event(MouseButton::one()), habitat_play, this);
	//			Simdunas::get_evt_handler()->add_hook(variacao_clima->get_click_event(MouseButton::one()), clima_play, this);
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
			titulo.show();
			img_videos.show();
			np_btn_clima.show();
			np_btn_continuar.show();
			np_btn_habitat.show();
			np_btn_lagartos.show();
			np_btn_predadores.show();
			np_btn_presas.show();
			np_btn_sair.show();
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

/*! Configura um botão dado os parametros para este menu */
void PauseScreen::default_button_config(PT(Button) button, NodePath &np,
		const string &text, float z, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, manager->get_default_font());
	np = get_root().attach_new_node(button);
	np.set_z(z);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
}

void PauseScreen::button_config(PT(Button) button, NodePath &np,
		const string &text, float x, float z, EventCallbackFunction *action) {

	default_button_config(button, np, text, z, action);
	np.set_x(x);
}

void PauseScreen::show() {
	pause_event();
}

void PauseScreen::hide() {
	titulo.hide();
	img_videos.hide();
	np_btn_clima.hide();
	np_btn_continuar.hide();
	np_btn_habitat.hide();
	np_btn_lagartos.hide();
	np_btn_predadores.hide();
	np_btn_presas.hide();
	np_btn_sair.hide();
}

bool PauseScreen::is_stopped_time() {
	return stopped_time;
}

void PauseScreen::lagartos_action() {

}

void PauseScreen::predadores_action() {

}

void PauseScreen::presas_action() {

}

void PauseScreen::clima_action() {

}

void PauseScreen::habitat_action() {

}

void PauseScreen::continuar_action() {
	pause_event();
}

void PauseScreen::sair_action() {
	//	Session::get_instance()->end_session();

	exit(0); //saindo direto, fechando o jogo
	//na tela de inicialização ou de game over
}
