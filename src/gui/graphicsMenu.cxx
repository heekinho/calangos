/*
 * graphicsMenu.cxx
 *
 *  Created on: Oct 24, 2010
 *      Author: jonatas
 */

#include "graphicsMenu.h"
#include "imageRepository.h"
#include "hint.h"
#include "session.h"
#include "mouseButton.h"
#include "timeControl.h"
#include "mouseWatcher.h"
#include "button.h"

//bool grafico_tempo_ativo;
//bool grafico_variavel_ativo;

//bool grafico_posicao1_ativo;
//bool grafico_posicao2_ativo;

// 0 - não está na tela; 1 - está em cima; 2 - está embaixo
int posicao_grafico_tempInterna;
int posicao_grafico_hidratacao;
int posicao_grafico_tempAr;
int posicao_grafico_umidade;
int posicao_grafico_tempSolo;
int posicao_grafico_alimentacao;
int posicao_grafico_energia;
int posicao_grafico_gastoEnergetico;

GraphicsMenu::GraphicsMenu(NodePath menu_frame_np) {
	history = Session::get_instance()->history();

	set_current_day(get_elapsed_days());

	make_tipo_graf(menu_frame_np);
	make_menu_graf_tempo(menu_frame_np);

	build_options();
	make_menu_graf_variavel();

	// remover daqui ou associar ao stash/unstash do gráfico
	make_btn_previous_page_chart1(menu_frame_np);
	make_btn_next_page_chart1(menu_frame_np);

	add_hooks();
	init_variables();

	//current_day = get_elapsed_days();

//	set_vetor_x(history->get_list(History::HI_world_temperature));
//	set_vetor_y(history->get_list(History::HI_world_temperature));
//
//	set_legenda_x((string) "Temp do ar");
//	set_legenda_y((string) "Temp do ar");
//	set_limite_superior_x(History::get_largest_element(vetor_x));//45;
//	set_vetor_x(history->get_list(History::HI_world_temperature));
//	set_limite_inferior_x(History::get_smallest_element(vetor_x));//9;
//
//	set_limite_superior_y(History::get_largest_element(vetor_y));//45;
//	set_vetor_y(history->get_list(History::HI_world_temperature));
//	set_limite_inferior_y(History::get_smallest_element(vetor_y));//9;
//
//	set_tamanho_vetor_x(history->get_size(History::HI_world_temperature));
//	set_tamanho_vetor_y(history->get_size(History::HI_world_temperature));
//
//	set_graphic_variavel(new Graphics((get_option_frame_np()), vetor_x, vetor_y, limite_superior_x, limite_inferior_x, limite_superior_y, limite_inferior_y, false));
//	graphicVariavel->set_Position_Graphic(0.2, 0.6);
//	graphicVariavel->set_scale(1.2);
//	graphicVariavel->hide();
}

GraphicsMenu::~GraphicsMenu() {}

void GraphicsMenu::add_hooks() {
	event_handler->add_hook(get_btn_graf_tempo()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempo,this);
	event_handler->add_hook(get_btn_graf_variavel()->get_click_event(MouseButton::one()), click_event_botao_grafico_variavel,this);
	event_handler->add_hook(get_btn_temp_interna()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempInterna,this);
	event_handler->add_hook(get_btn_hidratacao()->get_click_event(MouseButton::one()), click_event_botao_grafico_hidratacao, this);
	event_handler->add_hook(get_btn_temp_ar()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempAr,this);
	event_handler->add_hook(get_btn_umidade()->get_click_event(MouseButton::one()), click_event_botao_grafico_umidade,this);
	event_handler->add_hook(get_btn_temp_solo()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempSolo,this);
	event_handler->add_hook(get_btn_alimentacao()->get_click_event(MouseButton::one()), click_event_botao_grafico_alimentacao, this);
	event_handler->add_hook(get_btn_energia()->get_click_event(MouseButton::one()), click_event_botao_grafico_energia,this);
	event_handler->add_hook(get_btn_gasto_energetico()->get_click_event(MouseButton::one()), click_event_botao_grafico_gastoEnergetico,this);
	event_handler->add_hook(get_btn_temp_interna_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempInterna_v,this);
	event_handler->add_hook(get_btn_hidratacao_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_hidratacao_v, this);
	event_handler->add_hook(get_btn_temp_ar_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempAr_v,this);
	event_handler->add_hook(get_btn_umidade_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_umidade_v,this);
	event_handler->add_hook(get_btn_temp_solo_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempSolo_v,this);
	event_handler->add_hook(get_btn_alimentacao_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_alimentacao_v, this);
	event_handler->add_hook(get_btn_energia_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_energia_v,this);
	event_handler->add_hook(get_btn_gasto_energetico_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_gastoEnergetico_v,this);
	event_handler->add_hook(get_btn_previous_page_chart1()->get_click_event(MouseButton::one()), click_event_btn_previous_page_chart1, this);
	event_handler->add_hook(get_btn_next_page_chart1()->get_click_event(MouseButton::one()), click_event_btn_next_page_chart1, this);
	event_handler->add_hook(TimeControl::EV_pass_frame_gui_options, draw_hint_line, this);
	//event_handler->add_hook(option_frame->get_within_event(), draw_hint_line, this);
}

void GraphicsMenu::remove_hooks() {
	event_handler->remove_hook(get_btn_graf_tempo()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempo,this);
	event_handler->remove_hook(get_btn_graf_variavel()->get_click_event(MouseButton::one()), click_event_botao_grafico_variavel,this);
	event_handler->remove_hook(get_btn_temp_interna()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempInterna,this);
	event_handler->remove_hook(get_btn_hidratacao()->get_click_event(MouseButton::one()), click_event_botao_grafico_hidratacao, this);
	event_handler->remove_hook(get_btn_temp_ar()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempAr,this);
	event_handler->remove_hook(get_btn_umidade()->get_click_event(MouseButton::one()), click_event_botao_grafico_umidade,this);
	event_handler->remove_hook(get_btn_temp_solo()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempSolo,this);
	event_handler->remove_hook(get_btn_alimentacao()->get_click_event(MouseButton::one()), click_event_botao_grafico_alimentacao, this);
	event_handler->remove_hook(get_btn_energia()->get_click_event(MouseButton::one()), click_event_botao_grafico_energia,this);
	event_handler->remove_hook(get_btn_gasto_energetico()->get_click_event(MouseButton::one()), click_event_botao_grafico_gastoEnergetico,this);
	event_handler->remove_hook(get_btn_temp_interna_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempInterna_v,this);
	event_handler->remove_hook(get_btn_hidratacao_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_hidratacao_v, this);
	event_handler->remove_hook(get_btn_temp_ar_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempAr_v,this);
	event_handler->remove_hook(get_btn_umidade_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_umidade_v,this);
	event_handler->remove_hook(get_btn_temp_solo_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempSolo_v,this);
	event_handler->remove_hook(get_btn_alimentacao_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_alimentacao_v, this);
	event_handler->remove_hook(get_btn_energia_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_energia_v,this);
	event_handler->remove_hook(get_btn_gasto_energetico_v()->get_click_event(MouseButton::one()), click_event_botao_grafico_gastoEnergetico_v,this);
	event_handler->remove_hook(get_btn_previous_page_chart1()->get_click_event(MouseButton::one()), click_event_btn_previous_page_chart1,this);
	event_handler->remove_hook(get_btn_next_page_chart1()->get_click_event(MouseButton::one()), click_event_btn_next_page_chart1,this);
	event_handler->remove_hook(TimeControl::EV_pass_frame_gui_options, draw_hint_line, this);
	//event_handler->remove_hook(option_frame->get_within_event(), draw_hint_line, this);
}

void GraphicsMenu::init_variables() {
	grafico_tempo_ativo = false;
	grafico_variavel_ativo = false;
	grafico_posicao1_ativo = false;
	grafico_posicao2_ativo = false;
	posicao_grafico_tempInterna = 0;
	posicao_grafico_hidratacao = 0;
	posicao_grafico_tempAr = 0;
	posicao_grafico_umidade = 0;
	posicao_grafico_tempSolo = 0;
	posicao_grafico_alimentacao = 0;
	posicao_grafico_energia = 0;
	posicao_grafico_gastoEnergetico = 0;
	//chart1 = NULL;
	//chart2 = NULL;
}

void GraphicsMenu::click_event_botao_grafico_tempo(const Event*, void *data) {

	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;

	if (graphics_menu->get_grafico_tempo_ativo()) { // o gráfico ativo é do tipo tempo; ao clicar no botão, desabilita o gráfico
		graphics_menu->hide_menu_graf_tempo();
		graphics_menu->hide_all_graphics();
		graphics_menu->get_led_on_graf_tempo().stash();
		graphics_menu->get_led_off_graf_tempo().unstash();
		graphics_menu->get_led_on_graf_variavel().stash();
		graphics_menu->get_led_off_graf_variavel().unstash();
		graphics_menu->init_variables();
		graphics_menu->set_chart1(NULL);
		graphics_menu->set_chart2(NULL);
	} else { // verificar se os leds de Temperatura Interna e Hidratação são acesos por padrão
		graphics_menu->hide_menu_graf_variavel();
		graphics_menu->show_menu_graf_tempo();
		graphics_menu->get_graphic_variavel()->hide();
		graphics_menu->set_grafico_variavel_ativo(false);
		graphics_menu->init_graphics();
		graphics_menu->get_led_off_graf_tempo().stash();
		graphics_menu->get_led_on_graf_tempo().unstash();
		graphics_menu->get_led_on_graf_variavel().stash();
		graphics_menu->get_led_off_graf_variavel().unstash();
	}
}

void GraphicsMenu::click_event_botao_grafico_variavel(const Event*, void *data) {

	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;

	if (graphics_menu->get_grafico_variavel_ativo()) {
		graphics_menu->hide_menu_graf_variavel(); // verificar se os leds dos botões de gráfico variável apagam
		graphics_menu->hide_menu_graf_tempo();
		//graphics_menu->hide_all_graphics();
		graphics_menu->get_graphic_variavel()->hide();
		graphics_menu->get_led_on_graf_variavel().stash();
		graphics_menu->get_led_off_graf_variavel().unstash();
		graphics_menu->get_led_on_graf_tempo().stash();
		graphics_menu->get_led_off_graf_tempo().unstash();
		//graphics_menu->init_variables();
		graphics_menu->set_grafico_variavel_ativo(false);
	} else {
		//graphics_menu->hide_menu_graf_tempo();
		graphics_menu->show_menu_graf_tempo();
		graphics_menu->show_menu_graf_variavel();
		graphics_menu->init_variables();
		graphics_menu->set_chart1(NULL);
		graphics_menu->set_chart2(NULL);
		graphics_menu->set_grafico_variavel_ativo(true);
		graphics_menu->get_led_off_graf_variavel().stash();
		graphics_menu->get_led_on_graf_variavel().unstash();
		graphics_menu->get_led_on_graf_tempo().stash();
		graphics_menu->get_led_off_graf_tempo().unstash();
		graphics_menu->hide_all_led_on();
		graphics_menu->desliga_leds_painel_tempo();
		graphics_menu->create_default_time_chart();
	}
}

void GraphicsMenu::create_default_time_chart() { // mudar nome do método; aqui se cria o gráfico padrão do tipo variável!
	// exibe gráfico padrão do tipo Variável (Temp Ar x Temp Ar)
	create_variable_chart(get_history()->get_list(History::HI_world_temperature),
			get_history()->get_list(History::HI_world_temperature), "Temp Ar", "Temp Ar", true);
	// liga os leds do gráfico exibido por padrão (Temp Ar x Temp Ar) ao clicar no botão "Variável"
	get_led_on_temp_ar().unstash();
	get_led_off_temp_ar().stash();
	get_led_on_temp_ar_v().unstash();
	get_led_off_temp_ar_v().stash();
}

