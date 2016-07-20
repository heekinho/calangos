#ifndef SESSION_H
#define SESSION_H

//#define PSTATS  //se quiser rodar o pstats é só descomentar aqui

//#include "cIntervalManager.h"
//#include "world.h"
//#include "guiManager.h"
//#include "timeControl.h"
//#include "climaTempo.h"
//#include "microClima.h"
//#include "cameraControl.h"
#include "player.h"
//#include "playerControl.h"
//#include "menu.h"

//class GuiManager;
//class MicroClima;
//class ClimaTempo;
//class PlayerControl;

#include "referenceCount.h"

class History;
class stateHistory;

class Session {
public:
	static Session* get_instance();
	
	void run();

	void player_death(Player::PlayerDeathType death);
	Player::PlayerDeathType get_player_death_status() const;

//	static void stop_movie(const Event*, void *data);

	static void pause_game(const Event*, void *data);

	void receive_answer(char *ans);
//	int get_causa_mortis();

	void stop_animations();

	bool is_finished_loading();
	void init_session(int process_stage);

	vector<string> get_stage_info();

	bool game_over;

	bool mouse_on_screen;

	/* Obtém a fase do jogo selecionada pelo jogador */
	int get_level(){ return level; };
	void set_level(int level) { this->level = level; };


	PT(History) history() const;
	PT(stateHistory) shistory() const;
	/* Obtém o nível de dificuldade selecionado pelo jogador */
	int get_difficulty_level() {
		return difficulty_level;
	}

	void set_difficulty_level(int difficulty_level) {
		this->difficulty_level = difficulty_level;
	}

	bool is_lizard_adult() {
		return is_adult;
	}

	void set_is_adult(bool is_adult) {
		this->is_adult = is_adult;
	}

private:

	PT(History) _history;
	PT(stateHistory) _shistory;

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

	/* Converter para enum depois? */
	int level;

	int difficulty_level;

	bool is_adult;

	Player::PlayerDeathType _player_death_status;

//	int causa_mortis;
	vector<string> stage_info; // informações sobre as etapas de carregamento.
	bool finished_loading;
	void end_session();
};

#endif
