/*
 *  keyInstructionsScreen.h
 *  Created on: 05/03/2011
 *  Author: jonatas
 */

#ifndef KEYINSTRUCTIONSSCREEN_H
#define KEYINSTRUCTIONSSCREEN_H

#include "screenManager.h"
#include "screen.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(KeyInstructionsScreen))(KeyInstructionsScreen*)d)->mn(); }

class KeyInstructionsScreen : public Screen {
public:
	KeyInstructionsScreen(PT(ScreenManager) manager);
	~KeyInstructionsScreen();

	void load();
	void unload();
	void show();
	void hide();

private:

	NodePath img_teclas;
	PT(TextNode) lb_teclas;
	NodePath np_lb_teclas;
};

#undef ACTION

#endif
