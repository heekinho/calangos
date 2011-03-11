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

CreditsScreen::~CreditsScreen() {}

void CreditsScreen::load() {
    img_credit = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render_2d(), "models/apoio-creditos.jpg");
    img_credit.set_scale(0.12, 0.001, 0.15);
    img_credit.set_pos(0.0, 0.0, 0.06);

    default_button_config(btn_voltar, np_btn_voltar, "<< Voltar", -0.9, voltar_action);
    np_btn_voltar.set_x(-0.9);
}

void CreditsScreen::unload() {
	img_credit.remove_node();
	np_btn_voltar.remove_node();
	btn_voltar = NULL;
}

/*! Configura um botão dado os parametros para este menu */
void CreditsScreen::default_button_config(PT(Button) button, NodePath &np,
		const string &text, float z, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, manager->get_default_font());
	np = get_root().attach_new_node(button);
	np.set_z(z);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
}

void CreditsScreen::show() {
	np_btn_voltar.show();
	img_credit.show();
}

void CreditsScreen::hide() {
	np_btn_voltar.hide();
	img_credit.hide();
}

void CreditsScreen::voltar_action() {
	CalangosMenuManager* menu_manager = (CalangosMenuManager*) manager.p();
	menu_manager->open_screen(menu_manager->get_main_menu());
}
