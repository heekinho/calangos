#include "edibleVegetal.h"

#include "modelRepository.h"
#include "lodNode.h"
#include "simdunas.h"

NodePath EdibleVegetal::vegetals_food_placeholder = NodePath("Edible Vegetals Placeholder");
map<string, PT(EdibleVegetal)> EdibleVegetal::vegetals;

EdibleVegetal::EdibleVegetal(const NodePath &node) : ObjetoJogo(node) {}

EdibleVegetal::EdibleVegetal(PT(EdibleVegetal) base_vegetal)
: ObjetoJogo(NodePath(new LODNode("LOD Placeholder"))){
	/* Adiciona um switch com o vegetal. Só visível de perto */
	base_vegetal->instance_to(*this);
	((LODNode*) node())->add_switch(8, 0);

	/* Coloca no grafo de cena */
	reparent_to(vegetals_food_placeholder);

	/* Realiza configuração do vegetal de acordo com o vegetal base */
	configure_vegetal(base_vegetal);
}

EdibleVegetal::~EdibleVegetal(){

}

/*! Configura o vegetal de acordo com o modelo de vegetal passado */
void EdibleVegetal::configure_vegetal(PT(EdibleVegetal) base_vegetal){
	set_nutritional_value(base_vegetal->get_nutritional_value());
	set_hydration_value(base_vegetal->get_hydration_value());

	set_scale(base_vegetal->get_scale());
	set_offset_z(base_vegetal->get_offset_z());
}

/*! Configura e retorna um EdibleVegetal com as características informadas */
PT(EdibleVegetal) EdibleVegetal::configure_edible_vegetal(const string name, float scale, float offset_z, float nutritional_value, float hidratacao){
	PT(EdibleVegetal) especie = new EdibleVegetal(*ModelRepository::get_instance()->get_model(name));
	especie->set_nutritional_value(nutritional_value);
	especie->set_hydration_value(hidratacao);

//	especie->set_scale(scale);
	especie->set_width(scale*0.75, true);

//	especie->set_offset_z(offset_z);
	return especie;
}

/*! Faz a configuração padrão dos vegetais, para base dos vegetais a serem criados */
void EdibleVegetal::configure_edible_vegetables(){
	if(vegetals.size() == 0){ /* Sério? */
		EdibleVegetal::vegetals_food_placeholder = render.attach_new_node("Edible Vegetals Placeholder");

		float fl_nut = 2, fl_hid = 6.5;
		float fr_nut = 4, fr_hid = 8;
		
		vegetals["copaifera-flor"] = configure_edible_vegetal("copaifera-flor",0.03,-1.96,fl_nut,fl_hid);
		vegetals["jatropha-flor"] = configure_edible_vegetal("jatropha-flor",0.04,-1.96,fl_nut,fl_hid);
		vegetals["eugenia-flor"] = configure_edible_vegetal("eugenia-flor",0.02,-1.95,fl_nut,fl_hid);
		vegetals["colher-flor"] = configure_edible_vegetal("colher-flor",0.03,-1.94,fl_nut,fl_hid);
		vegetals["colher-fruto"] = configure_edible_vegetal("colher-fruto",0.09,-1.85,fr_nut,fr_hid);
		vegetals["murici-flor"] = configure_edible_vegetal("murici-flor",0.03,-1.94,fr_nut,fr_hid);
		vegetals["murici-fruto"] = configure_edible_vegetal("murici-fruto",0.09,-1.84,fr_nut,fr_hid);
		vegetals["xique_xique-fruto"] = configure_edible_vegetal("xique_xique-fruto",0.08,-1.86,fr_nut,fr_hid);

		//nao comestiveis
		//vegetals["quipa-fruto"] = configure_edible_vegetal("quipa-fruto",1,0.1,-1.6);
		//vegetals["eugenia-fruto"] = configure_edible_vegetal("eugenia-fruto",1,0.1,-2);
		//vegetals["mandacaru-fruto"] = configure_edible_vegetal("mandacaru-fruto",1,0.1,-1.0);

		map<string, PT(EdibleVegetal)>::iterator it = vegetals.begin();
		while(it != vegetals.end()){
			(*it).second->flatten_light();
			it++;
		}
	}
}

/*! Retorna um EdibleVegetal configurado, acessível através do nome */
PT(EdibleVegetal) EdibleVegetal::get_edible_vegetal(string name, EdibleT::EdibleType type){
	if(type == EdibleT::FLOWER) name += "-flor";
	else name += "-fruto";

	configure_edible_vegetables();
	if(vegetals.find(name) != vegetals.end()) return new EdibleVegetal(vegetals[name]);
	else return NULL;
}
