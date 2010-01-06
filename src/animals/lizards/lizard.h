#ifndef LIZARD_H
#define LIZARD_H

#include "animal.h"

namespace LizardEspecie {
	enum lizardEpecie {tropidurus , eurolophosaurus, cnemidophorus};
}

namespace LizardGender {
	enum lizardGender {female, male, young};
}

class Lizard : public Animal{
public:
	Lizard(NodePath node);
	Lizard(const string &model);

	~Lizard();

	void init();
        void isMale();
        void isFemale();

	static void load_lizards();
	virtual void change_sector(PT(Setor) new_sector);
	virtual void act();

	LizardGender::lizardGender get_gender(){ return gender; };
	void set_gender(LizardGender::lizardGender gender){ this->gender = gender; };

	float get_tamanho(){ return tamanho; };
	void set_tamanho(float tamanho){ this->tamanho = tamanho; };

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
	virtual void flee(){};
	virtual void chase(){};

protected:
	/* Mapeia as ações */
	map<string, bool> actions;

	LizardGender::lizardGender gender;
	float tamanho;
	float energia;
};

#endif

