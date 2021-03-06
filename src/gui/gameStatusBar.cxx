/*
 * gameStatusBar.cxx
 *
 *  Created on: Oct 4, 2010
 *      Author: jonatas
 */

#include "gameStatusBar.h"
#include "simdunas.h"
#include "imageRepository.h"

GameStatusBar::GameStatusBar(NodePath menu_frame_np) {
	make_relogio(menu_frame_np);

	make_life_bar(menu_frame_np);

	make_label_life(menu_frame_np);

	make_piscar_model(menu_frame_np);

	make_hidratacao_bar(menu_frame_np);

	make_temperatura_bar(menu_frame_np);

	make_temperatura_ambiente_bar(menu_frame_np);

	make_umidade_bar(menu_frame_np);

	make_estado_reprodutivo(menu_frame_np);

	make_idade(menu_frame_np);

	make_botao_grafico(menu_frame_np);
}

GameStatusBar::~GameStatusBar() {}

NodePath GameStatusBar::get_relogio() {
	return relogio;
}

PT(TextNode) GameStatusBar::get_label_life() {
	return label_life;
}

NodePath GameStatusBar::get_piscar_model() {
	return piscar_model;
}

ScrollBar GameStatusBar::get_hidratacao_scroll_bar() {
	return hidratacao_scroll_bar;
}

PT(TextNode) GameStatusBar::get_label_hidratacao() {
	return label_hidratacao;
}

ScrollBar GameStatusBar::get_temperatura_scroll_bar() {
	return temperatura_scroll_bar;
}

PT(TextNode) GameStatusBar::get_label_temperatura() {
	return label_temperatura;
}

PT(TextNode) GameStatusBar::get_label_temperatura_ambiente() {
	return label_temperatura_ambiente;
}

PT(TextNode) GameStatusBar::get_label_umidade() {
	return label_umidade;
}

ScrollBar GameStatusBar::get_temperatura_ambiente_scroll_bar() {
	return temperatura_ambiente_scroll_bar;
}

ScrollBar GameStatusBar::get_umidade_scroll_bar() {
	return umidade_scroll_bar;
}

PT(TextNode) GameStatusBar::get_label_egg_count() {
	return label_egg_count;
}

NodePath GameStatusBar::get_led_estado_reprodutivo() {
	return led_estado_reprodutivo;
}

PT(TextNode) GameStatusBar::get_label_idade() {
	return label_idade;
}

PT(TextNode) GameStatusBar::get_label_idade_numero() {
	return label_idade_numero;
}

PT(PGButton) GameStatusBar::get_btn_grafico() {
	return btn_grafico;
}

ImageBar GameStatusBar::get_life_bar() {
	return life_bar;
}


// Desenha o relógio para mostrar dia e noite
void GameStatusBar::make_relogio(NodePath menu_frame_np) {
	relogio = ImageRepository::get_instance()->get_image("diaEnoite");
	relogio.reparent_to(menu_frame_np);
	relogio.set_scale(0.016);
	relogio.set_pos(0.22, 0.0, 1.8);
	relogio.set_hpr(0.0, 0.0, 270.0);
	//relogio.set_transparency(TransparencyAttrib::M_alpha);
//	relogio.set_alpha_scale(1.0);

	relogio_pointer = ImageRepository::get_instance()->get_image("ponteiro");
	relogio_pointer.reparent_to(menu_frame_np);
	relogio_pointer.set_scale(0.005);
	relogio_pointer.set_pos(0.22, 0.0, 1.94);
	relogio_pointer.set_hpr(0.0, 0.0, 180.0);
//	relogio_pointer.set_transparency(TransparencyAttrib::M_alpha);
//	relogio_pointer.set_alpha_scale(1.0);

	hint_relogio = new Hint(menu_frame_np, relogio, "hint_relogio", ConfigVariableString("msg-hinttempo","Tempo"));
}

