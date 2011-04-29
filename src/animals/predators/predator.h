#ifndef PREDATOR_H
#define PREDATOR_H

#include "animatedObjetoJogo.h"
#include "animal.h"

class Predator : public Animal {
public:
	Predator(NodePath node);
	~Predator();

	static void load_predators();
	static void load_predator(const string &model, int qtd, float scale, int orientation = -1);

	virtual void act();
	virtual void pause_animation();
	virtual void continue_animation();
	virtual void change_sector(PT(Setor) new_sector);

	virtual float get_visibility();

	float get_visibility_distance() const;
	void set_visibility_distance(float visibility_distance);

private:
	void pursuit();
	void bite();

	float visibility_distance;

	/* Testando som */
	PT(AudioManager) AM;
	PT(AudioSound) sound;
};



#endif

