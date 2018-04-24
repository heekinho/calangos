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
#include "stateHistory.h"
#include "eventHandler.h"
#include "button.h"
class stateHistory;
class Graphics;
class Hint;
//class History;

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(GraphicsMenu))(GraphicsMenu*)d)->mn(); }

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

	PT(PGButton) get_btn_sombra();
	NodePath get_led_off_sombra();
	NodePath get_led_on_sombra();
	
	PT(PGButton) get_btn_correndo();
	NodePath get_led_off_correndo();
	NodePath get_led_on_correndo();

	PT(PGButton) get_btn_comeu();
	NodePath get_led_off_comeu();
	NodePath get_led_on_comeu();


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

    NodePath get_node_sombra();
	NodePath get_node_correndo();
	NodePath get_node_comeu();


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
	void make_txt_legen_graf(NodePath menu_frame_np);
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
	void make_btn_sombra(NodePath menu_frame_np);
	void make_btn_correndo(NodePath menu_frame_np);
	void make_btn_comeu(NodePath menu_frame_np);

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
	void hide_all_led_on();
	void show_menu_graf_variavel();

	void hide_all_graphics();
	void build_options();
	void init_graphics();

	static stateHistory::SHList list;
	PT(Graphics) make_new_chart(History::HistoryItem item, PT(Graphics) &chart,
			const string &title, const string &x_axis, const string &y_axis);
	PT(Graphics) novo_grafico1_TempInterna();
	PT(Graphics) novo_grafico2_Hidratacao();
	PT(Graphics) novo_grafico3_TempAr();
	PT(Graphics) novo_grafico4_Umidade();
	PT(Graphics) novo_grafico5_TempSolo();
	PT(Graphics) novo_grafico6_Alimentacao();
	PT(Graphics) novo_grafico7_Energia();
	PT(Graphics) novo_grafico8_GastoEnergetico();
	void desliga_leds_painel_tempo();
	void desliga_leds_painel_variavel();

	static void click_event_botao_grafico_tempo(const Event*, void *data);
	static void click_event_botao_grafico_variavel(const Event*, void *data);
	static void click_event_botao_grafico_tempInterna(const Event*, void *data);
	static void click_event_botao_grafico_hidratacao(const Event*, void *data);
	static void click_event_botao_grafico_tempAr(const Event*, void *data);
	static void click_event_botao_grafico_umidade(const Event*, void *data);
	static void click_event_botao_grafico_tempSolo(const Event*, void *data);
	static void click_event_botao_grafico_alimentacao(const Event*, void *data);
	static void click_event_botao_grafico_energia(const Event*, void *data);
	static void click_event_botao_grafico_gastoEnergetico(const Event*, void *data);

	static void click_event_botao_grafico_sombra(const Event*, void *data);
	static void click_event_botao_grafico_correndo(const Event*, void *data);
	static void click_event_botao_grafico_comeu(const Event*, void *data);

	static void click_event_botao_grafico_tempInterna_v(const Event*, void *data);
	static void click_event_botao_grafico_hidratacao_v(const Event*, void *data);
	static void click_event_botao_grafico_tempAr_v(const Event*, void *data);
	static void click_event_botao_grafico_umidade_v(const Event*, void *data);
	static void click_event_botao_grafico_tempSolo_v(const Event*, void *data);
	static void click_event_botao_grafico_alimentacao_v(const Event*, void *data);
	static void click_event_botao_grafico_energia_v(const Event*, void *data);
	static void click_event_botao_grafico_gastoEnergetico_v(const Event*, void *data);

	void set_chart_properties(int chart_number, int chart_position);
	PT(Graphics) create_time_chart(int chart_number, int chart_position);
	void create_variable_chart(History::HList *vetor_x, History::HList *vetor_y,
			const string &legenda_x, const string &legenda_y, bool set_eixo_y);
	void add_hooks();
	void remove_hooks();
	void init_variables();
	void create_default_time_chart();
	//void draw_hint_line(PT(Graphics) &chart, float min_y, float max_y);
	//void draw_hint_line();
	bool get_grafico_tempo_ativo();
	bool get_grafico_variavel_ativo();
	void set_grafico_variavel_ativo(bool grafico_variavel_ativo);
	PT(Graphics) get_chart1();
	PT(Graphics) get_chart2();
	void set_chart1(PT(Graphics) chart1);
	void set_chart2(PT(Graphics) chart2);
	ACTION(draw_hint_line);

	PT(History) get_history();
	PT(stateHistory) get_stateHistory();
	int get_elapsed_days();
	History::HList* get_item_list_by_day(int day_number, History::HList *item_list, History::HList *time_list);
	History::HList* get_time_list_by_day(int day_number, History::HList *time_list);
	
	int get_current_day();
	void set_current_day(int current_day);
	
	PT(PGButton) get_btn_previous_page_chart1();
	PT(PGButton) get_btn_next_page_chart1();
	void make_btn_previous_page_chart1(NodePath menu_frame_np);
	void make_btn_next_page_chart1(NodePath menu_frame_np);
	static void click_event_btn_previous_page_chart1(const Event*, void *data);
	static void click_event_btn_next_page_chart1(const Event*, void *data);
	
	void set_menu_frame_np(NodePath menu_frame);
	NodePath get_menu_frame_np();
	NodePath menu_np;
	History::HistoryItem get_item_chart1();
	History::HistoryItem get_item_chart2();
	void update_chart_page();
	void set_chart_page_properties(History::HistoryItem item, PT(Graphics) chart,
			const string &title, const string &x_axis, const string &y_axis, int chart_number);

