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

GraphicsMenu::GraphicsMenu(NodePath menu_frame_np) {
	history = Session::get_instance()->history();

	make_tipo_graf(menu_frame_np);

	flag_graf_tempo_ativo = true;

	flag_graf_variavel_ativo = false;

	make_menu_graf_tempo(menu_frame_np);

	build_options();
	make_menu_graf_variavel();

	set_vetor_x(history->get_list(History::HI_world_temperature));
	set_vetor_y(history->get_list(History::HI_world_temperature));

	set_legenda_x((string) "Temp do ar");
	set_legenda_y((string) "Temp do ar");
	set_limite_superior_x(History::get_largest_element(vetor_x));//45;
	set_vetor_x(history->get_list(History::HI_world_temperature));
	set_limite_inferior_x(History::get_smallest_element(vetor_x));//9;

	set_limite_superior_y(History::get_largest_element(vetor_y));//45;
	set_vetor_y(history->get_list(History::HI_world_temperature));
	set_limite_inferior_y(History::get_smallest_element(vetor_y));//9;

	set_tamanho_vetor_x(history->get_size(History::HI_world_temperature));
	set_tamanho_vetor_y(history->get_size(History::HI_world_temperature));

	set_graphic_variavel(new Graphics((get_option_frame_np()), vetor_x, vetor_y, limite_superior_x, limite_inferior_x, limite_superior_y, limite_inferior_y, false));
	graphicVariavel->set_Position_Graphic(0.2, 0.6);
	graphicVariavel->set_scale(1.2);
	graphicVariavel->hide();
}

GraphicsMenu::~GraphicsMenu() {}

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

// Monta a parte do topo onde tem escrito "Tipo do Grafico" (label, leds e botões)
void GraphicsMenu::make_tipo_graf(NodePath menu_frame_np) {
	make_txt_tipo_graf(menu_frame_np);

	make_btn_graf_tempo(menu_frame_np);

	make_btn_graf_variavel(menu_frame_np);
}

