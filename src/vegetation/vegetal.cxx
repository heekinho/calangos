#include "vegetal.h"

#include "setor.h"
#include "modelRepository.h"
//#include "forest.h"
#include "terrain.h"
#include "simdunas.h"
#include "nodePath.h"
#include "collision.h"
#include "edibleVegetal.h"

map<string,PT(Vegetal)> Vegetal::models;
map<string,int> Vegetal::datas;
map<Season::SeasonType,string> Vegetal::seasons;
vector<LVecBase3f> Vegetal::generate_elements_buffer;

LPoint2d  Vegetal::point_max = LPoint2d();
int Vegetal::tree_distance = 0;
int Vegetal::center_distance = 0;
int Vegetal::tree_points = 0;
int Vegetal::center_points = 0;
int Vegetal::center_edge = 0;

vector<string> Vegetal::vegetals_name;

vector<PT(Vegetal)> Vegetal::low_area;


Season::SeasonType Vegetal::current_season = Season::DRY;

NodePath Vegetal::vegetals_placeholder = NodePath("Vegetals Placeholder");
NodePath Vegetal::visible_vegetals_placeholder = NodePath("Vegetals Placeholder");

Vegetal::Vegetal(){}
Vegetal::Vegetal(const string &model) : ObjetoJogo(model){}
Vegetal::Vegetal(NodePath node) : ObjetoJogo(node) {

}

Vegetal::Vegetal(PT(ObjetoJogo) base_object) : ObjetoJogo(vegetals_placeholder.attach_new_node("VegetalPlaceholder")){
	base_object->instance_to(*this);
}

Vegetal::Vegetal(PT(Vegetal) base_vegetal) : ObjetoJogo(vegetals_placeholder.attach_new_node("VegetalPlaceholder")){
	base_vegetal->instance_to(*this);
	configure_vegetal(base_vegetal);
}

Vegetal::~Vegetal(){
}

/*! Configura um vegetal a partir de informações de um vegetal base */
void Vegetal::configure_vegetal(PT(Vegetal) base_vegetal){
	set_area(base_vegetal->get_area());
	set_radius(base_vegetal->get_radius());
	set_scale(base_vegetal->get_scale());
	set_offset_z(base_vegetal->get_offset_z());
	set_h(base_vegetal->get_h());
	set_vegetal_name(base_vegetal->get_vegetal_name());
	set_vegetal_season(base_vegetal->get_vegetal_season());

//	hide();
}

/*! Configura posição um vegetal a partir da posição de um vegetal base */
void Vegetal::configure_position(PT(Vegetal) base_vegetal){
	set_x(base_vegetal->get_x());
	set_y(base_vegetal->get_y());
	set_z(base_vegetal->get_z());
}

