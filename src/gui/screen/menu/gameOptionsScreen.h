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

	PT(TextNode) lb_opcoes_de_audio;	NodePath np_lb_opcoes_de_audio;

	PT(TextNode) lb_efeitos_sonoros;	NodePath np_lb_efeitos_sonoros;
	PT(PGButton) btn_mais_2;			NodePath np_btn_mais_2;			NodePath img_btn_mais_2;		ACTION(increase_volume_action);
	PT(PGButton) btn_menos_2;			NodePath np_btn_menos_2;		NodePath img_btn_menos_2;		ACTION(decrease_volume_action);
	PT(PGSliderBar) slide_2;			NodePath np_slide_2;											ACTION(slide_action_2);

	PT(TextNode) lb_musicas;			NodePath np_lb_musicas;
	PT(PGButton) btn_mais_3;			NodePath np_btn_mais_3;			NodePath img_btn_mais_3;		ACTION(increase_volume_action_2);
	PT(PGButton) btn_menos_3;			NodePath np_btn_menos_3;		NodePath img_btn_menos_3;		ACTION(decrease_volume_action_2);
	PT(PGSliderBar) slide_3;			NodePath np_slide_3;											ACTION(slide_action_3);

	PT(PGButton) btn_bgm_enabled;		NodePath np_btn_bgm_enabled;		NodePath img_btn_bgm_enabled;	ACTION(enable_bgm);
	PT(PGButton) btn_bgm_disabled;		NodePath np_btn_bgm_disabled;		NodePath img_btn_bgm_disabled;	ACTION(disable_bgm);
	PT(PGButton) btn_sfx_enabled;		NodePath np_btn_sfx_enabled;		NodePath img_btn_sfx_enabled;	ACTION(disable_sfx);
	PT(PGButton) btn_sfx_disabled;		NodePath np_btn_sfx_disabled;		NodePath img_btn_sfx_disabled;	ACTION(enable_sfx);

	PT(TextNode) lb_colisao;			NodePath np_lb_colisao;				ACTION(colisao_action);
	PT(PGButton) btn_colisao_ativada;	NodePath np_btn_colisao_ativada;	NodePath img_btn_colisao_ativada;
	PT(PGButton) btn_colisao_desativada;NodePath np_btn_colisao_desativada;	NodePath img_btn_colisao_desativada;

	PT(TextNode) lb_configuracoes_jogo;	NodePath np_lb_configuracoes_jogo;
	PT(TextNode) lb_relogio_virtual;	NodePath np_lb_relogio_virtual;

	PT(TextNode) lb_frase_relogio;		NodePath np_lb_frase_relogio;

	PT(Button) btn_instructions; 	NodePath np_instructions;	ACTION(instructions_action);
};

#undef ACTION

#endif /* GAMEOPTIONSSCREEN_H */
