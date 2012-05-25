/*
 * lizardBase.cxx
 * Created on: 25/05/2012
 * Author: heekinho
 */

#include "lizardBase.h"

LizardBase::LizardBase(LizardSpecies species, LizardGender gender){
	_species = species;
	_gender = gender;
	// TODO Auto-generated constructor stub

}

LizardBase::~LizardBase() {
	// TODO Auto-generated destructor stub
}


LizardBase::LizardSpecies LizardBase::get_species() const {
	return _species;
}

void LizardBase::set_species(LizardBase::LizardSpecies especies){
	_species = especies;
}

LizardBase::LizardGender LizardBase::get_gender() const {
	return _gender;
}

void LizardBase::set_gender(LizardBase::LizardGender gender){
	_gender = gender;
}

bool LizardBase::is_young() const {
	return (_gender == LizardBase::LG_young);
}

bool LizardBase::is_male() const {
	return (_gender == LizardBase::LG_male);
}

bool LizardBase::is_female() const {
	return (_gender == LizardBase::LG_female);
}

string LizardBase::get_species_name() const {
	return LizardBase::get_species_name(_species);
}

string LizardBase::get_gender_name() const {
	return LizardBase::get_gender_name(_gender);
}


string LizardBase::get_species_name(LizardBase::LizardSpecies specie){
	switch(specie){
		case(LizardBase::LS_tropidurus): return "tropidurus";
		case(LizardBase::LS_eurolophosaurus): return "eurolophosaurus";
		case(LizardBase::LS_cnemidophorus): return "cnemidophorus";
		case(LizardBase::LS_custom): return "custom";
		default: return "invalid";
	}
}

string LizardBase::get_gender_name(LizardBase::LizardGender gender){
	switch(gender){
		case(LizardBase::LG_young): return "young";
		case(LizardBase::LG_male): return "male";
		case(LizardBase::LG_female): return "female";
		default: return "invalid";
	}
}
