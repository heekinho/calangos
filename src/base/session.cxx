#include "session.h"

#include "guiManager.h"

#include "modelRepository.h"
#include "imageRepository.h"
#include "audioRepository.h"
#include "menu.h"

#include "stdio.h"
#include "audioRepository.h"

bool Session::instanceFlag = false;
Session* Session::singleSession = NULL;

#include "memoryUsage.h"
#include "memoryUsagePointers.h"
#include "inGameScreenManager.h"



/*! Constroi uma session default.*/
//Session::Session(WindowFramework *window) {
Session::Session() {
	finished_loading = false;
	stage_info.push_back("Criando Repositorio de Modelos...");
	stage_info.push_back("Criando Repositorio de Imagens...");
	stage_info.push_back("Criando Repositorio de Sons...");
	stage_info.push_back("Criando Controle de Tempo...");
	stage_info.push_back("Carregando Jogador...");
	stage_info.push_back("Criando Mundo...");
	stage_info.push_back("Inicializando Clima e Microclima...");
	stage_info.push_back("Criando Controle do Jogador...");
	stage_info.push_back("Criando Controle de Camera...");
	stage_info.push_back("Criando Interface...");
	stage_info.push_back("Distribuindo animais...");
}


/*! Inicia os controles da sessao e tals... */
void Session::init_session(int process_stage){
	switch (process_stage) {
		case 0:
			/* Sistema de Repositório de Modelos */
			nout << "Criando Repositorio de Modelos..." << endl;
			ModelRepository::get_instance()->load_models();
			break;
		case 1:
			nout << "Criando Repositorio de Imagens..." << endl;
			ImageRepository::get_instance();
			break;
		case 2:
			nout <<"Criando Repositodio de Sons..." << endl;
			audioRepository::get_instance();
			break;
		case 3:
			nout << "Criando Controle de Tempo..." << endl;
			TimeControl::get_instance();
			break;
		case 4:
			/* Cria um player padrão... */
			nout << "Carregando Jogador..." << endl;
			Player::load_player();
			break;
		case 5:
			/* Cria um controle de tempo e um mundo padrão... */
			nout << "Criando Mundo..." << endl;
			World::get_world();
			World::load_enviroment();
			break;
		case 6:
			/* inicializa clima e microclima */
			nout << "Inicializando Clima e Microclima..." << endl;
			ClimaTempo::get_instance();
			MicroClima::get_instance();
			break;
		case 7:
			nout << "Criando Controle do Jogador..." << endl;
			PlayerControl::get_instance();
			break;
		case 8:
			nout << "Criando Controle de Camera..." << endl;
			CameraControl::get_instance();
			break;
		case 9:
			/* Cria a Interface Grafica */
			nout << "Criando Interface..." << endl;
			GuiManager::get_instance();
			GuiManager::get_instance()->hide_frameNode();
			causa_mortis = -1;
			break;
		case 10:
			/* Redistribui animais para setores próximos ao player */
			nout << "Distribuindo animais..." << endl;
			Player::get_instance()->change_sector(Player::get_instance()->get_setor());
			finished_loading = true;
			break;
	}
}

/*! MainLoop. O loop principal da session */
void Session::run(){
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

	causa_mortis = -1;

	Simdunas::get_framework()->do_frame(Thread::get_current_thread());


	/* Loop principal do programa */
	Session::get_instance()->game_over = false;
	//Menu::get_instance()->hide_tela_over();
	nout << "Iniciando Jogo..." << endl;

#ifdef PSTATS
	if (!PStatClient::is_connected())
		PStatClient::connect();
#endif

	while(Simdunas::get_framework()->do_frame(Thread::get_current_thread()) && !Session::get_instance()->game_over) {
		/* O controle de tempo precisa saber o quanto de tempo se passou.
		 * Assim, todos os elementos de jogo que precisam ser atualizados, passam a escutar
		 * o evento de passagem de frame do TimeControl agindo a cada frame. */
		TimeControl::get_instance()->update_time_control(ClockObject::get_global_clock()->get_dt());
	}
	if(Session::get_instance()->game_over){
		cout<<" Reiniciando o Jogo..." << endl;
		this->end_session();

//		/* Colocando o evento para parar os vídeos das vinhetas
//		 * (ta aqui pq se não quando renicia não funciona mais) */
//		Simdunas::get_framework()->define_key("escape", "Stop_Movie", stop_movie, this);

		this->run();
	}
}

/*A morte do lagarto*/
void Session::player_death(int causa_mortis){
	/*causa_mortis  = 1, desnutrição
	 * causa_mortis  = 2, desidratação
	 * causa_mortis  = 3, alta temperatura
	 * causa_mortis  = 4, baixa temperatura
	 * causa_mortis  = 5, idade maxima
	 **depois fazer enum**/

	stop_animations();

	//cout << endl << "Morreu!" << endl;
	this->causa_mortis = causa_mortis;

	/* TODO: Deveria ser feito por evento */
	GuiManager::get_instance()->notifyGameOver();

	/* Pára o tempo */
	TimeControl::get_instance()->set_stop_time(true);
	Menu::get_instance()->tela_over(this);
}

void Session::receive_answer(char *ans){
	if(strcmp(ans, "r") == 0){
		//cout << "Pressionao Botão de Restar" << endl;
		Session::get_instance()->game_over = true;
	}
}

void Session::end_session(){
	nout << "Destruindo Tempo..." << endl;
	TimeControl::unload_timeControl();

	nout << "Destruindo Interface..." << endl;
	GuiManager::unload_gui();

	nout << "Destruindo PlayerControl..." << endl;
	PlayerControl::unload_player_control();

	nout << "Destruindo Microclima..." << endl;
	MicroClima::unload_microClima();

	nout << "Destruindo ClimaTempo..." << endl;
	ClimaTempo::unload_climaTempo();

	nout << "Destruindo ambiente de jogo..." << endl;
	World::unload_enviroment();

	nout << "Destruindo ""mundo""..." << endl;
	World::unload_world();

	nout << "Destruindo vetores..." << endl;
	Vetores::unload_vetores();


	nout << "Destruindo Controle de Camera..." << endl;
	CameraControl::unload();


	nout << "Destruindo Player..." << endl;
	Player::unload_player();
}


void Session::stop_animations(){
	Player::get_instance()->get_anim_control()->stop_all();
}

int Session::get_causa_mortis(){
	return this->causa_mortis;
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

bool Session::is_finished_loading() {
	return finished_loading;
}


//void Session::stop_movie(const Event*, void* data){
//	Menu::get_instance()->stop_movie(NULL,Menu::get_instance());
//}
