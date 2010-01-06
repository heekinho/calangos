#ifndef REDLEGGED_H
#define REDLEGGED_H

#include "predator.h"

class RedLegged : public Predator {
public:
	RedLegged(PT(AnimatedObjetoJogo) base_object);
	~RedLegged();

	static NodePath redleggeds_placeholder;

	static void load_redleggeds(int qtd);

	virtual void act();
private:
	void init();
};


#endif
