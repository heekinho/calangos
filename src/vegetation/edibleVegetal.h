#ifndef FOOD_VEGETAL_H
#define FOOD_VEGETAL_H

#include "objetoJogo.h"
#include "string.h"
#include "edible.h"

namespace EdibleT {
	enum EdibleType {
		FLOWER,
		FRUIT
	};
}

class EdibleVegetal : public ObjetoJogo, public Edible {
public:
	virtual ~EdibleVegetal();
	
	static PT(EdibleVegetal) get_edible_vegetal(string name, EdibleT::EdibleType type);

	void configure_vegetal(PT(EdibleVegetal) base_vegetal);
	static PT(EdibleVegetal) configure_edible_vegetal(const string name, float scale = 1.0, float offset_z = 0.0, float nutritional_value = 2, float hidratacao = 3);
	static void configure_edible_vegetables();

	static NodePath vegetals_food_placeholder;
	
private:
	EdibleVegetal(const NodePath &node);
	EdibleVegetal(PT(EdibleVegetal) vegetal);

	static map<string, PT(EdibleVegetal)> vegetals;
};

#endif
