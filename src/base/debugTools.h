/*
 * debugTools.h
 * Created on: 15/05/2012
 * Author: heekinho
 */

#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

//#include "nodePath.h"
//#include "simdunas.h"
//class Player;

#include "nodePath.h"
#include "referenceCount.h"

class DebugTools : public ReferenceCount {
public:
	DebugTools();
	virtual ~DebugTools();

	static void update(const Event*, void *data);
	void update();

	static void update_day(const Event*, void *data);
	void update_day();

	static void update_month(const Event*, void *data);
	void update_month();

	static void special_control(const Event*, void *data);


	void keep_player_healthy();

	NodePath draw_custom_terrain_wireframe();
	NodePath draw_indicator(int steps, float radius);

	void configure_input();

	bool show_foliage_wireframe;
	void toggle_foliage_wireframe();
	static void toggle_foliage_wireframe(const Event*, void *data);
};

#endif /* DEBUGTOOLS_H */
