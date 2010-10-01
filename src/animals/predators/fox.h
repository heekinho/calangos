#ifndef FOX_H
#define FOX_H

#include "predator.h"

class Fox : public Predator {
public:
	Fox(NodePath node);

	static void load_foxes(int qtd);
};

#endif
