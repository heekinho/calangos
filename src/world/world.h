#ifndef WORLD_H
#define WORLD_H

//#include "terrain.h"
#include "pandaFramework.h"
#include "referenceCount.h"

#include "sky.h"

class Terrain;
//class Sky;

class World:  public ReferenceCount {
public:
	World();
	
	static PT(World) get_world();
	static void unload_world();

	static void load_enviroment();
	static void unload_enviroment();

	PT(Terrain) get_terrain();
	PT(Sky) get_sky();

private:
    static PT(World) _world;

    PT(Sky) _sky;
};

#endif
