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
#include "audioController.h"
#include "imageRepository.h"
#include "collision.h"

GameOptionsScreen::GameOptionsScreen(PT(ScreenManager) manager) : Screen(manager) {
	load();
	hide();
}

GameOptionsScreen::~GameOptionsScreen() {
}

void GameOptionsScreen::load() {
	ratio = 0;

	///carregando titulo do menu de configurações
	lb_configuracoes_jogo = new TextNode("lb_configuracoes_jogo");
	lb_configuracoes_jogo->set_text(ConfigVariableString("msg-conf", "Configurações do Jogo"));
	lb_configuracoes_jogo->set_font(manager->get_default_font());
	np_lb_configuracoes_jogo = get_root().attach_new_node(lb_configuracoes_jogo);
	np_lb_configuracoes_jogo.set_pos(-0.7, 0, 0.8);
	np_lb_configuracoes_jogo.set_scale(0.14);
	np_lb_configuracoes_jogo.set_color(1, 1, 1, 1, 0);

	//relogio virtual////////////////////
	lb_relogio_virtual = new TextNode("lb_relogio_virtual");
	lb_relogio_virtual->set_text(ConfigVariableString("msg-relo", "Rélogio Virtual"));
	lb_relogio_virtual->set_font(manager->get_default_font());
	np_lb_relogio_virtual = get_root().attach_new_node(lb_relogio_virtual);
	np_lb_relogio_virtual.set_pos(-1.2, 0, 0.6);
	np_lb_relogio_virtual.set_scale(0.12);
	np_lb_relogio_virtual.set_color(1, 1, 1, 1, 0);

	lb_frase_relogio = new TextNode("lb_frase_relogio");
	lb_frase_relogio->set_text(ConfigVariableString("msg-minu", " Minutos = Um dia virtual do jogo"));
	lb_frase_relogio->set_font(manager->get_default_font());
	np_lb_frase_relogio = get_root().attach_new_node(lb_frase_relogio);
	np_lb_frase_relogio.set_pos(-1.05, 0, 0.375);
	np_lb_frase_relogio.set_scale(0.12);
	np_lb_frase_relogio.set_color(1, 1, 1, 1, 0);

//	/////////////////////Mostrando botão jogar////////////////////////
//	default_button_config(btn_jogar, np_btn_jogar, "Jogar", -0.8, jogar_action);

	// Mostrando botão voltar
	configure_default_back_button(((CalangosMenuManager* ) manager.p())->get_main_menu());

	//////////////////////////////////////////Opção de configuração Tempo Virtual//////////
	slide = new PGSliderBar("slid");
	slide->set_range(1, 60);
	slide->setup_slider(false, 1.0, 0.06, 0.01);
	slide->set_value(3);
	np_slide = get_root().attach_new_node(slide);
	np_slide.set_scale(0.5, 1.0, 1.0);
	np_slide.set_pos(-0.84, 0.0, 0.27);
	event_handler->add_hook(slide->get_adjust_event(), slide_action, this);

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

	// Opções de Áudio
	lb_opcoes_de_audio = new TextNode("lb_opcoes_de_audio");
	lb_opcoes_de_audio->set_text(ConfigVariableString("msg-audi", "Opções de Áudio"));
	lb_opcoes_de_audio->set_font(manager->get_default_font());
	np_lb_opcoes_de_audio = get_root().attach_new_node(lb_opcoes_de_audio);
	np_lb_opcoes_de_audio.set_pos(-1.2, 0.0, 0.075);
	np_lb_opcoes_de_audio.set_scale(0.12);
	np_lb_opcoes_de_audio.set_color(1, 1, 1, 1, 0);

	lb_efeitos_sonoros = new TextNode("lb_efeitos_sonoros");
	lb_efeitos_sonoros->set_text(ConfigVariableString("msg-efei", "Efeitos Sonoros:"));
	lb_efeitos_sonoros->set_font(manager->get_default_font());
	np_lb_efeitos_sonoros = get_root().attach_new_node(lb_efeitos_sonoros);
	np_lb_efeitos_sonoros.set_pos(-1.2, 0.0, -0.125);
	np_lb_efeitos_sonoros.set_scale(0.1);
	np_lb_efeitos_sonoros.set_color(1, 1, 1, 1, 0);

	slide_2 = new PGSliderBar("slid");
	slide_2->set_range(0, 100);
	slide_2->setup_slider(false, 1.0, 0.06, 0.01);
	slide_2->set_value(100);
	np_slide_2 = get_root().attach_new_node(slide_2);
	np_slide_2.set_scale(0.5, 1.0, 1.0);
	np_slide_2.set_pos(0, 0.0, -0.075);
	event_handler->add_hook(slide_2->get_adjust_event(), slide_action_2, this);

	img_btn_mais_2 = window->load_model(get_root(), "models/buttons/mais");
	img_btn_mais_2.detach_node();
	btn_mais_2 = new PGButton("mais_2");
	btn_mais_2->setup(img_btn_mais_2);
	np_btn_mais_2 = get_root().attach_new_node(btn_mais_2);
	np_btn_mais_2.set_scale(0.12);
	np_btn_mais_2.set_pos(0.31, 0.0, -0.075);
	btn_mais_2->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_mais_2->get_click_event(MouseButton::one()), increase_volume_action, this);

	img_btn_menos_2 = window->load_model(get_root(), "models/buttons/menos");
	img_btn_menos_2.detach_node();
	btn_menos_2 = new PGButton("menos_2");
	btn_menos_2->setup(img_btn_menos_2);
	np_btn_menos_2 = get_root().attach_new_node(btn_menos_2);
	np_btn_menos_2.set_scale(0.12);
	np_btn_menos_2.set_pos(-0.313, 0.0, -0.075);
	btn_menos_2->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_menos_2->get_click_event(MouseButton::one()), decrease_volume_action, this);

	img_btn_sfx_enabled = ImageRepository::get_instance()->get_image("v");
	img_btn_sfx_enabled.detach_node();
	btn_sfx_enabled = new PGButton("btn_sfx_enabled");
	btn_sfx_enabled->setup(img_btn_sfx_enabled);
	np_btn_sfx_enabled = get_root().attach_new_node(btn_sfx_enabled);
	np_btn_sfx_enabled.set_scale(0.015);
	np_btn_sfx_enabled.set_pos(0.45, 0.0, -0.075);
	event_handler->add_hook(btn_sfx_enabled->get_click_event(MouseButton::one()), disable_sfx, this);

	img_btn_sfx_disabled = ImageRepository::get_instance()->get_image("x");
	img_btn_sfx_disabled.detach_node();
	btn_sfx_disabled = new PGButton("btn_sfx_disabled");
	btn_sfx_disabled->setup(img_btn_sfx_disabled);
	np_btn_sfx_disabled = get_root().attach_new_node(btn_sfx_disabled);
	np_btn_sfx_disabled.stash();
	np_btn_sfx_disabled.set_scale(0.015);
	np_btn_sfx_disabled.set_pos(0.45, 0.0, -0.075);
	event_handler->add_hook(btn_sfx_disabled->get_click_event(MouseButton::one()), enable_sfx, this);

	lb_musicas = new TextNode("lb_musicas");
	lb_musicas->set_text(ConfigVariableString("msg-musi", "Músicas:"));
	lb_musicas->set_font(manager->get_default_font());
	np_lb_musicas = get_root().attach_new_node(lb_musicas);
	np_lb_musicas.set_pos(-0.79, 0.0, -0.35);
	np_lb_musicas.set_scale(0.1);
	np_lb_musicas.set_color(1, 1, 1, 1, 0);

	slide_3 = new PGSliderBar("slid_2");
	slide_3->set_range(0, 100);
	slide_3->setup_slider(false, 1.0, 0.06, 0.01);
	slide_3->set_value(100);
	np_slide_3 = get_root().attach_new_node(slide_3);
	np_slide_3.set_scale(0.5, 1.0, 1.0);
	np_slide_3.set_pos(0, 0.0, -0.3);
	event_handler->add_hook(slide_3->get_adjust_event(), slide_action_3, this);

	img_btn_mais_3 = window->load_model(get_root(), "models/buttons/mais");
	img_btn_mais_3.detach_node();
	btn_mais_3 = new PGButton("mais_3");
	btn_mais_3->setup(img_btn_mais_3);
	np_btn_mais_3 = get_root().attach_new_node(btn_mais_3);
	np_btn_mais_3.set_scale(0.12);
	np_btn_mais_3.set_pos(0.31, 0.0, -0.3);
	btn_mais_3->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_mais_3->get_click_event(MouseButton::one()), increase_volume_action_2, this);

	img_btn_menos_3 = window->load_model(get_root(), "models/buttons/menos");
	img_btn_menos_3.detach_node();
	btn_menos_3 = new PGButton("menos_3");
	btn_menos_3->setup(img_btn_menos_3);
	np_btn_menos_3 = get_root().attach_new_node(btn_menos_3);
	np_btn_menos_3.set_scale(0.12);
	np_btn_menos_3.set_pos(-0.313, 0.0, -0.3);
	btn_menos_3->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_menos_3->get_click_event(MouseButton::one()), decrease_volume_action_2, this);

	img_btn_bgm_enabled = ImageRepository::get_instance()->get_image("v");
	img_btn_bgm_enabled.detach_node();
	btn_bgm_enabled = new PGButton("btn_bgm_enabled");
	btn_bgm_enabled->setup(img_btn_bgm_enabled);
	np_btn_bgm_enabled = get_root().attach_new_node(btn_bgm_enabled);
	np_btn_bgm_enabled.set_scale(0.015);
	np_btn_bgm_enabled.set_pos(0.45, 0.0, -0.325);
	event_handler->add_hook(btn_bgm_enabled->get_click_event(MouseButton::one()), disable_bgm, this);

	img_btn_bgm_disabled = ImageRepository::get_instance()->get_image("x");
	img_btn_bgm_disabled.detach_node();
	btn_bgm_disabled = new PGButton("btn_bgm_disabled");
	btn_bgm_disabled->setup(img_btn_bgm_disabled);
	np_btn_bgm_disabled = get_root().attach_new_node(btn_bgm_disabled);
	np_btn_bgm_disabled.stash();
	np_btn_bgm_disabled.set_scale(0.015);
	np_btn_bgm_disabled.set_pos(0.45, 0.0, -0.325);
	event_handler->add_hook(btn_bgm_disabled->get_click_event(MouseButton::one()), enable_bgm, this);

	// Opções de Colisão
	lb_colisao = new TextNode("lb_colisao");
	lb_colisao->set_text(ConfigVariableString("msg-coli", "Colisão:"));
	lb_colisao->set_font(manager->get_default_font());
	np_lb_colisao = get_root().attach_new_node(lb_colisao);
	np_lb_colisao.set_pos(-1.2, 0.0, -0.55);
	np_lb_colisao.set_scale(0.12);
	np_lb_colisao.set_color(1, 1, 1, 1, 0);

	img_btn_colisao_ativada = ImageRepository::get_instance()->get_image("v");
	img_btn_colisao_ativada.detach_node();
	btn_colisao_ativada = new PGButton("btn_colisao_ativada");
	btn_colisao_ativada->setup(img_btn_colisao_ativada);
	np_btn_colisao_ativada = get_root().attach_new_node(btn_colisao_ativada);
	np_btn_colisao_ativada.set_scale(0.015);
	np_btn_colisao_ativada.set_pos(-0.7, 0.0, -0.55);
	event_handler->add_hook(btn_colisao_ativada->get_click_event(MouseButton::one()), colisao_action, this);

	img_btn_colisao_desativada = ImageRepository::get_instance()->get_image("x");
	img_btn_colisao_desativada.detach_node();
	btn_colisao_desativada = new PGButton("btn_colisao_desativada");
	btn_colisao_desativada->setup(img_btn_colisao_desativada);
	np_btn_colisao_desativada = get_root().attach_new_node(btn_colisao_desativada);
	np_btn_colisao_desativada.stash();
	np_btn_colisao_desativada.set_scale(0.015);
	np_btn_colisao_desativada.set_pos(-0.7, 0.0, -0.55);
	event_handler->add_hook(btn_colisao_desativada->get_click_event(MouseButton::one()), colisao_action, this);

	if (collision::get_instance()->get_colisao()) {
		np_btn_colisao_ativada.unstash();
		np_btn_colisao_desativada.stash();
	}
	else {
		np_btn_colisao_desativada.unstash();
		np_btn_colisao_ativada.stash();
	}

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
//	int minuto_dia_virtual = TimeControl::get_instance()->get_virtual_time_hour();
//	if (minuto_dia_virtual < 60) {
//		TimeControl::get_instance()->set_virtual_time_hour(++minuto_dia_virtual);
//
//		ostringstream letra; //convertendo float em string
//
//		//TimeControl::virtualTime = d->minuto_dia_virtual;
//
//		letra << minuto_dia_virtual;
//		std::string st(letra.str());
//
//		informa_segundos(st);
//
//		/*simdunas_cat.debug()<<"Valor :"<<(int)d->slid->get_value()<<endl;
//            simdunas_cat.debug()<<"Valor Minuto_dia_Virtual Direita:"<<d->minuto_dia_virtual<<endl;*/
//
//		slide->set_value(minuto_dia_virtual);
//	}
	int minuto_dia_virtual = slide->get_value();
	if (minuto_dia_virtual == 60) {
		return;
	}
	minuto_dia_virtual++;
	TimeControl::get_instance()->set_virtual_time_hour(minuto_dia_virtual);
	slide->set_value(minuto_dia_virtual);
	ostringstream letra; //convertendo float em string
	letra << minuto_dia_virtual;
	std::string st(letra.str());
	informa_segundos(st);
}

