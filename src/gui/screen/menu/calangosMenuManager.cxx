/*
 *  calangosMenuManager.cxx
 *  Created on: 23/02/2011
 *  Author: heekinho
 */

#include "calangosMenuManager.h"

#include "startMenu.h"
#include "loadingScreen.h"
#include "creditsScreen.h"
#include "optionsScreen.h"
#include "instructionsScreen.h"
#include "keyInstructionsScreen.h"
#include "indicatorsScreen.h"
#include "gameOptionsScreen.h"
#include "fontPool.h"
#include "editorTextureScreen.h"
#include "characterEditor.h"
#include "levelSelectionScreen.h"
#include "audioOptionsScreen.h"

PT(CalangosMenuManager) CalangosMenuManager::instance = NULL;

CalangosMenuManager::CalangosMenuManager() : ScreenManager() {
	/* Carrega uma fonte estática */
	default_menu_font = FontPool::load_font("models/gui/fonts/suplexcomic-large");
	create_menus();
	// a loading_screen é carregada separadamente porque no caso de um reinício de jogo, somente ela
	// precisará ser recarregada.
	set_loading_screen(new LoadingScreen(this));
	open_screen(main_menu);

	play_video("models/videos/vinheta_opcao_1_mpeg4.avi");
}

PT(CalangosMenuManager) CalangosMenuManager::get_instance() {
	if (instance == NULL) {
		instance = new CalangosMenuManager();
	}
	return instance;
}

void CalangosMenuManager::create_menus(){
	main_menu = new StartMenu(this);
	credits_screen = new CreditsScreen(this);
	options_screen = new OptionsScreen(this);
	instructions_screen = new InstructionsScreen(this);
	key_instructions_screen = new KeyInstructionsScreen(this);
	indicators_screen = new IndicatorsScreen(this);
	game_options_screen = new GameOptionsScreen(this);
	levels_screen = new LevelSelectionScreen(this);
	character_editor = new CharacterEditor(this);
	texture_screen = new editorTextureScreen(this);
	audio_options_screen = new AudioOptionsScreen(this);
}

void CalangosMenuManager::unload_menus() {
	main_menu = NULL;
	credits_screen = NULL;
	options_screen = NULL;
	instructions_screen = NULL;
	key_instructions_screen = NULL;
	indicators_screen = NULL;
	game_options_screen = NULL;
	levels_screen = NULL;
	character_editor = NULL;
	texture_screen = NULL;
	audio_options_screen = NULL;
}


/*! Retorna a fonte padrão a ser usada para a tela. Nada impede, porém, que
 *  outras fontes sejam utilizadas. */
PT(TextFont) CalangosMenuManager::get_default_font(){
	return default_menu_font;
}

PT(Screen) CalangosMenuManager::get_main_menu() {
	return main_menu;
}

PT(Screen) CalangosMenuManager::get_loading_screen() {
	return loading_screen;
}

PT(Screen) CalangosMenuManager::get_credits_screen() {
	return credits_screen;
}

PT(Screen) CalangosMenuManager::get_options_screen() {
	return options_screen;
}

PT(Screen) CalangosMenuManager::get_instructions_screen() {
	return instructions_screen;
}

PT(Screen) CalangosMenuManager::get_key_instructions_screen() {
	return key_instructions_screen;
}

PT(Screen) CalangosMenuManager::get_indicators_screen() {
	return indicators_screen;
}

PT(Screen) CalangosMenuManager::get_game_options_screen() {
	return game_options_screen;
}

PT(Screen) CalangosMenuManager::get_editor_texture_screen() {
	return texture_screen;
}

PT(Screen) CalangosMenuManager::get_character_editor() {
	return character_editor;
}

PT(Screen) CalangosMenuManager::get_audio_options_screen() {
	return audio_options_screen;
}

void CalangosMenuManager::set_loading_screen(PT(Screen) screen) {
	loading_screen = screen;
}
