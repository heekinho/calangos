/*
 *  characterEditor.h
 *  Created on: 18/03/2011
 *  Author: heekinho
 */

#ifndef CHARACTEREDITOR_H
#define CHARACTEREDITOR_H

#include "nodePath.h"

#include "screen.h"
#include "screenManager.h"

#include "pgVirtualFrame.h"
#include "pgFrameStyle.h"
#include "button.h"

#include "guiLayer.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((CharacterEditor*)d)->mn(); }

#define GUIITEM(itemname, pgitem, gaction) \
PT(pgitem) itemname; NodePath np_##itemname; ACTION(gaction);

/*! Editor de personagens do jogo. */
class CharacterEditor : public Screen {
public:
	CharacterEditor(PT(ScreenManager) manager);
	~CharacterEditor();

	virtual void load();
	virtual void unload();

private:
	void configure_toolbar();
	void configure_buttons();
	void configure_controls();
	void configure_button_actions();
	ACTION(update_layout);

	GuiLayer* gui;
	PT(PGVirtualFrame) toolbar;		NodePath np_toolbar;
	PT(PGVirtualFrame) statusbar;	NodePath np_statusbar;

	PT(Button) btn_sizing;			NodePath np_btn_sizing;			ACTION(sizing_action_performed);
	PT(Button) btn_head_sizing;		NodePath np_btn_head_sizing;	//ACTION(sizing_action_performed);
	PT(Button) btn_pattern;			NodePath np_btn_pattern;		ACTION(pattern_action_performed);
//	PT(Button) btn_density;			NodePath np_btn_density;
//	PT(Button) btn_diet;			NodePath np_btn_diet;

	PT(PGSliderBar) slide; NodePath np_slide;
};

#undef ACTION

#endif
