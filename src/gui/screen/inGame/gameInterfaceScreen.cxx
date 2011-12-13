/*
 * gameInterfaceScreen.cxx
 *
 *  Created on: Nov 30, 2011
 *      Author: jonatas
 */

#include "gameInterfaceScreen.h"
#include "simdunas.h"
#include "guiLayer.h"
#include "fontPool.h"
#include "achievementsWindow.h"

GameInterfaceScreen::GameInterfaceScreen(PT(ScreenManager) manager) : Screen(manager) {
	set_root(clickable_render2d);
	load();
	hide();
}

GameInterfaceScreen::~GameInterfaceScreen() {}

void GameInterfaceScreen::load() {
	btn_realizacoes = new Button("btn_realizacoes", "Realizações", FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	event_handler->add_hook(btn_realizacoes->get_click_event(MouseButton::one()), show_realizacoes_action, this);
	np_btn_realizacoes = get_root().attach_new_node(btn_realizacoes);
	np_btn_realizacoes.set_scale(0.5);
	np_btn_realizacoes.set_pos(-0.8, 0, 0.87);
}

void GameInterfaceScreen::unload() {
	btn_realizacoes = NULL;
	np_btn_realizacoes.remove_node();
}

void GameInterfaceScreen::show() {
	np_btn_realizacoes.show();
}

void GameInterfaceScreen::hide() {
	np_btn_realizacoes.hide();
}

void GameInterfaceScreen::show_realizacoes_action() {
	//wnd_realizacoes = new Window(get_root(), 1.5, 1, "Realizações");
	wnd_realizacoes = new AchievementsWindow(get_root(), 1.5, 1, "Realizações");
}
