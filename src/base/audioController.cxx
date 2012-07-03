/*!
 * audioController.cxx
 *
 * Esta classe provê métodos para que o áudio do jogo possa ser tocado. Nesses métodos é implementada também a lógica
 * de quando o áudio deve ser tocado.
 *
 *  Created on: 14/06/2011
 *      Author: jonatas
 */

#include "audioController.h"
#include "timeControl.h"
#include "simdunas.h"
#include "player.h"
#include "guiManager.h"
#include "playerControl.h"

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
	is_still_dangerous_temp = false;
	flag_stop_warning = false;
	bgm_number = 1;
	audio_repository = new AudioRepository();
	event_handler->add_hook(TimeControl::EV_pass_minute, play_bgm, this);
}

AudioController::~AudioController() {}

PT(AudioRepository) AudioController::get_audio_repository() {
	return audio_repository;
}

/*! Toca as BGM's do jogo. Cada BGM é tocada uma determinada quantidade de vezes (loops), depois é iniciada BGM posterior */
void AudioController::play_bgm(const Event*, void *data) {
	AudioController* _this = (AudioController*) data;

	if (AudioRepository::loops_remaining == 0) {
		switch (_this->bgm_number) {
			case 1:
				_this->audio_repository->play_bgm("BGM_1", 7, 0.15);
				break;
			case 2:
				_this->audio_repository->play_bgm("BGM_2", 1, 0.3);
				break;
			case 3:
				_this->audio_repository->play_bgm("BGM_3", 10, 0.3);
				break;
			case 4:
				_this->audio_repository->play_bgm("BGM_4", 1, 0.3);
				break;
		}
		_this->bgm_number++;
		if (_this->bgm_number > 4) {
			_this->bgm_number = 1;
		}
	}
}

/*! Pausa a BGM atual e toca a BGM de predador perseguindo */
void AudioController::predator_pursuing() {
	audio_repository->pause_bgm();
	audio_repository->play_bgm_infinitely("BGM_predator", 0.4);
}

/*! Para a BGM de predador perseguindo e despausa a BGM que estava tocando antes do início da perseguição */
void AudioController::pursuit_finished() {
	audio_repository->stop_bgm("BGM_predator");
	audio_repository->unpause_bgm();
}

/*!
 * Apenas toca um áudio qualquer
 *
 * @param sound_name Nome do áudio a ser tocado
 * @param unique Flag usado para garantir que, caso o mesmo áudio tente ser tocado novamente antes dele ter terminado de tocar, ele não comece a tocar novamente do começo
 * @param volume Volume do áudio (varia de 0 a 1)
 */
void AudioController::only_play(string sound_name, bool unique, float volume) {
	audio_repository->play_sound(sound_name, unique, volume);
}

/*!
 * Toca o som do sapo coachando
 *
 * @param frog Ponteiro do sapo que está próximo
 */
void AudioController::frog(PT(Frog) frog) {
	bool in_range = make_audio3d(6, *frog, AudioRepository::FROG);
	// verifica se está dentro da distância e se o som do sapo já não está sendo tocado
	if (in_range && !frog_delay) {
		//cout<<"TOCANDO SOM DO SAPO!!!"<<endl;
		//cout<<"balance = "<<audio_repository->get_audio("frog")->get_balance()<<endl;
		//cout<<"volume do sapo = "<<audio_repository->get_audio("frog")->get_volume()<<endl;
		audio_repository->play_sound("frog");
		frog_delay = true;
		// toca o som do sapo a cada 4 segundos
		TimeControl::get_instance()->notify("frog_sound_delay", finish_frog_delay, this, 4);
	}
}

/*!
 * Verifica se um objeto está numa distância em que o player deve ouvir o som emitido.
 * Configura também o balance e o volume de acordo com a posição do objeto para dar o efeito de áudio3D.
 *
 * @param max_dist Distância máxima em que o player poderá ouvir som emitido pelo objeto
 * @param obj Objeto emissor de som
 * @param audio_name Nome do áudio
 * @return Retorna true se a distância entre o player e o objeto for menor que max_dist e false caso contrário
 */
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
		// o set_balance não está funcionando pois não tinha sido implementado pelo panda (a versão verificada foi: 1.7.2)
		audio->set_balance(balance);
		audio->set_volume(volume);
		return true;
	}
}

/*! Seta o flag frog_delay como false, para que o som do sapo possa ser tocado novamente */
AsyncTask::DoneStatus AudioController::finish_frog_delay(GenericAsyncTask* task, void* data) {
	AudioController* _this = (AudioController*) data;
	_this->frog_delay = false;
	return AsyncTask::DS_done;
}

