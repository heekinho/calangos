/*
 * achievementsWindow.cxx
 *
 *  Created on: Dec 13, 2011
 *      Author: jonatas
 */

#include "achievementsWindow.h"
#include "fontPool.h"
#include "imageRepository.h"

// TODO colocar os outros achievements
// TODO se essa janela for aberta apenas com o jogo pausado, ajeitar para ter apenas uma variavel de estrela para cada achievement
AchievementsWindow::AchievementsWindow(NodePath parent, float width, float height, string title) : Window(parent, width, height, title) {
	lb_andamento = new TextNode("lb_andamento");
	lb_andamento->set_text("ANDAMENTO");
	//lb_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_andamento = np_frame.attach_new_node(lb_andamento);
	np_lb_andamento.set_scale(0.05);
	np_lb_andamento.set_pos(1.15, 0, 0.92);
	np_lb_andamento.set_color(0, 0, 0, 1);

	// Achievement: Senhor mordida perfeita
	lb_senhor_mordida = new TextNode("lb_senhor_mordida");
	lb_senhor_mordida->set_text("- Senhor mordida perfeita");
	//lb_senhor_mordida->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_senhor_mordida = np_frame.attach_new_node(lb_senhor_mordida);
	np_lb_senhor_mordida.set_scale(0.05);
	np_lb_senhor_mordida.set_pos(0.06, 0, 0.85);
	np_lb_senhor_mordida.set_color(0, 0, 0, 1);
	float text_width = lb_senhor_mordida->get_width();
	float text_height = lb_senhor_mordida->get_height();

	img_senhor_mordida_whitestar_1 = ImageRepository::get_instance()->get_image("white_star");
	img_senhor_mordida_whitestar_1.reparent_to(np_frame);
	img_senhor_mordida_whitestar_1.set_scale(0.003);
	img_senhor_mordida_whitestar_1.set_pos(0.76, 0, 0.86);

	img_senhor_mordida_yellowstar_1 = ImageRepository::get_instance()->get_image("yellow_star");
	img_senhor_mordida_yellowstar_1.reparent_to(np_frame);
	img_senhor_mordida_yellowstar_1.set_scale(0.003);
	img_senhor_mordida_yellowstar_1.set_pos(0.76, 0, 0.86);
	img_senhor_mordida_yellowstar_1.hide();

	img_senhor_mordida_whitestar_2 = ImageRepository::get_instance()->get_image("white_star");
	img_senhor_mordida_whitestar_2.reparent_to(np_frame);
	img_senhor_mordida_whitestar_2.set_scale(0.003);
	img_senhor_mordida_whitestar_2.set_pos(0.86, 0, 0.86);

	img_senhor_mordida_yellowstar_2 = ImageRepository::get_instance()->get_image("yellow_star");
	img_senhor_mordida_yellowstar_2.reparent_to(np_frame);
	img_senhor_mordida_yellowstar_2.set_scale(0.003);
	img_senhor_mordida_yellowstar_2.set_pos(0.86, 0, 0.86);
	img_senhor_mordida_yellowstar_2.hide();

	img_senhor_mordida_whitestar_3 = ImageRepository::get_instance()->get_image("white_star");
	img_senhor_mordida_whitestar_3.reparent_to(np_frame);
	img_senhor_mordida_whitestar_3.set_scale(0.003);
	img_senhor_mordida_whitestar_3.set_pos(0.96, 0, 0.86);

	img_senhor_mordida_yellowstar_3 = ImageRepository::get_instance()->get_image("yellow_star");
	img_senhor_mordida_yellowstar_3.reparent_to(np_frame);
	img_senhor_mordida_yellowstar_3.set_scale(0.003);
	img_senhor_mordida_yellowstar_3.set_pos(0.96, 0, 0.86);
	img_senhor_mordida_yellowstar_3.hide();

	hint_senhor_mordida_atual = new Hint(np_frame, np_lb_senhor_mordida, text_width, text_height, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
	int lvl_senhor_mordida = player->get_achievements()->get_lvl_senhor_mordida();
	if (lvl_senhor_mordida == 0) {
		hint_senhor_mordida_1 = new Hint(np_frame, img_senhor_mordida_whitestar_1, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
		hint_senhor_mordida_2 = new Hint(np_frame, img_senhor_mordida_whitestar_2, "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
		hint_senhor_mordida_3 = new Hint(np_frame, img_senhor_mordida_whitestar_3, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");
	}
	else if (lvl_senhor_mordida == 1) {
		hint_senhor_mordida_1 = new Hint(np_frame, img_senhor_mordida_yellowstar_1, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
		hint_senhor_mordida_2 = new Hint(np_frame, img_senhor_mordida_whitestar_2, "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
		hint_senhor_mordida_3 = new Hint(np_frame, img_senhor_mordida_whitestar_3, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");

		img_senhor_mordida_whitestar_1.hide();
		img_senhor_mordida_yellowstar_1.show();
	}
	else if (lvl_senhor_mordida == 2) {
		hint_senhor_mordida_1 = new Hint(np_frame, img_senhor_mordida_yellowstar_1, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
		hint_senhor_mordida_2 = new Hint(np_frame, img_senhor_mordida_yellowstar_2, "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
		hint_senhor_mordida_3 = new Hint(np_frame, img_senhor_mordida_whitestar_3, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");

		img_senhor_mordida_whitestar_1.hide();
		img_senhor_mordida_whitestar_2.hide();
		img_senhor_mordida_yellowstar_1.show();
		img_senhor_mordida_yellowstar_2.show();
	}
	else {
		hint_senhor_mordida_1 = new Hint(np_frame, img_senhor_mordida_yellowstar_1, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
		hint_senhor_mordida_2 = new Hint(np_frame, img_senhor_mordida_yellowstar_2, "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
		hint_senhor_mordida_3 = new Hint(np_frame, img_senhor_mordida_yellowstar_3, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");

		img_senhor_mordida_whitestar_1.hide();
		img_senhor_mordida_whitestar_2.hide();
		img_senhor_mordida_whitestar_3.hide();
		img_senhor_mordida_yellowstar_1.show();
		img_senhor_mordida_yellowstar_2.show();
		img_senhor_mordida_yellowstar_3.show();
	}

	lb_senhor_mordida_xnum = new TextNode("lb_senhor_mordida_xnum");
	stringstream senhor_mordida_adicionais;
	senhor_mordida_adicionais<<((lvl_senhor_mordida - 3) > 0 ? lvl_senhor_mordida - 3 : 0);
	lb_senhor_mordida_xnum->set_text("+ " + senhor_mordida_adicionais.str());
	lb_senhor_mordida_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_senhor_mordida_xnum = np_frame.attach_new_node(lb_senhor_mordida_xnum);
	np_lb_senhor_mordida_xnum.set_scale(0.06);
	np_lb_senhor_mordida_xnum.set_pos(1.01, 0, 0.83);
	np_lb_senhor_mordida_xnum.set_color(0, 0, 0, 1);

	lb_senhor_mordida_andamento = new TextNode("lb_senhor_mordida_andamento");
	cout<<"test = "<<player->get_achievements()->get_count_bites() + " / 10"<<endl;
	stringstream out;
	if (lvl_senhor_mordida == 0) {
		out<<player->get_achievements()->get_count_bites();
		lb_senhor_mordida_andamento->set_text(out.str() + " / 10");
	}
	else if (lvl_senhor_mordida == 1) {
		out<<player->get_achievements()->get_count_bites();
		lb_senhor_mordida_andamento->set_text(out.str() + " / 25");
	}
	else {
		out<<player->get_achievements()->get_count_bites();
		lb_senhor_mordida_andamento->set_text(out.str() + " / 50");
	}

	//lb_senhor_mordida_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_senhor_mordida_andamento = np_frame.attach_new_node(lb_senhor_mordida_andamento);
	np_lb_senhor_mordida_andamento.set_scale(0.05);
	np_lb_senhor_mordida_andamento.set_pos(1.25, 0, 0.85);
	np_lb_senhor_mordida_andamento.set_color(0, 0, 0, 1);

	// Achievement: O bom de boca
	lb_bom_de_boca = new TextNode("lb_bom_de_boca");
	lb_bom_de_boca->set_text("- O bom de boca");
	//lb_bom_de_boca->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca = np_frame.attach_new_node(lb_bom_de_boca);
	np_lb_bom_de_boca.set_scale(0.05);
	np_lb_bom_de_boca.set_pos(0.06, 0, 0.75);
	np_lb_bom_de_boca.set_color(0, 0, 0, 1);
	text_width = lb_bom_de_boca->get_width();
	text_height = lb_bom_de_boca->get_height();
	hint_bom_de_boca_1 = new Hint(np_frame, np_lb_bom_de_boca, text_width, text_height, "hint_bom_de_boca", "Coma um alimento qualquer.");

	img_bom_de_boca_whitestar_1 = ImageRepository::get_instance()->get_image("white_star");
	img_bom_de_boca_whitestar_1.reparent_to(np_frame);
	img_bom_de_boca_whitestar_1.set_scale(0.003);
	img_bom_de_boca_whitestar_1.set_pos(0.76, 0, 0.76);

	img_bom_de_boca_yellowstar_1 = ImageRepository::get_instance()->get_image("yellow_star");
	img_bom_de_boca_yellowstar_1.reparent_to(np_frame);
	img_bom_de_boca_yellowstar_1.set_scale(0.003);
	img_bom_de_boca_yellowstar_1.set_pos(0.76, 0, 0.76);
	img_bom_de_boca_yellowstar_1.hide();

	img_bom_de_boca_whitestar_2 = ImageRepository::get_instance()->get_image("white_star");
	img_bom_de_boca_whitestar_2.reparent_to(np_frame);
	img_bom_de_boca_whitestar_2.set_scale(0.003);
	img_bom_de_boca_whitestar_2.set_pos(0.86, 0, 0.76);

	img_bom_de_boca_yellowstar_2 = ImageRepository::get_instance()->get_image("yellow_star");
	img_bom_de_boca_yellowstar_2.reparent_to(np_frame);
	img_bom_de_boca_yellowstar_2.set_scale(0.003);
	img_bom_de_boca_yellowstar_2.set_pos(0.86, 0, 0.76);
	img_bom_de_boca_yellowstar_2.hide();

	img_bom_de_boca_whitestar_3 = ImageRepository::get_instance()->get_image("white_star");
	img_bom_de_boca_whitestar_3.reparent_to(np_frame);
	img_bom_de_boca_whitestar_3.set_scale(0.003);
	img_bom_de_boca_whitestar_3.set_pos(0.96, 0, 0.76);

	img_bom_de_boca_yellowstar_3 = ImageRepository::get_instance()->get_image("yellow_star");
	img_bom_de_boca_yellowstar_3.reparent_to(np_frame);
	img_bom_de_boca_yellowstar_3.set_scale(0.003);
	img_bom_de_boca_yellowstar_3.set_pos(0.96, 0, 0.76);
	img_bom_de_boca_yellowstar_3.hide();

	hint_bom_de_boca_atual = new Hint(np_frame, np_lb_bom_de_boca, text_width, text_height, "hint_bom_de_boca", "Coma 10 vezes sem errar a mordida");
	hint_bom_de_boca_1 = new Hint(np_frame, img_bom_de_boca_whitestar_1, "hint_bom_de_boca", "Ter comido um alimento qualquer");
	hint_bom_de_boca_2 = new Hint(np_frame, img_bom_de_boca_whitestar_2, "hint_bom_de_boca", "Ter comido metade dos tipos de alimento");
	hint_bom_de_boca_3 = new Hint(np_frame, img_bom_de_boca_whitestar_3, "hint_bom_de_boca", "Ter comido todos os tipos de alimento");

	lb_bom_de_boca_xnum = new TextNode("lb_bom_de_boca_xnum");
	lb_bom_de_boca_xnum->set_text("+ 0");
	lb_bom_de_boca_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca_xnum = np_frame.attach_new_node(lb_bom_de_boca_xnum);
	np_lb_bom_de_boca_xnum.set_scale(0.06);
	np_lb_bom_de_boca_xnum.set_pos(1.01, 0, 0.73);
	np_lb_bom_de_boca_xnum.set_color(0, 0, 0, 1);

	lb_bom_de_boca_andamento = new TextNode("lb_bom_de_boca_andamento");
	lb_bom_de_boca_andamento->set_text("0 / 0");
	//lb_bom_de_boca_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca_andamento = np_frame.attach_new_node(lb_bom_de_boca_andamento);
	np_lb_bom_de_boca_andamento.set_scale(0.05);
	np_lb_bom_de_boca_andamento.set_pos(1.25, 0, 0.75);
	np_lb_bom_de_boca_andamento.set_color(0, 0, 0, 1);
}

AchievementsWindow::~AchievementsWindow() {}
