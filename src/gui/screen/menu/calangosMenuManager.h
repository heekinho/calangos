/*
 *  calangosMenuManager.h
 *  Created on: 23/02/2011
 *  Author: heekinho
 */

#ifndef CALANGOSMENUMANAGER_H
#define CALANGOSMENUMANAGER_H

#include "screenManager.h"
#include "screen.h"
#include "audioManager.h"
#include "audioSound.h"
#include "movieTexture.h"
#include "cardMaker.h"

class CalangosMenuManager : public ScreenManager {
public:
	static PT(CalangosMenuManager) get_instance();
	~CalangosMenuManager(){}
	//Crystal
	PT(Screen) get_language_menu();
	//Crystal
	PT(Screen) get_main_menu();
	PT(Screen) get_name_screen();
	PT(Screen) get_loading_screen();
	PT(Screen) get_credits_screen();
	PT(Screen) get_options_screen();
	PT(Screen) get_instructions_screen();
	PT(Screen) get_key_instructions_screen();
	PT(Screen) get_indicators_screen();
	PT(Screen) get_game_options_screen();
	PT(Screen) get_editor_texture_screen();
	PT(Screen) get_character_editor();
	PT(Screen) get_level_selection_screen(){ return levels_screen; };
	PT(Screen) get_audio_options_screen();
	PT(Screen) get_character_options_screen();
	PT(Screen) get_scoreboard_screen();

	void set_loading_screen(PT(Screen) screen);

	void create_menus();
	void unload_menus();
	virtual PT(TextFont) get_default_font();

private:
	CalangosMenuManager();
	static PT(CalangosMenuManager) instance;
	PT(TextFont) default_menu_font;
	PT(Screen) character_editor;
	//Crystal
	PT(Screen) language_menu;
	//Crystal
	PT(Screen) main_menu;
	PT(Screen) name_screen;
	PT(Screen) loading_screen;
	PT(Screen) credits_screen;
	PT(Screen) options_screen;
	PT(Screen) instructions_screen;
	PT(Screen) key_instructions_screen;
	PT(Screen) indicators_screen;
	PT(Screen) game_options_screen;
    PT(Screen) texture_screen;
    PT(Screen) levels_screen;
    PT(Screen) audio_options_screen;
    PT(Screen) character_options_screen;
	PT(Screen) scoreboard_screen;
};

#endif
