/*
 * achievementsWindow.cxx
 *
 *  Created on: Dec 13, 2011
 *      Author: jonatas
 */

#include "achievementsWindow.h"
#include "fontPool.h"
#include "imageRepository.h"

// TODO colocar os hints nas estrelas
// TODO colocar os labels de andamento
// TODO Colocar os outros achievements
AchievementsWindow::AchievementsWindow(NodePath parent, float width, float height, string title) : Window(parent, width, height, title) {
	// Achievement: Senhor mordida perfeita
	lb_senhor_mordida = new TextNode("lb_senhor_mordida");
	lb_senhor_mordida->set_text("- Senhor mordida perfeita");
	//lb_senhor_mordida->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_senhor_mordida = np_frame.attach_new_node(lb_senhor_mordida);
	np_lb_senhor_mordida.set_scale(0.05);
	np_lb_senhor_mordida.set_pos(0.1, 0, 0.85);
	np_lb_senhor_mordida.set_color(0, 0, 0, 1);
	float text_width = lb_senhor_mordida->get_width();
	float text_height = lb_senhor_mordida->get_height();

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

	hint_senhor_mordida_atual = new Hint(np_frame, np_lb_senhor_mordida, text_width, text_height, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
	hint_senhor_mordida_1 = new Hint(np_frame, img_senhor_mordida_whitestar_1, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
	hint_senhor_mordida_2 = new Hint(np_frame, img_senhor_mordida_whitestar_2, "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
	hint_senhor_mordida_3 = new Hint(np_frame, img_senhor_mordida_whitestar_3, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");

	lb_senhor_mordida_xnum = new TextNode("lb_senhor_mordida_xnum");
	lb_senhor_mordida_xnum->set_text("+ 0");
	lb_senhor_mordida_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_senhor_mordida_xnum = np_frame.attach_new_node(lb_senhor_mordida_xnum);
	np_lb_senhor_mordida_xnum.set_scale(0.06);
	np_lb_senhor_mordida_xnum.set_pos(1.05, 0, 0.83);
	np_lb_senhor_mordida_xnum.set_color(0, 0, 0, 1);

	// Achievement: O bom de boca
	lb_bom_de_boca = new TextNode("lb_bom_de_boca");
	lb_bom_de_boca->set_text("- O bom de boca");
	//lb_bom_de_boca->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca = np_frame.attach_new_node(lb_bom_de_boca);
	np_lb_bom_de_boca.set_scale(0.05);
	np_lb_bom_de_boca.set_pos(0.1, 0, 0.75);
	np_lb_bom_de_boca.set_color(0, 0, 0, 1);
	text_width = lb_bom_de_boca->get_width();
	text_height = lb_bom_de_boca->get_height();
	hint_bom_de_boca_1 = new Hint(np_frame, np_lb_bom_de_boca, text_width, text_height, "hint_bom_de_boca", "Coma um alimento qualquer.");

	img_bom_de_boca_whitestar_1 = ImageRepository::get_instance()->get_image("white_star");
	img_bom_de_boca_whitestar_1.reparent_to(np_frame);
	img_bom_de_boca_whitestar_1.set_scale(0.003);
	img_bom_de_boca_whitestar_1.set_pos(0.8, 0, 0.76);

	img_bom_de_boca_yellowstar_1 = ImageRepository::get_instance()->get_image("yellow_star");
	img_bom_de_boca_yellowstar_1.reparent_to(np_frame);
	img_bom_de_boca_yellowstar_1.set_scale(0.003);
	img_bom_de_boca_yellowstar_1.set_pos(0.8, 0, 0.76);
	img_bom_de_boca_yellowstar_1.hide();

	img_bom_de_boca_whitestar_2 = ImageRepository::get_instance()->get_image("white_star");
	img_bom_de_boca_whitestar_2.reparent_to(np_frame);
	img_bom_de_boca_whitestar_2.set_scale(0.003);
	img_bom_de_boca_whitestar_2.set_pos(0.9, 0, 0.76);

	img_bom_de_boca_yellowstar_2 = ImageRepository::get_instance()->get_image("yellow_star");
	img_bom_de_boca_yellowstar_2.reparent_to(np_frame);
	img_bom_de_boca_yellowstar_2.set_scale(0.003);
	img_bom_de_boca_yellowstar_2.set_pos(0.9, 0, 0.76);
	img_bom_de_boca_yellowstar_2.hide();

	img_bom_de_boca_whitestar_3 = ImageRepository::get_instance()->get_image("white_star");
	img_bom_de_boca_whitestar_3.reparent_to(np_frame);
	img_bom_de_boca_whitestar_3.set_scale(0.003);
	img_bom_de_boca_whitestar_3.set_pos(1, 0, 0.76);

	img_bom_de_boca_yellowstar_3 = ImageRepository::get_instance()->get_image("yellow_star");
	img_bom_de_boca_yellowstar_3.reparent_to(np_frame);
	img_bom_de_boca_yellowstar_3.set_scale(0.003);
	img_bom_de_boca_yellowstar_3.set_pos(1, 0, 0.76);
	img_bom_de_boca_yellowstar_3.hide();

	lb_bom_de_boca_xnum = new TextNode("lb_bom_de_boca_xnum");
	lb_bom_de_boca_xnum->set_text("+ 0");
	lb_bom_de_boca_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca_xnum = np_frame.attach_new_node(lb_bom_de_boca_xnum);
	np_lb_bom_de_boca_xnum.set_scale(0.06);
	np_lb_bom_de_boca_xnum.set_pos(1.05, 0, 0.73);
	np_lb_bom_de_boca_xnum.set_color(0, 0, 0, 1);
}

AchievementsWindow::~AchievementsWindow() {}
