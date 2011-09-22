/*
 * audioController.cxx
 *
 *  Created on: 14/06/2011
 *      Author: jonatas
 */

#include "audioController.h"
#include "timeControl.h"
#include "player.h"

PT(AudioController) AudioController::instance = NULL;

PT(AudioController) AudioController::get_instance() {
	if (instance == NULL) {
		instance = new AudioController();
	}

	return instance;
}

AudioController::AudioController() {
	frog_delay = false;
	is_running = false;
	audio_repository = new AudioRepository();
	event_handler->add_hook(TimeControl::EV_pass_minute, play_bgm, this);
}

AudioController::~AudioController() {}

PT(AudioRepository) AudioController::get_audio_repository() {
	return audio_repository;
}

void AudioController::play_bgm(const Event*, void *data) {
	if (Sky::current_status == Sky::STATUS_DAY) {
		AudioController::get_instance()->only_play(AudioRepository::DAY_SOUND, true, 0.5);
	}
	else if (Sky::current_status == Sky::STATUS_NIGHT) {
		AudioController::get_instance()->only_play(AudioRepository::NIGHT_SOUND, true, 0.5);
	}
	else {
		AudioController::get_instance()->only_play(AudioRepository::RAIN_SOUND, true, 0.5);
	}
}

void AudioController::only_play(string sound_name, bool unique, float volume) {
	audio_repository->play_sound(sound_name, unique, volume);
}


void AudioController::frog(PT(Frog) frog) {
	bool in_range = make_audio3d(6, *frog, AudioRepository::FROG);
	if (in_range && !frog_delay) {
		//cout<<"TOCANDO SOM DO SAPO!!!"<<endl;
		//cout<<"balance = "<<audio_repository->get_audio("frog")->get_balance()<<endl;
		//cout<<"volume do sapo = "<<audio_repository->get_audio("frog")->get_volume()<<endl;
		audio_repository->play_sound("frog");
		frog_delay = true;
		TimeControl::get_instance()->notify("frog_sound_delay", finish_frog_delay, this, 4);
	}
}

bool AudioController::make_audio3d(int max_dist, NodePath obj, string audio_name) {
	LVector3f player2obj = player->get_pos(render) - obj.get_pos(render);
	float dist = player2obj.length();
	if (dist > max_dist) {
		return false;
	}
	else {
		LVector3f right = player->get_net_transform()->get_quat().get_right();
		float balance = player2obj.dot(right) / dist;
		//cout<<"Balance antes = "<<balance<<endl;
		float volume = 1 - (dist / max_dist);
		PT(AudioSound) audio = audio_repository->get_audio(audio_name);
		audio->set_balance(balance);
		audio->set_volume(volume);
		return true;
	}
}

AsyncTask::DoneStatus AudioController::finish_frog_delay(GenericAsyncTask* task, void* data) {
	AudioController* _this = (AudioController*) data;
	_this->frog_delay = false;
    return AsyncTask::DS_done;
}

void AudioController::bobbing() {
	audio_repository->play_sound(AudioRepository::BOBBING, false , 0.05);
}

void AudioController::warning_temp(double intern_temp, double extern_temp, double min_temp, double max_temp) {
	// esse valor não pode ser maior ou igual a 5 porque a max_temp do Eurolophosauros é
	// 45 e quando a temperatura está muito alta, na sombra fica 40, portanto se esse valor
	// fosse 5 o alerta ficaria tocando mesmo o player estando na sombra.
	if (intern_temp > (max_temp - 4)) {
		if (intern_temp < extern_temp) {
			audio_repository->play_sound(AudioRepository::WARNING, false, 0.7);
		}
		else {
			audio_repository->play_sound(AudioRepository::WARNING, false, 0.25);
		}
		GuiManager::get_instance()->get_game_status_bar()->temperatura_critica_on();
	}
	else if (intern_temp < (min_temp + 4)) {
		if (intern_temp > extern_temp) {
			audio_repository->play_sound(AudioRepository::WARNING, false, 0.7);
		}
		else {
			audio_repository->play_sound(AudioRepository::WARNING, false, 0.25);
		}
		GuiManager::get_instance()->get_game_status_bar()->temperatura_critica_on();
	}
	else {
		GuiManager::get_instance()->get_game_status_bar()->temperatura_critica_off();
	}
}

void AudioController::warning_hydrat(double hydrat, double min_hydrat) {
	if (hydrat < (min_hydrat + 4)) {
		audio_repository->play_sound(AudioRepository::WARNING);
		GuiManager::get_instance()->get_game_status_bar()->hidratacao_critica_on();
	}
	GuiManager::get_instance()->get_game_status_bar()->hidratacao_critica_off();
}

void AudioController::heart_beat(double energy, double min_energy) {
	if (energy < (min_energy + 15)) {
		if (energy < (min_energy + 7)) {
			audio_repository->get_audio(AudioRepository::HEART_BEAT)->set_play_rate(2);
		}
		else {
			audio_repository->get_audio(AudioRepository::HEART_BEAT)->set_play_rate(1);
		}
		audio_repository->play_sound(AudioRepository::HEART_BEAT, true);
	}
}

void AudioController::running() {
	if (is_running) return;

	is_running = true;
	audio_repository->play_sound(AudioRepository::DASH);
	TimeControl::get_instance()->notify("dash_finish", finish_dash, this, audio_repository->get_audio(AudioRepository::DASH)->length());
}

void AudioController::stop_running() {
	is_running = false;
	audio_repository->get_audio(AudioRepository::RUNNING)->stop();
}

AsyncTask::DoneStatus AudioController::finish_dash(GenericAsyncTask* task, void* data) {
	AudioController* _this = (AudioController*) data;
	_this->audio_repository->play_sound(AudioRepository::RUNNING);
	TimeControl::get_instance()->notify("loop_running", loop_running, _this, _this->audio_repository->get_audio(AudioRepository::RUNNING)->length());
	return AsyncTask::DS_done;
}

AsyncTask::DoneStatus AudioController::loop_running(GenericAsyncTask* task, void* data) {
	AudioController* _this = (AudioController*) data;

	if (!_this->is_running) return AsyncTask::DS_done;

	PlayerControl* playerCtrl = PlayerControl::get_instance();
	_this->audio_repository->play_sound(AudioRepository::RUNNING);
	return AsyncTask::DS_again;
}

void AudioController::play_warning() {
	audio_repository->play_sound(AudioRepository::WARNING, false, 0.2);
}
