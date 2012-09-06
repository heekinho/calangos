/*
 * characterOptionsScreen.cxx
 *
 *  Created on: Sep 5, 2012
 *      Author: eduardo
 */

#include "characterOptionsScreen.h"
#include "simdunas.h"
#include "mouseButton.h"
#include "calangosMenuManager.h"
#include "fontPool.h"
#include "editorTextureScreen.h"
#include "collision.h"

CharacterOptionsScreen::CharacterOptionsScreen(PT(ScreenManager) manager) : Screen(manager) {
	load();
	hide();
}

CharacterOptionsScreen::~CharacterOptionsScreen() {
}

void CharacterOptionsScreen::load() {

    ////////////////////////Tropidurus////////////////////
    tropidurus = window->load_model(render, "models/lizards/tropidurus/male/model");
    tropidurus.set_scale(0.04, 0.04, 0.04);
    tropidurus.set_pos(4, 35, -3);
    tropidurus.set_h(45);
    tropidurus.set_p(20);
    /* Animação */
    window->load_model(tropidurus, "models/lizards/tropidurus/male/walk");
    auto_bind(tropidurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    tropidurus.stash();

    //////////////////////////Eurolophosauros/////////////////
    eurolophosasurus = window->load_model(render, "models/lizards/eurolophosaurus/male/model");
    eurolophosasurus.set_scale(0.04, 0.04, 0.04);
    eurolophosasurus.set_pos(4, 35, -3);
    eurolophosasurus.set_h(45);
    eurolophosasurus.set_p(20);
    /* Animação */
    window->load_model(eurolophosasurus, "models/lizards/eurolophosaurus/male/walk");
    auto_bind(eurolophosasurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    eurolophosasurus.stash();

    //////////////////Cnemidophorus////////////
    cnemidophorus = window->load_model(render, "models/lizards/cnemidophorus/male/model");
    cnemidophorus.set_scale(0.04, 0.04, 0.04);
    cnemidophorus.set_pos(4, 35, -3);
    cnemidophorus.set_h(45);
    cnemidophorus.set_p(20);
    //		/* Animação */
    window->load_model(cnemidophorus, "models/lizards/cnemidophorus/male/walk");
    auto_bind(cnemidophorus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    cnemidophorus.stash();

	// Mostrando botão voltar
    configure_default_back_button(((CalangosMenuManager*)(manager.p()))->get_level_selection_screen());

    default_button_config(btn_avancar, np_btn_avancar, "Avançar >>", LVecBase3f(0.7, 0, -0.9), jogar_action);

	///////opção de configuração de Escolha da Espécie/////////////
	img_escolha_especie = window->load_model(get_root(), "models/buttons/especie.png");
	img_escolha_especie.set_scale(0.06, 0.0, 0.06);
	img_escolha_especie.set_pos(-0.68, 0.0, 0.03);

	//carregando o marcador/////////
	marcador = window->load_model(img_escolha_especie, "models/buttons/marcador.png");
	marcador.set_scale(0.2, 0.0, 0.2);
	marcador.set_pos(4.0, 0.0, -4.7);

	///////Botões para escolha da especie/////////////////

	//botão TROPIDURUS///////////////
	img_btn_tropidurus = window->load_model(get_root(), "models/buttons/tropidurus");
	img_btn_tropidurus.detach_node();
	btn_tropidurus = new PGButton("tropidurus");
	btn_tropidurus->setup(img_btn_tropidurus);
	np_btn_tropidurus = get_root().attach_new_node(btn_tropidurus);
	np_btn_tropidurus.set_scale(0.5, 0.1, 0.18);
	np_btn_tropidurus.set_pos(-0.85, 0.0, -0.1);
	btn_tropidurus->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_tropidurus->get_click_event(MouseButton::one()), tropidurus_action, this);

	///////botão EUROLOPHOSAURUS //////////////////////////
	img_btn_eurolophosaurus = window->load_model(get_root(), "models/buttons/eurolophosaurus");
	img_btn_eurolophosaurus.detach_node();
	btn_eurolophosaurus = new PGButton("eurolophosaurus");
	btn_eurolophosaurus->setup(img_btn_eurolophosaurus);
	np_btn_eurolophosaurus = get_root().attach_new_node(btn_eurolophosaurus);
	np_btn_eurolophosaurus.set_scale(0.6, 0.1, 0.18);
	np_btn_eurolophosaurus.set_pos(-0.8, 0.0, -0.25);
	btn_eurolophosaurus->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_eurolophosaurus->get_click_event(MouseButton::one()), eurolophosaurus_action, this);

	///////botão CNEMIDOPHORUS //////////////////////////
	img_btn_cnemidophorus = window->load_model(get_root(), "models/buttons/cnemidophorus");
	img_btn_cnemidophorus.detach_node();
	btn_cnemidophorus = new PGButton("cnemidophorus");
	btn_cnemidophorus->setup(img_btn_cnemidophorus);
	np_btn_cnemidophorus = get_root().attach_new_node(btn_cnemidophorus);
	np_btn_cnemidophorus.set_scale(0.6, 0.1, 0.18);
	np_btn_cnemidophorus.set_pos(-0.8, 0.0, -0.4);
	btn_cnemidophorus->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_cnemidophorus->get_click_event(MouseButton::one()), cnemidophorus_action, this);

	//botão de ativar/desativar colisão
	img_btn_colisao = window->load_model(get_root(), "models/buttons/colisao");
	img_btn_colisao.detach_node();
	btn_colisao = new PGButton("colisao");
	btn_colisao->setup(img_btn_colisao);
	np_btn_colisao = get_root().attach_new_node(btn_colisao);
	np_btn_colisao.set_scale(0.6, 0.1, 0.18);
	np_btn_colisao.set_pos(0.6, 0.0, 0.03);
	btn_colisao->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_colisao->get_click_event(MouseButton::one()), colisao_action, this);

	//carregando botão V (de ativar colisão)
	img_colisao_ativada = window->load_model(img_escolha_especie, "models/buttons/v.png");
	img_colisao_ativada.set_scale(0.2, 0.0, 0.2);
	img_colisao_ativada.set_pos(28.0, 0.0, 0.0);

	//carregando botão x (de desativar colisão)
	img_colisao_desativada = window->load_model(img_escolha_especie, "models/buttons/x.png");
	img_colisao_desativada.set_scale(0.2, 0.0, 0.2);
	img_colisao_desativada.set_pos(28.0, 0.0, 0.0);

	if (collision::get_instance()->get_colisao()) {
		img_colisao_ativada.unstash();
		img_colisao_desativada.stash();
	}
	else {
		img_colisao_desativada.unstash();
		img_colisao_ativada.stash();
	}

	//o lagarto default é o LS_eurolophosaurus
	eurolophosaurus_action();

}

