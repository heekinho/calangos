/*
 * NotificationManager.h
 *
 *  Created on: May 14, 2012
 *      Author: jonatas
 */

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "pandaFramework.h"

class NotificationManager {
public:
	NotificationManager();
	virtual ~NotificationManager();

	static void show_notification(string message);
	static AsyncTask::DoneStatus delay_hide_notification(GenericAsyncTask* task, void* data);

private:
	static deque<NodePath> notifications;

};

#endif /* NOTIFICATIONMANAGER_H */
