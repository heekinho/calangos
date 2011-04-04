#include "simdunas.h"

#include "load_prc_file.h"

#include "menu.h"
#include "antialiasAttrib.h"

#include "movieAudio.h"
#include "audioSound.h"
#include "objetoJogo.h"
#include "animal.h"
#include "sectorItems.h"

#include "screen.h"
#include "screenManager.h"
#include "calangosMenuManager.h"
#include "pStatClient.h"
#include "gameOptionsScreen.h"
#include "pgTop.h"
#include "loadingScreen.h"

//TODO: Colocar constants: modelpath, soundpath, imagepath, texturepath.

//WindowProperties *win_prop;
PandaFramework* Simdunas::framework = NULL;
WindowFramework* Simdunas::window = NULL;
EventQueue* Simdunas::evt_queue = NULL;
EventHandler* Simdunas::evt_handler = NULL;
GuiLayer* Simdunas::pixel2d = NULL;
NodePath Simdunas::clickable_render_2d = NULL;
bool Simdunas::play_clicked = false;

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
		Simdunas::set_pixel_2d(new GuiLayer(Simdunas::get_window()));
		Simdunas::get_window()->enable_keyboard();
		//Simdunas::get_window()->setup_trackball();
		//Simdunas::get_framework()->enable_default_keys();

		//Simdunas::get_window()->get_render().set_antialias(AntialiasAttrib::M_multisample);

		Simdunas::setup_clickable_render_2d();

		PT(CalangosMenuManager) menu_manager = new CalangosMenuManager();
		menu_manager->get_sound()->play();
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

		Simdunas::get_framework()->do_frame(current_thread);

		/* FIX: Se o usuário já fechou a janela, não executar mais nada do jogo */
		if(!Simdunas::get_window()->get_graphics_window()->get_properties().get_open()) return 0;

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

// Configura o nosso clickable_render_2d.
// Isso que foi feito aqui foi tirado do próprio código do Panda pois
// eles fazem o mesmo com o aspect_2d. Nós precisamos fazer isso porque
// houve a necessidade de capturar eventos de mouse no render_2d.
void Simdunas::setup_clickable_render_2d() {
	PGTop* top = new PGTop("clickable_render_2d");
	Simdunas::set_clickable_render_2d(Simdunas::get_window()->get_render_2d().attach_new_node(top));

	// Tell the PGTop about our MouseWatcher object, so the PGui
	// system can operate.
	PandaNode *mouse_node = Simdunas::get_window()->get_mouse().node();
	if (mouse_node->is_of_type(MouseWatcher::get_class_type())) {
		top->set_mouse_watcher(DCAST(MouseWatcher, mouse_node));
	}
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

void Simdunas::set_clickable_render_2d(NodePath node) {
	Simdunas::clickable_render_2d = node;
}

NodePath Simdunas::get_clickable_render_2d() {
	return Simdunas::clickable_render_2d;
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

