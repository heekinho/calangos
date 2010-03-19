#include "terrain.h"

#include "modelRepository.h"
#include "cardMaker.h"
#include "referenceCount.h"
#include "typedReferenceCount.h"


PT(Terrain)  Terrain::terrain = NULL;
TypeHandle Terrain::_type_handle;

// Constroi um novo terreno com o nome especificado
Terrain::Terrain(const string &name) : GeoMipTerrain (name) {

	nout << "Criando Terreno..." << endl;
	escala = 1;

	// Configuraes Padrao do terreno:
	//this->get_root().set_sz(100);
	this->set_block_size(32);   // Se houver muito lag, aumentar o tamanho
	//this->set_min_level(0); // Quanto menos, melhor a qualidade
	//this->set_factor(100);
	//Simdunas::get_window()->set_wireframe(true);

	shadows = new ShadowCard(LPoint2f(512, 512), LPoint2f(512, 512));
	this->get_root().set_texture(shadows->get_stage(), shadows->get_texture());

	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_move, update_terrain, this);
}


void Terrain::add_lizard(PT(Lizard) lizard){
	Setor::add_lizard(lizard, get_setor_from_pos(lizard->get_x(), lizard->get_y()) );
}

/*! Adiciona um animal ao seu respectivo setor */
void Terrain::add_animal(PT(Animal) animal){
	Setor::add_animal(animal, get_setor_from_pos(animal->get_x(), animal->get_y()) );
}

void Terrain::add_predator(PT(Predator) predator){
	Setor::add_predator(predator, get_setor_from_pos(predator->get_x(), predator->get_y()) );
}


/*! Adiciona um vegetal ao seu respectivo setor */
void Terrain::add_vegetal(PT(Vegetal) vegetal){
	Setor::add_vegetal(vegetal, get_setor_from_pos(vegetal->get_x(), vegetal->get_y()));
}

void Terrain::add_edible_vegetal(PT(EdibleVegetal) vegetal){
	Setor::add_edible_vegetal(vegetal, get_setor_from_pos( LPoint2d(vegetal->get_x(), vegetal->get_y()) ));
}

void Terrain::remove_all_edible_vegetals(){
	vector<PT(Setor)>::iterator setor = _setores.begin();
	while( setor != _setores.end()) {
		(*setor)->remove_edible_vegetals();
		setor++;
	}
}

PT(Terrain) Terrain::create_default_terrain(){

	if(terrain==NULL){
		// Cria o Terreno -----------------------------------------------------//
		terrain = new Terrain("Default_Dunas_Enviroment");

		// Carrega o heightfield e a textura
		terrain->set_heightfield((Filename) "models/terrain/heightmaps/heightmap_dunes.png");

		// Configuracoes de textura para perto
		PT(Texture) terrain_tex_near = TexturePool::load_texture("models/terrain/tile_near.jpg");
		terrain_tex_near->set_wrap_u(Texture::WM_repeat);
		terrain_tex_near->set_wrap_v(Texture::WM_repeat);
		terrain_tex_near->set_minfilter(Texture::FT_nearest_mipmap_nearest);

		PT(TextureStage) stage_near = new TextureStage("stage_near");
		terrain->get_root().set_texture(stage_near, terrain_tex_near);
		terrain->get_root().set_tex_scale(stage_near, 2000);

		// Configuracoes de textura para longe
		PT(Texture) terrain_tex_far = TexturePool::load_texture("models/terrain/tile_far.jpg");
		terrain_tex_far->set_wrap_u(Texture::WM_repeat);
		terrain_tex_far->set_wrap_v(Texture::WM_repeat);

		PT(TextureStage) stage_far = new TextureStage("stage_far");
		terrain->get_root().set_texture(stage_far, terrain_tex_far);
		terrain->get_root().set_tex_scale(stage_far, 20);

		// Gera o Terreno
		terrain->generate();
		terrain->get_root().reparent_to(Simdunas::get_window()->get_render());
		terrain->set_focal_point(LPoint2d(256, 256));
		terrain->update();

		// Configuracoes do terreno
		terrain->get_root().set_pos(terrain->get_root(), 0, 0, 0);
		terrain->set_escala(1);
		terrain->get_root().set_sz(16);
		terrain->init_sectors();
		//--------------------------------------------------------------------//
		return terrain;
	}
	else
	{
		return terrain;
	}
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

	//nout << "column: " << column << "; line: " << line << endl;

	//int index = column + (8 * line);

	int index = (column * NUM_SECTORS_X) + line;
	return _setores.at(index);
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

	//nout << "Sector: " << s->get_indice() << ": ";
	// Define a nova vizinhança
	int flagx = -1, flagy = -1;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			LPoint2d adj_sector = s->get_pos_start() + LPoint2d(flagx * (get_x_size()/8), flagy * (get_y_size()/8));
			if(has_inside(adj_sector) /* && !((i == 1) && (j == 1))*/){
				PT(Setor) sector_found = get_setor_from_pos(adj_sector);
				sector_found->set_player_neighbor(true);
				neighborhood.push_back(sector_found);
				//nout << sector_found->get_indice() << "; ";
			}
			flagx++;
		}
		flagx = -1;
		flagy++;
	}

	//nout << endl << "Tamanho da vizinhanca: " << neighborhood.size();
}

