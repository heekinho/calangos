/*
 * creditsScreen.h
 *
 *  Created on: Mar 1, 2011
 *      Author: jonatas
 */

#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include "pandaFramework.h"
#include "screenManager.h"
#include "screen.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(CreditsScreen))(CreditsScreen*)d)->mn(); }

class CreditsScreen : public Screen {
public:
	CreditsScreen(PT(ScreenManager) manager);
	virtual ~CreditsScreen();

	void load();
	void show();
	void hide();

private:
	NodePath img_credit;
};

#undef ACTION

#endif /* CREDITSSCREEN_H */