/*! Dados default dos vegetais*/
void Vegetal::load_default_model_and_data()
{
	seasons[Season::DRY] = string("-seco");
	seasons[Season::RAINY] = string("-chuvoso");

	//configura vegetais
        //(String, radius, scale, offset_z, multiplicador, x,y, z)
	add_vegetal_model("mimosa", 1.5, 0.2);//ok
	add_vegetal_model("quipa", 1, 0.09,0, 45); //ok
        add_vegetal_model("eugenia", 5, 0.20, -0.15, 4);//ok
	add_vegetal_model("mandacaru", 5, 0.22,-0.2, 3); // OK
	add_vegetal_model("colher", 5, 0.20,-0.2, 2);//ok
	add_vegetal_model("bromelia", 2, 0.20, -0.1, 4); //ok
	add_vegetal_model("xique_xique", 3, 0.2, -0.20, 4, -10,-15); // ok
	add_vegetal_model("murici", 2, 0.15, -0.15, 4);//ok
	add_vegetal_model("simaba", 4, 0.20, -0.15, 5,0 ,-6);//ok
	add_vegetal_model("bocoa", 4, 0.20,-0.2, 10, 0, 8);//ok
	add_vegetal_model("chamaecrista", 4, 0.20, -0.15, 3, 0, 0, 10);//ok
	add_vegetal_model("copaifera", 6, 0.20,-0.2, 4);//ok
	add_vegetal_model("croton", 4, 0.20,-0.2, 8, 0, 11);//bom
	add_vegetal_model("harpochilus", 3, 0.20, -0.2, 5, 5);//ok
	add_vegetal_model("jatropha", 6, 0.20, -0.25, 4, 0, -9);//ok

	//mudança de estação

	add_data("mimosa-seco",50);
	add_data("mimosa-chuvoso",50);

	add_data("copaifera-seco",90);
	add_data("copaifera-chuvoso",90);

	add_data("eugenia-seco",70);
	add_data("eugenia-chuvoso",40);

	add_data("simaba-seco",80);
	add_data("simaba-chuvoso",50);

	add_data("colher-seco",90);
	add_data("colher-chuvoso",50);

	add_data("bromelia-seco",70);
	add_data("bromelia-chuvoso",70);

	add_data("murici-seco",90);
	add_data("murici-chuvoso",90);

	//nao modificados ainda
	add_data("xique_xique-seco",50);
	add_data("xique_xique-chuvoso",50);

	add_data("mandacaru-seco",100);
	add_data("mandacaru-chuvoso",100);

	add_data("quipa-chuvoso",50);
	add_data("quipa-seco",50);

	add_data("bocoa-seco",50);
	add_data("bocoa-chuvoso",50);

	add_data("chamaecrista-seco",50);
	add_data("chamaecrista-chuvoso",50);

	add_data("croton-seco",50);
	add_data("croton-chuvoso",50);

	add_data("harpochilus-seco",50);
	add_data("harpochilus-chuvoso",50);

	add_data("jatropha-seco",50);//50
	add_data("jatropha-chuvoso",50);//50


	//densidades
	add_data("mimosa-low-density",20);
	add_data("quipa-low-density",119);
	add_data("eugenia-low-density",113);
	add_data("mandacaru-low-density",3);
	add_data("colher-low-density",23);
	add_data("bromelia-low-density",200);
	add_data("xique_xique-low-density",1);
	add_data("murici-low-density",13);
	add_data("simaba-low-density",8);
	add_data("copaifera-low-density",36);
	add_data("croton-low-density",27);
	add_data("harpochilus-low-density",50);
	add_data("jatropha-low-density",50);
	add_data("bocoa-low-density",50);
	add_data("chamaecrista-low-density",50);

	add_data("mimosa-mid-density",10);
	add_data("quipa-mid-density",34);
	add_data("eugenia-mid-density",65);//85
	add_data("mandacaru-mid-density",5);
	add_data("colher-mid-density",30);
	add_data("bromelia-mid-density",50);//60
	add_data("xique_xique-mid-density",1);
	add_data("murici-mid-density",17);
	add_data("simaba-mid-density",16);
	add_data("copaifera-mid-density",49);
	add_data("croton-mid-density",27);
	add_data("harpochilus-mid-density",50);
	add_data("jatropha-mid-density",50);
	add_data("bocoa-mid-density",50);
	add_data("chamaecrista-mid-density",50);

	add_data("mimosa-high-density",50);//70
	add_data("quipa-high-density",17);
	add_data("eugenia-high-density",65);//85
	add_data("mandacaru-high-density",3);
	add_data("colher-high-density",23);
	add_data("bromelia-high-density",0);
	add_data("xique_xique-high-density",1);
	add_data("murici-high-density",13);
	add_data("simaba-high-density",46);//56
	add_data("copaifera-high-density",36);
	add_data("croton-high-density",13);
	add_data("harpochilus-high-density",50);
	add_data("jatropha-high-density",50);//50
	add_data("bocoa-high-density",50);
	add_data("chamaecrista-high-density",50);

	//configuração de raio da sombra
	add_data("mimosa-shadow-radius",1);
	add_data("quipa-shadow-radius",1);
	add_data("eugenia-shadow-radius",6);
	add_data("mandacaru-shadow-radius",0);
	add_data("colher-shadow-radius",3);
	add_data("bromelia-shadow-radius",0);
	add_data("xique_xique-shadow-radius",1);
	add_data("murici-shadow-radius",0);
	add_data("simaba-shadow-radius",7);
	add_data("bocoa-shadow-radius",4);
	add_data("copaifera-shadow-radius",6);
	add_data("croton-shadow-radius",4);
	add_data("jatropha-shadow-radius",2);
	add_data("chamaecrista-shadow-radius",0);
	add_data("harpochilus-shadow-radius",0);


	//configuração de frutos e flores por estação
	//bocoa chamaecrista copaifera croton harpochilus jatropha
	configure_edible_vegetal_fruit("mimosa",0,0,0,0);
	configure_edible_vegetal_fruit("quipa",1,1,1,1);
	configure_edible_vegetal_fruit("eugenia",12,1,35,10);
	configure_edible_vegetal_fruit("mandacaru",0,0,0,0);
	configure_edible_vegetal_fruit("colher",50,7,10,1);
	configure_edible_vegetal_fruit("bromelia",0,0,0,0);
	configure_edible_vegetal_fruit("xique_xique",1,1,1,1);
	configure_edible_vegetal_fruit("murici",12,1,40,10);
	configure_edible_vegetal_fruit("bocoa",5,3,5,3);
	configure_edible_vegetal_fruit("chamaecrista",5,3,5,3);
	configure_edible_vegetal_fruit("copaifera",10,7,12,7);
	configure_edible_vegetal_fruit("croton",5,3,5,3);
	configure_edible_vegetal_fruit("harpochilus",5,3,5,3);
	configure_edible_vegetal_fruit("jatropha",5,3,5,3);

	configure_edible_vegetal_flower("mimosa",0,0,0,0);
	configure_edible_vegetal_flower("quipa",1,1,5,1);
	configure_edible_vegetal_flower("eugenia",4,1,8,10);
	configure_edible_vegetal_flower("mandacaru",0,0,0,0);
	configure_edible_vegetal_flower("colher",1,2,30,7);
	configure_edible_vegetal_flower("bromelia",0,0,0,0);
	configure_edible_vegetal_flower("xique_xique",1,1,1,1);
	configure_edible_vegetal_flower("murici",1,1,35,10);
	configure_edible_vegetal_flower("simaba",1,3,30,3);
	configure_edible_vegetal_flower("bocoa",5,3,5,3);
	configure_edible_vegetal_flower("chamaecrista",5,3,5,3);
	configure_edible_vegetal_flower("copaifera",1,7,30,7);
	configure_edible_vegetal_flower("croton",5,3,5,3);
	configure_edible_vegetal_flower("harpochilus",5,3,5,3);
	configure_edible_vegetal_flower("jatropha",5,3,5,3);

}

