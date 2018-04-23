#include "groupPrey.h"

GroupPrey::GroupPrey(){

}

GroupPrey::~GroupPrey(){
	group.clear();
}

/*! Verifica se a presa é líder *supremo* do grupo */
bool GroupPrey::is_master_leader(PT(Prey) prey){
	if(group.front() == prey) return true;
	return false;
}

/*! Remove uma presa do grupo */
void GroupPrey::remove_prey(PT(Prey) prey){
	group.remove(prey);
	prey->_group = NULL;
	calc_leaders();
}

/*! Faz o cálculo de liderança. A primeira presa do grupo, é o "master leader",
 * sendo que as presas seguintes tem como líder a presa que está à sua frente
 * no grupo */
void GroupPrey::calc_leaders(){
	PT(Prey) last_leader = NULL;
	for (list<PT(Prey)>::iterator it = group.begin(); it != group.end(); ++it){
		(*it)->set_leader(last_leader);
		last_leader = (*it);
	}
}

/*! Obtém quem é o líder da presa. Se não tem líder ela tem comportamento
 * independente e é considerada como "master leader" */
PT(Prey) GroupPrey::get_leader(PT(Prey) prey){
	PT(Prey) last_leader = NULL;
	for (list<PT(Prey)>::iterator it = group.begin(); it != group.end(); ++it){
		if((*it) == prey) return last_leader;
		last_leader = (*it);
	}
	return NULL;
}
