

#include <stddef.h>
#include "simdunas.h"
#include "audioRepository.h"

const string AudioRepository::BITE = "bite";
const string AudioRepository::BITE_FAIL = "bite_fail";
const string AudioRepository::MOUSE_ON = "mouse_on";
const string AudioRepository::MOUSE_CLICK = "mouse_click";
const string AudioRepository::HEART_BEAT = "heart_beat";
const string AudioRepository::WARNING = "warning";
const string AudioRepository::PREDATOR_HIT = "predator_hit";
const string AudioRepository::REPROD_SUCCESS = "reprod_success";
const string AudioRepository::REPROD_FAIL = "reprod_fail";
const string AudioRepository::BOBBING = "bobbing";
const string AudioRepository::FROG = "frog";
const string AudioRepository::DASH = "dash";
const string AudioRepository::RUNNING = "running";
const string AudioRepository::DAY_SOUND = "day_sound";
const string AudioRepository::NIGHT_SOUND = "night_sound";
const string AudioRepository::RAIN_SOUND = "rain_sound";
bool AudioRepository::playing = false;
bool AudioRepository::is_stopped = false;
int AudioRepository::loops_remaining = 0;

AudioRepository::AudioRepository() {

    AM= AudioManager::create_AudioManager();
    bgm_AM = AudioManager::create_AudioManager();
    is_stopped = false;
    using_security_loop = false;
    is_sfx_enabled = true;
    is_bgm_enabled = true;
    sfx_volume_percent = 1;
    bgm_volume_percent = 1;
    load_audio();


}

 void AudioRepository::load_audio(){
	 nout <<"Criando Repositorio de Sons..." << endl;
     //para adicionar mais sons é só inserir aqui
     //add_audio("mordida","models/sounds/EAT1.WAV");
     //add_audio("mordida","models/sounds/eating.wav");
     //add_audio("mordida","models/sounds/funny_bite.wav");
     //add_audio("mordida","models/sounds/mordida_03.mp3");
     add_audio(BITE,"models/sounds/Pop_28-S_Bainbr-7952.wav");
     //add_audio("falha_mordida","models/sounds/falha_10.mp3");
     //add_audio("falha_mordida","models/sounds/falha_07.mp3");
     add_audio(BITE_FAIL,"models/sounds/Blunk-Public_D-339.wav");
     //add_audio("mouse_on","models/sounds/Bleeep-Public_D-17.wav");
     //add_audio("mouse_on","models/sounds/Blip_1-Surround-147.wav");
     add_audio(MOUSE_ON,"models/sounds/ButtonM-wwwbeat-1899.wav");
	 //add_audio("mouse_on","models/sounds/Dink-Public_D-146.wav");
	 //add_audio("mouse_click","models/sounds/Nice_Cli-NEO_Soun-1375.wav");
	 add_audio(MOUSE_CLICK,"models/sounds/Click_14-Partners-48.wav");
	 //add_audio("mouse_click","models/sounds/Click_16-Partners-44.wav");
	 //add_audio("mouse_click","models/sounds/Click_17-Partners-43.wav");
	 add_audio(HEART_BEAT,"models/sounds/heartbea-dylan-1465.wav");
	 add_audio(WARNING,"models/sounds/Warning-public_d-308.wav");
	 add_audio("warning2","models/sounds/WARNING-TM-534.wav");
	 //add_audio(PREDATOR_HIT,"models/sounds/Woody_cl-Partners-69.wav");
	 add_audio(PREDATOR_HIT,"models/sounds/pc_apanhando.wav");
	 add_audio(REPROD_SUCCESS,"models/sounds/Energy-Mystery-2370.wav");
	 add_audio(REPROD_FAIL,"models/sounds/falha_07.mp3");
	 add_audio(BOBBING,"models/sounds/falha_09.mp3");
	 add_audio(FROG,"models/sounds/Frog_gar-TDR-451.wav");
	 //add_audio("frog","models/sounds/frog.aiff");
	 add_audio(DASH,"models/sounds/Arranque_2.wav");
	 add_audio(RUNNING,"models/sounds/Corrida_Lagarto.wav");
	 add_audio(DAY_SOUND,"models/sounds/forest+wind2.wav");
	 add_audio(NIGHT_SOUND,"models/sounds/night+wind.wav");
	 add_audio(RAIN_SOUND,"models/sounds/rain_1.mp3");
	 add_bgm("BGM_1","models/sounds/AncientLand.wav");
	 add_bgm("BGM_2","models/sounds/midnight-ride.mp3");
	 add_bgm("BGM_3","models/sounds/Overcome.wav");
	 add_bgm("BGM_4","models/sounds/iron-man.mp3");
	 add_bgm("BGM_predator","models/sounds/jungle-run.mp3");
}

 void AudioRepository::add_audio(const string& name, const string& path){

	 PT(AudioSound) a_sound = AM->get_sound(path);
	 a_sound->set_finished_event("finished_event");
     audio[name] = a_sound;

 }

 void AudioRepository::add_bgm(const string& name, const string& path){

	 PT(AudioSound) a_sound = bgm_AM->get_sound(path);
	 a_sound->set_finished_event("bgm_finished_evt");
     bgm[name] = a_sound;

 }

 //quando quiser tocar um som é só chamar este método passando o nome
  void AudioRepository::play_sound(const string& name, bool unique, float volume){
	 if (!is_sfx_enabled) return;

	 if (unique) {
		 if (playing) return;

		 playing = true;
		 TimeControl::get_instance()->notify("finished_sound", sound_finished, audio[name], audio[name]->length() + 1);
	 }
	 audio[name]->set_volume(volume * sfx_volume_percent);
     audio[name]->play();
 }

  AsyncTask::DoneStatus AudioRepository::sound_finished(GenericAsyncTask* task, void* data) {
	  cout<<"SOUND_FINISHED!"<<endl;
	  AudioSound* a_sound = (AudioSound*) data;
	  a_sound->stop();
	  playing = false;
	  return AsyncTask::DS_done;
  }

  void AudioRepository::play_bgm(const string& name, int loops, float volume) {
	  if (!is_bgm_enabled) return;

	  loops_remaining = loops;
	  TimeControl::get_instance()->notify("finished_bgm_" + name, bgm_finished, bgm[name], bgm[name]->length());
	  cout<<"bgm_volume_percent = "<<bgm_volume_percent<<endl;
	  bgm[name]->set_volume(volume * bgm_volume_percent);
	  bgm[name]->set_loop(true);
	  bgm[name]->play();
	  current_bgm = bgm[name];
  }

  void AudioRepository::pause_bgm() {
	  if (!is_bgm_enabled) return;

	  is_stopped = true;
	  if (!using_security_loop) {
		  loops_remaining++;
		  using_security_loop = true;
	  }
	  // esse método get_time() não está funcionando. T_T
	  position_before_stop = current_bgm->get_time();
	  current_bgm->stop();
  }

  void AudioRepository::unpause_bgm() {
	  if (!is_bgm_enabled || !is_stopped) return;

	  is_stopped = false;
	  current_bgm->set_time(position_before_stop);
	  current_bgm->play();
  }

  void AudioRepository::play_bgm_infinitely(const string& name, float volume) {
	  if (!is_bgm_enabled) return;

	  bgm[name]->set_volume(volume * bgm_volume_percent);
	  bgm[name]->set_loop(true);
	  bgm[name]->play();
  }

  // Esse método só deve ser usado para parar uma bgm que foi tocada pelo método
  // play_bgm_infinitely, porque as outras já tem o método bgm_finished para cuidar disso.
  void AudioRepository::stop_bgm(const string& name) {
	  if (!is_bgm_enabled) return;

	  bgm[name]->stop();
  }

  AsyncTask::DoneStatus AudioRepository::bgm_finished(GenericAsyncTask* task, void* data) {
	  cout<<"BGM_FINISHED!"<<endl;
	  if (is_stopped) return AsyncTask::DS_again;

	  AudioSound* a_sound = (AudioSound*) data;
	  //a_sound->stop();

	  loops_remaining--;
	  if (loops_remaining != 0) {
		  //a_sound->play();
		  return AsyncTask::DS_again;
	  }

	  a_sound->stop();
	  return AsyncTask::DS_done;
  }

  PT(AudioSound) AudioRepository::get_audio(string name) {
	  return audio[name];
  }

  PT(AudioSound) AudioRepository::get_bgm(string name) {
  	  return bgm[name];
  }

 PT(AudioManager) AudioRepository::get_audioManager(){
     return AM;
 }

 float AudioRepository::get_sfx_volume_percent() {
	 return sfx_volume_percent;
 }

 void AudioRepository::set_sfx_volume_percent(float percent) {
	 sfx_volume_percent = percent;
 }

 float AudioRepository::get_bgm_volume_percent() {
	 return bgm_volume_percent;
 }

 void AudioRepository::set_bgm_volume_percent(float percent) {
	 bgm_volume_percent = percent;
 }

 void AudioRepository::set_sfx_enabled(bool flag) {
	 is_sfx_enabled = flag;
 }

 void AudioRepository::set_bgm_enabled(bool flag) {
	 is_bgm_enabled = flag;
 }


AudioRepository::~AudioRepository() {
    audio.clear();
}

