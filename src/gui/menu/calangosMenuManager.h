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
	CalangosMenuManager();
	~CalangosMenuManager(){}

	PT(Screen) get_main_menu();
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

	void create_menus();
	PT(TextFont) get_default_font();
	PT(AudioSound) get_sound();
	PT(AudioManager) get_audio_manager();
	bool is_playing_movie();

	void play_movie(string file);
	static void stop_movie(const Event*, void *data);

private:
	PT(TextFont) default_menu_font;
	PT(Screen) character_editor;
	PT(Screen) main_menu;
	PT(Screen) loading_screen;
	PT(Screen) credits_screen;
	PT(Screen) options_screen;
	PT(Screen) instructions_screen;
	PT(Screen) key_instructions_screen;
	PT(Screen) indicators_screen;
	PT(Screen) game_options_screen;
    PT(Screen) texture_screen;
    PT(Screen) levels_screen;

    PT(MovieTexture) mov;
    CardMaker *cm;
    NodePath node_card;
    PT(AudioManager) AM;
    PT(AudioSound) ASound;
    bool playing_movie;
};

#endif
