/*
 * window.cxx
 *
 *  Created on: Nov 21, 2011
 *      Author: jonatas
 */

#include "window.h"
#include "fontPool.h"
#include "mouseButton.h"

//TODO implementar algum efeito para quando a janela abrir (tipo um fade).
Window::Window(NodePath parent, float width, float height, string title, float pos_x, float pos_y) {
	this->width = width;
	this->height = height;
	frame = new PGVirtualFrame("window");
	frame->setup(width, height);
	PGFrameStyle style = frame->get_frame_style(frame->get_state());
	style.set_type(PGFrameStyle::T_flat);
	frame->set_frame_style(frame->get_state(), style);
	frame->set_active(true);

	np_frame = NodePath(frame);
	np_frame.reparent_to(parent);
	np_frame.set_pos(pos_x, 0.0, pos_y);
	np_frame.set_transparency(TransparencyAttrib::M_alpha);
	np_frame.set_color(0.97, 0.945, 0.914, 0.85);

	header_frame = new PGVirtualFrame("window_header");
	header_frame->setup(width, 0.1);
	style.set_type(PGFrameStyle::T_flat);
	header_frame->set_frame_style(header_frame->get_state(), style);

	np_header_frame = NodePath(header_frame);
	np_header_frame.reparent_to(parent);
	np_header_frame.set_pos(pos_x, 0.0, height + pos_y);
	np_header_frame.set_color(1, 1, 1);

	header = new TextNode("header");
	header->set_text(title);
	header->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_header = np_header_frame.attach_new_node(header);
	np_header.set_scale(0.07);
	np_header.set_pos((width / 2.0) - (header->get_width() * np_header.get_sx() / 2.0), 0, (header->get_height() * np_header.get_sz() / 2) - 0.015);
	np_header.set_color(0, 0, 0, 1);

	btn_close = new Button("btn_close", ConfigVariableString("msg-fechar", "Fechar"), FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	event_handler->add_hook(btn_close->get_click_event(MouseButton::one()), close_action, this);
	np_btn_close = np_frame.attach_new_node(btn_close);
	np_btn_close.set_scale(0.6);
	np_btn_close.set_pos(width - 0.2, 0, 0.06);
}

Window::~Window() {
	simdunas_cat.debug()<<"Destruindo a window"<<endl;
	np_frame.remove_node();
	np_header_frame.remove_node();
	event_handler->remove_hooks_with(this);
}

void Window::close_action() {
	simdunas_cat.debug()<<"fechando a janela!"<<endl;
	np_frame.remove_node();
	np_header_frame.remove_node();
	event_handler->remove_hooks_with(this);
}

NodePath Window::get_np_frame() {
	return np_frame;
}

NodePath Window::get_np_header_frame() {
	return np_header_frame;
}

string Window::get_header() {
	return header->get_text();
}

void Window::set_header(string text) {
	header->set_text(text);
}

float Window::get_width() {
	return width;
}

void Window::set_width(float width) {
	frame->setup(width, height);
	header_frame->setup(width, 0.1);
}

float Window::get_height() {
	return height;
}

void Window::set_height(float height) {
	frame->setup(width, height);
}

float Window::get_pos_x() {
	return np_frame.get_x();
}

void Window::set_pos_x(float x) {
	np_frame.set_x(x);
}

float Window::get_pos_y() {
	return np_frame.get_y();
}

void Window::set_pos_y(float y) {
	np_frame.set_y(y);
}

/*! Configura um botão dado os parametros para este menu */
void Window::default_button_config(PT(Button) button, NodePath &np,
		const string &text, LVecBase3f pos, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, Simdunas::get_game_font(), 0.06);
	np = np_frame.attach_new_node(button);
	np.set_pos(pos);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	event_handler->add_hook(event_name, action, this);
}
