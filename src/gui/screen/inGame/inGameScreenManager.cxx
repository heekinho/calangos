/*
 *  inGameScreenManager.cxx
 *  Created on: 02/04/2011
 *  Author: jonatas
 */

#include "inGameScreenManager.h"
#include "fontPool.h"
#include "pauseScreen.h"
#include "gameOverScreen.h"
#include "videoManager.h"

PT(InGameScreenManager) InGameScreenManager::instance = NULL;

InGameScreenManager::InGameScreenManager() : ScreenManager() {
	/* Carrega uma fonte estática */
	default_menu_font = FontPool::load_font("models/gui/fonts/suplexcomic-large");
	video_manager = new VideoManager();
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
}


/*! Retorna a fonte padrão a ser usada para a tela. Nada impede, porém, que
 *  outras fontes sejam utilizadas. */
PT(TextFont) InGameScreenManager::get_default_font(){
	return default_menu_font;
}

PT(VideoManager) InGameScreenManager::get_video_manager() const {
	return video_manager;
}

PT(Screen) InGameScreenManager::get_pause_screen() {
	return pause_screen;
}

PT(Screen) InGameScreenManager::get_game_over_screen() {
	return game_over_screen;
}
