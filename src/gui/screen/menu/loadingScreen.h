/*
 * loadingScreen.h
 *
 *  Created on: Feb 7, 2011
 *      Author: jonatas
 */

#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "pandaFramework.h"
#include "pgVirtualFrame.h"
#include "screen.h"
#include "screenManager.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(LoadingScreen))(LoadingScreen*)d)->mn(); }

class LoadingScreen : public Screen {
public:
	LoadingScreen(PT(ScreenManager) manager);
	virtual ~LoadingScreen();

	PT(TextNode) get_lb_objetivo();
	NodePath get_np_lb_objetivo();
	PT(TextNode) get_lb_descricao_objetivo();
	NodePath get_np_lb_descricao_objetivo();
	PT(TextNode) get_lb_carregando();
	NodePath get_np_lb_carregando();
	PT(PGButton) get_btn_comecar();
	NodePath get_lb_btn_comecar();
	PT(TextNode) get_lb_comecar();
	NodePath get_np_lb_comecar();
	void set_start(bool flag);

	void load();
	void loading_completed();
	void loading_process();

private:
	void attach_objects();

	PT(PGVirtualFrame) frame;
	NodePath np_frame;
    PT(TextNode) lb_objetivo;
    NodePath np_lb_objetivo;
    PT(TextNode) lb_descricao_objetivo;
    NodePath np_lb_descricao_objetivo;
    PT(TextNode) lb_carregando;
    NodePath np_lb_carregando;
    PT(Button) btn_comecar;	ACTION(start_game);
    NodePath np_btn_comecar;
    PT(TextNode) lb_processo;
    NodePath np_lb_processo;
    PT(TextNode) lb_info_processo;
    NodePath np_lb_info_processo;
    bool start;
};

#undef ACTION

#endif /* LOADINGSCREEN_H */
