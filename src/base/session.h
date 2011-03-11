#ifndef SESSION_H
#define SESSION_H

//#define PSTATS  //se quiser rodar o pstats Ã© sÃ³ descomentar aqui

#include "world.h"
#include "guiManager.h"
#include "timeControl.h"
#include "climaTempo.h"
#include "microClima.h"
#include "cameraControl.h"
#include "player.h"
#include "playerControl.h"
//#include "menu.h"

class GuiManager;
class MicroClima;
class ClimaTempo;
//class PlayerControl;

class Session {
public:

	static Session* get_instance();
	
	void run();

	void player_death(int);

	static void stop_movie(const Event*, void *data);

	void receive_answer(char *ans);
	int get_causa_mortis();

	void stop_animations();

	bool is_finished_loading();
	void init_session(int process_stage);

	vector<string> get_stage_info();

	bool game_over;
private:

	Session();
	static bool instanceFlag;
	static Session *singleSession;

	//PT(GuiManager) gui;
	//TimeControl *time_control;
	//ClimaTempo *clima_tempo;
	//MicroClima *micro_clima;
	//CameraControl *camera_control;

	//PT(Player) player;
	//PlayerControl *player_control;

	int causa_mortis;
	vector<string> stage_info; // informações sobre as etapas de carregamento.
	bool finished_loading;
	void end_session();
};



#endif
