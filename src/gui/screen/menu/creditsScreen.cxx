/*
 * creditsScreen.cxx
 *
 *  Created on: Mar 1, 2011
 *      Author: jonatas
 */

#include "creditsScreen.h"
#include "simdunas.h"
#include "mouseButton.h"
#include "calangosMenuManager.h"

CreditsScreen::CreditsScreen(PT(ScreenManager) manager) : Screen(manager) {
	load();
	hide();
}

CreditsScreen::~CreditsScreen() {
}

void CreditsScreen::load() {
    img_credit = window->load_model(window->get_render_2d(), "models/apoio-creditos.jpg");
    img_credit.set_scale(0.12, 0.001, 0.15);
    img_credit.set_pos(0.0, 0.0, 0.06);

    configure_default_back_button(((CalangosMenuManager*) manager.p())->get_main_menu());
}

void CreditsScreen::show() {
	Screen::show();
	img_credit.unstash();
}

void CreditsScreen::hide() {
	Screen::hide();
	img_credit.stash();
}
