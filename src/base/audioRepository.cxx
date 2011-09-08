

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
bool AudioRepository::playing = false;

AudioRepository::AudioRepository() {

    AM= AudioManager::create_AudioManager();

    load_audio();


}

 void AudioRepository::load_audio(){
	 nout <<"Criando Repositodio de Sons..." << endl;
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
	 add_audio(PREDATOR_HIT,"models/sounds/Woody_cl-Partners-69.wav");
	 add_audio(REPROD_SUCCESS,"models/sounds/Energy-Mystery-2370.wav");
	 add_audio(REPROD_FAIL,"models/sounds/falha_07.mp3");
	 add_audio(BOBBING,"models/sounds/falha_09.mp3");
	 add_audio(FROG,"models/sounds/Frog_gar-TDR-451.wav");
	 //add_audio("frog","models/sounds/frog.aiff");
	 add_audio("dash","models/sounds/Arranque_2+.wav");
	 add_audio("running","models/sounds/Corrida_Lagarto+.wav");

}

 void AudioRepository::add_audio(const string& name, const string& path){

	 PT(AudioSound) a_sound = AM->get_sound(path);
	 a_sound->set_finished_event("finished_event");
     audio[name] = a_sound;

 }

 //quando quiser tocar um som é só chamar este método passando o nome
  void AudioRepository::play_sound(const string& name, bool unique){
	 if (unique) {
		 if (playing) return;

		 playing = true;
		 TimeControl::get_instance()->notify("finished_sound", finished_sound, audio[name], audio[name]->length() + 1);
	 }
     audio[name]->play();
 }

  AsyncTask::DoneStatus AudioRepository::finished_sound(GenericAsyncTask* task, void* data) {
	  cout<<"FINISHED_SOUND!"<<endl;
	  AudioSound* a_sound = (AudioSound*) data;
	  a_sound->stop();
	  playing = false;
	  return AsyncTask::DS_done;
  }

  PT(AudioSound) AudioRepository::get_audio(string name) {
	  return audio[name];
  }

 PT(AudioManager) AudioRepository::get_audioManager(){
     return AM;
 }


AudioRepository::~AudioRepository() {
    audio.clear();
}

