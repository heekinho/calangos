/*
 *  pauseScreen.h
 *  Created on: 02/04/2011
 *  Author: jonatas
 */

#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "screenManager.h"
#include "screen.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(PauseScreen))(PauseScreen*)d)->mn(); }

class PauseScreen : public Screen {
public:
	PauseScreen(PT(ScreenManager) manager);
	~PauseScreen();

	void load();
	void unload();
	void show();
	void hide();

	void default_button_config(PT(Button) button, NodePath &np,
			const string &text, float z, EventCallbackFunction *action);
	void button_config(PT(Button) button, NodePath &np,
				const string &text, float x, float z, EventCallbackFunction *action);

	void pause_event();
	bool is_stopped_time();

private:

	bool stopped_time;
	bool selected_video;
	/* Componentes do Menu */
	NodePath titulo;
	NodePath img_videos;
	PT(Button) btn_lagartos;		NodePath np_btn_lagartos;		 ACTION(lagartos_action);
	PT(Button) btn_predadores; 		NodePath np_btn_predadores;	 	 ACTION(predadores_action);
	PT(Button) btn_presas; 			NodePath np_btn_presas;			 ACTION(presas_action);
	PT(Button) btn_clima; 			NodePath np_btn_clima;		 	 ACTION(clima_action);
	PT(Button) btn_habitat; 		NodePath np_btn_habitat;		 ACTION(habitat_action);
	PT(Button) btn_continuar; 		NodePath np_btn_continuar;		 ACTION(continuar_action);
	PT(Button) btn_sair; 			NodePath np_btn_sair;		 	 ACTION(sair_action);
};

#undef ACTION

#endif
