/*
 * indicatorsScreen.h
 *
 *  Created on: Mar 6, 2011
 *      Author: jonatas
 */

#ifndef INDICATORSSCREEN_H
#define INDICATORSSCREEN_H

#include "pandaFramework.h"
#include "screenManager.h"
#include "screen.h"
#include "button.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(IndicatorsScreen))(IndicatorsScreen*)d)->mn(); }

class IndicatorsScreen : public Screen {
public:
	IndicatorsScreen(PT(ScreenManager) manager);
	virtual ~IndicatorsScreen();

	void load();
	void show();
	void hide();

private:
	NodePath img_indicadores;
};

#undef ACTION

#endif /* INDICATORSSCREEN_H */
