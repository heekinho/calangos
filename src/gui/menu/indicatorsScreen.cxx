/*
 * indicatorsScreen.cxx
 *
 *  Created on: Mar 6, 2011
 *      Author: jonatas
 */

#include "indicatorsScreen.h"
#include "simdunas.h"
#include "mouseButton.h"
#include "calangosMenuManager.h"

IndicatorsScreen::IndicatorsScreen(PT(ScreenManager) manager) : Screen(manager) {
	load();
	hide();
}

IndicatorsScreen::~IndicatorsScreen() {}

void IndicatorsScreen::load() {
	img_indicadores = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render_2d(), "models/gui/icones.png");
	img_indicadores.set_scale(0.1, 0.001, 0.15);
	img_indicadores.set_pos(0.0, 0.0, 0.0);

    default_button_config(btn_voltar, np_btn_voltar, "<< Voltar", -0.9, voltar_action);
    np_btn_voltar.set_x(-0.9);
}

void IndicatorsScreen::unload() {
	img_indicadores.remove_node();
	np_btn_voltar.remove_node();
	btn_voltar = NULL;
}

void IndicatorsScreen::show() {
	np_btn_voltar.show();
	img_indicadores.show();
}

void IndicatorsScreen::hide() {
	np_btn_voltar.hide();
	img_indicadores.hide();
}

void IndicatorsScreen::voltar_action() {
	CalangosMenuManager* menu_manager = (CalangosMenuManager*) manager.p();
	menu_manager->open_screen(menu_manager->get_instructions_screen());
}
