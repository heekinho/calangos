/*
 *  calangosMenuManager.h
 *  Created on: 23/02/2011
 *  Author: heekinho
 */

#ifndef CALANGOSMENUMANAGER_H
#define CALANGOSMENUMANAGER_H

#include "screenManager.h"
#include "screen.h"

class CalangosMenuManager : public ScreenManager {
public:
	CalangosMenuManager();
	~CalangosMenuManager(){}

	void create_menus();
	PT(TextFont) get_default_font();

protected:
	PT(TextFont) default_menu_font;
	PT(Screen) main_menu;
};

#endif
