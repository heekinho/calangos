#include "terrain.h"

#include "modelRepository.h"
#include "cardMaker.h"
#include "referenceCount.h"
#include "typedReferenceCount.h"
#include "texturePool.h"


PT(Terrain)  Terrain::terrain = NULL;
TypeHandle Terrain::_type_handle;

// Constroi um novo terreno com o nome especificado
Terrain::Terrain(const string &name) : GeoMipTerrain (name) {
	nout << "Criando Terreno..." << endl;
	escala = 1;

	//window->set_wireframe(true);

	shadows = new ShadowCard(LPoint2f(512, 512), LPoint2f(512, 512));
	this->get_root().set_texture(shadows->get_stage(), shadows->get_texture());

	//event_handler->add_hook(PlayerControl::EV_player_move, update_terrain, this);
	//get_root().hide();
}


/*! Adiciona um lagarto no setor correspondente à sua posição */
void Terrain::add_lizard(PT(Lizard) lizard){
	get_setor_from_pos(lizard->get_x(), lizard->get_y())->lizards()->push_back(lizard);
}

/*! Adiciona um animal no setor correspondente à sua posição */
void Terrain::add_animal(PT(Animal) animal){
	get_setor_from_pos(animal->get_x(), animal->get_y())->animals()->push_back(animal);
}

/*! Adiciona uma presa no setor correspondente à sua posição */
void Terrain::add_prey(PT(Prey) prey){
	list_prey.push_back(prey);
	get_setor_from_pos(prey->get_x(), prey->get_y())->preys()->push_back(prey);
}

/*! Adiciona um predador no setor correspondente à sua posição */
void Terrain::add_predator(PT(Predator) predator){
	get_setor_from_pos(predator->get_x(), predator->get_y())->predators()->push_back(predator);
}

/*! Adiciona um vegetal ao seu respectivo setor */
void Terrain::add_vegetal(PT(Vegetal) vegetal){
	get_setor_from_pos(vegetal->get_x(), vegetal->get_y())->vegetals()->push_back(vegetal);
}

void Terrain::add_edible_vegetal(PT(EdibleVegetal) vegetal){
	//	Setor::add_edible_vegetal(vegetal, get_setor_from_pos(vegetal->get_x(), vegetal->get_y()));
	get_setor_from_pos(vegetal->get_x(), vegetal->get_y())->edible_vegetals()->push_back(vegetal);
}

void Terrain::remove_all_edible_vegetals(){
	vector<PT(Setor)>::iterator setor = _setores.begin();
	while( setor != _setores.end()) {
		(*setor)->edible_vegetals()->clear();
		setor++;
	}
}

PT(Terrain) Terrain::get_default_terrain(){
	if(terrain==NULL){
		create_default_terrain();

	}
	return terrain;
}


void Terrain::create_default_terrain(){
	cout<< "1 create_defalt_terrain chamado "<< endl;
	if(terrain==NULL){
		// Cria o Terreno -----------------------------------------------------//
		terrain = new Terrain("Default_Dunas_Enviroment");

		// Carrega o heightfield e a textura
		terrain->set_heightfield(Filename("models/terrain/heightmaps/heightmap_dunes.png"));

		// Configuracoes de textura para perto
		PT(Texture) terrain_tex_near = TexturePool::load_texture("models/terrain/tile_near.jpg");
		terrain_tex_near->set_wrap_u(Texture::WM_repeat);
		terrain_tex_near->set_wrap_v(Texture::WM_repeat);
		terrain_tex_near->set_minfilter(Texture::FT_linear_mipmap_linear);

		PT(TextureStage) stage_near = new TextureStage("stage_near");
		terrain->get_root().set_texture(stage_near, terrain_tex_near);
		terrain->get_root().set_tex_scale(stage_near, 4096);

		// Configuracoes de textura para longe
		PT(Texture) terrain_tex_far = TexturePool::load_texture("models/terrain/tile_far.jpg");
		terrain_tex_far->set_wrap_u(Texture::WM_repeat);
		terrain_tex_far->set_wrap_v(Texture::WM_repeat);
		terrain_tex_far->set_minfilter(Texture::FT_linear_mipmap_linear);

		PT(TextureStage) stage_far = new TextureStage("stage_far");
		terrain->get_root().set_texture(stage_far, terrain_tex_far);
		terrain->get_root().set_tex_scale(stage_far, 20);

		terrain->get_root().reparent_to(render);
		terrain->set_focal_point(LPoint2d(256, 256));


		// Com Bruteforce: (Configuração legal: min_level: 2, 3, 4, block: 64)
		terrain->set_bruteforce(true);
		terrain->set_min_level(0);		/* Pode-se deixar configurável, mas precisa-se implementar o get_height de mipmap */
		//fiz alteração no valor do size block de 128 para 64
		terrain->set_block_size(64);	/* 128 parece oferecer o melhor trade-off. FPS melhor e mais estável */
		terrain->generate();


		//		// Gera o Terreno, sem bruteforce.
		//		//terrain->set_min_level(0);
		//		terrain->set_block_size(32);
		//		terrain->set_near_far(40, 100);
		//		terrain->generate();
		//		terrain->set_focal_point(*player);
		////		terrain->set_auto_flatten(GeoMipTerrain::AFM_strong);


		// Configuracoes do terreno
		terrain->set_escala(1);
		terrain->get_root().set_sz(16);
		terrain->init_sectors();
		//terrain->draw_map();
		//terrain->get_root().set_render_mode_wireframe(); //ativa wire_frame do terreno
		//--------------------------------------------------------------------//

		terrain->folhagem = new Foliage();

	}

}

