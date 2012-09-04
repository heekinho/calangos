/*
 *  audioOptionsScreen.h
 *  Created on: Oct 19, 2011
 *  Author: jonatas
 */

#ifndef AUDIOOPTIONSSCREEN_H
#define AUDIOOPTIONSSCREEN_H

#include "screenManager.h"
#include "screen.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(AudioOptionsScreen))(AudioOptionsScreen*)d)->mn(); }

class AudioOptionsScreen : public Screen {
public:
	AudioOptionsScreen(PT(ScreenManager) manager);
	~AudioOptionsScreen();

	void load();

private:

	/* Componentes do Menu */
	PT(TextNode) lb_titulo;				NodePath np_lb_titulo;
	PT(TextNode) lb_efeitos_sonoros;	NodePath np_lb_efeitos_sonoros;
	PT(PGButton) btn_mais;				NodePath np_btn_mais;			NodePath img_btn_mais;			ACTION(increase_volume_action);
	PT(PGButton) btn_menos;				NodePath np_btn_menos;			NodePath img_btn_menos;			ACTION(decrease_volume_action);
	PT(PGSliderBar) slide;				NodePath np_slide;												ACTION(slide_action);

	PT(TextNode) lb_musicas;			NodePath np_lb_musicas;
	PT(PGButton) btn_mais_2;			NodePath np_btn_mais_2;			NodePath img_btn_mais_2;		ACTION(increase_volume_action_2);
	PT(PGButton) btn_menos_2;			NodePath np_btn_menos_2;		NodePath img_btn_menos_2;		ACTION(decrease_volume_action_2);
	PT(PGSliderBar) slide_2;			NodePath np_slide_2;											ACTION(slide_action_2);

	PT(PGButton) btn_bgm_enabled;		NodePath np_btn_bgm_enabled;		NodePath img_btn_bgm_enabled;	ACTION(enable_bgm);
	PT(PGButton) btn_bgm_disabled;		NodePath np_btn_bgm_disabled;		NodePath img_btn_bgm_disabled;	ACTION(disable_bgm);
	PT(PGButton) btn_sfx_enabled;		NodePath np_btn_sfx_enabled;		NodePath img_btn_sfx_enabled;	ACTION(disable_sfx);
	PT(PGButton) btn_sfx_disabled;		NodePath np_btn_sfx_disabled;		NodePath img_btn_sfx_disabled;	ACTION(enable_sfx);
};

#undef ACTION

#endif
