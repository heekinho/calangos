#ifndef EDIBLE_H
#define EDIBLE_H

#include "pandaFramework.h"

class Edible {

public:
	enum Specie {
		// presas
		aranha,
		besouro,
		cupim,
		formiga,
		grilo,
		larva,

		// vegetais
		copaifera_flor,
		jatropha_flor,
		eugenia_flor,
		colher_flor,
		colher_fruto,
		murici_flor,
		murici_fruto,
		xique_xique_fruto
	};

	INLINE Edible();
	INLINE Edible(float nutritional, float hydration);

	INLINE Edible::Specie get_specie_value();
	INLINE void set_specie_value(Edible::Specie specie);

	INLINE float get_nutritional_value() const;
	INLINE void set_nutritional_value(float nutritional);

	INLINE float get_hydration_value() const;
	INLINE void set_hydration_value(float hydration);

private:
	Specie _specie;
	float _nutritional;
	float _hydration;
};

#include "edible.I"

#endif
