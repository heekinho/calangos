/*
 * keyInstructionsWindow.cxx
 *
 *  Created on: Nov 18, 2013
 *      Author: eduardo
 */

#include "keyInstructionsWindow.h"
#include "imageRepository.h"
#include "fontPool.h"
#include "mouseButton.h"
#include "simdunas.h"
#include "inGameScreenManager.h"
#include "pauseScreen.h"

KeyInstructionsWindow::KeyInstructionsWindow(NodePath parent, float width, float height, string title, float pos_x, float pos_y) : Window(parent, width, height, title, pos_x, pos_y) {

	//load(parent);
	//hide();

	// Substituir a herança de Window para Screen. Inserir um botão "Fechar" para esconder a imagem, ou seja, chamar o método hide()

	//img_teclas = window->load_model(parent, "models/gui/teclas.png");
	//img_teclas.set_scale(0.075, 0.0004, 0.06);
	//img_teclas.set_pos(0.0, 0.0, 0.0);

	img_teclas = ImageRepository::get_instance()->get_image("teclas_traduzidas");
	img_teclas.reparent_to(np_frame);
	img_teclas.set_scale(0.09);
	img_teclas.set_pos(1, 0.0, 0.75);
//	lb_teclas = new Text("lb_teclas", "Teclas", np_frame, TextNode::get_default_font(), 0.05);
//
//	np_lb_teclas = get_root().attach_new_node(lb_teclas);
//	np_lb_teclas.set_scale(0.17);
//	np_lb_teclas.set_pos(-1.2, 0, 0.35);

}

KeyInstructionsWindow::~KeyInstructionsWindow() {

}

void KeyInstructionsWindow::load(NodePath parent) {
	//img_teclas = window->load_model(parent, "models/gui/teclas.png");
	//img_teclas.set_scale(0.075, 0.0004, 0.06);
	//img_teclas.set_pos(0.0, 0.0, 0.0);
}

void KeyInstructionsWindow::hide() {
	img_teclas.stash();
}