/*! Evento de click no botão "-" do slider. Diminui 1 no valor dos minutos/hora do jogo. */
void GameOptionsScreen::slide_esquerda_action() {
//	int minuto_dia_virtual = TimeControl::get_instance()->get_virtual_time_hour();
//	if (minuto_dia_virtual > 1) {
//		TimeControl::get_instance()->set_virtual_time_hour(--minuto_dia_virtual);
//
//		ostringstream letra; //convertendo float em string
//
//		//TimeControl::virtualTime = d->minuto_dia_virtual;
//
//		letra << minuto_dia_virtual;
//		std::string st(letra.str());
//
//		informa_segundos(st);
//
//		/*simdunas_cat.debug()<<"Valor :"<<(int)d->slid->get_value()<<endl;
//            simdunas_cat.debug()<<"Valor Minuto_dia_Virtual Esquerda:"<<d->minuto_dia_virtual<<endl;*/
//		slide->set_value(minuto_dia_virtual);
//	}

	int minuto_dia_virtual = slide->get_value();
	if (minuto_dia_virtual == 1) {
		return;
	}
	minuto_dia_virtual--;
	TimeControl::get_instance()->set_virtual_time_hour(minuto_dia_virtual);
	slide->set_value(minuto_dia_virtual);
	ostringstream letra; //convertendo float em string
	letra << minuto_dia_virtual;
	std::string st(letra.str());
	informa_segundos(st);
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

/*! Evento de quando a barra do slider é movida. O novo valor para o volume dos efeitos sonoros é atualizado. */
void GameOptionsScreen::slide_action_2() {
	float value = slide_2->get_value();
	AudioController::get_instance()->get_audio_repository()->set_sfx_volume_percent(value / 100.0);
}

/*! Evento de click no botão "+" dos efeitos sonoros. Aumenta 1 no valor do volume dos efeitos sonoros. */
void GameOptionsScreen::increase_volume_action() {
	float value = slide_2->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 100) return;
	value += 1;
	AudioController::get_instance()->get_audio_repository()->set_sfx_volume_percent(value / 100.0);
	slide_2->set_value(value);
}