// Método genérico para chamar a criação de um novo gráfico.
// chart_number indica a qual gráfico se refere:
// 1 - tempInterna, 2 - hidratacao, 3 - tempAr, 4 - umidade, 5 - tempSolo, 6 - alimentacao, 7 - energia, 8 - gastoEnergetico
// chart_position indica se o grafico não está plotado na tela (0), se está na posição superior (1) ou posição inferior (2)
void GraphicsMenu::set_chart_properties(int chart_number, int chart_position) {

	if (chart_position != 0) { // se o gráfico estiver plotado na tela
		create_time_chart(chart_number, 0); // remove o gráfico da tela
		if (chart_position == 1) { // se o gráfico está na posição superior da tela
			set_chart1(NULL);
			grafico_posicao1_ativo = false;
		} else { // se o gráfico está na posição inferior da tela
			set_chart2(NULL);
			grafico_posicao2_ativo = false;
		}
	} else { // se o gráfico não estiver plotado na tela
		if (!grafico_posicao1_ativo) { // verifica se a posição superior está vazia
			set_chart1(create_time_chart(chart_number, 1)); // plota o gráfico na posição superior
			//create_time_chart(chart_number, 1);
			grafico_posicao1_ativo = true;
		} else if (!grafico_posicao2_ativo) {
			set_chart2(create_time_chart(chart_number, 2)); // plota o gráfico na posição inferior
			//create_time_chart(chart_number, 2);
			grafico_posicao2_ativo = true;
		}
	}

}

void GraphicsMenu::create_variable_chart(History::HList *valores_vetor_x, History::HList *valores_vetor_y,
		const string &legenda_eixo_x, const string &legenda_eixo_y, bool set_eixo_x) {
	if (graphicVariavel != NULL) {
		graphicVariavel->hide();
	}
	vetor_x = valores_vetor_x;
	vetor_y = valores_vetor_y;
	legenda_x = legenda_eixo_x;
	legenda_y = legenda_eixo_y;

	graphicVariavel = new Graphics(option_frame_np, false);
	graphicVariavel->update_chart_data(vetor_x, vetor_y, history);
	graphicVariavel->set_Position_Graphic(0.2, 0.6);
	graphicVariavel->set_scale(1.2);
	graphicVariavel->set_Titulo_Grafico(legenda_x + " x " + legenda_y);
	graphicVariavel->set_Titulo_EixoX(legenda_x);
	graphicVariavel->set_Titulo_EixoY(legenda_y);
	graphicVariavel->create_Graphic();
	if (set_eixo_x) {
		desliga_leds_painel_variavel();
	} else {
		desliga_leds_painel_tempo();
	}
}


// Indica se o gráfico selecionado será inserido ou removido da tela.
// chart_number é o número do gráfico selecionado pelo usuário através do clique no botão
// chart_position indica se o grafico será removido da tela (0), se será plotado na posição superior (1) ou inferior (2)
PT(Graphics) GraphicsMenu::create_time_chart(int chart_number, int chart_position) {

	if (chart_number == 1) { // Temperatura Interna
		posicao_grafico_tempInterna = chart_position; // atualiza a posição do gráfico
		if (chart_position != 0) { // se o gráfico não estiver plotado, ele é criado
			get_led_on_temp_interna().unstash();
			get_led_off_temp_interna().stash();
			return novo_grafico1_TempInterna();
		} else { // se o gráfico estiver plotado, ele é removido
			get_graphic()->hide();
			get_led_on_temp_interna().stash();
			get_led_off_temp_interna().unstash();
			return NULL;
		}
	} else if (chart_number == 2) { // Hidratacao
		posicao_grafico_hidratacao = chart_position;
		if (chart_position != 0) {
			get_led_on_hidratacao().unstash();
			get_led_off_hidratacao().stash();
			return novo_grafico2_Hidratacao();
		} else {
			get_graphic2()->hide();
			get_led_on_hidratacao().stash();
			get_led_off_hidratacao().unstash();
			return NULL;
		}
	} else if (chart_number == 3) { // Temperatura do Ar
		posicao_grafico_tempAr = chart_position;
		if (chart_position != 0) {
			get_led_on_temp_ar().unstash();
			get_led_off_temp_ar().stash();
			return novo_grafico3_TempAr();
		} else {
			get_graphic3()->hide();
			get_led_on_temp_ar().stash();
			get_led_off_temp_ar().unstash();
			return NULL;
		}
	} else if (chart_number == 4) { // Umidade
		posicao_grafico_umidade = chart_position;
		if (chart_position != 0) {
			get_led_on_umidade().unstash();
			get_led_off_umidade().stash();
			return novo_grafico4_Umidade();
		} else {
			get_graphic4()->hide();
			get_led_on_umidade().stash();
			get_led_off_umidade().unstash();
			return NULL;
		}
	} else if (chart_number == 5) { // Temperatura do Solo
		posicao_grafico_tempSolo = chart_position;
		if (chart_position != 0) {
			get_led_on_temp_solo().unstash();
			get_led_off_temp_solo().stash();
			return novo_grafico5_TempSolo();
		} else {
			get_graphic5()->hide();
			get_led_on_temp_solo().stash();
			get_led_off_temp_solo().unstash();
			return NULL;
		}
	} else if (chart_number == 6) { // Alimentação
		posicao_grafico_alimentacao = chart_position;
		if (chart_position != 0) {
			get_led_on_alimentacao().unstash();
			get_led_off_alimentacao().stash();
			return novo_grafico6_Alimentacao();
		} else {
			get_graphic6()->hide();
			get_led_on_alimentacao().stash();
			get_led_off_alimentacao().unstash();
			return NULL;
		}
	} else if (chart_number == 7) { // Energia
		posicao_grafico_energia = chart_position;
		if (chart_position != 0) {
			get_led_on_energia().unstash();
			get_led_off_energia().stash();
			return novo_grafico7_Energia();
		} else {
			get_graphic7()->hide();
			get_led_on_energia().stash();
			get_led_off_energia().unstash();
			return NULL;
		}
	} else if (chart_number == 8) { // Gasto Energético
		posicao_grafico_gastoEnergetico = chart_position;
		if (chart_position != 0) {
			get_led_on_gasto_energetico().unstash();
			get_led_off_gasto_energetico().stash();
			return novo_grafico8_GastoEnergetico();
		} else {
			get_graphic8()->hide();
			get_led_on_gasto_energetico().stash();
			get_led_off_gasto_energetico().unstash();
			return NULL;
		}
	}
}

// Botões exibidos nos gráficos dos tipos Tempo ou Variável (eixo Y)

void GraphicsMenu::click_event_botao_grafico_tempInterna(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(1, posicao_grafico_tempInterna);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_player_temperature), graphics_menu->get_legenda_x(), "Temp Interna", false);
		graphics_menu->get_led_on_temp_interna().unstash();
		graphics_menu->get_led_off_temp_interna().stash();
	}
}

void GraphicsMenu::click_event_botao_grafico_hidratacao(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(2, posicao_grafico_hidratacao);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_player_hydration), graphics_menu->get_legenda_x(), "Hidratação", false);
		graphics_menu->get_led_on_hidratacao().unstash();
		graphics_menu->get_led_off_hidratacao().stash();
	}
}

void GraphicsMenu::click_event_botao_grafico_tempAr(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(3, posicao_grafico_tempAr);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_world_temperature), graphics_menu->get_legenda_x(), "Temp Ar", false);
		graphics_menu->get_led_on_temp_ar().unstash();
		graphics_menu->get_led_off_temp_ar().stash();
	}
}

void GraphicsMenu::click_event_botao_grafico_umidade(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(4, posicao_grafico_umidade);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_world_humidity), graphics_menu->get_legenda_x(), "Umidade", false);
		graphics_menu->get_led_on_umidade().unstash();
		graphics_menu->get_led_off_umidade().stash();
	}
}

void GraphicsMenu::click_event_botao_grafico_tempSolo(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(5, posicao_grafico_tempSolo);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_soil_temperature), graphics_menu->get_legenda_x(), "Temp Solo", false);
		graphics_menu->get_led_on_temp_solo().unstash();
		graphics_menu->get_led_off_temp_solo().stash();
	}
}

void GraphicsMenu::click_event_botao_grafico_alimentacao(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(6, posicao_grafico_alimentacao);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_feeding), graphics_menu->get_legenda_x(), "Alimentacao", false);
		graphics_menu->get_led_on_alimentacao().unstash();
		graphics_menu->get_led_off_alimentacao().stash();
	}
}

void GraphicsMenu::click_event_botao_grafico_energia(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(7, posicao_grafico_energia);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_energy), graphics_menu->get_legenda_x(), "Energia", false);
		graphics_menu->get_led_on_energia().unstash();
		graphics_menu->get_led_off_energia().stash();
	}
}

void GraphicsMenu::click_event_botao_grafico_gastoEnergetico(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_grafico_tempo_ativo()) {
		graphics_menu->set_chart_properties(8, posicao_grafico_gastoEnergetico);
	} else {
		graphics_menu->create_variable_chart(graphics_menu->get_vetor_x(), graphics_menu->get_history()->
				get_list(History::HI_total_energy_cost), graphics_menu->get_legenda_x(), "Gasto Energético", false);
		graphics_menu->get_led_on_gasto_energetico().unstash();
		graphics_menu->get_led_off_gasto_energetico().stash();
	}
}

// Botões exibidos somente nos gráficos do tipo Variável (eixo X)

void GraphicsMenu::click_event_botao_grafico_tempInterna_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_player_temperature),
			graphics_menu->get_vetor_y(), "Temp Interna", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_temp_interna_v().unstash();
	graphics_menu->get_led_off_temp_interna_v().stash();
}

void GraphicsMenu::click_event_botao_grafico_hidratacao_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_player_hydration),
			graphics_menu->get_vetor_y(), "Hidratação", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_hidratacao_v().unstash();
	graphics_menu->get_led_off_hidratacao_v().stash();
}

void GraphicsMenu::click_event_botao_grafico_tempAr_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_world_temperature),
			graphics_menu->get_vetor_y(), "Temp Ar", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_temp_ar_v().unstash();
	graphics_menu->get_led_off_temp_ar_v().stash();
}

void GraphicsMenu::click_event_botao_grafico_umidade_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_world_humidity),
			graphics_menu->get_vetor_y(), "Umidade", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_umidade_v().unstash();
	graphics_menu->get_led_off_umidade_v().stash();
}

void GraphicsMenu::click_event_botao_grafico_tempSolo_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_soil_temperature),
			graphics_menu->get_vetor_y(), "Temp Solo", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_temp_solo_v().unstash();
	graphics_menu->get_led_off_temp_solo_v().stash();
}

void GraphicsMenu::click_event_botao_grafico_alimentacao_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_feeding),
			graphics_menu->get_vetor_y(), "Alimentação", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_alimentacao_v().unstash();
	graphics_menu->get_led_off_alimentacao_v().stash();
}

void GraphicsMenu::click_event_botao_grafico_energia_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_energy),
			graphics_menu->get_vetor_y(), "Energia", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_energia_v().unstash();
	graphics_menu->get_led_off_energia_v().stash();
}

void GraphicsMenu::click_event_botao_grafico_gastoEnergetico_v(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	graphics_menu->create_variable_chart(graphics_menu->get_history()->get_list(History::HI_total_energy_cost),
			graphics_menu->get_vetor_y(), "Gasto Energético", graphics_menu->get_legenda_y(), true);
	graphics_menu->get_led_on_gasto_energetico_v().unstash();
	graphics_menu->get_led_off_gasto_energetico_v().stash();
}

void GraphicsMenu::click_event_btn_previous_page_chart1(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_current_day() > 1) {
		graphics_menu->set_current_day(graphics_menu->get_current_day() - 1);
		graphics_menu->update_chart_page();
	}
}

