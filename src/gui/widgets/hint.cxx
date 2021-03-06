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

/*!
 * Primeiro construtor criado para o Hint. Ele foi criado inicialmente pensando em ser apenas para imagens, contudo,
 * foi necessário usá-lo depois também para botões e TextNodes, que demandaram a criação de construtores específicos.
 * O funcionamento é feito através de um botão invisível, que assumirá o mesmo tamanho e posicionamento da imagem.
 * Dessa forma, ele servirá para capturar os eventos de quando o mouse passar sobre a imagem e quando sair de cima da imagem.
 *
 * @param parent NodePath ao qual o hint será vinculado (parent.attach_new_node)
 * @param reference_node NodePath da imagem sobre a qual deseja-se exibir o hint. Usado como referência para posicionar o hint
 * @param name Nome passado ao construtor do PGBUtton
 * @param msg Mensagem que será exibida
 */
Hint::Hint(NodePath parent, NodePath reference_node, string name, string msg) {
	np_reference = reference_node;
	btn = new PGButton(name); // botão invisível
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

/*!
 * Construtor criado para o uso do Hint em TextNodes, pois com eles é prático passar as dimensões,
 * além do ponto principal ficar na esquerda, diferentemente das imagens que ficam no meio.
 *
 * @param parent NodePath ao qual o hint será vinculado (parent.attach_new_node)
 * @param reference_node NodePath do TextNode sobre a qual deseja-se exibir o hint. Usado como referência para posicionar o hint
 * @param width Largura do TextNode
 * @param height Altura do TextNode
 * @param name Nome passado ao construtor do PGBUtton
 * @param msg Mensagem que será exibida
 */
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

/*!
 * Construtor criado para o uso em botões. Dessa forma fica mais fácil, pois não se faz necessário o uso de um
 * botão invisível.
 *
 * @param parent NodePath ao qual o hint será vinculado (parent.attach_new_node)
 * @param hintable_btn Ponteiro para o botão sobre o qual deseja-se exibir o hint.
 * @param reference_node NodePath do botão. Usado como referência para posicionar o hint
 * @param name Nome passado ao construtor do PGBUtton
 * @param msg Mensagem que será exibida
 */
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

/*! Coloca o hint para pertencer a um novo TextNode */
void Hint::change_text_reference(NodePath np_text, float width, float height) {
	//btn->setup(np_text);
	this->width = width;
	this->height = height;
	np_btn.set_scale(np_text.get_scale());
	np_btn.set_pos(np_text.get_x(), np_text.get_y(), np_text.get_z());
	btn->set_frame(0, width, -height/2, height/2);
}

/*! Coloca o hint para pertencer a uma nova imagem */
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

/*! Coloca o hint para pertencer a um novo botão  */
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

/*! Constrói o "balão" com a mensagem. */
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
	np_text.stash();

	event_handler->add_hook(btn->get_enter_event(), enter_event, this);
	event_handler->add_hook(btn->get_exit_event(), exit_event, this);
}

Hint::~Hint() {
	np_btn.remove_node();
	np_text.remove_node();
	btn = NULL;
	text = NULL;
	event_handler->remove_hooks_with(this);
}

/*! Evento de quando o mouse passa por cima do botão invisível. Programa o hint para ser exibido após 1 segundo. */
void Hint::enter_event(const Event*, void *data) {
	if (data == NULL) return;
	Hint* _this = (Hint*) data;
	if (_this->btn == NULL || _this->text == NULL) return;
	TimeControl::get_instance()->notify("show_hint", show_hint, data, 1);
	_this->mouse_in = true;
}

/*! Exibe o hint um pouco acima e centralizado em relação ao ponteiro do mouse.  */
AsyncTask::DoneStatus Hint::show_hint(GenericAsyncTask* task, void* data) {
	if (data == NULL) {
		return AsyncTask::DS_done;
	}

	Hint* _this = (Hint*) data;

	if (_this->btn == NULL || _this->text == NULL) {
		return AsyncTask::DS_done;
	}

	if ((_this->np_reference.is_empty() && _this->np_reference.get_hidden_ancestor().is_empty()) || _this->np_reference.is_hidden() || _this->np_reference.is_stashed()) {
		return AsyncTask::DS_done;
	}
	PT(MouseWatcher) mwatcher = DCAST(MouseWatcher, window->get_mouse().node());
	if (!mwatcher->has_mouse()) {
		return AsyncTask::DS_done;
	}

	float mouse_x = mwatcher->get_mouse_x();
	float mouse_y = mwatcher->get_mouse_y();

	if (_this->btn == NULL || _this->text == NULL) return AsyncTask::DS_done;
	if (!_this->mouse_in) {
		return AsyncTask::DS_done;
	}

	if (_this->btn == NULL || _this->text == NULL) return AsyncTask::DS_done;

	float aspect_ratio = Simdunas::get_pixel_2d()->get_aspect_ratio();
	if (_this->btn == NULL || _this->text == NULL) return AsyncTask::DS_done;
	float half_text_size = _this->text->get_width() * _this->np_text.get_sx() / 2;
	_this->np_text.set_pos((mouse_x * aspect_ratio) - half_text_size, 0, mouse_y + 0.03);
	LPoint3f min, max;
	_this->np_text.calc_tight_bounds(min, max);

	if (_this->btn == NULL || _this->text == NULL) return AsyncTask::DS_done;

	if (max.get_x() > aspect_ratio) { // o balão passou da tela e precisará ser movido para a esquerda
		float offset_left = max.get_x() - aspect_ratio + half_text_size + 0.01;
		_this->np_text.set_pos(mouse_x * aspect_ratio - offset_left, 0, mouse_y + 0.03);
	}
	else if (min.get_x() < -aspect_ratio) { // o balão passou da tela e precisará ser movido para a direita
		float offset_right = min.get_x() + aspect_ratio + half_text_size * 0.8;
		_this->np_text.set_pos(mouse_x * aspect_ratio - offset_right, 0, mouse_y + 0.03);
	}

	_this->np_text.unstash();

	return AsyncTask::DS_done;
}

/*! Evento de quando o mouse sai de cima do botão invisível. Oculta o hint. */
void Hint::exit_event(const Event*, void *data) {
	if (data == NULL) return;

	Hint* _this = (Hint*) data;

	if (_this->btn == NULL || _this->text == NULL) return;

	_this->np_text.stash();
	_this->mouse_in = false;
}

void Hint::set_message(string msg) {
	text->set_text(msg);
}
