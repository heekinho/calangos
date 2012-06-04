#ifndef WORLD_H
#define WORLD_H

//#include "terrain.h"
#include "pandaFramework.h"
#include "sky.h"
#include "referenceCount.h"

class Terrain;

class World:  public ReferenceCount {
public:
	World();
	
	static PT(World) get_world();
	static void unload_world();

	static void load_enviroment();
	static void unload_enviroment();

	PT(Terrain) get_terrain();
	PT(Sky) get_skybox();

private:
    static PT(World) _world;
};

#endif
