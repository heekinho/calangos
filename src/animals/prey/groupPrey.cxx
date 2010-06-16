#include "groupPrey.h"

GroupPrey::GroupPrey(){}

bool GroupPrey::is_master_leader(PT(Prey) prey){
	if(group.front() == prey) return true;
	return false;
}

void GroupPrey::remove_prey(PT(Prey) prey){
	for (list<PT(Prey)>::iterator it = group.begin(); it != group.end(); ++it){
		if((*it) == prey) {
			group.erase(it);
			break;
		}
	}
	calc_leaders();
}

void GroupPrey::calc_leaders(){
	PT(Prey) last_leader = NULL;
	for (list<PT(Prey)>::iterator it = group.begin(); it != group.end(); ++it){
		(*it)->set_leader(last_leader);
		last_leader = (*it);
	}
}


PT(Prey) GroupPrey::get_leader(PT(Prey) prey){
	PT(Prey) last_leader = NULL;
	for (list<PT(Prey)>::iterator it = group.begin(); it != group.end(); ++it){
		if((*it) == prey) return last_leader;
		last_leader = (*it);
	}
}
