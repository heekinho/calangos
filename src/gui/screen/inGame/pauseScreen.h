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
#include "window.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(PauseScreen))(PauseScreen*)d)->mn(); }

class PauseScreen : public Screen {
public:
	PauseScreen(PT(ScreenManager) manager);
	~PauseScreen();

	void load();
	void show();
	void hide();

	void pause_event();
	bool is_stopped_time();

	ACTION(realizacoes_action);
	ACTION(videos_action);
	ACTION(continuar_action);
	ACTION(sair_action);
	static bool selected_video;
	static bool is_opened;

private:

	bool stopped_time;
	PT(Window) wnd_realizacoes;
	PT(Window) wnd_videos;
	/* Componentes do Menu */
	//NodePath titulo;
	//NodePath img_videos;
	PT(TextNode) lb_jogo_pausado;	NodePath np_lb_jogo_pausado;
	PT(TextNode) lb_videos;			NodePath np_lb_videos;
	PT(Button) btn_realizacoes;		NodePath np_btn_realizacoes;
	PT(Button) btn_videos;			NodePath np_btn_videos;
	PT(Button) btn_lagartos;		NodePath np_btn_lagartos;
	PT(Button) btn_predadores; 		NodePath np_btn_predadores;
	PT(Button) btn_presas; 			NodePath np_btn_presas;
	PT(Button) btn_clima; 			NodePath np_btn_clima;
	PT(Button) btn_habitat; 		NodePath np_btn_habitat;
	PT(Button) btn_continuar; 		NodePath np_btn_continuar;
	PT(Button) btn_sair; 			NodePath np_btn_sair;
};

#undef ACTION

#endif
