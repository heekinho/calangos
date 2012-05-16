/*
 * debugTools.cxx
 * Created on: 15/05/2012
 * Author: heekinho
 */

#include "debugTools.h"

#include "simdunas.h"
#include "lineSegs.h"

DebugTools::DebugTools() {
	// TODO Auto-generated constructor stub
	show_foliage_wireframe = false;


	configure_input();
}

DebugTools::~DebugTools() {
	// TODO Auto-generated destructor stub
}

/*! Configura os controles de debug. Recebe input e encaminha para
 *  o evento apropriado */
void DebugTools::configure_input(){
	Simdunas::get_framework()->define_key("v", "Foliage Wireframe", toggle_foliage_wireframe, this);
}


/*! Monta um wireframe customizado para o terreno do jogo. */
NodePath DebugTools::draw_custom_terrain_wireframe(){
	PT(Terrain) terrain = Terrain::get_default_terrain();

	LineSegs ls = LineSegs("Custom Terrain Wire");
	ls.set_color(0, 1, 0, 1);

	int step_x = 512, step_y = 512;

	for(int i = 0; i < step_x; i++){
		for(int j = 0; j < step_y; j++){
			ls.draw_to(i, j, terrain->get_elevation(i, j) + 0.001);
		}
	}
	return ls.create();
}


/*! Desenha um circulo indicador do tamanho especificado. Tal círculo
 *  segue a inclinação do terreno. */
NodePath DebugTools::draw_indicator(int steps, float radius){
	PT(Terrain) terrain = Terrain::get_default_terrain();

	LineSegs ls = LineSegs("indicator");
	ls.set_color(0, 1, 0, 1);

	float step = 360.0 / steps;

	for(int i = 0; i < steps+1; i++){
		float x = radius * sin(deg_2_rad(step*i));
		float y = radius * cos(deg_2_rad(step*i));
		ls.draw_to(x, y, terrain->get_elevation(x, y) + 0.001);
	}

	return NodePath(ls.create());
}

/*! Recebe o evento e encaminha para toggle_foliage_wireframe() */
void DebugTools::toggle_foliage_wireframe(const Event*, void *data) {
	((DebugTools*) data)->toggle_foliage_wireframe();
}

/*! Funciona como forma de debugar a folhagem. Alterna o wireframe das folhagens */
void DebugTools::toggle_foliage_wireframe(){
	PT(Foliage) foliage = World::get_world()->get_terrain()->get_foliage();
	if(foliage){
		foliage->set_wireframe((show_foliage_wireframe = !show_foliage_wireframe));
	}
}