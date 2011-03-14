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

CalangosMenuManager::CalangosMenuManager() : ScreenManager() {
	play_movie("models/videos/vinheta_opcao_1_mpeg4.avi");
	Simdunas::get_framework()->define_key("escape", "Stop_Movie", stop_movie, this);

	/* Carrega uma fonte estática */
	default_menu_font = FontPool::load_font("models/gui/fonts/suplexcomic-large.egg");
	create_menus();
//	open_screen(main_menu);
}

void CalangosMenuManager::create_menus(){
	main_menu = new StartMenu(this);
	loading_screen = new LoadingScreen(this);
	credits_screen = new CreditsScreen(this);
	options_screen = new OptionsScreen(this);
	instructions_screen = new InstructionsScreen(this);
	key_instructions_screen = new KeyInstructionsScreen(this);
	indicators_screen = new IndicatorsScreen(this);
	game_options_screen = new GameOptionsScreen(this);
        texture_screen = new editorTextureScreen(this);
	//	main_menu->load();
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

PT(AudioSound) CalangosMenuManager::get_sound() {
	return ASound;
}

PT(AudioManager) CalangosMenuManager::get_audio_manager() {
	return AM;
}

bool CalangosMenuManager::is_playing_movie() {
	return playing_movie;
}

void CalangosMenuManager::play_movie(string file) {
	mov = new MovieTexture("movie");
	mov->read(file);

	cm = new CardMaker("Video");
	cm->set_frame_fullscreen_quad();
	cm->set_uv_range(mov);
	node_card = NodePath(cm->generate());
	node_card.reparent_to(Simdunas::get_window()->get_render_2d());
	node_card.set_texture(mov);
	//node_card.set_tex_scale(TextureStage::get_default(), mov->get_tex_scale());

	AM = AudioManager::create_AudioManager();
	ASound = AM->get_sound(file, true, 1);

	mov->synchronize_to(ASound);

	ASound->play();
	playing_movie = true;
}

void CalangosMenuManager::stop_movie(const Event*, void* data) {
	CalangosMenuManager* _this = (CalangosMenuManager*) data;

	if (_this->playing_movie) {
		_this->ASound->stop();
		_this->node_card.remove_node();
		StartMenu* start_menu = (StartMenu*) _this->main_menu.p();
		if (!start_menu->get_np_options().is_empty()) {//só mostra a tela principal quando for a vinheta que estiver tocando
			_this->open_screen(_this->main_menu);

		}
//		else{//se não for a vinheta ele mostra o frame com os ícones do jogo
//			GuiManager::get_instance()->show_frameNode();
//		}
		_this->playing_movie = false; //o video não está mais tocando
	}

	//Simdunas::get_evt_handler()->remove_hooks("escape");//retirando o evento da fila, se não vai continuar chamando quando pressionar ESC

}