// Desenha barra do Life
void GameStatusBar::make_life_bar(NodePath menu_frame_np) {
	img_life_bar = ImageRepository::get_instance()->get_image("calango_color");
	img_life_bar.reparent_to(menu_frame_np);
	img_life_bar.set_scale(0.02);
	img_life_bar.set_sz(0.028);
	img_life_bar.set_pos(0.22, 0.0, 1.49);
	img_life_bar.set_transparency(TransparencyAttrib::M_alpha);
	img_life_bar.set_alpha_scale(0.75);

	border_life_bar = ImageRepository::get_instance()->get_image("calango_border");
	border_life_bar.reparent_to(menu_frame_np);
	border_life_bar.set_scale(0.02);
	border_life_bar.set_sz(0.028);
	border_life_bar.set_pos(0.22, 0.0, 1.49);

	//Criando uma barra para mostrar o "life"
	life_bar = ImageBar(menu_frame_np, border_life_bar, img_life_bar);

	hint_life_bar = new Hint(menu_frame_np, img_life_bar, "hint_life_bar", ConfigVariableString("msg-hintenerg","Energia"));
}

//Criando o label do life.
void GameStatusBar::make_label_life(NodePath menu_frame_np) {
	label_life = new TextNode("VIDA");
	label_life->set_text("VIDA");

	np_label_life = menu_frame_np.attach_new_node(label_life);
	np_label_life.set_pos(0.14, 0.0, 1.49);
	np_label_life.set_scale(0.05);
	np_label_life.set_color(0.0, 0.0, 0.0, 1,0);
}

//criando a imagem do calango que vai ficar piscando quando o calango comer
void GameStatusBar::make_piscar_model(NodePath menu_frame_np) {
	piscar_model = ImageRepository::get_instance()->get_image("pisca_life");
	piscar_model.set_scale(0.18);
	piscar_model.set_p(270);
	piscar_model.set_h(180);
	piscar_model.set_pos(0.80, 0.0, 0.49);
	piscar_model.detach_node();
}

// Barra da Hidratação
void GameStatusBar::make_hidratacao_bar(NodePath menu_frame_np) {
	img_hidratacao_bar = ImageRepository::get_instance()->get_image("modeloHidratacao");
	img_hidratacao_bar.reparent_to(menu_frame_np);
	img_hidratacao_bar.set_scale(0.01);
	img_hidratacao_bar.set_pos(0.10, 0.0, 1.25);
	img_hidratacao_bar.set_transparency(TransparencyAttrib::M_alpha);
	img_hidratacao_bar.set_alpha_scale(1.0);

	hidratacao_bar = ImageRepository::get_instance()->get_image("barra-hidratacao-espelhada");
	hidratacao_bar.reparent_to(menu_frame_np);
	hidratacao_bar.set_scale(0.013);
	hidratacao_bar.set_pos(0.28, 0.0, 1.19);

	hidratacao_bar_pointer = ImageRepository::get_instance()->get_image("ponteiro");
	hidratacao_bar_pointer.reparent_to(hidratacao_bar);
	hidratacao_bar_pointer.set_scale(0.18);
	hidratacao_bar_pointer.set_pos(0.0, 0.0, 0.0);
	hidratacao_bar_pointer_red = ImageRepository::get_instance()->get_image("ponteiro_red");
	hidratacao_bar_pointer_red.reparent_to(hidratacao_bar);
	hidratacao_bar_pointer_red.set_scale(0.18);
	hidratacao_bar_pointer_red.stash();

	//Criando a barra para mostrar o nivel de hidratação.
	hidratacao_scroll_bar = ScrollBar(menu_frame_np, hidratacao_bar, hidratacao_bar_pointer);

	//Criando o label da hidratação.
	label_hidratacao = new TextNode("Hidratação");
	label_hidratacao->set_text("");
	np_label_hidratacao = menu_frame_np.attach_new_node(label_hidratacao);
	np_label_hidratacao.set_pos(0.16, 0.0, 1.22);
	np_label_hidratacao.set_scale(0.04);
	np_label_hidratacao.set_color(0.0, 0.0, 0.0, 1,0);

	hint_hidratacao = new Hint(menu_frame_np, hidratacao_bar, "hint_hidratacao", ConfigVariableString("msg-hinthidra", "Hidratação"));
	hint_hidratacao2 = new Hint(menu_frame_np, img_hidratacao_bar, "hint_hidratacao2", ConfigVariableString("msg-hinthidra", "Hidratação"));
}

