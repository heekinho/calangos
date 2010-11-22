/*
 * graphicsMenu.cxx
 *
 *  Created on: Oct 24, 2010
 *      Author: jonatas
 */

#include "graphicsMenu.h"
#include "imageRepository.h"

GraphicsMenu::GraphicsMenu(NodePath menu_frame_np) {
	//Inicia o objeto vetores.
	vector = Vetores::get_instance();

	make_tipo_graf(menu_frame_np);

	flag_graf_tempo_ativo = true;

	flag_graf_variavel_ativo = false;

	make_menu_graf_tempo(menu_frame_np);

	make_menu_graf_variavel(menu_frame_np);

	set_vetor_x(vector->getVectorTemperaturaAr());
	set_vetor_y(vector->getVectorTemperaturaAr());

	set_legenda_x((string) "Temp do ar");
	set_legenda_y((string) "Temp do ar");
	set_limite_superior_x(vector->getLargestElement(vetor_x));//45;
	set_vetor_x(vector->getVectorTemperaturaAr());
	set_limite_inferior_x(vector->getSmallestElement(vetor_x));//9;

	set_limite_superior_y(vector->getLargestElement(vetor_y));//45;
	set_vetor_y(vector->getVectorTemperaturaAr());
	set_limite_inferior_y(vector->getSmallestElement(vetor_y));//9;
	set_tamanho_vetor_x(vector->getSizeVectorTemperaturaAr());
	set_tamanho_vetor_y(vector->getSizeVectorTemperaturaAr());

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

queue<double> GraphicsMenu::get_vetor_x() {
	return vetor_x;
}

void GraphicsMenu::set_vetor_x(queue<double> vetor) {
	vetor_x = vetor;
}

queue<double> GraphicsMenu::get_vetor_y() {
	return vetor_y;
}

void GraphicsMenu::set_vetor_y(queue<double> vetor) {
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

Vetores* GraphicsMenu::get_vector() {
	return vector;
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
	label_txt_tipo_graf.hide();
}

void GraphicsMenu::make_btn_graf_tempo(NodePath menu_frame_np) {
	//BOTAO PARA VER OS GRAFICOS DE TEMPO.
	btn_graf_tempo = new PGButton("btn_graf_tempo");
	btn_graf_tempo->setup("Tempo", 0.1);
	np_btn_graf_tempo = menu_frame_np.attach_new_node(btn_graf_tempo);
	np_btn_graf_tempo.set_scale(0.05);
	np_btn_graf_tempo.set_pos(0.08, 0.0, 1.80);
	np_btn_graf_tempo.hide();
	led_off_graf_tempo = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_graf_tempo.reparent_to(menu_frame_np);
	led_off_graf_tempo.set_scale(0.004);
	led_off_graf_tempo.set_pos(0.28, 0.0, 1.82);
	led_off_graf_tempo.hide();
	led_on_graf_tempo = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_graf_tempo.reparent_to(menu_frame_np);
	led_on_graf_tempo.set_scale(0.004);
	led_on_graf_tempo.set_pos(0.28, 0.0, 1.82);
	led_on_graf_tempo.hide();
}

void GraphicsMenu::make_btn_graf_variavel(NodePath menu_frame_np) {
	//BOTAO PARA VER OS GRAFICOS DE VARIAVEL.
	btn_graf_variavel = new PGButton("btn_graf_variavel");
	btn_graf_variavel->setup("Variavel", 0.1);
	np_btn_graf_variavel = menu_frame_np.attach_new_node(btn_graf_variavel);
	np_btn_graf_variavel.set_scale(0.05);
	np_btn_graf_variavel.set_pos(0.06, 0.0, 1.68);
	np_btn_graf_variavel.hide();
	led_off_graf_variavel = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_graf_variavel.reparent_to(menu_frame_np);
	led_off_graf_variavel.set_scale(0.004);
	led_off_graf_variavel.set_pos(0.28, 0.0, 1.70);
	led_off_graf_variavel.hide();
	led_on_graf_variavel = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_graf_variavel.reparent_to(menu_frame_np);
	led_on_graf_variavel.set_scale(0.004);
	led_on_graf_variavel.set_pos(0.28, 0.0, 1.70);
	led_on_graf_variavel.hide();
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
	np_btn_temp_interna.hide();
	img_btn_temp_interna = ImageRepository::get_instance()->get_image("modeloTemperatura");
	img_btn_temp_interna.reparent_to(menu_frame_np);
	img_btn_temp_interna.set_scale(0.008);
	img_btn_temp_interna.set_pos(0.08, 0.0, 1.52);
	img_btn_temp_interna.hide();
	led_off_temp_interna = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_interna.reparent_to(menu_frame_np);
	led_off_temp_interna.set_scale(0.0034);
	led_off_temp_interna.set_pos(0.17, 0.0, 1.48);
	led_off_temp_interna.hide();
	led_on_temp_interna = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_interna.reparent_to(menu_frame_np);
	led_on_temp_interna.set_scale(0.0034);
	led_on_temp_interna.set_pos(0.17, 0.0, 1.48);
	led_on_temp_interna.hide();
	btn_temp_interna->setup(img_btn_temp_interna);
	btn_temp_interna->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_hidratacao(NodePath menu_frame_np) {
	btn_hidratacao = new PGButton("btn_hidratacao");
	btn_hidratacao->setup("", 0.1);
	np_btn_hidratacao = menu_frame_np.attach_new_node(btn_hidratacao);
	np_btn_hidratacao.set_scale(0.03);
	np_btn_hidratacao.set_pos(0.26, 0.0, 1.52);
	np_btn_hidratacao.hide();
	img_btn_hidratacao = ImageRepository::get_instance()->get_image("modeloHidratacao");
	img_btn_hidratacao.reparent_to(menu_frame_np);
	img_btn_hidratacao.set_scale(0.008);
	img_btn_hidratacao.set_pos(0.26, 0.0, 1.52);
	img_btn_hidratacao.hide();
	led_off_hidratacao = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_hidratacao.reparent_to(menu_frame_np);
	led_off_hidratacao.set_scale(0.0034);
	led_off_hidratacao.set_pos(0.35, 0.0, 1.48);
	led_off_hidratacao.hide();
	led_on_hidratacao = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_hidratacao.reparent_to(menu_frame_np);
	led_on_hidratacao.set_scale(0.0034);
	led_on_hidratacao.set_pos(0.35, 0.0, 1.48);
	led_on_hidratacao.hide();
	btn_hidratacao->setup(img_btn_hidratacao);
	btn_hidratacao->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_temp_ar(NodePath menu_frame_np) {
	btn_temp_ar = new PGButton("btn_temp_ar");
	btn_temp_ar->setup("", 0.1);
	np_btn_temp_ar = menu_frame_np.attach_new_node(btn_temp_ar);
	np_btn_temp_ar.set_scale(0.03);
	np_btn_temp_ar.set_pos(0.08, 0.0, 1.30);
	np_btn_temp_ar.hide();
	img_btn_temp_ar = ImageRepository::get_instance()->get_image("mundo_temp2");
	img_btn_temp_ar.reparent_to(menu_frame_np);
	img_btn_temp_ar.set_scale(0.006);
	img_btn_temp_ar.set_pos(0.08, 0.0, 1.30);
	img_btn_temp_ar.hide();
	led_off_temp_ar = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_ar.reparent_to(menu_frame_np);
	led_off_temp_ar.set_scale(0.0034);
	led_off_temp_ar.set_pos(0.17, 0.0, 1.26);
	led_off_temp_ar.hide();
	led_on_temp_ar = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_ar.reparent_to(menu_frame_np);
	led_on_temp_ar.set_scale(0.0034);
	led_on_temp_ar.set_pos(0.17, 0.0, 1.26);
	led_on_temp_ar.hide();
	btn_temp_ar->setup(img_btn_temp_interna);
	btn_temp_ar->set_frame(-1.6 , 1.6 , -2.0, 2.0);
}

void GraphicsMenu::make_btn_umidade(NodePath menu_frame_np) {
	btn_umidade = new PGButton("btn_umidade");
	btn_umidade->setup("", 0.1);
	np_btn_umidade = menu_frame_np.attach_new_node(btn_umidade);
	np_btn_umidade.set_scale(0.03);
	np_btn_umidade.set_pos(0.26, 0.0, 1.30);
	np_btn_umidade.hide();
	img_btn_umidade = ImageRepository::get_instance()->get_image("mundo_umi");
	img_btn_umidade.reparent_to(menu_frame_np);
	img_btn_umidade.set_scale(0.005);
	img_btn_umidade.set_pos(0.26, 0.0, 1.30);
	img_btn_umidade.hide();
	led_off_umidade = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_umidade.reparent_to(menu_frame_np);
	led_off_umidade.set_scale(0.0034);
	led_off_umidade.set_pos(0.35, 0.0, 1.26);
	led_off_umidade.hide();
	led_on_umidade = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_umidade.reparent_to(menu_frame_np);
	led_on_umidade.set_scale(0.0034);
	led_on_umidade.set_pos(0.35, 0.0, 1.26);
	led_on_umidade.hide();
	btn_umidade->setup(img_btn_hidratacao);
	btn_umidade->set_frame(-1.6 , 1.6 , -2.0, 2.0);
}

void GraphicsMenu::make_btn_temp_solo(NodePath menu_frame_np) {
	btn_temp_solo = new PGButton("btn_temp_solo");
	btn_temp_solo->setup("", 0.1);
	np_btn_temp_solo = menu_frame_np.attach_new_node(btn_temp_solo);
	np_btn_temp_solo.set_scale(0.03);
	np_btn_temp_solo.set_pos(0.08, 0.0, 1.08);
	np_btn_temp_solo.hide();
	img_btn_temp_solo = ImageRepository::get_instance()->get_image("mundo_temp3");
	img_btn_temp_solo.reparent_to(menu_frame_np);
	img_btn_temp_solo.set_scale(0.006);
	img_btn_temp_solo.set_pos(0.08, 0.0, 1.08);
	img_btn_temp_solo.hide();
	led_off_temp_solo = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_solo.reparent_to(menu_frame_np);
	led_off_temp_solo.set_scale(0.0034);
	led_off_temp_solo.set_pos(0.17, 0.0, 1.04);
	led_off_temp_solo.hide();
	led_on_temp_solo = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_solo.reparent_to(menu_frame_np);
	led_on_temp_solo.set_scale(0.0034);
	led_on_temp_solo.set_pos(0.17, 0.0, 1.04);
	led_on_temp_solo.hide();
	btn_temp_solo->setup(img_btn_temp_solo);
	btn_temp_solo->set_frame(-1.6 , 1.6 , -2.0, 2.0);
}

void GraphicsMenu::make_btn_alimentacao(NodePath menu_frame_np) {
	btn_alimentacao = new PGButton("btn_alimentacao");
	btn_alimentacao->setup("", 0.1);
	np_btn_alimentacao = menu_frame_np.attach_new_node(btn_alimentacao);
	np_btn_alimentacao.set_scale(0.03);
	np_btn_alimentacao.set_pos(0.26, 0.0, 1.08);
	np_btn_alimentacao.hide();
	img_btn_alimentacao = ImageRepository::get_instance()->get_image("modeloNutricional");
	img_btn_alimentacao.reparent_to(menu_frame_np);
	img_btn_alimentacao.set_scale(0.008);
	img_btn_alimentacao.set_pos(0.26, 0.0, 1.08);
	img_btn_alimentacao.hide();
	led_off_alimentacao = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_alimentacao.reparent_to(menu_frame_np);
	led_off_alimentacao.set_scale(0.0034);
	led_off_alimentacao.set_pos(0.35, 0.0, 1.04);
	led_off_alimentacao.hide();
	led_on_alimentacao = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_alimentacao.reparent_to(menu_frame_np);
	led_on_alimentacao.set_scale(0.0034);
	led_on_alimentacao.set_pos(0.35, 0.0, 1.04);
	led_on_alimentacao.hide();
	btn_alimentacao->setup(img_btn_alimentacao);
	btn_alimentacao->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_energia(NodePath menu_frame_np) {
	btn_energia = new PGButton("btn_energia");
	btn_energia->setup("", 0.1);
	np_btn_energia = menu_frame_np.attach_new_node(btn_energia);
	np_btn_energia.set_scale(0.03);
	np_btn_energia.set_pos(0.08, 0.0, 0.86);
	np_btn_energia.hide();
	img_btn_energia = ImageRepository::get_instance()->get_image("modeloEnergia");
	img_btn_energia.reparent_to(menu_frame_np);
	img_btn_energia.set_scale(0.008);
	img_btn_energia.set_pos(0.08, 0.0, 0.86);
	img_btn_energia.hide();
	led_off_energia = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_energia.reparent_to(menu_frame_np);
	led_off_energia.set_scale(0.0034);
	led_off_energia.set_pos(0.17, 0.0, 0.82);
	led_off_energia.hide();
	led_on_energia = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_energia.reparent_to(menu_frame_np);
	led_on_energia.set_scale(0.0034);
	led_on_energia.set_pos(0.17, 0.0, 0.82);
	led_on_energia.hide();
	btn_energia->setup(img_btn_energia);
	btn_energia->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_btn_gasto_energetico(NodePath menu_frame_np) {
	btn_gasto_energetico = new PGButton("btn_gasto_energetico");
	btn_gasto_energetico->setup("", 0.1);
	np_btn_gasto_energetico = menu_frame_np.attach_new_node(btn_gasto_energetico);
	np_btn_gasto_energetico.set_scale(0.03);
	np_btn_gasto_energetico.set_pos(0.26, 0.0, 0.86);
	np_btn_gasto_energetico.hide();
	img_btn_gasto_energetico = ImageRepository::get_instance()->get_image("modeloGatoEnergetico");
	img_btn_gasto_energetico.reparent_to(menu_frame_np);
	img_btn_gasto_energetico.set_scale(0.008);
	img_btn_gasto_energetico.set_pos(0.26, 0.0, 0.86);
	img_btn_gasto_energetico.hide();
	led_off_gasto_energetico = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_gasto_energetico.reparent_to(menu_frame_np);
	led_off_gasto_energetico.set_scale(0.0034);
	led_off_gasto_energetico.set_pos(0.35, 0.0, 0.82);
	led_off_gasto_energetico.hide();
	led_on_gasto_energetico = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_gasto_energetico.reparent_to(menu_frame_np);
	led_on_gasto_energetico.set_scale(0.0034);
	led_on_gasto_energetico.set_pos(0.35, 0.0, 0.82);
	led_on_gasto_energetico.hide();
	btn_gasto_energetico->setup(img_btn_gasto_energetico);
	btn_gasto_energetico->set_frame(-1.3 , 1.3 , -2.8, 2.8);
}

void GraphicsMenu::make_menu_graf_variavel(NodePath menu_frame_np) {
	make_btn_temp_interna_v(menu_frame_np);

	make_btn_hidratacao_v(menu_frame_np);

	make_btn_temp_ar_v(menu_frame_np);

	make_btn_umidade_v(menu_frame_np);

	make_btn_temp_solo_v(menu_frame_np);

	make_btn_alimentacao_v(menu_frame_np);

	make_btn_energia_v(menu_frame_np);

	make_btn_gasto_energetico_v(menu_frame_np);
}

void GraphicsMenu::make_btn_temp_interna_v(NodePath menu_frame_np) {
	btn_temp_interna_v = new PGButton("btn_temp_interna_v");
	btn_temp_interna_v->setup("", 0.1);
	np_btn_temp_interna_v = grafico_variavel_frame_np.attach_new_node(btn_temp_interna_v);
	np_btn_temp_interna_v.set_scale(0.009);
	np_btn_temp_interna_v.set_pos(0.1, 0.0, 0.12);
	//np_btn_temp_interna_v.hide();
	img_btn_temp_interna_v = ImageRepository::get_instance()->get_image("modeloTemperatura");
	img_btn_temp_interna_v.reparent_to(grafico_variavel_frame_np);
	img_btn_temp_interna_v.set_scale(0.009);
	img_btn_temp_interna_v.set_pos(0.1, 0.0, 0.12);
	//img_btn_temp_interna_v.hide();
	led_off_temp_interna_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_interna_v.reparent_to(grafico_variavel_frame_np);
	led_off_temp_interna_v.set_scale(0.004);
	led_off_temp_interna_v.set_pos(0.1, 0.0, 0.32);
	//led_off_temp_interna_v.hide();
	led_on_temp_interna_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_interna_v.reparent_to(grafico_variavel_frame_np);
	led_on_temp_interna_v.set_scale(0.004);
	led_on_temp_interna_v.set_pos(0.1, 0.0, 0.32);
	led_on_temp_interna_v.hide();
	btn_temp_interna_v->setup(img_btn_temp_interna_v);
	btn_temp_interna_v->set_frame(-5.0 , 5.0 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_hidratacao_v(NodePath menu_frame_np) {
	btn_hidratacao_v = new PGButton("btn_hidratacao_v");
	btn_hidratacao_v->setup("", 0.1);
	np_btn_hidratacao_v = grafico_variavel_frame_np.attach_new_node(btn_hidratacao_v);
	np_btn_hidratacao_v.set_scale(0.009);
	np_btn_hidratacao_v.set_pos(0.26, 0.0, 0.12);
	//np_btn_hidratacao_v.hide();
	img_btn_hidratacao_v = ImageRepository::get_instance()->get_image("modeloHidratacao");
	img_btn_hidratacao_v.reparent_to(grafico_variavel_frame_np);
	img_btn_hidratacao_v.set_scale(0.009);
	img_btn_hidratacao_v.set_pos(0.26, 0.0, 0.12);
	//img_btn_hidratacao_v.hide();
	led_off_hidratacao_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_hidratacao_v.reparent_to(grafico_variavel_frame_np);
	led_off_hidratacao_v.set_scale(0.004);
	led_off_hidratacao_v.set_pos(0.26, 0.0, 0.32);
	//led_off_hidratacao_v.hide();
	led_on_hidratacao_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_hidratacao_v.reparent_to(grafico_variavel_frame_np);
	led_on_hidratacao_v.set_scale(0.004);
	led_on_hidratacao_v.set_pos(0.26, 0.0, 0.32);
	led_on_hidratacao_v.hide();
	btn_hidratacao_v->setup(img_btn_hidratacao_v);
	btn_hidratacao_v->set_frame(-5.0, 5.0, -10.0, 10.0);
}

void GraphicsMenu::make_btn_temp_ar_v(NodePath menu_frame_np) {
	btn_temp_ar_v = new PGButton("btn_temp_ar_v");
	btn_temp_ar_v->setup("", 0.1);
	np_btn_temp_ar_v = grafico_variavel_frame_np.attach_new_node(btn_temp_ar_v);
	np_btn_temp_ar_v.set_scale(0.009);
	np_btn_temp_ar_v.set_pos(0.42, 0.0, 0.12);
	//np_btn_temp_ar_v.hide();
	img_btn_temp_ar_v = ImageRepository::get_instance()->get_image("mundo_temp2");
	img_btn_temp_ar_v.reparent_to(grafico_variavel_frame_np);
	img_btn_temp_ar_v.set_scale(0.009);
	img_btn_temp_ar_v.set_pos(0.42, 0.0, 0.12);
	//img_btn_temp_ar_v.hide();
	led_off_temp_ar_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_ar_v.reparent_to(grafico_variavel_frame_np);
	led_off_temp_ar_v.set_scale(0.004);
	led_off_temp_ar_v.set_pos(0.42, 0.0, 0.32);
	led_off_temp_ar_v.hide();
	led_on_temp_ar_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_ar_v.reparent_to(grafico_variavel_frame_np);
	led_on_temp_ar_v.set_scale(0.004);
	led_on_temp_ar_v.set_pos(0.42, 0.0, 0.32);
	//led_on_temp_ar_v.hide();
	btn_temp_ar_v->setup(img_btn_temp_ar_v);
	btn_temp_ar_v->set_frame(-8.1 , 8.1 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_umidade_v(NodePath menu_frame_np) {
	btn_umidade_v = new PGButton("btn_umidade_v");
	btn_umidade_v->setup("", 0.1);
	np_btn_umidade_v = grafico_variavel_frame_np.attach_new_node(btn_umidade_v);
	np_btn_umidade_v.set_scale(0.008);
	np_btn_umidade_v.set_pos(0.60, 0.0, 0.12);
	//botao4UmidadeAr_np.hide();
	img_btn_umidade_v = ImageRepository::get_instance()->get_image("mundo_umi");
	img_btn_umidade_v.reparent_to(grafico_variavel_frame_np);
	img_btn_umidade_v.set_scale(0.008);
	img_btn_umidade_v.set_pos(0.60, 0.0, 0.12);
	//botao4UmidadeAr_image.hide();
	led_off_umidade_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_umidade_v.reparent_to(grafico_variavel_frame_np);
	led_off_umidade_v.set_scale(0.004);
	led_off_umidade_v.set_pos(0.60, 0.0, 0.32);
	//botao4UmidadeAr_ledOFF.hide();
	led_on_umidade_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_umidade_v.reparent_to(grafico_variavel_frame_np);
	led_on_umidade_v.set_scale(0.004);
	led_on_umidade_v.set_pos(0.60, 0.0, 0.32);
	led_on_umidade_v.hide();
	btn_umidade_v->setup(img_btn_umidade_v);
	btn_umidade_v->set_frame(-8.8 , 8.8 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_temp_solo_v(NodePath menu_frame_np) {
	btn_temp_solo_v = new PGButton("btn_temp_solo_v");
	btn_temp_solo_v->setup("", 0.1);
	np_btn_temp_solo_v = grafico_variavel_frame_np.attach_new_node(btn_temp_solo_v);
	np_btn_temp_solo_v.set_scale(0.009);
	np_btn_temp_solo_v.set_pos(0.78, 0.0, 0.12);
	//np_btn_temp_solo_v.hide();
	img_btn_temp_solo_v = ImageRepository::get_instance()->get_image("mundo_temp3");
	img_btn_temp_solo_v.reparent_to(grafico_variavel_frame_np);
	img_btn_temp_solo_v.set_scale(0.009);
	img_btn_temp_solo_v.set_pos(0.78, 0.0, 0.12);
	//img_btn_temp_solo_v.hide();
	led_off_temp_solo_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_temp_solo_v.reparent_to(grafico_variavel_frame_np);
	led_off_temp_solo_v.set_scale(0.004);
	led_off_temp_solo_v.set_pos(0.78, 0.0, 0.32);
	//led_off_temp_solo_v.hide();
	led_on_temp_solo_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_temp_solo_v.reparent_to(grafico_variavel_frame_np);
	led_on_temp_solo_v.set_scale(0.004);
	led_on_temp_solo_v.set_pos(0.78, 0.0, 0.32);
	led_on_temp_solo_v.hide();
	btn_temp_solo_v->setup(img_btn_temp_solo_v);
	btn_temp_solo_v->set_frame(-8.1 , 8.1 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_alimentacao_v(NodePath menu_frame_np) {
	btn_alimentacao_v = new PGButton("btn_alimentacao_v");
	btn_alimentacao_v->setup("", 0.1);
	np_btn_alimentacao_v = grafico_variavel_frame_np.attach_new_node(btn_alimentacao_v);
	np_btn_alimentacao_v.set_scale(0.009);
	np_btn_alimentacao_v.set_pos(0.94, 0.0, 0.12);
	//np_btn_alimentacao_v.hide();
	img_btn_alimentacao_v = ImageRepository::get_instance()->get_image("modeloNutricional");
	img_btn_alimentacao_v.reparent_to(grafico_variavel_frame_np);
	img_btn_alimentacao_v.set_scale(0.009);
	img_btn_alimentacao_v.set_pos(0.94, 0.0, 0.12);
	//img_btn_alimentacao_v.hide();
	led_off_alimentacao_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_alimentacao_v.reparent_to(grafico_variavel_frame_np);
	led_off_alimentacao_v.set_scale(0.004);
	led_off_alimentacao_v.set_pos(0.94, 0.0, 0.32);
	//led_off_alimentacao_v.hide();
	led_on_alimentacao_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_alimentacao_v.reparent_to(grafico_variavel_frame_np);
	led_on_alimentacao_v.set_scale(0.004);
	led_on_alimentacao_v.set_pos(0.94, 0.0, 0.32);
	led_on_alimentacao_v.hide();
	btn_alimentacao_v->setup(img_btn_alimentacao_v);
	btn_alimentacao_v->set_frame(-5.0 , 5.0, -10.0, 10.0);
}

void GraphicsMenu::make_btn_energia_v(NodePath menu_frame_np) {
	btn_energia_v = new PGButton("btn_energia_v");
	btn_energia_v->setup("", 0.1);
	np_btn_energia_v = grafico_variavel_frame_np.attach_new_node(btn_energia_v);
	np_btn_energia_v.set_scale(0.009);
	np_btn_energia_v.set_pos(1.10, 0.0, 0.12);
	//np_btn_energia_v.hide();
	img_btn_energia_v = ImageRepository::get_instance()->get_image("modeloEnergia");
	img_btn_energia_v.reparent_to(grafico_variavel_frame_np);
	img_btn_energia_v.set_scale(0.009);
	img_btn_energia_v.set_pos(1.10, 0.0, 0.12);
	//img_btn_energia_v.hide();
	led_off_energia_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_energia_v.reparent_to(grafico_variavel_frame_np);
	led_off_energia_v.set_scale(0.004);
	led_off_energia_v.set_pos(1.10, 0.0, 0.32);
	//led_off_energia_v.hide();
	led_on_energia_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_energia_v.reparent_to(grafico_variavel_frame_np);
	led_on_energia_v.set_scale(0.004);
	led_on_energia_v.set_pos(1.10, 0.0, 0.32);
	led_on_energia_v.hide();
	btn_energia_v->setup(img_btn_energia_v);
	btn_energia_v->set_frame(-5.0 , 5.0 , -10.0, 10.0);
}

void GraphicsMenu::make_btn_gasto_energetico_v(NodePath menu_frame_np) {
	btn_gasto_energetico_v = new PGButton("btn_gasto_energetico_v");
	btn_gasto_energetico_v->setup("", 0.1);
	np_btn_gasto_energetico_v = grafico_variavel_frame_np.attach_new_node(btn_gasto_energetico_v);
	np_btn_gasto_energetico_v.set_scale(0.009);
	np_btn_gasto_energetico_v.set_pos(1.28, 0.0, 0.12);
	//np_btn_gasto_energetico_v.hide();
	img_btn_gasto_energetico_v = ImageRepository::get_instance()->get_image("modeloGatoEnergetico");
	img_btn_gasto_energetico_v.reparent_to(grafico_variavel_frame_np);
	img_btn_gasto_energetico_v.set_scale(0.009);
	img_btn_gasto_energetico_v.set_pos(1.28, 0.0, 0.12);
	//img_btn_gasto_energetico_v.hide();
	led_off_gasto_energetico_v = ImageRepository::get_instance()->get_image("GrayLed");
	led_off_gasto_energetico_v.reparent_to(grafico_variavel_frame_np);
	led_off_gasto_energetico_v.set_scale(0.004);
	led_off_gasto_energetico_v.set_pos(1.28, 0.0, 0.32);
	//led_off_gasto_energetico_v.hide();
	led_on_gasto_energetico_v = ImageRepository::get_instance()->get_image("GreenLed");
	led_on_gasto_energetico_v.reparent_to(grafico_variavel_frame_np);
	led_on_gasto_energetico_v.set_scale(0.004);
	led_on_gasto_energetico_v.set_pos(1.28, 0.0, 0.32);
	led_on_gasto_energetico_v.hide();
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
	label_txt_tipo_graf.hide();
	np_btn_graf_tempo.hide();
	led_off_graf_tempo.hide();
	led_on_graf_tempo.hide();
	np_btn_graf_variavel.hide();
	led_off_graf_variavel.hide();
	led_on_graf_variavel.hide();
}

//Torna invisivel o painel que contem os botoes para ativar os graficos de tempo.
void GraphicsMenu::hide_menu_graf_tempo() {
	np_btn_temp_interna.hide();
	img_btn_temp_interna.hide();
	led_on_temp_interna.hide();
	led_off_temp_interna.hide();
	np_btn_hidratacao.hide();
	img_btn_hidratacao.hide();
	led_on_hidratacao.hide();
	led_off_hidratacao.hide();
	np_btn_temp_ar.hide();
	img_btn_temp_ar.hide();
	led_on_temp_ar.hide();
	led_off_temp_ar.hide();
	np_btn_umidade.hide();
	img_btn_umidade.hide();
	led_on_umidade.hide();
	led_off_umidade.hide();
	np_btn_temp_solo.hide();
	img_btn_temp_solo.hide();
	led_on_temp_solo.hide();
	led_off_temp_solo.hide();
	np_btn_alimentacao.hide();
	img_btn_alimentacao.hide();
	led_on_alimentacao.hide();
	led_off_alimentacao.hide();
	np_btn_energia.hide();
	img_btn_energia.hide();
	led_on_energia.hide();
	led_off_energia.hide();
	np_btn_gasto_energetico.hide();
	img_btn_gasto_energetico.hide();
	led_on_gasto_energetico.hide();
	led_off_gasto_energetico.hide();
}

//Torna invisivel o painel que contem os botoes para ativar os graficos de variaveis.
void GraphicsMenu::hide_menu_graf_variavel() {
//	this->esconde_painel_grafico_tempo();
	grafico_variavel_frame_np.hide();
}

//Torna visivel o painel que contem os botoes para ativar os graficos de tempo.
void GraphicsMenu::show_menu_graf_tempo() {
	label_txt_tipo_graf.show();
	np_btn_graf_tempo.show();
	led_on_graf_tempo.show();
	np_btn_graf_variavel.show();
	led_off_graf_variavel.show();
	np_btn_temp_interna.show();
	img_btn_temp_interna.show();
	led_on_temp_interna.show();
	np_btn_hidratacao.show();
	img_btn_hidratacao.show();
	led_on_hidratacao.show();
	np_btn_temp_ar.show();
	img_btn_temp_ar.show();
	led_off_temp_ar.show();
	np_btn_umidade.show();
	img_btn_umidade.show();
	led_off_umidade.show();
	np_btn_temp_solo.show();
	img_btn_temp_solo.show();
	led_off_temp_solo.show();
	np_btn_alimentacao.show();
	img_btn_alimentacao.show();
	led_off_alimentacao.show();
	np_btn_energia.show();
	img_btn_energia.show();
	led_off_energia.show();
	np_btn_gasto_energetico.show();
	img_btn_gasto_energetico.show();
	led_off_gasto_energetico.show();
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
	grafico_variavel_frame_np.show();
}

//Constroi o painel que contém os graficos.
void GraphicsMenu::build_options() {
	option_frame = new PGVirtualFrame("Frame do menu de opcoes");
	option_frame->setup(1.58, 2.0);
	PGFrameStyle style = option_frame->get_frame_style(option_frame->get_state());
	style.set_type(PGFrameStyle::T_flat);
	option_frame->set_frame_style(option_frame->get_state(), style);
	option_frame_np = NodePath(option_frame);
	option_frame_np.reparent_to(Simdunas::get_window()->get_aspect_2d());
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
	grafico_variavel_frame_np.reparent_to(Simdunas::get_window()->get_aspect_2d());
	//Seta a posição do frame
	grafico_variavel_frame_np.set_pos(1.0, 0.0, -1.0);
	//Seta a cor do frame
	grafico_variavel_frame_np.set_color(0.8, 0.8, 0.8);
	//Seta a transparencia do frame.
	grafico_variavel_frame_np.set_transparency(TransparencyAttrib::M_alpha);
	grafico_variavel_frame_np.set_alpha_scale(0.85);
	grafico_variavel_frame_np.hide();
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

//Constroi o grafico de temperatura interna X tempo.
void GraphicsMenu::novo_grafico1_TempInterna() {
	graphic = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaLagarto(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaLagarto()), vector->getSmallestElement(vector->getVectorTemperaturaLagarto()), true);
	graphic->set_Position_Graphic(0.4, 1.0);
	graphic->set_scale(0.86);
	graphic->set_Titulo_Grafico("Temperatura Interna");
	graphic->set_Titulo_EixoX("Tempo (h)");
	graphic->set_Titulo_EixoY("Temperatura (C)");
	graphic->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorTemperaturaLagarto());
}

//Constroi o grafico de hidratacao X tempo.
void GraphicsMenu::novo_grafico2_Hidratacao() {
	graphic2 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorHidratacaoLagarto(), 0, 0, 100, 0, true);
	graphic2->set_Position_Graphic(0.4, 1.0);
	graphic2->set_scale(0.86);
	graphic2->set_Titulo_Grafico("Hidratacao do lagarto");
	graphic2->set_Titulo_EixoX("Tempo (h)");
	graphic2->set_Titulo_EixoY("Hidratacao (%)");
	graphic2->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorHidratacaoLagarto());
}

//Constroi o grafico de temperatura do ar X tempo.
void GraphicsMenu::novo_grafico3_TempAr() {
	graphic3 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaAr(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaAr()), vector->getSmallestElement(vector->getVectorTemperaturaAr()), true);
	graphic3->set_Position_Graphic(0.4, 1.0);
	graphic3->set_scale(0.86);
	graphic3->set_Titulo_Grafico("Temperatura do ar.");
	graphic3->set_Titulo_EixoX("Tempo (h)");
	graphic3->set_Titulo_EixoY("Temperatura (c)");
	graphic3->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorTemperaturaAr());
}

//Constroi o grafico de umidade X tempo.
void GraphicsMenu::novo_grafico4_Umidade() {
	graphic4 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorUmidadeAmbiente(), 0, 0, 100, 0, true);
	graphic4->set_Position_Graphic(0.4, 1.0);
	graphic4->set_scale(0.86);
	graphic4->set_Titulo_Grafico("Umidade do ar.");
	graphic4->set_Titulo_EixoX("Tempo (h)");
	graphic4->set_Titulo_EixoY("Umidade");
	graphic4->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorUmidadeAmbiente());
}

//Constroi o grafico de temperatura do solo X tempo.
void GraphicsMenu::novo_grafico5_TempSolo() {
	graphic5 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorTemperaturaSolo(), 0, 0, vector->getLargestElement(vector->getVectorTemperaturaSolo()), vector->getSmallestElement(vector->getVectorTemperaturaSolo()), true);
	graphic5->set_Position_Graphic(0.4, 1.0);
	graphic5->set_scale(0.86);
	graphic5->set_Titulo_Grafico("Temperatura do Solo");
	graphic5->set_Titulo_EixoX("Tempo (h)");
	graphic5->set_Titulo_EixoY("Temperatura (C)");
	graphic5->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorTemperaturaSolo());
}

//Constroi o grafico de alimentacao X tempo.
void GraphicsMenu::novo_grafico6_Alimentacao() {
	graphic6 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorAlimentacao(), 0, 0, vector->getLargestElement(vector->getVectorAlimentacao()), vector->getSmallestElement(vector->getVectorAlimentacao()), true);
	graphic6->set_Position_Graphic(0.4, 1.0);
	graphic6->set_scale(0.86);
	graphic6->set_Titulo_Grafico("Alimentacao");
	graphic6->set_Titulo_EixoX("Tempo (h)");
	graphic6->set_Titulo_EixoY("Alimentacao");
	graphic6->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorAlimentacao());
}

//Constroi o grafico de energia X tempo.
void GraphicsMenu::novo_grafico7_Energia() {
	graphic7 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorEnergia(), 0, 0, 100, 0, true);
	graphic7->set_Position_Graphic(0.4, 1.0);
	graphic7->set_scale(0.86);
	graphic7->set_Titulo_Grafico("Energia");
	graphic7->set_Titulo_EixoX("Tempo (h)");
	graphic7->set_Titulo_EixoY("Energia");
	graphic7->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorEnergia());

}

//Constroi o grafico de gasto energetico X tempo.
void GraphicsMenu::novo_grafico8_GastoEnergetico() {
	graphic8 = new Graphics((option_frame_np), vector->getVectorTempo(), vector->getVectorGastoEnergeticoTotal(), 0, 0, vector->getLargestElement(vector->getVectorGastoEnergeticoTotal()), vector->getSmallestElement(vector->getVectorGastoEnergeticoTotal()), true);
	graphic8->set_Position_Graphic(0.4, 1.0);
	graphic8->set_scale(0.86);
	graphic8->set_Titulo_Grafico("Gasto energetico");
	graphic8->set_Titulo_EixoX("Tempo (h)");
	graphic8->set_Titulo_EixoY("Gasto energetico");
	graphic8->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorGastoEnergiticoTotal());
}

