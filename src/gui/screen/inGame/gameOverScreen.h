/*
 *  gameOverScreen.h
 *  Created on: 09/05/2011
 *  Author: jonatas
 */

#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "screenManager.h"
#include "screen.h"
#include "button.h"
#include "pgVirtualFrame.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(GameOverScreen))(GameOverScreen*)d)->mn(); }

class GameOverScreen : public Screen {
public:
	GameOverScreen(PT(ScreenManager) manager);
	~GameOverScreen();

	void load();
	void unload();
	void show();

	static void restart(const Event*, void* data);

private:
	PT(PGVirtualFrame) frame_tela;
	NodePath np_frame_tela;
	NodePath logo;
	NodePath indica_morte;
	PT(Button) btn_restart;
	NodePath np_btn_restart;
	PT(PGButton) btn_graph;
	enum Causa_Mortis {
	        DESNUTRICAO = 1, DESIDRATACAO, ALTA_TEMPERATURA, BAIXA_TEMPERATURA, MORTE_IDADE
	};
};

#undef ACTION

#endif
