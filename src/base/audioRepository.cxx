

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
     add_audio("mordida","models/sounds/teste.mp3");

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

