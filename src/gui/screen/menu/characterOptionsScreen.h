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
	NodePath np_btn_avancar;
	PT(Button) btn_avancar;
	ACTION(jogar_action);

	PT(TextNode) lb_escolha_especie;	NodePath np_lb_escolha_especie;
	PT(Button) btn_tropidurus;			NodePath np_btn_tropidurus;			ACTION(tropidurus_action);
	PT(Button) btn_eurolophosaurus;		NodePath np_btn_eurolophosaurus;	ACTION(eurolophosaurus_action);
	PT(Button) btn_cnemidophorus;		NodePath np_btn_cnemidophorus;		ACTION(cnemidophorus_action);

	PT(TextNode) lb_nivel_dificuldade;	NodePath np_lb_nivel_dificuldade;
	PT(Button) btn_nivel_facil;			NodePath np_btn_nivel_facil;		ACTION(nivel_facil_action);
	PT(Button) btn_nivel_medio;			NodePath np_btn_nivel_medio;		ACTION(nivel_medio_action);
	PT(Button) btn_nivel_dificil;		NodePath np_btn_nivel_dificil;		ACTION(nivel_dificil_action);

};

#undef ACTION

#endif /* CHARACTEROPTIONSSCREEN_H */
