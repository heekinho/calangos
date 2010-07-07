#ifndef VEGETAL_H
#define VEGETAL_H

#include "objetoJogo.h"
#include "edibleVegetal.h"

namespace Season {
	enum SeasonType {
		DRY,
		RAINY
	};
}

namespace Area {
	enum AreaType { 
		LOW, 
		MID, 
		HIGH 
	};
}


class Vegetal : public ObjetoJogo {
public:
	~Vegetal();

	static NodePath vegetals_placeholder;

	static void configure_show_hide_event();

	static Season::SeasonType get_season();
	static void change_season(Season::SeasonType season = Season::DRY);

	//muda densidade em world.cxx
	static void load_vegetals(int density = 100);
	static void unload_vegetals();
	static void load_default_model_and_data();

	void configure_vegetal(PT(Vegetal) base_vegetal);
	void configure_position( PT(Vegetal) base_vegetal);	

	static void add_vegetal_model(const string &name,
	            float radius = 1.0, float scale = 1.0, float offset_z  = 0.0);
	static void add_vegetal_model(const string &map_name, const string &reposit_name, const string &veg_name,
	            Area::AreaType area, float radius = 1.0, float scale = 1.0, float offset_z  = 0.0);

	float get_radius();
	void set_radius(float radius);

	Area::AreaType get_area();
	void set_area(Area::AreaType area);
	
	void set_vegetal_name(string name);
	string get_vegetal_name();
	
	void set_vegetal_season(Season::SeasonType type);
	Season::SeasonType get_vegetal_season();

	static void configure_edible_vegetal_fruit(string model_name, int percent_dry, int quant_dry, int percent_rainy, int quant_rainy );
	static void configure_edible_vegetal_flower(string model_name, int percent_dry, int quant_dry, int percent_rainy, int quant_rainy );

	//TODO: mudar logica para edibleVegetal
	void load_edible_vegetal_model(string name, int quant_flower = 0, int quant_fruit = 0);
	void load_edible_vegetals(string veg_name, Season::SeasonType type);

	void add_edible_vegetal(PT(EdibleVegetal) vegetal);
	void remove_edible_vegetal(PT(EdibleVegetal) vegetal);

	void show_edible_vegetals();
	void hide_edible_vegetals();

	static void add_data(const string &map_name, int value);

	static const int MAX_CENTER_GEN_ERROR = 1000;
	static const int LOW_TERRAIN_DIVISION = 3;
	static const int HIGH_TERRAIN_DIVISION = 8;
	
	static const int VEGETAL_PERCENT_LOW_AREA = 70;
	static const int VEGETAL_PERCENT_MID_AREA = 50;
	static const int VEGETAL_PERCENT_HIGH_AREA = 30;

	static void update_show_hide();
private:
	Vegetal();
	Vegetal(const string &model);
	Vegetal(NodePath node);
	Vegetal(PT(ObjetoJogo) vegetal);
	Vegetal(PT(Vegetal) vegetal);

	float radius;
	Area::AreaType area;
	string vegetal_name;
	Season::SeasonType season_type;

	static Season::SeasonType current_season;
	

	static vector<string> vegetals_name;
	static map<string,PT(Vegetal)> models;
	static map<string,int> datas;
	static map<Season::SeasonType,string> seasons;
	
	static void configure_change_season_event();
	static void hook_change_season(const Event* evt, void *data);

	//vector<PT(EdibleVegetal)> edibleVegetals;
	

	static void hook_show(const Event* evt, void *data);
	static void hook_hide(const Event* evt, void *data);

	//Distribuicao Vegetal
	static LPoint2d point_max;
	static vector<LVecBase3f> generate_elements_buffer;
	static int tree_distance, center_distance;
	static int tree_points, center_points;
	static int center_edge;
	//static int shadow_radius;

	static vector<PT(Vegetal)> low_area;
	
	static void build_forest();

	static Area::AreaType randomize_area(Area::AreaType area);
	static PT(Vegetal) get_random_vegetal(Area::AreaType area);
	static string get_name_area(Area::AreaType area);
	static int get_random_vegetal_index_by_density( vector<PT(Vegetal)> *vegetals, Area::AreaType area);
	static bool is_vegetal_group(PT(Vegetal) vegetal);

	static vector<LVecBase3f> generate_elements(LPoint2d start, LPoint2d end, int qtd, float distance, float model_radius = 0);
	static bool verify_distance(vector<LVecBase3f>* points, LVecBase3f point, float distance);

};
#endif
