/*
 * achievements.h
 *
 *  Created on: Jan 2, 2012
 *      Author: jonatas
 */

#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include "pandaFramework.h"

class Achievements : public ReferenceCount {
public:
	Achievements();
	virtual ~Achievements();

	void inc_bites();
	void clear_bites();
	int get_count_bites();
	int get_lvl_senhor_mordida();

private:
	int count_bites;
	int lvl_senhor_mordida;
};

#endif /* ACHIEVEMENTS_H */
