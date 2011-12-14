/*
 * achievementsWindow.cxx
 *
 *  Created on: Dec 13, 2011
 *      Author: jonatas
 */

#include "achievementsWindow.h"
#include "fontPool.h"
#include "imageRepository.h"

AchievementsWindow::AchievementsWindow(NodePath parent, float width, float height, string title) : Window(parent, width, height, title) {
	lb_senhor_mordida = new TextNode("lb_senhor_mordida");
	lb_senhor_mordida->set_text("- Senhor mordida perfeita");
	//lb_senhor_mordida->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_senhor_mordida = np_frame.attach_new_node(lb_senhor_mordida);
	np_lb_senhor_mordida.set_scale(0.05);
	np_lb_senhor_mordida.set_pos(0.1, 0, 0.85);
	np_lb_senhor_mordida.set_color(0, 0, 0, 1);

	img_senhor_mordida_whitestar_1 = ImageRepository::get_instance()->get_image("white_star");
	img_senhor_mordida_whitestar_1.reparent_to(np_frame);
	img_senhor_mordida_whitestar_1.set_scale(0.003);
	img_senhor_mordida_whitestar_1.set_pos(0.8, 0, 0.86);

	img_senhor_mordida_yellowstar_1 = ImageRepository::get_instance()->get_image("yellow_star");
	img_senhor_mordida_yellowstar_1.reparent_to(np_frame);
	img_senhor_mordida_yellowstar_1.set_scale(0.003);
	img_senhor_mordida_yellowstar_1.set_pos(0.8, 0, 0.86);
	img_senhor_mordida_yellowstar_1.hide();

	img_senhor_mordida_whitestar_2 = ImageRepository::get_instance()->get_image("white_star");
	img_senhor_mordida_whitestar_2.reparent_to(np_frame);
	img_senhor_mordida_whitestar_2.set_scale(0.003);
	img_senhor_mordida_whitestar_2.set_pos(0.9, 0, 0.86);

	img_senhor_mordida_yellowstar_2 = ImageRepository::get_instance()->get_image("yellow_star");
	img_senhor_mordida_yellowstar_2.reparent_to(np_frame);
	img_senhor_mordida_yellowstar_2.set_scale(0.003);
	img_senhor_mordida_yellowstar_2.set_pos(0.9, 0, 0.86);
	img_senhor_mordida_yellowstar_2.hide();

	img_senhor_mordida_whitestar_3 = ImageRepository::get_instance()->get_image("white_star");
	img_senhor_mordida_whitestar_3.reparent_to(np_frame);
	img_senhor_mordida_whitestar_3.set_scale(0.003);
	img_senhor_mordida_whitestar_3.set_pos(1, 0, 0.86);

	img_senhor_mordida_yellowstar_3 = ImageRepository::get_instance()->get_image("yellow_star");
	img_senhor_mordida_yellowstar_3.reparent_to(np_frame);
	img_senhor_mordida_yellowstar_3.set_scale(0.003);
	img_senhor_mordida_yellowstar_3.set_pos(1, 0, 0.86);
	img_senhor_mordida_yellowstar_3.hide();

	lb_senhor_mordida_xnum = new TextNode("lb_senhor_mordida_xnum");
	lb_senhor_mordida_xnum->set_text("+ 0");
	lb_senhor_mordida_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_senhor_mordida_xnum = np_frame.attach_new_node(lb_senhor_mordida_xnum);
	np_lb_senhor_mordida_xnum.set_scale(0.05);
	np_lb_senhor_mordida_xnum.set_pos(1.1, 0, 0.85);
	//np_lb_senhor_mordida_xnum.set_color(0, 0, 0, 1);
}

AchievementsWindow::~AchievementsWindow() {}
