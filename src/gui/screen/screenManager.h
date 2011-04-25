/*
 *  screenManager.h
 *  Created on: 19/02/2011
 *  Author: heekinho
 */

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "pandaFramework.h"
#include "textFont.h"
//#include <map>

#include "simdunas.h"
#include "eventHandler.h"
#include "eventQueue.h"
#include "videoManager.h"

class Screen;

class ScreenManager : public ReferenceCount {
public:
	ScreenManager();
	virtual ~ScreenManager();

	/*! Factory Method */
	virtual void create_menus() = 0;

	virtual void open_screen(PT(Screen) screen);
	virtual void close_screen(PT(Screen) screen);
	virtual PT(Screen) get_active_screen();

	virtual PT(TextFont) get_default_font() = 0;

	/*! Métodos foram delegados aqui para maior flexibilidade nas possíveis
	 *  mudanças futuras */
	EventHandler* get_event_handler();
	EventQueue* get_event_queue();

	PT(VideoManager) get_video_manager();

	void play_video(string path);
	static void stop_video(const Event*, void* data);
	bool is_playing_video();
protected:
	void set_active_screen(PT(Screen) screen);

	PT(Screen) active_screen;
	PT(VideoManager) video_manager;

	//typedef map<string, PT(Screen)>::iterator ScreenIterator;
	//map<string, PT(Screen)> screens;
};

#endif
