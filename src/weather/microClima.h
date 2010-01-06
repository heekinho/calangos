#ifndef MICROCLIMA_H
#define MICROCLIMA_H

#include "climaTempo.h"
#include "player.h"
#include "playerControl.h"
#include "terrain.h"

class Player;
class ClimaTempo;
class PlayerControl;

class MicroClima : public TypedReferenceCount{

public:
	MicroClima();
	~MicroClima();

	double get_temp_ar_sector();
	double get_temp_solo_sector();
	double get_temp_toca_sector();
	double get_umidade_relativa_sector();

	static void event_player_hour_move(const Event *, void *data);

	//Singleton
	static PT(MicroClima) get_instance();
	static void unload_microClima();

	FILE *arquivo;
	// Typed Object
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "MicroClima"); }

private:
	void atualizar_variaveis();

	double temp_ar_sector;
	double temp_solo_sector;
	double temp_toca_sector;
	double umidade_relativa_sector;

	static bool instanceFlag;
	static PT(MicroClima) single;

	static TypeHandle _type_handle;
};

#endif
