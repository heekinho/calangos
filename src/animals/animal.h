#ifndef ANIMAL_H
#define ANIMAL_H

#include "animatedObjetoJogo.h"

class Animal : public AnimatedObjetoJogo {
public:
	Animal(NodePath node);
	~Animal();

	static NodePath animals_placeholder;

	static void load_animals();

	static void unload_animals();

	static void start_acting(const Event*, void *data);
	static void act(const Event*, void *data);
	virtual void act();
	static void stop_acting(const Event*, void *data);
	void set_acting(bool acting);
	bool is_acting();

	//virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector);
	static void redistribute_animals();
	static void migrate_animals(vector<PT(ObjetoJogo)>* vect, PT(Setor) sector_from, vector<PT(Setor)> *sectors_to);
	static void migrate_animal(PT(ObjetoJogo) theanimal, PT(Setor) to);

	void set_setor(PT(Setor) setor);


	/* Caracteristicas NPC */
	int level;				// Criar enum para ele. 5 níveis, segundo documento
	int health;// = 2;		// Quando filhote 2, aumenta em 1 para cada nível de tamanho.

	int bite_damage;// = 3; // Quando filhote 3, aumenta em 1 a cada nível de tamanho
	double bite_prob;// = 0.4;
	//private void calc_bite_thr();

	/* Ações NPC */
	void reproduce();
	void bite();			// Ação de morder
	void eat();				// Ação de comer (verificar necessidade)

	/* Ações relacionadas ao movimento */
	virtual float get_velocity() { return velocity; };
	virtual void set_velocity(float velocity) { this->velocity = velocity; };

	void wander();
	void walk();			// Anda com velocidade normal de locomoção.
	void run();				// Corre (velocidade é aumentada)
	void walk_sneakily();	// Reduz dois terços a velocidade normal de locomoção.
	void get_away();		// Quando o player tem sucesso em uma intimidação.


	virtual void pause_animation(){};
	virtual void continue_animation(){};
protected:
	virtual int stay_quiet();
	bool acting;

	float velocity;

	int stay_x_frame_stoped;
};

#endif
