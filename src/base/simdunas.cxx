#include "simdunas.h"

#include "menu.h"
#include "antialiasAttrib.h"
//TODO: Colocar constants: modelpath, soundpath, imagepath, texturepath.

//WindowProperties *win_prop;
PandaFramework* Simdunas::framework = NULL;
WindowFramework* Simdunas::window = NULL;
EventQueue* Simdunas::evt_queue = NULL;
EventHandler* Simdunas::evt_handler = NULL;

int main(int argc, char *argv[]) {
	Simdunas::init_types();

	PandaFramework framework;
	framework.open_framework(argc, argv);
	framework.set_window_title("Simdunas v1.0");

	/* Configurações Iniciais da Janela */
	WindowProperties properties = WindowProperties();
	framework.get_default_window_props(properties);

	#ifndef DEBUG
		properties.set_fullscreen(true);
	#endif

	// Define a janela, o framework, manipulação e geração de eventos e constrói uma nova sessão.
	Simdunas::set_window(framework.open_window(properties));
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

		nout << "Carregando Tela de Abertura..." << endl;

		/* Inicia o Menu */
		Menu::get_instance()->start_Menu();

		// Segura o jogo no menu até que este libere o início do jogo
		Thread *current_thread = Thread::get_current_thread();
		while (Simdunas::get_framework()->do_frame(current_thread)
				&& Menu::get_instance()->get_rodar() == false) {}

		TimeControl::virtualTime = Menu::get_instance()->get_minuto_dia_virtual();

		/* Como só chama o Menu uma vez: */
		Player::lizard_specie = Menu::get_instance()->get_especie();
		Player::lizard_gender = Player::young;

		/* Inicia uma sessão padrão */
		Session::get_instance()->run();
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
