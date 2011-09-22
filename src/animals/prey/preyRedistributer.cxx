/*
 * preyRedistributer.cxx
 *
 * Created on: 30/12/2010
 * Author: heekinho
 */

#include "preyRedistributer.h"
#include "prey.h"

#include "groupPrey.h"

const float PreyRedistributer::dist_min = 5.0;
const float PreyRedistributer::dist_mid = 6.0;
const float PreyRedistributer::dist_max = 10.0;

/*! Cria e inicialiaza o método de redistribuição de presas */
PreyRedistributer::PreyRedistributer(list<PT(Prey)> preys){
	this->_preys = preys;
	event_handler->add_hook(PlayerControl::EV_player_move, update_redistribution, this);
	update_redistribution();
}

/*! Destrutor do sistema de redistribuição */
PreyRedistributer::~PreyRedistributer(){
	_preys.clear();
}

/*! Metódo chamada via eventos para atualizar distribuição */
void PreyRedistributer::update_redistribution(){
	list<PT(Prey)>::iterator prey = _preys.begin();
	while(prey != _preys.end()){
		if((*prey)->get_distance_squared(*player) > dist_max*dist_max) realoc_prey(*prey, player->get_pos());
		prey++;
	}
}

/*! Redistribui uma presa */
void PreyRedistributer::realoc_prey(PT(Prey) prey, LPoint3f ref){
	/* Redistribui somente as presas soltas e líderes de grupo.
	 * Presas soltas são consideradas master leaders mas por segurança o _group é checado */
	if(!prey->_group || prey->is_master_leader()){
		LPoint2f new_pos = generate_distribution_point();
		prey->set_pos(ref.get_x()+new_pos.get_x(), ref.get_y()+new_pos.get_y(), 0);
		prey->was_redistributed();
	}

	/* Redistribuindo o grupo de presa */
	if(prey->_group && prey->is_master_leader()){
		PT(Prey) last_leader = prey;
		prey->set_h(rand()%360);
		LVecBase3f orientation = NodePath().get_relative_vector(*prey, LVector3f(0, 1, 0));
		for (list<PT(Prey)>::iterator it = prey->_group->get_array()->begin(); it != prey->_group->get_array()->end(); ++it){
			/* TODO: Colocar deslocamento baseado no tamanho real da presa */
			(*it)->set_pos(last_leader->get_pos() + orientation * 0.1);
			(*it)->look_at(*last_leader);
			last_leader = *it;
		}
	}
}

/*! Gera um ponto de acordo com os paramêtros da distribuição */
LPoint2f PreyRedistributer::generate_distribution_point(){
	float x, y;

	/* Divisão em quadrantes para evitar colocar presa perto do player */
	/* Poderia ser feita de maneira circular */
	if(rand()%2 == 1){
		x = (rand()%2?1:-1) * random(dist_min, dist_mid);
		y = random(-1.0*dist_mid, dist_mid);
	} else {
		x = random(-1.0*dist_mid, dist_mid);
		y = (rand()%2?1:-1) * random(dist_min, dist_mid);
	}

	return LPoint2f(x, y);
}

/*! Função auxiliar */
float PreyRedistributer::random(float lower, float higher){
	return lower + (higher-lower)*(float(rand())/RAND_MAX);
}
