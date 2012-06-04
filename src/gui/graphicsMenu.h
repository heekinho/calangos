/*
 * graphicsMenu.h
 *
 *  Created on: Oct 24, 2010
 *      Author: jonatas
 */

#ifndef GRAPHICSMENU_H
#define GRAPHICSMENU_H

#include "pandaFramework.h"
#include "pgVirtualFrame.h"
#include "graphics.h"

#include "history.h"

class Graphics;
class Hint;
//class History;

class GraphicsMenu : public ReferenceCount {
public:
	GraphicsMenu(NodePath menu_frame_np);
	virtual ~GraphicsMenu();

	PT(PGButton) get_btn_graf_tempo();
	NodePath get_led_off_graf_tempo();
	NodePath get_led_on_graf_tempo();

	PT(PGButton) get_btn_graf_variavel();
	NodePath get_led_off_graf_variavel();
	NodePath get_led_on_graf_variavel();

	// Métodos get dos itens referentes ao menu de gráfico por tempo
	PT(PGButton) get_btn_temp_interna();
	NodePath get_led_off_temp_interna();
	NodePath get_led_on_temp_interna();

	PT(PGButton) get_btn_hidratacao();
	NodePath get_led_off_hidratacao();
	NodePath get_led_on_hidratacao();

	PT(PGButton) get_btn_temp_ar();
	NodePath get_led_off_temp_ar();
	NodePath get_led_on_temp_ar();

	PT(PGButton) get_btn_umidade();
	NodePath get_led_off_umidade();
	NodePath get_led_on_umidade();

	PT(PGButton) get_btn_temp_solo();
	NodePath get_led_off_temp_solo();
	NodePath get_led_on_temp_solo();

	PT(PGButton) get_btn_alimentacao();
	NodePath get_led_off_alimentacao();
	NodePath get_led_on_alimentacao();

	PT(PGButton) get_btn_energia();
	NodePath get_led_off_energia();
	NodePath get_led_on_energia();

	PT(PGButton) get_btn_gasto_energetico();
	NodePath get_led_off_gasto_energetico();
	NodePath get_led_on_gasto_energetico();

	// Métodos get dos itens referentes ao menu de gráfico variável
	PT(PGButton) get_btn_temp_interna_v();
	NodePath get_led_off_temp_interna_v();
	NodePath get_led_on_temp_interna_v();

	PT(PGButton) get_btn_hidratacao_v();
	NodePath get_led_off_hidratacao_v();
	NodePath get_led_on_hidratacao_v();

	PT(PGButton) get_btn_temp_ar_v();
	NodePath get_led_off_temp_ar_v();
	NodePath get_led_on_temp_ar_v();

	PT(PGButton) get_btn_umidade_v();
	NodePath get_led_off_umidade_v();
	NodePath get_led_on_umidade_v();

	PT(PGButton) get_btn_temp_solo_v();
	NodePath get_led_off_temp_solo_v();
	NodePath get_led_on_temp_solo_v();

	PT(PGButton) get_btn_alimentacao_v();
	NodePath get_led_off_alimentacao_v();
	NodePath get_led_on_alimentacao_v();

	PT(PGButton) get_btn_energia_v();
	NodePath get_led_off_energia_v();
	NodePath get_led_on_energia_v();

	PT(PGButton) get_btn_gasto_energetico_v();
	NodePath get_led_off_gasto_energetico_v();
	NodePath get_led_on_gasto_energetico_v();

	NodePath get_option_frame_np();
	NodePath get_grafico_variavel_frame_np();

	PT(Graphics) get_graphic_variavel();
	void set_graphic_variavel(PT(Graphics) graphic);
	PT(Graphics) get_graphic();
	PT(Graphics) get_graphic2();
	PT(Graphics) get_graphic3();
	PT(Graphics) get_graphic4();
	PT(Graphics) get_graphic5();
	PT(Graphics) get_graphic6();
	PT(Graphics) get_graphic7();
	PT(Graphics) get_graphic8();

	History::HList* get_vetor_x();
	void set_vetor_x(History::HList* vetor);
	History::HList* get_vetor_y();
	void set_vetor_y(History::HList* vetor);
	string get_legenda_x();
	void set_legenda_x(string legenda);
	string get_legenda_y();
	void set_legenda_y(string legenda);
    double get_limite_superior_x();
    void set_limite_superior_x(double limite);
    double get_limite_inferior_x();
    void set_limite_inferior_x(double limite);
    double get_limite_superior_y();
    void set_limite_superior_y(double limite);
    double get_limite_inferior_y();
    void set_limite_inferior_y(double limite);
    double get_tamanho_vetor_x();
    void set_tamanho_vetor_x(double tamanho);
    double get_tamanho_vetor_y();
    void set_tamanho_vetor_y(double tamanho);

