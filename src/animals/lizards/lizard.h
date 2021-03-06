#ifndef LIZARD_H
#define LIZARD_H

#include "animal.h"
#include "vegetal.h"
#include "predator.h"
#include "lizardBase.h"

class Lizard : public Animal, public LizardBase {
public:
	Lizard(NodePath node);

	virtual ~Lizard();

	virtual void act();
//	virtual void new_act();

	static void check_temp(const Event *theEvent, void *data);

	void init();

	static void load_lizards();
	virtual void change_sector(PT(Setor) new_sector);


	virtual float get_relative_size();
	float get_tamanho_real();

	virtual void set_relative_size(float novo_tamanho_base);//(float tamanho){ this->tamanho = tamanho; };
	virtual void set_tamanho_real(float novo_tamanho_real);

	float get_energia(){ return energia; };
	void set_energia(float energia){ this->energia = energia; };

	virtual int is_inverted(){ return -1; };

	void clear_actions();
	void set_action(string action, bool turn_off_others = false);
	bool is_action_active(string action){ return actions[action]; }
	bool has_other_anim_active(string action);

	bool has_other_action_active(string action);
	void config_anims_to_action();
	void play_action_anims(bool loop = false);

	/* Ações dos NPCs */
	virtual void fight(){};
	virtual void bob(){};
	virtual void wander(){};
	virtual void bite(){};
	virtual void flee();
	virtual void flee(const NodePath &other);
	virtual void chase(){};

	bool hide_from_predator();
	PT(Vegetal) get_arvore_da_sombra();


	//virtual void move(float velocity);

	virtual void continue_animation();
	virtual void pause_animation();

	void set_predator(PT(Predator) other);
	PT(Predator) get_predator();

protected:
	/* Mapeia as ações */
	map<string, bool> actions;

//	LizardGender::lizardGender gender;
	float tamanho_real;
	float tamanho_base;
	float energia;
	float age;
	float scale_temp;
	float scale;

	PT(Predator) predator;
private:
	bool ficar_na_sombra;
	int tempo_no_sol_thr;
	int tempo_na_sombra_thr;
	int tempo_no_sol;
	int tempo_na_sombra;

	PT(Vegetal) arvore_da_sombra;

	float calculate_inicial_size();
};

#endif

