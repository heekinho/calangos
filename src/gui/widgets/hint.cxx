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
#include "mouseWatcher.h"

/*
 * - parent = NodePath ao qual o hint será vinculado (parent.attach_new_node)
 * - reference_node = NodePath usado como referência para posicionar o hint
 * - name = Nome passado ao construtor do PGBUtton
 * - msg = Mensagem que será exibida
 */
Hint::Hint(NodePath parent, NodePath reference_node, string name, string msg) {
	np_reference = reference_node;
	btn = new PGButton(name);
	btn->setup(reference_node);
	np_btn = parent.attach_new_node(btn);
	np_btn.set_scale(reference_node.get_scale());
	np_btn.set_pos(reference_node.get_x(), reference_node.get_y(), reference_node.get_z());
	LPoint3f min, max, size;
	reference_node.calc_tight_bounds(min, max);
	size = (max-min);
	width = size.get_x()/reference_node.get_sx();
	height = size.get_z()/reference_node.get_sz();
	btn->set_frame(-width/2, width/2, -height/2, height/2);

	buildHint(msg);
}

// Construtor criado para o uso do Hint em TextNodes, pois com eles é prático passar as dimensões
// e o ponto principal fica à esquerda, diferentemente das imagens que ficam no meio.
Hint::Hint(NodePath parent, NodePath reference_node, float width, float height, string name, string msg) {
	np_reference = reference_node;
	this->width = width;
	this->height = height;
	btn = new PGButton(name);
	//btn->setup(reference_node);
	np_btn = parent.attach_new_node(btn);
	np_btn.set_scale(reference_node.get_scale());
	np_btn.set_pos(reference_node.get_x(), reference_node.get_y(), reference_node.get_z());
	btn->set_frame(0, width, -height/2, height/2);

	buildHint(msg);
}

Hint::Hint(NodePath parent, PGButton* hintable_btn, NodePath reference_node, string name, string msg) {
	np_reference = reference_node;
	btn = hintable_btn;
	np_btn = reference_node;
	LPoint3f min, max, size;
	reference_node.calc_tight_bounds(min, max);
	size = (max-min);
	width = size.get_x()/reference_node.get_sx();
	height = size.get_z()/reference_node.get_sz();
	buildHint(msg);
}

void Hint::change_text_reference(NodePath np_text, float width, float height) {
	//btn->setup(np_text);
	this->width = width;
	this->height = height;
	np_btn.set_scale(np_text.get_scale());
	np_btn.set_pos(np_text.get_x(), np_text.get_y(), np_text.get_z());
	btn->set_frame(0, width, -height/2, height/2);
}

void Hint::change_img_reference(NodePath np_img) {
	//btn->setup(reference_node);
	np_btn.set_scale(np_img.get_scale());
	np_btn.set_pos(np_img.get_x(), np_img.get_y(), np_img.get_z());
	LPoint3f min, max, size;
	np_img.calc_tight_bounds(min, max);
	size = (max-min);
	width = size.get_x()/np_img.get_sx();
	height = size.get_z()/np_img.get_sz();
	btn->set_frame(-width/2, width/2, -height/2, height/2);
}

void Hint::change_btn_reference(PGButton* hintable_btn, NodePath reference_node) {
	np_reference = reference_node;
	btn = hintable_btn;
	np_btn = reference_node;
	LPoint3f min, max, size;
	reference_node.calc_tight_bounds(min, max);
	size = (max-min);
	width = size.get_x()/reference_node.get_sx();
	height = size.get_z()/reference_node.get_sz();
}

void Hint::buildHint(string msg) {
	text = new TextNode("text");
	text->set_text(msg);

	float text_width = text->get_width();
	float text_height = text->get_height();
	text->set_card_actual(-0.3, text_width + 0.35, -(text_height / 2 - 0.14), text_height - 0.14);
	text->set_card_color(1, 1, 1, 1);

	text->set_frame_actual(-0.3, text_width + 0.35, -(text_height / 2 - 0.14), text_height - 0.14);
	text->set_frame_color(0, 0, 0, 1);

	np_text = aspect2d.attach_new_node(text);
	np_text.set_scale(0.04);
	np_text.set_color(0.0, 0.0, 0.0, 1,0);
	np_text.hide();

	event_handler->add_hook(btn->get_enter_event(), enter_event, this);
	event_handler->add_hook(btn->get_exit_event(), exit_event, this);
}

Hint::~Hint() {

}

void Hint::enter_event(const Event*, void *data) {
	Hint* _this = (Hint*) data;
	TimeControl::get_instance()->notify("show_hint", show_hint, data, 1);
	_this->mouse_in = true;
}

AsyncTask::DoneStatus Hint::show_hint(GenericAsyncTask* task, void* data) {
	Hint* _this = (Hint*) data;
	if (_this->np_reference.is_hidden()) {
		return AsyncTask::DS_done;
	}
	PT(MouseWatcher) mwatcher = DCAST(MouseWatcher, window->get_mouse().node());
	if (!mwatcher->has_mouse()) {
		return AsyncTask::DS_done;
	}

	float mouse_x = mwatcher->get_mouse_x();
	float mouse_y = mwatcher->get_mouse_y();

	if (!_this->mouse_in) {
		return AsyncTask::DS_done;
	}

	float aspect_ratio = Simdunas::get_pixel_2d()->get_aspect_ratio();
	float half_text_size = _this->text->get_width() * _this->np_text.get_sx() / 2;
	_this->np_text.set_pos((mouse_x * aspect_ratio) - half_text_size, 0, mouse_y + 0.03);
	LPoint3f min, max;
	_this->np_text.calc_tight_bounds(min, max);

	if (max.get_x() > aspect_ratio) { // o balão passou da tela e precisará recuar para a esquerda
		float offset_left = max.get_x() - aspect_ratio + half_text_size + 0.01;
		_this->np_text.set_pos(mouse_x * aspect_ratio - offset_left, 0, mouse_y + 0.03);
	}
	else if (min.get_x() < -aspect_ratio) {
		float offset_right = min.get_x() + aspect_ratio + half_text_size * 0.8;
		_this->np_text.set_pos(mouse_x * aspect_ratio - offset_right, 0, mouse_y + 0.03);
	}

	_this->np_text.show();

	return AsyncTask::DS_done;
}

void Hint::exit_event(const Event*, void *data) {
	Hint* _this = (Hint*) data;
	_this->np_text.hide();
	_this->mouse_in = false;
}

void Hint::set_message(string msg) {
	text->set_text(msg);
}