	void make_tipo_graf(NodePath menu_frame_np);
	void make_txt_tipo_graf(NodePath menu_frame_np);
	void make_btn_graf_tempo(NodePath menu_frame_np);
	void make_btn_graf_variavel(NodePath menu_frame_np);

	void make_menu_graf_tempo(NodePath menu_frame_np);
	void make_btn_temp_interna(NodePath menu_frame_np);
	void make_btn_hidratacao(NodePath menu_frame_np);
	void make_btn_temp_ar(NodePath menu_frame_np);
	void make_btn_umidade(NodePath menu_frame_np);
	void make_btn_temp_solo(NodePath menu_frame_np);
	void make_btn_alimentacao(NodePath menu_frame_np);
	void make_btn_energia(NodePath menu_frame_np);
	void make_btn_gasto_energetico(NodePath menu_frame_np);

	void make_menu_graf_variavel();
	void make_btn_temp_interna_v();
	void make_btn_hidratacao_v();
	void make_btn_temp_ar_v();
	void make_btn_umidade_v();
	void make_btn_temp_solo_v();
	void make_btn_alimentacao_v();
	void make_btn_energia_v();
	void make_btn_gasto_energetico_v();

	void hide_all_option_graphics();
	void hide_menu_graf_tempo();
	void hide_menu_graf_variavel();
	void show_all_option_graphics();
	void show_menu_graf_tempo();
	void show_menu_graf_variavel();

	void hide_all_graphics();
	void build_options();
	void init_graphics();

	void make_new_chart(History::HistoryItem item, PT(Graphics) &chart,
			const string &title, const string &x_axis, const string &y_axis);
	void novo_grafico1_TempInterna();
	void novo_grafico2_Hidratacao();
	void novo_grafico3_TempAr();
	void novo_grafico4_Umidade();
	void novo_grafico5_TempSolo();
	void novo_grafico6_Alimentacao();
	void novo_grafico7_Energia();
	void novo_grafico8_GastoEnergetico();
	void desliga_leds_painel_tempo();
	void desliga_leds_painel_variavel();


private:
	PT(TextNode) txt_tipo_graf;
	NodePath label_txt_tipo_graf;

	PT(PGButton) btn_graf_tempo;
	NodePath np_btn_graf_tempo;
	NodePath led_off_graf_tempo;
	NodePath led_on_graf_tempo;

	PT(PGButton) btn_graf_variavel;
	NodePath np_btn_graf_variavel;
	NodePath led_off_graf_variavel;
	NodePath led_on_graf_variavel;

	bool flag_graf_tempo_ativo; // esses flags provavelmente devem ficar em guiManager mesmo.
	bool flag_graf_variavel_ativo;

	PT(PGButton) btn_temp_interna;
	NodePath np_btn_temp_interna;
	NodePath img_btn_temp_interna;
	PT(Hint) hint_btn_temp_interna;
	NodePath led_off_temp_interna;
	NodePath led_on_temp_interna;
	bool flag_temp_interna;

	PT(PGButton) btn_hidratacao;
	NodePath np_btn_hidratacao;
	NodePath img_btn_hidratacao;
	PT(Hint) hint_btn_hidratacao;
	NodePath led_off_hidratacao;
	NodePath led_on_hidratacao;
	bool flag_hidratacao;

	PT(PGButton) btn_temp_ar;
	NodePath np_btn_temp_ar;
	NodePath img_btn_temp_ar;
	PT(Hint) hint_btn_temp_ar;
	NodePath led_off_temp_ar;
	NodePath led_on_temp_ar;
	bool flag_temp_ar;

	PT(PGButton) btn_umidade;
	NodePath np_btn_umidade;
	NodePath img_btn_umidade;
	PT(Hint) hint_btn_umidade;
	NodePath led_off_umidade;
	NodePath led_on_umidade;
	bool flag_umidade;

	PT(PGButton) btn_temp_solo;
	NodePath np_btn_temp_solo;
	NodePath img_btn_temp_solo;
	PT(Hint) hint_btn_temp_solo;
	NodePath led_off_temp_solo;
	NodePath led_on_temp_solo;
	bool flag_temp_solo;

