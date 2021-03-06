/*
 * gameStatusBar.h
 *
 *  Created on: Oct 4, 2010
 *      Author: jonatas
 */

#ifndef GAMESTATUSBAR_H
#define GAMESTATUSBAR_H

#include "pandaFramework.h"
#include "pgVirtualFrame.h"
#include "scrollBar.h"
#include "imageBar.h"
#include "hint.h"

class Hint;

class GameStatusBar : public ReferenceCount {
public:
	GameStatusBar(NodePath menu_frame_np);
	virtual ~GameStatusBar();

	NodePath get_relogio();
	ImageBar get_life_bar();
	PT(TextNode) get_label_life();
	NodePath get_piscar_model();
	ScrollBar get_hidratacao_scroll_bar();
	PT(TextNode) get_label_hidratacao();
	ScrollBar get_temperatura_scroll_bar();
	PT(TextNode) get_label_temperatura();
	ScrollBar get_temperatura_ambiente_scroll_bar();
	PT(TextNode) get_label_temperatura_ambiente();
	ScrollBar get_umidade_scroll_bar();
	PT(TextNode) get_label_umidade();
	PT(TextNode) get_label_egg_count();
	NodePath get_led_estado_reprodutivo();
	PT(TextNode) get_label_idade();
	PT(TextNode) get_label_idade_numero();
	PT(PGButton) get_btn_grafico();

	void make_relogio(NodePath menu_frame_np);
	void make_life_bar(NodePath menu_frame_np);
	void make_label_life(NodePath menu_frame_np);
	void make_piscar_model(NodePath menu_frame_np);
	void make_hidratacao_bar(NodePath menu_frame_np);
	void make_temperatura_bar(NodePath menu_frame_np);
	void make_temperatura_ambiente_bar(NodePath menu_frame_np);
	void make_umidade_bar(NodePath menu_frame_np);
	void make_estado_reprodutivo(NodePath menu_frame_np);
	void make_botao_grafico(NodePath menu_frame_np);
	void make_idade(NodePath menu_frame_np);
	void hide_all_status_components();
	void show_all_status_components();
	void set_led_estado_reprodutivo(bool on, NodePath menu_frame_np);

	void hidratacao_critica_on();
	void hidratacao_critica_off();
	static AsyncTask::DoneStatus efeito_alerta_hidratacao(GenericAsyncTask* task, void* data);

	void temperatura_critica_on();
	void temperatura_critica_off();
	static AsyncTask::DoneStatus efeito_alerta_temperatura(GenericAsyncTask* task, void* data);

private:
	NodePath relogio;
	NodePath relogio_pointer;
	PT(Hint) hint_relogio;
	NodePath img_life_bar;
	NodePath border_life_bar;
	ImageBar life_bar;
	PT(Hint) hint_life_bar;
	PT(TextNode) label_life;
	NodePath np_label_life;
	NodePath piscar_model;
	NodePath hidratacao_bar;
	NodePath hidratacao_bar_pointer;
	NodePath hidratacao_bar_pointer_red;
	NodePath img_hidratacao_bar;
	ScrollBar hidratacao_scroll_bar;
	PT(Hint) hint_hidratacao;
	PT(Hint) hint_hidratacao2;
	PT(TextNode) label_hidratacao;
	NodePath np_label_hidratacao;
	NodePath temperatura_bar;
	NodePath temperatura_bar_pointer;
	NodePath temperatura_bar_pointer_red;
	NodePath img_temperatura_bar;
	ScrollBar temperatura_scroll_bar;
	PT(Hint) hint_temperatura;
	PT(Hint) hint_temperatura2;
	PT(TextNode) label_temperatura;
	NodePath np_label_temperatura;
	NodePath temperatura_ambiente_bar;
	NodePath temperatura_ambiente_bar_pointer;
	NodePath img_temperatura_ambiente_bar;
	ScrollBar temperatura_ambiente_scroll_bar;
	PT(Hint) hint_temperatura_ambiente;
	PT(Hint) hint_temperatura_ambiente2;
	PT(TextNode) label_temperatura_ambiente;
	NodePath np_label_temperatura_ambiente;
	NodePath umidade_bar;
	NodePath umidade_bar_pointer;
	NodePath img_umidade_bar;
	ScrollBar umidade_scroll_bar;
	PT(Hint) hint_umidade;
	PT(Hint) hint_umidade2;
	PT(TextNode) label_umidade;
	NodePath np_label_umidade;
	NodePath estado_reprodutivo;
	PT(Hint) hint_estado_reprodutivo;
	NodePath led_estado_reprodutivo;
	NodePath egg;
	PT(Hint) hint_egg;
	PT(TextNode) label_egg_count;
	NodePath np_label_egg_count;
	PT(TextNode) label_idade;
	NodePath np_label_idade;
	PT(TextNode) label_idade_numero;
	NodePath np_label_idade_numero;
	NodePath img_calendar;
	PT(Hint) hint_idade;
	PT(PGButton) btn_grafico;
	NodePath np_btn_grafico;
	NodePath img_btn_grafico;
	PT(Hint) hint_btn_grafico;

	bool hidrat_critica;
	bool temp_critica;
	bool num_hidrat_vermelho;
	bool num_temp_vermelho;

};

#endif /* GAMESTATUSBAR_H */
