/*
 * guiLayer.h
 * Created on: 26/01/2011
 * Last significant modification: 19/03/2011
 * Author: heekinho
 * */

#ifndef GUILAYER_H
#define GUILAYER_H

#include "windowFramework.h"
#include "nodePath.h"

#include "event.h"
#include "eventHandler.h"

class GuiLayer {
public:
	GuiLayer(WindowFramework* window);
	~GuiLayer();

	/*! Marcadores de Interface. */
	NodePath pbackground;
	NodePath ptl, ptc, ptr;
	NodePath pml, pmc, pmr;
	NodePath pbl, pbc, pbr;

	/* Configurações da janela */
	void adjust_aspect_ratio();
	INLINE int get_width(){ return xsize; }
	INLINE int get_height(){ return ysize; }
	INLINE float get_aspect_ratio(){ return aspect_ratio; }

	/* Eventos de janela */
	void window_event();
	static void window_event(const Event* evt, void* data){
		((GuiLayer*)data)->window_event();
	}

private:
	void configure_layer();
	void add_marker_nodes();
	void configure_marker_nodes();

	int xsize, ysize;
	float aspect_ratio;

public:NodePath pixel2d;
	WindowFramework* window;
};

#endif