/*!configura quantidade de árvores com frutos e quantidade de frutos por estação*/
void Vegetal::configure_edible_vegetal_fruit(string model_name, int percent_dry, int quant_dry, int percent_rainy, int quant_rainy )
{
	add_data(model_name+"-seco-fruto-percent", percent_dry);
	add_data(model_name+"-chuvoso-fruto-percent", percent_rainy);
	add_data(model_name+"-seco-fruto", quant_dry);
	add_data(model_name+"-chuvoso-fruto", quant_rainy);
}


/*!configura quantidade de árvores com flores e quantidade de flores por estação*/
void Vegetal::configure_edible_vegetal_flower(string model_name, int percent_dry, int quant_dry, int percent_rainy, int quant_rainy )
{
	add_data(model_name+"-seco-flor-percent", percent_dry);
	add_data(model_name+"-chuvoso-flor-percent", percent_rainy);
	add_data(model_name+"-seco-flor", quant_dry);
	add_data(model_name+"-chuvoso-flor", quant_rainy);
}

/*! Handler para gerar modelos
 * @param name - nome do vegetal
 * @param area - altitude que se encontra
 * @param radius - raio do modelo
 * @param scale - escala do modelo
 * @param offset_z - deslocamento do modelo no eixo z*/
void Vegetal::add_vegetal_model(const string &name, float radius, float scale, float offset_z, float multiplicador, float x, float y, float z)
{
	vegetals_name.push_back(name);

	map<Season::SeasonType,string>::iterator current;
	for(current = seasons.begin(); current != seasons.end(); current++)
	{
		string posfix = current->second;
		const string &map_name = name + posfix;
		PT(Vegetal) especie = new Vegetal(*ModelRepository::get_instance()->get_model(map_name));

                //ADICIONA NÓ DE COLISÃO A TODOS OS VEGETAIS CARREGADOS
                //esses valores de raios não estão perfeitos ainda
                collision::get_instance()->esferaCollision(especie, x, y, z, multiplicador*radius);
		//especie->set_area(area);
		especie->set_radius(radius);
		especie->set_scale(scale);
		especie->set_offset_z(offset_z);
		especie->set_vegetal_name(name);
		especie->set_vegetal_season(current->first);

		models[map_name] = especie;

		//carrega modelos para o serteio dos vegetais
		if( current->first == Season::DRY )
			low_area.push_back(especie);
	}

}