void GraphicsMenu::click_event_btn_next_page_chart1(const Event*, void *data) {
	PT(GraphicsMenu) graphics_menu = (PT(GraphicsMenu)) (GraphicsMenu*) data;
	if (graphics_menu->get_current_day() < graphics_menu->get_elapsed_days()) {
		graphics_menu->set_current_day(graphics_menu->get_current_day() + 1);
		graphics_menu->update_chart_page();
	}
}

PT(Graphics) GraphicsMenu::get_chart1() {
	return chart1;
}

PT(Graphics) GraphicsMenu::get_chart2() {
	return chart2;
}

void GraphicsMenu::set_chart1(PT(Graphics) cht1) {
	chart1 = cht1;
}

void GraphicsMenu::set_chart2(PT(Graphics) cht2) {
	chart2 = cht2;
}

bool GraphicsMenu::get_grafico_tempo_ativo() {
	return grafico_tempo_ativo;
}

bool GraphicsMenu::get_grafico_variavel_ativo() {
	return grafico_variavel_ativo;
}

void GraphicsMenu::set_grafico_variavel_ativo(bool graf_variavel_ativo) {
	grafico_variavel_ativo = graf_variavel_ativo;
}

PT(History) GraphicsMenu::get_history() {
	return history;
}

PT(PGButton) GraphicsMenu::get_btn_graf_tempo() {
	return btn_graf_tempo;
}

NodePath GraphicsMenu::get_led_off_graf_tempo() {
	return led_off_graf_tempo;
}

NodePath GraphicsMenu::get_led_on_graf_tempo() {
	return led_on_graf_tempo;
}

PT(PGButton) GraphicsMenu::get_btn_graf_variavel() {
	return btn_graf_variavel;
}

NodePath GraphicsMenu::get_led_off_graf_variavel() {
	return led_off_graf_variavel;
}

NodePath GraphicsMenu::get_led_on_graf_variavel() {
	return led_on_graf_variavel;
}

PT(PGButton) GraphicsMenu::get_btn_temp_interna() {
	return btn_temp_interna;
}

NodePath GraphicsMenu::get_led_off_temp_interna() {
	return led_off_temp_interna;
}

NodePath GraphicsMenu::get_led_on_temp_interna() {
	return led_on_temp_interna;
}

PT(PGButton) GraphicsMenu::get_btn_hidratacao() {
	return btn_hidratacao;
}

NodePath GraphicsMenu::get_led_off_hidratacao() {
	return led_off_hidratacao;
}

NodePath GraphicsMenu::get_led_on_hidratacao() {
	return led_on_hidratacao;
}

PT(PGButton) GraphicsMenu::get_btn_temp_ar() {
	return btn_temp_ar;
}

NodePath GraphicsMenu::get_led_off_temp_ar() {
	return led_off_temp_ar;
}

NodePath GraphicsMenu::get_led_on_temp_ar() {
	return led_on_temp_ar;
}

PT(PGButton) GraphicsMenu::get_btn_umidade() {
	return btn_umidade;
}

NodePath GraphicsMenu::get_led_off_umidade() {
	return led_off_umidade;
}

NodePath GraphicsMenu::get_led_on_umidade() {
	return led_on_umidade;
}

PT(PGButton) GraphicsMenu::get_btn_temp_solo() {
	return btn_temp_solo;
}

NodePath GraphicsMenu::get_led_off_temp_solo() {
	return led_off_temp_solo;
}

NodePath GraphicsMenu::get_led_on_temp_solo() {
	return led_on_temp_solo;
}

PT(PGButton) GraphicsMenu::get_btn_alimentacao() {
	return btn_alimentacao;
}

NodePath GraphicsMenu::get_led_off_alimentacao() {
	return led_off_alimentacao;
}

NodePath GraphicsMenu::get_led_on_alimentacao() {
	return led_on_alimentacao;
}

PT(PGButton) GraphicsMenu::get_btn_energia() {
	return btn_energia;
}

NodePath GraphicsMenu::get_led_off_energia() {
	return led_off_energia;
}

NodePath GraphicsMenu::get_led_on_energia() {
	return led_on_energia;
}

PT(PGButton) GraphicsMenu::get_btn_gasto_energetico() {
	return btn_gasto_energetico;
}

NodePath GraphicsMenu::get_led_off_gasto_energetico() {
	return led_off_gasto_energetico;
}

NodePath GraphicsMenu::get_led_on_gasto_energetico() {
	return led_on_gasto_energetico;
}

PT(PGButton) GraphicsMenu::get_btn_temp_interna_v() {
	return btn_temp_interna_v;
}

NodePath GraphicsMenu::get_led_off_temp_interna_v() {
	return led_off_temp_interna_v;
}

NodePath GraphicsMenu::get_led_on_temp_interna_v() {
	return led_on_temp_interna_v;
}

PT(PGButton) GraphicsMenu::get_btn_hidratacao_v() {
	return btn_hidratacao_v;
}

NodePath GraphicsMenu::get_led_off_hidratacao_v() {
	return led_off_hidratacao_v;
}

NodePath GraphicsMenu::get_led_on_hidratacao_v() {
	return led_on_hidratacao_v;
}

PT(PGButton) GraphicsMenu::get_btn_temp_ar_v() {
	return btn_temp_ar_v;
}

NodePath GraphicsMenu::get_led_off_temp_ar_v() {
	return led_off_temp_ar_v;
}

NodePath GraphicsMenu::get_led_on_temp_ar_v() {
	return led_on_temp_ar_v;
}

PT(PGButton) GraphicsMenu::get_btn_umidade_v() {
	return btn_umidade_v;
}

NodePath GraphicsMenu::get_led_off_umidade_v() {
	return led_off_umidade_v;
}

NodePath GraphicsMenu::get_led_on_umidade_v() {
	return led_on_umidade_v;
}

PT(PGButton) GraphicsMenu::get_btn_temp_solo_v() {
	return btn_temp_solo_v;
}

NodePath GraphicsMenu::get_led_off_temp_solo_v() {
	return led_off_temp_solo_v;
}

NodePath GraphicsMenu::get_led_on_temp_solo_v() {
	return led_on_temp_solo_v;
}

PT(PGButton) GraphicsMenu::get_btn_alimentacao_v() {
	return btn_alimentacao_v;
}

NodePath GraphicsMenu::get_led_off_alimentacao_v() {
	return led_off_alimentacao_v;
}

NodePath GraphicsMenu::get_led_on_alimentacao_v() {
	return led_on_alimentacao_v;
}

PT(PGButton) GraphicsMenu::get_btn_energia_v() {
	return btn_energia_v;
}

NodePath GraphicsMenu::get_led_off_energia_v() {
	return led_off_energia_v;
}

NodePath GraphicsMenu::get_led_on_energia_v() {
	return led_on_energia_v;
}

PT(PGButton) GraphicsMenu::get_btn_gasto_energetico_v() {
	return btn_gasto_energetico_v;
}

NodePath GraphicsMenu::get_led_off_gasto_energetico_v() {
	return led_off_gasto_energetico_v;
}

NodePath GraphicsMenu::get_led_on_gasto_energetico_v() {
	return led_on_gasto_energetico_v;
}

NodePath GraphicsMenu::get_option_frame_np() {
	return option_frame_np;
}

NodePath GraphicsMenu::get_grafico_variavel_frame_np() {
	return grafico_variavel_frame_np;
}

PT(Graphics) GraphicsMenu::get_graphic_variavel() {
	return graphicVariavel;
}

void GraphicsMenu::set_graphic_variavel(PT(Graphics) graphic) {
	graphicVariavel = graphic;
}

PT(Graphics) GraphicsMenu::get_graphic() {
	return graphic;
}

PT(Graphics) GraphicsMenu::get_graphic2() {
	return graphic2;
}

PT(Graphics) GraphicsMenu::get_graphic3() {
	return graphic3;
}

PT(Graphics) GraphicsMenu::get_graphic4() {
	return graphic4;
}

PT(Graphics) GraphicsMenu::get_graphic5() {
	return graphic5;
}

PT(Graphics) GraphicsMenu::get_graphic6() {
	return graphic6;
}

PT(Graphics) GraphicsMenu::get_graphic7() {
	return graphic7;
}

PT(Graphics) GraphicsMenu::get_graphic8() {
	return graphic8;
}

History::HList* GraphicsMenu::get_vetor_x() {
	return vetor_x;
}

void GraphicsMenu::set_vetor_x(History::HList* vetor) {
	vetor_x = vetor;
}

History::HList* GraphicsMenu::get_vetor_y() {
	return vetor_y;
}

void GraphicsMenu::set_vetor_y(History::HList* vetor) {
	vetor_y = vetor;
}

string GraphicsMenu::get_legenda_x() {
	return legenda_x;
}

void GraphicsMenu::set_legenda_x(string legenda) {
	legenda_x = legenda;
}

string GraphicsMenu::get_legenda_y() {
	return legenda_y;
}

void GraphicsMenu::set_legenda_y(string legenda) {
	legenda_y = legenda;
}

double GraphicsMenu::get_limite_superior_x() {
	return limite_superior_x;
}

void GraphicsMenu::set_limite_superior_x(double limite) {
	limite_superior_x = limite;
}

double GraphicsMenu::get_limite_inferior_x() {
	return limite_inferior_x;
}

void GraphicsMenu::set_limite_inferior_x(double limite) {
	limite_inferior_x = limite;
}

double GraphicsMenu::get_limite_superior_y() {
	return limite_superior_y;
}

void GraphicsMenu::set_limite_superior_y(double limite) {
	limite_superior_y = limite;
}

double GraphicsMenu::get_limite_inferior_y() {
	return limite_inferior_y;
}

void GraphicsMenu::set_limite_inferior_y(double limite) {
	limite_inferior_y = limite;
}

double GraphicsMenu::get_tamanho_vetor_x() {
	return tamanho_vetor_x;
}

void GraphicsMenu::set_tamanho_vetor_x(double tamanho) {
	tamanho_vetor_x = tamanho;
}

double GraphicsMenu::get_tamanho_vetor_y() {
	return tamanho_vetor_y;
}

void GraphicsMenu::set_tamanho_vetor_y(double tamanho) {
	tamanho_vetor_y = tamanho;
}

int GraphicsMenu::get_current_day() {
	return current_day;
}

void GraphicsMenu::set_current_day(int day) {
	current_day = day;
	//cout << "\n............ Current Day: " << current_day;
}

PT(PGButton) GraphicsMenu::get_btn_previous_page_chart1() {
	return btn_previous_page_chart1;
}

PT(PGButton) GraphicsMenu::get_btn_next_page_chart1() {
	return btn_next_page_chart1;
}

History::HistoryItem GraphicsMenu::get_item_chart1() {
	return item_chart1;
}

History::HistoryItem GraphicsMenu::get_item_chart2() {
	return item_chart2;
}

// Monta a parte do topo onde tem escrito "Tipo do Grafico" (label, leds e botões)
void GraphicsMenu::make_tipo_graf(NodePath menu_frame_np) {
	make_txt_tipo_graf(menu_frame_np);

	make_btn_graf_tempo(menu_frame_np);

	make_btn_graf_variavel(menu_frame_np);
}

void GraphicsMenu::make_txt_tipo_graf(NodePath menu_frame_np) {
	txt_tipo_graf = new TextNode("txt_tipo_graf");
	txt_tipo_graf->set_text("Tipo do gráfico");
	label_txt_tipo_graf = menu_frame_np.attach_new_node(txt_tipo_graf);
	label_txt_tipo_graf.set_pos(0.04, 0.0, 1.90);
	label_txt_tipo_graf.set_scale(0.06);
	label_txt_tipo_graf.set_color(0.0, 0.0, 0.0, 1,0);
	label_txt_tipo_graf.stash();
}

