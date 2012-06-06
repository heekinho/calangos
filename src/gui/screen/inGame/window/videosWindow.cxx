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
#include "imageRepository.h"
#include "videoManager.h"

VideosWindow::VideosWindow(NodePath parent, PT(ScreenManager) manager, float width, float height, string title, float pos_x, float pos_y) : Window(parent, width, height, title, pos_x, pos_y) {
	this->manager = manager;

	img_video_lagartos = ImageRepository::get_instance()->get_image("video_lagartos");
	img_video_lagartos.reparent_to(np_frame);
	img_video_lagartos.set_scale(0.025);
	img_video_lagartos.set_pos(0.35, 0.0, 1);

	img_video_predadores = ImageRepository::get_instance()->get_image("video_predadores");
	img_video_predadores.reparent_to(np_frame);
	img_video_predadores.set_scale(0.025);
	img_video_predadores.set_pos(1, 0.0, 1);

	img_video_presas = ImageRepository::get_instance()->get_image("video_presas");
	img_video_presas.reparent_to(np_frame);
	img_video_presas.set_scale(0.025);
	img_video_presas.set_pos(1.65, 0.0, 1);

	img_video_clima = ImageRepository::get_instance()->get_image("video_clima");
	img_video_clima.reparent_to(np_frame);
	img_video_clima.set_scale(0.025);
	img_video_clima.set_pos(0.675, 0.0, 0.45);

	img_video_habitat = ImageRepository::get_instance()->get_image("video_habitat");
	img_video_habitat.reparent_to(np_frame);
	img_video_habitat.set_scale(0.025);
	img_video_habitat.set_pos(1.325, 0.0, 0.45);

	default_button_config(btn_lagartos, np_btn_lagartos, "Lagartos", LVecBase3f(0.35, 0, 0.75), VideosWindow::lagartos_action);
	default_button_config(btn_predadores, np_btn_predadores, "Predadores", LVecBase3f(1, 0, 0.75), VideosWindow::predadores_action);
	default_button_config(btn_presas, np_btn_presas, "Presas", LVecBase3f(1.65, 0, 0.75), VideosWindow::presas_action);
	default_button_config(btn_clima, np_btn_clima, "Clima", LVecBase3f(0.675, 0, 0.2), VideosWindow::clima_action);
	default_button_config(btn_habitat, np_btn_habitat, "Habitat", LVecBase3f(1.325, 0, 0.2), VideosWindow::habitat_action);
}

VideosWindow::~VideosWindow() {}

void VideosWindow::open_video(const string &video_path){
	nout << "VideosWindows::open_video" << endl;

	PauseScreen::selected_video = true;
	InGameScreenManager::get_instance()->get_pause_screen()->hide();
	AudioController::get_instance()->get_audio_repository()->pause_bgm();

	/* Toca o vídeo */
	PT(VideoManager) video_manager = InGameScreenManager::get_instance()->get_video_manager();
	video_manager->play_video(video_path);
}

void VideosWindow::lagartos_action() {
	open_video("models/videos/clipe_1_lagartos_mpeg4.avi");
}

void VideosWindow::predadores_action() {
	open_video("models/videos/clipe_2_predadores_mpeg4.avi");
}

void VideosWindow::presas_action() {
	open_video("models/videos/clipe_3_presas_mpeg4.avi");
}

void VideosWindow::clima_action() {
	open_video("models/videos/clipe_5_variacoes_climaticas_mpeg4.avi");
}

void VideosWindow::habitat_action() {
	open_video("models/videos/clipe_4_habitat_mpeg4.avi");
}
