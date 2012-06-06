/*
 * videoManager.cxx
 *
 *  Created on: Apr 22, 2011
 *      Author: jonatas
 */

#include "videoManager.h"

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

void VideoManager::play(string path) {
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
	audio_sound = audio_manager->get_sound(path, true, 1);
	audio_sound->set_finished_event("finished_event");

	movie_texture->synchronize_to(audio_sound);
	audio_sound->play();
}

void VideoManager::stop() {
	playing = false;
	audio_sound->stop();
	movie_texture->clear();
	np_card_maker.remove_node();
//	delete card_maker;
}

bool VideoManager::is_playing() {
	return playing;
}