/*! Necessário para atualizar o ponto focal para o LOD do terreno */
//TODO: Mudar nome para update_terrain...
void Terrain::update_terrain(const Event*, void *data){
	//terrain->set_focal_point(player->get_pos());
	terrain->update();
}
void Terrain::draw_map(){
	//#### método que tenta modificar posição do terreno para resolver o problema de sobre posição com as folhagens (sem sucesso)
	NodePathCollection nodePathCollection = terrain->get_root().find_all_matches("**/+GeomNode");

	cout << "Quantidade de nodePath:  " << nodePathCollection.size() << endl; //retornou 64
	for (int i = 0; i < nodePathCollection.size(); ++i)
	{

		NodePath nodePath = nodePathCollection[i];

		//obtem posição de cada NodePath em relação ao NodePath root
		float x = nodePath.get_pos(terrain->get_root()).get_x();
		float y = nodePath.get_pos(terrain->get_root()).get_y();
		//descobre o block onde o NodePath está
		LVecBase2f lbase2  =  terrain->get_block_from_pos(x,y);
		//obtem o indice x e y do block
		unsigned int index_x  = lbase2.get_x();
		unsigned int index_y  = lbase2.get_y();


		PT(GeomNode) geomNode = DCAST(GeomNode, nodePath.node());
		PT(GeomVertexData)  vdata = geomNode->modify_geom(0)->modify_vertex_data();

		GeomVertexWriter vertexWriter = GeomVertexWriter(vdata, "vertex");
		GeomVertexReader vertex = GeomVertexReader(vdata, "vertex");

		while (!vertex.is_at_end())
		{
			const LVecBase3f& v = vertex.get_data3f();
			//convertendo para posição real do terreno
			float pos_x = (v.get_x() + 32) + 64*index_x;
			float pos_y = (v.get_y() + 32) + 64*index_y;
			//    cout << "indices (x,y)" << x <<  y << endl;

			float pos_z = terrain->get_elevation(pos_x, pos_y)/16;

			if(pos_z != v.get_z()){ //Em nenhum momento entra nesse if
				cout << "Coordenadas x,y,z e novo_z" << endl;
				cout << v.get_x() << ", "  <<   v.get_y()  << ", "  << v.get_z() << " e "  << pos_z << endl;
			}

			vertexWriter.set_data3f(v.get_x() , v.get_y() , pos_z); //faz modificação

		}//fim do while

	}//fim do for

}

Terrain::~Terrain(){
	shadows = NULL;
	delete water_maker;
	buffer = NULL;
	water_tex = NULL;
	water_stage = NULL;
}


int Terrain::get_x_size(){
	return terrain->escala * (terrain->heightfield().get_x_size() - 1);
}

int Terrain::get_y_size(){
	return terrain->escala * (terrain->heightfield().get_y_size() - 1);
}


void Terrain::set_escala(int escala){
	terrain->escala = escala;
	terrain->get_root().set_scale(terrain->escala);
}

int Terrain::get_escala(){
	return terrain->escala;
}


/*! Adiciona setor */
void Terrain::add_setor(PT(Setor) setor){
	if(_setores.size() < MAX_SETORES){
		_setores.push_back(setor);
	}
}

/*! Obtem setor */
PT(Setor) Terrain::get_setor(int setor){
	return _setores.at(setor);
}