void GraphicsMenu::make_btn_graf_tempo(NodePath menu_frame_np) {
	//BOTAO PARA VER OS GRAFICOS DE TEMPO.
	btn_graf_tempo = new PGButton("btn_graf_tempo");
	btn_graf_tempo->setup("Tempo", 0.1);
	np_btn_graf_tempo = menu_frame_np.attach_new_node(btn_graf_tempo);
	np_btn_graf_tempo.set_scale(0.05);
	np_btn_graf_tempo.set_pos(0.09, 0.0, 1.80);
	np_btn_graf_tempo.stash();
	led_off_graf_tempo = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_graf_tempo.reparent_to(menu_frame_np);
	led_off_graf_tempo.set_scale(0.004);
	led_off_graf_tempo.set_pos(0.32, 0.0, 1.82);
	led_off_graf_tempo.stash();
	led_on_graf_tempo = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_graf_tempo.reparent_to(menu_frame_np);
	led_on_graf_tempo.set_scale(0.004);
	led_on_graf_tempo.set_pos(0.32, 0.0, 1.82);
	led_on_graf_tempo.stash();
}

void GraphicsMenu::make_btn_graf_variavel(NodePath menu_frame_np) {
	//BOTAO PARA VER OS GRAFICOS DE VARIAVEL.
	btn_graf_variavel = new PGButton("btn_graf_variavel");
	btn_graf_variavel->setup("Variável", 0.1);
	np_btn_graf_variavel = menu_frame_np.attach_new_node(btn_graf_variavel);
	np_btn_graf_variavel.set_scale(0.05);
	np_btn_graf_variavel.set_pos(0.06, 0.0, 1.68);
	np_btn_graf_variavel.stash();
	led_off_graf_variavel = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_graf_variavel.reparent_to(menu_frame_np);
	led_off_graf_variavel.set_scale(0.004);
	led_off_graf_variavel.set_pos(0.32, 0.0, 1.70);
	led_off_graf_variavel.stash();
	led_on_graf_variavel = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_graf_variavel.reparent_to(menu_frame_np);
	led_on_graf_variavel.set_scale(0.004);
	led_on_graf_variavel.set_pos(0.32, 0.0, 1.70);
	led_on_graf_variavel.stash();
}

//------------
//Aqui sao setadas as propriedades dos botes da barra lateral
//1 - Inicia o botão e seta a imagem nele.
//2 - Inicia o led que fica ao lado do botão.
//Essa sequencia serve para os 8 botões.
//------------
void GraphicsMenu::make_menu_graf_tempo(NodePath menu_frame_np) {
	make_btn_temp_interna(menu_frame_np);

	make_btn_hidratacao(menu_frame_np);

	make_btn_temp_ar(menu_frame_np);

	make_btn_umidade(menu_frame_np);

	make_btn_temp_solo(menu_frame_np);

	make_btn_alimentacao(menu_frame_np);

	make_btn_energia(menu_frame_np);

	make_btn_gasto_energetico(menu_frame_np);
}