/*! Evento de click no botão "-" dos efeitos sonoros. Diminui 1 no valor do volume dos efeitos sonoros. */
void GameOptionsScreen::decrease_volume_action() {
	float value = slide_2->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 0) return;
	value -= 1;
	AudioController::get_instance()->get_audio_repository()->set_sfx_volume_percent(value / 100.0);
	slide_2->set_value(value);
}

/*! Evento de click no botão que desabilita os efeitos sonoros. */
void GameOptionsScreen::disable_sfx() {
	np_btn_sfx_enabled.stash();
	np_btn_sfx_disabled.unstash();
	btn_mais_2->set_active(false);
	btn_menos_2->set_active(false);
	slide_2->set_active(false);
	AudioController::get_instance()->get_audio_repository()->set_sfx_enabled(false);
}

/*! Evento de click no botão que habilita os efeitos sonoros. */
void GameOptionsScreen::enable_sfx() {
	np_btn_sfx_enabled.unstash();
	np_btn_sfx_disabled.stash();
	btn_mais_2->set_active(true);
	btn_menos_2->set_active(true);
	slide_2->set_active(true);
	AudioController::get_instance()->get_audio_repository()->set_sfx_enabled(true);
}

/*! Evento de quando a barra do slider é movida. O novo valor para o volume das músicas de fundo é atualizado. */
void GameOptionsScreen::slide_action_3() {
	float value = slide_3->get_value();
	AudioController::get_instance()->get_audio_repository()->set_bgm_volume_percent(value / 100.0);
}

