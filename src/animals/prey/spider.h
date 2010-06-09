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
private:
	void init();
};



#endif

