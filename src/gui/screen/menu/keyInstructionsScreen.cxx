/*
 *  keyInstructionsScreen.cxx
 *  Created on: 05/03/2011
 *  Author: jonatas
 */

#include "keyInstructionsScreen.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"
#include "calangosMenuManager.h"

/*! O menu é carregado e escondido. O manager é responsável por escolher o menu */
KeyInstructionsScreen::KeyInstructionsScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

KeyInstructionsScreen::~KeyInstructionsScreen() {
}

void KeyInstructionsScreen::load(){
	/////Carregando tela teclas
	img_teclas = window->load_model(window->get_render_2d(), "models/gui/teclas.png");
	img_teclas.set_scale(0.1, 0.001, 0.17);
	img_teclas.set_pos(0.0, 0.0, 0.06);

	lb_teclas = new TextNode("inicio");
	lb_teclas->set_font(FontPool::load_font("models/ExpletiveDeleted.ttf"));
	lb_teclas->set_text("Teclas");

	np_lb_teclas = get_root().attach_new_node(lb_teclas);
	np_lb_teclas.set_scale(0.17);
	np_lb_teclas.set_pos(-1.2, 0, 0.35);
	np_lb_teclas.set_color(0.87, 0.72, 0.52);


	np_lb_teclas.set_pos(-0.3, 0.0, 0.85);
	//np_lb_teclas.set_color(0.0, 0.0, 0.0);
	//construindo o botão instruções

	configure_default_back_button(((CalangosMenuManager*)(manager.p()))->get_instructions_screen());
}

void KeyInstructionsScreen::show() {
	Screen::show();
	img_teclas.unstash();
}

void KeyInstructionsScreen::hide() {
	Screen::hide();
	img_teclas.stash();
}
