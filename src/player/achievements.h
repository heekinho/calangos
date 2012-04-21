/*
 * achievements.h
 *
 *  Created on: Jan 2, 2012
 *      Author: jonatas
 */

#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include "pandaFramework.h"
#include "edible.h"

class Achievements : public ReferenceCount {
public:
	Achievements();
	virtual ~Achievements();

	void inc_bites();
	void clear_bites();
	int get_count_bites();
	int get_lvl_senhor_mordida();
	int get_lvl_bom_de_boca();
	int get_count_species();
	void inc_meses_sobrevivente();
	int get_count_sobrevivente();
	int get_lvl_sobrevivente();
	void inc_reprodutor();
	int get_count_reprodutor();
	int get_lvl_reprodutor();
	void check_edible_specie(Edible::Specie);

private:
	int count_bites;
	int lvl_senhor_mordida;
	vector<Edible::Specie> eaten_species;
	int lvl_bom_de_boca;
	int count_species;
	int lvl_sobrevivente;
	int count_sobrevivente;
	int lvl_reprodutor;
	int count_reprodutor;
};

#endif /* ACHIEVEMENTS_H */