// Barra da temperatura interna do lagarto
void GameStatusBar::make_temperatura_bar(NodePath menu_frame_np) {
	img_temperatura_bar = ImageRepository::get_instance()->get_image("modeloTemperatura");
	img_temperatura_bar.reparent_to(menu_frame_np);
	img_temperatura_bar.set_scale(0.01);
	img_temperatura_bar.set_pos(0.10, 0.0, 1.05);
	img_temperatura_bar.set_alpha_scale(0.9);

	temperatura_bar = ImageRepository::get_instance()->get_image("barra-hidratacao4");
	temperatura_bar.reparent_to(menu_frame_np);
	//temperaturaBar.set_scale(1.3);
	//temperaturaBar.set_pos(18.0, 0.0, -6.0);
	temperatura_bar.set_scale(0.013);
	temperatura_bar.set_pos(0.28, 0.0, 0.99);

	temperatura_bar_pointer = ImageRepository::get_instance()->get_image("ponteiro");
	temperatura_bar_pointer.reparent_to(temperatura_bar);
	temperatura_bar_pointer.set_scale(0.18);
	temperatura_bar_pointer.set_pos(0.0, 0.0, 0.0);
	temperatura_bar_pointer_red = ImageRepository::get_instance()->get_image("ponteiro_red");
	temperatura_bar_pointer_red.reparent_to(temperatura_bar);
	temperatura_bar_pointer_red.set_scale(0.18);
	temperatura_bar_pointer_red.stash();

	//Criando a barra para mostrar a temperatura.
	temperatura_scroll_bar = ScrollBar(menu_frame_np, temperatura_bar, temperatura_bar_pointer);

	//Criando o label da temperatura.
	label_temperatura = new TextNode("Temperatura");
	label_temperatura->set_text("");

	np_label_temperatura = menu_frame_np.attach_new_node(label_temperatura);
	np_label_temperatura.set_pos(0.16, 0.0,1.02);
	np_label_temperatura.set_scale(0.04);
	np_label_temperatura.set_color(0.0, 0.0, 0.0, 1,0);

	hint_temperatura = new Hint(menu_frame_np, temperatura_bar, "hint_temperatura", ConfigVariableString("msg-hinttempi","Temperatura Interna"));
	hint_temperatura2 = new Hint(menu_frame_np, img_temperatura_bar, "hint_temperatura2", ConfigVariableString("msg-hinttempi","Temperatura Interna"));
}

// Barra da temperatura do ambiente
void GameStatusBar::make_temperatura_ambiente_bar(NodePath menu_frame_np) {
	img_temperatura_ambiente_bar = ImageRepository::get_instance()->get_image("mundo_temp2");
	img_temperatura_ambiente_bar.reparent_to(menu_frame_np);
	img_temperatura_ambiente_bar.set_scale(0.008);
	img_temperatura_ambiente_bar.set_pos(0.10, 0.0, 0.85);
	img_temperatura_ambiente_bar.set_alpha_scale(0.9);

	temperatura_ambiente_bar = ImageRepository::get_instance()->get_image("barra-hidratacao4");
	temperatura_ambiente_bar.reparent_to(menu_frame_np);
	//temperaturaAmbienteBar.set_scale(1.3);
	//temperaturaAmbienteBar.set_pos(18.0, 0.0, -6.0);
	temperatura_ambiente_bar.set_scale(0.013);
	temperatura_ambiente_bar.set_pos(0.28, 0.0, 0.79);

	temperatura_ambiente_bar_pointer = ImageRepository::get_instance()->get_image("ponteiro");
	temperatura_ambiente_bar_pointer.reparent_to(temperatura_ambiente_bar);
	temperatura_ambiente_bar_pointer.set_scale(0.18);
	temperatura_ambiente_bar_pointer.set_pos(0.0, 0.0, 0.0);

	//Criando a barra para mostrar a temperatura.
	temperatura_ambiente_scroll_bar = ScrollBar(menu_frame_np, temperatura_ambiente_bar, temperatura_ambiente_bar_pointer);

	//Criando o label da temperatura do ambiente.
	label_temperatura_ambiente = new TextNode("Temperatura do ambiente");
	label_temperatura_ambiente->set_text("");

	np_label_temperatura_ambiente = menu_frame_np.attach_new_node(label_temperatura_ambiente);
	np_label_temperatura_ambiente.set_pos(0.16, 0.0, 0.82);
	np_label_temperatura_ambiente.set_scale(0.04);
	np_label_temperatura_ambiente.set_color(0.0, 0.0, 0.0, 1,0);

	hint_temperatura_ambiente = new Hint(menu_frame_np, temperatura_ambiente_bar, "hint_temperatura_ambiente", ConfigVariableString("msg-hinttemps","Temperatura do Solo"));
	hint_temperatura_ambiente2 = new Hint(menu_frame_np, img_temperatura_ambiente_bar, "hint_temperatura_ambiente2", ConfigVariableString("msg-hinttemps","Temperatura do Solo"));
}