//handler para carregar a lista de modelos de vegetal
void Vegetal::add_vegetal_model(const string &map_name, const string &reposit_name, const string &veg_name,
	            Area::AreaType area, float radius, float scale, float offset_z)
{
	PT(Vegetal) especie = new Vegetal(*ModelRepository::get_instance()->get_model(reposit_name));


        especie->set_area(area);
	especie->set_radius(radius);
	especie->set_scale(scale);
	especie->set_offset_z(offset_z);
	especie->set_vegetal_name(veg_name);

	models[map_name] = especie;
}

//handler para carregar a lista de dados gerais de vegetal
void Vegetal::add_data(const string &map_name, int value)
{
	datas[map_name] = value;
}

/*! Carrega todos os vegetais do jogo */
void Vegetal::load_vegetals(int density) {

	load_default_model_and_data();

	//Vegetal::vegetals_placeholder = Simdunas::get_window()->get_render().attach_new_node("Vegetals Placeholder");
	//Vegetal::vegetals_placeholder.reparent_to(Simdunas::get_window()->get_render());
	Vegetal::visible_vegetals_placeholder.reparent_to(Simdunas::get_window()->get_render());

	int terrain_x_size = (int) World::get_world()->get_terrain()->get_x_size();
	int terrain_y_size = (int) World::get_world()->get_terrain()->get_y_size();

	point_max = LPoint2d(terrain_x_size, terrain_y_size);

	// Distâncias de configuração entre árvores e entre centros.
	tree_distance = 0;
	tree_points = (density/10) + 25 ;
	//shadow_radius = 1;

	// Quantidade de pontos de árvores e de centros.
	center_distance = 15;//15;
	center_points = 3 * density;
	center_edge = 4;//2;

	srand(time(NULL));

	//configure_vegetals();
	build_forest();
	configure_show_hide_event();

	configure_change_season_event();
	int month = TimeControl::get_instance()->get_mes();
	if (month >= 6 && month < 12)
		change_season(Season::DRY);
	else
		change_season(Season::RAINY);
}

/*! Remove todos os vegetais e comestíveis*/
void Vegetal::unload_vegetals() {
	// Removendo os vegetais dos setores
	// O Garbage do Panda (PT) já cuida de deletar
	for (int cont = 0; cont < Terrain::MAX_SETORES; cont++){
		World::get_world()->get_terrain()->get_setor(cont)->vegetals()->clear();
		World::get_world()->get_terrain()->get_setor(cont)->edible_vegetals()->clear();
	}
	models.clear();

	vegetals_placeholder.remove_node();
}

/*! Dá flatten no animais por setores. */
void Vegetal::flatten_vegetals(){
	/* Patch para dar flatten na vegetação */
	/* Problemas no Patch:
	 * 	- Em alguns trechos do código, utiliza-se get_pos(). Com a operação
	 * 	de flatten, esta informação é perdida.
	 * Por enquanto, estou criando uma cópia (sic) e colocando para renderizar.
	 * */
	PT(Terrain) terrain = World::get_world()->get_terrain();

	for(int i = 0; i < terrain->MAX_SETORES; i++){
		PT(Setor) sector = terrain->get_setor(i);
		SectorItems<PT(Vegetal)>::iterator it = sector->vegetals()->begin();
		while(it != sector->vegetals()->end()){
			//NodePath vcopy = (*it)->copy_to(NodePath("Vegetal_copy"));
			NodePath vcopy = (*it)->instance_to(NodePath("Vegetal_copy"));
			//(*it)->reparent_to(sector->_vegetals);
			vcopy.reparent_to(sector->_vegetals);
			it++;
		}
		sector->_vegetals.clear_model_nodes();
		sector->_vegetals.flatten_strong();
	}
}

void Vegetal::configure_change_season_event(){
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_month, hook_change_season, NULL);
}