/*! Toca o som do bobbing */
void AudioController::bobbing() {
	audio_repository->play_sound(AudioRepository::BOBBING, false , 0.05);
}

/*! Toca o alerta de temperatura alta demais ou baixa demais */
void AudioController::warning_temp(double intern_temp, double extern_temp, double min_temp, double max_temp) {
	// esse valor não pode ser maior ou igual a 5 porque a max_temp do Eurolophosauros é
	// 45 e quando a temperatura está muito alta, na sombra fica 40, portanto se esse valor
	// fosse 5 o alerta ficaria tocando mesmo o player estando na sombra.
	if (intern_temp > (max_temp - 4)) {
		// se a temperatura interna é menor que a externa, está em perigo pois a temperatura interna irá aumentar
		if (intern_temp < extern_temp) {
			is_still_dangerous_temp = true;
			flag_stop_warning = false;
			TimeControl::get_instance()->notify("dangerous_temp_verifier", dangerous_temp_verifier, this, 3);
			audio_repository->play_sound(AudioRepository::WARNING, false, 0.5);
		}
		else {
			// temperatura interna está maior que a externa, logo ela vai abaixar, então já não está mais em perigo
			is_still_dangerous_temp = false;
			// verifica se o áudio ainda está tocando
			if (!flag_stop_warning) {
				// passa a tocar o alerta em um volume menor, para indicar que a temperatura já está abaixando
				audio_repository->play_sound(AudioRepository::WARNING, false, 0.25);
			}
		}
		// ativa efeito de temperatura crítica na barra de status
		GuiManager::get_instance()->get_game_status_bar()->temperatura_critica_on();
	}
	// verifica se está muito próximo da temperatura mínima
	else if (intern_temp < (min_temp + 4)) {
		// se a temperatura interna está maior que a externa, está em perigo pois a temperatura interna irá diminuir
		if (intern_temp > extern_temp) {
			is_still_dangerous_temp = true;
			flag_stop_warning = false;
			audio_repository->play_sound(AudioRepository::WARNING, false, 0.5);
		}
		else {
			// temperatura interna está menor que a externa, então irá aumentar e já não estará mais em perigo
			is_still_dangerous_temp = false;
			// verifica se o áudio ainda está tocando
			if (!flag_stop_warning) {
				// passa a tocar o alerta em um volume menor, para indicar que a temperatura já está aumentando
				audio_repository->play_sound(AudioRepository::WARNING, false, 0.25);
			}
		}
		// ativa efeito de temperatura crítica na barra de status
		GuiManager::get_instance()->get_game_status_bar()->temperatura_critica_on();
	}
	else {
		// desativa efeito de temperatura crítica na barra de status
		GuiManager::get_instance()->get_game_status_bar()->temperatura_critica_off();
	}
}

/*! Toca o alerta de hidratação baixa demais */
void AudioController::warning_hydrat(double hydrat, double min_hydrat) {
	if (hydrat < (min_hydrat + 4)) {
		audio_repository->play_sound(AudioRepository::WARNING);
		// ativa efeito de hidratação crítica na barra de status
		GuiManager::get_instance()->get_game_status_bar()->hidratacao_critica_on();
	}
	// desativa efeito de hidratação crítica na barra de status
	GuiManager::get_instance()->get_game_status_bar()->hidratacao_critica_off();
}

/*! Toca um som de batidas de coração caso a energia do jogador esteja muito baixa */
void AudioController::heart_beat(double energy, double min_energy) {
	if (energy < (min_energy + 15)) {
		// se estiver com 7 (ou menos) de energia a mais que a energia mínima
		if (energy < (min_energy + 7)) {
			// coloca o som do coração para bater em rítmo acelerado
			audio_repository->get_audio(AudioRepository::HEART_BEAT)->set_play_rate(2);
		}
		// está com a energia entre 7 e 15 a mais que a energia mínima
		else {
			// coloca o som do coração para bater em rítimo normal
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

AsyncTask::DoneStatus AudioController::dangerous_temp_verifier(GenericAsyncTask* task, void* data) {
	AudioController* _this = (AudioController*) data;
	if (_this->is_still_dangerous_temp) return AsyncTask::DS_again;

	_this->flag_stop_warning = true;
	return AsyncTask::DS_done;
}

void AudioController::play_warning() {
	audio_repository->play_sound("warning2", false, 0.2);
}
