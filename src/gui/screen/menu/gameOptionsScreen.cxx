/*
 * gameOptionsScreen.cxx
 *
 *  Created on: Mar 6, 2011
 *      Author: jonatas
 */

#include "gameOptionsScreen.h"
#include "simdunas.h"
#include "mouseButton.h"
#include "calangosMenuManager.h"
#include "fontPool.h"
#include "editorTextureScreen.h"

GameOptionsScreen::GameOptionsScreen(PT(ScreenManager) manager) : Screen(manager) {
	load();
	hide();
}

GameOptionsScreen::~GameOptionsScreen() {
}

void GameOptionsScreen::load() {
	ratio = 0;

	///carregando titulo do menu de configurações
	img_titulo = window->load_model(get_root(), "models/config_jogo.png");
	img_titulo.set_scale(0.1);
	img_titulo.set_pos(0.0, 0, 0.8);

	//relogio virtual////////////////////
	img_tempo = window->load_model(get_root(), "models/buttons/tempo");
	img_tempo.set_scale(1, 0.0, 0.2);
	img_tempo.set_pos(-0.8, 0.0, 0.6);

	img_frase_relogio = window->load_model(get_root(), "models/buttons/relogio_frase");
	img_frase_relogio.set_scale(1.8, 0.0, 0.2);
	img_frase_relogio.set_pos(-0.1, 0.0, 0.4);

//	/////////////////////Mostrando botão jogar////////////////////////
//	default_button_config(btn_jogar, np_btn_jogar, "Jogar", -0.8, jogar_action);

	// Mostrando botão voltar
	configure_default_back_button(((CalangosMenuManager* ) manager.p())->get_options_screen());

	//////////////////////////////////////////Opção de configuração Tempo Virtual//////////
	slide = new PGSliderBar("slid");
	slide->set_range(1, 60);
	slide->setup_slider(false, 1.0, 0.06, 0.01);
	np_slide = get_root().attach_new_node(slide);
	np_slide.set_scale(0.5, 1.0, 1.0);
	np_slide.set_pos(-0.84, 0.0, 0.27);

	//criando o botão mais//////////////////////////////////////////////////////////
	img_btn_mais = window->load_model(get_root(), "models/buttons/mais");
	img_btn_mais.detach_node();
	btn_mais = new PGButton("mais");
	btn_mais->setup(img_btn_mais);
	np_btn_mais = get_root().attach_new_node(btn_mais);
	np_btn_mais.set_scale(0.12);
	np_btn_mais.set_pos(-0.53, 0.0, 0.28);
	btn_mais->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_mais->get_click_event(MouseButton::one()), slide_direita_action, this);

	////////o default será três? minutos então ja começa como se tivesse dado três clicks no +
//	for (int i = 0; i < TimeControl::get_instance()->get_virtual_time_hour(); i++) {
//		//                            const Event *ev_direita = new Event(btn_mais->get_click_event(MouseButton::one()));
//		//                            event_queue->queue_event(ev_direita);
//		//  simdunas_cat.debug()<<"Minuto dia virtual: "<<config->minuto_dia_virtual<<endl;
//
//		//melhor que ficar enfileirando eventos!!!
//		slide_direita_action();
//	}

	//criando o botão menos///////////////////////////////
	img_btn_menos = window->load_model(get_root(), "models/buttons/menos");
	img_btn_menos.detach_node();

	btn_menos = new PGButton("menos");
	btn_menos->setup(img_btn_menos);
	np_btn_menos = get_root().attach_new_node(btn_menos);
	np_btn_menos.set_scale(0.12);
	np_btn_menos.set_pos(-1.15, 0.0, 0.28);
	btn_menos->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_menos->get_click_event(MouseButton::one()), slide_esquerda_action, this);

	/* Configuração de NumMinutos */
	lb_num_minutos = new TextNode("inicio");
	lb_num_minutos->set_font(FontPool::load_font("models/ExpletiveDeleted.ttf"));

	np_lb_num_minutos = get_root().attach_new_node(lb_num_minutos);
	np_lb_num_minutos.set_scale(0.17);
	np_lb_num_minutos.set_pos(-1.2, 0, 0.35);
	np_lb_num_minutos.set_color(0.87, 0.72, 0.52);
	np_lb_num_minutos.unstash();

	ostringstream letra; //convertendo minuto dia virtual em string
	letra << TimeControl::get_instance()->get_virtual_time_hour();
	std::string st(letra.str());
	informa_segundos(st);
}

void GameOptionsScreen::show() {
	Screen::show();
}

void GameOptionsScreen::hide() {
	Screen::hide();
}

/*! Evento de click no botão "+" do slider. Aumenta 1 no valor dos minutos/hora do jogo. */
void GameOptionsScreen::slide_direita_action() {
	int minuto_dia_virtual = TimeControl::get_instance()->get_virtual_time_hour();
	if (minuto_dia_virtual < 60) {
		TimeControl::get_instance()->set_virtual_time_hour(++minuto_dia_virtual);

		ostringstream letra; //convertendo float em string

		//TimeControl::virtualTime = d->minuto_dia_virtual;

		letra << minuto_dia_virtual;
		std::string st(letra.str());

		informa_segundos(st);

		/*simdunas_cat.debug()<<"Valor :"<<(int)d->slid->get_value()<<endl;
            simdunas_cat.debug()<<"Valor Minuto_dia_Virtual Direita:"<<d->minuto_dia_virtual<<endl;*/

		slide->set_value(minuto_dia_virtual);
	}
}

/*! Evento de click no botão "-" do slider. Diminui 1 no valor dos minutos/hora do jogo. */
void GameOptionsScreen::slide_esquerda_action() {
	int minuto_dia_virtual = TimeControl::get_instance()->get_virtual_time_hour();
	if (minuto_dia_virtual > 1) {
		TimeControl::get_instance()->set_virtual_time_hour(--minuto_dia_virtual);

		ostringstream letra; //convertendo float em string

		//TimeControl::virtualTime = d->minuto_dia_virtual;

		letra << minuto_dia_virtual;
		std::string st(letra.str());

		informa_segundos(st);

		/*simdunas_cat.debug()<<"Valor :"<<(int)d->slid->get_value()<<endl;
            simdunas_cat.debug()<<"Valor Minuto_dia_Virtual Esquerda:"<<d->minuto_dia_virtual<<endl;*/
		slide->set_value(minuto_dia_virtual);
	}
}

void GameOptionsScreen::informa_segundos(string aviso) {
	lb_num_minutos->set_text(aviso);
}

/*! Evento de quando a barra do slider é movida. O novo valor para os minutos/hora do jogo é atualizado. */
void GameOptionsScreen::slide_action() {
    int minuto_dia_virtual = (int) slide->get_value();
    TimeControl::get_instance()->set_virtual_time_hour(minuto_dia_virtual);
    ostringstream letra; //convertendo float em string
    letra << minuto_dia_virtual;
    std::string st(letra.str());

    informa_segundos(st);
}
