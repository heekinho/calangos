#include "edibleVegetal.h"

#include "modelRepository.h"

NodePath EdibleVegetal::vegetals_food_placeholder = NodePath("Edible Vegetals Placeholder");
map<string, PT(EdibleVegetal)> EdibleVegetal::vegetals;

EdibleVegetal::EdibleVegetal(){}
EdibleVegetal::EdibleVegetal(const string &model) : ObjetoJogo(model){}
EdibleVegetal::EdibleVegetal(NodePath node) : ObjetoJogo(node) {}

EdibleVegetal::EdibleVegetal(PT(ObjetoJogo) base_object) : ObjetoJogo(vegetals_food_placeholder.attach_new_node("EdibleVegetalPlaceholder")) {
	base_object->instance_to(*this);
}

EdibleVegetal::EdibleVegetal(PT(EdibleVegetal) base_vegetal) : ObjetoJogo(vegetals_food_placeholder.attach_new_node("EdibleVegetalPlaceholder")) {
	base_vegetal->instance_to(*this);
	configure_vegetal(base_vegetal);
}

void EdibleVegetal::configure_vegetal(PT(EdibleVegetal) base_vegetal){
	set_valor_nutricional(base_vegetal->get_valor_nutricional());
	set_scale(base_vegetal->get_scale());
	set_offset_z(base_vegetal->get_offset_z());
}

PT(EdibleVegetal) EdibleVegetal::configure_edible_vegetal(const string name, float scale, float offset_z, int nutritional_value, int hidratacao){

	PT(EdibleVegetal) especie = new EdibleVegetal(*ModelRepository::get_instance()->get_model(name));
	especie->set_valor_nutricional(nutritional_value);
	especie->set_valor_hidratacao(hidratacao);
	especie->set_scale(scale);
	especie->set_offset_z(offset_z);
	return especie;
}

void EdibleVegetal::configure_default_edible_vegetal(){
	
	if(vegetals.size() == 0)
	{
		EdibleVegetal::vegetals_food_placeholder = Simdunas::get_window()->get_render().attach_new_node("Edible Vegetals Placeholder");
		
		vegetals["copaifera-flor"] = configure_edible_vegetal("copaifera-flor",0.03,-1.96);
		vegetals["jatropha-flor"] = configure_edible_vegetal("jatropha-flor",0.04,-1.96);
		vegetals["eugenia-flor"] = configure_edible_vegetal("eugenia-flor",0.02,-1.95);
		vegetals["colher-flor"] = configure_edible_vegetal("colher-flor",0.03,-1.94);
		vegetals["colher-fruto"] = configure_edible_vegetal("colher-fruto",0.09,-1.85);
		vegetals["murici-flor"] = configure_edible_vegetal("murici-flor",0.03,-1.94);
		vegetals["murici-fruto"] = configure_edible_vegetal("murici-fruto",0.09,-1.84);
		vegetals["xique_xique-fruto"] = configure_edible_vegetal("xique_xique-fruto",0.08,-1.86);
		
		//nao comestiveis
		//vegetals["quipa-fruto"] = configure_edible_vegetal("quipa-fruto",1,0.1,-1.6);
		//vegetals["eugenia-fruto"] = configure_edible_vegetal("eugenia-fruto",1,0.1,-2);
		//vegetals["mandacaru-fruto"] = configure_edible_vegetal("mandacaru-fruto",1,0.1,-1.0);

	}
}

EdibleVegetal::~EdibleVegetal(){}

PT(EdibleVegetal) EdibleVegetal::get_edible_vegetal(string name, Edible::EdibleType type){
	if(type == Edible::FLOWER)
		name += "-flor";
	else
		name += "-fruto";

	configure_default_edible_vegetal();
	if( vegetals.find(name) != vegetals.end() )
		return new EdibleVegetal( vegetals[name] );
	else
		return NULL;
}
