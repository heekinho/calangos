#ifndef GROUPPREY_H

#define GROUPPREY_H



#include "prey.h"



class Prey;



class GroupPrey : public ReferenceCount {

public:

	GroupPrey();

	virtual ~GroupPrey();



	bool is_master_leader(PT(Prey) prey);

	void calc_leaders();



	list<PT(Prey)>* get_array(){ return &group; }

	void set_array(list<PT(Prey)>* new_group){ this->group = *new_group; };



	PT(Prey) get_leader(PT(Prey) prey);

	PT(Prey) get_master_leader();



	void remove_prey(PT(Prey) prey);

	void add_prey(PT(Prey) prey){ group.push_back(prey); };

private:

	list<PT(Prey)> group;



};



#endif

