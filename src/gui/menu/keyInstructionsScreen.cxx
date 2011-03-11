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

KeyInstructionsScreen::~KeyInstructionsScreen(){}

void KeyInstructionsScreen::load(){
	/////Carregando tela teclas
	img_teclas = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render_2d(), "models/gui/teclas.png");
	img_teclas.set_scale(0.1, 0.001, 0.17);
	img_teclas.set_pos(0.0, 0.0, 0.06);

	lb_teclas = new TextNode("inicio");
	lb_teclas->set_font(FontPool::load_font("models/ExpletiveDeleted.ttf"));
	lb_teclas->set_text("Teclas");

	np_lb_teclas = Simdunas::get_window()->get_aspect_2d().attach_new_node(lb_teclas);
	np_lb_teclas.set_scale(0.17);
	np_lb_teclas.set_pos(-1.2, 0, 0.35);
	np_lb_teclas.set_color(0.87, 0.72, 0.52);


	np_lb_teclas.set_pos(-0.3, 0.0, 0.85);
	//np_lb_teclas.set_color(0.0, 0.0, 0.0);
	//construindo o botão instruções

	PT(TextFont) font = manager->get_default_font();
	default_button_config(btn_voltar, np_btn_voltar, "<< Voltar", -0.9, voltar_action);
	np_btn_voltar.set_x(-0.9);
}

void KeyInstructionsScreen::unload() {
	img_teclas.remove_node();
	np_lb_teclas.remove_node();
	np_btn_voltar.remove_node();
	btn_voltar = NULL;
	lb_teclas = NULL;
}

/*! Configura um botão dado os parametros para este menu */
void KeyInstructionsScreen::default_button_config(PT(Button) button, NodePath &np,
		const string &text, float z, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, manager->get_default_font());
	np = get_root().attach_new_node(button);
	np.set_z(z);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
}

void KeyInstructionsScreen::show() {
	img_teclas.show();
	np_lb_teclas.show();
	np_btn_voltar.show();
}

void KeyInstructionsScreen::hide() {
	img_teclas.hide();
	np_lb_teclas.hide();
	np_btn_voltar.hide();
}

void KeyInstructionsScreen::voltar_action(){
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_instructions_screen());
}
