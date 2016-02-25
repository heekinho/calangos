#ifndef ANIMAL_H
#define ANIMAL_H

#include "animatedObjetoJogo.h"

class Animal : public AnimatedObjetoJogo {

public:
	enum Activity {
		A_day,
		A_night,
		A_both
	};

	Animal(NodePath node);
	static void load_animals();
	
	virtual ~Animal();
	static void unload_animals();

	static void act(const Event*, void *data);
	virtual void act();



	//virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector) = 0;
	static void redistribute_animals();
	static void migrate_animals(list<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to);
	static void migrate_animal(PT(ObjetoJogo) theanimal, PT(Setor) to);

	/* Ações relacionadas ao movimento */
	/* Precisava mesmo ser virtual??? =/ */
	virtual float get_velocity() const { return _velocity; };
	virtual void set_velocity(float velocity) { this->_velocity = velocity; };

	Activity get_activity() const;
	void set_activity(Activity activity);

	virtual void pause_animation(){};
	virtual void continue_animation(){};

	void set_frames_stopped(int frames);

	static NodePath animals_placeholder;
protected:
	virtual int stay_quiet();
	int stay_x_frame_stoped;

	float _velocity;
	Activity activity;
};

#endif
