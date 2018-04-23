/*
 * videosWindow.h
 *
 *  Created on: Mar 3, 2012
 *      Author: jonatas
 */

#ifndef VIDEOSWINDOW_H
#define VIDEOSWINDOW_H

#include "window.h"
#include "screenManager.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(VideosWindow))(VideosWindow*)d)->mn(); }

class VideosWindow : public Window {
public:
	VideosWindow(NodePath parent, PT(ScreenManager) manager, float width = 2, float height = 1, string title = "frame", float pos_x = -0.8, float pos_y = -0.8);
	virtual ~VideosWindow();
	ACTION(lagartos_action);
	ACTION(predadores_action);
	ACTION(presas_action);
	ACTION(clima_action);
	ACTION(habitat_action);

private:
	void open_video(const string &video_path);

	PT(ScreenManager) manager;

	PT(Button) btn_lagartos;		NodePath np_btn_lagartos;		NodePath img_video_lagartos;
	PT(Button) btn_predadores; 		NodePath np_btn_predadores;		NodePath img_video_predadores;
	PT(Button) btn_presas; 			NodePath np_btn_presas;			NodePath img_video_presas;
	PT(Button) btn_clima; 			NodePath np_btn_clima;			NodePath img_video_clima;
	PT(Button) btn_habitat; 		NodePath np_btn_habitat;		NodePath img_video_habitat;
};

#undef ACTION

#endif /* VIDEOSWINDOW_H */
