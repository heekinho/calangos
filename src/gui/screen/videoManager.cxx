/*
 * videoManager.cxx
 * Created on: Apr 22, 2011
 * Author: jonatas
 */

#include "videoManager.h"

#include "audioController.h"

bool VideoManager::playing = false;

VideoManager::VideoManager() {
}

VideoManager::~VideoManager() {
	audio_manager = NULL;
	audio_sound = NULL;
	movie_texture = NULL;
//	card_maker = NULL;
	np_card_maker.remove_node();
}

PT(AudioManager) VideoManager::get_audio_manager() {
	return audio_manager;
}

PT(AudioSound) VideoManager::get_audio_sound() {
	return audio_sound;
}

/*!
 * Começa a exibir um vídeo.
 * @param path Caminho do vídeo que será exibido
 */
void VideoManager::play(const string &path) {
	playing = true;

	movie_texture = new MovieTexture("movie_texture");
	movie_texture->read(path);

	CardMaker card_maker = CardMaker("video");
	card_maker.set_frame_fullscreen_quad();
	card_maker.set_uv_range(movie_texture);

	np_card_maker = NodePath(card_maker.generate());
	np_card_maker.reparent_to(window->get_render_2d());
	np_card_maker.set_texture(movie_texture);

	audio_manager = AudioManager::create_AudioManager();
	audio_sound = audio_manager->get_sound(path, false, 1);
	audio_sound->set_finished_event("finished_event");

	movie_texture->synchronize_to(audio_sound);
	audio_sound->play();
}

/*! Interrompe a exibição do vídeo */
void VideoManager::stop() {
	playing = false;
	audio_sound->stop();
	movie_texture->clear();
	np_card_maker.remove_node();
}

/*!
 * Manda o vídeo ser exibido e adiciona dois eventos para que o vídeo seja fechado quando terminar ou caso o jogador
 * pressione a tecla ESC.
 * @param path Caminho do vídeo que será exibido
 */
void VideoManager::play_video(const string &path) {
	play(path);
	Simdunas::get_framework()->define_key("escape", "stop_video", stop_video, this);
	event_handler->add_hook(audio_sound->get_finished_event(), stop_video, this);
}

void VideoManager::stop_video(const Event*, void* data) {
	cout << "VideoManager::stop_video() - Apertei ESC! " << endl;
	VideoManager* _this = (VideoManager*) data;
	if (_this->get_audio_sound() != NULL && _this->is_playing()) {
		cout << "Parando o video!" << endl;

		event_handler->remove_hook(_this->get_audio_sound()->get_finished_event(), stop_video, _this);

		_this->stop();
		// volta a tocar a música de fundo
		AudioController::get_instance()->get_audio_repository()->unpause_bgm();
	}
}

bool VideoManager::is_playing() {
	return playing;
}