/*! Necessário para atualizar o ponto focal para o LOD do terreno */
//TODO: Mudar nome para update_terrain...
void Terrain::update_terrain(const Event*, void *data){
	terrain->set_focal_point(Player::get_instance()->get_pos());
	terrain->update();
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

	for(double x = 0; x < x_size; x = x + width) {
		for (double y = 0; y < y_size; y = y + height) {
			LPoint2d pos_inicio = LPoint2d(x, y);
			LPoint2d pos_fim = LPoint2d( x+(width-1), y+(height-1) );

			PT(Setor) novoSetor = new Setor(pos_inicio, pos_fim, index);
			terrain->add_setor(novoSetor);
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
  		vector<PT(Vegetal)>* vegetal_list = setor->get_vegetals();
  		vector<PT(ObjetoJogo)>* toca_list = setor->get_tocas();
  		for (unsigned int j = 0; j < vegetal_list->size(); j++){
			PT(Vegetal) vegetal = vegetal_list->at(j);
			double x = vegetal->get_x();
			double y = vegetal->get_y();
			double elevation  = get_elevation(x,y);
			double elevation_toca = get_elevation(x+1,y+1);
			if (elevation < 1 && elevation_toca < 1){
				toca_list->push_back( ModelRepository::get_instance()->get_model_instance("toca") );
				toca_list->back()->reparent_to(Simdunas::get_window()->get_render());
				toca_list->back()->set_pos(x+1, y+1, 0);
				toca_list->back()->set_scale(0.001);
				if (toca_list->size() > 10)
					break;
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

	for(int i = 0; i < terrain_x_size; i+=5){
		pos = i;
		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(Simdunas::get_window()->get_render());
		cercas.back()->set_pos(limit, pos, 0);
		cercas.back()->set_scale(0.05);

		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(Simdunas::get_window()->get_render());
		cercas.back()->set_pos(pos, limit, 0);
		cercas.back()->set_scale(0.05);
		cercas.back()->set_h( *cercas.back(), -270);
	}

	for(int i = 130; i < terrain_y_size; i+=5){
		pos = i;
		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(Simdunas::get_window()->get_render());
		cercas.back()->set_pos(pos, 0.5, 0);
		cercas.back()->set_scale(0.05);
		cercas.back()->set_h(*cercas.back(), -270);
	}

	for(int i = 302; i < terrain_y_size; i+=5){
		pos = i;
		cercas.push_back( ModelRepository::get_instance()->get_model_instance("cerca") );
		cercas.back()->reparent_to(Simdunas::get_window()->get_render());
        cercas.back()->set_pos(0.5, pos, 0);
		cercas.back()->set_scale(0.05);
	}

	string casa_model[6] = { "casa1", "casa2", "casa3", "casa2", "casa1", "casa3" };

	int index_casa = 0;
	double distancia = 11.5;
	for (double pos = 10.5; pos <= 130.0; pos += distancia) {
		casas.push_back( ModelRepository::get_instance()->get_model_instance( casa_model[index_casa] ) );
		casas.back()->reparent_to(Simdunas::get_window()->get_render());
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
		casas.back()->reparent_to(Simdunas::get_window()->get_render());
        casas.back()->set_x(terrain_x_size);
        casas.back()->set_y(terrain_y_size - pos);
		casas.back()->set_scale(0.05);
	}


}

/*! Carrega o rio*/
void Terrain::load_water(){

	water_maker = new CardMaker("water_maker");
	water_maker->set_frame( 0, 120, 0, 120 );
	water = Simdunas::get_window()->get_render().attach_new_node(water_maker->generate());
	water.set_hpr(0,-90,0);
	water.set_pos(0, 0, 1);
	water.set_transparency(TransparencyAttrib::M_alpha);
	//buffer = Simdunas::get_window()->get_graphics_window()->make_texture_buffer("waterBuffer", 512, 512);
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
		_setores.at(cont)->remove_tocas();
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


LPoint3f Terrain::get_random_point(){
	int x = rand() % get_x_size();
	int y = rand() % get_y_size();
	int z = get_elevation(x, y);

	return LPoint3f(x, y, z);
}

