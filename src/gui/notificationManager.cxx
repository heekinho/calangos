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
#include "mouseButton.h"
#include "button.h"
#include "achievementsWindow.h"
//#include "guiManager.h"
//#include "fontPool.h"

deque<NodePath> NotificationManager::notifications;
PT(TextNode) NotificationManager::last_achievement;
PT(NotificationManager) NotificationManager::instance;

//NodePath NotificationManager::np_last_achievement;
//PT(Window) NotificationManager::wnd_realizacoes;
//PT(Button) NotificationManager::btn_realizacoes;
//NodePath NotificationManager::np_btn_realizacoes;

//NotificationManager::NotificationManager(PT(ScreenManager) manager) : Screen(manager)  {
//	//cout << "\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PASSOU PELO CONSTRUTOR ";
//	//hide();
//}

NotificationManager::NotificationManager() {
	default_hud_font = FontPool::load_font("models/gui/fonts/suplexcomic-large");
	button = new Button("notification-button", " ", default_hud_font, 0.075);
}

NotificationManager::~NotificationManager() {
}

void NotificationManager::show_notification(string message) {
	PT(TextNode) text = new TextNode("text");
	text->set_text(message);
	text->set_shadow(0.06, 0.06);
	text->set_shadow_color(0, 0, 0, 1);

	if (last_achievement == NULL) {
		last_achievement = new TextNode("last_achievement");
		last_achievement->set_shadow(0.06, 0.06);
		last_achievement->set_shadow_color(0, 0, 0, 1);
	}

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
	//np_text.set_pos(-half_text_size, 0, -0.7);
	np_text.set_pos(-half_text_size, 0, 0.03);

	for (unsigned int i = 0; i < notifications.size(); i++) {
		notifications.at(i).set_z(notifications.at(i).get_z() + 0.1);
	}

	notifications.push_back(np_text);
	TimeControl::get_instance()->notify("delay_hide_notification", delay_hide_notification, NULL, 4);

	// texto fixo no canto superior esquerdo da tela
//	NodePath np_text2 = aspect2d.attach_new_node(text);
//	np_text2.set_scale(0.05);
//	np_text2.set_color_scale(1, 1, 1, 0, 0);
//	fadein(np_text2);
//	np_text2.set_pos(-0.5, 0, -0.5); // setar posição
	//notify();
	//load_m();
	//NotificationManager::load_m();

//	last_achievement->set_text(message + ". \nPressione Esc para ver as realizações já alcançadas.");
//	NodePath np_last_achievement = aspect2d.attach_new_node(last_achievement);
//	np_last_achievement.set_scale(0.05);
//	np_last_achievement.set_color_scale(1, 1, 1, 0, 0);
//	np_last_achievement.set_pos(-1.7, 0, 0.9);
//
//	fadein(np_last_achievement);

//	button->get_te
	if(!np_button.is_empty()) np_button.remove_node();
	button = new Button("notification-button", message, default_hud_font, 0.075);
	np_button = aspect2d.attach_new_node(button);
	float half_button_size = button->get_text_width() * np_button.get_sx() / 2;
	np_button.set_pos(-half_button_size, 0, 0.9);

	string event_name = button->get_click_event(MouseButton::one());
	event_handler->add_hook(event_name, show_achievements_window, this);

	//default_button_config(btn_realizacoes, np_btn_realizacoes, message, LVecBase3f(-0.5, 0, -0.5), show_achievements_window);
}

void NotificationManager::show_achievements_window() {
	wnd_realizacoes = new AchievementsWindow(aspect2d, 1.5, 1.1, "Realizações", -0.8, -0.8);
	wnd_realizacoes->set_pos_y(0);
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

//void NotificationManager::show_achievements_window() {
//	wnd_realizacoes = new AchievementsWindow(get_root(), 1.5, 1.1, "Realizações", -0.8, -0.8);
//	wnd_realizacoes->set_pos_y(0);
//}
//
