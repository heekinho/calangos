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

IndicatorsScreen::~IndicatorsScreen() {
}

void IndicatorsScreen::load() {
	string imagem1 = ConfigVariableString("msg-imag1", "models/gui/teclasPortugues.png");

	img_indicadores = window->load_model(window->get_render_2d(), imagem1);
	img_indicadores.set_scale(0.1, 0.001, 0.15);
	img_indicadores.set_pos(0.0, 0.0, 0.0);

    configure_default_back_button(((CalangosMenuManager* ) manager.p())->get_instructions_screen());
}

void IndicatorsScreen::show() {
	Screen::show();
	img_indicadores.unstash();
}

void IndicatorsScreen::hide() {
	Screen::hide();
	img_indicadores.stash();
}