/*! Evento de click no botão "+" das músicas de fundo. Aumenta 1 no valor do volume das músicas de fundo. */
void GameOptionsScreen::increase_volume_action_2() {
	float value = slide_3->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 100) return;
	value += 1;
	AudioController::get_instance()->get_audio_repository()->set_bgm_volume_percent(value / 100.0);
	slide_3->set_value(value);
}

/*! Evento de click no botão "-" das músicas de fundo. Diminui 1 no valor do volume das músicas de fundo. */
void GameOptionsScreen::decrease_volume_action_2() {
	float value = slide_3->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 0) return;
	value -= 1;
	AudioController::get_instance()->get_audio_repository()->set_bgm_volume_percent(value / 100.0);
	slide_3->set_value(value);
}

/*! Evento de click no botão que desabilita as músicas de fundo. */
void GameOptionsScreen::disable_bgm() {
	np_btn_bgm_enabled.stash();
	np_btn_bgm_disabled.unstash();
	btn_mais_3->set_active(false);
	btn_menos_3->set_active(false);
	slide_3->set_active(false);
	AudioController::get_instance()->get_audio_repository()->set_bgm_enabled(false);
}

/*! Evento de click no botão que habilita as músicas de fundo. */
void GameOptionsScreen::enable_bgm() {
	np_btn_bgm_enabled.unstash();
	np_btn_bgm_disabled.stash();
	btn_mais_3->set_active(true);
	btn_menos_3->set_active(true);
	slide_3->set_active(true);
	AudioController::get_instance()->get_audio_repository()->set_bgm_enabled(true);
}

void GameOptionsScreen::colisao_action() {
    //se a colisão tiver ativada, então desativa agora
    if(collision::get_instance()->get_colisao()){
        np_btn_colisao_ativada.stash();
        np_btn_colisao_desativada.unstash();
        collision::get_instance()->set_colisao(false);
    }else
    { //se estiver desativada então ativa.
    	np_btn_colisao_ativada.unstash();
    	np_btn_colisao_desativada.stash();
        collision::get_instance()->set_colisao(true);
    }
}
