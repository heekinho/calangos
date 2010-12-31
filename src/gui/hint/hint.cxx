/*
 * hint.cxx
 *
 *  Created on: Nov 26, 2010
 *      Author: jonatas
 */

#include "hint.h"
#include "simdunas.h"
#include "imageRepository.h"
#include "timeControl.h"

/*
 * - parent = NodePath ao qual o hint será vinculado (parent.attach_new_node)
 * - reference_node = NodePath usado como referência para posicionar o hint
 * - name = Nome passado ao construtor do PGBUtton
 * - msg = Mensagem que será exibida
 */
Hint::Hint(NodePath parent, NodePath reference_node, string name, string msg) {
	btn = new PGButton(name);
	np_btn = parent.attach_new_node(btn);
	np_btn.set_scale(reference_node.get_scale());
	np_btn.set_pos(reference_node.get_x(), reference_node.get_y(), reference_node.get_z());
	LPoint3f min, max, size;
	reference_node.calc_tight_bounds(min, max);
	size = (max-min);
	width = size.get_x()/reference_node.get_sx();
	height = size.get_z()/reference_node.get_sz();
	btn->set_frame(-width/2, width/2, -height/2, height/2);

	text = new TextNode("text");
	text->set_text(msg);

	text->set_card_actual(-0.3, text->get_width() + 0.35, -(text->get_height() / 2) + 0.18, text->get_height() - 0.24);
	text->set_card_color(1, 1, 1, 1);

	text->set_frame_actual(-0.3, text->get_width() + 0.35, -(text->get_height() / 2) + 0.18, text->get_height() - 0.24);
	text->set_frame_color(0, 0, 0, 1);

	np_text = Simdunas::get_window()->get_aspect_2d().attach_new_node(text);
	np_text.set_scale(0.04);
	np_text.set_color(0.0, 0.0, 0.0, 1,0);
	np_text.hide();

	Simdunas::get_evt_handler()->add_hook(btn->get_enter_event(), enter_event, this);
	Simdunas::get_evt_handler()->add_hook(btn->get_exit_event(), exit_event, this);
}

Hint::~Hint() {

}

void Hint::enter_event(const Event*, void *data) {
	Hint* _this = (Hint*) data;
	TimeControl::get_instance()->notify_after_n_seconds(1, Hint::show_hint, _this);
}

void Hint::show_hint(const Event* evt, void *data) {
	TimeControl::get_instance()->get_p_handler()->remove_hook(evt->get_name(), Hint::show_hint, data);

	Hint* _this = (Hint*) data;
	MouseWatcher *mwatcher = DCAST(MouseWatcher, Simdunas::get_window()->get_mouse().node());
	if (!mwatcher->has_mouse()) {
		return;
	}

	float mouse_x = mwatcher->get_mouse_x();
	float mouse_y = mwatcher->get_mouse_y();
	float pos_x = _this->np_btn.get_pos().get_x() + 0.58;
	float pos_z = _this->np_btn.get_pos().get_z() - 1;
	float s_width = _this->width * _this->np_btn.get_sx(); // width com a escala.
	float s_height = _this->height * _this->np_btn.get_sy(); // height com a escala.

	// verifica se ainda está com o mouse sobre a imagem
	if (!((mouse_x >= pos_x - (s_width / 2) && mouse_x <= pos_x + (s_width / 2))
			&& (mouse_y >= pos_z - (s_height / 2) && mouse_y <= pos_z + (s_height / 2)))) {
		return;
	}

	_this->np_text.set_pos(mwatcher->get_mouse_x(), 0, mwatcher->get_mouse_y() + 0.03);
	LPoint3f min, max;
	_this->np_text.calc_tight_bounds(min, max);

	if (max.get_x() > 1) { // o balão passou da tela e precisará recuar para a esquerda
		float offset_left = max.get_x() - 1 + 0.01;
		_this->np_text.set_pos(mwatcher->get_mouse_x() - offset_left, 0, mwatcher->get_mouse_y() + 0.03);
	}

	_this->np_text.show();
}

void Hint::exit_event(const Event*, void *data) {
	Hint* _this = (Hint*) data;
	_this->np_text.hide();
}
