#ifndef LIZARD_H
#define LIZARD_H

#include "animal.h"
#include "vegetal.h"
#include "predator.h"


namespace LizardEspecie {
	enum lizardEpecie {tropidurus , eurolophosaurus, cnemidophorus};
}

namespace LizardGender {
	enum lizardGender {female, male, young};
}

class Lizard : public Animal{
public:
	Lizard(NodePath node);

	~Lizard();

	virtual void act();
//	virtual void new_act();

	static void check_temp(const Event *theEvent, void *data);

	void init();
        void isMale();
        void isFemale();

	static void load_lizards();
	virtual void change_sector(PT(Setor) new_sector);

	LizardGender::lizardGender get_gender(){ return gender; };
	void set_gender(LizardGender::lizardGender gender){ this->gender = gender; };

	float get_tamanho_base();
	float get_tamanho_real();

	void set_tamanho_base(float novo_tamanho_base);//(float tamanho){ this->tamanho = tamanho; };
	void set_tamanho_real(float novo_tamanho_real);

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

	LizardGender::lizardGender gender;
	float tamanho_real;
	float tamanho_base;
	float energia;
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


};

#endif

