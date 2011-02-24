/*
 *  calangosMenuManager.cxx
 *  Created on: 23/02/2011
 *  Author: heekinho
 */

#include "calangosMenuManager.h"

#include "startMenu.h"
#include "fontPool.h"

CalangosMenuManager::CalangosMenuManager() : ScreenManager() {
	/* Carrega uma fonte estática */
	default_menu_font = FontPool::load_font("models/gui/fonts/suplexcomic-large.egg");
	create_menus();
	open_screen(main_menu);
}

void CalangosMenuManager::create_menus(){
	main_menu = new StartMenu(this);
//	main_menu->load();
}


/*! Retorna a fonte padrão a ser usada para a tela. Nada impede, porém, que
 *  outras fontes sejam utilizadas. */
PT(TextFont) CalangosMenuManager::get_default_font(){
	return default_menu_font;
}