/*! Obtem um setor a partir de um determinado ponto */
PT(Setor) Terrain::get_setor_from_pos(LPoint2d pos){
	return get_setor_from_pos(pos.get_x(), pos.get_y());
}

/*! Obtem um setor a partir de um determinado ponto */
PT(Setor) Terrain::get_setor_from_pos(int x, int y){

	//cout << "posicao: " << pos.get_x() << " , " << pos.get_y() << endl;
	int column = (int) x/(get_x_size()/NUM_SECTORS_X);
	int line = (int) y/(get_y_size()/NUM_SECTORS_Y);

	// O código tava quebrando ao retornar setores inexistentes.
	if(column > NUM_SECTORS_X - 1) column = NUM_SECTORS_X - 1;
	if(column < 0) column = 0;
	if(line > NUM_SECTORS_Y - 1) line = NUM_SECTORS_Y - 1;
	if(line < 0) line = 0;

	//int index = column + (8 * line);

	int index = (column * NUM_SECTORS_X) + line;
	return _setores.at(index);
}

/*! Obtem os setores mais próximos baseando-se no subsetor. Cada setor é dividido em
 * quatro subsetores, somentes os setores mais próximos à esses subsetores estão listados*/
vector<PT(Setor)> *Terrain::get_closest_sectors(){
	return &closest_sector;
}

/*! Atualiza os setores mais próximos do subsetor*/
void Terrain::update_closest_sectors(PT(Setor) s, LPoint2d subsector){

	for(unsigned int i = 0; i < closest_sector.size(); i++){
		closest_sector.at(i)->set_is_closest_sector(false);
	}

	closest_sector.clear();
	if(subsector.get_x() == 1){

		if(subsector.get_y() == 1){//Subsetor Superior Direito
			//Setor Acima do subsetor
			LPoint2d clo_sector = s->get_pos_start() + LPoint2d( 0 * (get_x_size()/8) , 1*(get_y_size()/8));
			PT(Setor) sector_found = get_setor_from_pos(clo_sector);
			//Considerando o setor próximo ao player
			sector_found->set_is_closest_sector(true);
			//Colocando na lista de setores próximos
			closest_sector.push_back(sector_found);

			//Setor na diagonal ao subsetor
			clo_sector =  s->get_pos_start() + LPoint2d( 1 * (get_x_size()/8) , 1 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);

			//Setor a direita ao subsector
			clo_sector =  s->get_pos_start() + LPoint2d( 1 * (get_x_size()/8) , 0 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);
			return;
		}

		else{//Subsetor Inferior Direito
			//Setor Abaixo do subsetor
			LPoint2d clo_sector = s->get_pos_start() + LPoint2d( 0 * (get_x_size()/8) , -1*(get_y_size()/8));
			PT(Setor) sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);

			//Setor na diagonal ao subsetor
			clo_sector =  s->get_pos_start() + LPoint2d( 1 * (get_x_size()/8) , -1 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);

			//Setor a direita ao subsector
			clo_sector =  s->get_pos_start() + LPoint2d( 1 * (get_x_size()/8) , 0 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);
			return;
		}
	}


	else{

		if(subsector.get_y() == 1){//Subsetor Superior Esquerdo
			//Setor Acima do subsetor
			LPoint2d clo_sector = s->get_pos_start() + LPoint2d( 0 * (get_x_size()/8) , 1*(get_y_size()/8));
			PT(Setor) sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);

			//Setor na diagonal do subsetor
			clo_sector =  s->get_pos_start() + LPoint2d( -1 * (get_x_size()/8) , 1 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);

			//Setor a esquerda do subsetor
			clo_sector =  s->get_pos_start() + LPoint2d( -1 * (get_x_size()/8) , 0 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);
			return;
		}

		else{//Subsetor Inferior Esquerdo

			//Setor Abaixo do subsetor
			LPoint2d clo_sector = s->get_pos_start() + LPoint2d(0 * (get_x_size()/8) , -1*(get_y_size()/8));
			PT(Setor) sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);

			//Setor na diagonal do subsetor
			clo_sector =  s->get_pos_start() + LPoint2d( -1 * (get_x_size()/8) , -1 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);

			//Setor a esquerda do subsetor
			clo_sector =  s->get_pos_start() + LPoint2d( -1 * (get_x_size()/8) , 0 * (get_y_size()/8));
			sector_found = get_setor_from_pos(clo_sector);
			sector_found->set_is_closest_sector(true);
			closest_sector.push_back(sector_found);
			return;
		}
	}
}


