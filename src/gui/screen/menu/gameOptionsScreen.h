/*
 * gameOptionsScreen.h
 *
 *  Created on: Mar 6, 2011
 *      Author: jonatas
 */

#ifndef GAMEOPTIONSSCREEN_H
#define GAMEOPTIONSSCREEN_H

#include "pandaFramework.h"
#include "screenManager.h"
#include "screen.h"
#include "button.h"
#include "player.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(GameOptionsScreen))(GameOptionsScreen*)d)->mn(); }

class GameOptionsScreen : public Screen {
public:
	GameOptionsScreen(PT(ScreenManager) manager);
	virtual ~GameOptionsScreen();

	void load();
	void show();
	void hide();

	void informa_segundos(string aviso);

private:
	NodePath img_titulo;
	float ratio;
	NodePath img_tempo;
	NodePath img_frase_relogio;
	NodePath np_slide;
	PT(TextNode) lb_num_minutos;
	NodePath np_lb_num_minutos;
	bool showing_custom;
	PT(PGSliderBar) slide;																						ACTION(slide_action);
	PT(PGButton) btn_mais;				NodePath np_btn_mais;				NodePath img_btn_mais;				ACTION(slide_direita_action);
	PT(PGButton) btn_menos;				NodePath np_btn_menos;				NodePath img_btn_menos;				ACTION(slide_esquerda_action);
};

#undef ACTION

#endif /* GAMEOPTIONSSCREEN_H */
