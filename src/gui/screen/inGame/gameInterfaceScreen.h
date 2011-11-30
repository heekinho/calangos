/*
 * gameInterfaceScreen.h
 *
 *  Created on: Nov 30, 2011
 *      Author: jonatas
 */

#ifndef GAMEINTERFACESCREEN_H
#define GAMEINTERFACESCREEN_H

#include "pandaFramework.h"
#include "button.h"
#include "screenManager.h"
#include "screen.h"
#include "window.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(GameInterfaceScreen))(GameInterfaceScreen*)d)->mn(); }

class GameInterfaceScreen : public Screen {
public:
	GameInterfaceScreen(PT(ScreenManager) manager);
	virtual ~GameInterfaceScreen();

	void load();
	void unload();
	void show();
	void hide();

private:
	PT(Button) btn_realizacoes;		NodePath np_btn_realizacoes;	ACTION(show_realizacoes_action);
	PT(Window) wnd_realizacoes;
};

#undef ACTION

#endif /* GAMEINTERFACESCREEN_H */
