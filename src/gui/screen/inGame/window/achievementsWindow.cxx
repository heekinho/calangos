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

	img_senhor_mordida_star_1 = ImageRepository::get_instance()->get_image("white_star");
	img_senhor_mordida_star_1.reparent_to(np_frame);
	img_senhor_mordida_star_1.set_scale(0.003);
	img_senhor_mordida_star_1.set_pos(0.7, 0, 0.7);
}

AchievementsWindow::~AchievementsWindow() {}
