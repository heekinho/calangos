/*
 *  screenManager.cxx
 *  Created on: 19/02/2011
 *  Author: heekinho
 */

#include "screenManager.h"
#include "screen.h"

// TODO: Tirar essa depedencia. Talvez fazer aquela ideia de GameFramework.
#include "simdunas.h"

ScreenManager::ScreenManager(){
	active_screen = NULL;
	video_manager = new VideoManager();
}

ScreenManager::~ScreenManager(){
	nout << "Deleting ScreenManager" << endl;
//	for(ScreenIterator it = screens.begin(); it != screens.end(); it++)
//		(*it).second = NULL;
//	screens.clear();
}

PT(VideoManager) ScreenManager::get_video_manager() {
	return video_manager;
}

/*! Obtém a tela ativa no momento */
PT(Screen) ScreenManager::get_active_screen(){
	return active_screen;
}

/*! Define a tela ativa. Este método é protegido, sendo que para o uso comum
 *  de definição de telas outras classes devem utilizar o método "open_screen". */
void ScreenManager::set_active_screen(PT(Screen) screen){
	active_screen = screen;
}

/*! Abre a tela especificada */
void ScreenManager::open_screen(PT(Screen) screen){
	/* Se uma tela já estava carrega, fecha-se antes. */
	if(get_active_screen()) close_screen(get_active_screen());

	/* Faz a substituição propriamente dita das telas */
	set_active_screen(screen);
	get_active_screen()->show();
}

/*! Geralmente chamado por open_screen para fechar a tela atual dando espaço
 *  para a nova. É pública pois pode haver interesse externo em efetuar tal
 *  ação, embora não seja aconselhável. */
void ScreenManager::close_screen(PT(Screen) screen){
	screen->hide();
}

/*! Retorna o gerenciador de eventos */
EventHandler* ScreenManager::get_event_handler(){
	return Simdunas::get_evt_handler();
}

/*! Retorna a fila de eventos */
EventQueue* ScreenManager::get_event_queue(){
	return Simdunas::get_evt_queue();
}

void ScreenManager::play_video(string path) {
	Simdunas::get_framework()->define_key("escape", "stop_video", stop_video, this);
	if (active_screen != NULL) {
		active_screen->hide();
	}

	video_manager->play(path);
	Simdunas::get_evt_handler()->add_hook(video_manager->get_audio_sound()->get_finished_event(), stop_video, this);
}

void ScreenManager::stop_video(const Event*, void* data) {
	ScreenManager* _this = (ScreenManager*) data;
	if (_this->video_manager->get_audio_sound() != NULL && _this->video_manager->is_playing()) {
		Simdunas::get_evt_handler()->remove_hook(_this->video_manager->get_audio_sound()->get_finished_event(), stop_video, _this);

		_this->video_manager->stop();

		if (_this->active_screen != NULL) {
			_this->active_screen->show();
		}
	}
}

bool ScreenManager::is_playing_video() {
	return video_manager->is_playing();
}
