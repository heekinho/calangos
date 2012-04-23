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
AchievementsWindow::AchievementsWindow(NodePath parent, float width, float height, string title, float pos_x, float pos_y) : Window(parent, width, height, title, pos_x, pos_y) {
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

	string white = "white_star";
	string yellow = "yellow_star";

	int lvl_senhor_mordida = player->get_achievements()->get_lvl_senhor_mordida();
	switch (lvl_senhor_mordida) {
		case 0:
			create_senhor_mordida_stars(white, white, white);
			hint_senhor_mordida_atual = new Hint(np_frame, np_lb_senhor_mordida, text_width, text_height, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
			break;
		case 1:
			create_senhor_mordida_stars(yellow, white, white);
			hint_senhor_mordida_atual = new Hint(np_frame, np_lb_senhor_mordida, text_width, text_height, "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
			break;
		case 2:
			create_senhor_mordida_stars(yellow, yellow, white);
			hint_senhor_mordida_atual = new Hint(np_frame, np_lb_senhor_mordida, text_width, text_height, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");
			break;
		default:
			create_senhor_mordida_stars(yellow, yellow, yellow);
			hint_senhor_mordida_atual = new Hint(np_frame, np_lb_senhor_mordida, text_width, text_height, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");
	}

	hint_senhor_mordida_1 = new Hint(np_frame, img_senhor_mordida_star_1, "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
	hint_senhor_mordida_2 = new Hint(np_frame, img_senhor_mordida_star_2, "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
	hint_senhor_mordida_3 = new Hint(np_frame, img_senhor_mordida_star_3, "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");

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
	// FIM DO ACHIEVEMENT

	// ACHIEVEMENT: O bom de boca
	lb_bom_de_boca = new TextNode("lb_bom_de_boca");
	lb_bom_de_boca->set_text("- O bom de boca");
	//lb_bom_de_boca->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca = np_frame.attach_new_node(lb_bom_de_boca);
	np_lb_bom_de_boca.set_scale(0.05);
	np_lb_bom_de_boca.set_pos(0.06, 0, 0.75);
	np_lb_bom_de_boca.set_color(0, 0, 0, 1);
	text_width = lb_bom_de_boca->get_width();
	text_height = lb_bom_de_boca->get_height();

	int lvl_bom_de_boca = player->get_achievements()->get_lvl_bom_de_boca();
	switch (lvl_bom_de_boca) {
		case 0:
			create_bom_de_boca_stars(white, white, white);
			hint_bom_de_boca_atual = new Hint(np_frame, np_lb_bom_de_boca, text_width, text_height, "hint_bom_de_boca", "Coma 4 espécies diferentes de insetos ou plantas.");
			break;
		case 1:
			create_bom_de_boca_stars(yellow, white, white);
			hint_bom_de_boca_atual = new Hint(np_frame, np_lb_bom_de_boca, text_width, text_height, "hint_bom_de_boca", "Coma mais 5 espécies diferentes de insetos ou plantas.");
			break;
		case 2:
			create_bom_de_boca_stars(yellow, yellow, white);
			hint_bom_de_boca_atual = new Hint(np_frame, np_lb_bom_de_boca, text_width, text_height, "hint_bom_de_boca", "Coma mais 5 espécies diferentes de insetos ou plantas.");
			break;
		default:
			create_bom_de_boca_stars(yellow, yellow, yellow);
			hint_bom_de_boca_atual = new Hint(np_frame, np_lb_bom_de_boca, text_width, text_height, "hint_bom_de_boca", "Coma mais 5 espécies diferentes de insetos ou plantas.");
	}

	hint_bom_de_boca_1 = new Hint(np_frame, img_bom_de_boca_star_1, "hint_bom_de_boca", "Ter comido 4 espécies diferentes de insetos ou plantas");
	hint_bom_de_boca_2 = new Hint(np_frame, img_bom_de_boca_star_2, "hint_bom_de_boca", "Ter comido 9 espécies diferentes de insetos ou plantas");
	hint_bom_de_boca_3 = new Hint(np_frame, img_bom_de_boca_star_3, "hint_bom_de_boca", "Ter comido de todas as 14 espécies diferentes de insetos ou plantas");

	lb_bom_de_boca_xnum = new TextNode("lb_bom_de_boca_xnum");
	stringstream bom_de_boca_adicionais;
	bom_de_boca_adicionais<<((lvl_bom_de_boca - 3) > 0 ? lvl_bom_de_boca - 3 : 0);
	lb_bom_de_boca_xnum->set_text("+ " + bom_de_boca_adicionais.str());
	lb_bom_de_boca_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca_xnum = np_frame.attach_new_node(lb_bom_de_boca_xnum);
	np_lb_bom_de_boca_xnum.set_scale(0.06);
	np_lb_bom_de_boca_xnum.set_pos(1.01, 0, 0.73);
	np_lb_bom_de_boca_xnum.set_color(0, 0, 0, 1);

	stringstream bom_de_boca_andamento;
	lb_bom_de_boca_andamento = new TextNode("lb_bom_de_boca_andamento");
	if (lvl_bom_de_boca == 0) {
		bom_de_boca_andamento<<player->get_achievements()->get_count_species();
		lb_bom_de_boca_andamento->set_text(bom_de_boca_andamento.str() + " / 4");
	}
	else if (lvl_bom_de_boca == 1) {
		bom_de_boca_andamento<<player->get_achievements()->get_count_species();
		lb_bom_de_boca_andamento->set_text(bom_de_boca_andamento.str() + " / 5");
	}
	else {
		bom_de_boca_andamento<<player->get_achievements()->get_count_species();
		lb_bom_de_boca_andamento->set_text(bom_de_boca_andamento.str() + " / 5");
	}
	//lb_bom_de_boca_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_bom_de_boca_andamento = np_frame.attach_new_node(lb_bom_de_boca_andamento);
	np_lb_bom_de_boca_andamento.set_scale(0.05);
	np_lb_bom_de_boca_andamento.set_pos(1.25, 0, 0.75);
	np_lb_bom_de_boca_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT

	// ACHIEVEMENT: Sobrevivente
	lb_sobrevivente = new TextNode("lb_sobrevivente");
	lb_sobrevivente->set_text("- Sobrevivente");
	//lb_sobrevivente->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_sobrevivente = np_frame.attach_new_node(lb_sobrevivente);
	np_lb_sobrevivente.set_scale(0.05);
	np_lb_sobrevivente.set_pos(0.06, 0, 0.65);
	np_lb_sobrevivente.set_color(0, 0, 0, 1);
	text_width = lb_sobrevivente->get_width();
	text_height = lb_sobrevivente->get_height();

	int lvl_sobrevivente = player->get_achievements()->get_lvl_sobrevivente();
	switch (lvl_sobrevivente) {
		case 0:
			create_sobrevivente_stars(white, white, white);
			hint_sobrevivente_atual = new Hint(np_frame, np_lb_sobrevivente, text_width, text_height, "hint_sobrevivente", "Sobreviva por 4 meses.");
			break;
		case 1:
			create_sobrevivente_stars(yellow, white, white);
			hint_sobrevivente_atual = new Hint(np_frame, np_lb_sobrevivente, text_width, text_height, "hint_sobrevivente", "Sobreviva por mais 7 meses.");
			break;
		case 2:
			create_sobrevivente_stars(yellow, yellow, white);
			hint_sobrevivente_atual = new Hint(np_frame, np_lb_sobrevivente, text_width, text_height, "hint_sobrevivente", "Sobreviva por mais 11 meses");
			break;
		default:
			create_sobrevivente_stars(yellow, yellow, yellow);
			hint_sobrevivente_atual = new Hint(np_frame, np_lb_sobrevivente, text_width, text_height, "hint_sobrevivente", "Sobreviva por mais 11 meses");
	}

	hint_sobrevivente_1 = new Hint(np_frame, img_sobrevivente_star_1, "hint_sobrevivente", "Ter sobrevivido por 4 meses");
	hint_sobrevivente_2 = new Hint(np_frame, img_sobrevivente_star_2, "hint_sobrevivente", "Ter sobrevivido por 7 meses");
	hint_sobrevivente_3 = new Hint(np_frame, img_sobrevivente_star_3, "hint_sobrevivente", "Ter sobrevivido por 11 meses");

	lb_sobrevivente_xnum = new TextNode("lb_sobrevivente_xnum");
	stringstream sobrevivente_adicionais;
	sobrevivente_adicionais<<((lvl_sobrevivente - 3) > 0 ? lvl_sobrevivente - 3 : 0);
	lb_sobrevivente_xnum->set_text("+ " + sobrevivente_adicionais.str());
	lb_sobrevivente_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_sobrevivente_xnum = np_frame.attach_new_node(lb_sobrevivente_xnum);
	np_lb_sobrevivente_xnum.set_scale(0.06);
	np_lb_sobrevivente_xnum.set_pos(1.01, 0, 0.63);
	np_lb_sobrevivente_xnum.set_color(0, 0, 0, 1);

	stringstream sobrevivente_andamento;
	lb_sobrevivente_andamento = new TextNode("lb_sobrevivente_andamento");
	if (lvl_sobrevivente == 0) {
		sobrevivente_andamento<<player->get_achievements()->get_count_sobrevivente();
		lb_sobrevivente_andamento->set_text(sobrevivente_andamento.str() + " / 4");
	}
	else if (lvl_sobrevivente == 1) {
		sobrevivente_andamento<<player->get_achievements()->get_count_sobrevivente();
		lb_sobrevivente_andamento->set_text(sobrevivente_andamento.str() + " / 7");
	}
	else {
		sobrevivente_andamento<<player->get_achievements()->get_count_sobrevivente();
		lb_sobrevivente_andamento->set_text(sobrevivente_andamento.str() + " / 11");
	}
	//lb_sobrevivente_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_sobrevivente_andamento = np_frame.attach_new_node(lb_sobrevivente_andamento);
	np_lb_sobrevivente_andamento.set_scale(0.05);
	np_lb_sobrevivente_andamento.set_pos(1.25, 0, 0.65);
	np_lb_sobrevivente_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT

	// ACHIEVEMENT: Reprodutor
	lb_reprodutor = new TextNode("lb_reprodutor");
	lb_reprodutor->set_text("- Reprodutor");
	//lb_reprodutor->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_reprodutor = np_frame.attach_new_node(lb_reprodutor);
	np_lb_reprodutor.set_scale(0.05);
	np_lb_reprodutor.set_pos(0.06, 0, 0.55);
	np_lb_reprodutor.set_color(0, 0, 0, 1);
	text_width = lb_reprodutor->get_width();
	text_height = lb_reprodutor->get_height();

	int lvl_reprodutor = player->get_achievements()->get_lvl_reprodutor();
	switch (lvl_reprodutor) {
		case 0:
			create_reprodutor_stars(white, white, white);
			hint_reprodutor_atual = new Hint(np_frame, np_lb_reprodutor, text_width, text_height, "hint_reprodutor", "Reproduza 3 vezes.");
			break;
		case 1:
			create_reprodutor_stars(yellow, white, white);
			hint_reprodutor_atual = new Hint(np_frame, np_lb_reprodutor, text_width, text_height, "hint_reprodutor", "Reproduza 6 vezes.");
			break;
		case 2:
			create_reprodutor_stars(yellow, yellow, white);
			hint_reprodutor_atual = new Hint(np_frame, np_lb_reprodutor, text_width, text_height, "hint_reprodutor", "Reproduza 10 vezes.");
			break;
		default:
			create_reprodutor_stars(yellow, yellow, yellow);
			hint_reprodutor_atual = new Hint(np_frame, np_lb_reprodutor, text_width, text_height, "hint_reprodutor", "Reproduza 10 vezes.");
	}

	hint_reprodutor_1 = new Hint(np_frame, img_reprodutor_star_1, "hint_reprodutor", "Ter reproduzido 3 vezes");
	hint_reprodutor_2 = new Hint(np_frame, img_reprodutor_star_2, "hint_reprodutor", "Ter reproduzido mais 6 vezes");
	hint_reprodutor_3 = new Hint(np_frame, img_reprodutor_star_3, "hint_reprodutor", "Ter reproduzido mais 10 vezes");

	lb_reprodutor_xnum = new TextNode("lb_reprodutor_xnum");
	stringstream reprodutor_adicionais;
	reprodutor_adicionais<<((lvl_reprodutor - 3) > 0 ? lvl_reprodutor - 3 : 0);
	lb_reprodutor_xnum->set_text("+ " + reprodutor_adicionais.str());
	lb_reprodutor_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_reprodutor_xnum = np_frame.attach_new_node(lb_reprodutor_xnum);
	np_lb_reprodutor_xnum.set_scale(0.06);
	np_lb_reprodutor_xnum.set_pos(1.01, 0, 0.53);
	np_lb_reprodutor_xnum.set_color(0, 0, 0, 1);

	stringstream reprodutor_andamento;
	lb_reprodutor_andamento = new TextNode("lb_reprodutor_andamento");
	if (lvl_reprodutor == 0) {
		reprodutor_andamento<<player->get_achievements()->get_count_reprodutor();
		lb_reprodutor_andamento->set_text(reprodutor_andamento.str() + " / 3");
	}
	else if (lvl_reprodutor == 1) {
		reprodutor_andamento<<player->get_achievements()->get_count_reprodutor();
		lb_reprodutor_andamento->set_text(reprodutor_andamento.str() + " / 6");
	}
	else {
		reprodutor_andamento<<player->get_achievements()->get_count_reprodutor();
		lb_reprodutor_andamento->set_text(reprodutor_andamento.str() + " / 10");
	}
	//lb_reprodutor_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_reprodutor_andamento = np_frame.attach_new_node(lb_reprodutor_andamento);
	np_lb_reprodutor_andamento.set_scale(0.05);
	np_lb_reprodutor_andamento.set_pos(1.25, 0, 0.55);
	np_lb_reprodutor_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT REPRODUTOR

	// ACHIEVEMENT: Temperatura
	lb_temperatura = new TextNode("lb_temperatura");
	lb_temperatura->set_text("- Temperatura");
	//lb_temperatura->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_temperatura = np_frame.attach_new_node(lb_temperatura);
	np_lb_temperatura.set_scale(0.05);
	np_lb_temperatura.set_pos(0.06, 0, 0.45);
	np_lb_temperatura.set_color(0, 0, 0, 1);
	text_width = lb_temperatura->get_width();
	text_height = lb_temperatura->get_height();

	int lvl_temperatura = player->get_achievements()->get_lvl_temperatura();
	switch (lvl_temperatura) {
		case 0:
			create_temperatura_stars(white, white, white);
			hint_temperatura_atual = new Hint(np_frame, np_lb_temperatura, text_width, text_height, "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 45 segundos.");
			break;
		case 1:
			create_temperatura_stars(yellow, white, white);
			hint_temperatura_atual = new Hint(np_frame, np_lb_temperatura, text_width, text_height, "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 60 segundos.");
			break;
		case 2:
			create_temperatura_stars(yellow, yellow, white);
			hint_temperatura_atual = new Hint(np_frame, np_lb_temperatura, text_width, text_height, "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 90 segundos.");
			break;
		default:
			create_temperatura_stars(yellow, yellow, yellow);
			hint_temperatura_atual = new Hint(np_frame, np_lb_temperatura, text_width, text_height, "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 90 segundos.");
	}

	hint_temperatura_1 = new Hint(np_frame, img_temperatura_star_1, "hint_temperatura", "Ter mantido a temperatura entre 35 e 40 graus durante 45 segundos");
	hint_temperatura_2 = new Hint(np_frame, img_temperatura_star_2, "hint_temperatura", "Ter mantido a temperatura entre 35 e 40 graus durante 60 segundos");
	hint_temperatura_3 = new Hint(np_frame, img_temperatura_star_3, "hint_temperatura", "Ter mantido a temperatura entre 35 e 40 graus durante 90 segundos");

	lb_temperatura_xnum = new TextNode("lb_temperatura_xnum");
	stringstream temperatura_adicionais;
	temperatura_adicionais<<((lvl_temperatura - 3) > 0 ? lvl_temperatura - 3 : 0);
	lb_temperatura_xnum->set_text("+ " + temperatura_adicionais.str());
	lb_temperatura_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_temperatura_xnum = np_frame.attach_new_node(lb_temperatura_xnum);
	np_lb_temperatura_xnum.set_scale(0.06);
	np_lb_temperatura_xnum.set_pos(1.01, 0, 0.43);
	np_lb_temperatura_xnum.set_color(0, 0, 0, 1);

	stringstream temperatura_andamento;
	lb_temperatura_andamento = new TextNode("lb_temperatura_andamento");
	if (lvl_temperatura == 0) {
		temperatura_andamento<<player->get_achievements()->get_count_secs_temp();
		lb_temperatura_andamento->set_text(temperatura_andamento.str() + " / 30");
	}
	else if (lvl_temperatura == 1) {
		temperatura_andamento<<player->get_achievements()->get_count_secs_temp();
		lb_temperatura_andamento->set_text(temperatura_andamento.str() + " / 60");
	}
	else {
		temperatura_andamento<<player->get_achievements()->get_count_secs_temp();
		lb_temperatura_andamento->set_text(temperatura_andamento.str() + " / 90");
	}
	//lb_temperatura_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_temperatura_andamento = np_frame.attach_new_node(lb_temperatura_andamento);
	np_lb_temperatura_andamento.set_scale(0.05);
	np_lb_temperatura_andamento.set_pos(1.25, 0, 0.45);
	np_lb_temperatura_andamento.set_color(0, 0, 0, 1);
}

AchievementsWindow::~AchievementsWindow() {}

void AchievementsWindow::create_senhor_mordida_stars(string star1, string star2, string star3) {
	img_senhor_mordida_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_senhor_mordida_star_1.reparent_to(np_frame);
	img_senhor_mordida_star_1.set_scale(0.003);
	img_senhor_mordida_star_1.set_pos(0.76, 0, 0.86);

	img_senhor_mordida_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_senhor_mordida_star_2.reparent_to(np_frame);
	img_senhor_mordida_star_2.set_scale(0.003);
	img_senhor_mordida_star_2.set_pos(0.86, 0, 0.86);

	img_senhor_mordida_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_senhor_mordida_star_3.reparent_to(np_frame);
	img_senhor_mordida_star_3.set_scale(0.003);
	img_senhor_mordida_star_3.set_pos(0.96, 0, 0.86);
}

void AchievementsWindow::create_bom_de_boca_stars(string star1, string star2, string star3) {
	img_bom_de_boca_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_bom_de_boca_star_1.reparent_to(np_frame);
	img_bom_de_boca_star_1.set_scale(0.003);
	img_bom_de_boca_star_1.set_pos(0.76, 0, 0.76);

	img_bom_de_boca_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_bom_de_boca_star_2.reparent_to(np_frame);
	img_bom_de_boca_star_2.set_scale(0.003);
	img_bom_de_boca_star_2.set_pos(0.86, 0, 0.76);

	img_bom_de_boca_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_bom_de_boca_star_3.reparent_to(np_frame);
	img_bom_de_boca_star_3.set_scale(0.003);
	img_bom_de_boca_star_3.set_pos(0.96, 0, 0.76);
}

void AchievementsWindow::create_sobrevivente_stars(string star1, string star2, string star3) {
	img_sobrevivente_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_sobrevivente_star_1.reparent_to(np_frame);
	img_sobrevivente_star_1.set_scale(0.003);
	img_sobrevivente_star_1.set_pos(0.76, 0, 0.66);

	img_sobrevivente_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_sobrevivente_star_2.reparent_to(np_frame);
	img_sobrevivente_star_2.set_scale(0.003);
	img_sobrevivente_star_2.set_pos(0.86, 0, 0.66);

	img_sobrevivente_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_sobrevivente_star_3.reparent_to(np_frame);
	img_sobrevivente_star_3.set_scale(0.003);
	img_sobrevivente_star_3.set_pos(0.96, 0, 0.66);
}

void AchievementsWindow::create_reprodutor_stars(string star1, string star2, string star3) {
	img_reprodutor_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_reprodutor_star_1.reparent_to(np_frame);
	img_reprodutor_star_1.set_scale(0.003);
	img_reprodutor_star_1.set_pos(0.76, 0, 0.56);

	img_reprodutor_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_reprodutor_star_2.reparent_to(np_frame);
	img_reprodutor_star_2.set_scale(0.003);
	img_reprodutor_star_2.set_pos(0.86, 0, 0.56);

	img_reprodutor_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_reprodutor_star_3.reparent_to(np_frame);
	img_reprodutor_star_3.set_scale(0.003);
	img_reprodutor_star_3.set_pos(0.96, 0, 0.56);
}

void AchievementsWindow::create_temperatura_stars(string star1, string star2, string star3) {
	img_temperatura_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_temperatura_star_1.reparent_to(np_frame);
	img_temperatura_star_1.set_scale(0.003);
	img_temperatura_star_1.set_pos(0.76, 0, 0.46);

	img_temperatura_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_temperatura_star_2.reparent_to(np_frame);
	img_temperatura_star_2.set_scale(0.003);
	img_temperatura_star_2.set_pos(0.86, 0, 0.46);

	img_temperatura_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_temperatura_star_3.reparent_to(np_frame);
	img_temperatura_star_3.set_scale(0.003);
	img_temperatura_star_3.set_pos(0.96, 0, 0.46);
}