void GraphicsMenu::make_txt_tipo_graf(NodePath menu_frame_np) {
	txt_tipo_graf = new TextNode("txt_tipo_graf");
	txt_tipo_graf->set_text("Tipo do grafico");
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
	btn_graf_variavel->setup("Variavel", 0.1);
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

//Torna visivel as opções relacionadas aos graficos.
void GraphicsMenu::show_all_option_graphics() {
	show_menu_graf_tempo();
}

//Torna invisivel as opções relacionadas aos graficos.
void GraphicsMenu::hide_all_option_graphics() {
	hide_menu_graf_tempo();
	hide_menu_graf_variavel();
	graphicVariavel->hide();
	label_txt_tipo_graf.stash();
	np_btn_graf_tempo.stash();
	led_off_graf_tempo.stash();
	led_on_graf_tempo.stash();
	np_btn_graf_variavel.stash();
	led_off_graf_variavel.stash();
	led_on_graf_variavel.stash();
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
	this->novo_grafico1_TempInterna();
	this->novo_grafico2_Hidratacao();
	graphic2->set_Position_Graphic(0.4, 0.1);
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

void GraphicsMenu::make_new_chart(History::HistoryItem item, PT(Graphics) &chart,
		const string &title, const string &x_axis, const string &y_axis){
	history->output(History::HI_player_hydration, title, cout);

	History::HList* time_list = history->get_list(History::HI_time);
	History::HList* item_list = history->get_list(item);
	float largest_element = history->get_largest_element(item);
	float smallest_element = history->get_smallest_element(item);

	chart = new Graphics((option_frame_np), time_list, item_list, 0, 0, largest_element, smallest_element, true);
	chart->set_Position_Graphic(0.4, 1.0);
	chart->set_scale(0.86);
	chart->set_Titulo_Grafico(title);
	chart->set_Titulo_EixoX(x_axis);
	chart->set_Titulo_EixoY(y_axis);
	chart->create_Graphic(history->get_size(History::HI_time), history->get_size(item));
}

//Constroi o grafico de temperatura interna X tempo.
void GraphicsMenu::novo_grafico1_TempInterna() {
//	print_queue_values(vector->getVectorTemperaturaLagarto(), "TEMPERATURA INTERNA");
//	history->output(History::HI_player_hydration, "Temperatura interna", cout);
//	graphic = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaLagarto(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaLagarto()), vector->getSmallestElement(vector->getVectorTemperaturaLagarto()), true);
//	graphic->set_Position_Graphic(0.4, 1.0);
//	graphic->set_scale(0.86);
//	graphic->set_Titulo_Grafico("Temperatura Interna");
//	graphic->set_Titulo_EixoX("Tempo (h)");
//	graphic->set_Titulo_EixoY("Temperatura (C)");
//	graphic->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorTemperaturaLagarto());

	make_new_chart(History::HI_player_temperature, graphic, "Temperatura Interna", "Tempo (h)", "Temperatura (C)");
}

//Constroi o grafico de hidratacao X tempo.
void GraphicsMenu::novo_grafico2_Hidratacao() {
//	print_queue_values(vector->getVectorHidratacaoLagarto(), "HIDRATAÇÃO");
//	history->output(History::HI_player_hydration, "Hidratação", cout);
//	graphic2 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorHidratacaoLagarto(), 0, 0, 100, 0, true);
//	graphic2->set_Position_Graphic(0.4, 1.0);
//	graphic2->set_scale(0.86);
//	graphic2->set_Titulo_Grafico("Hidratacao do lagarto");
//	graphic2->set_Titulo_EixoX("Tempo (h)");
//	graphic2->set_Titulo_EixoY("Hidratacao (%)");
//	graphic2->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorHidratacaoLagarto());

	make_new_chart(History::HI_player_hydration, graphic2, "Hidratação do Lagarto", "Tempo (h)", "Hidratação (%)");
}

//Constroi o grafico de temperatura do ar X tempo.
void GraphicsMenu::novo_grafico3_TempAr() {
//	print_queue_values(vector->getVectorTemperaturaAr(), "TEMPERATURA DO AR");
//	history->output(History::HI_player_hydration, "Temperatura do ar", cout);
//	graphic3 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaAr(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaAr()), vector->getSmallestElement(vector->getVectorTemperaturaAr()), true);
//	graphic3->set_Position_Graphic(0.4, 1.0);
//	graphic3->set_scale(0.86);
//	graphic3->set_Titulo_Grafico("Temperatura do ar.");
//	graphic3->set_Titulo_EixoX("Tempo (h)");
//	graphic3->set_Titulo_EixoY("Temperatura (c)");
//	graphic3->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorTemperaturaAr());

	make_new_chart(History::HI_world_temperature, graphic3, "Temperatura do ar", "Tempo (h)", "Temperatura (C)");
}

//Constroi o grafico de umidade X tempo.
void GraphicsMenu::novo_grafico4_Umidade() {
//	print_queue_values(vector->getVectorUmidadeAmbiente(), "UMIDADE");
//	history->output(History::HI_player_hydration, "Umidade", cout);
//	graphic4 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorUmidadeAmbiente(), 0, 0, 100, 0, true);
//	graphic4->set_Position_Graphic(0.4, 1.0);
//	graphic4->set_scale(0.86);
//	graphic4->set_Titulo_Grafico("Umidade do ar.");
//	graphic4->set_Titulo_EixoX("Tempo (h)");
//	graphic4->set_Titulo_EixoY("Umidade");
//	graphic4->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorUmidadeAmbiente());
	make_new_chart(History::HI_world_humidity, graphic4, "Umidade do ar", "Tempo (h)", "Umidade");
}

//Constroi o grafico de temperatura do solo X tempo.
void GraphicsMenu::novo_grafico5_TempSolo() {
//	print_queue_values(vector->getVectorTemperaturaSolo(), "TEMPERATURA DO SOLO");
//	history->output(History::HI_player_hydration, "Temperatura do solo", cout);
//	graphic5 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaSolo(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaSolo()), vector->getSmallestElement(vector->getVectorTemperaturaSolo()), true);
//	graphic5->set_Position_Graphic(0.4, 1.0);
//	graphic5->set_scale(0.86);
//	graphic5->set_Titulo_Grafico("Temperatura do Solo");
//	graphic5->set_Titulo_EixoX("Tempo (h)");
//	graphic5->set_Titulo_EixoY("Temperatura (C)");
//	graphic5->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorTemperaturaSolo());
	make_new_chart(History::HI_soil_temperature, graphic5, "Temperatura do solo", "Tempo (h)", "Temperatura (C)");
}

//Constroi o grafico de alimentacao X tempo.
void GraphicsMenu::novo_grafico6_Alimentacao() {
//	print_queue_values(vector->getVectorAlimentacao(), "ALIMENTAÇÃO");
//	history->output(History::HI_player_hydration, "Alimentação", cout);
//	graphic6 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorAlimentacao(), 0, 0, vector->getLargestElement(vector->getVectorAlimentacao()), vector->getSmallestElement(vector->getVectorAlimentacao()), true);
//	graphic6->set_Position_Graphic(0.4, 1.0);
//	graphic6->set_scale(0.86);
//	graphic6->set_Titulo_Grafico("Alimentacao");
//	graphic6->set_Titulo_EixoX("Tempo (h)");
//	graphic6->set_Titulo_EixoY("Alimentacao");
//	graphic6->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorAlimentacao());
	make_new_chart(History::HI_feeding, graphic6, "Alimentação", "Tempo (h)", "Alimentação");
}

//Constroi o grafico de energia X tempo.
void GraphicsMenu::novo_grafico7_Energia() {
//	print_queue_values(vector->getVectorEnergia(), "ENERGIA");
//	history->output(History::HI_player_hydration, "Energia", cout);
//	graphic7 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorEnergia(), 0, 0, 100, 0, true);
//	graphic7->set_Position_Graphic(0.4, 1.0);
//	graphic7->set_scale(0.86);
//	graphic7->set_Titulo_Grafico("Energia");
//	graphic7->set_Titulo_EixoX("Tempo (h)");
//	graphic7->set_Titulo_EixoY("Energia");
//	graphic7->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorEnergia());
	make_new_chart(History::HI_energy, graphic7, "Energia", "Tempo (h)", "Energia");
}

//Constroi o grafico de gasto energetico X tempo.
void GraphicsMenu::novo_grafico8_GastoEnergetico() {
//	print_queue_values(vector->getVectorGastoEnergeticoTotal(), "GASTO ENERGÉTICO");
//	history->output(History::HI_player_hydration, "Gasto Energético", cout);
//	graphic8 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorGastoEnergeticoTotal(), 0, 0, vector->getLargestElement(vector->getVectorGastoEnergeticoTotal()), vector->getSmallestElement(vector->getVectorGastoEnergeticoTotal()), true);
//	graphic8->set_Position_Graphic(0.4, 1.0);
//	graphic8->set_scale(0.86);
//	graphic8->set_Titulo_Grafico("Gasto energetico");
//	graphic8->set_Titulo_EixoX("Tempo (h)");
//	graphic8->set_Titulo_EixoY("Gasto energetico");
//	graphic8->create_Graphic(history->get_size(History::HI_time), vector->getSizeVectorGastoEnergiticoTotal());
	make_new_chart(History::HI_total_energy_cost, graphic8, "Gasto energetico", "Tempo (h)", "Gasto Energetico");
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
