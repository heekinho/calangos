/*
 *  inGameScreenManager.h
 *  Created on: 02/04/2011
 *  Author: jonatas
 */

#ifndef INGAMESCREENMANAGER_H
#define INGAMESCREENMANAGER_H

#include "screenManager.h"
#include "screen.h"

class InGameScreenManager : public ScreenManager {
public:
	static PT(InGameScreenManager) get_instance();
	~InGameScreenManager(){}

	PT(Screen) get_pause_screen();
	void create_menus();
	PT(TextFont) get_default_font();

private:
	InGameScreenManager();
	static PT(InGameScreenManager) instance;

	PT(TextFont) default_menu_font;
	PT(Screen) pause_screen;
};

#endif
