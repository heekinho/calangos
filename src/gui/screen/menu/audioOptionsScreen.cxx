/*
 *  audioOptionsScreen.cxx
 *  Created on: Oct 19, 2011
 *  Author: jonatas
 */

#include "audioOptionsScreen.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"
#include "calangosMenuManager.h"
#include "audioController.h"
#include "imageRepository.h"

/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
AudioOptionsScreen::AudioOptionsScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

AudioOptionsScreen::~AudioOptionsScreen() {

}

void AudioOptionsScreen::load(){
	lb_titulo = new TextNode("txt_titulo");
	lb_titulo->set_text("Opções de Áudio");
	lb_titulo->set_font(manager->get_default_font());
	np_lb_titulo = get_root().attach_new_node(lb_titulo);
	np_lb_titulo.set_scale(0.2);
	np_lb_titulo.set_x(-lb_titulo->get_width()*np_lb_titulo.get_sx()*0.5);
	np_lb_titulo.set_z(0.7);
	np_lb_titulo.set_color(0.87, 0.72, 0.52);

	lb_efeitos_sonoros = new TextNode("lb_efeitos_sonoros");
	lb_efeitos_sonoros->set_text("Efeitos Sonoros:");
	lb_efeitos_sonoros->set_font(manager->get_default_font());
	np_lb_efeitos_sonoros = get_root().attach_new_node(lb_efeitos_sonoros);
	np_lb_efeitos_sonoros.set_pos(-1.2, 0.0, 0.25);
	np_lb_efeitos_sonoros.set_scale(0.1);
	np_lb_efeitos_sonoros.set_color(1, 1, 1, 1, 0);

	slide = new PGSliderBar("slid");
	slide->set_range(0, 100);
	slide->setup_slider(false, 1.0, 0.06, 0.01);
	slide->set_value(100);
	np_slide = get_root().attach_new_node(slide);
	np_slide.set_scale(0.5, 1.0, 1.0);
	np_slide.set_pos(0, 0.0, 0.275);
	event_handler->add_hook(slide->get_adjust_event(), slide_action, this);

	img_btn_mais = window->load_model(get_root(), "models/buttons/mais");
	img_btn_mais.detach_node();
	btn_mais = new PGButton("mais");
	btn_mais->setup(img_btn_mais);
	np_btn_mais = get_root().attach_new_node(btn_mais);
	np_btn_mais.set_scale(0.12);
	np_btn_mais.set_pos(0.31, 0.0, 0.28);
	btn_mais->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_mais->get_click_event(MouseButton::one()), increase_volume_action, this);

	img_btn_menos = window->load_model(get_root(), "models/buttons/menos");
	img_btn_menos.detach_node();
	btn_menos = new PGButton("menos");
	btn_menos->setup(img_btn_menos);
	np_btn_menos = get_root().attach_new_node(btn_menos);
	np_btn_menos.set_scale(0.12);
	np_btn_menos.set_pos(-0.313, 0.0, 0.28);
	btn_menos->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_menos->get_click_event(MouseButton::one()), decrease_volume_action, this);

	img_btn_sfx_enabled = ImageRepository::get_instance()->get_image("v");
	img_btn_sfx_enabled.detach_node();
	btn_sfx_enabled = new PGButton("btn_sfx_enabled");
	btn_sfx_enabled->setup(img_btn_sfx_enabled);
	np_btn_sfx_enabled = get_root().attach_new_node(btn_sfx_enabled);
	np_btn_sfx_enabled.set_scale(0.015);
	np_btn_sfx_enabled.set_pos(0.45, 0.0, 0.26);
	event_handler->add_hook(btn_sfx_enabled->get_click_event(MouseButton::one()), disable_sfx, this);

	img_btn_sfx_disabled = ImageRepository::get_instance()->get_image("x");
	img_btn_sfx_disabled.detach_node();
	btn_sfx_disabled = new PGButton("btn_sfx_disabled");
	btn_sfx_disabled->setup(img_btn_sfx_disabled);
	np_btn_sfx_disabled = get_root().attach_new_node(btn_sfx_disabled);
	np_btn_sfx_disabled.stash();
	np_btn_sfx_disabled.set_scale(0.015);
	np_btn_sfx_disabled.set_pos(0.45, 0.0, 0.26);
	event_handler->add_hook(btn_sfx_disabled->get_click_event(MouseButton::one()), enable_sfx, this);

	lb_musicas = new TextNode("lb_musicas");
	lb_musicas->set_text("Músicas:");
	lb_musicas->set_font(manager->get_default_font());
	np_lb_musicas = get_root().attach_new_node(lb_musicas);
	np_lb_musicas.set_pos(-0.79, 0.0, -0.121);
	np_lb_musicas.set_scale(0.1);
	np_lb_musicas.set_color(1, 1, 1, 1, 0);

	slide_2 = new PGSliderBar("slid_2");
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
	np_btn_mais_2.set_pos(0.31, 0.0, -0.08);
	btn_mais_2->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_mais_2->get_click_event(MouseButton::one()), increase_volume_action_2, this);

	img_btn_menos_2 = window->load_model(get_root(), "models/buttons/menos");
	img_btn_menos_2.detach_node();
	btn_menos_2 = new PGButton("menos_2");
	btn_menos_2->setup(img_btn_menos_2);
	np_btn_menos_2 = get_root().attach_new_node(btn_menos_2);
	np_btn_menos_2.set_scale(0.12);
	np_btn_menos_2.set_pos(-0.313, 0.0, -0.08);
	btn_menos_2->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_menos_2->get_click_event(MouseButton::one()), decrease_volume_action_2, this);

	img_btn_bgm_enabled = ImageRepository::get_instance()->get_image("v");
	img_btn_bgm_enabled.detach_node();
	btn_bgm_enabled = new PGButton("btn_bgm_enabled");
	btn_bgm_enabled->setup(img_btn_bgm_enabled);
	np_btn_bgm_enabled = get_root().attach_new_node(btn_bgm_enabled);
	np_btn_bgm_enabled.set_scale(0.015);
	np_btn_bgm_enabled.set_pos(0.45, 0.0, -0.10);
	event_handler->add_hook(btn_bgm_enabled->get_click_event(MouseButton::one()), disable_bgm, this);

	img_btn_bgm_disabled = ImageRepository::get_instance()->get_image("x");
	img_btn_bgm_disabled.detach_node();
	btn_bgm_disabled = new PGButton("btn_bgm_disabled");
	btn_bgm_disabled->setup(img_btn_bgm_disabled);
	np_btn_bgm_disabled = get_root().attach_new_node(btn_bgm_disabled);
	np_btn_bgm_disabled.stash();
	np_btn_bgm_disabled.set_scale(0.015);
	np_btn_bgm_disabled.set_pos(0.45, 0.0, -0.10);
	event_handler->add_hook(btn_bgm_disabled->get_click_event(MouseButton::one()), enable_bgm, this);

	configure_default_back_button(((CalangosMenuManager*)(manager.p()))->get_options_screen());
}