void GraphicsMenu::make_btn_temp_interna(NodePath menu_frame_np) {
	btn_temp_interna = new PGButton("btn_temp_interna");
	btn_temp_interna->setup("", 0.1);
	np_btn_temp_interna = menu_frame_np.attach_new_node(btn_temp_interna);
	np_btn_temp_interna.set_scale(0.03);
	np_btn_temp_interna.set_pos(0.08, 0.0, 1.52);
	np_btn_temp_interna.stash();
	img_btn_temp_interna = ImageRepository::get_instance()->get_image("modeloTemperatura");
	img_btn_temp_interna.reparent_to(menu_frame_np);
	img_btn_temp_interna.set_scale(0.008);
	img_btn_temp_interna.set_pos(0.08, 0.0, 1.52);
	img_btn_temp_interna.stash();
	hint_btn_temp_interna = new Hint(menu_frame_np, btn_temp_interna.p(), img_btn_temp_interna, "hint_btn_temp_interna", "Temperatura Interna");
	led_off_temp_interna = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_interna.reparent_to(menu_frame_np);
	led_off_temp_interna.set_scale(0.0034);
	led_off_temp_interna.set_pos(0.17, 0.0, 1.48);
	led_off_temp_interna.stash();
	led_on_temp_interna = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_interna.reparent_to(menu_frame_np);
	led_on_temp_interna.set_scale(0.0034);
	led_on_temp_interna.set_pos(0.17, 0.0, 1.48);
	led_on_temp_interna.stash();
	btn_temp_interna->setup(img_btn_temp_interna);
	btn_temp_interna->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_hidratacao(NodePath menu_frame_np) {
	btn_hidratacao = new PGButton("btn_hidratacao");
	btn_hidratacao->setup("", 0.1);
	np_btn_hidratacao = menu_frame_np.attach_new_node(btn_hidratacao);
	np_btn_hidratacao.set_scale(0.03);
	np_btn_hidratacao.set_pos(0.26, 0.0, 1.52);
	np_btn_hidratacao.stash();
	img_btn_hidratacao = ImageRepository::get_instance()->get_image("modeloHidratacao");
	img_btn_hidratacao.reparent_to(menu_frame_np);
	img_btn_hidratacao.set_scale(0.008);
	img_btn_hidratacao.set_pos(0.26, 0.0, 1.52);
	img_btn_hidratacao.stash();
	hint_btn_hidratacao = new Hint(menu_frame_np, btn_hidratacao.p(), img_btn_hidratacao, "hint_btn_hidratacao", "Hidratação");
	led_off_hidratacao = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_hidratacao.reparent_to(menu_frame_np);
	led_off_hidratacao.set_scale(0.0034);
	led_off_hidratacao.set_pos(0.35, 0.0, 1.48);
	led_off_hidratacao.stash();
	led_on_hidratacao = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_hidratacao.reparent_to(menu_frame_np);
	led_on_hidratacao.set_scale(0.0034);
	led_on_hidratacao.set_pos(0.35, 0.0, 1.48);
	led_on_hidratacao.stash();
	btn_hidratacao->setup(img_btn_hidratacao);
	btn_hidratacao->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_temp_ar(NodePath menu_frame_np) {
	btn_temp_ar = new PGButton("btn_temp_ar");
	btn_temp_ar->setup("", 0.1);
	np_btn_temp_ar = menu_frame_np.attach_new_node(btn_temp_ar);
	np_btn_temp_ar.set_scale(0.03);
	np_btn_temp_ar.set_pos(0.08, 0.0, 1.30);
	np_btn_temp_ar.stash();
	img_btn_temp_ar = ImageRepository::get_instance()->get_image("mundo_temp2");
	img_btn_temp_ar.reparent_to(menu_frame_np);
	img_btn_temp_ar.set_scale(0.006);
	img_btn_temp_ar.set_pos(0.08, 0.0, 1.30);
	img_btn_temp_ar.stash();
	hint_btn_temp_ar = new Hint(menu_frame_np, btn_temp_ar.p(), img_btn_temp_ar, "hint_btn_temp_ar", "Temperatura do Ar");
	led_off_temp_ar = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_ar.reparent_to(menu_frame_np);
	led_off_temp_ar.set_scale(0.0034);
	led_off_temp_ar.set_pos(0.17, 0.0, 1.26);
	led_off_temp_ar.stash();
	led_on_temp_ar = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_ar.reparent_to(menu_frame_np);
	led_on_temp_ar.set_scale(0.0034);
	led_on_temp_ar.set_pos(0.17, 0.0, 1.26);
	led_on_temp_ar.stash();
	btn_temp_ar->setup(img_btn_temp_interna);
	btn_temp_ar->set_frame(-1.6 , 1.6 , -2.0, 2.0);
}

void GraphicsMenu::make_btn_umidade(NodePath menu_frame_np) {
	btn_umidade = new PGButton("btn_umidade");
	btn_umidade->setup("", 0.1);
	np_btn_umidade = menu_frame_np.attach_new_node(btn_umidade);
	np_btn_umidade.set_scale(0.03);
	np_btn_umidade.set_pos(0.26, 0.0, 1.30);
	np_btn_umidade.stash();
	img_btn_umidade = ImageRepository::get_instance()->get_image("mundo_umi");
	img_btn_umidade.reparent_to(menu_frame_np);
	img_btn_umidade.set_scale(0.005);
	img_btn_umidade.set_pos(0.26, 0.0, 1.30);
	img_btn_umidade.stash();
	hint_btn_umidade = new Hint(menu_frame_np, btn_umidade.p(), img_btn_umidade, "hint_btn_umidade", "Umidade do Ar");
	led_off_umidade = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_umidade.reparent_to(menu_frame_np);
	led_off_umidade.set_scale(0.0034);
	led_off_umidade.set_pos(0.35, 0.0, 1.26);
	led_off_umidade.stash();
	led_on_umidade = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_umidade.reparent_to(menu_frame_np);
	led_on_umidade.set_scale(0.0034);
	led_on_umidade.set_pos(0.35, 0.0, 1.26);
	led_on_umidade.stash();
	btn_umidade->setup(img_btn_hidratacao);
	btn_umidade->set_frame(-1.6 , 1.6 , -2.0, 2.0);
}

void GraphicsMenu::make_btn_temp_solo(NodePath menu_frame_np) {
	btn_temp_solo = new PGButton("btn_temp_solo");
	btn_temp_solo->setup("", 0.1);
	np_btn_temp_solo = menu_frame_np.attach_new_node(btn_temp_solo);
	np_btn_temp_solo.set_scale(0.03);
	np_btn_temp_solo.set_pos(0.08, 0.0, 1.08);
	np_btn_temp_solo.stash();
	img_btn_temp_solo = ImageRepository::get_instance()->get_image("mundo_temp3");
	img_btn_temp_solo.reparent_to(menu_frame_np);
	img_btn_temp_solo.set_scale(0.006);
	img_btn_temp_solo.set_pos(0.08, 0.0, 1.08);
	img_btn_temp_solo.stash();
	hint_btn_temp_solo = new Hint(menu_frame_np, btn_temp_solo.p(), img_btn_temp_solo, "hint_btn_temp_solo", "Temperatura do Solo");
	led_off_temp_solo = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_solo.reparent_to(menu_frame_np);
	led_off_temp_solo.set_scale(0.0034);
	led_off_temp_solo.set_pos(0.17, 0.0, 1.04);
	led_off_temp_solo.stash();
	led_on_temp_solo = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_solo.reparent_to(menu_frame_np);
	led_on_temp_solo.set_scale(0.0034);
	led_on_temp_solo.set_pos(0.17, 0.0, 1.04);
	led_on_temp_solo.stash();
	btn_temp_solo->setup(img_btn_temp_solo);
	btn_temp_solo->set_frame(-1.6 , 1.6 , -2.0, 2.0);
}

void GraphicsMenu::make_btn_alimentacao(NodePath menu_frame_np) {
	btn_alimentacao = new PGButton("btn_alimentacao");
	btn_alimentacao->setup("", 0.1);
	np_btn_alimentacao = menu_frame_np.attach_new_node(btn_alimentacao);
	np_btn_alimentacao.set_scale(0.03);
	np_btn_alimentacao.set_pos(0.26, 0.0, 1.08);
	np_btn_alimentacao.stash();
	img_btn_alimentacao = ImageRepository::get_instance()->get_image("modeloNutricional");
	img_btn_alimentacao.reparent_to(menu_frame_np);
	img_btn_alimentacao.set_scale(0.008);
	img_btn_alimentacao.set_pos(0.26, 0.0, 1.08);
	img_btn_alimentacao.stash();
	hint_btn_alimentacao = new Hint(menu_frame_np, btn_alimentacao.p(), img_btn_alimentacao, "hint_btn_alimentacao", "Alimentação");
	led_off_alimentacao = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_alimentacao.reparent_to(menu_frame_np);
	led_off_alimentacao.set_scale(0.0034);
	led_off_alimentacao.set_pos(0.35, 0.0, 1.04);
	led_off_alimentacao.stash();
	led_on_alimentacao = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_alimentacao.reparent_to(menu_frame_np);
	led_on_alimentacao.set_scale(0.0034);
	led_on_alimentacao.set_pos(0.35, 0.0, 1.04);
	led_on_alimentacao.stash();
	btn_alimentacao->setup(img_btn_alimentacao);
	btn_alimentacao->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_energia(NodePath menu_frame_np) {
	btn_energia = new PGButton("btn_energia");
	btn_energia->setup("", 0.1);
	np_btn_energia = menu_frame_np.attach_new_node(btn_energia);
	np_btn_energia.set_scale(0.03);
	np_btn_energia.set_pos(0.08, 0.0, 0.86);
	np_btn_energia.stash();
	img_btn_energia = ImageRepository::get_instance()->get_image("modeloEnergia");
	img_btn_energia.reparent_to(menu_frame_np);
	img_btn_energia.set_scale(0.008);
	img_btn_energia.set_pos(0.08, 0.0, 0.86);
	img_btn_energia.stash();
	hint_btn_energia = new Hint(menu_frame_np, btn_energia.p(), img_btn_energia, "hint_btn_energia", "Energia");
	led_off_energia = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_energia.reparent_to(menu_frame_np);
	led_off_energia.set_scale(0.0034);
	led_off_energia.set_pos(0.17, 0.0, 0.82);
	led_off_energia.stash();
	led_on_energia = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_energia.reparent_to(menu_frame_np);
	led_on_energia.set_scale(0.0034);
	led_on_energia.set_pos(0.17, 0.0, 0.82);
	led_on_energia.stash();
	btn_energia->setup(img_btn_energia);
	btn_energia->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_gasto_energetico(NodePath menu_frame_np) {
	btn_gasto_energetico = new PGButton("btn_gasto_energetico");
	btn_gasto_energetico->setup("", 0.1);
	np_btn_gasto_energetico = menu_frame_np.attach_new_node(btn_gasto_energetico);
	np_btn_gasto_energetico.set_scale(0.03);
	np_btn_gasto_energetico.set_pos(0.26, 0.0, 0.86);
	np_btn_gasto_energetico.stash();
	img_btn_gasto_energetico = ImageRepository::get_instance()->get_image("modeloGatoEnergetico");
	img_btn_gasto_energetico.reparent_to(menu_frame_np);
	img_btn_gasto_energetico.set_scale(0.008);
	img_btn_gasto_energetico.set_pos(0.26, 0.0, 0.86);
	img_btn_gasto_energetico.stash();
	hint_btn_gasto_energetico = new Hint(menu_frame_np, btn_gasto_energetico.p(), img_btn_gasto_energetico, "hint_btn_gasto_energetico", "Gasto Energético");
	led_off_gasto_energetico = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_gasto_energetico.reparent_to(menu_frame_np);
	led_off_gasto_energetico.set_scale(0.0034);
	led_off_gasto_energetico.set_pos(0.35, 0.0, 0.82);
	led_off_gasto_energetico.stash();
	led_on_gasto_energetico = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_gasto_energetico.reparent_to(menu_frame_np);
	led_on_gasto_energetico.set_scale(0.0034);
	led_on_gasto_energetico.set_pos(0.35, 0.0, 0.82);
	led_on_gasto_energetico.stash();
	btn_gasto_energetico->setup(img_btn_gasto_energetico);
	btn_gasto_energetico->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_menu_graf_variavel() {
	make_btn_temp_interna_v();

	make_btn_hidratacao_v();

	make_btn_temp_ar_v();

	make_btn_umidade_v();

	make_btn_temp_solo_v();

	make_btn_alimentacao_v();

	make_btn_energia_v();

	make_btn_gasto_energetico_v();
}

void GraphicsMenu::make_btn_temp_interna_v() {
	btn_temp_interna_v = new PGButton("btn_temp_interna_v");
	btn_temp_interna_v->setup("", 0.1);
	np_btn_temp_interna_v = grafico_variavel_frame_np.attach_new_node(btn_temp_interna_v);
	np_btn_temp_interna_v.set_scale(0.009);
	np_btn_temp_interna_v.set_pos(0.1, 0.0, 0.12);
	//np_btn_temp_interna_v.stash();
	img_btn_temp_interna_v = ImageRepository::get_instance()->get_image("modeloTemperatura");
	img_btn_temp_interna_v.reparent_to(grafico_variavel_frame_np);
	img_btn_temp_interna_v.set_scale(0.009);
	img_btn_temp_interna_v.set_pos(0.1, 0.0, 0.12);
	//img_btn_temp_interna_v.stash();
	hint_btn_temp_interna_v = new Hint(grafico_variavel_frame_np, btn_temp_interna_v.p(), img_btn_temp_interna_v, "hint_btn_temp_interna_v", "Temperatura Interna");
	led_off_temp_interna_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_interna_v.reparent_to(grafico_variavel_frame_np);
	led_off_temp_interna_v.set_scale(0.004);
	led_off_temp_interna_v.set_pos(0.1, 0.0, 0.32);
	//led_off_temp_interna_v.stash();
	led_on_temp_interna_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_interna_v.reparent_to(grafico_variavel_frame_np);
	led_on_temp_interna_v.set_scale(0.004);
	led_on_temp_interna_v.set_pos(0.1, 0.0, 0.32);
	led_on_temp_interna_v.stash();
	btn_temp_interna_v->setup(img_btn_temp_interna_v);
	btn_temp_interna_v->set_frame(-5.0 , 5.0 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_hidratacao_v() {
	btn_hidratacao_v = new PGButton("btn_hidratacao_v");
	btn_hidratacao_v->setup("", 0.1);
	np_btn_hidratacao_v = grafico_variavel_frame_np.attach_new_node(btn_hidratacao_v);
	np_btn_hidratacao_v.set_scale(0.009);
	np_btn_hidratacao_v.set_pos(0.26, 0.0, 0.12);
	//np_btn_hidratacao_v.stash();
	img_btn_hidratacao_v = ImageRepository::get_instance()->get_image("modeloHidratacao");
	img_btn_hidratacao_v.reparent_to(grafico_variavel_frame_np);
	img_btn_hidratacao_v.set_scale(0.009);
	img_btn_hidratacao_v.set_pos(0.26, 0.0, 0.12);
	//img_btn_hidratacao_v.stash();
	hint_btn_hidratacao_v = new Hint(grafico_variavel_frame_np, btn_hidratacao_v.p(), img_btn_hidratacao_v, "hint_btn_hidratacao_v", "Hidratação");
	led_off_hidratacao_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_hidratacao_v.reparent_to(grafico_variavel_frame_np);
	led_off_hidratacao_v.set_scale(0.004);
	led_off_hidratacao_v.set_pos(0.26, 0.0, 0.32);
	//led_off_hidratacao_v.stash();
	led_on_hidratacao_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_hidratacao_v.reparent_to(grafico_variavel_frame_np);
	led_on_hidratacao_v.set_scale(0.004);
	led_on_hidratacao_v.set_pos(0.26, 0.0, 0.32);
	led_on_hidratacao_v.stash();
	btn_hidratacao_v->setup(img_btn_hidratacao_v);
	btn_hidratacao_v->set_frame(-5.0, 5.0, -10.0, 10.0);
}

void GraphicsMenu::make_btn_temp_ar_v() {
	btn_temp_ar_v = new PGButton("btn_temp_ar_v");
	btn_temp_ar_v->setup("", 0.1);
	np_btn_temp_ar_v = grafico_variavel_frame_np.attach_new_node(btn_temp_ar_v);
	np_btn_temp_ar_v.set_scale(0.009);
	np_btn_temp_ar_v.set_pos(0.42, 0.0, 0.12);
	//np_btn_temp_ar_v.stash();
	img_btn_temp_ar_v = ImageRepository::get_instance()->get_image("mundo_temp2");
	img_btn_temp_ar_v.reparent_to(grafico_variavel_frame_np);
	img_btn_temp_ar_v.set_scale(0.009);
	img_btn_temp_ar_v.set_pos(0.42, 0.0, 0.12);
	//img_btn_temp_ar_v.stash();
	hint_btn_temp_ar_v = new Hint(grafico_variavel_frame_np, btn_temp_ar_v.p(), img_btn_temp_ar_v, "hint_btn_temp_ar_v", "Temperatura do Ar");
	led_off_temp_ar_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_ar_v.reparent_to(grafico_variavel_frame_np);
	led_off_temp_ar_v.set_scale(0.004);
	led_off_temp_ar_v.set_pos(0.42, 0.0, 0.32);
	led_off_temp_ar_v.stash();
	led_on_temp_ar_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_ar_v.reparent_to(grafico_variavel_frame_np);
	led_on_temp_ar_v.set_scale(0.004);
	led_on_temp_ar_v.set_pos(0.42, 0.0, 0.32);
	//led_on_temp_ar_v.stash();
	btn_temp_ar_v->setup(img_btn_temp_ar_v);
	btn_temp_ar_v->set_frame(-8.1 , 8.1 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_umidade_v() {
	btn_umidade_v = new PGButton("btn_umidade_v");
	btn_umidade_v->setup("", 0.1);
	np_btn_umidade_v = grafico_variavel_frame_np.attach_new_node(btn_umidade_v);
	np_btn_umidade_v.set_scale(0.008);
	np_btn_umidade_v.set_pos(0.60, 0.0, 0.12);
	//botao4UmidadeAr_np.stash();
	img_btn_umidade_v = ImageRepository::get_instance()->get_image("mundo_umi");
	img_btn_umidade_v.reparent_to(grafico_variavel_frame_np);
	img_btn_umidade_v.set_scale(0.008);
	img_btn_umidade_v.set_pos(0.60, 0.0, 0.12);
	//botao4UmidadeAr_image.stash();
	hint_btn_umidade_v = new Hint(grafico_variavel_frame_np, btn_umidade_v.p(), img_btn_umidade_v, "hint_btn_umidade_v", "Umidade");
	led_off_umidade_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_umidade_v.reparent_to(grafico_variavel_frame_np);
	led_off_umidade_v.set_scale(0.004);
	led_off_umidade_v.set_pos(0.60, 0.0, 0.32);
	//botao4UmidadeAr_ledOFF.stash();
	led_on_umidade_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_umidade_v.reparent_to(grafico_variavel_frame_np);
	led_on_umidade_v.set_scale(0.004);
	led_on_umidade_v.set_pos(0.60, 0.0, 0.32);
	led_on_umidade_v.stash();
	btn_umidade_v->setup(img_btn_umidade_v);
	btn_umidade_v->set_frame(-8.8 , 8.8 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_temp_solo_v() {
	btn_temp_solo_v = new PGButton("btn_temp_solo_v");
	btn_temp_solo_v->setup("", 0.1);
	np_btn_temp_solo_v = grafico_variavel_frame_np.attach_new_node(btn_temp_solo_v);
	np_btn_temp_solo_v.set_scale(0.009);
	np_btn_temp_solo_v.set_pos(0.78, 0.0, 0.12);
	//np_btn_temp_solo_v.stash();
	img_btn_temp_solo_v = ImageRepository::get_instance()->get_image("mundo_temp3");
	img_btn_temp_solo_v.reparent_to(grafico_variavel_frame_np);
	img_btn_temp_solo_v.set_scale(0.009);
	img_btn_temp_solo_v.set_pos(0.78, 0.0, 0.12);
	//img_btn_temp_solo_v.stash();
	hint_btn_temp_solo_v = new Hint(grafico_variavel_frame_np, btn_temp_solo_v.p(), img_btn_temp_solo_v, "hint_btn_temp_solo_v", "Temperatura do Solo");
	led_off_temp_solo_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_solo_v.reparent_to(grafico_variavel_frame_np);
	led_off_temp_solo_v.set_scale(0.004);
	led_off_temp_solo_v.set_pos(0.78, 0.0, 0.32);
	//led_off_temp_solo_v.stash();
	led_on_temp_solo_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_solo_v.reparent_to(grafico_variavel_frame_np);
	led_on_temp_solo_v.set_scale(0.004);
	led_on_temp_solo_v.set_pos(0.78, 0.0, 0.32);
	led_on_temp_solo_v.stash();
	btn_temp_solo_v->setup(img_btn_temp_solo_v);
	btn_temp_solo_v->set_frame(-8.1 , 8.1 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_alimentacao_v() {
	btn_alimentacao_v = new PGButton("btn_alimentacao_v");
	btn_alimentacao_v->setup("", 0.1);
	np_btn_alimentacao_v = grafico_variavel_frame_np.attach_new_node(btn_alimentacao_v);
	np_btn_alimentacao_v.set_scale(0.009);
	np_btn_alimentacao_v.set_pos(0.94, 0.0, 0.12);
	//np_btn_alimentacao_v.stash();
	img_btn_alimentacao_v = ImageRepository::get_instance()->get_image("modeloNutricional");
	img_btn_alimentacao_v.reparent_to(grafico_variavel_frame_np);
	img_btn_alimentacao_v.set_scale(0.009);
	img_btn_alimentacao_v.set_pos(0.94, 0.0, 0.12);
	//img_btn_alimentacao_v.stash();
	hint_btn_alimentacao_v = new Hint(grafico_variavel_frame_np, btn_alimentacao_v.p(), img_btn_alimentacao_v, "hint_btn_alimentacao_v", "Alimentação");
	led_off_alimentacao_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_alimentacao_v.reparent_to(grafico_variavel_frame_np);
	led_off_alimentacao_v.set_scale(0.004);
	led_off_alimentacao_v.set_pos(0.94, 0.0, 0.32);
	//led_off_alimentacao_v.stash();
	led_on_alimentacao_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_alimentacao_v.reparent_to(grafico_variavel_frame_np);
	led_on_alimentacao_v.set_scale(0.004);
	led_on_alimentacao_v.set_pos(0.94, 0.0, 0.32);
	led_on_alimentacao_v.stash();
	btn_alimentacao_v->setup(img_btn_alimentacao_v);
	btn_alimentacao_v->set_frame(-5.0 , 5.0, -10.0, 10.0);
}

void GraphicsMenu::make_btn_energia_v() {
	btn_energia_v = new PGButton("btn_energia_v");
	btn_energia_v->setup("", 0.1);
	np_btn_energia_v = grafico_variavel_frame_np.attach_new_node(btn_energia_v);
	np_btn_energia_v.set_scale(0.009);
	np_btn_energia_v.set_pos(1.10, 0.0, 0.12);
	//np_btn_energia_v.stash();
	img_btn_energia_v = ImageRepository::get_instance()->get_image("modeloEnergia");
	img_btn_energia_v.reparent_to(grafico_variavel_frame_np);
	img_btn_energia_v.set_scale(0.009);
	img_btn_energia_v.set_pos(1.10, 0.0, 0.12);
	//img_btn_energia_v.stash();
	hint_btn_energia_v = new Hint(grafico_variavel_frame_np, btn_energia_v.p(), img_btn_energia_v, "hint_btn_energia_v", "Energia");
	led_off_energia_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_energia_v.reparent_to(grafico_variavel_frame_np);
	led_off_energia_v.set_scale(0.004);
	led_off_energia_v.set_pos(1.10, 0.0, 0.32);
	//led_off_energia_v.stash();
	led_on_energia_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_energia_v.reparent_to(grafico_variavel_frame_np);
	led_on_energia_v.set_scale(0.004);
	led_on_energia_v.set_pos(1.10, 0.0, 0.32);
	led_on_energia_v.stash();
	btn_energia_v->setup(img_btn_energia_v);
	btn_energia_v->set_frame(-5.0 , 5.0 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_gasto_energetico_v() {
	btn_gasto_energetico_v = new PGButton("btn_gasto_energetico_v");
	btn_gasto_energetico_v->setup("", 0.1);
	np_btn_gasto_energetico_v = grafico_variavel_frame_np.attach_new_node(btn_gasto_energetico_v);
	np_btn_gasto_energetico_v.set_scale(0.009);
	np_btn_gasto_energetico_v.set_pos(1.28, 0.0, 0.12);
	//np_btn_gasto_energetico_v.stash();
	img_btn_gasto_energetico_v = ImageRepository::get_instance()->get_image("modeloGatoEnergetico");
	img_btn_gasto_energetico_v.reparent_to(grafico_variavel_frame_np);
	img_btn_gasto_energetico_v.set_scale(0.009);
	img_btn_gasto_energetico_v.set_pos(1.28, 0.0, 0.12);
	//img_btn_gasto_energetico_v.stash();
	hint_btn_gasto_energetico_v = new Hint(grafico_variavel_frame_np, btn_gasto_energetico_v.p(), img_btn_gasto_energetico_v, "hint_btn_gasto_energetico_v", "Gasto Energético");
	led_off_gasto_energetico_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_gasto_energetico_v.reparent_to(grafico_variavel_frame_np);
	led_off_gasto_energetico_v.set_scale(0.004);
	led_off_gasto_energetico_v.set_pos(1.28, 0.0, 0.32);
	//led_off_gasto_energetico_v.stash();
	led_on_gasto_energetico_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_gasto_energetico_v.reparent_to(grafico_variavel_frame_np);
	led_on_gasto_energetico_v.set_scale(0.004);
	led_on_gasto_energetico_v.set_pos(1.28, 0.0, 0.32);
	led_on_gasto_energetico_v.stash();
	btn_gasto_energetico_v->setup(img_btn_gasto_energetico_v);
	btn_gasto_energetico_v->set_frame(-5.0 , 5.0 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_previous_page_chart1(NodePath menu_frame_np) {
	btn_previous_page_chart1 = new PGButton("btn_previous_page_chart1");
	btn_previous_page_chart1->setup("<<<", 0.1);
	np_btn_previous_page_chart1 = menu_frame_np.attach_new_node(btn_previous_page_chart1);
	np_btn_previous_page_chart1.set_scale(0.05);
	np_btn_previous_page_chart1.set_pos(1.0, 0.0, 0.975);
	np_btn_previous_page_chart1.unstash();

}

void GraphicsMenu::make_btn_next_page_chart1(NodePath menu_frame_np) {
	btn_next_page_chart1 = new PGButton("btn_next_page_chart1");
	btn_next_page_chart1->setup(">>>", 0.1);
	np_btn_next_page_chart1 = menu_frame_np.attach_new_node(btn_next_page_chart1);
	np_btn_next_page_chart1.set_scale(0.05);
	np_btn_next_page_chart1.set_pos(1.65, 0.0, 0.975);
	np_btn_next_page_chart1.unstash();
}

//Torna visivel as opções relacionadas aos graficos.
void GraphicsMenu::show_all_option_graphics() {
	show_menu_graf_tempo();
	set_current_day(get_elapsed_days());
	//cout << "\nDIA CORRENTE: " << current_day;
}

//Torna invisivel as opções relacionadas aos graficos.
void GraphicsMenu::hide_all_option_graphics() {
	hide_menu_graf_tempo();
	hide_menu_graf_variavel();
	if (graphicVariavel != NULL) {
		graphicVariavel->hide();
	}
	label_txt_tipo_graf.stash();
	np_btn_graf_tempo.stash();
	led_off_graf_tempo.stash();
	led_on_graf_tempo.stash();
	np_btn_graf_variavel.stash();
	led_off_graf_variavel.stash();
	led_on_graf_variavel.stash();
	init_variables();
}

//Torna invisivel o painel que contem os botoes para ativar os graficos de tempo.
void GraphicsMenu::hide_menu_graf_tempo() {
	np_btn_temp_interna.stash();
	img_btn_temp_interna.stash();
	led_on_temp_interna.stash();
	led_off_temp_interna.stash();
	np_btn_hidratacao.stash();
	img_btn_hidratacao.stash();
	led_on_hidratacao.stash();
	led_off_hidratacao.stash();
	np_btn_temp_ar.stash();
	img_btn_temp_ar.stash();
	led_on_temp_ar.stash();
	led_off_temp_ar.stash();
	np_btn_umidade.stash();
	img_btn_umidade.stash();
	led_on_umidade.stash();
	led_off_umidade.stash();
	np_btn_temp_solo.stash();
	img_btn_temp_solo.stash();
	led_on_temp_solo.stash();
	led_off_temp_solo.stash();
	np_btn_alimentacao.stash();
	img_btn_alimentacao.stash();
	led_on_alimentacao.stash();
	led_off_alimentacao.stash();
	np_btn_energia.stash();
	img_btn_energia.stash();
	led_on_energia.stash();
	led_off_energia.stash();
	np_btn_gasto_energetico.stash();
	img_btn_gasto_energetico.stash();
	led_on_gasto_energetico.stash();
	led_off_gasto_energetico.stash();
}

//Torna invisivel o painel que contem os botoes para ativar os graficos de variaveis.
void GraphicsMenu::hide_menu_graf_variavel() {
//	this->esconde_painel_grafico_tempo();
	grafico_variavel_frame_np.stash();
}

//Torna visivel o painel que contem os botoes para ativar os graficos de tempo.
void GraphicsMenu::show_menu_graf_tempo() {
	hide_all_led_on();
	label_txt_tipo_graf.unstash();
	np_btn_graf_tempo.unstash();
	led_on_graf_tempo.unstash();
	np_btn_graf_variavel.unstash();
	led_off_graf_variavel.unstash();
	np_btn_temp_interna.unstash();
	img_btn_temp_interna.unstash();
	led_on_temp_interna.unstash();
	np_btn_hidratacao.unstash();
	img_btn_hidratacao.unstash();
	led_on_hidratacao.unstash();
	np_btn_temp_ar.unstash();
	img_btn_temp_ar.unstash();
	led_off_temp_ar.unstash();
	np_btn_umidade.unstash();
	img_btn_umidade.unstash();
	led_off_umidade.unstash();
	np_btn_temp_solo.unstash();
	img_btn_temp_solo.unstash();
	led_off_temp_solo.unstash();
	np_btn_alimentacao.unstash();
	img_btn_alimentacao.unstash();
	led_off_alimentacao.unstash();
	np_btn_energia.unstash();
	img_btn_energia.unstash();
	led_off_energia.unstash();
	np_btn_gasto_energetico.unstash();
	img_btn_gasto_energetico.unstash();
	led_off_gasto_energetico.unstash();
}

void GraphicsMenu::hide_all_led_on() {
	led_on_alimentacao.stash();
	led_on_energia.stash();
	led_on_gasto_energetico.stash();
	led_on_hidratacao.stash();
	led_on_temp_ar.stash();
	led_on_temp_interna.stash();
	led_on_temp_solo.stash();
	led_on_umidade.stash();
}

//Faz com que os graficos nao fiquem visiveis.
void GraphicsMenu::hide_all_graphics() {
	graphic->hide();
	graphic2->hide();
	graphic3->hide();
	graphic4->hide();
	graphic5->hide();
	graphic6->hide();
	graphic7->hide();
	graphic8->hide();
}

//Torna visivel o painel que contem os botoes para ativar os graficos de variaveis.
void GraphicsMenu::show_menu_graf_variavel() {
	this->hide_all_graphics();
	grafico_variavel_frame_np.unstash();
}

//Constroi o painel que contém os graficos.
void GraphicsMenu::build_options() {
	option_frame = new PGVirtualFrame("Frame do menu de opcoes");
	option_frame->setup(1.58, 2.0);
	PGFrameStyle style = option_frame->get_frame_style(option_frame->get_state());
	style.set_type(PGFrameStyle::T_flat);
	option_frame->set_frame_style(option_frame->get_state(), style);
	option_frame_np = NodePath(option_frame);
	option_frame_np.reparent_to(Simdunas::get_clickable_render_2d());
	//Seta a posição do frame
	option_frame_np.set_pos(1.0, 0.0, -1.0);
	//Seta a cor do frame
	option_frame_np.set_color(0.8, 0.8, 0.8);
	//Seta a transparencia do frame.
	option_frame_np.set_transparency(TransparencyAttrib::M_alpha);
	option_frame_np.set_alpha_scale(0.85);

	grafico_variavel_frame = new PGVirtualFrame("Frame das opcoes de grafico de variavel");
	grafico_variavel_frame->setup(1.58, 0.4);
	style = grafico_variavel_frame->get_frame_style(grafico_variavel_frame->get_state());
	style.set_type(PGFrameStyle::T_flat);
	grafico_variavel_frame->set_frame_style(grafico_variavel_frame->get_state(), style);
	grafico_variavel_frame_np = NodePath(grafico_variavel_frame);
	grafico_variavel_frame_np.reparent_to(Simdunas::get_clickable_render_2d());
	//Seta a posição do frame
	grafico_variavel_frame_np.set_pos(1.0, 0.0, -1.0);
	//Seta a cor do frame
	grafico_variavel_frame_np.set_color(0.8, 0.8, 0.8);
	//Seta a transparencia do frame.
	grafico_variavel_frame_np.set_transparency(TransparencyAttrib::M_alpha);
	grafico_variavel_frame_np.set_alpha_scale(0.85);
	grafico_variavel_frame_np.stash();
}

//Inicia os objetos dos graficos.
void GraphicsMenu::init_graphics() {
	 // por padrão, ao abrir o painel de gráficos, mostram-se os gráficos de Temperatura Interna e Hidratação (tipo tempo)
	grafico_tempo_ativo = true;
	PT(Graphics) chart1 = this->novo_grafico1_TempInterna();
	//this->novo_grafico1_TempInterna();
	posicao_grafico_tempInterna = 1;
	set_chart1(chart1);
	PT(Graphics) chart2 = this->novo_grafico2_Hidratacao();
	//this->novo_grafico2_Hidratacao();
	posicao_grafico_hidratacao = 2;
	set_chart2(chart2);
	//graphic2->set_Position_Graphic(0.4, 0.1);
	this->novo_grafico3_TempAr();
	graphic3->hide();
	this->novo_grafico4_Umidade();
	graphic4->hide();
	this->novo_grafico5_TempSolo();
	graphic5->hide();
	this->novo_grafico6_Alimentacao();
	graphic6->hide();
	this->novo_grafico7_Energia();
	graphic7->hide();
	this->novo_grafico8_GastoEnergetico();
	graphic8->hide();
}

void GraphicsMenu::draw_hint_line() {
	float mouse_x = 0; // coordenada X do mouse na tela
	float mouse_y = 0; // coordenada Y do mouse na tela
	MouseWatcher *mwatcher = DCAST(MouseWatcher, window->get_mouse().node());
	if (mwatcher->has_mouse()) {
		mouse_x = mwatcher->get_mouse_x();
		mouse_y = mwatcher->get_mouse_y();
		if (mouse_x >= 0.03 && mouse_x <= 0.57 && mouse_y >= 0.12 && mouse_y <= 0.66) { // cursor dentro do gráfico superior
			if (chart1 != NULL) {
				chart1->update_hint_line(mouse_x, 0.12, 0.66);
			}
		}
		else if (mouse_x >= 0.03 && mouse_x <= 0.57 && mouse_y >= -0.77 && mouse_y <= -0.23) {
			if (chart2 != NULL) {
				chart2->update_hint_line(mouse_x, -0.77, -0.23);
			}
		}
	}
}

// Retorna a quantidade de dias decorridos de jogo de acordo com o vetor de tempo
// Obtém a quantidade de 00:00 (meia-noite) do vetor de tempo para determinar quantos dias se passaram
int GraphicsMenu::get_elapsed_days() {

	History::HList* time_list = history->get_list(History::HI_time);
	int days = 1; // o primeiro dia começa às 06:00
	double front_time_list;
	History::HList* list = new History::HList(*time_list); // cópia do vetor de tempo
	double previous_time_value = 5; // o primeiro dia começa às 06:00, então passará na primeira iteração
	int list_size = list->size();

	// exibir o primeiro e último elemento da lista e o tamanho
	//cout << "\nPrimeiro item da lista: " << list->front();
	//cout << "\nÚltimo item da lista: " << list->back();
	//cout << "\nTamanho da lista: " << list_size;

	for (int i = 0; i < list_size; i++) {
		front_time_list = list->front(); // para ser readicionado ao final do vetor
		//if (front_time_list == 0.0) { // se chegou em 00:00 é um novo dia - pegar a transição de um dia para o outro
		// na transição de um dia para o outro, a última referência de hora do dia anterior (23:xx) será maior que que a primeira referência de hora do dia seguinte (00:xx)
		if (previous_time_value > front_time_list) {
			days++;
		}
		previous_time_value = front_time_list;
		list->pop_front(); // remove do início do vetor
	}

	return days;

}

// Obtém a lista de dados (eixo Y do gráfico) do dia passado como parâmetro
// Por padrão o gráfico exibe a página do dia atual de jogo (último dia jogado), portanto a lista é percorrida de trás para frente
History::HList* GraphicsMenu::get_item_list_by_day(int day_number, History::HList* item_list, History::HList* time_list) {

	History::HList* time = new History::HList(*time_list); // cópia do vetor de tempo
	History::HList* item = new History::HList(*item_list); // cópia do vetor de itens (eixo Y)
	double last_item_time_list; // último item do vetor de horas
	double last_item_data_list = item->back(); // último item do vetor de dados - a lista é percorrida de trás para frente
	History::HList* result_list = new History::HList(); // retorno da função - lista de dados (eixo Y do gráfico) do dia passado como parâmetro
	int current_day = get_elapsed_days(); // número de dias jogados
	double previous_time_value = 25; // valor anterior na iteração do vetor de horas
	int i = 0;

	while (current_day > day_number && i < time->size()) { // enquanto não chegar ao dia desejado ou percorrer toda a lista
		last_item_time_list = time->back(); // pega a última amostra do vetor de horas
		last_item_data_list = item->back(); // pega o último item do vetor de dados
		if (last_item_time_list > previous_time_value) { // é um novo dia? verifica a transição de um dia para o outro
			current_day--; // diminui um dia
			if (current_day == day_number) {
				result_list->push_back(last_item_data_list); // adiciona a última amostra do dia ao vetor de resultado
			}
		}
		previous_time_value = last_item_time_list; // guarda o valor atual de tempo para comparar na próxima iteração
		time->pop_back(); // remove a última amostra do vetor de horas
		item->pop_back(); // remove o último item do vetor de dados
		i++;
	}

	if (current_day == day_number) { // chegou ao dia desejado?
		// atualiza as variáveis dos vetores de horas e dados, senão ficam com as referências da amostra adicionada acima
		last_item_time_list = time->back();
		last_item_data_list = item->back();
		while (last_item_time_list < previous_time_value && time->size() > 0) { // enquanto não chegar ao final da lista ou no dia anterior
			result_list->push_back(last_item_data_list); // adiciona o item na lista de dados
			time->pop_back();
			item->pop_back();
			previous_time_value = last_item_time_list;
			last_item_time_list = time->back(); // pega a última amostra do vetor de horas
			last_item_data_list = item->back(); // pega o último item do vetor de dados
		}
	}

	return result_list; // o que fazer quando ela não for preenchida dentro do primeiro while?
}

// Obtém a lista de amostras de tempo (eixo X do gráfico) do dia passado como parâmetro
// Por padrão o gráfico exibe a página do dia atual de jogo (último dia jogado), portanto a lista é percorrida de trás para frente
History::HList* GraphicsMenu::get_time_list_by_day(int day_number, History::HList* time_list) {

	History::HList* time = new History::HList(*time_list); // cópia do vetor de tempo
	double last_item_time_list; // último item do vetor de horas
	History::HList* result_list = new History::HList(); // retorno da função - lista de amostras de tempo (eixo X) do dia passado como parâmetro
	int current_day = get_elapsed_days(); // número de dias jogados
	double previous_time_value = 25; // valor anterior na iteração do vetor de horas
	int i = 0;

	// Por algum motivo obscuro, a lista de tempo não está sendo preenchida corretamente do primeiro para o segundo dia. Como se tivesse um
	// limite de tamanho. Por exemplo, se o segundo dia tem 60 amostras, o último item da lista é 3,0 horas. Se há 63 amostras, o último é 3,5.
	// Conforme o dia passa, last_item_time_list aumenta do segundo dia aumenta, sendo que deveria ser sempre a primeira amostra do dia;

	while (current_day > day_number && i < time->size()) { // enquanto não chegar ao dia desejado ou percorrer toda a lista
		last_item_time_list = time->back(); // pega a última amostra do vetor de horas
		if (last_item_time_list > previous_time_value) { // é um novo dia? verifica a transição de um dia para o outro
			current_day--; // diminui um dia
			if (current_day == day_number) {
				result_list->push_back(last_item_time_list); // adiciona a última amostra ao vetor de resultado
			}
		}
		previous_time_value = last_item_time_list; // guarda o valor atual de tempo para comparar na próxima iteração
		time->pop_back(); // remove a última amostra do vetor de horas
		i++;
	}

	if (current_day == day_number) { // chegou ao dia desejado?
		// atualiza a variável do vetor de horas, senão fica com a referência da amostra adicionada acima
		last_item_time_list = time->back();
		while (last_item_time_list < previous_time_value && time->size() > 0) { // enquanto não chegar ao final da lista ou no dia anterior
			result_list->push_back(last_item_time_list); // adiciona o item na lista de tempo
			time->pop_back();
			previous_time_value = last_item_time_list;
			last_item_time_list = time->back(); // pega a última amostra do vetor de horas
		}
	}

	return result_list; // o que fazer quando ela não for preenchida dentro do primeiro while?
}


void GraphicsMenu::update_chart_page() {
//	cout << "\n\n------------- DIA DA PAGINAÇÃO: " << current_day;
//	History::HList* time_list = history->get_list(History::HI_time);
//	History::HList* time_chart = get_time_list_by_day(current_day, time_list);
//
//	History::HList* item_list_chart1 = history->get_list(item_chart1);
//	History::HList* items_chart1 = get_item_list_by_day(current_day, item_list_chart1, time_list);
//	chart1->hide();
//	chart1->update_chart_data(time_chart, items_chart1, history);
//	chart1->create_Graphic();
//
//	History::HList* item_list_chart2 = history->get_list(item_chart2);
//	History::HList* items_chart2 = get_item_list_by_day(current_day, item_list_chart2, time_list);
//	chart2->hide();
//	chart2->update_chart_data(time_chart, items_chart2, history);
//	chart2->create_Graphic();

	cout << "\n\n------------- DIA NA PAGINAÇÃO: " << current_day;
//	History::HList* time_list = history->get_list(History::HI_time);
//	History::HList* time_chart = get_time_list_by_day(current_day, time_list);

//	History::HList* item_list_chart1 = history->get_list(item_chart1);
//	History::HList* items_chart1 = get_item_list_by_day(current_day, item_list_chart1, time_list);
	chart_1->hide();
	grafico_posicao1_ativo = false;
	make_new_chart(item_chart1, chart_1, title_chart1, x_axis_chart1, y_axis_chart1);

//	History::HList* item_list_chart2 = history->get_list(item_chart2);
//	History::HList* items_chart2 = get_item_list_by_day(current_day, item_list_chart2, time_list);
	chart_2->hide();
	grafico_posicao2_ativo = false;
	make_new_chart(item_chart2, chart_2, title_chart2, x_axis_chart2, y_axis_chart2);

}

void GraphicsMenu::set_chart_page_properties(History::HistoryItem item, PT(Graphics) chart,
		const string &title, const string &x_axis, const string &y_axis, int chart_number) {
	if (chart_number == 1) {
		item_chart1 = item;
		chart_1 = chart;
		title_chart1 = title;
		x_axis_chart1 = x_axis;
		y_axis_chart1 = y_axis;
	} else {
		item_chart2 = item;
		chart_2 = chart;
		title_chart2 = title;
		x_axis_chart2 = x_axis;
		y_axis_chart2 = y_axis;
	}

}

PT(Graphics) GraphicsMenu::make_new_chart(History::HistoryItem item, PT(Graphics) &chart,
		const string &title, const string &x_axis, const string &y_axis){
	history->output(History::HI_player_hydration, title, simdunas_cat.debug());

	History::HList* time_list = history->get_list(History::HI_time);
	History::HList* item_list = history->get_list(item);

	// o controle de paginação não deve ser feito dentro do método make_new_chart() - mover daqui
	// função para dar o numero de dias no vetor de horas
	// função para obter o dia corrente
	/* para atualizar o dia corrente da paginação, basta atualizar o atributo current_day com -1 ou +1 dia
	 * a cada vez que os botões de << (dia anterior) e >> (próximo dia) forem clicados */

	// deve permanecer aqui
	// função para obter sublista dado lista full e o dia

	// função para obter sublista de tempo de acordo com o dia
	History::HList* time = get_time_list_by_day(get_current_day(), time_list);

	History::HList* items = get_item_list_by_day(get_current_day(), item_list, time_list);

	//cout << "\n\n------------FRONT ITEM: " << items->front();
	//cout << "\n------------BACK ITEM: " << items->back();
	//cout << "\n------------SIZE ITEMS: " << items->size();
	cout << "\n------------CURRENT DAY: " << get_current_day();

	//cout << "\n\n------------FRONT TIME: " << time->front();
	//cout << "\n------------BACK TIME: " << time->back();
	//cout << "\n------------SIZE TIME: " << time->size();

	chart = new Graphics(option_frame_np, true);
	//chart = new Graphics((option_frame_np), time_list, item_list, 0, 0, largest_element, smallest_element, true);
	chart->update_chart_data(time, items, history);
	if (!grafico_posicao1_ativo) {
		chart->set_Position_Graphic(0.4, 1.0);
		set_chart_page_properties(item, chart, title, x_axis, y_axis, 1);
		grafico_posicao1_ativo = true;
	} else if (!grafico_posicao2_ativo) {
		chart->set_Position_Graphic(0.4, 0.1);
		//item_chart2 = item;
		set_chart_page_properties(item, chart, title, x_axis, y_axis, 2);
		grafico_posicao2_ativo = true;
	}
	chart->set_scale(0.86);
	chart->set_Titulo_Grafico(title);
	chart->set_Titulo_EixoX(x_axis);
	chart->set_Titulo_EixoY(y_axis);
	chart->create_Graphic();

	return chart;
}

//Constroi o grafico de temperatura interna X tempo.
PT(Graphics) GraphicsMenu::novo_grafico1_TempInterna() {
//	print_queue_values(vector->getVectorTemperaturaLagarto(), "TEMPERATURA INTERNA");
//	history->output(History::HI_player_hydration, "Temperatura interna", simdunas_cat.debug());
//	graphic = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaLagarto(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaLagarto()), vector->getSmallestElement(vector->getVectorTemperaturaLagarto()), true);
//	graphic->set_Position_Graphic(0.4, 1.0);
//	graphic->set_scale(0.86);
//	graphic->set_Titulo_Grafico("Temperatura Interna");
//	graphic->set_Titulo_EixoX("Tempo (h)");
//	graphic->set_Titulo_EixoY("Temperatura (C)");
//	graphic->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorTemperaturaLagarto());

	return make_new_chart(History::HI_player_temperature, graphic, "Temperatura Interna", "Tempo (h)", "Temperatura (C)");
}

//Constroi o grafico de hidratacao X tempo.
PT(Graphics) GraphicsMenu::novo_grafico2_Hidratacao() {
//	print_queue_values(vector->getVectorHidratacaoLagarto(), "HIDRATAÇÃO");
//	history->output(History::HI_player_hydration, "Hidratação", simdunas_cat.debug());
//	graphic2 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorHidratacaoLagarto(), 0, 0, 100, 0, true);
//	graphic2->set_Position_Graphic(0.4, 1.0);
//	graphic2->set_scale(0.86);
//	graphic2->set_Titulo_Grafico("Hidratacao do lagarto");
//	graphic2->set_Titulo_EixoX("Tempo (h)");
//	graphic2->set_Titulo_EixoY("Hidratacao (%)");
//	graphic2->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorHidratacaoLagarto());

	return make_new_chart(History::HI_player_hydration, graphic2, "Hidratação do Lagarto", "Tempo (h)", "Hidratação (%)");
}

//Constroi o grafico de temperatura do ar X tempo.
PT(Graphics) GraphicsMenu::novo_grafico3_TempAr() {
//	print_queue_values(vector->getVectorTemperaturaAr(), "TEMPERATURA DO AR");
//	history->output(History::HI_player_hydration, "Temperatura do ar", simdunas_cat.debug());
//	graphic3 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaAr(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaAr()), vector->getSmallestElement(vector->getVectorTemperaturaAr()), true);
//	graphic3->set_Position_Graphic(0.4, 1.0);
//	graphic3->set_scale(0.86);
//	graphic3->set_Titulo_Grafico("Temperatura do ar.");
//	graphic3->set_Titulo_EixoX("Tempo (h)");
//	graphic3->set_Titulo_EixoY("Temperatura (c)");
//	graphic3->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorTemperaturaAr());

	return make_new_chart(History::HI_world_temperature, graphic3, "Temperatura do ar", "Tempo (h)", "Temperatura (C)");
}

//Constroi o grafico de umidade X tempo.
PT(Graphics) GraphicsMenu::novo_grafico4_Umidade() {
//	print_queue_values(vector->getVectorUmidadeAmbiente(), "UMIDADE");
//	history->output(History::HI_player_hydration, "Umidade", simdunas_cat.debug());
//	graphic4 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorUmidadeAmbiente(), 0, 0, 100, 0, true);
//	graphic4->set_Position_Graphic(0.4, 1.0);
//	graphic4->set_scale(0.86);
//	graphic4->set_Titulo_Grafico("Umidade do ar.");
//	graphic4->set_Titulo_EixoX("Tempo (h)");
//	graphic4->set_Titulo_EixoY("Umidade");
//	graphic4->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorUmidadeAmbiente());
	return make_new_chart(History::HI_world_humidity, graphic4, "Umidade do ar", "Tempo (h)", "Umidade");
}

//Constroi o grafico de temperatura do solo X tempo.
PT(Graphics) GraphicsMenu::novo_grafico5_TempSolo() {
//	print_queue_values(vector->getVectorTemperaturaSolo(), "TEMPERATURA DO SOLO");
//	history->output(History::HI_player_hydration, "Temperatura do solo", simdunas_cat.debug());
//	graphic5 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaSolo(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaSolo()), vector->getSmallestElement(vector->getVectorTemperaturaSolo()), true);
//	graphic5->set_Position_Graphic(0.4, 1.0);
//	graphic5->set_scale(0.86);
//	graphic5->set_Titulo_Grafico("Temperatura do Solo");
//	graphic5->set_Titulo_EixoX("Tempo (h)");
//	graphic5->set_Titulo_EixoY("Temperatura (C)");
//	graphic5->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorTemperaturaSolo());
	return make_new_chart(History::HI_soil_temperature, graphic5, "Temperatura do solo", "Tempo (h)", "Temperatura (C)");
}

//Constroi o grafico de alimentacao X tempo.
PT(Graphics) GraphicsMenu::novo_grafico6_Alimentacao() {
//	print_queue_values(vector->getVectorAlimentacao(), "ALIMENTAÇÃO");
//	history->output(History::HI_player_hydration, "Alimentação", simdunas_cat.debug());
//	graphic6 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorAlimentacao(), 0, 0, vector->getLargestElement(vector->getVectorAlimentacao()), vector->getSmallestElement(vector->getVectorAlimentacao()), true);
//	graphic6->set_Position_Graphic(0.4, 1.0);
//	graphic6->set_scale(0.86);
//	graphic6->set_Titulo_Grafico("Alimentacao");
//	graphic6->set_Titulo_EixoX("Tempo (h)");
//	graphic6->set_Titulo_EixoY("Alimentacao");
//	graphic6->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorAlimentacao());
	return make_new_chart(History::HI_feeding, graphic6, "Alimentação", "Tempo (h)", "Alimentação");
}

//Constroi o grafico de energia X tempo.
PT(Graphics) GraphicsMenu::novo_grafico7_Energia() {
//	print_queue_values(vector->getVectorEnergia(), "ENERGIA");
//	history->output(History::HI_player_hydration, "Energia", simdunas_cat.debug());
//	graphic7 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorEnergia(), 0, 0, 100, 0, true);
//	graphic7->set_Position_Graphic(0.4, 1.0);
//	graphic7->set_scale(0.86);
//	graphic7->set_Titulo_Grafico("Energia");
//	graphic7->set_Titulo_EixoX("Tempo (h)");
//	graphic7->set_Titulo_EixoY("Energia");
//	graphic7->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorEnergia());
	return make_new_chart(History::HI_energy, graphic7, "Energia", "Tempo (h)", "Energia");
}

//Constroi o grafico de gasto energetico X tempo.
PT(Graphics) GraphicsMenu::novo_grafico8_GastoEnergetico() {
//	print_queue_values(vector->getVectorGastoEnergeticoTotal(), "GASTO ENERGÉTICO");
//	history->output(History::HI_player_hydration, "Gasto Energético", simdunas_cat.debug());
//	graphic8 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorGastoEnergeticoTotal(), 0, 0, vector->getLargestElement(vector->getVectorGastoEnergeticoTotal()), vector->getSmallestElement(vector->getVectorGastoEnergeticoTotal()), true);
//	graphic8->set_Position_Graphic(0.4, 1.0);
//	graphic8->set_scale(0.86);
//	graphic8->set_Titulo_Grafico("Gasto energetico");
//	graphic8->set_Titulo_EixoX("Tempo (h)");
//	graphic8->set_Titulo_EixoY("Gasto energetico");
//	graphic8->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorGastoEnergiticoTotal());
	return make_new_chart(History::HI_total_energy_cost, graphic8, "Gasto Energético", "Tempo (h)", "Gasto Energético");
}

//Desliga as luzes que indicam quais graficos estao ativos no painel de tempo.
void GraphicsMenu::desliga_leds_painel_tempo() {
	led_on_temp_interna.stash();
	led_on_hidratacao.stash();
	led_on_temp_ar.stash();
	led_on_umidade.stash();
	led_on_temp_solo.stash();
	led_on_alimentacao.stash();
	led_on_energia.stash();
	led_on_gasto_energetico.stash();
	led_off_temp_interna.unstash();
	led_off_hidratacao.unstash();
	led_off_temp_ar.unstash();
	led_off_umidade.unstash();
	led_off_temp_solo.unstash();
	led_off_alimentacao.unstash();
	led_off_energia.unstash();
	led_off_gasto_energetico.unstash();
}

//Desliga as luzes que indicam quais graficos estao ativos no painel de variavel.
void GraphicsMenu::desliga_leds_painel_variavel() {
	led_on_temp_interna_v.stash();
	led_on_hidratacao_v.stash();
	led_on_temp_ar_v.stash();
	led_on_umidade_v.stash();
	led_on_temp_solo_v.stash();
	led_on_alimentacao_v.stash();
	led_on_energia_v.stash();
	led_on_gasto_energetico_v.stash();
	led_off_temp_interna_v.unstash();
	led_off_hidratacao_v.unstash();
	led_off_temp_ar_v.unstash();
	led_off_umidade_v.unstash();
	led_off_temp_solo_v.unstash();
	led_off_alimentacao_v.unstash();
	led_off_energia_v.unstash();
	led_off_gasto_energetico_v.unstash();
}

