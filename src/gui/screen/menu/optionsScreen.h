/*
 *  optionsScreen.h
 *  Created on: 05/03/2011
 *  Author: jonatas
 */

#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "screenManager.h"
#include "screen.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(OptionsScreen))(OptionsScreen*)d)->mn(); }

class OptionsScreen : public Screen {
public:
	OptionsScreen(PT(ScreenManager) manager);
	~OptionsScreen();

	void load();
	void unload();
	void show();
	void hide();

private:

	/* Componentes do Menu */
	PT(TextNode) lb_titulo;		NodePath np_lb_titulo;
	PT(Button) btn_video; 		NodePath np_btn_video;		 ACTION(video_action);
	PT(Button) btn_audio; 		NodePath np_btn_audio;	 	 ACTION(audio_action);
	PT(Button) btn_controles; 	NodePath np_btn_controles;	 ACTION(controles_action);
	PT(Button) btn_jogo; 		NodePath np_btn_jogo;		 ACTION(jogo_action);
	PT(Button) btn_voltar; 		NodePath np_btn_voltar;		 ACTION(voltar_action);
};

#undef ACTION

#endif