void Vegetal::hook_change_season(const Event* evt, void *data){
	if( TimeControl::get_instance()->get_mes() == 6)
		change_season(Season::DRY);
	if( TimeControl::get_instance()->get_mes() == 12)
		change_season(Season::RAINY);
}

void Vegetal::change_season(Season::SeasonType season){
	current_season = season;
	World::get_world()->get_terrain()->remove_all_edible_vegetals();

	for (int cont = 0; cont < Terrain::MAX_SETORES; cont++){
		SectorItems<PT(Vegetal)>* vegetals = World::get_world()->
				get_terrain()->get_setor(cont)->vegetals();
		SectorItems<PT(Vegetal)>::iterator it;
		for(it = vegetals->begin(); it != vegetals->end(); ++it){
			//busca por modelo a partir do nome e estacao
			string model_name = (*it)->get_vegetal_name();
			model_name += seasons[current_season];

			//sorteia chance do vegetal mudar na estacao
			if( rand() % 100 < datas[model_name] )
			{
				PT(Vegetal) new_vegetal =  new Vegetal( models[model_name] );

				new_vegetal->configure_position(*it);
				new_vegetal->configure_vegetal(*it);

				*it = NULL;
				*it = new_vegetal;

				//sorteia frutos
				(*it)->load_edible_vegetals(new_vegetal->get_vegetal_name(), season);
			}
		}
	}
}

/*!atualiza setores visiveis e invisiveis de acordo com o player*/
void Vegetal::update_show_hide(){
	PT(Terrain) terrain = World::get_world()->get_terrain();
	int max_sectors = terrain->MAX_SETORES;

	for (int i = 0; i < max_sectors; ++i){
		PT(Setor) sector = terrain->get_setor(i);

		//config inicial
//		if( sector->is_player_neighbor() )
//			sector->show_vegetals();
//		else
//			sector->hide_vegetals();

		if(sector->is_player_neighbor()) sector->_vegetals.show();
		else sector->_vegetals.hide();
	}
	World::get_world()->get_terrain()->get_shadows()->update_active_shadows();
}

/*! configura eventos de show and hide dos setores*/
void Vegetal::configure_show_hide_event(){
	update_show_hide();
}

/*! escolhe quais e quantos frutos/flores serão sorteados e carrega*/
void Vegetal::load_edible_vegetals(string veg_name, Season::SeasonType type) {

	string season_vegetal = veg_name;
	if(type == Season::DRY)
		season_vegetal += "-seco";
	else
		season_vegetal += "-chuvoso";

	int quant_flower = datas[season_vegetal+"-fruto"];
	int quant_fruit = datas[season_vegetal+"-flor"];

	load_edible_vegetal_model(veg_name, quant_flower, quant_fruit);
}

/*!carregamento propriamente dito do modelo*/
void Vegetal::load_edible_vegetal_model(string name, int quant_flower, int quant_fruit) {

	int max_edible_per_tree = quant_flower + quant_fruit;
	int radius_size = 1;
	EdibleT::EdibleType type;

	float param = 0, result;

	//qunatidade de frutos
	int quant = 0;
	if(max_edible_per_tree > 0)
		quant = rand() % max_edible_per_tree;
	//pequena variacao para n parecer padronizado
	param += rand() % 360;

	/*
	Divide 359 graus pela quantidade de frutos e posiciona cada uma
	na posicao achada
	*/
	for(int c = 0; c < quant; param+=(360.0/quant), c++ )
	{

		//sorteia posicao mais perto ou mais longe da arvore
		radius_size = static_cast<int>(get_radius());
		float radius = (rand()%radius_size) + 1;
		//cout << "radius: " << radius << endl;
		int variation = (rand() % 10) -5;
		param+=variation;

		//TODO: mudar valor de 3.14 para PI
		result = cos (param*3.14/180);
		float new_x = get_x() + result*radius;
		result = sin (param*3.14/180);
		float new_y = get_y() + result*radius;

		//escolhe fruto ou flor
		if(quant_flower == 0) {
			type = EdibleT::FRUIT;
			--quant_fruit;
		}
		if(quant_fruit == 0) {
			type = EdibleT::FLOWER;
			--quant_flower;
		}
		if(quant_fruit > 0 && quant_flower > 0) {
			if( rand() % 2 == 0 ) {
				type = EdibleT::FLOWER;
				--quant_flower;
			}
			else {
				type = EdibleT::FRUIT;
				--quant_fruit;
			}
		}

		// configura vegetal comestivel
		PT(EdibleVegetal) vegetal = EdibleVegetal::get_edible_vegetal(name, type);
		if(vegetal != NULL) {
			vegetal->set_x(new_x);
			vegetal->set_y(new_y);

			vegetal->set_z(World::get_world()->get_terrain()->get_elevation(new_x,new_y)+vegetal->get_offset_z()+2);
			vegetal->set_h(rand()%360);
			World::get_world()->get_terrain()->add_edible_vegetal(vegetal);
		}
	}

}


