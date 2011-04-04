#ifndef SIMDUNAS_H
#define SIMDUNAS_H

#define DEBUG 1

#include <iostream>
#include <string>
using namespace std;

#include "pandaFramework.h"
#include "session.h"
#include "guiLayer.h"

class Session;

class Simdunas {
public:
	static PandaFramework* get_framework();
	static void set_framework(PandaFramework *framework);

	static WindowFramework* get_window();
	static void set_window(WindowFramework* window);

	static EventHandler* get_evt_handler();
	static void set_evt_handler(EventHandler *evt_handler);

	static EventQueue* get_evt_queue();
	static void set_evt_queue(EventQueue *evt_queue);

	static GuiLayer* get_pixel_2d(){ return pixel2d; }
	static void set_pixel_2d(GuiLayer* pixel2d){ Simdunas::pixel2d = pixel2d; }

	static NodePath get_clickable_render_2d();
	static void set_clickable_render_2d(NodePath node);

	static void init_types();

	static bool is_play_clicked();
	static void set_play_clicked(bool flag);

	static void setup_clickable_render_2d();

private:
	static GuiLayer* pixel2d;
	static PandaFramework *framework;
	static WindowFramework *window;
	static NodePath clickable_render_2d;
	static EventQueue *evt_queue;
	static EventHandler *evt_handler;
	static bool play_clicked;
};


/*! Classe com algumas utilidades para acelerar o desenvolvimento.
 * 	Apenas teste, sairá daqui depois */
class Util {
public:
	/* Retorna o ponto dentro do range especificado. (Utiliza min como piso e max como teto) */
	static LPoint2f in_range(LPoint2f point, float min, float max){
		return LPoint2f(in_range(point[0], min, max), in_range(point[1], min, max));
	}

	/* Retorna o valor dentro do range especificado. (Utiliza min como piso e max como teto) */
	static float in_range(float value, float min, float max){
		if(value < min) return min;
		if(value > max) return max;
		return value;
	}
};

#endif
