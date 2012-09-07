/*
 * achievementsWindow.h
 *
 *  Created on: Dec 13, 2011
 *      Author: jonatas
 */

#ifndef ACHIEVEMENTSWINDOW_H
#define ACHIEVEMENTSWINDOW_H

#include "window.h"
#include "hint.h"
#include "text.h"

class AchievementsWindow : public Window {
public:
	AchievementsWindow(NodePath parent, float width = 2, float height = 1, string title = "frame", float pos_x = -0.8, float pos_y = -0.8);
	virtual ~AchievementsWindow();

	void create_senhor_mordida_stars(string star1, string star2, string star3);
	void create_bom_de_boca_stars(string star1, string star2, string star3);
	void create_sobrevivente_stars(string star1, string star2, string star3);
	void create_reprodutor_stars(string star1, string star2, string star3);
	void create_temperatura_stars(string star1, string star2, string star3);
	void create_hidratacao_stars(string star1, string star2, string star3);
	void create_energia_stars(string star1, string star2, string star3);
	void create_intocavel_stars(string star1, string star2, string star3);
	void create_guerreiro_stars(string star1, string star2, string star3);

private:
	PT(TextNode) lb_andamento;
	NodePath np_lb_andamento;

	// Achievement: Senhor mordida perfeita
	PT(Text) lb_senhor_mordida;
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
	PT(Text) lb_bom_de_boca;
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
	PT(Text) lb_sobrevivente;
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
	PT(Text) lb_reprodutor;
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

	// Achievement: Temperatura
	PT(Text) lb_temperatura;
	PT(Hint) hint_temperatura_atual;
	PT(Hint) hint_temperatura_1;
	PT(Hint) hint_temperatura_2;
	PT(Hint) hint_temperatura_3;
	NodePath img_temperatura_star_1;
	NodePath img_temperatura_star_2;
	NodePath img_temperatura_star_3;
	PT(TextNode) lb_temperatura_xnum;
	NodePath np_lb_temperatura_xnum;
	PT(TextNode) lb_temperatura_andamento;
	NodePath np_lb_temperatura_andamento;

	// Achievement: Hidratação
	PT(Text) lb_hidratacao;
	PT(Hint) hint_hidratacao_atual;
	PT(Hint) hint_hidratacao_1;
	PT(Hint) hint_hidratacao_2;
	PT(Hint) hint_hidratacao_3;
	NodePath img_hidratacao_star_1;
	NodePath img_hidratacao_star_2;
	NodePath img_hidratacao_star_3;
	PT(TextNode) lb_hidratacao_xnum;
	NodePath np_lb_hidratacao_xnum;
	PT(TextNode) lb_hidratacao_andamento;
	NodePath np_lb_hidratacao_andamento;

	// Achievement: Energia
	PT(Text) lb_energia;
	PT(Hint) hint_energia_atual;
	PT(Hint) hint_energia_1;
	PT(Hint) hint_energia_2;
	PT(Hint) hint_energia_3;
	NodePath img_energia_star_1;
	NodePath img_energia_star_2;
	NodePath img_energia_star_3;
	PT(TextNode) lb_energia_xnum;
	NodePath np_lb_energia_xnum;
	PT(TextNode) lb_energia_andamento;
	NodePath np_lb_energia_andamento;

	// Achievement: Intocável
	PT(Text) lb_intocavel;
	PT(Hint) hint_intocavel_atual;
	PT(Hint) hint_intocavel_1;
	PT(Hint) hint_intocavel_2;
	PT(Hint) hint_intocavel_3;
	NodePath img_intocavel_star_1;
	NodePath img_intocavel_star_2;
	NodePath img_intocavel_star_3;
	PT(TextNode) lb_intocavel_xnum;
	NodePath np_lb_intocavel_xnum;
	PT(TextNode) lb_intocavel_andamento;
	NodePath np_lb_intocavel_andamento;

	// Achievement: Guerreiro
	PT(Text) lb_guerreiro;
	PT(Hint) hint_guerreiro_atual;
	PT(Hint) hint_guerreiro_1;
	PT(Hint) hint_guerreiro_2;
	PT(Hint) hint_guerreiro_3;
	NodePath img_guerreiro_star_1;
	NodePath img_guerreiro_star_2;
	NodePath img_guerreiro_star_3;
	PT(TextNode) lb_guerreiro_xnum;
	NodePath np_lb_guerreiro_xnum;
	PT(TextNode) lb_guerreiro_andamento;
	NodePath np_lb_guerreiro_andamento;
};

#endif /* ACHIEVEMENTSWINDOW_H */
