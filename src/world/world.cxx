#include "world.h"
#include "vegetal.h"
#include "terrain.h"
#include "sky.h"

#include "modelRepository.h"

PT(World)  World::_world = NULL;
TypeHandle World::_type_handle;

/*! Constrói o mundo no qual se passará o jogo. O mundo será composto de
 * um terreno, céu e diversos outros elementos. */
World::World(){
	Terrain::get_default_terrain();
    Sky::get_default_sky();
}

/*! Obtém o mundo (ou constrói um padrão se ainda não existir) */
PT(World) World::get_world(){
	if (!_world) _world = new World();
	return _world;
}

/*! Descarrega o mundo */
void World::unload_world(){
    Sky::unload_skybox();
    _world = NULL;
}

/*! Carrega o ambiente (terreno, rio, vegetação etc) */
void World::load_enviroment(){
	/* Carrega limites do terreno */
	nout << "Carregando Limites do Terreno..." << endl;
	World::get_world()->get_terrain()->load_terrain_limit();

	nout << "Carregando Rio..." << endl;
	/* Carrega o rio */
	World::get_world()->get_terrain()->load_water();

	/* Carrega vegetais. */
	nout << "Distribuindo Vegetacao..." << endl;
	Vegetal::load_vegetals();
	nout << "Juntando vegetação..." << endl;
	Vegetal::flatten_vegetals();
	nout << endl;

	/* Carrega os NPCs. */
	nout << "Distribuindo Animais..." << endl;
	Animal::load_animals();
	nout << endl;

	/* Carrega tocas */
	nout << "Carregando Tocas..." << endl;
	World::get_world()->get_terrain()->load_tocas();

}

/*! Descarrega o ambiente */
void World::unload_enviroment(){
	nout << "Descarregando Animais..." << endl;
	Animal::unload_animals();
	nout << endl;

	nout << "Descarregando Vegetação..." << endl;
	Vegetal::unload_vegetals();
	nout << endl;

	nout << "Descarregando Toca e Terreno..." << endl;
	World::get_world()->get_terrain()->unload_terrain();
}

/*! Retorna o terreno associado ao mundo */
PT(Terrain) World::get_terrain(){
	return Terrain::get_default_terrain();
}

/*! Retorna o skybox associado ao mundo */
PT(Sky) World::get_skybox(){
	return Sky::get_default_sky();
}