//Desliga as luzes que indicam quais graficos estao ativos no painel de tempo.
void GraphicsMenu::desliga_leds_painel_tempo() {
	led_on_temp_interna.hide();
	led_on_hidratacao.hide();
	led_on_temp_ar.hide();
	led_on_umidade.hide();
	led_on_temp_solo.hide();
	led_on_alimentacao.hide();
	led_on_energia.hide();
	led_on_gasto_energetico.hide();
	led_off_temp_interna.show();
	led_off_hidratacao.show();
	led_off_temp_ar.show();
	led_off_umidade.show();
	led_off_temp_solo.show();
	led_off_alimentacao.show();
	led_off_energia.show();
	led_off_gasto_energetico.show();
}

//Desliga as luzes que indicam quais graficos estao ativos no painel de variavel.
void GraphicsMenu::desliga_leds_painel_variavel() {
	led_on_temp_interna_v.hide();
	led_on_hidratacao_v.hide();
	led_on_temp_ar_v.hide();
	led_on_umidade_v.hide();
	led_on_temp_solo_v.hide();
	led_on_alimentacao_v.hide();
	led_on_energia_v.hide();
	led_on_gasto_energetico_v.hide();
	led_off_temp_interna_v.show();
	led_off_hidratacao_v.show();
	led_off_temp_ar_v.show();
	led_off_umidade_v.show();
	led_off_temp_solo_v.show();
	led_off_alimentacao_v.show();
	led_off_energia_v.show();
	led_off_gasto_energetico_v.show();
}
