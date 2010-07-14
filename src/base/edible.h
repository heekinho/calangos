#ifndef EDIBLE_H
#define EDIBLE_H

#include "pandaFramework.h"

class Edible {
public:
	INLINE Edible();
	INLINE Edible(float nutritional, float hydration);

	INLINE float get_nutritional_value() const;
	INLINE void set_nutritional_value(float nutritional);

	INLINE float get_hydration_value() const;
	INLINE void set_hydration_value(float hydration);
private:
	float _nutritional;
	float _hydration;
};

#include "edible.I"

#endif
