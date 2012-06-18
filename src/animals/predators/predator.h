#ifndef PREDATOR_H
#define PREDATOR_H

#include "simdunas.h"
#include "animatedObjetoJogo.h"
#include "animal.h"


class Predator : public Animal {
public:

	enum PredatorID {
		ID_teiu,
		ID_siriema,
		ID_gato,
		ID_raposa,
		ID_jararaca,
		ID_colubridae,
		ID_coruja
	};

	enum ActState {
		AS_walking,
		AS_pursuing,
		AS_biting,
	};


	Predator(NodePath node,Predator::PredatorID type);
	virtual ~Predator();

	static void load_predators();

	static void load_predator(Predator::PredatorID type, Activity activity = Animal::A_day);

	static void event_psegundo_change_state(const Event *, void *data);
	void change_state();

	virtual void act();
	virtual void pause_animation();
	virtual void continue_animation();
	virtual void change_sector(PT(Setor) new_sector);

	void chance_act_state();

	string get_type_predator() const;
	void set_type_predator(string type);

	/*Tipos de predadores*/

	PredatorID tipo_predator_enum;

	static string get_predator_type(Predator::PredatorID type);

	void set_tipo_predator_enum(Predator::PredatorID type);
	Predator::PredatorID get_tipo_predator_enum();

	Predator::ActState  get_state();
	void set_state(Predator::ActState );

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

	static float dist_player_hide;
	static float dist_to_hunt;
	static float dist_to_bite;

	float predator_to_prey;

	PT(AnimatedObjetoJogo) get_prey();
	void set_prey(PT(AnimatedObjetoJogo) other);


	bool get_closest_player();
	void set_closest_player(bool closest);



private:

	void act_fase_2();

	ActState  act_state; //Estado atual do predador

	void pursuit();
	void pursuit(const NodePath &other);

	void bite();
	void bite_other();
	bool find_prey();

	float visibility_distance;

	/* Se tivesse uma classe para cada predador (realmente OOP) seria estático.
	 * "Bom" é que se pode adicionar variações em cada predador. Colocar um cego. kkkk */
	float day_visibility;
	float night_visibility;

	string type_predator;
	float distance_pursuit;
	float distance_bite;

	PT(AnimatedObjetoJogo) prey;
	bool hunting_lizard;//Se está perseguindo ou caçando alguma presa
	bool hunting_player;

	bool closest_to_player;//True se predador é aquele mais próximo ao player

	/* Testando som */
	//	PT(AudioManager) AM;
	//	PT(AudioSound) sound;

	/* Círculo que mostra o raio de visibilidade de cada predador */
	NodePath debug_visibility_circle;
};



#endif

