#include "cIntervalManager.h"

#include "history.h"
#include "stateHistory.h"
#include "session.h"

#include "guiManager.h"

#include "modelRepository.h"
#include "imageRepository.h"
#include "audioRepository.h"

#include "stdio.h"


bool Session::instanceFlag = false;
Session* Session::singleSession = NULL;

#include "memoryUsage.h"
#include "memoryUsagePointers.h"
#include "calangosMenuManager.h"
#include "loadingScreen.h"
#include "pauseScreen.h"
#include "achievements.h"

#include "world.h"
#include "cameraControl.h"
#include "inGameScreenManager.h"
#include "videoManager.h"
#include "mouseWatcher.h"

/*! Constroi uma session default.*/
//Session::Session(WindowFramework *window) {
Session::Session() {
	_player_death_status = Player::PDT_NOT_DEAD;
	level = 1;

	_history = new CalangosHistory();
	

	finished_loading = false;
	stage_info.push_back(ConfigVariableString("msg-cri1", "Criando Repositorio de Modelos..."));
	stage_info.push_back(ConfigVariableString("msg-cri2", "Criando Repositorio de Imagens..."));
	stage_info.push_back(ConfigVariableString("msg-cri3", "Criando Repositorio de Sons..."));
	stage_info.push_back(ConfigVariableString("msg-cri4", "Criando Controle de Tempo..."));
	stage_info.push_back(ConfigVariableString("msg-cri5", "Carregando Jogador..."));
	stage_info.push_back(ConfigVariableString("msg-cri6", "Formação do Mundo..."));
	stage_info.push_back(ConfigVariableString("msg-cri7", "Inicializando Clima e Microclima..."));
	stage_info.push_back(ConfigVariableString("msg-cri8", "Criando Controle do Jogador..."));
	stage_info.push_back(ConfigVariableString("msg-cri9", "Criando Controle de Camera..."));
	stage_info.push_back(ConfigVariableString("msg-cri10", "Criando Interface..."));
	stage_info.push_back(ConfigVariableString("msg-cri11", "Distribuindo Animais..."));
}


/*! Inicia os controles da sessao e tals... */
void Session::init_session(int process_stage){
	simdunas_cat.debug() << stage_info[process_stage] << endl;
	switch (process_stage) {
		case 0:
			/* Sistema de Repositório de Modelos */
//			simdunas_cat.debug() << "Criando Repositorio de Modelos..." << endl;
			ModelRepository::get_instance()->load_models();
			break;
		case 1:
//			simdunas_cat.debug() << "Criando Repositorio de Imagens..." << endl;
			ImageRepository::get_instance();
			break;
		case 2:
			//simdunas_cat.debug() <<"Criando Repositodio de Sons..." << endl;
			//audioRepository::get_instance();
			// retirar essa etapa
			break;
		case 3:
//			simdunas_cat.debug() << "Criando Controle de Tempo..." << endl;
			TimeControl::get_instance();
			break;
		case 4:
			/* Cria um player padrão... */
//			simdunas_cat.debug() << "Carregando Jogador..." << endl;
			Player::load_player();
			break;
		case 5:
			/* Cria um controle de tempo e um mundo padrão... */
//			simdunas_cat.debug() << "Criando Mundo..." << endl;
			World::get_world();
			World::load_enviroment();
			break;
		case 6:
			/* inicializa clima e microclima */
//			simdunas_cat.debug() << "Inicializando Clima e Microclima..." << endl;
			ClimaTempo::get_instance();
			MicroClima::get_instance();
			break;
		case 7:
//			simdunas_cat.debug() << "Criando Controle do Jogador..." << endl;
			PlayerControl::get_instance();
			break;
		case 8:
//			simdunas_cat.debug() << "Criando Controle de Camera..." << endl;
			CameraControl::get_instance();
			break;
		case 9:
			/* Cria a Interface Grafica */
//			simdunas_cat.debug() << "Criando Interface..." << endl;
			GuiManager::get_instance();
			GuiManager::get_instance()->hide_frameNode();
			InGameScreenManager::get_instance();
			break;
		case 10:
			/* Redistribui animais para setores próximos ao player */
//			simdunas_cat.debug() << "Distribuindo animais..." << endl;
			player->change_sector(player->get_setor());
			finished_loading = true;
			break;
	}
}

