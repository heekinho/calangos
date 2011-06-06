

#include <stddef.h>

#include "audioRepository.h"

audioRepository* audioRepository::instance = NULL;


audioRepository::audioRepository() {
    
    AM= AudioManager::create_AudioManager();

    load_audio();


}

audioRepository * audioRepository::get_instance(){

    if(instance==NULL){
       instance = new audioRepository();
    }

    return instance;
}

 void audioRepository::load_audio(){

     //para adicionar mais sons é só inserir aqui
     //add_audio("mordida","models/sounds/EAT1.WAV");
     //add_audio("mordida","models/sounds/eating.wav");
     add_audio("mordida","models/sounds/funny_bite.wav");
     //add_audio("mordida","models/sounds/mordida_03.mp3");
     add_audio("mordida","models/sounds/Pop_28-S_Bainbr-7952.wav");
     //add_audio("falha_mordida","models/sounds/falha_10.mp3");
     //add_audio("falha_mordida","models/sounds/falha_07.mp3");
     add_audio("falha_mordida","models/sounds/Blunk-Public_D-339.wav");
     //add_audio("mouse_on","models/sounds/Bleeep-Public_D-17.wav");
     //add_audio("mouse_on","models/sounds/Blip_1-Surround-147.wav");
     add_audio("mouse_on","models/sounds/ButtonM-wwwbeat-1899.wav");
	 //add_audio("mouse_on","models/sounds/Dink-Public_D-146.wav");
	 //add_audio("mouse_click","models/sounds/Nice_Cli-NEO_Soun-1375.wav");
	 add_audio("mouse_click","models/sounds/Click_14-Partners-48.wav");
	 //add_audio("mouse_click","models/sounds/Click_16-Partners-44.wav");
	 //add_audio("mouse_click","models/sounds/Click_17-Partners-43.wav");
	 add_audio("heart_beat","models/sounds/heartbea-dylan-1465.wav");

}

 void audioRepository::add_audio(const string& name, const string& path){

     audio[name]=AM->get_sound(path);

 }

 //quando quiser tocar um som é só chamar este método passando o nome
  void audioRepository::play_sound(const string& name){

     instance->audio[name]->play();
 }

 PT(AudioManager) audioRepository::get_audioManager(){
     return AM;
 }


audioRepository::~audioRepository() {
    audio.clear();
}