/*! Adiciona uma certa aleatoriedade na area.
 * 5% de chance de ser um vegetal de area diferente da area real */
Area::AreaType Vegetal::randomize_area(Area::AreaType area) {

	int area_percent = rand() % 100;
	int percent_different_tree = 5;

	if (area_percent <= percent_different_tree) {
		/* Se for alguma área dos extremos, centraliza a "descaracterização"
		 * Acho que o motivo é não deixar uma árvore "avançar" duas áreas.
		 * As árvores do meio devem ir para cima ou para baixo. */
		if (area == Area::LOW || area == Area::HIGH) return Area::MID;
		else if (area_percent < ((int) (percent_different_tree / 2))) return Area::LOW;
		else return Area::HIGH;
	}

	return area;
}

/*! Sorteia um vegetal de determinada área */
PT(Vegetal) Vegetal::get_random_vegetal(Area::AreaType area) {
	unsigned int index;
	vector<PT(Vegetal)> * vegetals;
	vegetals = &low_area;

	index = get_random_vegetal_index_by_density(vegetals, area);
	return new Vegetal( vegetals->at(index) );

}

/*! escolhe um vegetal considerando a sua densidade por area*/
int Vegetal::get_random_vegetal_index_by_density( vector<PT(Vegetal)> *vegetals, Area::AreaType area )
{
	int max = 0;
	unsigned int index = 0;
	string name_density;

	while( index < vegetals->size() ) {
		name_density = vegetals->at(index++)->get_vegetal_name() + get_name_area(area) + "-density";
		max += datas[ name_density ];
	}

	int random = (rand() % max) + 1;
	index = 0;
	max = 0;
	while( index < vegetals->size() ) {
		name_density = vegetals->at(index)->get_vegetal_name() + get_name_area(area) + "-density";
		max += datas[ name_density ];
		if( max >= random )
			return index;
		index++;
	}

	return 0;
}

string Vegetal::get_name_area(Area::AreaType area)
{
	switch (area) {
	case Area::LOW:
		return "-low";
		break;
	case Area::MID:
		return "-mid";
		break;
	case Area::HIGH:
		return "-high";
		break;
	default:
		cout << "Erro em get_name_area() na classe Center" << endl;
		exit(1);
	}
}

/*! verifica se o vegetal eh distribuido em conjuntos*/
bool Vegetal::is_vegetal_group(PT(Vegetal) vegetal)
{
	//quipa bromelia mimosa
	if( vegetal->get_vegetal_name().compare("quipa") == 0 )
		return true;
	if( vegetal->get_vegetal_name().compare("bromelia") == 0 )
		return true;
	if( vegetal->get_vegetal_name().compare("mimosa") == 0 )
		return true;
	return false;
}

