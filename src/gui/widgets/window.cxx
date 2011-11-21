/*
 * window.cxx
 *
 *  Created on: Nov 21, 2011
 *      Author: jonatas
 */

#include "window.h"

//TODO gets e sets.
//TODO header
//TODO efeito ao abrir
//TODO padronizar forma de fechar
Window::Window(NodePath parent, float width, float height, string name) {
	frame = new PGVirtualFrame(name);
	frame->setup(width, height);
	PGFrameStyle style = frame->get_frame_style(frame->get_state());
	style.set_type(PGFrameStyle::T_flat);
	frame->set_frame_style(frame->get_state(), style);

	frame_np = NodePath(frame);
	frame_np.reparent_to(parent);
	//Seta a posição do frame
	frame_np.set_pos(-0.8, 0.0, -0.8);
	//Seta a cor do frame
	frame_np.set_color(0.97, 0.945, 0.914);
}

Window::~Window() {}
