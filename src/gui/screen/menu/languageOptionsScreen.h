/*
 * languageOptionsScreen.h
 *
 *  Created on: 27/07/2015
 *      Author: crystal
 */

#ifndef SRC_GUI_SCREEN_MENU_LANGUAGEOPTIONSSCREEN_H_
#define SRC_GUI_SCREEN_MENU_LANGUAGEOPTIONSSCREEN_H_

#include "screenManager.h"
#include "screen.h"
#include "pandaFramework.h"
#include "button.h"
#include "textNode.h"
#include "nodePath.h"

/*! Define uma ação a ser cadastrada no sistema de eventos.
 * 	Este define é útil para evitar poluição no código com os métodos estáticos
 *  necessários para o funcionamento do sistema de eventos do panda, bem como
 *  para fornecer uma maneira automática de se chamar o método de nome mn
 *  passado para o define.
 *
 *  Dica rápida de uso:
 *  return_type method_name();
 *  ACTION(method_name)
 *
 *	Seria possível apenas chamar ACTION(method_name), mas perderia-se muito de
 *	legibilidade a ausência das definições no cabeçalho. Poderia-se também usar
 *	uma maneira mais genérica para este define, mas precisaría-se passar o nome
 *	da classe também (poluindo). */
#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(LanguageOptionsScreen))(LanguageOptionsScreen*)d)->mn(); }

/*! Representa o primeiro menu presente no Jogo */
class LanguageOptionsScreen : public Screen {
public:
	LanguageOptionsScreen(PT(ScreenManager) manager);
	~LanguageOptionsScreen();

	void load();
	void show();
	void hide();

	NodePath get_np_options();
	NodePath get_np_play();
	static int get_esco();

private:

	NodePath np_lagarto;
	AnimControlCollection anims;
	NodePath np_logo;

	PT(Button) btn_portugues; 			NodePath np_portugues;		 	ACTION(portugues_action);
	PT(Button) btn_ingles; 				NodePath np_ingles;		 		ACTION(ingles_action);
	PT(Button) btn_espanhol; 			NodePath np_espanhol;			ACTION(espanhol_action);


};

#undef ACTION

#endif

