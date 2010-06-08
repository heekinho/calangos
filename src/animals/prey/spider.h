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


	virtual void change_sector(PT(Setor) new_sector);

	virtual void act();
	void set_random_living_tree();
private:
	void init();
};



#endif