void CharacterOptionsScreen::show() {
	Screen::show();

	switch (Player::properties.species) {//mostrando especie q tava selecionada
		case Player::LS_tropidurus :
			tropidurus.unstash();
			break;
		case Player::LS_eurolophosaurus :
			eurolophosasurus.unstash();
			break;

		case Player::LS_cnemidophorus :
			cnemidophorus.unstash();
			break;
	}
}

void CharacterOptionsScreen::hide() {
	Screen::hide();

	switch (Player::properties.species) {//mostrando especie q tava selecionada
		case Player::LS_tropidurus :
			tropidurus.stash();
			break;
		case Player::LS_eurolophosaurus :
			eurolophosasurus.stash();
			break;

		case Player::LS_cnemidophorus :
			cnemidophorus.stash();
			break;
	}
}

/*! Evento de click no botão "Tropidurus". Seleciona a espécie Tropidurus. */
void CharacterOptionsScreen::tropidurus_action() {
	switch (Player::properties.species) {
		case Player::LS_cnemidophorus :
			cnemidophorus.stash();
			break;
		case Player::LS_eurolophosaurus :
			eurolophosasurus.stash();
			break;
	}
	Player::properties.species = Player::LS_tropidurus;
	marcador.set_pos(4.0, 0.0, -2.2); //movendo o marcador
	tropidurus.set_scale(0.04, 0.04, 0.04);
	tropidurus.set_pos(4, 35, -2);
	tropidurus.unstash();
}

/*! Evento de click no botão "Eurolophosaurus". Seleciona a espécie Eurolophosaurus. */
void CharacterOptionsScreen::eurolophosaurus_action() {
	switch (Player::properties.species) {
		case Player::LS_tropidurus :
			tropidurus.stash();
			break;
		case Player::LS_cnemidophorus :
			cnemidophorus.stash();
			break;
	}

	Player::properties.species = Player::LS_eurolophosaurus;
	marcador.set_pos(4.0, 0.0, -4.7); //movendo o marcador
	eurolophosasurus.set_scale(0.04, 0.04, 0.04);
	eurolophosasurus.set_pos(4, 35, -2);
	eurolophosasurus.unstash();
}

/*! Evento de click no botão "Cnemidophorus". Seleciona a espécie Cnemidophorus. */
void CharacterOptionsScreen::cnemidophorus_action() {
	switch (Player::properties.species) {
		case Player::LS_tropidurus :
			tropidurus.stash();
			break;
		case Player::LS_eurolophosaurus :
			eurolophosasurus.stash();
			break;
	}
	Player::properties.species = Player::LS_cnemidophorus;
	marcador.set_pos(4.0, 0.0, -7.2); //movendo o marcador
	cnemidophorus.set_scale(0.04, 0.04, 0.04);
	cnemidophorus.set_pos(4, 35, -2);
	cnemidophorus.unstash();
}

void CharacterOptionsScreen::colisao_action() {
    //se a colisão tiver ativada, então desativa agora
    if(collision::get_instance()->get_colisao()){
        img_colisao_ativada.stash();
        img_colisao_desativada.unstash();
        collision::get_instance()->set_colisao(false);
    }else
    { //se estiver desativada então ativa.
    	img_colisao_ativada.unstash();
    	img_colisao_desativada.stash();
        collision::get_instance()->set_colisao(true);
    }
}

void CharacterOptionsScreen::jogar_action() {
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());
	Simdunas::set_play_clicked(true);
	Session::get_instance()->set_level(1);
}