/*! Realiza a distribuição das árvores */
void Vegetal::build_forest(){

	vector<LVecBase3f> centers = generate_elements(LPoint2d(0, 0), point_max, center_points, center_distance, center_edge);
	generate_elements_buffer.clear();

	int quantidade_arv = 0;
	// Para cada centro, gera as árvores.
	for( unsigned int i = 0; i < centers.size(); i++){
		LPoint2d start = LPoint2d(centers[i].get_x() - center_distance,
											centers[i].get_y() - center_distance);
		LPoint2d end = LPoint2d(centers[i].get_x() + center_distance,
											centers[i].get_y() + center_distance);

		//definindo area do centro
		int current_z = (int)( World::get_world()->get_terrain()->get_elevation(centers[i].get_x(), centers[i].get_y()));
		Area::AreaType area = Area::MID;

		if(current_z <= LOW_TERRAIN_DIVISION) area = Area::LOW;
		else if (current_z > HIGH_TERRAIN_DIVISION) area = Area::HIGH;

		bool distributable = true;
		int cont_tree = 0;
		vector<LVecBase3f> vegetals;
		int cont_conjunt = 0;
		string veg_name;
		LPoint2d group_start, group_end;

		//porcentagem de vegetais na area
		int new_tree_points = tree_points;
		if(area == Area::LOW) new_tree_points = tree_points * VEGETAL_PERCENT_LOW_AREA / 100;
		if(area == Area::MID) new_tree_points = tree_points * VEGETAL_PERCENT_MID_AREA / 100;
		if(area == Area::HIGH) new_tree_points = tree_points * VEGETAL_PERCENT_HIGH_AREA / 100;

		//distribuindo vegetais
		while( distributable && (cont_tree < new_tree_points) )
		{
			Area::AreaType area_tree = randomize_area(area);
			PT(Vegetal) vegetal;
			unsigned int old_cont = vegetals.size();

			//sorteia a posicao do vegetal no centro
			//separa sorteio por vegetais de grupo ou normal
			//vegetais de grupo so sao achados em conjunto com outros da mesma especie
			if(cont_conjunt <= 0)
			{
				vegetal = get_random_vegetal(area_tree);
				vegetals = generate_elements(start, end, 1, tree_distance, vegetal->get_radius());
				if( is_vegetal_group(vegetal) )
				{
					cont_conjunt = rand()%6 + 1;
					veg_name = vegetal->get_vegetal_name() + "-seco";
					group_start = LPoint2d ( vegetals[old_cont].get_x() - 4 * vegetal->get_radius(),
					                         vegetals[old_cont].get_y() - 4 * vegetal->get_radius());
					group_end = LPoint2d ( vegetals[old_cont].get_x() + 4 * vegetal->get_radius(),
					                         vegetals[old_cont].get_y() + 4 * vegetal->get_radius());
				}
			}
			else
			{
				map<string,PT(Vegetal)>::iterator it = models.find(veg_name);
				vegetal = new Vegetal( it->second );
				vegetals = generate_elements(group_start, group_end, 1, tree_distance, vegetal->get_radius());
				cont_conjunt--;
			}

			//verifica se foi possivel acrescentar a arvore
			if( vegetals.size() > old_cont )
			{
				quantidade_arv++;
				//configura arvore
				vegetal->set_pos(vegetals[old_cont].get_x(), vegetals[old_cont].get_y(), 0);
				vegetal->set_h(rand() % 360);
				//vegetal->load_edible_vegetal_model("eugenia",0,3);
				vegetal->load_edible_vegetals(vegetal->get_vegetal_name(), current_season);

				// adicionar pequenas variações no tamanho, largura etc.

				// Sombras
				PNMImage shadow_image = PNMImage();
				//TODO: fazer o raio variavel de acordo com a arvore
				int shadow_radius = datas[ vegetal->get_vegetal_name() + "-shadow-radius"];
				shadow_image.set_read_size( vegetal->get_radius()+shadow_radius, vegetal->get_radius()+shadow_radius);
				shadow_image.read("models/sombra.png");

				//Criar as sombras da árvore.
				World::get_world()->get_terrain()->get_shadows()->create_shadow(shadow_image, *vegetal);
				World::get_world()->get_terrain()->add_vegetal(vegetal);
				cont_tree++;
			}
			else
			{
				distributable = false;
				vegetal = NULL;
			}
		}

		/*
		//mostra apenas (distancia x, distancia y, distancia necessaria) entre vegetais
		for( int i = 0; i < generate_elements_buffer.size() - 1; i++)
			for( int j = i + 1; j < generate_elements_buffer.size(); j++)
			{
				float x = fabs( generate_elements_buffer[i].get_x() - generate_elements_buffer[j].get_x() );
				float y = fabs( generate_elements_buffer[i].get_y() - generate_elements_buffer[j].get_y() );
				int radius = tree_distance + generate_elements_buffer[i].get_z() + generate_elements_buffer[j].get_z();
				nout << "(" << x << "," << y << "," << radius << ") ";
			}
			nout << endl << endl;
		*/

		//limpa buffer com com todas as posicoes de arvore
		generate_elements_buffer.clear();
	}


	cout << "quantidade de centros gerados: " << centers.size() << endl;
	cout << "quantidade de arvores geradas: " << quantidade_arv << endl;

	// Adiciona um pouco de transparencia ao canal das sombras.
	World::get_world()->get_terrain()->get_shadows()->add_transparency_to_shadows(0.5);
	// De fato mostra as sombras. É como se tivesse fazendo antes um offscreen buffer.
	World::get_world()->get_terrain()->get_shadows()->update_shadows();
}



