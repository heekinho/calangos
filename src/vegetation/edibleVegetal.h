#ifndef FOOD_VEGETAL_H
#define FOOD_VEGETAL_H

#include "objetoJogo.h"
#include "string.h"

namespace Edible {
	enum EdibleType {
		FLOWER,
		FRUIT
	};
}

class EdibleVegetal : public ObjetoJogo {
public:
	~EdibleVegetal();

	float get_nutritional_value();
	void set_nutritional_value(float value);
	
	static PT(EdibleVegetal) get_edible_vegetal(string name, Edible::EdibleType type);

	void configure_vegetal(PT(EdibleVegetal) base_vegetal);
	static PT(EdibleVegetal) configure_edible_vegetal(const string name, float scale = 1.0, float offset_z = 0.0, float nutritional_value = 2, float hidratacao = 3);
	static void configure_default_edible_vegetal();

	static NodePath vegetals_food_placeholder;
	
private:
	EdibleVegetal();
	EdibleVegetal(const string &model);
	EdibleVegetal(NodePath node);
	EdibleVegetal(PT(ObjetoJogo) vegetal);
	EdibleVegetal(PT(EdibleVegetal) vegetal);

	static map<string, PT(EdibleVegetal)> vegetals;

	//ver depois como funciona valor nutricional
	//float nutritional_value;
	
};

#endif