/*! Obtem os setores vizinhos... 8 se no meio, 6 se no canto e 3 se no extremo canto. */
vector<PT(Setor)> *Terrain::get_adjacent_sectors(){
	return &neighborhood;
}


/*! Obtem os setores vizinhos dado um setor de referencia */
void Terrain::update_adjacent_sectors(PT(Setor) s){
	// Tira todo mundo da vizinha


	for(unsigned int i = 0; i < neighborhood.size(); i++){
		neighborhood.at(i)->set_player_neighbor(false);
	}
	neighborhood.clear();

	int i = -1;
	int j = -1;
	for ( i = -1; i < 2; ++i) {
		for ( j = -1; j < 2; ++j) {
			LPoint2d adj_sector = s->get_pos_start() + LPoint2d(j * (get_x_size()/8), i * (get_y_size()/8));

			PT(Setor) sector_found = get_setor_from_pos(adj_sector);
			if(!sector_found->is_player_neighbor()){
				sector_found->set_player_neighbor(true);
				neighborhood.push_back(sector_found);
			}
		}
	}


	//
	//	nout << "neighbors(" << player->get_setor()->get_indice() << "): ";
	//	for(int i = 0; i < neighborhood.size(); i++){
	//		nout << neighborhood.at(i)->get_indice() << " ";
	//	}
	//	nout << endl;
}

/*! Atualiza a posição Z do objeto. Como parametro opcional, um offset,
 * para efetuar pequenos ajustes. */
void Terrain::update_node_z(NodePath node, double offset){
	node.set_z(terrain->get_elevation(node.get_x(), node.get_y()) + offset);
}

void Terrain::update_object_z(PT(ObjetoJogo) object, double aditional_offset){
	object->set_z(terrain->get_elevation(object->get_x(), object->get_y()) + object->get_offset_z() + aditional_offset);
}

double Terrain::get_elevation(double x, double y){
	return terrain->GeoMipTerrain::get_elevation(x, y)*get_root().get_sz();
}


/*! Inicializa os setores */
void Terrain::init_sectors(){

	int index = 0;
	int x_size = terrain->get_x_size();
	int y_size = terrain->get_y_size();
	int width = x_size/NUM_SECTORS_X;
	int height = y_size/NUM_SECTORS_Y;

	//no_setores=new NodePath[MAX_SETORES];//64 setores

	//// no_setores=render.attach_new_node("setor");

	std::string s;
	std::stringstream out;

	for(double x = 0; x < x_size; x = x + width) {
		for (double y = 0; y < y_size; y = y + height) {
			LPoint2d pos_inicio = LPoint2d(x, y);
			LPoint2d pos_fim = LPoint2d( x+(width-1), y+(height-1) );

			PT(Setor) setor = new Setor(pos_inicio, pos_fim, index);
			//out << index;
			//s = out.str();
			//no_setores[index]=render.attach_new_node("setor"+s);
			terrain->add_setor(setor);
			index++;



		}
	}

}

/*! Para Debug */
void Terrain::print_sectors(){
	for (unsigned int i = 0; i < _setores.size(); i++ ){
		cout << "\n Setor: " << _setores.at(i)->get_indice() << endl;
		cout << "posicao inicio : " << _setores.at(i)->get_pos_start().get_x() <<  " , " << _setores.at(i)->get_pos_start().get_y() << endl;
		cout << "posicao final : " <<  _setores.at(i)->get_pos_end().get_x() << " , " << _setores.at(i)->get_pos_end().get_y() << endl;
	}
}


/*! Verifica se um NodePath está dentro do Terrain */
bool Terrain::has_inside(NodePath node){
	return is_inside(node.get_x(), node.get_y());
}

/*! Verifica se um LPoint3f está dentro do Terrain */
bool Terrain::has_inside(LPoint3f point){
	return is_inside(point.get_x(), point.get_y());
}

bool Terrain::has_inside(LPoint2d point){
	return is_inside(point.get_x(), point.get_y());
}


bool Terrain::is_inside(float x, float y)
{
	if ((x <= 120) && (y <= 120)){
		//if ((y - (x*(-0.706)) >= 79.85) && (y - (x*(-0.825))  >= 87.15))
		if (y - (x*(-0.97)) >= 114.9)
			if ((x >= 0.5) && (x <= get_x_size()-0.5) && (y >= 0.5) && (y <= get_y_size()-0.5))
				return true;
	}
	else{
		if ( (x >= 382.2) && (y >= 382.2)){
			if( (x <= 507.9) && (y  <= 507.9))
				return true;
		}
		else
			if ((x >= 0.5) && (x <= get_x_size()-0.5) && (y >= 0.5) && (y <= get_y_size()-0.5))
				return true;
	}
	return false;
}