/*! Gera pontos de vegetação ou centros dados:
 * @param start - inicio da área de geração de pontos-chaves
 * @param end	- fim da área de geração de pontos-chaves
 * @param qtd	- quantidade de centros/vegetais gerados.
 * @param distance - distância entre centros/vegetais.
 * @param model_radius - quando há um modelo com raio especifico */

vector<LVecBase3f> Vegetal::generate_elements(LPoint2d start, LPoint2d end, int qtd, float distance, float model_radius){

	int current_qtd = 0;
	int current_error = 0;
	LVecBase3f random_point;
	random_point.set_z(model_radius);

	while((current_qtd < qtd) && (current_error < MAX_CENTER_GEN_ERROR)){
		/* A área tem um ponto de inicio e de fim.
		 * Então, sorteia-se um ponto dentro dessa area levando em consideração que ele tem um raio (distance).
		 * rand_x = rand() % (TAMANHO_DA_AREA_LEVANDO_EM_CONTA_O_RAIO) + (POSICIONANDO_NO_PERIMETRO_CERTO).
		 * O TAMANHO_DE_AREA considera de 0 ao tamanho máximo mas desconsidera que esse bloco de area pode
		 * estar localizado em outro ponto de um terreno maior, portanto soma-se + inicio.get_"V"().
		 * A soma + distance em POSICIONAMENTO serve para centralizar. */

		LPoint2d lengths = start - end;
		random_point.set_x( rand() % (int) ((int)fabs(lengths.get_x()) - 2*(distance+model_radius)) + start.get_x() + distance + model_radius);
		random_point.set_y( rand() % (int) ((int)fabs(lengths.get_y()) - 2*(distance+model_radius)) + start.get_y() + distance + model_radius);

		// Verifica se é uma posição válida e instancia um vegetal seguindo os padrões de area etc.
		if(verify_distance(&generate_elements_buffer, random_point, distance + model_radius)
		     && World::get_world()->get_terrain()->has_inside(random_point)){
			// Mantém controle sobre os pontos (até sair do escopo) e gera o vegetal.
			generate_elements_buffer.push_back(random_point);
			current_qtd++;
			current_error = 0;
		}
		else current_error++;
	}
	return generate_elements_buffer;
}



/*! Confere com todos os pontos já distribuidos, se o ponto + distancia é uma posicão válida e
 * se esta dentro da area total permitida
 */

bool Vegetal::verify_distance(vector<LVecBase3f>* points, LVecBase3f point, float distance){

	for( unsigned int i = 0; i < points->size(); i++){
		float x = fabs( points->at(i).get_x() - point.get_x() );
		float y = fabs( points->at(i).get_y() - point.get_y() );

		if( x < distance + (*points)[i].get_z() && y < distance + (*points)[i].get_z() ) return false;

		if(point.get_x() + distance >= point_max.get_x() || point.get_y() + distance >= point_max.get_y()
	    	|| point.get_x() - distance <= 0 || point.get_y() - distance <= 0)
			return false;

	}

	return true;
}

/*! Obtém o raio do vegetal */
float Vegetal::get_radius(){
	return radius;
}

/*! Define o raio do vegetal */
void Vegetal::set_radius(float radius){
	this->radius = radius;
}

/*! Obtém em qual area o vegetal se encontra */
Area::AreaType Vegetal::get_area(){
	return area;
}

/*! Define em qual area o vegetal se encontra */
void Vegetal::set_area(Area::AreaType area) {
	this->area = area;
}

void Vegetal::set_vegetal_name(string name) {
	vegetal_name = name;
}

string Vegetal::get_vegetal_name() {
	return vegetal_name;
}

void Vegetal::set_vegetal_season(Season::SeasonType type) {
	season_type = type;
}
Season::SeasonType Vegetal::get_vegetal_season() {
	return season_type;
}

Season::SeasonType Vegetal::get_season() {
	return current_season;
}
