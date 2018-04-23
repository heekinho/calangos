#include "simdunas.h"

#include "load_prc_file.h"

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
#include "audioController.h"
#include "debugTools.h"

//TODO: Colocar constants: modelpath, soundpath, imagepath, texturepath.

//WindowProperties *win_prop;
PandaFramework* Simdunas::pframework = NULL;
WindowFramework* Simdunas::pwindow = NULL;
GuiLayer* Simdunas::pixel2d = NULL;
NodePath Simdunas::clickable_render_2d = NULL;
bool Simdunas::play_clicked = false;
TextFont* Simdunas::game_font = NULL;

NotifyCategoryDef(simdunas, "");

PT(DebugTools) debug;

#include "gameSession.h"

int main(int argc, char *argv[]) {


	/* Carrega o arquivo de configuração do jogo */
#if DEBUG
	load_prc_file("myConfig-Calangos-develop.prc");
#else
	load_prc_file("myConfig-Calangos-distribute.prc");
#endif

	/* Configurações de jogo */
	load_prc_file("config/calangos.prc");
	
	
	TextNode::set_default_encoding(TextNode::E_utf8);
	Simdunas::game_font = FontPool::load_font("models/gui/fonts/suplexcomic-large");

	Simdunas::init_types();

	PandaFramework framework;
	framework.open_framework(argc, argv);

	/* TODO: Ajustar nome a cada versão do release */
	framework.set_window_title("Calangos");


	/* Configurações Iniciais da Janela */
	WindowProperties properties = WindowProperties();
	framework.get_default_window_props(properties);
	properties.set_fullscreen(true);
	int width = framework.get_default_pipe()->get_display_width();
	int height = framework.get_default_pipe()->get_display_height();
	if(width > 0 && height > 0){
		properties.set_size(width, height);
	}

#if DEBUG
	Simdunas::set_window(framework.open_window(/*properties*/));
#else
	Simdunas::set_window(framework.open_window(properties,  0));
#endif

	// Define a janela, o framework, manipulação e geração de eventos e constrói uma nova sessão.
	Simdunas::set_framework(window->get_panda_framework());

	PT(Thread) current_thread = Thread::get_current_thread();


	// Verifica se a janela abriu direitin :)
	if (window != (WindowFramework *) NULL) {
		Simdunas::set_pixel_2d(new GuiLayer(window));
		window->enable_keyboard();
		//window->setup_trackball();
		//Simdunas::get_framework()->enable_default_keys();

		//render.set_antialias(AntialiasAttrib::M_multisample);

		Simdunas::setup_clickable_render_2d();

		/* O vídeo deve ser a primeira coisa a ser rodado. Sem maior espera */
//		PT(ScreenManager) initial_manager = new ScreenManager();
//		PT(VideoScreen) video_screen = new VideoScreen(initial_manager);
//		initial_manager->open_screen((PT(Screen)) video_screen);






		string video_path = "models/videos/vinheta_opcao_1_mpeg4.avi";
		Simdunas::get_framework()->define_key("escape", "stop_video", VideoManager::stop_video, VideoManager::get_instance());
		VideoManager::get_instance()->play_openning(video_path);
		simdunas_cat.debug() << "Starting Video" << endl;

		while (VideoManager::get_instance()->is_playing()) {
			Simdunas::get_framework()->do_frame(current_thread);
			VideoManager::get_instance()->get_audio_manager()->update();
		}

		event_handler->remove_hook("escape", VideoManager::stop_video, VideoManager::get_instance());










//		/* Descarrega o manager */
//		initial_manager->unload();
//		simdunas_cat.debug() << "Video Screen Ref Count: " << video_screen->get_ref_count() << endl;
//		simdunas_cat.debug() << "Initial Manager: " << initial_manager->get_ref_count() << endl;
//		video_screen = NULL;
//		initial_manager = NULL;

//		return 0;

		if(ConfigVariableBool("calangos-want-debugtools", true)) debug = new DebugTools();

//	//	PT(GameSession) game_session = new GameSession();
//	//	game_session->verify_references();
//	//	game_session->_debug_tools = debug;
//	//	game_session->verify_references();
//	//	simdunas_cat.debug().flush();
//	//	simdunas_cat.debug() << "Closing..." << endl;
//	//	return 0;
//
//		/* Pode criar a sessão. A inicialização é depois. */
//		Session::get_instance();
//		//Simdunas::set_session(new Session());
//
//		AudioController::get_instance();

		CalangosMenuManager::get_instance();

////		menu_manager->get_sound()->play();
//		Thread *current_thread = Thread::get_current_thread();
		while(!Simdunas::is_play_clicked()){
			Simdunas::get_framework()->do_frame(current_thread);
//			if (menu_manager->is_playing_video()) {
//				menu_manager->get_video_manager()->get_audio_manager()->update();
//			}
		}
//
		Simdunas::get_framework()->do_frame(current_thread);

		/* FIX: Se o usuário já fechou a janela, não executar mais nada do jogo */
		if(!window->get_graphics_window()->get_properties().get_open()) return 0;

//		Player::lizard_gender = Player::LG_YOUNG;

		//		/* Inicia uma sessão padrão */
		//		Session::get_instance()->run();
		((LoadingScreen*)CalangosMenuManager::get_instance()->get_loading_screen().p())->loading_process();
		CalangosMenuManager::get_instance()->unload_menus();
		Session::get_instance()->run();
	} else {
		simdunas_cat.debug() << "Nao foi possivel carregar a janela" << endl;
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
	Simdunas::set_clickable_render_2d(window->get_render_2d().attach_new_node(top));

	// Tell the PGTop about our MouseWatcher object, so the PGui
	// system can operate.
	PandaNode *mouse_node = window->get_mouse().node();
	if (mouse_node->is_of_type(MouseWatcher::get_class_type())) {
		top->set_mouse_watcher(DCAST(MouseWatcher, mouse_node));
	}
}


void Simdunas::init_types(){
	//TODO: Colocar todos os objetos TypedReferenceCount aqui!!!
	ObjetoJogo::init_type();
}


PandaFramework* Simdunas::get_framework() {
	return Simdunas::pframework;
}

void Simdunas::set_framework(PandaFramework* pframework){
	Simdunas::pframework = pframework;
}

WindowFramework* window{
	return Simdunas::pwindow;
}

void Simdunas::set_window(WindowFramework* the_window){
	Simdunas::pwindow = the_window;
}

void Simdunas::set_clickable_render_2d(NodePath node) {
	Simdunas::clickable_render_2d = node;
}

NodePath Simdunas::get_clickable_render_2d() {
	return Simdunas::clickable_render_2d;
}

bool Simdunas::is_play_clicked() {
	return Simdunas::play_clicked;
}

void Simdunas::set_play_clicked(bool flag) {
	Simdunas::play_clicked = flag;
}

TextFont* Simdunas::get_game_font() {
	return Simdunas::game_font;
}

