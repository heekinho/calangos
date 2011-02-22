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



/*! Constroi uma session default.*/
//Session::Session(WindowFramework *window) {
Session::Session() {
}


/*! Inicia os controles da sessao e tals... */
void Session::init_session(){
	/* Sistema de Repositório de Modelos */
	nout << "Criando Repositorio de Modelos..." << endl;
	ModelRepository::get_instance();

	nout << "Criando Repositorio de Imagens..." << endl;
	ImageRepository::get_instance();

        nout <<"Criando Repositodio de Sons..." << endl;
        audioRepository::get_instance();

	nout << "Criando Controle de Tempo..." << endl;
	TimeControl::get_instance();

	/* Cria um player padrão... */
	nout << "Carregando Jogador..." << endl;
	Player::load_player();

	/* Cria um controle de tempo e um mundo padrão... */
	nout << "Criando Mundo..." << endl;
	World::get_world();
	World::load_enviroment();

	/* inicializa clima e microclima */
	nout << "Inicializando Clima e Microclima..." << endl;
	ClimaTempo::get_instance();
	MicroClima::get_instance();

	nout << "Criando Controle do Jogador..." << endl;
	PlayerControl::get_instance();

	nout << "Criando Controle de Camera..." << endl;
	CameraControl::get_instance();

	/* Cria a Interface Grafica */
	nout << "Criando Interface..." << endl;
	GuiManager::get_instance();
	causa_mortis = -1;

	/* Redistribui animais para setores próximos ao player */
	Player::get_instance()->change_sector(Player::get_instance()->get_setor());
}

/*! MainLoop. O loop principal da session */
void Session::run(){
	/* Inicializa de fato a sessao, para então rodar o loop principal */
	init_session();
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

		/* Colocando o evento para parar os vídeos das vinhetas
		 * (ta aqui pq se não quando renicia não funciona mais) */
		Simdunas::get_framework()->define_key("escape", "Stop_Movie", stop_movie, this);
	
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


void Session::stop_movie(const Event*, void* data){
	/* Apenas chama o stop_movie de menu que vai parar os vídeos efetivamente */
	Menu::get_instance()->stop_movie(NULL,Menu::get_instance());

	
}
