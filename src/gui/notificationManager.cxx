/*
 * NotificationManager.cxx
 *
 *  Created on: May 14, 2012
 *      Author: jonatas
 */

#include "notificationManager.h"
#include "simdunas.h"
#include "timeControl.h"
#include "cLerpNodePathInterval.h"

deque<NodePath> NotificationManager::notifications;

NotificationManager::NotificationManager() {

}

NotificationManager::~NotificationManager() {}

void NotificationManager::show_notification(string message) {
	PT(TextNode) text = new TextNode("text");
	text->set_text(message);
	text->set_shadow(0.06, 0.06);
	text->set_shadow_color(0, 0, 0, 1);

	//float text_width = text->get_width();
	//float text_height = text->get_height();
	//text->set_card_actual(-0.3, text_width + 0.35, -(text_height / 2 - 0.14), text_height - 0.14);
	//text->set_card_color(0, 0, 0, 0);

	//text->set_frame_actual(-0.3, text_width + 0.35, -(text_height / 2 - 0.14), text_height - 0.14);
	//text->set_frame_color(0, 0, 0, 0);

	NodePath np_text = aspect2d.attach_new_node(text);
	np_text.set_scale(0.05);
	np_text.set_color_scale(1, 1, 1, 0, 0);

	fadein(np_text);
	TimeControl::get_instance()->notify("delay_fadeout_notification", fadeout, NULL, 3);

	float half_text_size = text->get_width() * np_text.get_sx() / 2;
	np_text.set_pos(-half_text_size, 0, -0.7);

	for (unsigned int i = 0; i < notifications.size(); i++) {
		notifications.at(i).set_z(notifications.at(i).get_z() + 0.1);
	}

	notifications.push_back(np_text);
	TimeControl::get_instance()->notify("delay_hide_notification", delay_hide_notification, NULL, 4);
}

AsyncTask::DoneStatus NotificationManager::delay_hide_notification(GenericAsyncTask* task, void* data) {
	notifications.front().remove_node();
	notifications.pop_front();
	return AsyncTask::DS_done;
}

void NotificationManager::fadein(NodePath np) {
	PT(CLerpNodePathInterval) fade_interval = new CLerpNodePathInterval("fadein notif", 1, CLerpNodePathInterval::BT_no_blend, true, false, np, NodePath());
	fade_interval->set_end_color_scale(LVecBase4f(1, 1, 1, 1));
	fade_interval->start();
}

AsyncTask::DoneStatus NotificationManager::fadeout(GenericAsyncTask* task, void* data) {
	NodePath np = notifications.front();
	PT(CLerpNodePathInterval) fade_interval = new CLerpNodePathInterval("fadeout notif", 1, CLerpNodePathInterval::BT_no_blend, true, false, np, NodePath());
	fade_interval->set_end_color_scale(LVecBase4f(1, 1, 1, 0));
	fade_interval->start();
	return AsyncTask::DS_done;
}