// Barra de umidade do ar
void GameStatusBar::make_umidade_bar(NodePath menu_frame_np) {
	img_umidade_bar = ImageRepository::get_instance()->get_image("mundo_umi");
	img_umidade_bar.reparent_to(menu_frame_np);
	img_umidade_bar.set_scale(0.007);
	img_umidade_bar.set_pos(0.10, 0.0, 0.65);
	img_umidade_bar.set_alpha_scale(0.9);

	umidade_bar = ImageRepository::get_instance()->get_image("barra-hidratacao-espelhada");
	umidade_bar.reparent_to(menu_frame_np);
	//umidadeBar.set_scale(1.3);
	//umidadeBar.set_pos(18.0, 0.0, -6.0);
	umidade_bar.set_scale(0.013);
	umidade_bar.set_pos(0.28, 0.0, 0.59);

	umidade_bar_pointer = ImageRepository::get_instance()->get_image("ponteiro");
	umidade_bar_pointer.reparent_to(umidade_bar);
	umidade_bar_pointer.set_scale(0.18);
	umidade_bar_pointer.set_pos(0.0, 0.0, 0.0);

	//Criando a barra para mostrar a umidade.
	umidade_scroll_bar = ScrollBar(menu_frame_np, umidade_bar, umidade_bar_pointer);

	//Criando o label da umidade.
	label_umidade = new TextNode("Temperatura do ambiente");
	label_umidade->set_text("");

	np_label_umidade = menu_frame_np.attach_new_node(label_umidade);
	np_label_umidade.set_pos(0.16, 0.0, 0.62);
	np_label_umidade.set_scale(0.04);
	np_label_umidade.set_color(0.0, 0.0, 0.0, 1,0);

	hint_umidade = new Hint(menu_frame_np, umidade_bar, "hint_umidade", ConfigVariableString("msg-hintumi", "Umidade do Ar"));
	hint_umidade2 = new Hint(menu_frame_np, img_umidade_bar, "hint_umidade2", ConfigVariableString("msg-hintumi", "Umidade do Ar"));
}

// Aviso do estado reprodutivo
void GameStatusBar::make_estado_reprodutivo(NodePath menu_frame_np) {
	estado_reprodutivo = ImageRepository::get_instance()->get_image("(fe)male_symbol");
	estado_reprodutivo.reparent_to(menu_frame_np);
	estado_reprodutivo.set_scale(0.007);
	estado_reprodutivo.set_pos(0.10, 0.0, 0.33);

	//led é a luz que indica se o estado reprodutivo está ativo ou não.
	led_estado_reprodutivo = ImageRepository::get_instance()->get_image("GrayLed");
	//ledGreen = window->load_model(aspect2d, "models/gui/GreenLed.png");
	led_estado_reprodutivo.reparent_to(menu_frame_np);
	led_estado_reprodutivo.set_scale(0.004);
	led_estado_reprodutivo.set_pos(0.16, 0.0, 0.29);

	egg = ImageRepository::get_instance()->get_image("egg2");
	egg.reparent_to(menu_frame_np);
	egg.set_scale(0.006);
	egg.set_pos(0.28, 0.0, 0.29);

	//Inicia o contador de ovos.
	label_egg_count = new TextNode("0");
	label_egg_count->set_text("0");

	np_label_egg_count = menu_frame_np.attach_new_node(label_egg_count);
	np_label_egg_count.set_pos(0.35, 0.0, 0.27);
	np_label_egg_count.set_scale(0.065);
	np_label_egg_count.set_color(0.0, 0.0, 0.0, 1,0);

	hint_estado_reprodutivo = new Hint(menu_frame_np, estado_reprodutivo, "hint_estado_reprodutivo", ConfigVariableString("msg-hintrepro","Número de Reproduções"));
	hint_egg = new Hint(menu_frame_np, egg, "hint_egg", ConfigVariableString("msg-hintrepro","Número de Reproduções"));
}

