#ifndef FEMALELIZARD_H
#define FEMALELIZARD_H

#include "lizard.h"

class FemaleLizard : public Lizard {
public:
	FemaleLizard(NodePath node);
	virtual ~FemaleLizard();

	void init();
	virtual void act();

	static void reproduzir(const Event *theEvent, void *data);
	static void back_to_reprodutive(const Event *theEvent, void *data);
	static void stop_flee(const Event *theEvent, void *data);
	bool reproduziu;
private:
    NodePath female_symbol;

    bool away_from_player;
};

#endif
