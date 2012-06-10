#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

//#include "player.h"
#include "windowFramework.h"
#include "maleLizard.h"
//#include "simdunas.h"
//#include "timeControl.h"

//Forward Declaration, Para referencia circular
//class Player;
//class Session;
#include "cLerpNodePathInterval.h"

class PlayerControl {
public:
	virtual ~PlayerControl();

	//Singleton
	static PlayerControl* get_instance();
	static void unload_player_control();

	static void set_key(const Event*, void *data);
	static void unset_key(const Event*, void *data);


	//static void move_forward(const Event* ev, void *data);
	static const string EV_player_move;
	static const string EV_player_bobbing;
	static const string EV_player_reproducao;
	static const string EV_player_enter_toca;
	static const string EV_player_outof_toca;
	static void update(const Event*, void *data);
	void update();
	static void event_female_next(const Event *, void *data);


	// Testando... Mesmo que não vá ficar aqui.
	static void eat(const Event*, void *data);
	static void missed_bite(const Event*, void *data);
	static void toca_control(const Event*, void *data);
	static void really_eat(const Event*, void *data);
    static void special_control(const Event*, void *data);
    static void bobbing(const Event*, void *data);
    static void reproducao(const Event*, void *data);


    //ativa desativa wireframe
    static void root_control(const Event*, void *data);

    int last_eating_frame;
    static void eating(const Event*, void *data);
	void move(float vel);
	void walk();
	void run();


	NodePath indicator;
	PT(ObjetoJogo) get_closest_biteable();
	void calc_closest_objects();

	NodePath line_indicator;



	static bool mouse_on_button;
private:
	/* Para o fadein e fadeout do bury */
	PT(CLerpNodePathInterval) _bury_interval;
    void bury_action();
    static void bury_action(const Event*, void* data);
	static void unbury_action_complete(const Event*, void* data);
	void fadein();
	void fadeout();

	PT(ObjetoJogo) _closest_biteable;

	NodePath _female_indicator;
	PT(ObjetoJogo) _closest_female;

	NodePath _toca_indicator;
	PT(ObjetoJogo) _closest_toca;

	static bool wire_frame_terrain;

	//bool is_reachable(PT(ObjetoJogo) object);

	/* Controle do Singleton */
	static bool instanceFlag;
	static PlayerControl *single;

	PlayerControl();

	map<string,bool> key_map_player;

	void fight(MaleLizard*);
};

#endif
