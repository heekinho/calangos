#ifndef PREDATOR_H
#define PREDATOR_H

#include "animatedObjetoJogo.h"
#include "animal.h"

class Predator : public Animal {
public:
	Predator(NodePath node);
	~Predator();

	static void load_predators();
	static void load_predator(const string &model, int qtd, float scale,
			int orientation = -1, Activity activity = Animal::A_day);

	virtual void act();
	virtual void pause_animation();
	virtual void continue_animation();
	virtual void change_sector(PT(Setor) new_sector);

	static void check_visibility(const Event*, void* data);
	virtual float get_visibility();

	float get_visibility_distance() const;
	void set_visibility_distance(float visibility_distance);

	float get_day_visibility() const;
	void set_day_visibility(float dvisibility);

	float get_night_visibility() const;
	void set_night_visibility(float nvisibility);

private:
	void pursuit();
	void bite();

	float visibility_distance;

	/* Se tivesse uma classe para cada predador (realmente OOP) seria estático.
	 * "Bom" é que se pode adicionar variações em cada presa. Coloca uma cega. kkkk */
	float day_visibility;
	float night_visibility;

	bool check_visibility_expired;
	bool is_attacking;
	/* Testando som */
//	PT(AudioManager) AM;
//	PT(AudioSound) sound;

	/* Círculo que mostra o raio de visibilidade de cada predador */
	NodePath debug_visibility_circle;
	float debug_dist;
};



#endif

