/*
 *  screen.h
 *  Created on: 19/02/2011
 *  Author: heekinho
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "referenceCount.h"
#include "pandaFramework.h"

#include "mouseButton.h"
#include "button.h"
#include "event.h"

typedef void EventCallbackFunction(const Event *, void *);

class ScreenManager;

/*! Lida com as Screens (Menus) do sistema do jogo. */
class Screen : public ReferenceCount {
public:
	Screen(PT(ScreenManager) manager);
	~Screen();

	virtual void show();
	virtual void hide();

	/*! É chamado geralmente no método create_menu de algum manager */
	virtual void load() = 0;
	/*! É chamado geralmente quando um certo manager não é mais necessário */
	virtual void unload() = 0;

	NodePath get_root();

	static void configure_component(NodePath &np,
		const LVecBase3f &size = LVecBase3f(1), const LPoint3f &pos = LPoint3f(0),
		const LVecBase3f &hpr = LVector3f(0), const Colorf &color = Colorf(1));

	void default_button_config(PT(Button) button, NodePath &np,
			const string &text, LVecBase3f pos, EventCallbackFunction *action);

	PT(Screen)  get_previous_screen();
	void set_previous_screen(PT(Screen) previous);
	static void back_action(const Event*, void* data);
	void configure_default_back_button(PT(Screen) previous);

protected:
	NodePath root;
	PT(ScreenManager) manager;
	PT(Screen) previous;

	NodePath np_btn_back;
	PT(Button) btn_back;
};

#endif