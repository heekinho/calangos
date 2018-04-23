#include "world.h"
#include "vegetal.h"
#include "terrain.h"
#include "sky.h"

#include "modelRepository.h"

PT(World)  World::_world = NULL;

/*! Constrói o mundo no qual se passará o jogo. O mundo será composto de
 * um terreno, céu e diversos outros elementos. */
World::World(){
	Terrain::get_default_terrain();

	_sky = new Sky("models/skybox");
}

/*! Obtém o mundo (ou constrói um padrão se ainda não existir) */
PT(World) World::get_world(){
	if (!_world)
		_world = new World();
	return _world;
}

/*! Descarrega o mundo */
void World::unload_world(){
	event_handler->remove_hooks_with(_world->_sky);
	//    delete world->_sky; // Mesmo sendo reference counted (talvez os eventos não o excluam =/)

//    Sky::unload_skybox();
    _world = NULL;
}

/*! Carrega o ambiente (terreno, rio, vegetação etc) */
void World::load_enviroment(){
	/* Carrega limites do terreno */
	simdunas_cat.debug() << "Carregando Limites do Terreno..." << endl;
	World::get_world()->get_terrain()->load_terrain_limit();

	simdunas_cat.debug() << "Carregando Rio..." << endl;
	/* Carrega o rio */
	World::get_world()->get_terrain()->load_water();

	/* Carrega vegetais. */
	simdunas_cat.debug() << "Distribuindo Vegetacao..." << endl;
	Vegetal::load_vegetals();
	simdunas_cat.debug() << "Juntando vegetação..." << endl;
	/* NOTA: Não pode fazer isso pq da mudança de estação */
//	Vegetal::flatten_vegetals();
//	simdunas_cat.debug() << endl;

	/* Carrega os NPCs. */
	simdunas_cat.debug() << "Distribuindo Animais..." << endl;
	Animal::load_animals();
	simdunas_cat.debug() << endl;

	/* Carrega tocas */
	simdunas_cat.debug() << "Carregando Tocas..." << endl;
	World::get_world()->get_terrain()->load_tocas();

}

/*! Descarrega o ambiente */
void World::unload_enviroment(){
	simdunas_cat.debug() << "Descarregando Animais..." << endl;
	Animal::unload_animals();
	simdunas_cat.debug() << endl;

	simdunas_cat.debug() << "Descarregando Vegetação..." << endl;
	Vegetal::unload_vegetals();
	simdunas_cat.debug() << endl;

	simdunas_cat.debug() << "Descarregando Toca e Terreno..." << endl;
	World::get_world()->get_terrain()->unload_terrain();
}

/*! Retorna o terreno associado ao mundo */
PT(Terrain) World::get_terrain(){
	return Terrain::get_default_terrain();
}

/*! Retorna o skybox associado ao mundo */
PT(Sky) World::get_sky(){
	return _sky;
}