private:
	PT(TextNode) get_txt_legenda();
	void set_txt_legenda(PT(TextNode) text_legenda);
	void set_txt_legenda_np(NodePath text_legenda_np);
	PT(TextNode) txt_legenda;
	NodePath txt_legenda_np;
	NodePath get_txt_legenda_np();
	//void set_txt_legenda_np(NodePath text_legenda_np);
	


	PT(TextNode) txt_tipo_graf;
	NodePath label_txt_tipo_graf;

	PT(TextNode) txt_legen_graf;
	NodePath label_txt_legen_graf;

	PT(PGButton) btn_graf_tempo;
	NodePath np_btn_graf_tempo;
	NodePath led_off_graf_tempo;
	NodePath led_on_graf_tempo;

	PT(PGButton) btn_graf_variavel;
	NodePath np_btn_graf_variavel;
	NodePath led_off_graf_variavel;
	NodePath led_on_graf_variavel;

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

	
	NodePath node_sombra;
	NodePath node_correndo;
	NodePath node_comeu;

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


	PT(PGButton) btn_sombra;
	NodePath np_btn_sombra;
	NodePath img_btn_sombra;
	PT(Hint) hint_btn_sombra;
	NodePath led_off_sombra;
	NodePath led_on_sombra;
	bool flag_sombra;

	PT(PGButton) btn_correndo;
	NodePath np_btn_correndo;
	NodePath img_btn_correndo;
	PT(Hint) hint_btn_correndo;
	NodePath led_off_correndo;
	NodePath led_on_correndo;
	bool flag_correndo;

	PT(PGButton) btn_comeu;
	NodePath np_btn_comeu;
	NodePath img_btn_comeu;
	PT(Hint) hint_btn_comeu;
	NodePath led_off_comeu;
	NodePath led_on_comeu;
	bool flag_comeu;

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
	PT(stateHistory) stateHistory;

    bool grafico_tempo_ativo;
    bool grafico_variavel_ativo;

    bool grafico_posicao1_ativo;
    bool grafico_posicao2_ativo;

    PT(Graphics) chart1; // gráfico posicionado na parte superior do menu de gráficos
    PT(Graphics) chart2; // gráfico posicionado na parte inferior do menu de gráficos

    int current_day; // dia atual visualizado na paginação dos gráficos

    // botões "<<<" e ">>>" do gráfico
    PT(PGButton) btn_previous_page_chart1;
    NodePath np_btn_previous_page_chart1;
    PT(PGButton) btn_next_page_chart1;
    NodePath np_btn_next_page_chart1;

	// itens correntes nos gráficos superior e inferior (umidade, hidratacao, energia etc)
	History::HistoryItem item_chart1;
	History::HistoryItem item_chart2;
	 
	PT(Graphics) chart_1;
	PT(Graphics) chart_2;
	string title_chart1;
	string title_chart2;
	string x_axis_chart1;
	string x_axis_chart2;
	string y_axis_chart1;
	string y_axis_chart2;



//    // 0 - não está na tela; 1 - está em cima; 2 - está embaixo
//    static int posicao_grafico_tempInterna;
//    static int posicao_grafico_hidratacao;
//    static int posicao_grafico_tempAr;
//    static int posicao_grafico_umidade;
//    static int posicao_grafico_tempSolo;
//    static int posicao_grafico_alimentacao;
//    static int posicao_grafico_energia;
//    static int posicao_grafico_gastoEnergetico;

};

#undef ACTION

#endif /* GRAPHICSMENU_H */
