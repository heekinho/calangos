/*
 * loadingScreen.cxx
 *
 *  Created on: Feb 7, 2011
 *      Author: jonatas
 */

#include "loadingScreen.h"
#include "mouseButton.h"
#include "simdunas.h"
#include "session.h"
#include "pgVirtualFrame.h"

LoadingScreen::LoadingScreen(PT(ScreenManager) manager) : Screen(manager) {
	start = false;
	load();
	attach_objects();
	hide();

	manager->get_event_handler()->add_hook(btn_comecar->get_click_event(MouseButton::one()), start_game, this);
}


LoadingScreen::~LoadingScreen() {
}


// Carrega e configura os objetos
void LoadingScreen::load() {
	frame = new PGVirtualFrame("LoadingScreen");
	frame->setup(2, 2);
	PGFrameStyle style = frame->get_frame_style(frame->get_state());
	style.set_type(PGFrameStyle::T_flat);
	frame->set_frame_style(frame->get_state(), style);
	np_frame = NodePath(frame);

	lb_objetivo = new TextNode("lb_objetivo");
	lb_objetivo->set_text(ConfigVariableString("msg-objt1", "Objetivo"));
	lb_objetivo->set_font(manager->get_default_font());

	lb_descricao_objetivo = new TextNode("lb_descricao_objetivo");
	lb_descricao_objetivo->set_text(ConfigVariableString("msg-objt2", "Seu objetivo nesta primeira fase é\n sobreviver, desenvolver-se e reproduzir.\n Seu sucesso será medido pelo número de\n vezes que conseguiu se reproduzir. Busque controlar o nível de energia e de hidratação, e também a temperatura\n interna. Seu lagarto vive até 36 meses.\n"));
	lb_descricao_objetivo->set_wordwrap(20);
	lb_descricao_objetivo->set_font(manager->get_default_font());

	lb_carregando = new TextNode("lb_carregando");
	lb_carregando->set_text(ConfigVariableString("msg-carre", "Carregando..."));
	lb_carregando->set_font(manager->get_default_font());

	lb_processo = new TextNode("lb_processo");
	lb_processo->set_text(ConfigVariableString("msg-proce", "Processo:"));
	lb_processo->set_font(manager->get_default_font());

	lb_info_processo = new TextNode("lb_info_processo");
	lb_info_processo->set_text("");
	lb_info_processo->set_font(manager->get_default_font());

	btn_comecar = new Button("btn_comecar", ConfigVariableString("msg-come", "Começar"), manager->get_default_font(), 0.17);
}


/*! Posiciona os objetos na tela. */
void LoadingScreen::attach_objects() {
	set_root(Simdunas::get_clickable_render_2d().attach_new_node("loadingScreen"));
	np_frame.reparent_to(get_root());
	np_frame.set_pos(-1, 0, -1);
	np_frame.set_color(0, 0, 0);

	np_lb_objetivo = np_frame.attach_new_node(lb_objetivo);
	np_lb_objetivo.set_pos(0.7, 0.0, 1.8);
	np_lb_objetivo.set_scale(0.15);
	np_lb_objetivo.set_color(0.87, 0.72, 0.52);

	np_lb_descricao_objetivo = np_frame.attach_new_node(lb_descricao_objetivo);
	np_lb_descricao_objetivo.set_pos(0.05, 0.0, 1.6);
	np_lb_descricao_objetivo.set_scale(0.1);
	np_lb_descricao_objetivo.set_color(1, 1, 1, 1, 0);

	np_lb_carregando = np_frame.attach_new_node(lb_carregando);
	np_lb_carregando.set_pos(0.7, 0.0, 0.3);
	np_lb_carregando.set_scale(0.13);
	np_lb_carregando.set_color(1, 1, 1, 1, 0);

	np_lb_processo = np_frame.attach_new_node(lb_processo);
	np_lb_processo.set_pos(0.4, 0.0, 0.1);
	np_lb_processo.set_scale(0.07);
	np_lb_processo.set_color(1, 1, 1, 1, 0);

	np_lb_info_processo = np_frame.attach_new_node(lb_info_processo);
	np_lb_info_processo.set_pos(np_lb_processo.get_x() + (lb_processo->get_width() * np_lb_processo.get_sx()) + 0.05, 0.0, 0.1);
	np_lb_info_processo.set_scale(0.07);
	np_lb_info_processo.set_color(1, 1, 1, 1, 0);

	np_btn_comecar = get_root().attach_new_node(btn_comecar);
	np_btn_comecar.set_pos(0, 0, -0.7);
	np_btn_comecar.set_alpha_scale(1, 2);
	np_btn_comecar.stash();
}

/*! Faz as chamadas para cada etapa de carregamento do jogo e atualiza a tela informando qual etapa está sendo carregada. */
void LoadingScreen::loading_process() {
	int process_stage = 0;
	while (!Session::get_instance()->is_finished_loading()) {
		string text = Session::get_instance()->get_stage_info()[process_stage];
		lb_info_processo->set_text(text);
		Simdunas::get_framework()->do_frame(Thread::get_current_thread());
		Simdunas::get_framework()->do_frame(Thread::get_current_thread());
		Session::get_instance()->init_session(process_stage);
		process_stage++;
	}
	loading_completed();
}

/*! Mostra o botão de começar e esconde as labels de progresso do carregamento. Também aguarda até que o botão
 * "Começar" seja clicado */
void LoadingScreen::loading_completed() {
	np_lb_carregando.stash();
	lb_info_processo->set_text(ConfigVariableString("msg-concl", "Concluído"));
	np_frame.set_transparency(TransparencyAttrib::M_alpha);
	np_frame.set_alpha_scale(0.5);
	np_btn_comecar.unstash();

	// espera até que o usuário tenha clicado no botão "Começar"
	while (!start) {
		Simdunas::get_framework()->do_frame(Thread::get_current_thread());
	}
}

/*! Evento de click no botão "Começar". Sinaliza que foi clicado através do flag. */
void LoadingScreen::start_game() {
//	LoadingScreen* _this = (LoadingScreen*) data;
//	_this->set_start(true);
	start = true;
}

void LoadingScreen::set_start(bool flag) {
	start = flag;
}
