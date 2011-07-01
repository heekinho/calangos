#ifndef TERRAIN_H
#define TERRAIN_H

#include "pandaFramework.h"
#include "geoMipTerrain.h"
#include "objetoJogo.h"
#include "vegetal.h"
#include "lizard.h"
#include "setor.h"
#include "player.h"
#include "cardMaker.h"
#include "pnmImage.h"
#include "textureStage.h"
#include "texture.h"
#include "referenceCount.h"
#include "typedReferenceCount.h"
#include "foliage.h"

#include "predator.h"
#include "prey.h"

class ShadowCard;
#include "shadowCard.h"

/*! A classe Terrain, é compostas por setores, que são divisões lógicas do mesmo.
 * Classe que conta com o auxilio do GeoMipTerrain para gerar os terrenos a partir de um
 * heightmap.<br>
 * Este terreno também possui vários métodos para lidar com as sombras dos objetos. */
class Terrain : public GeoMipTerrain,  public TypedReferenceCount {
public:
	Terrain(const string &name = "UNDEFINED_TERRAIN");
	static PT(Terrain) get_default_terrain();
	
	~Terrain();

	void add_animal(PT(Animal) animal);
	void add_prey(PT(Prey) prey);
	void add_lizard(PT(Lizard) lizard);
	void add_predator(PT(Predator) predator);
	void add_vegetal(PT(Vegetal) vegetal);
	void add_edible_vegetal(PT(EdibleVegetal) vegetal);

	void remove_all_edible_vegetals();

	// Metodos relacionados aos setores

	void add_setor(PT(Setor) setor);
	void print_sectors();
	PT(Setor) get_setor(int setor);
	PT(Setor) get_setor_from_pos(int x, int y);
	PT(Setor) get_setor_from_pos(LPoint2d pos);

	// Em relacao ao player
	void update_adjacent_sectors(PT(Setor) s);
	vector<PT(Setor)> *get_adjacent_sectors();
	static void update_terrain(const Event*, void *data);
	//void update_setor(ObjetoJogo *object);

	//Métodos auxiliares
	void update_node_z(NodePath node, double offset = 0);
	//TODO: Como sobreescrevi o set_z() lá em Object, podemos limar isso aqui depois.
	void update_object_z(PT(ObjetoJogo) object, double aditional_offset = 0);
	/*@overhide*/ double get_elevation(double x, double y);

	void draw_map();

	bool is_inside(float x, float y);
	bool has_inside(NodePath node);
	bool has_inside(LPoint3f point);
	bool has_inside(LPoint2d point);

	int get_x_size();
	int get_y_size();

	int get_escala();
	void set_escala(int escala);


	// Manipulação com os setores
	static const int MAX_SETORES = 64;
	static const int NUM_SECTORS_X = 8;
	static const int NUM_SECTORS_Y = 8;
	static int SECTOR_WIDTH ;
	static int SECTOR_HEIGHT;

	void load_tocas();
	void load_terrain_limit();
	void load_water();
	void unload_vectors();
	void unload_terrain();
	//void load_object(ObjetoJogo* model, double x, double y, double z, double scale, double h);
    // Typed Object
    static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "Terrain"); }

	PT(ShadowCard) get_shadows(){ return shadows; };
	
        foliage* get_foliage(){return folhagem; };
	LPoint3f get_random_point();

	float get_sampled_elevation(const LPoint2f &reference_point, float radius = 0.1);
	LVector3f get_normal(const LPoint2f &reference_point);
	LVector3f get_sampled_normal(const LPoint2f &reference_point, float radius = 0.1);

	list<PT(Prey)> list_prey;
private:
	static void create_default_terrain();
	void init_sectors();
	vector<PT(Setor)> _setores;
	int escala;
	

	vector<PT(ObjetoJogo)> cercas;
	vector<PT(ObjetoJogo)> casas;

	// Setores vizinhos ao setor que o player se encontra
	vector<PT(Setor)> neighborhood;


	PT(ShadowCard) shadows;
	foliage* folhagem;
	//Water
	NodePath water;
	CardMaker* water_maker;
	PT(GraphicsOutput) buffer;
	PT(Texture) water_tex;
	PT(TextureStage) water_stage;


	 static PT(Terrain) terrain;
	 static TypeHandle _type_handle;
};

#endif
