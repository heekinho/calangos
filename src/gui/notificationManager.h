/*
 * NotificationManager.h
 *
 *  Created on: May 14, 2012
 *      Author: jonatas
 */

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "pandaFramework.h"
//#include "screenManager.h"
//#include "screen.h"
//#include "button.h"
#include "window.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(NotificationManager))(NotificationManager*)d)->mn(); }

//class NotificationManager : public Screen {
class NotificationManager : public ReferenceCount {
public:
	//NotificationManager(PT(ScreenManager) manager);
	virtual ~NotificationManager();

	void show_notification(string message);
	//void show_notification(string message);
	static PT(NotificationManager) get_instance(){
		if(!instance) {
			instance = new NotificationManager();
		}
		return instance;
	}

private:
	NotificationManager();
	static AsyncTask::DoneStatus delay_hide_notification(GenericAsyncTask* task, void* data);
	static void fadein(NodePath np);
	static AsyncTask::DoneStatus fadeout(GenericAsyncTask* task, void* data);

	static deque<NodePath> notifications;
	static PT(TextNode) last_achievement;
	//static NodePath np_last_achievement;

	PT(Window) wnd_realizacoes;
	PT(Button) button;
	NodePath np_button;
//	static PT(Button) btn_realizacoes;
//	static NodePath np_btn_realizacoes;
	ACTION(show_achievements_window);

	static PT(NotificationManager) instance;
	PT(TextFont) default_hud_font;
};

#undef ACTION

#endif /* NOTIFICATIONMANAGER_H */
