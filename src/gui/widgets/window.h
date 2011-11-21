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

private:
	PT(PGVirtualFrame) frame;
	NodePath frame_np;
};

#endif /* WINDOW_H */