/*! Evento de quando a barra do slider é movida. O novo valor para o volume dos efeitos sonoros é atualizado. */
void AudioOptionsScreen::slide_action() {
	float value = slide->get_value();
	AudioController::get_instance()->get_audio_repository()->set_sfx_volume_percent(value / 100.0);
}

/*! Evento de click no botão "+" dos efeitos sonoros. Aumenta 1 no valor do volume dos efeitos sonoros. */
void AudioOptionsScreen::increase_volume_action() {
	float value = slide->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 100) return;
	value += 1;
	AudioController::get_instance()->get_audio_repository()->set_sfx_volume_percent(value / 100.0);
	slide->set_value(value);
}

/*! Evento de click no botão "-" dos efeitos sonoros. Diminui 1 no valor do volume dos efeitos sonoros. */
void AudioOptionsScreen::decrease_volume_action() {
	float value = slide->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 0) return;
	value -= 1;
	AudioController::get_instance()->get_audio_repository()->set_sfx_volume_percent(value / 100.0);
	slide->set_value(value);
}

/*! Evento de click no botão que desabilita os efeitos sonoros. */
void AudioOptionsScreen::disable_sfx() {
	np_btn_sfx_enabled.stash();
	np_btn_sfx_disabled.unstash();
	btn_mais->set_active(false);
	btn_menos->set_active(false);
	slide->set_active(false);
	AudioController::get_instance()->get_audio_repository()->set_sfx_enabled(false);
}

/*! Evento de click no botão que habilita os efeitos sonoros. */
void AudioOptionsScreen::enable_sfx() {
	np_btn_sfx_enabled.unstash();
	np_btn_sfx_disabled.stash();
	btn_mais->set_active(true);
	btn_menos->set_active(true);
	slide->set_active(true);
	AudioController::get_instance()->get_audio_repository()->set_sfx_enabled(true);
}

/*! Evento de quando a barra do slider é movida. O novo valor para o volume das músicas de fundo é atualizado. */
void AudioOptionsScreen::slide_action_2() {
	float value = slide_2->get_value();
	AudioController::get_instance()->get_audio_repository()->set_bgm_volume_percent(value / 100.0);
}

/*! Evento de click no botão "+" das músicas de fundo. Aumenta 1 no valor do volume das músicas de fundo. */
void AudioOptionsScreen::increase_volume_action_2() {
	float value = slide_2->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 100) return;
	value += 1;
	AudioController::get_instance()->get_audio_repository()->set_bgm_volume_percent(value / 100.0);
	slide_2->set_value(value);
}

/*! Evento de click no botão "-" das músicas de fundo. Diminui 1 no valor do volume das músicas de fundo. */
void AudioOptionsScreen::decrease_volume_action_2() {
	float value = slide_2->get_value();
	simdunas_cat.debug()<<"value = "<<value<<endl;
	if (value == 0) return;
	value -= 1;
	AudioController::get_instance()->get_audio_repository()->set_bgm_volume_percent(value / 100.0);
	slide_2->set_value(value);
}

/*! Evento de click no botão que desabilita as músicas de fundo. */
void AudioOptionsScreen::disable_bgm() {
	np_btn_bgm_enabled.stash();
	np_btn_bgm_disabled.unstash();
	btn_mais_2->set_active(false);
	btn_menos_2->set_active(false);
	slide_2->set_active(false);
	AudioController::get_instance()->get_audio_repository()->set_bgm_enabled(false);
}

/*! Evento de click no botão que habilita as músicas de fundo. */
void AudioOptionsScreen::enable_bgm() {
	np_btn_bgm_enabled.unstash();
	np_btn_bgm_disabled.stash();
	btn_mais_2->set_active(true);
	btn_menos_2->set_active(true);
	slide_2->set_active(true);
	AudioController::get_instance()->get_audio_repository()->set_bgm_enabled(true);
}
