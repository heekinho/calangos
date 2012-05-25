/*
 * lizardBase.h
 * Created on: 25/05/2012
 * Author: heekinho
 */

#ifndef LIZARDBASE_H
#define LIZARDBASE_H

#include <iostream>
using namespace std;

class LizardBase {
public:
	enum LizardSpecies {
		LS_custom,
		LS_tropidurus,
		LS_eurolophosaurus,
		LS_cnemidophorus
	};

	enum LizardGender {
		LG_female,
		LG_male,
		LG_young
	};

	LizardBase(LizardSpecies species = LS_eurolophosaurus, LizardGender gender = LG_young);
	virtual ~LizardBase();

	LizardBase::LizardSpecies get_species() const;
	void set_species(LizardBase::LizardSpecies especies);

	LizardBase::LizardGender get_gender() const;
	void set_gender(LizardBase::LizardGender gender);

	string get_species_name() const;
	string get_gender_name() const;

	static string get_species_name(LizardBase::LizardSpecies specie);
	static string get_gender_name(LizardBase::LizardGender gender);

	bool is_young() const;
	bool is_male() const;
	bool is_female() const;

private:
	LizardBase::LizardSpecies _species;
	LizardBase::LizardGender _gender;

};

#endif /* LIZARDBASE_H */
