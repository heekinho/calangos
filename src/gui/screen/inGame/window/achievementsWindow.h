/*
 * achievementsWindow.h
 *
 *  Created on: Dec 13, 2011
 *      Author: jonatas
 */

#ifndef ACHIEVEMENTSWINDOW_H
#define ACHIEVEMENTSWINDOW_H

#include "window.h"

class AchievementsWindow : public Window {
public:
	AchievementsWindow(NodePath parent, float width = 2, float height = 1, string title = "frame", float pos_x = -0.8, float pos_y = -0.8);
	virtual ~AchievementsWindow();

	void create_senhor_mordida_stars(string star1, string star2, string star3);
	void create_bom_de_boca_stars(string star1, string star2, string star3);

private:
	PT(TextNode) lb_andamento;
	NodePath np_lb_andamento;

	// Achievement: Senhor mordida perfeita
	PT(TextNode) lb_senhor_mordida;
	NodePath np_lb_senhor_mordida;
	PT(Hint) hint_senhor_mordida_atual;
	PT(Hint) hint_senhor_mordida_1;
	PT(Hint) hint_senhor_mordida_2;
	PT(Hint) hint_senhor_mordida_3;
	NodePath img_senhor_mordida_star_1;
	NodePath img_senhor_mordida_star_2;
	NodePath img_senhor_mordida_star_3;
	PT(TextNode) lb_senhor_mordida_xnum;
	NodePath np_lb_senhor_mordida_xnum;
	PT(TextNode) lb_senhor_mordida_andamento;
	NodePath np_lb_senhor_mordida_andamento;

	// Achievement: O bom de boca
	PT(TextNode) lb_bom_de_boca;
	NodePath np_lb_bom_de_boca;
	PT(Hint) hint_bom_de_boca_atual;
	PT(Hint) hint_bom_de_boca_1;
	PT(Hint) hint_bom_de_boca_2;
	PT(Hint) hint_bom_de_boca_3;
	NodePath img_bom_de_boca_star_1;
	NodePath img_bom_de_boca_star_2;
	NodePath img_bom_de_boca_star_3;
	PT(TextNode) lb_bom_de_boca_xnum;
	NodePath np_lb_bom_de_boca_xnum;
	PT(TextNode) lb_bom_de_boca_andamento;
	NodePath np_lb_bom_de_boca_andamento;

	// Achievement: Sobrevivente
	PT(TextNode) lb_sobrevivente;
	NodePath np_lb_sobrevivente;
	PT(Hint) hint_sobrevivente_atual;
	PT(Hint) hint_sobrevivente_1;
	PT(Hint) hint_sobrevivente_2;
	PT(Hint) hint_sobrevivente_3;
	NodePath img_sobrevivente_star_1;
	NodePath img_sobrevivente_star_2;
	NodePath img_sobrevivente_star_3;
	PT(TextNode) lb_sobrevivente_xnum;
	NodePath np_lb_sobrevivente_xnum;
	PT(TextNode) lb_sobrevivente_andamento;
	NodePath np_lb_sobrevivente_andamento;

	// Achievement: Reprodutor
	PT(TextNode) lb_reprodutor;
	NodePath np_lb_reprodutor;
	PT(Hint) hint_reprodutor_atual;
	PT(Hint) hint_reprodutor_1;
	PT(Hint) hint_reprodutor_2;
	PT(Hint) hint_reprodutor_3;
	NodePath img_reprodutor_star_1;
	NodePath img_reprodutor_star_2;
	NodePath img_reprodutor_star_3;
	PT(TextNode) lb_reprodutor_xnum;
	NodePath np_lb_reprodutor_xnum;
	PT(TextNode) lb_reprodutor_andamento;
	NodePath np_lb_reprodutor_andamento;
};

#endif /* ACHIEVEMENTSWINDOW_H */
