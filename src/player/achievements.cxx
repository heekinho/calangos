/*
 * achievements.cxx
 *
 *  Created on: Jan 2, 2012
 *      Author: jonatas
 */

#include "achievements.h"

Achievements::Achievements() {
	count_bites = 0;
	lvl_senhor_mordida = 0;
}

Achievements::~Achievements() {}

void Achievements::inc_bites() {
	count_bites++;
	if (lvl_senhor_mordida == 0 && count_bites == 10) {
		clear_bites();
		lvl_senhor_mordida++;
	}
	else if (lvl_senhor_mordida == 1 && count_bites == 25) {
		clear_bites();
		lvl_senhor_mordida++;
	}
	else if (count_bites == 50) {
		clear_bites();
		lvl_senhor_mordida++;
	}
	cout<<"incrementando o contador de mordidas"<<endl;
}

void Achievements::clear_bites() {
	count_bites = 0;
	cout<<"zerando o contador de mordidas"<<endl;
}

int Achievements::get_count_bites() {
	return count_bites;
}

int Achievements::get_lvl_senhor_mordida() {
	return lvl_senhor_mordida;
}
