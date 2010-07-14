#ifndef ANIMAL_H
#define ANIMAL_H

#include "animatedObjetoJogo.h"

class Animal : public AnimatedObjetoJogo {
public:
	Animal(NodePath node);
	static void load_animals();

	~Animal();
	static void unload_animals();

	static void act(const Event*, void *data);
	virtual void act();

	//virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector);
	static void redistribute_animals();
	static void migrate_animals(vector<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to);
	static void migrate_animal(PT(ObjetoJogo) theanimal, PT(Setor) to);

	/* Ações relacionadas ao movimento */
	virtual float get_velocity() { return velocity; };
	virtual void set_velocity(float velocity) { this->velocity = velocity; };


	virtual void pause_animation(){};
	virtual void continue_animation(){};

	void set_frames_stopped(int frames);

	static NodePath animals_placeholder;
protected:
	virtual int stay_quiet();
	int stay_x_frame_stoped;

	float velocity;
};

#endif