	PT(PGButton) btn_alimentacao;
	NodePath np_btn_alimentacao;
	NodePath img_btn_alimentacao;
	PT(Hint) hint_btn_alimentacao;
	NodePath led_off_alimentacao;
	NodePath led_on_alimentacao;
	bool flag_alimentacao;

	PT(PGButton) btn_energia;
	NodePath np_btn_energia;
	NodePath img_btn_energia;
	PT(Hint) hint_btn_energia;
	NodePath led_off_energia;
	NodePath led_on_energia;
	bool flag_energia;

	PT(PGButton) btn_gasto_energetico;
	NodePath np_btn_gasto_energetico;
	NodePath img_btn_gasto_energetico;
	PT(Hint) hint_btn_gasto_energetico;
	NodePath led_off_gasto_energetico;
	NodePath led_on_gasto_energetico;
	bool flag_gasto_energetico;

	PT(PGButton) btn_temp_interna_v; // "_v" de "variavel", para diferenciar das do gráfico de tempo
	NodePath np_btn_temp_interna_v;
	NodePath img_btn_temp_interna_v;
	PT(Hint) hint_btn_temp_interna_v;
	NodePath led_off_temp_interna_v;
	NodePath led_on_temp_interna_v;
	bool flag_temp_interna_v;

	PT(PGButton) btn_hidratacao_v;
	NodePath np_btn_hidratacao_v;
	NodePath img_btn_hidratacao_v;
	PT(Hint) hint_btn_hidratacao_v;
	NodePath led_off_hidratacao_v;
	NodePath led_on_hidratacao_v;
	bool flag_hidratacao_v;

	PT(PGButton) btn_temp_ar_v;
	NodePath np_btn_temp_ar_v;
	NodePath img_btn_temp_ar_v;
	PT(Hint) hint_btn_temp_ar_v;
	NodePath led_off_temp_ar_v;
	NodePath led_on_temp_ar_v;
	bool flag_temp_ar_v;

	PT(PGButton) btn_umidade_v;
	NodePath np_btn_umidade_v;
	NodePath img_btn_umidade_v;
	PT(Hint) hint_btn_umidade_v;
	NodePath led_off_umidade_v;
	NodePath led_on_umidade_v;
	bool flag_umidade_v;

	PT(PGButton) btn_temp_solo_v;
	NodePath np_btn_temp_solo_v;
	NodePath img_btn_temp_solo_v;
	PT(Hint) hint_btn_temp_solo_v;
	NodePath led_off_temp_solo_v;
	NodePath led_on_temp_solo_v;
	bool flag_temp_solo_v;

	PT(PGButton) btn_alimentacao_v;
	NodePath np_btn_alimentacao_v;
	NodePath img_btn_alimentacao_v;
	PT(Hint) hint_btn_alimentacao_v;
	NodePath led_off_alimentacao_v;
	NodePath led_on_alimentacao_v;
	bool flag_alimentacao_v;

	PT(PGButton) btn_energia_v;
	NodePath np_btn_energia_v;
	NodePath img_btn_energia_v;
	PT(Hint) hint_btn_energia_v;
	NodePath led_off_energia_v;
	NodePath led_on_energia_v;
	bool flag_energia_v;

	PT(PGButton) btn_gasto_energetico_v;
	NodePath np_btn_gasto_energetico_v;
	NodePath img_btn_gasto_energetico_v;
	PT(Hint) hint_btn_gasto_energetico_v;
	NodePath led_off_gasto_energetico_v;
	NodePath led_on_gasto_energetico_v;
	bool flag_gasto_energetico_v;

	PT(Graphics) graphicVariavel;
    PT(Graphics) graphic;
    PT(Graphics) graphic2;
    PT(Graphics) graphic3;
    PT(Graphics) graphic4;
    PT(Graphics) graphic5;
    PT(Graphics) graphic6;
    PT(Graphics) graphic7;
    PT(Graphics) graphic8;

    PT(PGVirtualFrame) option_frame;
    NodePath option_frame_np;

    PT(PGVirtualFrame) grafico_variavel_frame;
    NodePath grafico_variavel_frame_np;

	//CONFIGURAÇÕES DOS GRAFICOS DE VARIAVEIS.
    History::HList* vetor_x;
    History::HList* vetor_y;

    string legenda_x;
    string legenda_y;
    double limite_superior_x;
    double limite_inferior_x;
    double limite_superior_y;
    double limite_inferior_y;
    double tamanho_vetor_x;
    double tamanho_vetor_y;

    PT(History) history;
};

#endif /* GRAPHICSMENU_H */
