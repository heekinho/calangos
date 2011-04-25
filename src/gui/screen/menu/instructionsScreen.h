/*
 *  instructionsScreen.h
 *  Created on: 05/03/2011
 *  Author: jonatas
 */

#ifndef INSTRUCTIONSSCREEN_H
#define INSTRUCTIONSSCREEN_H

#include "screenManager.h"
#include "screen.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(InstructionsScreen))(InstructionsScreen*)d)->mn(); }

class InstructionsScreen : public Screen {
public:
	InstructionsScreen(PT(ScreenManager) manager);
	~InstructionsScreen();

	void load();
	void unload();
	void show();
	void hide();

private:

	/* Componentes do Menu */
	PT(TextNode) lb_titulo;			NodePath np_lb_titulo;
	PT(Button) btn_controles;	 	NodePath np_btn_controles;		 ACTION(controles_action);
	PT(Button) btn_indicadores; 	NodePath np_btn_indicadores;	 ACTION(indicadores_action);
};

#undef ACTION

#endif