void Terrain::load_tocas(){

	for (int i = 0; i < MAX_SETORES; i++){
		PT(Setor) setor = get_setor(i);
		SectorItems<PT(Vegetal)>* vegetal_list = setor->vegetals();
		SectorItems<PT(ObjetoJogo)>* toca_list = setor->tocas();
		SectorItems<PT(Vegetal)>::iterator it;
		for (it = vegetal_list->begin(); it != vegetal_list->end(); ++it){
			PT(Vegetal) vegetal = (*it);
			double x = vegetal->get_x();
			double y = vegetal->get_y();
			double elevation  = get_elevation(x,y);
			double elevation_toca = get_elevation(x+1,y+1);

			if (elevation < 1 && elevation_toca < 1){
				toca_list->push_back( ModelRepository::get_instance()->get_model_instance("toca") );
				toca_list->back()->reparent_to(render);
				toca_list->back()->set_pos(x+1, y+1, 0);
				toca_list->back()->set_scale(0.001);
				if (toca_list->size() > 10){
					break;
				}

			}
		}
	}

}


/*! Carrega uma cerca em volta do terreno e algumas casas no limite das dunas.*/
void Terrain::load_terrain_limit(){
	double pos = 0;
	int terrain_x_size = terrain->get_x_size();
	int terrain_y_size = terrain->get_y_size();
	double limit = terrain_x_size - 0.5;

	NodePath left_fence_set = NodePath("Conjunto de cercas da Esquerda");
	NodePath top_fence_set = NodePath("Conjunto de cercas do Topo");
	NodePath down_fence_set = NodePath("Conjunto de cercas de Baixo");
	NodePath right_fence_set = NodePath("Conjunto de cercas da Direita");

	for(int i = 0; i < terrain_x_size; i+=5){
		pos = i;

		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(right_fence_set);
		cercas.back()->set_pos(limit, pos, 0);
		cercas.back()->set_scale(0.05);

		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(top_fence_set);
		cercas.back()->set_pos(pos, limit, 0);
		cercas.back()->set_scale(0.05);
		cercas.back()->set_h(*cercas.back(), -270);
	}

	for(int i = 130; i < terrain_y_size; i+=5){
		pos = i;
		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(down_fence_set);
		cercas.back()->set_pos(pos, 0.5, 0);
		cercas.back()->set_scale(0.05);
		cercas.back()->set_h(*cercas.back(), -270);
	}

	for(int i = 302; i < terrain_y_size; i+=5){
		pos = i;
		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(left_fence_set);
		cercas.back()->set_pos(0.5, pos, 0);
		cercas.back()->set_scale(0.05);
	}

	ModelRepository::get_instance()->get_model("cerca")->clear_model_nodes();
	top_fence_set.flatten_strong();
	right_fence_set.flatten_strong();
	left_fence_set.flatten_strong();
	down_fence_set.flatten_strong();

	top_fence_set.reparent_to(render);
	right_fence_set.reparent_to(render);
	left_fence_set.reparent_to(render);
	down_fence_set.reparent_to(render);


	string casa_model[6] = { "casa1", "casa2", "casa3", "casa2", "casa1", "casa3" };
	NodePath houses = NodePath("Conjuntos de casas");

	int index_casa = 0;
	double distancia = 11.5;
	for (double pos = 10.5; pos <= 130.0; pos += distancia) {
		casas.push_back( ModelRepository::get_instance()->get_model_instance( casa_model[index_casa] ) );
		casas.back()->reparent_to(houses);
		casas.back()->set_x(terrain_x_size - pos);
		casas.back()->set_y(terrain_y_size);
		casas.back()->set_scale(0.05);
		casas.back()->set_h(*casas.back(), 90);

		index_casa++;
		distancia = distancia + 1.0;
		if (index_casa > 2) {
			index_casa = 0;
			distancia = 11.5;
		}

		casas.push_back( ModelRepository::get_instance()->get_model_instance( casa_model[index_casa+3] ));
		casas.back()->reparent_to(houses);
		casas.back()->set_x(terrain_x_size);
		casas.back()->set_y(terrain_y_size - pos);
		casas.back()->set_scale(0.05);
	}

	ModelRepository::get_instance()->get_model("casa1")->clear_model_nodes();
	ModelRepository::get_instance()->get_model("casa2")->clear_model_nodes();
	ModelRepository::get_instance()->get_model("casa3")->clear_model_nodes();

	houses.flatten_strong();
	houses.reparent_to(render);
}

