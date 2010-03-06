#ifndef REDLEGGED_H
#define REDLEGGED_H

#include "predator.h"

class RedLegged : public Predator {
public:
	RedLegged(NodePath node);
	~RedLegged();

	static NodePath redleggeds_placeholder;

	static void load_redleggeds(int qtd);

	virtual void act();
	virtual int is_inverted(){ return -1; };
private:
	void init();
};


#endif
