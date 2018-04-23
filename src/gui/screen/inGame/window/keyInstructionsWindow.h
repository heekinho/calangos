/*
 * keyInstructionsWindow.h
 *
 *  Created on: Nov 18, 2013
 *      Author: eduardo
 */

#ifndef KEYINSTRUCTIONSWINDOW_H_
#define KEYINSTRUCTIONSWINDOW_H_

#include "window.h"

//#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(KeyInstructionsWindow))(KeyInstructionsWindow*)d)->mn(); }

class KeyInstructionsWindow : public Window {
public:
	//KeyInstructionsWindow(NodePath parent, PT(ScreenManager) manager, float width = 2, float height = 1, string title = "frame", float pos_x = -0.8, float pos_y = -0.8);
	KeyInstructionsWindow(NodePath parent, float width = 2, float height = 1, string title = "frame", float pos_x = -0.8, float pos_y = -0.8);
	virtual ~KeyInstructionsWindow();

	void load(NodePath parent);
	void hide();

private:

	NodePath img_teclas;
	NodePath np_lb_teclas;
	PT(TextNode) lb_teclas;

};

//#undef ACTION

#endif /* KEYINSTRUCTIONSWINDOW_H_ */