/*! Carrega o rio*/
void Terrain::load_water(){

	water_maker = new CardMaker("water_maker");
	water_maker->set_frame( 0, 120, 0, 120 );
	water = render.attach_new_node(water_maker->generate());
	water.set_hpr(0,-90,0);
	water.set_pos(0, 0, 1);
	water.set_transparency(TransparencyAttrib::M_alpha);
	//buffer = window->get_graphics_window()->make_texture_buffer("waterBuffer", 512, 512);
	//buffer->set_clear_color( LVector4f( 0, 0, 0, 1 ) );

	//	tex0 = buffer->get_texture();
	//	tex0->set_wrap_u(Texture::WM_clamp);
	//	tex0->set_wrap_v(Texture::WM_clamp);
	//	TextureStage *ts0 = new TextureStage("reflection");
	//	water.set_texture(ts0, tex0);

	water_tex = TexturePool::load_texture("models/terrain/down.png");
	water_tex->set_wrap_u(Texture::WM_repeat);
	water_tex->set_wrap_v(Texture::WM_repeat);

	water_stage = new TextureStage("water");
	water.set_texture(water_stage, water_tex);
	water.set_tex_scale(water_stage, 10);


}

void Terrain::unload_vectors(){
	casas.clear();
	cercas.clear();
	for (unsigned int cont = 0; cont < _setores.size(); cont++){
		_setores.at(cont)->tocas()->clear();
		_setores.at(cont)->unload_sector();
	}
	neighborhood.clear();
	_setores.clear();

}

void Terrain::unload_terrain(){
	unload_vectors();
	terrain->get_root().remove_node();
	water.remove_node();
	terrain = NULL;
}

/*! Retorna um ponto aleatório do terreno */
LPoint3f Terrain::get_random_point(){
	int x = rand() % get_x_size();
	int y = rand() % get_y_size();
	int z = get_elevation(x, y);

	return LPoint3f(x, y, z);
}

/*! Obtém o z em determinado ponto de forma amostrada. Pega-se 4 pontos, distantes
 * em radius metros do ponto de referência, e tira-se uma média. */
float Terrain::get_sampled_elevation(const LPoint2f &reference_point, float radius){
	LPoint2f s1 = reference_point + LPoint2f(radius, radius);
	LPoint2f s2 = reference_point + LPoint2f(radius, -radius);
	LPoint2f s3 = reference_point + LPoint2f(-radius, radius);
	LPoint2f s4 = reference_point + LPoint2f(-radius, -radius);

	LPoint2f sampled_position = (s1 + s2 + s3 + s4) * 0.25;

	return get_elevation(sampled_position.get_x(), sampled_position.get_y());
}

/*! Obtém a normal de determinado ponto do terreno */
LVector3f Terrain::get_normal(const LPoint2f &reference_point){
	/* A altura é carregada aqui para evitar possíveis erros de um LPoint3f.z */
	float elevation = get_elevation(reference_point[0], reference_point[1]);
	LPoint3f point = LPoint3f(reference_point[0], reference_point[1], elevation);

	/* Resolução para o cálculo da normal */
	float step = 0.01;

	/* Pega um ponto à frente. Pode ser axis-aligned, certo? */
	LPoint3f front = point + LPoint3f(0, -step, 0);
	front.set_z(get_elevation(front[0], front[1]));

	/* Pega um ponto ao lado */
	LPoint3f right = point + LPoint3f(step, 0, 0);
	right.set_z(get_elevation(right[0], right[1]));

	/* A normal é o produto vetorial dos vetores */
	LVector3f normal = (front - point).cross(right - point);
	normal.normalize();

	return normal;
}

/*! Obtém a normal de determinado ponto de forma amostrada. Pega-se 4 pontos,
 * distantes em radius metros do ponto de referência, e tira-se uma média. */
LVector3f Terrain::get_sampled_normal(const LPoint2f &reference_point, float radius){
	LVector3f n1 = get_normal(reference_point + LPoint2f(radius, radius));
	LVector3f n2 = get_normal(reference_point + LPoint2f(radius, -radius));
	LVector3f n3 = get_normal(reference_point + LPoint2f(-radius, radius));
	LVector3f n4 = get_normal(reference_point + LPoint2f(-radius, -radius));

	return (n1 + n2 + n3 + n4) * 0.25;
}
