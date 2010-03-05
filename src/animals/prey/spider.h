#ifndef SPIDER_H
#define SPIDER_H

#include "prey.h"
#include "vegetal.h"


class Spider : public Prey {

public:
	Spider(NodePath node);
	~Spider();

	static NodePath spiders_placeholder;

	static void load_spiders(int qtd);

	virtual void act();
//	virtual void change_sector(PT(Setor) new_sector);

	void set_living_tree(PT(Vegetal) living_tree);
	PT(Vegetal) get_living_tree();

	void surround_tree();
private:
	void init();

	PT(Vegetal) living_tree;
	float radius_thr;
};



#endif

