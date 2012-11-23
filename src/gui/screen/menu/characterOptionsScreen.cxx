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

	// nivel de dificuldade
	lb_nivel_dificuldade = new TextNode("lb_nivel_dificuldade");
	lb_nivel_dificuldade->set_text("Nível de Dificuldade");
	lb_nivel_dificuldade->set_font(manager->get_default_font());
	np_lb_nivel_dificuldade = get_root().attach_new_node(lb_nivel_dificuldade);
	np_lb_nivel_dificuldade.set_pos(-1.2, 0.0, 0.75);
	np_lb_nivel_dificuldade.set_scale(0.12);
	np_lb_nivel_dificuldade.set_color(1, 1, 1, 1, 0);

	lb_idade = new TextNode("lb_idade");
	lb_idade->set_text("Idade");
	lb_idade->set_font(manager->get_default_font());
	np_lb_idade = get_root().attach_new_node(lb_idade);
	np_lb_idade.set_pos(0.3, 0.0, 0.75);
	np_lb_idade.set_scale(0.13);
	np_lb_idade.set_color(1, 1, 1, 1, 0);

	default_button_config(btn_jovem, np_btn_jovem, "Jovem", LVecBase3f(0.55, 0, 0.55), jovem_action);
	default_button_config(btn_adulto, np_btn_adulto, "Adulto", LVecBase3f(0.55, 0, 0.4), adulto_action);

	// botões para escolha do nível de dificuldade
	default_button_config(btn_nivel_facil, np_btn_nivel_facil, "Fácil", LVecBase3f(-1.03, 0, 0.55), nivel_facil_action);
	default_button_config(btn_nivel_medio, np_btn_nivel_medio, "Médio", LVecBase3f(-1.0, 0, 0.4), nivel_medio_action);
	default_button_config(btn_nivel_dificil, np_btn_nivel_dificil, "Difícil", LVecBase3f(-1.0, 0, 0.25), nivel_dificil_action);

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
	lb_escolha_especie = new TextNode("lb_escolha_especie");
	lb_escolha_especie->set_text("Escolha da Espécie");
	lb_escolha_especie->set_font(manager->get_default_font());
	np_lb_escolha_especie = get_root().attach_new_node(lb_escolha_especie);
	np_lb_escolha_especie.set_pos(-1.2, 0.0, 0.03);
	np_lb_escolha_especie.set_scale(0.12);
	np_lb_escolha_especie.set_color(1, 1, 1, 1, 0);

	//carregando o marcador/////////
	marcador = window->load_model(img_escolha_especie, "models/buttons/marcador.png");
	marcador.set_scale(0.2, 0.0, 0.2);
	marcador.set_pos(4.0, 0.0, -4.7);

	///////Botões para escolha da especie/////////////////
	default_button_config(btn_tropidurus, np_btn_tropidurus, "Tropidurus psammonastes", LVecBase3f(-0.41, 0, -0.175), tropidurus_action);
	default_button_config(btn_eurolophosaurus, np_btn_eurolophosaurus, "Eurolophosaurus divaricatus", LVecBase3f(-0.33, 0, -0.325), eurolophosaurus_action);
	default_button_config(btn_cnemidophorus, np_btn_cnemidophorus, "Cnemidophorus sp. nov.", LVecBase3f(-0.5, 0, -0.475), cnemidophorus_action);

	//o lagarto default é o LS_eurolophosaurus
	eurolophosaurus_action();

	// o nível default é o fácil
	nivel_facil_action();

	// por default o lagarto começa como jovem
	jovem_action();

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
	tropidurus.set_pos(6, 35, -2);
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
	eurolophosasurus.set_pos(6, 35, -2);
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
	cnemidophorus.set_pos(6, 35, -2);
	cnemidophorus.unstash();
}

void CharacterOptionsScreen::jogar_action() {
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());
	Simdunas::set_play_clicked(true);
	Session::get_instance()->set_level(1);
}

void CharacterOptionsScreen::nivel_facil_action() {
	Session::get_instance()->set_difficulty_level(1);
}

void CharacterOptionsScreen::nivel_medio_action() {
	Session::get_instance()->set_difficulty_level(2);
}

void CharacterOptionsScreen::nivel_dificil_action() {
	Session::get_instance()->set_difficulty_level(3);
}

void CharacterOptionsScreen::jovem_action() {
	Session::get_instance()->set_is_adult(false);
}

void CharacterOptionsScreen::adulto_action() {
	Session::get_instance()->set_is_adult(true);
	//Player::properties.is_adult = true;
}

