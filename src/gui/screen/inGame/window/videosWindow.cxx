/*
 * videosWindow.cxx
 *
 *  Created on: Mar 3, 2012
 *      Author: jonatas
 */

#include "videosWindow.h"
#include "audioController.h"
#include "pauseScreen.h"
#include "inGameScreenManager.h"

VideosWindow::VideosWindow(NodePath parent, PT(ScreenManager) manager, float width, float height, string title, float pos_x, float pos_y) : Window(parent, width, height, title, pos_x, pos_y) {
	this->manager = manager;

	default_button_config(btn_lagartos, np_btn_lagartos, "Lagartos", LVecBase3f(0.2, 0, 1.2), VideosWindow::lagartos_action);
	default_button_config(btn_predadores, np_btn_predadores, "Predadores", LVecBase3f(0.9, 0, 1.2), VideosWindow::predadores_action);
	default_button_config(btn_presas, np_btn_presas, "Presas", LVecBase3f(0.2, 0, 0.8), VideosWindow::presas_action);
	default_button_config(btn_clima, np_btn_clima, "Clima", LVecBase3f(0.9, 0, 0.8), VideosWindow::clima_action);
	default_button_config(btn_habitat, np_btn_habitat, "Habitat", LVecBase3f(0.2, 0, 0.4), VideosWindow::habitat_action);
}

VideosWindow::~VideosWindow() {}

void VideosWindow::lagartos_action() {
	PauseScreen::selected_video = true;
	InGameScreenManager::get_instance()->get_pause_screen()->hide();
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_1_lagartos_mpeg4.avi");
}

void VideosWindow::predadores_action() {
	PauseScreen::selected_video = true;
	InGameScreenManager::get_instance()->get_pause_screen()->hide();
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_2_predadores_mpeg4.avi");
}

void VideosWindow::presas_action() {
	PauseScreen::selected_video = true;
	InGameScreenManager::get_instance()->get_pause_screen()->hide();
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_3_presas_mpeg4.avi");
}

void VideosWindow::clima_action() {
	PauseScreen::selected_video = true;
	InGameScreenManager::get_instance()->get_pause_screen()->hide();
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_5_variacoes_climaticas_mpeg4.avi");
}

void VideosWindow::habitat_action() {
	PauseScreen::selected_video = true;
	InGameScreenManager::get_instance()->get_pause_screen()->hide();
	AudioController::get_instance()->get_audio_repository()->pause_bgm();
	manager->play_video("models/videos/clipe_4_habitat_mpeg4.avi");
}
