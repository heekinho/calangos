#ifndef PREDATOR_H
#define PREDATOR_H

#include "animatedObjetoJogo.h"
#include "animal.h"

class Predator : public Animal {
public:

	enum types_predator{
			teiu,
			siriema,
			gato,
			raposa,
			jararaca,
			colubridae,
			coruja
	};



	Predator(NodePath node,Predator::types_predator type);
	~Predator();

	static void load_predators();

	static void load_predator(Predator::types_predator type, int qtd, float scale,
				int orientation = -1, Activity activity = Animal::A_day);


	virtual void act();
	virtual void pause_animation();
	virtual void continue_animation();
	virtual void change_sector(PT(Setor) new_sector);


	string get_type_predator() const;
	void set_type_predator(string type);

	/*Tipos de predadores*/

	types_predator tipo_predator_enum;
	static string get_predator_type(Predator::types_predator type);

	void set_tipo_predator_enum(Predator::types_predator type);
	Predator::types_predator get_tipo_predator_enum();


	virtual float get_visibility();

	float get_visibility_distance() const;
	void set_visibility_distance(float visibility_distance);

	float get_day_visibility() const;
	void set_day_visibility(float dvisibility);

	float get_night_visibility() const;
	void set_night_visibility(float nvisibility);

	float get_distance_pursuit() ;
	void set_distance_pursuit(float distance);

	float get_distance_bite() ;
	void set_distance_bite(float distance);

	float get_visibility_factor() const;

	static bool pursuing;

	static float const dist_player_hide = 3.5*3.5;
private:


	void pursuit();
	void bite();

	float visibility_distance;

	/* Se tivesse uma classe para cada predador (realmente OOP) seria estático.
	 * "Bom" é que se pode adicionar variações em cada predador. Colocar um cego. kkkk */
	float day_visibility;
	float night_visibility;

	string type_predator;
	float distance_pursuit;
	float distance_bite;

	/* Testando som */
//	PT(AudioManager) AM;
//	PT(AudioSound) sound;

	/* Círculo que mostra o raio de visibilidade de cada predador */
	NodePath debug_visibility_circle;
};



#endif