// Quantidade de meses de vida do calango
void GameStatusBar::make_idade(NodePath menu_frame_np) {
	img_calendar = ImageRepository::get_instance()->get_image("calendar");
	img_calendar.reparent_to(menu_frame_np);
	img_calendar.set_pos(0.09, 0.0, 0.48);
	img_calendar.set_scale(0.0065);
//	img_calendar.set_transparency(TransparencyAttrib::M_alpha);
//	img_calendar.set_alpha_scale(0.6);

	label_idade = new TextNode("Idade");
	label_idade->set_text(ConfigVariableString("msg-mes", "mês"));

	np_label_idade = menu_frame_np.attach_new_node(label_idade);
	np_label_idade.set_pos(0.23, 0.0, 0.45);
	np_label_idade.set_scale(0.05);
	np_label_idade.set_color(0.0, 0.0, 0.0, 1,0);

	label_idade_numero = new TextNode("0");
	label_idade_numero->set_text("0");

	np_label_idade_numero = menu_frame_np.attach_new_node(label_idade_numero);
	np_label_idade_numero.set_pos(0.18, 0.0, 0.45);
	np_label_idade_numero.set_scale(0.05);
	np_label_idade_numero.set_color(0.0, 0.0, 0.0, 1,0);

	hint_idade = new Hint(menu_frame_np, img_calendar, "hint_idade", ConfigVariableString("msg-hintidade","Idade"));
}

void GameStatusBar::make_botao_grafico(NodePath menu_frame_np) {
	btn_grafico = new PGButton("graficoBtn");
	btn_grafico->setup("Grafico", 0.1);
	np_btn_grafico = menu_frame_np.attach_new_node(btn_grafico);
	np_btn_grafico.set_scale(0.05);
	np_btn_grafico.set_pos(0.25, 0.0, 0.12);

	img_btn_grafico = ImageRepository::get_instance()->get_image("graphic_1");
	img_btn_grafico.reparent_to(menu_frame_np);
	img_btn_grafico.set_pos(0.25, 0.0, 0.12);
	img_btn_grafico.set_scale(0.01);
	btn_grafico->setup(img_btn_grafico);
	btn_grafico->set_frame(-2.0 , 2.0 , -1.5, 1.5);

	hint_btn_grafico = new Hint(menu_frame_np, btn_grafico.p(), img_btn_grafico, "hint_btn_grafico", ConfigVariableString("msg-hintgraf","Gráficos"));
}

//Deixa os componentes de interface que estão no painel lateral invisiveis.
void GameStatusBar::hide_all_status_components() {
	relogio.stash();
	relogio_pointer.stash();
	img_life_bar.stash();
	border_life_bar.stash();
	np_label_life.stash();
	hidratacao_bar.stash();
	hidratacao_bar_pointer.stash();
	img_hidratacao_bar.stash();
	np_label_hidratacao.stash();
	temperatura_bar.stash();
	temperatura_bar_pointer.stash();
	img_temperatura_bar.stash();
	np_label_temperatura.stash();
	temperatura_ambiente_bar.stash();
	temperatura_ambiente_bar_pointer.stash();
	img_temperatura_ambiente_bar.stash();
	np_label_temperatura_ambiente.stash();
	umidade_bar.stash();
	umidade_bar_pointer.stash();
	img_umidade_bar.stash();
	np_label_umidade.stash();
	estado_reprodutivo.stash();
	led_estado_reprodutivo.stash();
	egg.stash();
	np_label_egg_count.stash();
	np_label_idade.stash();
	np_label_idade_numero.stash();
	img_calendar.stash();
}