/*! MainLoop. O loop principal da session */
void Session::run(){
	finished_loading = false;
	//	/* Inicializa de fato a sessao, para então rodar o loop principal */
	//	init_session();
	//
	//	GuiManager::get_instance()->hide_frameNode();
	//
	//	LoadScreenStage1::get_instance()->loading_completed();

	//	while (!start) {
	//		Simdunas::get_framework()->do_frame(Thread::get_current_thread());
	//	}

	GuiManager::get_instance()->show_frameNode();

//	causa_mortis = -1;
	_player_death_status = Player::PDT_NOT_DEAD;


	Simdunas::get_framework()->do_frame(Thread::get_current_thread());

	/* Loop principal do programa */
	Session::get_instance()->game_over = false;
	//Menu::get_instance()->hide_tela_over();
	simdunas_cat.debug() << "Iniciando Jogo... Fase: " << get_level() << endl;

#ifdef PSTATS
	if (!PStatClient::is_connected())
		PStatClient::connect();
#endif

	TimeControl::get_instance()->notify("count_seconds_untouched", Achievements::count_seconds_untouched, player->get_achievements(), 1);

	/* Define a tecla de pause */
	Simdunas::get_framework()->define_key("escape", "Pause Game", pause_game, this);

	while(Simdunas::get_framework()->do_frame(Thread::get_current_thread()) && !Session::get_instance()->game_over) {
		MouseWatcher *mwatcher = DCAST(MouseWatcher, window->get_mouse().node());
		if(!mwatcher->has_mouse()){
			mouse_on_screen = false;
		}

		/* O controle de tempo precisa saber o quanto de tempo se passou.
		 * Assim, todos os elementos de jogo que precisam ser atualizados, passam a escutar
		 * o evento de passagem de frame do TimeControl agindo a cada frame. */
		TimeControl::get_instance()->update_time_control(global_clock->get_dt());
		CIntervalManager::get_global_ptr()->step();
	}
	if(Session::get_instance()->game_over){
		simdunas_cat.debug()<<" Reiniciando o Jogo..." << endl;
		this->end_session();

//		/* Colocando o evento para parar os vídeos das vinhetas
//		 * (ta aqui pq se não quando renicia não funciona mais) */
//		Simdunas::get_framework()->define_key("escape", "Stop_Movie", stop_movie, this);

		CalangosMenuManager::get_instance()->set_loading_screen(new LoadingScreen(CalangosMenuManager::get_instance().p()));
		CalangosMenuManager::get_instance()->open_screen(CalangosMenuManager::get_instance()->get_loading_screen());
		((LoadingScreen*) CalangosMenuManager::get_instance()->get_loading_screen().p())->loading_process();
//		this->run();
	}
}


/*! Pausa o jogo e chama a tela de pause */
void Session::pause_game(const Event*, void *data){
	PauseScreen* pause_screen = (PauseScreen*) InGameScreenManager::get_instance()->get_pause_screen().p();
	//InGameScreenManager::get_instance()->open_screen(pause_screen);
	simdunas_cat.debug()<<"evento chama pause"<<endl;
	if (!PauseScreen::is_opened) {
		simdunas_cat.debug()<<"tela de pause nao esta aberta!"<<endl;
		pause_screen->show();
	}
	else if (PauseScreen::selected_video) {
		simdunas_cat.debug()<<"esta tocando video! Parando o video agora!"<<endl;
		VideoManager::stop_video(NULL, NULL);
		pause_screen->show();
	}
	else {
		simdunas_cat.debug()<<"tela de pause aberta, fechando a tela"<<endl;
		pause_screen->show();
	}

	/* É pq pausou */
	if(TimeControl::get_instance()->get_stop_time()){
		event_queue->queue_event(new Event("calangos-pause-in"));
	}
	else {
		event_queue->queue_event(new Event("calangos-pause-out"));
	}
}


/*! A morte do lagarto */
void Session::player_death(Player::PlayerDeathType death){
	/* Pequeno bugfix para não permitir múltiplas mortes */
	if(_player_death_status != Player::PDT_NOT_DEAD) {
		simdunas_cat.debug() << "Já tá morto! Só é permitido morrer uma vez! lol" << endl;
		return;
	}

	stop_animations();

	//simdunas_cat.debug() << endl << "Morreu!" << endl;
//	this->causa_mortis = causa_mortis;
	_player_death_status = death;

	/* TODO: Deveria ser feito por evento */
	GuiManager::get_instance()->notifyGameOver();

	/* Pára o tempo */
	TimeControl::get_instance()->set_stop_time(true);
	InGameScreenManager::get_instance()->open_screen(InGameScreenManager::get_instance()->get_game_over_screen());
}

Player::PlayerDeathType Session::get_player_death_status() const {
	return _player_death_status;
}

void Session::receive_answer(char *ans){
	if(strcmp(ans, "r") == 0){
		//simdunas_cat.debug() << "Pressionao Botão de Restar" << endl;
		Session::get_instance()->game_over = true;
	}
}

void Session::end_session(){
	simdunas_cat.debug() << "Destruindo Tempo..." << endl;
	TimeControl::unload_timeControl();

	simdunas_cat.debug() << "Destruindo Interface..." << endl;
	GuiManager::unload_gui();

	simdunas_cat.debug() << "Destruindo PlayerControl..." << endl;
	PlayerControl::unload_player_control();

	simdunas_cat.debug() << "Destruindo Microclima..." << endl;
	MicroClima::unload_microClima();

	simdunas_cat.debug() << "Destruindo ClimaTempo..." << endl;
	ClimaTempo::unload_climaTempo();

	simdunas_cat.debug() << "Destruindo ambiente de jogo..." << endl;
	World::unload_enviroment();

	simdunas_cat.debug() << "Destruindo ""mundo""..." << endl;
	World::unload_world();

	simdunas_cat.debug() << "Destruindo Controle de Camera..." << endl;
	CameraControl::unload();

	simdunas_cat.debug() << "Destruindo Player..." << endl;
	Player::unload_player();
}

/*! Tem o intuito de parar todas as animações. TODO: Ainda não faz a funcionalidade */
void Session::stop_animations(){
	player->get_anim_control()->stop_all();
}

Session* Session::get_instance() {
	if(!instanceFlag) {
		singleSession = new Session();
		instanceFlag = true;
	}
	return singleSession;
}

vector<string> Session::get_stage_info() {
	return stage_info;
}

/*! Verifica se o processo de carregamento já terminou */
bool Session::is_finished_loading() {
	return finished_loading;
}

//void Session::stop_movie(const Event*, void* data){
//	Menu::get_instance()->stop_movie(NULL,Menu::get_instance());
//}


PT(History) Session::history() const {
	return _history;
}
