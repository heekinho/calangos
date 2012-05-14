/*
 * NotificationManager.cxx
 *
 *  Created on: May 14, 2012
 *      Author: jonatas
 */

#include "notificationManager.h"
#include "simdunas.h"
#include "timeControl.h"

deque<NodePath> NotificationManager::notifications;

NotificationManager::NotificationManager() {

}

NotificationManager::~NotificationManager() {}

void NotificationManager::show_notification(string message) {
	PT(TextNode) text = new TextNode("text");
	text->set_text(message);

	float text_width = text->get_width();
	float text_height = text->get_height();
	text->set_card_actual(-0.3, text_width + 0.35, -(text_height / 2 - 0.14), text_height - 0.14);
	text->set_card_color(1, 1, 1, 1);

	text->set_frame_actual(-0.3, text_width + 0.35, -(text_height / 2 - 0.14), text_height - 0.14);
	text->set_frame_color(0, 0, 0, 1);

	NodePath np_text = aspect2d.attach_new_node(text);
	np_text.set_scale(0.04);
	np_text.set_color(0.0, 0.0, 0.0, 1,0);

	float half_text_size = text->get_width() * np_text.get_sx() / 2;
	np_text.set_pos(-half_text_size, 0, -0.7);

	notifications.push_back(np_text);
	TimeControl::get_instance()->notify("delay_hide_notification", delay_hide_notification, NULL, 2);
}

AsyncTask::DoneStatus NotificationManager::delay_hide_notification(GenericAsyncTask* task, void* data) {
	notifications.front().remove_node();
	notifications.pop_front();
}
