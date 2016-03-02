/*
 *  startMenu.h
 *  Created on: 21/02/2011
 *  Author: heekinho
 */

#ifndef STARTMENU_H
#define STARTMENU_H

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
static void mn(const Event*, void* d){ ((PT(StartMenu))(StartMenu*)d)->mn(); }

/*! Representa o primeiro menu presente no Jogo */
class StartMenu : public Screen {
public:
	StartMenu(PT(ScreenManager) manager);
	~StartMenu();

	void load();
	void show();
	void hide();

	NodePath get_np_options();
	NodePath get_np_play();

private:
	NodePath np_lagarto;
	AnimControlCollection anims;
	NodePath np_logo;

	/* Componentes do Menu */




	PT(Button) btn_play; 			NodePath np_play;		 	ACTION(play_action);
	PT(Button) btn_options; 		NodePath np_options;		ACTION(options_action);
	PT(Button) btn_instructions; 	NodePath np_instructions;	ACTION(instructions_action);
	PT(Button) btn_language; 		NodePath np_language;	 	ACTION(language_action);
	PT(Button) btn_credits; 		NodePath np_credits;	 	ACTION(credits_action);
	PT(Button) btn_exit; 			NodePath np_exit;		 	ACTION(exit_action);



};

#undef ACTION

#endif
