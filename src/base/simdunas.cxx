#include "simdunas.h"

#include "load_prc_file.h"

#include "menu.h"
#include "antialiasAttrib.h"

#include "movieAudio.h"
#include "audioSound.h"

#include "pStatClient.h"
#include "gameOptionsScreen.h"

//TODO: Colocar constants: modelpath, soundpath, imagepath, texturepath.

//WindowProperties *win_prop;
PandaFramework* Simdunas::framework = NULL;
WindowFramework* Simdunas::window = NULL;
EventQueue* Simdunas::evt_queue = NULL;
EventHandler* Simdunas::evt_handler = NULL;
bool Simdunas::play_clicked = false;

#include "objetoJogo.h"
#include "animal.h"
#include "sectorItems.h"

#include "screen.h"
#include "screenManager.h"
#include "calangosMenuManager.h"

int main(int argc, char *argv[]) {
	/* Carrega o arquivo de configuração do jogo */
#if DEBUG
	load_prc_file("myConfig-Calangos-develop.prc");
#else
	load_prc_file("myConfig-Calangos-distribute.prc");
#endif

	TextNode::set_default_encoding(TextNode::E_utf8);
	Simdunas::init_types();

	PandaFramework framework;
	framework.open_framework(argc, argv);
	/*AJUSTAR NOME DA VERSÃO A CADA RELEASE*/
	framework.set_window_title("Simdunas v1.0 beta");


	/* Configurações Iniciais da Janela */
	//	WindowProperties properties = WindowProperties();
	//	framework.get_default_window_props(properties);
	//	properties.set_fullscreen(true);

	// Define a janela, o framework, manipulação e geração de eventos e constrói uma nova sessão.
	Simdunas::set_window(framework.open_window(/*properties*/));
	Simdunas::set_framework(Simdunas::get_window()->get_panda_framework());
	Simdunas::set_evt_queue(EventQueue::get_global_event_queue());
	Simdunas::set_evt_handler(EventHandler::get_global_event_handler(Simdunas::get_evt_queue()));

	Session::get_instance();
	//Simdunas::set_session(new Session());

	// Verifica se a janela abriu direitin :)
	if (Simdunas::get_window() != (WindowFramework *) NULL) {
		Simdunas::get_window()->enable_keyboard();
		//Simdunas::get_window()->setup_trackball();
		//Simdunas::get_framework()->enable_default_keys();

		//Simdunas::get_window()->get_render().set_antialias(AntialiasAttrib::M_multisample);


		/* Novo sistema de menu começa aqui, descomente para testar */
		PT(CalangosMenuManager) menu_manager = new CalangosMenuManager();
		Thread *current_thread = Thread::get_current_thread();
		while(Simdunas::get_framework()->do_frame(current_thread) && !Simdunas::is_play_clicked()){
			Simdunas::get_framework()->do_frame(current_thread);
			if(menu_manager->is_playing_movie()){//verifica se a vinheta ta sendo tocada
				if (menu_manager->get_sound()->get_time() <= 62) {//verifica se o video chegou ao fim(DEPOIS PROCURAR UMA OUTRA FORMA DE FAZER)
					menu_manager->get_audio_manager()->update(); //é necessário atualizar a cada frame
				}
				else {
					menu_manager->stop_movie(NULL,menu_manager);//quando chegar chama o método que para

				}
			}
		}
		/* Novo sistema de menu termina aqui */

		//		nout << "Carregando Tela de Abertura..." << endl;
		//
		//		/* Inicia o Menu */
		//		Menu::get_instance()->start_Menu();
		//
		//		// Segura o jogo no menu até que este libere o início do jogo
		////		Thread *current_thread = Thread::get_current_thread();
		//		while (!Simdunas::is_play_clicked()) {
		//			Simdunas::get_framework()->do_frame(current_thread);
		//			if(Menu::get_instance()->get_playing_movie()){//verifica se a vinheta ta sendo tocada
		//				if (Menu::get_instance()->get_sound()->get_time() <= 62) {//verifica se o video chegou ao fim(DEPOIS PROCURAR UMA OUTRA FORMA DE FAZER)
		//					Menu::get_instance()->get_audioManager()->update(); //é necessário atualizar a cada frame
		//				}
		//				else {
		//					Menu::get_instance()->stop_movie(NULL,Menu::get_instance());//quando chegar chama o método que para
		//
		//				}
		//			}
		//		}

		Simdunas::get_framework()->do_frame(current_thread);

		/* FIX: Se o usuário já fechou a janela, não executar mais nada do jogo */
		if(!Simdunas::get_window()->get_graphics_window()->get_properties().get_open()) return 0;

		TimeControl::virtualTime = Menu::get_instance()->get_minuto_dia_virtual();

		/* Como só chama o Menu uma vez: */
//		Player::lizard_specie = Menu::get_instance()->get_especie();
		Player::lizard_specie = ((GameOptionsScreen*) menu_manager->get_game_options_screen().p())->get_especie();
		Player::lizard_gender = Player::young;

		//		/* Inicia uma sessão padrão */
		//		Session::get_instance()->run();
		LoadingScreen* loading_screen = (LoadingScreen*) menu_manager->get_loading_screen().p();
		loading_screen->loading_process();
	} else {
		nout << "Nao foi possivel carregar a janela" << endl;
	}

	Simdunas::get_framework()->close_framework();
	return (0);
}


void Simdunas::init_types(){
	//TODO: Colocar todos os objetos TypedReferenceCount aqui!!!
	ObjetoJogo::init_type();
}


PandaFramework* Simdunas::get_framework() {
	return Simdunas::framework;
}

void Simdunas::set_framework(PandaFramework* framework){
	Simdunas::framework = framework;
}

WindowFramework* Simdunas::get_window(){
	return Simdunas::window;
}

void Simdunas::set_window(WindowFramework* window){
	Simdunas::window = window;
}

EventHandler* Simdunas::get_evt_handler(){
	return Simdunas::evt_handler;
}

void Simdunas::set_evt_handler(EventHandler *evt_handler){
	Simdunas::evt_handler = evt_handler;
}

EventQueue* Simdunas::get_evt_queue(){
	return Simdunas::evt_queue;
}

void Simdunas::set_evt_queue(EventQueue *evt_queue){
	Simdunas::evt_queue = evt_queue;
}

bool Simdunas::is_play_clicked() {
	return Simdunas::play_clicked;
}

void Simdunas::set_play_clicked(bool flag) {
	Simdunas::play_clicked = flag;
}

