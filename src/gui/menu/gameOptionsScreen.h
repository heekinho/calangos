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
	void unload();
	void show();
	void hide();

	Player::lizardEpecie get_especie();

	void informa_segundos(string aviso);

private:
	AnimControlCollection anims;
	NodePath img_titulo;
	float ratio;
	NodePath img_tempo;
	NodePath img_frase_relogio;
	NodePath np_slide;
	NodePath img_escolha_especie;
	NodePath marcador;
	static Player::lizardEpecie especie;
	NodePath tropidurus, eurolophosasurus, cnemidophorus; //lagarto andando
	PT(TextNode) lb_num_minutos;
	NodePath np_lb_num_minutos;
	bool showing_custom;
	NodePath img_colisao_ativada;
	NodePath img_colisao_desativada;
	PT(PGSliderBar) slide;																						ACTION(slide_action);
	PT(PGButton) btn_mais;				NodePath np_btn_mais;				NodePath img_btn_mais;				ACTION(slide_direita_action);
	PT(PGButton) btn_menos;				NodePath np_btn_menos;				NodePath img_btn_menos;				ACTION(slide_esquerda_action);
	PT(PGButton) btn_tropidurus;		NodePath np_btn_tropidurus;			NodePath img_btn_tropidurus;		ACTION(tropidurus_action);
	PT(PGButton) btn_eurolophosaurus;	NodePath np_btn_eurolophosaurus;	NodePath img_btn_eurolophosaurus;	ACTION(eurolophosaurus_action);
	PT(PGButton) btn_cnemidophorus;		NodePath np_btn_cnemidophorus;		NodePath img_btn_cnemidophorus;		ACTION(cnemidophorus_action);
	PT(PGButton) btn_personalizar;		NodePath np_btn_personalizar;		NodePath img_btn_personalizar;		ACTION(personalizar_action);
	PT(PGButton) btn_colisao;			NodePath np_btn_colisao;			NodePath img_btn_colisao;			ACTION(colisao_action);
	PT(Button) btn_jogar;				NodePath np_btn_jogar;													ACTION(jogar_action);
	PT(Button) btn_voltar;				NodePath np_btn_voltar;													ACTION(voltar_action);
};

#undef ACTION

#endif /* GAMEOPTIONSSCREEN_H */
