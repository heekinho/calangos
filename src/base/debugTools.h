/*
 * debugTools.h
 * Created on: 15/05/2012
 * Author: heekinho
 */

#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

#include "simdunas.h"

class DebugTools {
public:
	DebugTools();
	virtual ~DebugTools();

	NodePath draw_custom_terrain_wireframe();
	NodePath draw_indicator(int steps, float radius);

	void configure_input();

	bool show_foliage_wireframe;
	void toggle_foliage_wireframe();
	static void toggle_foliage_wireframe(const Event*, void *data);
};

#endif /* DEBUGTOOLS_H */
