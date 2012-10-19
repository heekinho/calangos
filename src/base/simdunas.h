#ifndef SIMDUNAS_H
#define SIMDUNAS_H

//#define DEBUG 1

#include <iostream>
#include <string>
using namespace std;

#include "pandaFramework.h"
#include "session.h"
#include "guiLayer.h"
#include "fontPool.h"
#include "timeControl.h"


#include "notifyCategoryProxy.h"
NotifyCategoryDeclNoExport(simdunas);

class Session;

class Simdunas {
public:
	static PandaFramework* get_framework();
	static void set_framework(PandaFramework *framework);

	static WindowFramework* get_window();
	static void set_window(WindowFramework* thewindow);

	static GuiLayer* get_pixel_2d(){ return pixel2d; }
	static void set_pixel_2d(GuiLayer* pixel2d){ Simdunas::pixel2d = pixel2d; }

	static NodePath get_clickable_render_2d();
	static void set_clickable_render_2d(NodePath node);

	static void init_types();

	static bool is_play_clicked();
	static void set_play_clicked(bool flag);

	static void setup_clickable_render_2d();

	static TextFont* get_game_font();
	static TextFont* game_font;

private:
	static GuiLayer* pixel2d;
	static PandaFramework *pframework;
	static WindowFramework *pwindow;
	static NodePath clickable_render_2d;
	static bool play_clicked;

};


/*! Alguns shortcuts para facilitar o trabalho e deixar o código mais legível */
#define event_handler EventHandler::get_global_event_handler()
#define event_queue EventQueue::get_global_event_queue()
#define task_mgr AsyncTaskManager::get_global_ptr()

#define window Simdunas::get_window()
#define render window->get_render()
//#define render2d window->get_render_2d()
#define aspect2d window->get_aspect_2d()
#define clickable_render2d Simdunas::get_clickable_render_2d()

#define player Player::get_instance()
#define global_clock ClockObject::get_global_clock()


#include "pandaVersion.h"
#include "luse.h"
#if (PANDA_MAJOR_VERSION >= 1 && PANDA_MINOR_VERSION < 8)
	typedef Colorf LColorf;
	typedef RGBColord LRGBColord;
#endif

//#define camera_np window->get_camera_group()
//#define camera DCAST(Camera, window->get_camera(0))


#endif
