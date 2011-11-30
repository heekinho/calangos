/*
 *  inGameScreenManager.cxx
 *  Created on: 02/04/2011
 *  Author: jonatas
 */

#include "inGameScreenManager.h"
#include "fontPool.h"
#include "pauseScreen.h"
#include "gameOverScreen.h"
#include "gameInterfaceScreen.h"

PT(InGameScreenManager) InGameScreenManager::instance = NULL;

InGameScreenManager::InGameScreenManager() : ScreenManager() {
	/* Carrega uma fonte estática */
	default_menu_font = FontPool::load_font("models/gui/fonts/suplexcomic-large");
	create_menus();
}

PT(InGameScreenManager) InGameScreenManager::get_instance() {
	if (instance == NULL) {
		instance = new InGameScreenManager();
	}
	return instance;
}

void InGameScreenManager::create_menus(){
	pause_screen = new PauseScreen(this);
	game_over_screen = new GameOverScreen(this);
	game_interface_screen = new GameInterfaceScreen(this);
}


/*! Retorna a fonte padrão a ser usada para a tela. Nada impede, porém, que
 *  outras fontes sejam utilizadas. */
PT(TextFont) InGameScreenManager::get_default_font(){
	return default_menu_font;
}

PT(Screen) InGameScreenManager::get_pause_screen() {
	return pause_screen;
}

PT(Screen) InGameScreenManager::get_game_over_screen() {
	return game_over_screen;
}

PT(Screen) InGameScreenManager::get_game_interface_screen() {
	return game_interface_screen;
}
