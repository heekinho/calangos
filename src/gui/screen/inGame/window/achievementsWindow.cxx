/*
 * achievementsWindow.cxx
 *
 *  Created on: Dec 13, 2011
 *      Author: jonatas
 */

#include "achievementsWindow.h"
#include "fontPool.h"
#include "imageRepository.h"

/*!
 * Constrói a janela de Achievements. Os parâmetros são simplesmente repassados para a superclasse (Window).
 */
AchievementsWindow::AchievementsWindow(NodePath parent, float width, float height, string title, float pos_x, float pos_y) : Window(parent, width, height, title, pos_x, pos_y) {
	lb_andamento = new TextNode("lb_andamento");
	lb_andamento->set_text("ANDAMENTO");
	//lb_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_andamento = np_frame.attach_new_node(lb_andamento);
	np_lb_andamento.set_scale(0.05);
	np_lb_andamento.set_pos(1.15, 0, 1.02);
	np_lb_andamento.set_color(0, 0, 0, 1);

	// Achievement: Senhor mordida perfeita
	lb_senhor_mordida = new Text("lb_senhor_mordida", "- Senhor mordida perfeita", np_frame, TextNode::get_default_font(), 0.05);
	lb_senhor_mordida->set_pos(0.06, 0, 0.95);

	string white = "white_star";
	string yellow = "yellow_star";

	int lvl_senhor_mordida = player->get_achievements()->get_lvl_senhor_mordida();
	switch (lvl_senhor_mordida) {
		case 0:
			create_senhor_mordida_stars(white, white, white);
			hint_senhor_mordida_atual = new Hint(np_frame, lb_senhor_mordida, lb_senhor_mordida->get_np(), "hint_senhor_mordida", "Coma 10 vezes sem errar a mordida");
			break;
		case 1:
			create_senhor_mordida_stars(yellow, white, white);
			hint_senhor_mordida_atual = new Hint(np_frame, lb_senhor_mordida, lb_senhor_mordida->get_np(), "hint_senhor_mordida", "Coma 25 vezes sem errar a mordida");
			break;
		case 2:
			create_senhor_mordida_stars(yellow, yellow, white);
			hint_senhor_mordida_atual = new Hint(np_frame, lb_senhor_mordida, lb_senhor_mordida->get_np(), "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");
			break;
		default:
			create_senhor_mordida_stars(yellow, yellow, yellow);
			hint_senhor_mordida_atual = new Hint(np_frame, lb_senhor_mordida, lb_senhor_mordida->get_np(), "hint_senhor_mordida", "Coma 50 vezes sem errar a mordida");
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
	np_lb_senhor_mordida_xnum.set_pos(1.01, 0, 0.93);
	np_lb_senhor_mordida_xnum.set_color(0, 0, 0, 1);

	lb_senhor_mordida_andamento = new TextNode("lb_senhor_mordida_andamento");
	simdunas_cat.debug()<<"test = "<<player->get_achievements()->get_count_bites() + " / 10"<<endl;
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
	np_lb_senhor_mordida_andamento.set_pos(1.25, 0, 0.95);
	np_lb_senhor_mordida_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT

	// ACHIEVEMENT: O bom de boca
	lb_bom_de_boca = new Text("lb_bom_de_boca", "- O bom de boca", np_frame, TextNode::get_default_font(), 0.05);
	lb_bom_de_boca->set_pos(0.06, 0, 0.85);

	int lvl_bom_de_boca = player->get_achievements()->get_lvl_bom_de_boca();
	switch (lvl_bom_de_boca) {
		case 0:
			create_bom_de_boca_stars(white, white, white);
			hint_bom_de_boca_atual = new Hint(np_frame, lb_bom_de_boca, lb_bom_de_boca->get_np(), "hint_bom_de_boca", "Coma 4 espécies diferentes de insetos ou plantas.");
			break;
		case 1:
			create_bom_de_boca_stars(yellow, white, white);
			hint_bom_de_boca_atual = new Hint(np_frame, lb_bom_de_boca, lb_bom_de_boca->get_np(), "hint_bom_de_boca", "Coma mais 5 espécies diferentes de insetos ou plantas.");
			break;
		case 2:
			create_bom_de_boca_stars(yellow, yellow, white);
			hint_bom_de_boca_atual = new Hint(np_frame, lb_bom_de_boca, lb_bom_de_boca->get_np(), "hint_bom_de_boca", "Coma mais 5 espécies diferentes de insetos ou plantas.");
			break;
		default:
			create_bom_de_boca_stars(yellow, yellow, yellow);
			hint_bom_de_boca_atual = new Hint(np_frame, lb_bom_de_boca, lb_bom_de_boca->get_np(), "hint_bom_de_boca", "Coma mais 5 espécies diferentes de insetos ou plantas.");
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
	np_lb_bom_de_boca_xnum.set_pos(1.01, 0, 0.83);
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
	np_lb_bom_de_boca_andamento.set_pos(1.25, 0, 0.85);
	np_lb_bom_de_boca_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT

	// ACHIEVEMENT: Sobrevivente
	lb_sobrevivente = new Text("lb_sobrevivente", "- Sobrevivente", np_frame, TextNode::get_default_font(), 0.05);
	lb_sobrevivente->set_pos(0.06, 0, 0.75);

	int lvl_sobrevivente = player->get_achievements()->get_lvl_sobrevivente();
	switch (lvl_sobrevivente) {
		case 0:
			create_sobrevivente_stars(white, white, white);
			hint_sobrevivente_atual = new Hint(np_frame, lb_sobrevivente, lb_sobrevivente->get_np(), "hint_sobrevivente", "Sobreviva por 4 meses.");
			break;
		case 1:
			create_sobrevivente_stars(yellow, white, white);
			hint_sobrevivente_atual = new Hint(np_frame, lb_sobrevivente, lb_sobrevivente->get_np(), "hint_sobrevivente", "Sobreviva por mais 7 meses.");
			break;
		case 2:
			create_sobrevivente_stars(yellow, yellow, white);
			hint_sobrevivente_atual = new Hint(np_frame, lb_sobrevivente, lb_sobrevivente->get_np(), "hint_sobrevivente", "Sobreviva por mais 11 meses");
			break;
		default:
			create_sobrevivente_stars(yellow, yellow, yellow);
			hint_sobrevivente_atual = new Hint(np_frame, lb_sobrevivente, lb_sobrevivente->get_np(), "hint_sobrevivente", "Sobreviva por mais 11 meses");
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
	np_lb_sobrevivente_xnum.set_pos(1.01, 0, 0.73);
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
	np_lb_sobrevivente_andamento.set_pos(1.25, 0, 0.75);
	np_lb_sobrevivente_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT

	// ACHIEVEMENT: Reprodutor
	lb_reprodutor = new Text("lb_reprodutor", "- Reprodutor", np_frame, TextNode::get_default_font(), 0.05);
	lb_reprodutor->set_text("- Reprodutor");
	lb_reprodutor->set_pos(0.06, 0, 0.65);

	int lvl_reprodutor = player->get_achievements()->get_lvl_reprodutor();
	switch (lvl_reprodutor) {
		case 0:
			create_reprodutor_stars(white, white, white);
			hint_reprodutor_atual = new Hint(np_frame, lb_reprodutor, lb_reprodutor->get_np(), "hint_reprodutor", "Reproduza 3 vezes.");
			break;
		case 1:
			create_reprodutor_stars(yellow, white, white);
			hint_reprodutor_atual = new Hint(np_frame, lb_reprodutor, lb_reprodutor->get_np(), "hint_reprodutor", "Reproduza 6 vezes.");
			break;
		case 2:
			create_reprodutor_stars(yellow, yellow, white);
			hint_reprodutor_atual = new Hint(np_frame, lb_reprodutor, lb_reprodutor->get_np(), "hint_reprodutor", "Reproduza 10 vezes.");
			break;
		default:
			create_reprodutor_stars(yellow, yellow, yellow);
			hint_reprodutor_atual = new Hint(np_frame, lb_reprodutor, lb_reprodutor->get_np(), "hint_reprodutor", "Reproduza 10 vezes.");
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
	np_lb_reprodutor_xnum.set_pos(1.01, 0, 0.63);
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
	np_lb_reprodutor_andamento.set_pos(1.25, 0, 0.65);
	np_lb_reprodutor_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT REPRODUTOR

	// ACHIEVEMENT: Temperatura
	lb_temperatura = new Text("lb_temperatura", "- Temperatura", np_frame, TextNode::get_default_font(), 0.05);
	lb_temperatura->set_pos(0.06, 0, 0.55);

	int lvl_temperatura = player->get_achievements()->get_lvl_temperatura();
	switch (lvl_temperatura) {
		case 0:
			create_temperatura_stars(white, white, white);
			hint_temperatura_atual = new Hint(np_frame, lb_temperatura, lb_temperatura->get_np(), "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 45 segundos.");
			break;
		case 1:
			create_temperatura_stars(yellow, white, white);
			hint_temperatura_atual = new Hint(np_frame, lb_temperatura, lb_temperatura->get_np(), "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 60 segundos.");
			break;
		case 2:
			create_temperatura_stars(yellow, yellow, white);
			hint_temperatura_atual = new Hint(np_frame, lb_temperatura, lb_temperatura->get_np(), "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 90 segundos.");
			break;
		default:
			create_temperatura_stars(yellow, yellow, yellow);
			hint_temperatura_atual = new Hint(np_frame, lb_temperatura, lb_temperatura->get_np(), "hint_temperatura", "Mantenha sua temperatura entre 35 e 40 graus durante 90 segundos.");
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
	np_lb_temperatura_xnum.set_pos(1.01, 0, 0.53);
	np_lb_temperatura_xnum.set_color(0, 0, 0, 1);

	stringstream temperatura_andamento;
	lb_temperatura_andamento = new TextNode("lb_temperatura_andamento");
	if (lvl_temperatura == 0) {
		temperatura_andamento<<player->get_achievements()->get_count_secs_temp();
		lb_temperatura_andamento->set_text(temperatura_andamento.str() + " / 45");
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
	np_lb_temperatura_andamento.set_pos(1.25, 0, 0.55);
	np_lb_temperatura_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT TEMPERATURA

	// ACHIEVEMENT: Hidratação
	lb_hidratacao = new Text("lb_hidratacao", "- Hidratação", np_frame, TextNode::get_default_font(), 0.05);
	lb_hidratacao->set_text("- hidratacao");
	lb_hidratacao->set_pos(0.06, 0, 0.45);

	int lvl_hidratacao = player->get_achievements()->get_lvl_hidratacao();
	switch (lvl_hidratacao) {
		case 0:
			create_hidratacao_stars(white, white, white);
			hint_hidratacao_atual = new Hint(np_frame, lb_hidratacao, lb_hidratacao->get_np(), "hint_hidratacao", "Mantenha sua hidratação maior que 70 durante 60 segundos.");
			break;
		case 1:
			create_hidratacao_stars(yellow, white, white);
			hint_hidratacao_atual = new Hint(np_frame, lb_hidratacao, lb_hidratacao->get_np(), "hint_hidratacao", "Mantenha sua hidratação maior que 80 durante 120 segundos.");
			break;
		case 2:
			create_hidratacao_stars(yellow, yellow, white);
			hint_hidratacao_atual = new Hint(np_frame, lb_hidratacao, lb_hidratacao->get_np(), "hint_hidratacao", "Mantenha sua hidratação maior que 90 durante 180 segundos.");
			break;
		default:
			create_hidratacao_stars(yellow, yellow, yellow);
			hint_hidratacao_atual = new Hint(np_frame, lb_hidratacao, lb_hidratacao->get_np(), "hint_hidratacao", "Mantenha sua hidratação maior que 90 durante 180 segundos.");
	}

	hint_hidratacao_1 = new Hint(np_frame, img_hidratacao_star_1, "hint_hidratacao", "Ter mantido a hidratação maior que 70 durante 60 segundos");
	hint_hidratacao_2 = new Hint(np_frame, img_hidratacao_star_2, "hint_hidratacao", "Ter mantido a hidratação maior que 80 durante 120 segundos");
	hint_hidratacao_3 = new Hint(np_frame, img_hidratacao_star_3, "hint_hidratacao", "Ter mantido a hidratação maior que 90 durante 180 segundos");

	lb_hidratacao_xnum = new TextNode("lb_hidratacao_xnum");
	stringstream hidratacao_adicionais;
	hidratacao_adicionais<<((lvl_hidratacao - 3) > 0 ? lvl_hidratacao - 3 : 0);
	lb_hidratacao_xnum->set_text("+ " + hidratacao_adicionais.str());
	lb_hidratacao_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_hidratacao_xnum = np_frame.attach_new_node(lb_hidratacao_xnum);
	np_lb_hidratacao_xnum.set_scale(0.06);
	np_lb_hidratacao_xnum.set_pos(1.01, 0, 0.43);
	np_lb_hidratacao_xnum.set_color(0, 0, 0, 1);

	stringstream hidratacao_andamento;
	lb_hidratacao_andamento = new TextNode("lb_hidratacao_andamento");
	if (lvl_hidratacao == 0) {
		hidratacao_andamento<<player->get_achievements()->get_count_secs_hyd();
		lb_hidratacao_andamento->set_text(hidratacao_andamento.str() + " / 60");
	}
	else if (lvl_hidratacao == 1) {
		hidratacao_andamento<<player->get_achievements()->get_count_secs_hyd();
		lb_hidratacao_andamento->set_text(hidratacao_andamento.str() + " / 120");
	}
	else {
		hidratacao_andamento<<player->get_achievements()->get_count_secs_hyd();
		lb_hidratacao_andamento->set_text(hidratacao_andamento.str() + " / 180");
	}
	//lb_hidratacao_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_hidratacao_andamento = np_frame.attach_new_node(lb_hidratacao_andamento);
	np_lb_hidratacao_andamento.set_scale(0.05);
	np_lb_hidratacao_andamento.set_pos(1.25, 0, 0.45);
	np_lb_hidratacao_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT HIDRATAÇÃO

	// ACHIEVEMENT: Energia
	lb_energia = new Text("lb_energia", "- Energia", np_frame, TextNode::get_default_font(), 0.05);
	lb_energia->set_pos(0.06, 0, 0.35);

	int lvl_energia = player->get_achievements()->get_lvl_energia();
	switch (lvl_energia) {
		case 0:
			create_energia_stars(white, white, white);
			hint_energia_atual = new Hint(np_frame, lb_energia, lb_energia->get_np(), "hint_energia", "Mantenha sua energia maior que 70 durante 60 segundos.");
			break;
		case 1:
			create_energia_stars(yellow, white, white);
			hint_energia_atual = new Hint(np_frame, lb_energia, lb_energia->get_np(), "hint_energia", "Mantenha sua energia maior que 80 durante 120 segundos.");
			break;
		case 2:
			create_energia_stars(yellow, yellow, white);
			hint_energia_atual = new Hint(np_frame, lb_energia, lb_energia->get_np(), "hint_energia", "Mantenha sua energia maior que 90 durante 180 segundos.");
			break;
		default:
			create_energia_stars(yellow, yellow, yellow);
			hint_energia_atual = new Hint(np_frame, lb_energia, lb_energia->get_np(), "hint_energia", "Mantenha sua energia maior que 90 durante 180 segundos.");
	}

	hint_energia_1 = new Hint(np_frame, img_energia_star_1, "hint_energia", "Ter mantido a energia maior que 70 durante 60 segundos");
	hint_energia_2 = new Hint(np_frame, img_energia_star_2, "hint_energia", "Ter mantido a energia maior que 80 durante 120 segundos");
	hint_energia_3 = new Hint(np_frame, img_energia_star_3, "hint_energia", "Ter mantido a energia maior que 90 durante 180 segundos");

	lb_energia_xnum = new TextNode("lb_energia_xnum");
	stringstream energia_adicionais;
	energia_adicionais<<((lvl_energia - 3) > 0 ? lvl_energia - 3 : 0);
	lb_energia_xnum->set_text("+ " + energia_adicionais.str());
	lb_energia_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_energia_xnum = np_frame.attach_new_node(lb_energia_xnum);
	np_lb_energia_xnum.set_scale(0.06);
	np_lb_energia_xnum.set_pos(1.01, 0, 0.33);
	np_lb_energia_xnum.set_color(0, 0, 0, 1);

	stringstream energia_andamento;
	lb_energia_andamento = new TextNode("lb_energia_andamento");
	if (lvl_energia == 0) {
		energia_andamento<<player->get_achievements()->get_count_secs_energy();
		lb_energia_andamento->set_text(energia_andamento.str() + " / 60");
	}
	else if (lvl_energia == 1) {
		energia_andamento<<player->get_achievements()->get_count_secs_energy();
		lb_energia_andamento->set_text(energia_andamento.str() + " / 120");
	}
	else {
		energia_andamento<<player->get_achievements()->get_count_secs_energy();
		lb_energia_andamento->set_text(energia_andamento.str() + " / 180");
	}
	//lb_energia_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_energia_andamento = np_frame.attach_new_node(lb_energia_andamento);
	np_lb_energia_andamento.set_scale(0.05);
	np_lb_energia_andamento.set_pos(1.25, 0, 0.35);
	np_lb_energia_andamento.set_color(0, 0, 0, 1);
	// FIM DO ACHIEVEMENT ENERGIA

	// ACHIEVEMENT: O intocável
	lb_intocavel = new Text("lb_intocavel", "- O intocável", np_frame, TextNode::get_default_font(), 0.05);
	lb_intocavel->set_pos(0.06, 0, 0.25);

	int lvl_intocavel = player->get_achievements()->get_lvl_intocavel();
	switch (lvl_intocavel) {
		case 0:
			create_intocavel_stars(white, white, white);
			hint_intocavel_atual = new Hint(np_frame, lb_intocavel, lb_intocavel->get_np(), "hint_intocavel", "Permaneça sem receber dano de predadores durante 60 segundos.");
			break;
		case 1:
			create_intocavel_stars(yellow, white, white);
			hint_intocavel_atual = new Hint(np_frame, lb_intocavel, lb_intocavel->get_np(), "hint_intocavel", "Permaneça sem receber dano de predadores durante 120 segundos.");
			break;
		case 2:
			create_intocavel_stars(yellow, yellow, white);
			hint_intocavel_atual = new Hint(np_frame, lb_intocavel, lb_intocavel->get_np(), "hint_intocavel", "Permaneça sem receber dano de predadores durante 180 segundos.");
			break;
		default:
			create_intocavel_stars(yellow, yellow, yellow);
			hint_intocavel_atual = new Hint(np_frame, lb_intocavel, lb_intocavel->get_np(), "hint_intocavel", "Permaneça sem receber dano de predadores durante 180 segundos.");
	}

	hint_intocavel_1 = new Hint(np_frame, img_intocavel_star_1, "hint_intocavel", "Não ter recebido dano de nenhum predador durante 60 segundos");
	hint_intocavel_2 = new Hint(np_frame, img_intocavel_star_2, "hint_intocavel", "Não ter recebido dano de nenhum predador durante 120 segundos");
	hint_intocavel_3 = new Hint(np_frame, img_intocavel_star_3, "hint_intocavel", "Não ter recebido dano de nenhum predador durante 180 segundos");

	lb_intocavel_xnum = new TextNode("lb_intocavel_xnum");
	stringstream intocavel_adicionais;
	intocavel_adicionais<<((lvl_intocavel - 3) > 0 ? lvl_intocavel - 3 : 0);
	lb_intocavel_xnum->set_text("+ " + intocavel_adicionais.str());
	lb_intocavel_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_intocavel_xnum = np_frame.attach_new_node(lb_intocavel_xnum);
	np_lb_intocavel_xnum.set_scale(0.06);
	np_lb_intocavel_xnum.set_pos(1.01, 0, 0.23);
	np_lb_intocavel_xnum.set_color(0, 0, 0, 1);

	stringstream intocavel_andamento;
	lb_intocavel_andamento = new TextNode("lb_intocavel_andamento");
	simdunas_cat.debug()<<"seconds untouched = "<<player->get_achievements()->get_count_secs_untouched()<<endl;
	if (lvl_intocavel == 0) {
		intocavel_andamento<<player->get_achievements()->get_count_secs_untouched();
		lb_intocavel_andamento->set_text(intocavel_andamento.str() + " / 60");
	}
	else if (lvl_intocavel == 1) {
		intocavel_andamento<<player->get_achievements()->get_count_secs_untouched();
		lb_intocavel_andamento->set_text(intocavel_andamento.str() + " / 120");
	}
	else {
		intocavel_andamento<<player->get_achievements()->get_count_secs_untouched();
		lb_intocavel_andamento->set_text(intocavel_andamento.str() + " / 180");
	}
	//lb_intocavel_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_intocavel_andamento = np_frame.attach_new_node(lb_intocavel_andamento);
	np_lb_intocavel_andamento.set_scale(0.05);
	np_lb_intocavel_andamento.set_pos(1.25, 0, 0.25);
	np_lb_intocavel_andamento.set_color(0, 0, 0, 1);

	// ACHIEVEMENT: O Guerreiro
	lb_guerreiro = new Text("lb_guerreiro", "- Guerreiro", np_frame, TextNode::get_default_font(), 0.05);
	lb_guerreiro->set_pos(0.06, 0, 0.15);

	int lvl_guerreiro = player->get_achievements()->get_lvl_guerreiro();
	switch (lvl_guerreiro) {
		case 0:
			create_guerreiro_stars(white, white, white);
			hint_guerreiro_atual = new Hint(np_frame, lb_guerreiro, lb_guerreiro->get_np(), "hint_guerreiro", "Espante 2 lagartos machos (necessários 12 meses de vida).");
			break;
		case 1:
			create_guerreiro_stars(yellow, white, white);
			hint_guerreiro_atual = new Hint(np_frame, lb_guerreiro, lb_guerreiro->get_np(), "hint_guerreiro", "Espante 5 lagartos machos (necessários 12 meses de vida).");
			break;
		case 2:
			create_guerreiro_stars(yellow, yellow, white);
			hint_guerreiro_atual = new Hint(np_frame, lb_guerreiro, lb_guerreiro->get_np(), "hint_guerreiro", "Espante 10 lagartos machos (necessários 12 meses de vida).");
			break;
		default:
			create_guerreiro_stars(yellow, yellow, yellow);
			hint_guerreiro_atual = new Hint(np_frame, lb_guerreiro, lb_guerreiro->get_np(), "hint_guerreiro", "Espante 10 lagartos machos (necessários 12 meses de vida).");
	}

	hint_guerreiro_1 = new Hint(np_frame, img_guerreiro_star_1, "hint_guerreiro", "Ter espantado 2 lagartos machos.");
	hint_guerreiro_2 = new Hint(np_frame, img_guerreiro_star_2, "hint_guerreiro", "Ter espantado 5 lagartos machos.");
	hint_guerreiro_3 = new Hint(np_frame, img_guerreiro_star_3, "hint_guerreiro", "Ter espantado 10 lagartos machos.");

	lb_guerreiro_xnum = new TextNode("lb_guerreiro_xnum");
	stringstream guerreiro_adicionais;
	guerreiro_adicionais<<((lvl_guerreiro - 3) > 0 ? lvl_guerreiro - 3 : 0);
	lb_guerreiro_xnum->set_text("+ " + guerreiro_adicionais.str());
	lb_guerreiro_xnum->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_guerreiro_xnum = np_frame.attach_new_node(lb_guerreiro_xnum);
	np_lb_guerreiro_xnum.set_scale(0.06);
	np_lb_guerreiro_xnum.set_pos(1.01, 0, 0.13);
	np_lb_guerreiro_xnum.set_color(0, 0, 0, 1);

	stringstream guerreiro_andamento;
	lb_guerreiro_andamento = new TextNode("lb_guerreiro_andamento");
	if (lvl_guerreiro == 0) {
		guerreiro_andamento<<player->get_achievements()->get_count_guerreiro();
		lb_guerreiro_andamento->set_text(guerreiro_andamento.str() + " / 2");
	}
	else if (lvl_guerreiro == 1) {
		guerreiro_andamento<<player->get_achievements()->get_count_guerreiro();
		lb_guerreiro_andamento->set_text(guerreiro_andamento.str() + " / 5");
	}
	else {
		guerreiro_andamento<<player->get_achievements()->get_count_guerreiro();
		lb_guerreiro_andamento->set_text(guerreiro_andamento.str() + " / 10");
	}
	//lb_guerreiro_andamento->set_font(FontPool::load_font("models/gui/fonts/suplexcomic-large"));
	np_lb_guerreiro_andamento = np_frame.attach_new_node(lb_guerreiro_andamento);
	np_lb_guerreiro_andamento.set_scale(0.05);
	np_lb_guerreiro_andamento.set_pos(1.25, 0, 0.15);
	np_lb_guerreiro_andamento.set_color(0, 0, 0, 1);
}

AchievementsWindow::~AchievementsWindow() {
	hint_bom_de_boca_1 = NULL;
	hint_bom_de_boca_2 = NULL;
	hint_bom_de_boca_3 = NULL;
	hint_bom_de_boca_atual = NULL;
	hint_energia_1 = NULL;
	hint_energia_2 = NULL;
	hint_energia_3 = NULL;
	hint_energia_atual = NULL;
	hint_guerreiro_1 = NULL;
	hint_guerreiro_2 = NULL;
	hint_guerreiro_3 = NULL;
	hint_guerreiro_atual = NULL;
	hint_hidratacao_1 = NULL;
	hint_hidratacao_2 = NULL;
	hint_hidratacao_3 = NULL;
	hint_hidratacao_atual = NULL;
	hint_intocavel_1 = NULL;
	hint_intocavel_2 = NULL;
	hint_intocavel_3 = NULL;
	hint_intocavel_atual = NULL;
	hint_reprodutor_1 = NULL;
	hint_reprodutor_2 = NULL;
	hint_reprodutor_3 = NULL;
	hint_reprodutor_atual = NULL;
	hint_sobrevivente_1 = NULL;
	hint_sobrevivente_2 = NULL;
	hint_sobrevivente_3 = NULL;
	hint_sobrevivente_atual = NULL;
	hint_temperatura_1 = NULL;
	hint_temperatura_2 = NULL;
	hint_temperatura_3 = NULL;
	hint_temperatura_atual = NULL;
}

void AchievementsWindow::create_senhor_mordida_stars(string star1, string star2, string star3) {
	img_senhor_mordida_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_senhor_mordida_star_1.reparent_to(np_frame);
	img_senhor_mordida_star_1.set_scale(0.003);
	img_senhor_mordida_star_1.set_pos(0.76, 0, 0.96);

	img_senhor_mordida_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_senhor_mordida_star_2.reparent_to(np_frame);
	img_senhor_mordida_star_2.set_scale(0.003);
	img_senhor_mordida_star_2.set_pos(0.86, 0, 0.96);

	img_senhor_mordida_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_senhor_mordida_star_3.reparent_to(np_frame);
	img_senhor_mordida_star_3.set_scale(0.003);
	img_senhor_mordida_star_3.set_pos(0.96, 0, 0.96);
}

void AchievementsWindow::create_bom_de_boca_stars(string star1, string star2, string star3) {
	img_bom_de_boca_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_bom_de_boca_star_1.reparent_to(np_frame);
	img_bom_de_boca_star_1.set_scale(0.003);
	img_bom_de_boca_star_1.set_pos(0.76, 0, 0.86);

	img_bom_de_boca_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_bom_de_boca_star_2.reparent_to(np_frame);
	img_bom_de_boca_star_2.set_scale(0.003);
	img_bom_de_boca_star_2.set_pos(0.86, 0, 0.86);

	img_bom_de_boca_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_bom_de_boca_star_3.reparent_to(np_frame);
	img_bom_de_boca_star_3.set_scale(0.003);
	img_bom_de_boca_star_3.set_pos(0.96, 0, 0.86);
}

void AchievementsWindow::create_sobrevivente_stars(string star1, string star2, string star3) {
	img_sobrevivente_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_sobrevivente_star_1.reparent_to(np_frame);
	img_sobrevivente_star_1.set_scale(0.003);
	img_sobrevivente_star_1.set_pos(0.76, 0, 0.76);

	img_sobrevivente_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_sobrevivente_star_2.reparent_to(np_frame);
	img_sobrevivente_star_2.set_scale(0.003);
	img_sobrevivente_star_2.set_pos(0.86, 0, 0.76);

	img_sobrevivente_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_sobrevivente_star_3.reparent_to(np_frame);
	img_sobrevivente_star_3.set_scale(0.003);
	img_sobrevivente_star_3.set_pos(0.96, 0, 0.76);
}

void AchievementsWindow::create_reprodutor_stars(string star1, string star2, string star3) {
	img_reprodutor_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_reprodutor_star_1.reparent_to(np_frame);
	img_reprodutor_star_1.set_scale(0.003);
	img_reprodutor_star_1.set_pos(0.76, 0, 0.66);

	img_reprodutor_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_reprodutor_star_2.reparent_to(np_frame);
	img_reprodutor_star_2.set_scale(0.003);
	img_reprodutor_star_2.set_pos(0.86, 0, 0.66);

	img_reprodutor_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_reprodutor_star_3.reparent_to(np_frame);
	img_reprodutor_star_3.set_scale(0.003);
	img_reprodutor_star_3.set_pos(0.96, 0, 0.66);
}

void AchievementsWindow::create_temperatura_stars(string star1, string star2, string star3) {
	img_temperatura_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_temperatura_star_1.reparent_to(np_frame);
	img_temperatura_star_1.set_scale(0.003);
	img_temperatura_star_1.set_pos(0.76, 0, 0.56);

	img_temperatura_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_temperatura_star_2.reparent_to(np_frame);
	img_temperatura_star_2.set_scale(0.003);
	img_temperatura_star_2.set_pos(0.86, 0, 0.56);

	img_temperatura_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_temperatura_star_3.reparent_to(np_frame);
	img_temperatura_star_3.set_scale(0.003);
	img_temperatura_star_3.set_pos(0.96, 0, 0.56);
}

void AchievementsWindow::create_hidratacao_stars(string star1, string star2, string star3) {
	img_hidratacao_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_hidratacao_star_1.reparent_to(np_frame);
	img_hidratacao_star_1.set_scale(0.003);
	img_hidratacao_star_1.set_pos(0.76, 0, 0.46);

	img_hidratacao_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_hidratacao_star_2.reparent_to(np_frame);
	img_hidratacao_star_2.set_scale(0.003);
	img_hidratacao_star_2.set_pos(0.86, 0, 0.46);

	img_hidratacao_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_hidratacao_star_3.reparent_to(np_frame);
	img_hidratacao_star_3.set_scale(0.003);
	img_hidratacao_star_3.set_pos(0.96, 0, 0.46);
}

void AchievementsWindow::create_energia_stars(string star1, string star2, string star3) {
	img_energia_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_energia_star_1.reparent_to(np_frame);
	img_energia_star_1.set_scale(0.003);
	img_energia_star_1.set_pos(0.76, 0, 0.36);

	img_energia_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_energia_star_2.reparent_to(np_frame);
	img_energia_star_2.set_scale(0.003);
	img_energia_star_2.set_pos(0.86, 0, 0.36);

	img_energia_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_energia_star_3.reparent_to(np_frame);
	img_energia_star_3.set_scale(0.003);
	img_energia_star_3.set_pos(0.96, 0, 0.36);
}

void AchievementsWindow::create_intocavel_stars(string star1, string star2, string star3) {
	img_intocavel_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_intocavel_star_1.reparent_to(np_frame);
	img_intocavel_star_1.set_scale(0.003);
	img_intocavel_star_1.set_pos(0.76, 0, 0.26);

	img_intocavel_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_intocavel_star_2.reparent_to(np_frame);
	img_intocavel_star_2.set_scale(0.003);
	img_intocavel_star_2.set_pos(0.86, 0, 0.26);

	img_intocavel_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_intocavel_star_3.reparent_to(np_frame);
	img_intocavel_star_3.set_scale(0.003);
	img_intocavel_star_3.set_pos(0.96, 0, 0.26);
}

void AchievementsWindow::create_guerreiro_stars(string star1, string star2, string star3) {
	img_guerreiro_star_1 = ImageRepository::get_instance()->get_image(star1);
	img_guerreiro_star_1.reparent_to(np_frame);
	img_guerreiro_star_1.set_scale(0.003);
	img_guerreiro_star_1.set_pos(0.76, 0, 0.16);

	img_guerreiro_star_2 = ImageRepository::get_instance()->get_image(star2);
	img_guerreiro_star_2.reparent_to(np_frame);
	img_guerreiro_star_2.set_scale(0.003);
	img_guerreiro_star_2.set_pos(0.86, 0, 0.16);

	img_guerreiro_star_3 = ImageRepository::get_instance()->get_image(star3);
	img_guerreiro_star_3.reparent_to(np_frame);
	img_guerreiro_star_3.set_scale(0.003);
	img_guerreiro_star_3.set_pos(0.96, 0, 0.16);
}
