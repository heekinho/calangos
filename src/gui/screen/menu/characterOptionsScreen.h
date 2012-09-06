/*
 * characterOptionsScreen.h
 *
 *  Created on: Sep 5, 2012
 *      Author: eduardo
 */

#ifndef CHARACTEROPTIONSSCREEN_H_
#define CHARACTEROPTIONSSCREEN_H_

#include "pandaFramework.h"
#include "screenManager.h"
#include "screen.h"
#include "button.h"
#include "player.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(CharacterOptionsScreen))(CharacterOptionsScreen*)d)->mn(); }

class CharacterOptionsScreen : public Screen {
public:
	CharacterOptionsScreen(PT(ScreenManager) manager);
	virtual ~CharacterOptionsScreen();

	void load();
	void show();
	void hide();

private:
	AnimControlCollection anims;
	NodePath img_escolha_especie;
	NodePath marcador;
	NodePath tropidurus, eurolophosasurus, cnemidophorus; //lagarto andando
	NodePath img_colisao_ativada;
	NodePath img_colisao_desativada;
	NodePath np_btn_avancar;
	PT(Button) btn_avancar;
	ACTION(jogar_action);
	PT(PGButton) btn_tropidurus;		NodePath np_btn_tropidurus;			NodePath img_btn_tropidurus;		ACTION(tropidurus_action);
	PT(PGButton) btn_eurolophosaurus;	NodePath np_btn_eurolophosaurus;	NodePath img_btn_eurolophosaurus;	ACTION(eurolophosaurus_action);
	PT(PGButton) btn_cnemidophorus;		NodePath np_btn_cnemidophorus;		NodePath img_btn_cnemidophorus;		ACTION(cnemidophorus_action);
	PT(PGButton) btn_colisao;			NodePath np_btn_colisao;			NodePath img_btn_colisao;			ACTION(colisao_action);
};

#undef ACTION

#endif /* CHARACTEROPTIONSSCREEN_H */
