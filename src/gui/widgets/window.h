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
#include "button.h"
#include "simdunas.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(Window))(Window*)d)->mn(); }

class Window : public ReferenceCount {
public:
	Window(NodePath parent, float width = 2, float height = 1, string name = "frame", float pos_x = -0.8, float pos_y = -0.8);
	virtual ~Window();

	NodePath get_np_frame();
	NodePath get_np_header_frame();
	string get_header();
	void set_header(string text);
	float get_width();
	void set_width(float width);
	float get_height();
	void set_height(float height);
	float get_pos_x();
	void set_pos_x(float x);
	float get_pos_y();
	void set_pos_y(float y);
	void default_button_config(PT(Button) button, NodePath &np,
			const string &text, LVecBase3f pos, EventCallbackFunction *action);

protected:
	float width;
	float height;
	PT(PGVirtualFrame) frame;
	NodePath np_frame;
	PT(PGVirtualFrame) header_frame;
	NodePath np_header_frame;
	PT(TextNode) header;
	NodePath np_header;
	PT(Button) btn_close;		NodePath np_btn_close;		ACTION(close_action);
};

#undef ACTION

#endif /* WINDOW_H */
