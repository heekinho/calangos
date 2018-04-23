#ifndef MICROCLIMA_H
#define MICROCLIMA_H

#include "climaTempo.h"
#include "player.h"
#include "playerControl.h"
#include "terrain.h"

class Player;
class ClimaTempo;
class PlayerControl;

/*! Clase responsável por calcular o valor das variáveis ambientais (temperaturas e umidade relativa do ar)
* na microregião onde o personagem se encontra. Para isso ela 'recebe' os eventos de tanto de hora, quando
* atualiza os valores base, gerados pela classe climaTempo, quanto de movimentação do personagem, pois,
* a depender de onde ele esteja (exposto ao Sol, na sombra, em alguma toca), os valores de temperatura e
* umidade relativa do ar mudam. */
class MicroClima : public ReferenceCount {

public:
	MicroClima();
	~MicroClima();

	double get_temp_ar_sector();
	double get_temp_solo_sector();
	double get_temp_toca_sector();
	double get_umidade_relativa_sector();

	/* Assina evento que informa passagem de hora (virtual), ou de movimentação do lagarto. */
	static void event_player_hour_move(const Event *, void *data);

	//Singleton
	static PT(MicroClima) get_instance();
	static void unload_microClima();

	FILE *arquivo;

private:
	void atualizar_variaveis();

	//armazena temperatura do ar do setor em que o lagarto (personagem) se encontra
	double temp_ar_sector;
	//armazena temperatura do solo do setor em que o lagarto (personagem) se encontra
	double temp_solo_sector;
	/*armazena temperatura da toca (aproximadamente 20 cm abaixo da superf�cie) do setor 
	*em que o lagarto (personagem) se encontra*/
	double temp_toca_sector;
	//armazena umidade relativa do ar do setor em que o lagarto (personagem) se encontra
	double umidade_relativa_sector;

	static bool instanceFlag;
	static PT(MicroClima) single;
};

#endif
