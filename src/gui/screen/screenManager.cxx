/*
 *  screenManager.cxx
 *  Created on: 19/02/2011
 *  Author: heekinho
 */

#include "screenManager.h"
#include "screen.h"

#include "textFont.h"

// TODO: Tirar essa depedencia. Talvez fazer aquela ideia de GameFramework.
#include "simdunas.h"
#include "audioController.h"

ScreenManager::ScreenManager(){
	active_screen = NULL;
}

ScreenManager::~ScreenManager(){
	simdunas_cat.debug() << "Deleting ScreenManager" << endl;
//	for(ScreenIterator it = screens.begin(); it != screens.end(); it++)
//		(*it).second = NULL;
//	screens.clear();
}

void ScreenManager::unload(){
	active_screen = NULL;
}

//PT(VideoManager) ScreenManager::get_video_manager() {
//	return video_manager;
//}

/*! Obtém a tela ativa no momento */
PT(Screen) ScreenManager::get_active_screen(){
	return active_screen;
}
PT(Screen) ScreenManager::get_screen(PT(Screen) screen){
	return screen;
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
	if(screen) get_active_screen()->show();
}

/*! Geralmente chamado por open_screen para fechar a tela atual dando espaço
 *  para a nova. É pública pois pode haver interesse externo em efetuar tal
 *  ação, embora não seja aconselhável. */
void ScreenManager::close_screen(PT(Screen) screen){
	screen->hide();
}

/*! Retorna o gerenciador de eventos */
EventHandler* ScreenManager::get_event_handler(){
	return event_handler;
}

/*! Retorna a fila de eventos */
EventQueue* ScreenManager::get_event_queue(){
	return event_queue;
}

PT(TextFont) ScreenManager::get_default_font(){
	return TextNode::get_default_font();
}
