/*
 *  levelSelectionScreen.h
 *  Created on: 03/04/2011
 *  Author: heekinho
 */

#ifndef LEVELSELECTION_H
#define LEVELSELECTION_H

#include "screen.h"
#include "screenManager.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((LevelSelectionScreen*)d)->mn(); }

class LevelSelectionScreen : public Screen {
public:
	LevelSelectionScreen(PT(ScreenManager) manager);
	~LevelSelectionScreen();

	void load();

private:
	/* Componentes do Menu */
	PT(Button) btn_level_one; 	NodePath np_btn_level_one;	ACTION(level_one_action);
	PT(Button) btn_level_two; 	NodePath np_btn_level_two;	ACTION(level_two_action);
};

#undef ACTION

#endif
