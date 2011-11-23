/*
 * window.h
 *
 *  Created on: Nov 21, 2011
 *      Author: jonatas
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "pandaFramework.h"
#include "pgVirtualFrame.h"

class Window {
public:
	Window(NodePath parent, float width = 2, float height = 1, string name = "frame");
	virtual ~Window();

	void set_header(string text);
	string get_header();
	void set_width(float width);
	float get_width();
	void set_pos_x(float x);
	float get_pos_x();
	void set_pos_y(float y);
	float get_pos_y();

private:
	PT(PGVirtualFrame) frame;
	NodePath np_frame;
	PT(PGVirtualFrame) header_frame;
	NodePath np_header_frame;
	PT(TextNode) header;
	NodePath np_header;
};

#endif /* WINDOW_H */
