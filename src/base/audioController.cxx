/*
 * audioController.cxx
 *
 *  Created on: 14/06/2011
 *      Author: jonatas
 */

#include "audioController.h"

PT(AudioController) AudioController::instance = NULL;

PT(AudioController) AudioController::get_instance() {
	if (instance == NULL) {
		instance = new AudioController();
	}

	return instance;
}

AudioController::AudioController() {
	audio_repository = new AudioRepository();
}

AudioController::~AudioController() {}

PT(AudioRepository) AudioController::get_audio_repository() {
	return audio_repository;
}

void AudioController::only_play(string sound_name) {
	audio_repository->play_sound(sound_name);
}


void AudioController::frog(float distance_to_player) {
	if (distance_to_player < 5 && !AudioRepository::playing) {
		cout<<"TOCANDO SOM DO SAPO!!!"<<endl;
		audio_repository->play_sound("frog", true);
	}
}

void AudioController::bobbing() {
	audio_repository->get_audio("bobbing")->set_volume(0.05);
	audio_repository->play_sound("bobbing");
}

void AudioController::warning_temp(double intern_temp, double extern_temp) {
	if (intern_temp > 41) {
		if (intern_temp < extern_temp) {
			audio_repository->get_audio("warning")->set_volume(1);
		}
		else {
			audio_repository->get_audio("warning")->set_volume(0.4);
		}
		audio_repository->play_sound("warning");
	}
	else if (intern_temp < 16) {
		if (intern_temp > extern_temp) {
			audio_repository->get_audio("warning")->set_volume(1);
		}
		else {
			audio_repository->get_audio("warning")->set_volume(0.4);
		}
		audio_repository->play_sound("warning");
	}
}

void AudioController::warning_hydrat(double hydrat) {
	if (hydrat < 15) {
		audio_repository->play_sound("warning");
	}
}

void AudioController::heart_beat(double energy) {
	if (energy < 20) {
		if (energy < 10) {
			audio_repository->get_audio("heart_beat")->set_play_rate(2);
		}
		else {
			audio_repository->get_audio("heart_beat")->set_play_rate(1);
		}
		audio_repository->play_sound("heart_beat", true);
	}
}
