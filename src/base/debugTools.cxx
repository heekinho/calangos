/*
 * debugTools.cxx
 * Created on: 15/05/2012
 * Author: heekinho
 */

#include "debugTools.h"

#include "simdunas.h"
#include "timeControl.h"
#include "lineSegs.h"
#include "player.h"
#include "foliage.h"
#include "world.h"
#include "terrain.h"

DebugTools::DebugTools() {
	simdunas_cat.debug() << "Criando DebugTools" << endl;

	// TODO Auto-generated constructor stub
	show_foliage_wireframe = false;

	/* Cadastra a função de update para o debug */
	event_handler->add_hook(TimeControl::EV_pass_frame, update, this);
	event_handler->add_hook(TimeControl::EV_pass_day, update_day, this);
	event_handler->add_hook(TimeControl::EV_pass_month, update_month, this);

	char* action;

	action = "grow-old";
	Simdunas::get_framework()->define_key("control-o", "EasterEgg - Grow Old", special_control, action);

	action = "kill-player";
	Simdunas::get_framework()->define_key("control-k", "EasterEgg - Kill Player", special_control, action);

	action = "see-graphs";
	Simdunas::get_framework()->define_key("control-g", "See Scene Graphs", special_control, action);

	action = "custom";
	Simdunas::get_framework()->define_key("control-c", "Custom", special_control, action);

	configure_input();
}

DebugTools::~DebugTools() {

}

/*! Configura os controles de debug. Recebe input e encaminha para
 *  o evento apropriado */
void DebugTools::configure_input(){
	Simdunas::get_framework()->define_key("v", "Foliage Wireframe", toggle_foliage_wireframe, this);
}

/*! Recebe o evento a cada frame e encaminha para a função update() */
void DebugTools::update(const Event*, void *data){
	((DebugTools*) data)->update();
}

/*! Realiza as operações desejadas a cada frame */
void DebugTools::update(){
	//keep_player_healthy();
}

/*! Recebe o evento a cada dia e encaminha para a função update() */
void DebugTools::update_day(const Event*, void *data){
	((DebugTools*) data)->update_day();
}

/*! Realiza as operações desejadas a cada dia */
void DebugTools::update_day(){
	//keep_player_healthy();
}


/*! Recebe o evento a cada mês e encaminha para a função update() */
void DebugTools::update_month(const Event*, void *data){
	((DebugTools*) data)->update_month();
}

/*! Realiza as operações desejadas a cada mês */
void DebugTools::update_month(){
	//keep_player_healthy();
}

void DebugTools::special_control(const Event*, void *data){
	char* action = (char*) data;

	if(strcmp(action, "grow-old") == 0){
		event_queue->queue_event(new Event(TimeControl::EV_pass_day));
		event_queue->queue_event(new Event(TimeControl::EV_pass_month));
	}

	if(strcmp(action, "kill-player") == 0){
		player->add_energy(-player->get_energy());
	}

	if(strcmp(action, "custom") == 0){
//		EdibleVegetal::vegetals_food_placeholder.stash();
		Simdunas::get_clickable_render_2d().stash();
	}

	if(strcmp(action, "see-graphs") == 0){
		simdunas_cat.debug() << "======== Begin of Render ======== " << endl;
		window->get_render().ls();
		simdunas_cat.debug() << "======== End of Render ======== " << endl;

		simdunas_cat.debug() << "======== Begin of Render 2d ======== " << endl;
		window->get_render_2d().ls();
		simdunas_cat.debug() << "======== End of Render 2d ======== " << endl;

//		simdunas_cat.debug() << "======== Begin of Render 2d ======== " << endl;
//		window->get_aspect_2d().ls();
//		simdunas_cat.debug() << "======== End of Render 2d ======== " << endl;
	}
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

/*! Espécie de EasterEgg que não deixa o lagarto morrer.
 *  É bom para debugar pois evita que o lagarto morra de mortes indesejadas
 *  em algumas situações de desenvolvimento */
void DebugTools::keep_player_healthy(){
//	player->set_temp_interna(40.0);
//	player->set_energy(100.0);
//	player->set_hydration(100.0);
}