//Deixa os componentes de interface que estão no painel lateral visiveis.
void GameStatusBar::show_all_status_components(){
	relogio.unstash();
	relogio_pointer.unstash();
	img_life_bar.unstash();
	border_life_bar.unstash();
	np_label_life.unstash();
	hidratacao_bar.unstash();
	hidratacao_bar_pointer.unstash();
	img_hidratacao_bar.unstash();
	np_label_hidratacao.unstash();
	temperatura_bar.unstash();
	temperatura_bar_pointer.unstash();
	img_temperatura_bar.unstash();
	np_label_temperatura.unstash();
	temperatura_ambiente_bar.unstash();
	temperatura_ambiente_bar_pointer.unstash();
	img_temperatura_ambiente_bar.unstash();
	np_label_temperatura_ambiente.unstash();
	umidade_bar.unstash();
	umidade_bar_pointer.unstash();
	img_umidade_bar.unstash();
	np_label_umidade.unstash();
	estado_reprodutivo.unstash();
	led_estado_reprodutivo.unstash();
	egg.unstash();
	np_label_egg_count.unstash();
	np_label_idade.unstash();
	np_label_idade_numero.unstash();
	img_calendar.unstash();
}

void GameStatusBar::set_led_estado_reprodutivo(bool on, NodePath menu_frame_np) {
	led_estado_reprodutivo.remove_node();
	if (on) {
		led_estado_reprodutivo = ImageRepository::get_instance()->get_image("GreenLed");
	}
	else {
		led_estado_reprodutivo = ImageRepository::get_instance()->get_image("GrayLed");
	}
	led_estado_reprodutivo.reparent_to(menu_frame_np);
	led_estado_reprodutivo.set_scale(0.004);
	led_estado_reprodutivo.set_pos(0.16, 0.0, 0.32);
}

void GameStatusBar::hidratacao_critica_on() {
	if (hidrat_critica) return;

	hidrat_critica = true;
	TimeControl::get_instance()->notify("efeito_alerta_hidratacao", efeito_alerta_hidratacao, this, 0.5);
}

void GameStatusBar::hidratacao_critica_off() {
	hidrat_critica = false;
}

AsyncTask::DoneStatus GameStatusBar::efeito_alerta_hidratacao(GenericAsyncTask* task, void* data) {
	GameStatusBar* _this = (GameStatusBar*) data;
	if (!_this->hidrat_critica) {
		_this->hidratacao_bar_pointer.unstash();
		_this->hidratacao_bar_pointer_red.stash();
		_this->np_label_hidratacao.set_color(0, 0, 0, 1);
		return AsyncTask::DS_done;
	}

	if (_this->num_hidrat_vermelho) {
		_this->hidratacao_bar_pointer.unstash();
		_this->hidratacao_bar_pointer_red.stash();
		_this->np_label_hidratacao.set_color(0, 0, 0, 1);
		_this->num_hidrat_vermelho = false;
	}
	else {
		_this->hidratacao_bar_pointer.stash();
		_this->hidratacao_bar_pointer_red.set_pos(_this->hidratacao_bar_pointer.get_pos());
		_this->hidratacao_bar_pointer_red.unstash();
		_this->np_label_hidratacao.set_color(1, 0, 0, 1);
		_this->num_hidrat_vermelho = true;
	}

	return AsyncTask::DS_again;
}

void GameStatusBar::temperatura_critica_on() {
	if (temp_critica) return;

	temp_critica = true;
	TimeControl::get_instance()->notify("efeito_alerta_temperatura", efeito_alerta_temperatura, this, 0.5);
}

void GameStatusBar::temperatura_critica_off() {
	temp_critica = false;
}

AsyncTask::DoneStatus GameStatusBar::efeito_alerta_temperatura(GenericAsyncTask* task, void* data) {
	GameStatusBar* _this = (GameStatusBar*) data;
	if (!_this->temp_critica) {
		_this->temperatura_bar_pointer.unstash();
		_this->temperatura_bar_pointer_red.stash();
		_this->np_label_temperatura.set_color(0, 0, 0, 1);
		return AsyncTask::DS_done;
	}

	if (_this->num_temp_vermelho) {
		_this->temperatura_bar_pointer.unstash();
		_this->temperatura_bar_pointer_red.stash();
		_this->np_label_temperatura.set_color(0, 0, 0, 1);
		_this->num_temp_vermelho = false;
	}
	else {
		_this->temperatura_bar_pointer.stash();
		_this->temperatura_bar_pointer_red.set_pos(_this->temperatura_bar_pointer.get_pos());
		_this->temperatura_bar_pointer_red.unstash();
		_this->np_label_temperatura.set_color(1, 0, 0, 1);
		_this->num_temp_vermelho = true;
	}

	return AsyncTask::DS_again;
}
