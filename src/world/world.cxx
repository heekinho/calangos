#include "world.h"
#include "vegetal.h"
#include "terrain.h"
#include "sky.h"

#include "modelRepository.h"

PT(World)  World::world=NULL;
TypeHandle World::_type_handle;

World::World(){
	Terrain::create_default_terrain();
    Sky::get_default_sky();
}

PT(World) World::get_default_world(){
	/* Carrega o Mundo: Terreno e Céu */
	if (world == NULL){
		world = new World();
		return world;
	}
	else{
		return world;
	}
}

void World::unload_default_world(){
    Sky::unload_skybox();
    world = NULL;
}


World::~World(){}

void World::load_enviroment(){
	/* Carrega limites do terreno */
	nout << "Carregando Limites do Terreno..." << endl;
	World::get_default_world()->get_terrain()->load_terrain_limit();

	nout << "Carregando Rio..." << endl;
	/* Carrega o rio */
	World::get_default_world()->get_terrain()->load_water();

	/* Carrega vegetais. */
	nout << "Distribuindo Vegetacao..." << endl;
	Vegetal::load_vegetals();
	nout << endl;

	/* Carrega os NPCs. */
	nout << "Distribuindo Animais..." << endl;
	Animal::load_animals();
	nout << endl;

	/* Carrega tocas */
	nout << "Carregando Tocas..." << endl;
	World::get_default_world()->get_terrain()->load_tocas();

}

void World::unload_enviroment(){

	nout << "Descarregando Animais..." << endl;
	Animal::unload_animals();
	nout << endl;

	nout << "Descarregando Vegetação..." << endl;
	Vegetal::unload_vegetals();
	nout << endl;

	nout << "Descarregando Toca e Terreno..." << endl;
	World::get_default_world()->get_terrain()->unload_terrain();
}

/*! Retorna o terreno associado ao mundo */
PT(Terrain) World::get_terrain(){
	return Terrain::create_default_terrain();
}

/*! Retorna o skybox associado ao mundo */
PT(Sky) World::get_skybox(){
	return Sky::get_default_sky();
}



