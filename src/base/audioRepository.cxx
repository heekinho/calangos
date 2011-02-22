

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

     add_audio("mordida","models/sounds/teste.mp3");

}

 void audioRepository::add_audio(const string& name, const string& path){

     audio[name]=AM->get_sound(path);

 }

 PT(AudioSound) audioRepository::get_sound(const string& name){

     return audio[name];
 }

 PT(AudioManager) audioRepository::get_audioManager(){
     return AM;
 }


audioRepository::~audioRepository() {
    audio.clear();
}

