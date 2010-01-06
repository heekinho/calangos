#ifndef WORLD_H
#define WORLD_H

//#include "terrain.h"
#include "pandaFramework.h"
#include "sky.h"
#include "referenceCount.h"

class Terrain;

class World:  public TypedReferenceCount{
public:
	World();
	
	static PT(World) get_default_world();
	static void unload_default_world();
	static void load_enviroment();
	static void unload_enviroment();

	~World();

	PT(Terrain) get_terrain();
	PT(Sky) get_skybox();
    // Typed Object
   static TypeHandle get_class_type() { return _type_handle; }
   static void init_type() { register_type(_type_handle, "World"); }

private:
	
    static PT(World) world;
    static TypeHandle _type_handle;
};

#endif
