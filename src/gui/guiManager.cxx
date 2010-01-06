
#include "windowFramework.h"
#include "graphics.h"
#include "guiManager.h"
#include "menu.h"
#include "mouseButton.h"
#include "vetores.h"
#include "playerControl.h"

#define ABS(a)		(((a) < 0) ? -(a) : (a))
#define LIMITE_SUPERIOR_TEMP_LAGARTO 45.0
#define LIMITE_INFERIOR_TEMP_LAGARTO 9.0
#define LIMITE_SUPERIOR_TEMP_AMBIENTE 65.0
#define LIMITE_INFERIOR_TEMP_AMBIENTE 9.0

//PAINEL DE MOSTRADORES
NodePath relogio_pointer;
NodePath calango;
NodePath calango_border;
NodePath label_np;
NodePath hidratacao_bar;
NodePath hidratacao_pointer;
NodePath hidratacao_image;
NodePath temperatura_bar;
NodePath temperatura_pointer;
NodePath temperatura_image;
NodePath tempAmbiente_bar;
NodePath tempAmbiente_pointer;
NodePath tempAmbiente_image;
NodePath umidade_bar;
NodePath umidade_pointer;
NodePath umidade_image;

//BOTOES DE ESCOLHA DE TIPO GRAFICOS
TextNode* botaoEscolhaGrafico_text;
NodePath botaoEscolhaGrafico_label;
PGButton* botaoEscolhaGraficoTempo;
NodePath botaoEscolhaGraficoTempo_image;
NodePath botaoEscolhaGraficoTempo_image_ativo;
NodePath botaoEscolhaGraficoTempo_np;
PGButton* botaoEscolhaGraficoVariavel;
NodePath botaoEscolhaGraficoVariavel_np;
NodePath botaoEscolhaGraficoVariavel_image_ativo;
NodePath botaoEscolhaGraficoVariavel_image;
bool grafico_tempo_ativo;
bool grafico_variavel_ativo;

//BOTOES DE ESCOLHA DE GRAFICOS (TEMPO)
PGButton* botao1TempInterna;
NodePath botao1TempInterna_np;
NodePath botao1TempInterna_image;
NodePath botao1TempInterna_ledON;
NodePath botao1TempInterna_ledOFF;
bool botao1Flag;
PGButton* botao2Hidratcao;
NodePath botao2Hidratcao_np;
NodePath botao2Hidratcao_image;
NodePath botao2Hidratcao_ledON;
NodePath botao2Hidratcao_ledOFF;
bool botao2Flag;
PGButton* botao3TempAr;
NodePath botao3TempAr_np;
NodePath botao3TempAr_image;
NodePath botao3TempAr_ledON;
NodePath botao3TempAr_ledOFF;
bool botao3Flag;
PGButton* botao4UmidadeAr;
NodePath botao4UmidadeAr_np;
NodePath botao4UmidadeAr_image;
NodePath botao4UmidadeAr_ledON;
NodePath botao4UmidadeAr_ledOFF;
bool botao4Flag;
PGButton* botao5TempSolo;
NodePath botao5TempSolo_np;
NodePath botao5TempSolo_image;
NodePath botao5TempSolo_ledON;
NodePath botao5TempSolo_ledOFF;
bool botao5Flag;
PGButton* botao6Alimentacao;
NodePath botao6Alimentacao_np;
NodePath botao6Alimentacao_image;
NodePath botao6Alimentacao_ledON;
NodePath botao6Alimentacao_ledOFF;
bool botao6Flag;
PGButton* botao7Energia;
NodePath botao7Energia_np;
NodePath botao7Energia_image;
NodePath botao7Energia_ledON;
NodePath botao7Energia_ledOFF;
bool botao7Flag;
PGButton* botao8GastoEnergetico;
NodePath botao8GastoEnergetico_np;
NodePath botao8GastoEnergetico_image;
NodePath botao8GastoEnergetico_ledON;
NodePath botao8GastoEnergetico_ledOFF;
bool botao8Flag;

//BOTOES DE ESCOLHA DE GRAFICOS (VARIAVEL)
PGButton* vBotao1TempInterna;
NodePath vBotao1TempInterna_np;
NodePath vBotao1TempInterna_image;
NodePath vBotao1TempInterna_ledON;
NodePath vBotao1TempInterna_ledOFF;
PGButton* vBotao2Hidratcao;
NodePath vBotao2Hidratcao_np;
NodePath vBotao2Hidratcao_image;
NodePath vBotao2Hidratcao_ledON;
NodePath vBotao2Hidratcao_ledOFF;
PGButton* vBotao3TempAr;
NodePath vBotao3TempAr_np;
NodePath vBotao3TempAr_image;
NodePath vBotao3TempAr_ledON;
NodePath vBotao3TempAr_ledOFF;
PGButton* vBotao4UmidadeAr;
NodePath vBotao4UmidadeAr_np;
NodePath vBotao4UmidadeAr_image;
NodePath vBotao4UmidadeAr_ledON;
NodePath vBotao4UmidadeAr_ledOFF;
PGButton* vBotao5TempSolo;
NodePath vBotao5TempSolo_np;
NodePath vBotao5TempSolo_image;
NodePath vBotao5TempSolo_ledON;
NodePath vBotao5TempSolo_ledOFF;
PGButton* vBotao6Alimentacao;
NodePath vBotao6Alimentacao_np;
NodePath vBotao6Alimentacao_image;
NodePath vBotao6Alimentacao_ledON;
NodePath vBotao6Alimentacao_ledOFF;
PGButton* vBotao7Energia;
NodePath vBotao7Energia_np;
NodePath vBotao7Energia_image;
NodePath vBotao7Energia_ledON;
NodePath vBotao7Energia_ledOFF;
PGButton* vBotao8GastoEnergetico;
NodePath vBotao8GastoEnergetico_np;
NodePath vBotao8GastoEnergetico_image;
NodePath vBotao8GastoEnergetico_ledON;
NodePath vBotao8GastoEnergetico_ledOFF;

//CONFIGURAÇÕES DOS GRAFICOS DE VARIAVEIS.
queue<double> vetorX;
queue<double> vetorY;
string legendaX;
string legendaY;
double limiteSuperiorX;
double limiteInferiorX;
double limiteSuperiorY;
double limiteInferiorY;
double tamanhoVetorX;
double tamanhoVetorY;

//OPÇÕES DO MOUSE
MouseWatcher* mouse;
MouseWatcherGroup* mouseGroup;
MouseWatcherRegion* mouseRegion;
MouseWatcherRegion* mouseRegion2;
double mouseX, mouseY;

bool is_game_over;

//CONFIGURAÇÕES PARA TORNAR A CLASSE PT
TypeHandle GuiManager::_type_handle;

//VARIAVEIS UTILIZADAS PELO PADRAO SINGLETON
bool GuiManager::instanceFlag = false;
PT(GuiManager) GuiManager::instance = NULL;

NodePath GuiManager::piscar=NULL;
bool GuiManager::flag_piscar=false;
int GuiManager::conta=0;
//float GuiManager::controle_tempo_piscando=0.0;

GuiManager::~GuiManager(){
	

    cout<< "\n inicio do destrutor... " << endl;
    graphic = NULL;
    graphic2 = NULL;
    graphic3 = NULL;
    graphic4 = NULL;
    graphic5 = NULL;
    graphic6 = NULL;
    graphic7 = NULL;
    graphic8 = NULL;
    cout<< "\n fim do destrutor..." << endl;
}

PT(GuiManager) GuiManager::get_instance() {
    if (!instanceFlag) {
        instance = new GuiManager();
        instanceFlag = true;
    }
    return instance;
}

void GuiManager::unload_gui(){
    GuiManager::get_instance()->remove_hooks();
    //delete this;
    GuiManager::get_instance()->graphic = NULL;
    GuiManager::get_instance()->graphic2 = NULL;
    GuiManager::get_instance()->graphic3 = NULL;
    GuiManager::get_instance()->graphic4 = NULL;
    GuiManager::get_instance()->graphic5 = NULL;
    GuiManager::get_instance()->graphic6 = NULL;
    GuiManager::get_instance()->graphic7 = NULL;
    GuiManager::get_instance()->graphic8 = NULL;
    GuiManager::get_instance()->frameNode.detach_node();
    instance = NULL;
    instanceFlag = false;
}

void GuiManager::remove_hooks() {
    //------------------------------------------------------------
    Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_segundo_real, update_gui, this);
    //Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame_gui_options, init_options, this);
    Simdunas::get_evt_handler()->remove_hook(botaoGrafico->get_click_event(MouseButton::one()), click_event_botao_grafico, this);
    Simdunas::get_evt_handler()->remove_hook(botaoEscolhaGraficoTempo->get_click_event(MouseButton::one()), click_event_botao_grafico_tempo, this);
    Simdunas::get_evt_handler()->remove_hook(botaoEscolhaGraficoVariavel->get_click_event(MouseButton::one()), click_event_botao_grafico_variavel, this);
    Simdunas::get_evt_handler()->remove_hook(botao1TempInterna->get_click_event(MouseButton::one()), click_event_botao1_grafico_TempInterna, this);
    Simdunas::get_evt_handler()->remove_hook(botao2Hidratcao->get_click_event(MouseButton::one()), click_event_botao2_grafico_Hidratacao, this);
    Simdunas::get_evt_handler()->remove_hook(botao3TempAr->get_click_event(MouseButton::one()), click_event_botao3_grafico_TempAr, this);
    Simdunas::get_evt_handler()->remove_hook(botao4UmidadeAr->get_click_event(MouseButton::one()), click_event_botao4_grafico_Umidade, this);
    Simdunas::get_evt_handler()->remove_hook(botao5TempSolo->get_click_event(MouseButton::one()), click_event_botao5_grafico_TempSolo, this);
    Simdunas::get_evt_handler()->remove_hook(botao6Alimentacao->get_click_event(MouseButton::one()), click_event_botao6_grafico_Alimentacao, this);
    Simdunas::get_evt_handler()->remove_hook(botao7Energia->get_click_event(MouseButton::one()), click_event_botao7_grafico_Energia, this);
    Simdunas::get_evt_handler()->remove_hook(botao8GastoEnergetico->get_click_event(MouseButton::one()), click_event_botao8_grafico_GastoEnergetico, this);

}

GuiManager::GuiManager() {
    //window = Simdunas::get_window();

////////controla quanto tempo  o lagarto vai ficar piscando quando comer uma presa
//    controle_tempo_piscando=(50/Menu::get_instance()->get_minuto_dia_virtual());

    //Regula o aspect 2d.
    Simdunas::get_window()->get_aspect_2d().set_scale(1.0);
    //Inicia o objeto vetores.
    vector = Vetores::get_instance();
    is_game_over = false;

	//Toca
	molduraToca = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/objects/toca.png");
	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_enter_toca, mostra_moldura_toca, this);
	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_outof_toca, esconde_moldura_toca, this);
	molduraToca.reparent_to(Simdunas::get_window()->get_aspect_2d());
	molduraToca.set_scale(0.1);
	molduraToca.set_pos(0.0, 0.0, 0.0);
	molduraToca.hide();


	//FRAME.-----------------------------------------------------------
  	testeFrame = new PGVirtualFrame("Frame de teste");
  	testeFrame->setup(0.42, 2.0);
        PGFrameStyle style = testeFrame->get_frame_style(testeFrame->get_state());
        style.set_type(PGFrameStyle::T_flat);
        testeFrame->set_frame_style(testeFrame->get_state(), style);

   	frameNode = NodePath(testeFrame);
  	frameNode.reparent_to(Simdunas::get_window()->get_aspect_2d());
  	cont_gui_options = 0.58;
  	//Seta a posição do frame
  	frameNode.set_pos(0.58, 0.0, -1.0);
  	//Seta a cor do frame
  	frameNode.set_color(0.8, 0.8, 0.8);
  	//Seta a transparencia do frame.
  	frameNode.set_transparency(TransparencyAttrib::M_alpha);
	frameNode.set_alpha_scale(0.85);



	//RELOGIO PARA MOSTRAR DIA/NOITE.----------------------------------
	relogioDiaNoite = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/diaEnoite.png");
	relogio_pointer = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/ponteiro.png");

	relogioDiaNoite.reparent_to(frameNode);
	relogioDiaNoite.set_scale(0.016);
	relogioDiaNoite.set_pos(0.22, 0.0, 1.8);
	relogioDiaNoite.set_hpr(0.0, 0.0, 270.0);
	relogioDiaNoite.set_transparency(TransparencyAttrib::M_alpha);
	relogioDiaNoite.set_alpha_scale(1.0);

	relogio_pointer.reparent_to(frameNode);
	relogio_pointer.set_scale(0.005);
	relogio_pointer.set_pos(0.22, 0.0, 1.94);
	relogio_pointer.set_hpr(0.0, 0.0, 180.0);
	relogio_pointer.set_transparency(TransparencyAttrib::M_alpha);
	relogio_pointer.set_alpha_scale(1.0);

	cont_relogio = (TimeControl::get_instance()->get_hora())*270/6;

	//BARRA DO LIFE.---------------------------------------------------
  	calango = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/calango_color.png");
	calango_border = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/calango_border.png");

	calango.reparent_to(frameNode);
	calango_border.reparent_to(frameNode);
	calango.set_scale(0.02);
	calango.set_sz(0.028);
	calango.set_pos(0.22, 0.0, 1.46);
	calango.set_transparency(TransparencyAttrib::M_alpha);
	calango.set_alpha_scale(0.75);

	calango_border.set_scale(0.02);
	calango_border.set_sz(0.028);
	calango_border.set_pos(0.22, 0.0, 1.46);

	//Criando uma barra para mostrar o "life"
	life_bar = ImageBar(frameNode, calango_border, calango);

	//Criando o label do life.
	labelDamage = new TextNode("Life");
	labelDamage->set_text("VIDA");

	label_np = frameNode.attach_new_node(labelDamage);
	label_np.set_pos(0.14, 0.0, 1.445);
	label_np.set_scale(0.05);
  	label_np.set_color(0.0, 0.0, 0.0, 1,0);

    //criando a imagem do calando q vai ficar piscando quando o calango comer
    /////////////////////////////////////////
    piscar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/pisca_life");
    piscar.set_scale(0.18);
    piscar.set_p(270);
    piscar.set_h(180);
    piscar.set_pos(0.80, 0.0, 0.44);
    piscar.detach_node();

	//BARRA DA HIDRATAÇÃO.---------------------------------------------
	hidratacao_bar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/barra-hidratacao-espelhada.png");
	hidratacao_pointer = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/ponteiro.png");
	hidratacao_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloHidratacao.png");
	
        hidratacao_image.reparent_to(frameNode);
	hidratacao_image.set_scale(0.01);
	hidratacao_image.set_pos(0.10, 0.0, 1.20);
	hidratacao_image.set_transparency(TransparencyAttrib::M_alpha);
	hidratacao_image.set_alpha_scale(1.0);

	hidratacao_bar.reparent_to(frameNode);
	//hidratacao_bar.set_scale(1.3);
	//hidratacao_bar.set_pos(18.0, 0.0, -6.0);
	hidratacao_bar.set_scale(0.013);
	hidratacao_bar.set_pos(0.28, 0.0, 1.14);

	hidratacao_pointer.reparent_to(hidratacao_bar);
	hidratacao_pointer.set_scale(0.18);
	hidratacao_pointer.set_pos(0.0, 0.0, 0.0);

	//Criando a barra para mostrar o nivel de hidratação.
	hidratacao_scrollBar = ScrollBar(frameNode, hidratacao_bar, hidratacao_pointer);

	//Criando o label da hidratação.
	labelHidratacao = new TextNode("Hidratação");
	labelHidratacao->set_text("");

	labelHidratacao_np = frameNode.attach_new_node(labelHidratacao);
	labelHidratacao_np.set_pos(0.16, 0.0, 1.17);
	labelHidratacao_np.set_scale(0.04);
  	labelHidratacao_np.set_color(0.0, 0.0, 0.0, 1,0);

	//BARRA DA TEMPERATURA.--------------------------------------------
	temperatura_bar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/barra-hidratacao4.png");
	temperatura_pointer = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/ponteiro.png");
	temperatura_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloTemperatura.png");

	temperatura_image.reparent_to(frameNode);
	temperatura_image.set_scale(0.01);
	temperatura_image.set_pos(0.10, 0.0, 1.0);
	temperatura_image.set_alpha_scale(0.9);

	temperatura_bar.reparent_to(frameNode);
	//temperatura_bar.set_scale(1.3);
	//temperatura_bar.set_pos(18.0, 0.0, -6.0);
	temperatura_bar.set_scale(0.013);
	temperatura_bar.set_pos(0.28, 0.0, 0.94);

	temperatura_pointer.reparent_to(temperatura_bar);
	temperatura_pointer.set_scale(0.18);
	temperatura_pointer.set_pos(0.0, 0.0, 0.0);

	//Criando a barra para mostrar a temperatura.
	temperatura_scrollBar = ScrollBar(frameNode, temperatura_bar, temperatura_pointer);

	//Criando o label da temperatura.
	labelTemperatura = new TextNode("Temperatura");
	labelTemperatura->set_text("");

	labelTemperatura_np = frameNode.attach_new_node(labelTemperatura);
	labelTemperatura_np.set_pos(0.16, 0.0,0.97);
	labelTemperatura_np.set_scale(0.04);
  	labelTemperatura_np.set_color(0.0, 0.0, 0.0, 1,0);

	//BARRA DA TEMPERATURA DO AMBIENTE.--------------------------------
	tempAmbiente_bar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/barra-hidratacao4.png");
	tempAmbiente_pointer = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/ponteiro.png");
	tempAmbiente_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_temp2.png");

	tempAmbiente_image.reparent_to(frameNode);
	tempAmbiente_image.set_scale(0.008);
	tempAmbiente_image.set_pos(0.10, 0.0, 0.8);
	tempAmbiente_image.set_alpha_scale(0.9);

	tempAmbiente_bar.reparent_to(frameNode);
	//tempAmbiente_bar.set_scale(1.3);
	//tempAmbiente_bar.set_pos(18.0, 0.0, -6.0);
	tempAmbiente_bar.set_scale(0.013);
	tempAmbiente_bar.set_pos(0.28, 0.0, 0.74);

	tempAmbiente_pointer.reparent_to(tempAmbiente_bar);
	tempAmbiente_pointer.set_scale(0.18);
	tempAmbiente_pointer.set_pos(0.0, 0.0, 0.0);

	//Criando a barra para mostrar a temperatura.
	tempAmbiente_scrollBar = ScrollBar(frameNode, tempAmbiente_bar, tempAmbiente_pointer);

	//Criando o label da temperatura do ambiente.
	labelTemperaturaAmb = new TextNode("Temperatura do ambiente");
	labelTemperaturaAmb->set_text("");

	labelTemperaturaAmb_np = frameNode.attach_new_node(labelTemperaturaAmb);
	labelTemperaturaAmb_np.set_pos(0.16, 0.0, 0.77);
	labelTemperaturaAmb_np.set_scale(0.04);
  	labelTemperaturaAmb_np.set_color(0.0, 0.0, 0.0, 1,0);

	//BARRA DE UMIDADE DO AR.------------------------------------------
	umidade_bar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/barra-hidratacao-espelhada.png");
	umidade_pointer = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/ponteiro.png");
	umidade_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_umi.png");

	umidade_image.reparent_to(frameNode);
	umidade_image.set_scale(0.007);
	umidade_image.set_pos(0.10, 0.0, 0.6);
	umidade_image.set_alpha_scale(0.9);

	umidade_bar.reparent_to(frameNode);
	//umidade_bar.set_scale(1.3);
	//umidade_bar.set_pos(18.0, 0.0, -6.0);
	umidade_bar.set_scale(0.013);
	umidade_bar.set_pos(0.28, 0.0, 0.54);

	umidade_pointer.reparent_to(umidade_bar);
	umidade_pointer.set_scale(0.18);
	umidade_pointer.set_pos(0.0, 0.0, 0.0);

	//Criando a barra para mostrar a umidade.
	umidade_scrollBar = ScrollBar(frameNode, umidade_bar, umidade_pointer);

	//Criando o label da umidade.
	labelUmidade = new TextNode("Temperatura do ambiente");
	labelUmidade->set_text("");

	labelUmidade_np = frameNode.attach_new_node(labelUmidade);
	labelUmidade_np.set_pos(0.16, 0.0, 0.57);
	labelUmidade_np.set_scale(0.04);
  	labelUmidade_np.set_color(0.0, 0.0, 0.0, 1,0);

        //----------------------------------------------------------------------
	//AVISO DO ESTADO REPRODUTIVO.------------------------------------------
        //----------------------------------------------------------------------
	estadoReprodutivo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/(fe)male_symbol.png");
	led = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        egg = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/egg2.png");
	//ledGreen = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");

	estadoReprodutivo.reparent_to(frameNode);
	estadoReprodutivo.set_scale(0.008);
	estadoReprodutivo.set_pos(0.10, 0.0, 0.36);

	led.reparent_to(frameNode);
	led.set_scale(0.004);
	led.set_pos(0.16, 0.0, 0.32);

        egg.reparent_to(frameNode);
	egg.set_scale(0.006);
	egg.set_pos(0.28, 0.0, 0.32);

        labelCountEgg = new TextNode("CountEgg");
	labelCountEgg->set_text("0");

	labelCountEgg_np = frameNode.attach_new_node(labelCountEgg);
	labelCountEgg_np.set_pos(0.35, 0.0, 0.30);
	labelCountEgg_np.set_scale(0.065);
  	labelCountEgg_np.set_color(0.0, 0.0, 0.0, 1,0);

        //----------------------------------------------------------------------
	//BOTAO DO GRAFICO.-----------------------------------------------------
        //----------------------------------------------------------------------
        botaoGrafico = new PGButton("botaoGrafico");
        botaoGrafico->setup("Grafico", 0.1);
        botaoGrafico_np = frameNode.attach_new_node(botaoGrafico);
        botaoGrafico_np.set_scale(0.05);
        botaoGrafico_np.set_pos(0.25, 0.0, 0.12);
        
        botaoGrafico2 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/graphic_1.jpg");
  	botaoGrafico2.reparent_to(frameNode);
 	botaoGrafico2.set_pos(0.25, 0.0, 0.12);
        botaoGrafico2.set_scale(0.01);
        botaoGrafico->setup(botaoGrafico2);
        botaoGrafico->set_frame(-2.0 , 2.0 , -1.5, 1.5);

        //----------------------------------------------------------------------
        //BOTOES DE ESCOLHA DO GRAFICO.-----------------------------------------
        //----------------------------------------------------------------------
        //TITULO DE ESCOLHA DO TIPO DE GRAFICO.
        botaoEscolhaGrafico_text = new TextNode("EscolhaDoGrafico");
	botaoEscolhaGrafico_text->set_text("Tipo do grafico");
        botaoEscolhaGrafico_label = frameNode.attach_new_node(botaoEscolhaGrafico_text);
	botaoEscolhaGrafico_label.set_pos(0.04, 0.0, 1.90);
	botaoEscolhaGrafico_label.set_scale(0.06);
  	botaoEscolhaGrafico_label.set_color(0.0, 0.0, 0.0, 1,0);
        botaoEscolhaGrafico_label.hide();

        //BOTAO PARA VER OS GRAFICOS DE TEMPO.
        botaoEscolhaGraficoTempo = new PGButton("botaoGraficoEscolhaTempo");
        botaoEscolhaGraficoTempo->setup("Tempo", 0.1);
        botaoEscolhaGraficoTempo_np = frameNode.attach_new_node(botaoEscolhaGraficoTempo);
        botaoEscolhaGraficoTempo_np.set_scale(0.05);
        botaoEscolhaGraficoTempo_np.set_pos(0.08, 0.0, 1.80);
        botaoEscolhaGraficoTempo_np.hide();
        botaoEscolhaGraficoTempo_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botaoEscolhaGraficoTempo_image.reparent_to(frameNode);
        botaoEscolhaGraficoTempo_image.set_scale(0.004);
        botaoEscolhaGraficoTempo_image.set_pos(0.28, 0.0, 1.82);
        botaoEscolhaGraficoTempo_image.hide();
        botaoEscolhaGraficoTempo_image_ativo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botaoEscolhaGraficoTempo_image_ativo.reparent_to(frameNode);
        botaoEscolhaGraficoTempo_image_ativo.set_scale(0.004);
        botaoEscolhaGraficoTempo_image_ativo.set_pos(0.28, 0.0, 1.82);
        botaoEscolhaGraficoTempo_image_ativo.hide();

        //BOTAO PARA VER OS GRAFICOS DE VARIAVEL.
        botaoEscolhaGraficoVariavel = new PGButton("botaoGraficoEscolhaTempo");
        botaoEscolhaGraficoVariavel->setup("Variavel", 0.1);
        botaoEscolhaGraficoVariavel_np = frameNode.attach_new_node(botaoEscolhaGraficoVariavel);
        botaoEscolhaGraficoVariavel_np.set_scale(0.05);
        botaoEscolhaGraficoVariavel_np.set_pos(0.06, 0.0, 1.68);
        botaoEscolhaGraficoVariavel_np.hide();
        botaoEscolhaGraficoVariavel_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botaoEscolhaGraficoVariavel_image.reparent_to(frameNode);
        botaoEscolhaGraficoVariavel_image.set_scale(0.004);
        botaoEscolhaGraficoVariavel_image.set_pos(0.28, 0.0, 1.70);
        botaoEscolhaGraficoVariavel_image.hide();
        botaoEscolhaGraficoVariavel_image_ativo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botaoEscolhaGraficoVariavel_image_ativo.reparent_to(frameNode);
        botaoEscolhaGraficoVariavel_image_ativo.set_scale(0.004);
        botaoEscolhaGraficoVariavel_image_ativo.set_pos(0.28, 0.0, 1.70);
        botaoEscolhaGraficoVariavel_image_ativo.hide();

        grafico_tempo_ativo = true;
        grafico_variavel_ativo = false;
        //------------
        botao1TempInterna = new PGButton("Botao_temperatura_interna");
        botao1TempInterna->setup("", 0.1);
        botao1TempInterna_np = frameNode.attach_new_node(botao1TempInterna);
        botao1TempInterna_np.set_scale(0.03);
        botao1TempInterna_np.set_pos(0.08, 0.0, 1.52);
        botao1TempInterna_np.hide();
        botao1TempInterna_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloTemperatura.png");
        botao1TempInterna_image.reparent_to(frameNode);
        botao1TempInterna_image.set_scale(0.008);
        botao1TempInterna_image.set_pos(0.08, 0.0, 1.52);
        botao1TempInterna_image.hide();
        botao1TempInterna_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao1TempInterna_ledOFF.reparent_to(frameNode);
        botao1TempInterna_ledOFF.set_scale(0.0034);
        botao1TempInterna_ledOFF.set_pos(0.17, 0.0, 1.48);
        botao1TempInterna_ledOFF.hide();
        botao1TempInterna_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao1TempInterna_ledON.reparent_to(frameNode);
        botao1TempInterna_ledON.set_scale(0.0034);
        botao1TempInterna_ledON.set_pos(0.17, 0.0, 1.48);
        botao1TempInterna_ledON.hide();
        botao1TempInterna->setup(botao1TempInterna_image);
        botao1TempInterna->set_frame(-1.3 , 1.3 , -2.8, 2.8);
        botao1Flag = false;
        //------------------

        //------------
        botao2Hidratcao = new PGButton("Botao_hidratacao");
        botao2Hidratcao->setup("", 0.1);
        botao2Hidratcao_np = frameNode.attach_new_node(botao2Hidratcao);
        botao2Hidratcao_np.set_scale(0.03);
        botao2Hidratcao_np.set_pos(0.26, 0.0, 1.52);
        botao2Hidratcao_np.hide();
        botao2Hidratcao_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloHidratacao.png");
        botao2Hidratcao_image.reparent_to(frameNode);
        botao2Hidratcao_image.set_scale(0.008);
        botao2Hidratcao_image.set_pos(0.26, 0.0, 1.52);
        botao2Hidratcao_image.hide();
        botao2Hidratcao_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao2Hidratcao_ledOFF.reparent_to(frameNode);
        botao2Hidratcao_ledOFF.set_scale(0.0034);
        botao2Hidratcao_ledOFF.set_pos(0.35, 0.0, 1.48);
        botao2Hidratcao_ledOFF.hide();
        botao2Hidratcao_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao2Hidratcao_ledON.reparent_to(frameNode);
        botao2Hidratcao_ledON.set_scale(0.0034);
        botao2Hidratcao_ledON.set_pos(0.35, 0.0, 1.48);
        botao2Hidratcao_ledON.hide();
        botao2Hidratcao->setup(botao2Hidratcao_image);
        botao2Hidratcao->set_frame(-1.3 , 1.3 , -2.8, 2.8);
        botao2Flag = false;
        //------------------

        //------------
        botao3TempAr = new PGButton("Botao_temperatura_ar");
        botao3TempAr->setup("", 0.1);
        botao3TempAr_np = frameNode.attach_new_node(botao3TempAr);
        botao3TempAr_np.set_scale(0.03);
        botao3TempAr_np.set_pos(0.08, 0.0, 1.30);
        botao3TempAr_np.hide();
        botao3TempAr_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_temp2.png");
        botao3TempAr_image.reparent_to(frameNode);
        botao3TempAr_image.set_scale(0.006);
        botao3TempAr_image.set_pos(0.08, 0.0, 1.30);
        botao3TempAr_image.hide();
        botao3TempAr_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao3TempAr_ledOFF.reparent_to(frameNode);
        botao3TempAr_ledOFF.set_scale(0.0034);
        botao3TempAr_ledOFF.set_pos(0.17, 0.0, 1.26);
        botao3TempAr_ledOFF.hide();
        botao3TempAr_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao3TempAr_ledON.reparent_to(frameNode);
        botao3TempAr_ledON.set_scale(0.0034);
        botao3TempAr_ledON.set_pos(0.17, 0.0, 1.26);
        botao3TempAr_ledON.hide();
        botao3TempAr->setup(botao1TempInterna_image);
        botao3TempAr->set_frame(-1.6 , 1.6 , -2.0, 2.0);
        botao3Flag = false;
        //------------------

        //------------
        botao4UmidadeAr = new PGButton("Botao_umidade");
        botao4UmidadeAr->setup("", 0.1);
        botao4UmidadeAr_np = frameNode.attach_new_node(botao4UmidadeAr);
        botao4UmidadeAr_np.set_scale(0.03);
        botao4UmidadeAr_np.set_pos(0.26, 0.0, 1.30);
        botao4UmidadeAr_np.hide();
        botao4UmidadeAr_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_umi.png");
        botao4UmidadeAr_image.reparent_to(frameNode);
        botao4UmidadeAr_image.set_scale(0.005);
        botao4UmidadeAr_image.set_pos(0.26, 0.0, 1.30);
        botao4UmidadeAr_image.hide();
        botao4UmidadeAr_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao4UmidadeAr_ledOFF.reparent_to(frameNode);
        botao4UmidadeAr_ledOFF.set_scale(0.0034);
        botao4UmidadeAr_ledOFF.set_pos(0.35, 0.0, 1.26);
        botao4UmidadeAr_ledOFF.hide();
        botao4UmidadeAr_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao4UmidadeAr_ledON.reparent_to(frameNode);
        botao4UmidadeAr_ledON.set_scale(0.0034);
        botao4UmidadeAr_ledON.set_pos(0.35, 0.0, 1.26);
        botao4UmidadeAr_ledON.hide();
        botao4UmidadeAr->setup(botao2Hidratcao_image);
        botao4UmidadeAr->set_frame(-1.6 , 1.6 , -2.0, 2.0);
        botao4Flag = false;
        //------------------

        //------------
        botao5TempSolo = new PGButton("Botao_temperatura_solo");
        botao5TempSolo->setup("", 0.1);
        botao5TempSolo_np = frameNode.attach_new_node(botao5TempSolo);
        botao5TempSolo_np.set_scale(0.03);
        botao5TempSolo_np.set_pos(0.08, 0.0, 1.08);
        botao5TempSolo_np.hide();
        botao5TempSolo_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_temp3.png");
        botao5TempSolo_image.reparent_to(frameNode);
        botao5TempSolo_image.set_scale(0.006);
        botao5TempSolo_image.set_pos(0.08, 0.0, 1.08);
        botao5TempSolo_image.hide();
        botao5TempSolo_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao5TempSolo_ledOFF.reparent_to(frameNode);
        botao5TempSolo_ledOFF.set_scale(0.0034);
        botao5TempSolo_ledOFF.set_pos(0.17, 0.0, 1.04);
        botao5TempSolo_ledOFF.hide();
        botao5TempSolo_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao5TempSolo_ledON.reparent_to(frameNode);
        botao5TempSolo_ledON.set_scale(0.0034);
        botao5TempSolo_ledON.set_pos(0.17, 0.0, 1.04);
        botao5TempSolo_ledON.hide();
        botao5TempSolo->setup(botao5TempSolo_image);
        botao5TempSolo->set_frame(-1.6 , 1.6 , -2.0, 2.0);
        botao5Flag = false;
        //------------------

        //------------
        botao6Alimentacao = new PGButton("Botao_alimentacao");
        botao6Alimentacao->setup("", 0.1);
        botao6Alimentacao_np = frameNode.attach_new_node(botao6Alimentacao);
        botao6Alimentacao_np.set_scale(0.03);
        botao6Alimentacao_np.set_pos(0.26, 0.0, 1.08);
        botao6Alimentacao_np.hide();
        botao6Alimentacao_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloNutricional.png");
        botao6Alimentacao_image.reparent_to(frameNode);
        botao6Alimentacao_image.set_scale(0.008);
        botao6Alimentacao_image.set_pos(0.26, 0.0, 1.08);
        botao6Alimentacao_image.hide();
        botao6Alimentacao_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao6Alimentacao_ledOFF.reparent_to(frameNode);
        botao6Alimentacao_ledOFF.set_scale(0.0034);
        botao6Alimentacao_ledOFF.set_pos(0.35, 0.0, 1.04);
        botao6Alimentacao_ledOFF.hide();
        botao6Alimentacao_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao6Alimentacao_ledON.reparent_to(frameNode);
        botao6Alimentacao_ledON.set_scale(0.0034);
        botao6Alimentacao_ledON.set_pos(0.35, 0.0, 1.04);
        botao6Alimentacao_ledON.hide();
        botao6Alimentacao->setup(botao6Alimentacao_image);
        botao6Alimentacao->set_frame(-1.3 , 1.3 , -2.8, 2.8);
        botao6Flag = false;
        //------------------

        //------------
        botao7Energia = new PGButton("Botao_energia");
        botao7Energia->setup("", 0.1);
        botao7Energia_np = frameNode.attach_new_node(botao7Energia);
        botao7Energia_np.set_scale(0.03);
        botao7Energia_np.set_pos(0.08, 0.0, 0.86);
        botao7Energia_np.hide();
        botao7Energia_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloEnergia.png");
        botao7Energia_image.reparent_to(frameNode);
        botao7Energia_image.set_scale(0.008);
        botao7Energia_image.set_pos(0.08, 0.0, 0.86);
        botao7Energia_image.hide();
        botao7Energia_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao7Energia_ledOFF.reparent_to(frameNode);
        botao7Energia_ledOFF.set_scale(0.0034);
        botao7Energia_ledOFF.set_pos(0.17, 0.0, 0.82);
        botao7Energia_ledOFF.hide();
        botao7Energia_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao7Energia_ledON.reparent_to(frameNode);
        botao7Energia_ledON.set_scale(0.0034);
        botao7Energia_ledON.set_pos(0.17, 0.0, 0.82);
        botao7Energia_ledON.hide();
        botao7Energia->setup(botao7Energia_image);
        botao7Energia->set_frame(-1.3 , 1.3 , -2.8, 2.8);
        botao7Flag = false;
        //------------------

        //------------
        botao8GastoEnergetico = new PGButton("Botao_gasto_energetico");
        botao8GastoEnergetico->setup("", 0.1);
        botao8GastoEnergetico_np = frameNode.attach_new_node(botao8GastoEnergetico);
        botao8GastoEnergetico_np.set_scale(0.03);
        botao8GastoEnergetico_np.set_pos(0.26, 0.0, 0.86);
        botao8GastoEnergetico_np.hide();
        botao8GastoEnergetico_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloGatoEnergetico.png");
        botao8GastoEnergetico_image.reparent_to(frameNode);
        botao8GastoEnergetico_image.set_scale(0.008);
        botao8GastoEnergetico_image.set_pos(0.26, 0.0, 0.86);
        botao8GastoEnergetico_image.hide();
        botao8GastoEnergetico_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        botao8GastoEnergetico_ledOFF.reparent_to(frameNode);
        botao8GastoEnergetico_ledOFF.set_scale(0.0034);
        botao8GastoEnergetico_ledOFF.set_pos(0.35, 0.0, 0.82);
        botao8GastoEnergetico_ledOFF.hide();
        botao8GastoEnergetico_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        botao8GastoEnergetico_ledON.reparent_to(frameNode);
        botao8GastoEnergetico_ledON.set_scale(0.0034);
        botao8GastoEnergetico_ledON.set_pos(0.35, 0.0, 0.82);
        botao8GastoEnergetico_ledON.hide();
        botao8GastoEnergetico->setup(botao8GastoEnergetico_image);
        botao8GastoEnergetico->set_frame(-1.3 , 1.3 , -2.8, 2.8);
        botao8Flag = false;
        //------------------

        this->build_options();
	gui_options_flag = false;
	gui_options_flag2 = false;

        //------------
        vBotao1TempInterna = new PGButton("Botao_temperatura_interna");
        vBotao1TempInterna->setup("", 0.1);
        vBotao1TempInterna_np = graficoVariavelFrameNode.attach_new_node(vBotao1TempInterna);
        vBotao1TempInterna_np.set_scale(0.009);
        vBotao1TempInterna_np.set_pos(0.1, 0.0, 0.12);
        //vBotao1TempInterna_np.hide();
        vBotao1TempInterna_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloTemperatura.png");
        vBotao1TempInterna_image.reparent_to(graficoVariavelFrameNode);
        vBotao1TempInterna_image.set_scale(0.009);
        vBotao1TempInterna_image.set_pos(0.1, 0.0, 0.12);
        //vBotao1TempInterna_image.hide();
        vBotao1TempInterna_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao1TempInterna_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao1TempInterna_ledOFF.set_scale(0.004);
        vBotao1TempInterna_ledOFF.set_pos(0.1, 0.0, 0.32);
        //vBotao1TempInterna_ledOFF.hide();
        vBotao1TempInterna_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao1TempInterna_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao1TempInterna_ledON.set_scale(0.004);
        vBotao1TempInterna_ledON.set_pos(0.1, 0.0, 0.32);
        vBotao1TempInterna_ledON.hide();
        vBotao1TempInterna->setup(vBotao1TempInterna_image);
        vBotao1TempInterna->set_frame(-5.0 , 5.0 , -10.0, 10.0);
        //------------------

        //------------
        vBotao2Hidratcao = new PGButton("Botao_hidratacao");
        vBotao2Hidratcao->setup("", 0.1);
        vBotao2Hidratcao_np = graficoVariavelFrameNode.attach_new_node(vBotao2Hidratcao);
        vBotao2Hidratcao_np.set_scale(0.009);
        vBotao2Hidratcao_np.set_pos(0.26, 0.0, 0.12);
        //vBotao2Hidratcao_np.hide();
        vBotao2Hidratcao_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloHidratacao.png");
        vBotao2Hidratcao_image.reparent_to(graficoVariavelFrameNode);
        vBotao2Hidratcao_image.set_scale(0.009);
        vBotao2Hidratcao_image.set_pos(0.26, 0.0, 0.12);
        //vBotao2Hidratcao_image.hide();
        vBotao2Hidratcao_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao2Hidratcao_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao2Hidratcao_ledOFF.set_scale(0.004);
        vBotao2Hidratcao_ledOFF.set_pos(0.26, 0.0, 0.32);
        //vBotao2Hidratcao_ledOFF.hide();
        vBotao2Hidratcao_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao2Hidratcao_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao2Hidratcao_ledON.set_scale(0.004);
        vBotao2Hidratcao_ledON.set_pos(0.26, 0.0, 0.32);
        vBotao2Hidratcao_ledON.hide();
        vBotao2Hidratcao->setup(botao2Hidratcao_image);
        vBotao2Hidratcao->set_frame(-5.0, 5.0, -10.0, 10.0);
        //------------------

        //------------
        vBotao3TempAr = new PGButton("Botao_temperatura_ar");
        vBotao3TempAr->setup("", 0.1);
        vBotao3TempAr_np = graficoVariavelFrameNode.attach_new_node(vBotao3TempAr);
        vBotao3TempAr_np.set_scale(0.009);
        vBotao3TempAr_np.set_pos(0.42, 0.0, 0.12);
        //vBotao3TempAr_np.hide();
        vBotao3TempAr_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_temp2.png");
        vBotao3TempAr_image.reparent_to(graficoVariavelFrameNode);
        vBotao3TempAr_image.set_scale(0.009);
        vBotao3TempAr_image.set_pos(0.42, 0.0, 0.12);
        //vBotao3TempAr_image.hide();
        vBotao3TempAr_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao3TempAr_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao3TempAr_ledOFF.set_scale(0.004);
        vBotao3TempAr_ledOFF.set_pos(0.42, 0.0, 0.32);
        vBotao3TempAr_ledOFF.hide();
        vBotao3TempAr_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao3TempAr_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao3TempAr_ledON.set_scale(0.004);
        vBotao3TempAr_ledON.set_pos(0.42, 0.0, 0.32);
        //vBotao3TempAr_ledON.hide();
        vBotao3TempAr->setup(vBotao1TempInterna_image);
        vBotao3TempAr->set_frame(-8.1 , 8.1 , -10.0, 10.0);
        //------------------

        //------------
        vBotao4UmidadeAr = new PGButton("Botao_umidade");
        vBotao4UmidadeAr->setup("", 0.1);
        vBotao4UmidadeAr_np = graficoVariavelFrameNode.attach_new_node(vBotao4UmidadeAr);
        vBotao4UmidadeAr_np.set_scale(0.008);
        vBotao4UmidadeAr_np.set_pos(0.60, 0.0, 0.12);
        //botao4UmidadeAr_np.hide();
        vBotao4UmidadeAr_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_umi.png");
        vBotao4UmidadeAr_image.reparent_to(graficoVariavelFrameNode);
        vBotao4UmidadeAr_image.set_scale(0.008);
        vBotao4UmidadeAr_image.set_pos(0.60, 0.0, 0.12);
        //botao4UmidadeAr_image.hide();
        vBotao4UmidadeAr_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao4UmidadeAr_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao4UmidadeAr_ledOFF.set_scale(0.004);
        vBotao4UmidadeAr_ledOFF.set_pos(0.60, 0.0, 0.32);
        //botao4UmidadeAr_ledOFF.hide();
        vBotao4UmidadeAr_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao4UmidadeAr_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao4UmidadeAr_ledON.set_scale(0.004);
        vBotao4UmidadeAr_ledON.set_pos(0.60, 0.0, 0.32);
        vBotao4UmidadeAr_ledON.hide();
        vBotao4UmidadeAr->setup(vBotao2Hidratcao_image);
        vBotao4UmidadeAr->set_frame(-8.8 , 8.8 , -10.0, 10.0);
        //------------------

        //------------
        vBotao5TempSolo = new PGButton("Botao_temperatura_solo");
        vBotao5TempSolo->setup("", 0.1);
        vBotao5TempSolo_np = graficoVariavelFrameNode.attach_new_node(vBotao5TempSolo);
        vBotao5TempSolo_np.set_scale(0.009);
        vBotao5TempSolo_np.set_pos(0.78, 0.0, 0.12);
        //vBotao5TempSolo_np.hide();
        vBotao5TempSolo_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/mundo_temp3.png");
        vBotao5TempSolo_image.reparent_to(graficoVariavelFrameNode);
        vBotao5TempSolo_image.set_scale(0.009);
        vBotao5TempSolo_image.set_pos(0.78, 0.0, 0.12);
        //vBotao5TempSolo_image.hide();
        vBotao5TempSolo_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao5TempSolo_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao5TempSolo_ledOFF.set_scale(0.004);
        vBotao5TempSolo_ledOFF.set_pos(0.78, 0.0, 0.32);
        //vBotao5TempSolo_ledOFF.hide();
        vBotao5TempSolo_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao5TempSolo_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao5TempSolo_ledON.set_scale(0.004);
        vBotao5TempSolo_ledON.set_pos(0.78, 0.0, 0.32);
        vBotao5TempSolo_ledON.hide();
        vBotao5TempSolo->setup(vBotao5TempSolo_image);
        vBotao5TempSolo->set_frame(-8.1 , 8.1 , -10.0, 10.0);
        //------------------

        //------------
        vBotao6Alimentacao = new PGButton("Botao_alimentacao");
        vBotao6Alimentacao->setup("", 0.1);
        vBotao6Alimentacao_np = graficoVariavelFrameNode.attach_new_node(vBotao6Alimentacao);
        vBotao6Alimentacao_np.set_scale(0.009);
        vBotao6Alimentacao_np.set_pos(0.94, 0.0, 0.12);
        //vBotao6Alimentacao_np.hide();
        vBotao6Alimentacao_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloNutricional.png");
        vBotao6Alimentacao_image.reparent_to(graficoVariavelFrameNode);
        vBotao6Alimentacao_image.set_scale(0.009);
        vBotao6Alimentacao_image.set_pos(0.94, 0.0, 0.12);
        //vBotao6Alimentacao_image.hide();
        vBotao6Alimentacao_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao6Alimentacao_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao6Alimentacao_ledOFF.set_scale(0.004);
        vBotao6Alimentacao_ledOFF.set_pos(0.94, 0.0, 0.32);
        //vBotao6Alimentacao_ledOFF.hide();
        vBotao6Alimentacao_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao6Alimentacao_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao6Alimentacao_ledON.set_scale(0.004);
        vBotao6Alimentacao_ledON.set_pos(0.94, 0.0, 0.32);
        vBotao6Alimentacao_ledON.hide();
        vBotao6Alimentacao->setup(vBotao6Alimentacao_image);
        vBotao6Alimentacao->set_frame(-5.0 , 5.0, -10.0, 10.0);
        //------------------

        //------------
        vBotao7Energia = new PGButton("Botao_energia");
        vBotao7Energia->setup("", 0.1);
        vBotao7Energia_np = graficoVariavelFrameNode.attach_new_node(vBotao7Energia);
        vBotao7Energia_np.set_scale(0.009);
        vBotao7Energia_np.set_pos(1.10, 0.0, 0.12);
        //vBotao7Energia_np.hide();
        vBotao7Energia_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloEnergia.png");
        vBotao7Energia_image.reparent_to(graficoVariavelFrameNode);
        vBotao7Energia_image.set_scale(0.009);
        vBotao7Energia_image.set_pos(1.10, 0.0, 0.12);
        //vBotao7Energia_image.hide();
        vBotao7Energia_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao7Energia_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao7Energia_ledOFF.set_scale(0.004);
        vBotao7Energia_ledOFF.set_pos(1.10, 0.0, 0.32);
        //vBotao7Energia_ledOFF.hide();
        vBotao7Energia_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao7Energia_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao7Energia_ledON.set_scale(0.004);
        vBotao7Energia_ledON.set_pos(1.10, 0.0, 0.32);
        vBotao7Energia_ledON.hide();
        vBotao7Energia->setup(vBotao7Energia_image);
        vBotao7Energia->set_frame(-5.0 , 5.0 , -10.0, 10.0);
        //------------------

        //------------
        vBotao8GastoEnergetico = new PGButton("Botao_gasto_energetico");
        vBotao8GastoEnergetico->setup("", 0.1);
        vBotao8GastoEnergetico_np = graficoVariavelFrameNode.attach_new_node(vBotao8GastoEnergetico);
        vBotao8GastoEnergetico_np.set_scale(0.009);
        vBotao8GastoEnergetico_np.set_pos(1.28, 0.0, 0.12);
        //vBotao8GastoEnergetico_np.hide();
        vBotao8GastoEnergetico_image = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/modeloGatoEnergetico.png");
        vBotao8GastoEnergetico_image.reparent_to(graficoVariavelFrameNode);
        vBotao8GastoEnergetico_image.set_scale(0.009);
        vBotao8GastoEnergetico_image.set_pos(1.28, 0.0, 0.12);
        //vBotao8GastoEnergetico_image.hide();
        vBotao8GastoEnergetico_ledOFF = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
        vBotao8GastoEnergetico_ledOFF.reparent_to(graficoVariavelFrameNode);
        vBotao8GastoEnergetico_ledOFF.set_scale(0.004);
        vBotao8GastoEnergetico_ledOFF.set_pos(1.28, 0.0, 0.32);
        //vBotao8GastoEnergetico_ledOFF.hide();
        vBotao8GastoEnergetico_ledON = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
        vBotao8GastoEnergetico_ledON.reparent_to(graficoVariavelFrameNode);
        vBotao8GastoEnergetico_ledON.set_scale(0.004);
        vBotao8GastoEnergetico_ledON.set_pos(1.28, 0.0, 0.32);
        vBotao8GastoEnergetico_ledON.hide();
        vBotao8GastoEnergetico->setup(vBotao8GastoEnergetico_image);
        vBotao8GastoEnergetico->set_frame(-5.0 , 5.0 , -10.0, 10.0);

        vetorX = vector->getVectorTemperaturaAr();
        vetorY = vector->getVectorTemperaturaAr();
        legendaX = (string) "Temp do ar";
        legendaY = (string) "Temp do ar";
        limiteSuperiorX = 45;
        limiteInferiorX = 9;
        limiteSuperiorY = 45;
        limiteInferiorY = 9;
        tamanhoVetorX = vector->getSizeVectorTemperaturaAr();
        tamanhoVetorY = vector->getSizeVectorTemperaturaAr();

        graphicVariavel = new Graphics(&(optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        graphicVariavel->set_Position_Graphic(0.2, 0.6);
        graphicVariavel->set_scale(1.2);
        graphicVariavel->hide();

        //----------------------------------------------------------------------
	TimeControl::get_instance()->set_habilita_event_frame_gui(true);
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_segundo_real, update_gui, this);
	
        Simdunas::get_evt_handler()->add_hook(botaoGrafico->get_click_event(MouseButton::one()), click_event_botao_grafico,this);
        Simdunas::get_evt_handler()->add_hook(botaoEscolhaGraficoTempo->get_click_event(MouseButton::one()), click_event_botao_grafico_tempo,this);
        Simdunas::get_evt_handler()->add_hook(botaoEscolhaGraficoVariavel->get_click_event(MouseButton::one()), click_event_botao_grafico_variavel,this);
        Simdunas::get_evt_handler()->add_hook(botao1TempInterna->get_click_event(MouseButton::one()), click_event_botao1_grafico_TempInterna,this);
        Simdunas::get_evt_handler()->add_hook(botao2Hidratcao->get_click_event(MouseButton::one()), click_event_botao2_grafico_Hidratacao, this);
        Simdunas::get_evt_handler()->add_hook(botao3TempAr->get_click_event(MouseButton::one()), click_event_botao3_grafico_TempAr,this);
        Simdunas::get_evt_handler()->add_hook(botao4UmidadeAr->get_click_event(MouseButton::one()), click_event_botao4_grafico_Umidade,this);
        Simdunas::get_evt_handler()->add_hook(botao5TempSolo->get_click_event(MouseButton::one()), click_event_botao5_grafico_TempSolo,this);
        Simdunas::get_evt_handler()->add_hook(botao6Alimentacao->get_click_event(MouseButton::one()), click_event_botao6_grafico_Alimentacao, this);
        Simdunas::get_evt_handler()->add_hook(botao7Energia->get_click_event(MouseButton::one()), click_event_botao7_grafico_Energia,this);
        Simdunas::get_evt_handler()->add_hook(botao8GastoEnergetico->get_click_event(MouseButton::one()), click_event_botao8_grafico_GastoEnergetico,this);
        Simdunas::get_evt_handler()->add_hook(vBotao1TempInterna->get_click_event(MouseButton::one()), click_event_vBotao1_grafico_TempInterna,this);
        Simdunas::get_evt_handler()->add_hook(vBotao2Hidratcao->get_click_event(MouseButton::one()), click_event_vBotao2_grafico_Hidratacao, this);
        Simdunas::get_evt_handler()->add_hook(vBotao3TempAr->get_click_event(MouseButton::one()), click_event_vBotao3_grafico_TempAr,this);
        Simdunas::get_evt_handler()->add_hook(vBotao4UmidadeAr->get_click_event(MouseButton::one()), click_event_vBotao4_grafico_Umidade,this);
        Simdunas::get_evt_handler()->add_hook(vBotao5TempSolo->get_click_event(MouseButton::one()), click_event_vBotao5_grafico_TempSolo,this);
        Simdunas::get_evt_handler()->add_hook(vBotao6Alimentacao->get_click_event(MouseButton::one()), click_event_vBotao6_grafico_Alimentacao, this);
        Simdunas::get_evt_handler()->add_hook(vBotao7Energia->get_click_event(MouseButton::one()), click_event_vBotao7_grafico_Energia,this);
        Simdunas::get_evt_handler()->add_hook(vBotao8GastoEnergetico->get_click_event(MouseButton::one()), click_event_vBotao8_grafico_GastoEnergetico,this);

}

void GuiManager::notifyGameOver() {
	update_gui(NULL,this);
    is_game_over = true;
    Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_segundo_real, update_gui, this);
    Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame_gui_options, update_gui, this);
}

void GuiManager::click_event_botao_grafico(const Event*, void *data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    /*Aqui, antes de chamar os graficos é verificado se o jogo não está PAUSADO,
    caso esteja sera escondida a tela de pause*/
    if (Menu::get_instance()->get_flag_stop_time_pause()) {
        Menu::get_instance()->hide_tela_pause();
    }

    //Caso as opções dos graficos esteja fechada.
    if (this_guiManager->gui_options_flag == false) {

        if (flag_piscar) {//caso o calango esteja piscando será necessário tira-lo para que não fique piscando enquanto mostra os gráficos
            conta = 0;
            flag_piscar = false;
            piscar.detach_node();
            Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_segundo_real, verifica_conta, this_guiManager);
        }


        if (is_game_over) {
            Menu::get_instance()->hide_tela_over();
        }
        this_guiManager->esconde_mostradores();
        this_guiManager->mostra_opcoes_dos_graficos();
        grafico_tempo_ativo = true;
        grafico_variavel_ativo = false;
        botao1Flag = true;
        botao2Flag = true;
        botao3Flag = false;
        botao4Flag = false;
        botao5Flag = false;
        botao6Flag = false;
        botao7Flag = false;
        botao8Flag = false;

        this_guiManager->graficoPosicao1 = true;
        this_guiManager->graficoPosicao2 = true;
        this_guiManager->grafico1Cima = true;
        this_guiManager->grafico1Baixo = false;
        this_guiManager->grafico2Cima = false;
        this_guiManager->grafico2Baixo = true;
        this_guiManager->grafico3Cima = false;
        this_guiManager->grafico3Baixo = false;
        this_guiManager->grafico4Cima = false;
        this_guiManager->grafico4Baixo = false;
        this_guiManager->grafico5Cima = false;
        this_guiManager->grafico5Baixo = false;
        this_guiManager->grafico6Cima = false;
        this_guiManager->grafico6Baixo = false;
        this_guiManager->grafico7Cima = false;
        this_guiManager->grafico7Baixo = false;
        this_guiManager->grafico8Cima = false;
        this_guiManager->grafico8Baixo = false;

        this_guiManager->inicia_graficos();

        Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame_gui_options, init_options, this_guiManager);
        TimeControl::get_instance()->set_stop_time(true);
    } else {
        this_guiManager->gui_options_flag2 = true;
    }

}

void GuiManager::update_gui(const Event*, void *data) {
    //TODO:Chamar método genérico para mostrar temperatura do ambiente, não mais temperatura do ar, do solo, etc...

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    if (!is_game_over) {
        //this_guiManager->my_bar.set_value(this_guiManager->my_bar.get_value() - 0.01, 0.02, 0.22);
        this_guiManager->life_bar.set_value((Player::get_instance()->get_energia() / 100), 0.02, 0.22);
        //A barra varia de -9.5 até 9.5, por isso 0.19 * valor_de_hidratação.
        this_guiManager->hidratacao_scrollBar.set_value(0.19 * (Player::get_instance()->get_hidratacao()));
        sprintf(this_guiManager->stringHidratacao, "%.1f", Player::get_instance()->get_hidratacao());
        this_guiManager->labelHidratacao->set_text(this_guiManager->stringHidratacao);

        //FAZENDO OS CALCULOS PRA PARAMETRIZAR A TEMPERATURA DO LAGARTO
        if (Player::get_instance()->get_temp_interna() < Player::get_instance()->get_temp_interna_maxlimite()) {
            float passo = (17 - 2) / (Player::get_instance()->get_temp_interna_maxlimite() - Player::get_instance()->get_temp_interna_minlimite());
            this_guiManager->temperatura_scrollBar.set_value((3 + ((Player::get_instance()->get_temp_interna() - Player::get_instance()->get_temp_interna_minlimite()) * passo) - 2*passo));
            //cout << (3 + ((Player::get_instance()->get_temp_interna() - Player::get_instance()->get_temp_interna_minlimite()) * passo)) << endl;
            sprintf(this_guiManager->stringTemperatura, "%.1f", Player::get_instance()->get_temp_interna());
            this_guiManager->labelTemperatura->set_text(this_guiManager->stringTemperatura);
        } else {
            if (Player::get_instance()->get_temp_interna() > Player::get_instance()->get_temp_interna_minlimite() && Player::get_instance()->get_temp_interna() < Player::get_instance()->get_temp_interna_maxlimite()) {
                float passo = (17 - 2) / (Player::get_instance()->get_temp_interna_maxlimite() - Player::get_instance()->get_temp_interna_minlimite());
                this_guiManager->temperatura_scrollBar.set_value(3 + ((Player::get_instance()->get_temp_interna() - Player::get_instance()->get_temp_interna_minlimite()) * passo));
                //cout << (3 + ((Player::get_instance()->get_temp_interna() - Player::get_instance()->get_temp_interna_minlimite()) * passo)) << endl;
                sprintf(this_guiManager->stringTemperatura, "%.1f", Player::get_instance()->get_temp_interna());
                this_guiManager->labelTemperatura->set_text(this_guiManager->stringTemperatura);
            } else {
                float passo = (17 - 2) / (Player::get_instance()->get_temp_interna_maxlimite() - Player::get_instance()->get_temp_interna_minlimite());
                this_guiManager->temperatura_scrollBar.set_value((3 + ((Player::get_instance()->get_temp_interna() - Player::get_instance()->get_temp_interna_minlimite()) * passo) + 2 * passo));
                //cout << (3 + ((Player::get_instance()->get_temp_interna() - 15) * passo)) << endl;
                sprintf(this_guiManager->stringTemperatura, "%.1f", Player::get_instance()->get_temp_interna());
                this_guiManager->labelTemperatura->set_text(this_guiManager->stringTemperatura);
            }
        }

        //FAZENDO OS CALCULOS PRA PARAMETRIZAR A TEMPERATURA DO ar
        if (Player::get_instance()->get_environment_temp() < LIMITE_INFERIOR_TEMP_AMBIENTE) {
            float passo = (17 - 2) / (LIMITE_SUPERIOR_TEMP_AMBIENTE - LIMITE_INFERIOR_TEMP_AMBIENTE);
            this_guiManager->tempAmbiente_scrollBar.set_value((3 + ((Player::get_instance()->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo) - 2*passo));
            //cout << (3 + ((Player::get_instance()->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo)) << endl;
            sprintf(this_guiManager->stringTemperaturaAmb, "%.1f", Player::get_instance()->get_environment_temp());
            this_guiManager->labelTemperaturaAmb->set_text(this_guiManager->stringTemperaturaAmb);
        } else {
            if (Player::get_instance()->get_environment_temp() > LIMITE_INFERIOR_TEMP_AMBIENTE && Player::get_instance()->get_environment_temp() < LIMITE_SUPERIOR_TEMP_AMBIENTE) {
                float passo = (17 - 2) / (LIMITE_SUPERIOR_TEMP_AMBIENTE - LIMITE_INFERIOR_TEMP_AMBIENTE);
                this_guiManager->tempAmbiente_scrollBar.set_value(3 + ((Player::get_instance()->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo));
                //cout << (3 + ((Player::get_instance()->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo)) << endl;
                sprintf(this_guiManager->stringTemperaturaAmb, "%.1f", Player::get_instance()->get_environment_temp());
                this_guiManager->labelTemperaturaAmb->set_text(this_guiManager->stringTemperaturaAmb);
            } else {
                float passo = (17 - 2) / (LIMITE_SUPERIOR_TEMP_AMBIENTE - LIMITE_INFERIOR_TEMP_AMBIENTE);
                this_guiManager->tempAmbiente_scrollBar.set_value((3 + ((Player::get_instance()->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo) + 2 * passo));
                //cout << (3 + ((Player::get_instance()->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo)) << endl;
                sprintf(this_guiManager->stringTemperaturaAmb, "%.1f", Player::get_instance()->get_environment_temp());
                this_guiManager->labelTemperaturaAmb->set_text(this_guiManager->stringTemperaturaAmb);
            }
        }

//        this_guiManager->tempAmbiente_scrollBar.set_value(0.19 * (Player::get_instance()->get_environment_temp()));
//        sprintf(this_guiManager->stringTemperaturaAmb, "%.1f", Player::get_instance()->get_environment_temp());
//        this_guiManager->labelTemperaturaAmb->set_text(this_guiManager->stringTemperaturaAmb);

        this_guiManager->umidade_scrollBar.set_value(0.19 * (MicroClima::get_instance()->get_umidade_relativa_sector()));
        sprintf(this_guiManager->stringUmidade, "%.1f", MicroClima::get_instance()->get_umidade_relativa_sector());
        this_guiManager->labelUmidade->set_text(this_guiManager->stringUmidade);

        sprintf(this_guiManager->stringVida, "%.1f", Player::get_instance()->get_energia());
        this_guiManager->labelDamage->set_text(this_guiManager->stringVida);

        sprintf(this_guiManager->stringCountEgg, "%d", Player::get_instance()->get_num_ovos());
        this_guiManager->labelCountEgg->set_text(this_guiManager->stringCountEgg);
    }

    //Controla o relogio.
    if (!is_game_over) {
        if (this_guiManager->cont_relogio >= 360) {
            this_guiManager->cont_relogio = 0;
        }
		this_guiManager->cont_relogio = 180+TimeControl::get_instance()->get_hora()*360.0/24+TimeControl::get_instance()->get_minuto()*360.0/(24*60);
		//nout << TimeControl::get_instance()->get_hora()<<":"<<TimeControl::get_instance()->get_minuto()<<">"<<this_guiManager->cont_relogio<<endl;
        //this_guiManager->cont_relogio = this_guiManager->cont_relogio + 0.25; //360/(24*60)
        this_guiManager->relogioDiaNoite.set_hpr(0.0, 0.0, this_guiManager->cont_relogio);
    }
}

void GuiManager::init_options(const Event *, void *data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (this_guiManager->gui_options_flag == false) {
        this_guiManager->cont_gui_options = this_guiManager->cont_gui_options - 0.02;
        if (this_guiManager->cont_gui_options >= -1.01) {
            this_guiManager->frameNode.set_pos(this_guiManager->cont_gui_options, 0.0, -1.0);
            this_guiManager->optionFrameNode.set_pos((this_guiManager->cont_gui_options + 0.42), 0.0, -1.0);
            this_guiManager->graficoVariavelFrameNode.set_pos((this_guiManager->cont_gui_options + 0.42), 0.0, -1.0);
        } else {
            this_guiManager->gui_options_flag = true;
        }
    } else {

        if (this_guiManager->gui_options_flag2 == true) {
            this_guiManager->cont_gui_options = this_guiManager->cont_gui_options + 0.02;
            if (this_guiManager->cont_gui_options <= 0.59) {
                this_guiManager->frameNode.set_pos(this_guiManager->cont_gui_options, 0.0, -1.0);
                this_guiManager->optionFrameNode.set_pos((this_guiManager->cont_gui_options + 0.42), 0.0, -1.0);
                this_guiManager->graficoVariavelFrameNode.set_pos((this_guiManager->cont_gui_options + 0.42), 0.0, -1.0);
            } else {
                this_guiManager->gui_options_flag = false;
                this_guiManager->gui_options_flag2 = false;
                this_guiManager->esconde_opcoes_dos_graficos();
                this_guiManager->mostra_mostradores();

                Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame_gui_options, init_options, this_guiManager);
                if (!is_game_over) {
					if(!Menu::get_instance()->get_flag_stop_time_pause()){//verifica se o jogo está pausado
                    TimeControl::get_instance()->set_stop_time(false);//caso esteja não libera o tempo virtual
					}
					else {
						Menu::get_instance()->show_tela_pause();
					}
                } else {
                    Menu::get_instance()->show_tela_over();
                }
            }
        }

    }
}

void GuiManager::build_options() {

    optionFrame = new PGVirtualFrame("Frame do menu de opcoes");
    optionFrame->setup(1.58, 2.0);
    PGFrameStyle style = optionFrame->get_frame_style(optionFrame->get_state());
    style.set_type(PGFrameStyle::T_flat);
    optionFrame->set_frame_style(optionFrame->get_state(), style);
    optionFrameNode = NodePath(optionFrame);
    optionFrameNode.reparent_to(Simdunas::get_window()->get_aspect_2d());
    //Seta a posição do frame
    optionFrameNode.set_pos(1.0, 0.0, -1.0);
    //Seta a cor do frame
    optionFrameNode.set_color(0.8, 0.8, 0.8);
    //Seta a transparencia do frame.
    optionFrameNode.set_transparency(TransparencyAttrib::M_alpha);
    optionFrameNode.set_alpha_scale(0.85);

    graficoVariavelFrame = new PGVirtualFrame("Frame das opcoes de grafico de variavel");
    graficoVariavelFrame->setup(1.58, 0.4);
    style = graficoVariavelFrame->get_frame_style(graficoVariavelFrame->get_state());
    style.set_type(PGFrameStyle::T_flat);
    graficoVariavelFrame->set_frame_style(graficoVariavelFrame->get_state(), style);
    graficoVariavelFrameNode = NodePath(graficoVariavelFrame);
    graficoVariavelFrameNode.reparent_to(Simdunas::get_window()->get_aspect_2d());
    //Seta a posição do frame
    graficoVariavelFrameNode.set_pos(1.0, 0.0, -1.0);
    //Seta a cor do frame
    graficoVariavelFrameNode.set_color(0.8, 0.8, 0.8);
    //Seta a transparencia do frame.
    graficoVariavelFrameNode.set_transparency(TransparencyAttrib::M_alpha);
    graficoVariavelFrameNode.set_alpha_scale(0.85);
    graficoVariavelFrameNode.hide();

}

void GuiManager::inicia_graficos() {
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

void GuiManager::esconde_graficos() {
    graphic->hide();
    graphic2->hide();
    graphic3->hide();
    graphic4->hide();
    graphic5->hide();
    graphic6->hide();
    graphic7->hide();
    graphic8->hide();
}

void GuiManager::novo_grafico1_TempInterna() {
    graphic = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorTemperaturaLagarto(), 0, 0, 55, 15, true);
    graphic->set_Position_Graphic(0.4, 1.0);
    graphic->set_scale(0.86);
    graphic->set_Titulo_Grafico("Temperatura Interna");
    graphic->set_Titulo_EixoX("Tempo (h)");
    graphic->set_Titulo_EixoY("Temperatura (C)");
    graphic->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorTemperaturaLagarto());
}

void GuiManager::novo_grafico2_Hidratacao(){
    graphic2 = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorHidratacaoLagarto(), 0, 0, 100, 0, true);
    graphic2->set_Position_Graphic(0.4, 1.0);
    graphic2->set_scale(0.86);
    graphic2->set_Titulo_Grafico("Hidratacao do lagarto");
    graphic2->set_Titulo_EixoX("Tempo (h)");
    graphic2->set_Titulo_EixoY("Hidratacao");
    graphic2->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorHidratacaoLagarto());
}

void GuiManager::novo_grafico3_TempAr() {
    graphic3 = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorTemperaturaAr(), 0, 0, 45, 9, true);
    graphic3->set_Position_Graphic(0.4, 1.0);
    graphic3->set_scale(0.86);
    graphic3->set_Titulo_Grafico("Temperatura do ar.");
    graphic3->set_Titulo_EixoX("Tempo (h)");
    graphic3->set_Titulo_EixoY("Temperatura (c)");
    graphic3->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorTemperaturaAr());
}

void GuiManager::novo_grafico4_Umidade() {
    graphic4 = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorUmidadeAmbiente(), 0, 0, 100, 0, true);
    graphic4->set_Position_Graphic(0.4, 1.0);
    graphic4->set_scale(0.86);
    graphic4->set_Titulo_Grafico("Umidade do ar.");
    graphic4->set_Titulo_EixoX("Tempo (h)");
    graphic4->set_Titulo_EixoY("Umidade");
    graphic4->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorUmidadeAmbiente());
}

void GuiManager::novo_grafico5_TempSolo(){
    graphic5 = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorTemperaturaSolo(), 0, 0, 70, 8, true);
    graphic5->set_Position_Graphic(0.4, 1.0);
    graphic5->set_scale(0.86);
    graphic5->set_Titulo_Grafico("Temperatura do Solo");
    graphic5->set_Titulo_EixoX("Tempo (h)");
    graphic5->set_Titulo_EixoY("Temperatura (C)");
    graphic5->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorTemperaturaSolo());
}

void GuiManager::novo_grafico6_Alimentacao(){
    graphic6 = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorAlimentacao(), 0, 0, 5, 0, true);
    graphic6->set_Position_Graphic(0.4, 1.0);
    graphic6->set_scale(0.86);
    graphic6->set_Titulo_Grafico("Alimentacao");
    graphic6->set_Titulo_EixoX("Tempo (h)");
    graphic6->set_Titulo_EixoY("Alimentacao");
    graphic6->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorAlimentacao());
}

void GuiManager::novo_grafico7_Energia(){
    graphic7 = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorEnergia(), 0, 0, 100, 0, true);
    graphic7->set_Position_Graphic(0.4, 1.0);
    graphic7->set_scale(0.86);
    graphic7->set_Titulo_Grafico("Energia");
    graphic7->set_Titulo_EixoX("Tempo (h)");
    graphic7->set_Titulo_EixoY("Energia");
    graphic7->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorEnergia());

}

void GuiManager::novo_grafico8_GastoEnergetico(){
    graphic8 = new Graphics(&(optionFrameNode), vector->getVectorTempo(), vector->getVectorGastoEnergeticoTotal(), 0, 0, 0.4, 0, true);
    graphic8->set_Position_Graphic(0.4, 1.0);
    graphic8->set_scale(0.86);
    graphic8->set_Titulo_Grafico("Gasto energetico");
    graphic8->set_Titulo_EixoX("Tempo (h)");
    graphic8->set_Titulo_EixoY("Gasto energetico");
    graphic8->create_Graphic(vector->getSizeVectorTempo(), vector->getSizeVectorGastoEnergiticoTotal());
}

void GuiManager::liga_led_estado_reprodutivo() {
    led.remove_node();
    led = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GreenLed.png");
    led.reparent_to(frameNode);
    led.set_scale(0.004);
    led.set_pos(0.16, 0.0, 0.32);
}

void GuiManager::desliga_led_estado_reprodutivo(){
    led.remove_node();
    led = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/gui/GrayLed.png");
    led.reparent_to(frameNode);
    led.set_scale(0.004);
    led.set_pos(0.16, 0.0, 0.32);
}

void GuiManager::esconde_mostradores(){
    relogioDiaNoite.hide();
    relogio_pointer.hide();
    calango.hide();
    calango_border.hide();
    label_np.hide();
    hidratacao_bar.hide();
    hidratacao_pointer.hide();
    hidratacao_image.hide();
    labelHidratacao_np.hide();
    temperatura_bar.hide();
    temperatura_pointer.hide();
    temperatura_image.hide();
    labelTemperatura_np.hide();
    tempAmbiente_bar.hide();
    tempAmbiente_pointer.hide();
    tempAmbiente_image.hide();
    labelTemperaturaAmb_np.hide();
    umidade_bar.hide();
    umidade_pointer.hide();
    umidade_image.hide();
    labelUmidade_np.hide();
    estadoReprodutivo.hide();
    led.hide();
    egg.hide();
    labelCountEgg_np.hide();
}

void GuiManager::mostra_mostradores(){
    relogioDiaNoite.show();
    relogio_pointer.show();
    calango.show();
    calango_border.show();
    label_np.show();
    hidratacao_bar.show();
    hidratacao_pointer.show();
    hidratacao_image.show();
    labelHidratacao_np.show();
    temperatura_bar.show();
    temperatura_pointer.show();
    temperatura_image.show();
    labelTemperatura_np.show();
    tempAmbiente_bar.show();
    tempAmbiente_pointer.show();
    tempAmbiente_image.show();
    labelTemperaturaAmb_np.show();
    umidade_bar.show();
    umidade_pointer.show();
    umidade_image.show();
    labelUmidade_np.show();
    estadoReprodutivo.show();
    led.show();
    egg.show();
    labelCountEgg_np.show();
}

void GuiManager::mostra_opcoes_dos_graficos(){
    this->mostra_painel_grafico_tempo();
}

void GuiManager::esconde_opcoes_dos_graficos(){
    this->esconde_painel_grafico_tempo();
    this->esconde_painel_grafico_variavel();
    graphicVariavel->hide();
    botaoEscolhaGrafico_label.hide();
    botaoEscolhaGraficoTempo_np.hide();
    botaoEscolhaGraficoTempo_image.hide();
    botaoEscolhaGraficoTempo_image_ativo.hide();
    botaoEscolhaGraficoVariavel_np.hide();
    botaoEscolhaGraficoVariavel_image.hide();
    botaoEscolhaGraficoVariavel_image_ativo.hide();
}

void GuiManager::click_event_botao_grafico_tempo(const Event*, void* data) {

     PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        this_guiManager->esconde_painel_grafico_tempo();
        this_guiManager->esconde_graficos();
        botaoEscolhaGraficoTempo_image.show();
        botaoEscolhaGraficoTempo_image_ativo.hide();
        botaoEscolhaGraficoVariavel_image_ativo.hide();
        botaoEscolhaGraficoVariavel_image.show();
        grafico_tempo_ativo = false;
    } else {
        this_guiManager->esconde_painel_grafico_variavel();
        this_guiManager->mostra_painel_grafico_tempo();
        this_guiManager->graphicVariavel->hide();
        this_guiManager->inicia_graficos();
        botaoEscolhaGraficoTempo_image.hide();
        botaoEscolhaGraficoTempo_image_ativo.show();
        botaoEscolhaGraficoVariavel_image_ativo.hide();
        botaoEscolhaGraficoVariavel_image.show();
        grafico_tempo_ativo = true;
        grafico_variavel_ativo = false;
        this_guiManager->graficoPosicao1 = true;
        this_guiManager->graficoPosicao2 = true;
        this_guiManager->grafico1Cima = true;
        this_guiManager->grafico1Baixo = false;
        this_guiManager->grafico2Cima = false;
        this_guiManager->grafico2Baixo = true;
        this_guiManager->grafico3Cima = false;
        this_guiManager->grafico3Baixo = false;
        this_guiManager->grafico4Cima = false;
        this_guiManager->grafico4Baixo = false;
        this_guiManager->grafico5Cima = false;
        this_guiManager->grafico5Baixo = false;
        this_guiManager->grafico6Cima = false;
        this_guiManager->grafico6Baixo = false;
        this_guiManager->grafico7Cima = false;
        this_guiManager->grafico7Baixo = false;
        this_guiManager->grafico8Cima = false;
        this_guiManager->grafico8Baixo = false;
    }
}

void GuiManager::click_event_botao_grafico_variavel(const Event*, void* data) {

     PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_variavel_ativo) {
        this_guiManager->esconde_painel_grafico_variavel();
        this_guiManager->esconde_graficos();
        botaoEscolhaGraficoVariavel_image_ativo.hide();
        botaoEscolhaGraficoVariavel_image.show();
        botaoEscolhaGraficoTempo_image.show();
        botaoEscolhaGraficoTempo_image_ativo.hide();
        this_guiManager->graphicVariavel->hide();
        grafico_variavel_ativo = false;
    } else {
        this_guiManager->mostra_painel_grafico_tempo();
        this_guiManager->mostra_painel_grafico_variavel();
        botaoEscolhaGraficoVariavel_image_ativo.show();
        botaoEscolhaGraficoVariavel_image.hide();
        botaoEscolhaGraficoTempo_image.show();
        botaoEscolhaGraficoTempo_image_ativo.hide();
        botao1TempInterna_ledOFF.show();
        botao1TempInterna_ledON.hide();
        botao2Hidratcao_ledOFF.show();
        botao2Hidratcao_ledON.hide();
        botao3TempAr_ledOFF.hide();
        botao3TempAr_ledON.show();
        botao4UmidadeAr_ledOFF.show();
        botao4UmidadeAr_ledON.hide();
        botao5TempSolo_ledOFF.show();
        botao5TempSolo_ledON.hide();
        botao6Alimentacao_ledOFF.show();
        botao6Alimentacao_ledON.hide();
        botao7Energia_ledOFF.show();
        botao7Energia_ledON.hide();
        botao8GastoEnergetico_ledOFF.show();
        botao8GastoEnergetico_ledON.hide();
        grafico_variavel_ativo = true;
        grafico_tempo_ativo = false;

        vetorX = this_guiManager->vector->getVectorTemperaturaAr();
        vetorY = this_guiManager->vector->getVectorTemperaturaAr();
        tamanhoVetorX = this_guiManager->vector->getSizeVectorTemperaturaAr();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorTemperaturaAr();
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;
        this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);
    }
}

void GuiManager::desliga_leds_painel_tempo(){
    botao1TempInterna_ledON.hide();
    botao2Hidratcao_ledON.hide();
    botao3TempAr_ledON.hide();
    botao4UmidadeAr_ledON.hide();
    botao5TempSolo_ledON.hide();
    botao6Alimentacao_ledON.hide();
    botao7Energia_ledON.hide();
    botao8GastoEnergetico_ledON.hide();
    botao1TempInterna_ledOFF.show();
    botao2Hidratcao_ledOFF.show();
    botao3TempAr_ledOFF.show();
    botao4UmidadeAr_ledOFF.show();
    botao5TempSolo_ledOFF.show();
    botao6Alimentacao_ledOFF.show();
    botao7Energia_ledOFF.show();
    botao8GastoEnergetico_ledOFF.show();
}

void GuiManager::desliga_leds_painel_variavel(){
    vBotao1TempInterna_ledON.hide();
    vBotao2Hidratcao_ledON.hide();
    vBotao3TempAr_ledON.hide();
    vBotao4UmidadeAr_ledON.hide();
    vBotao5TempSolo_ledON.hide();
    vBotao6Alimentacao_ledON.hide();
    vBotao7Energia_ledON.hide();
    vBotao8GastoEnergetico_ledON.hide();
    vBotao1TempInterna_ledOFF.show();
    vBotao2Hidratcao_ledOFF.show();
    vBotao3TempAr_ledOFF.show();
    vBotao4UmidadeAr_ledOFF.show();
    vBotao5TempSolo_ledOFF.show();
    vBotao6Alimentacao_ledOFF.show();
    vBotao7Energia_ledOFF.show();
    vBotao8GastoEnergetico_ledOFF.show();
}

void GuiManager::mostra_painel_grafico_tempo() {
    botaoEscolhaGrafico_label.show();
    botaoEscolhaGraficoTempo_np.show();
    botaoEscolhaGraficoTempo_image_ativo.show();
    botaoEscolhaGraficoVariavel_np.show();
    botaoEscolhaGraficoVariavel_image.show();
    botao1TempInterna_np.show();
    botao1TempInterna_image.show();
    botao1TempInterna_ledON.show();
    botao2Hidratcao_np.show();
    botao2Hidratcao_image.show();
    botao2Hidratcao_ledON.show();
    botao3TempAr_np.show();
    botao3TempAr_image.show();
    botao3TempAr_ledOFF.show();
    botao4UmidadeAr_np.show();
    botao4UmidadeAr_image.show();
    botao4UmidadeAr_ledOFF.show();
    botao5TempSolo_np.show();
    botao5TempSolo_image.show();
    botao5TempSolo_ledOFF.show();
    botao6Alimentacao_np.show();
    botao6Alimentacao_image.show();
    botao6Alimentacao_ledOFF.show();
    botao7Energia_np.show();
    botao7Energia_image.show();
    botao7Energia_ledOFF.show();
    botao8GastoEnergetico_np.show();
    botao8GastoEnergetico_image.show();
    botao8GastoEnergetico_ledOFF.show();
}

void GuiManager::esconde_painel_grafico_tempo() {
    botao1TempInterna_np.hide();
    botao1TempInterna_image.hide();
    botao1TempInterna_ledON.hide();
    botao1TempInterna_ledOFF.hide();
    botao2Hidratcao_np.hide();
    botao2Hidratcao_image.hide();
    botao2Hidratcao_ledON.hide();
    botao2Hidratcao_ledOFF.hide();
    botao3TempAr_np.hide();
    botao3TempAr_image.hide();
    botao3TempAr_ledON.hide();
    botao3TempAr_ledOFF.hide();
    botao4UmidadeAr_np.hide();
    botao4UmidadeAr_image.hide();
    botao4UmidadeAr_ledON.hide();
    botao4UmidadeAr_ledOFF.hide();
    botao5TempSolo_np.hide();
    botao5TempSolo_image.hide();
    botao5TempSolo_ledON.hide();
    botao5TempSolo_ledOFF.hide();
    botao6Alimentacao_np.hide();
    botao6Alimentacao_image.hide();
    botao6Alimentacao_ledON.hide();
    botao6Alimentacao_ledOFF.hide();
    botao7Energia_np.hide();
    botao7Energia_image.hide();
    botao7Energia_ledON.hide();
    botao7Energia_ledOFF.hide();
    botao8GastoEnergetico_np.hide();
    botao8GastoEnergetico_image.hide();
    botao8GastoEnergetico_ledON.hide();
    botao8GastoEnergetico_ledOFF.hide();
}

void GuiManager::mostra_painel_grafico_variavel(){
    this->esconde_graficos();
    graficoVariavelFrameNode.show();
}

void GuiManager::esconde_painel_grafico_variavel(){
    this->esconde_painel_grafico_tempo();
    graficoVariavelFrameNode.hide();
}

void GuiManager::click_event_botao1_grafico_TempInterna(const Event*, void *data) {

     PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico1Baixo || this_guiManager->grafico1Cima) {
            //cout << "entrou no IF da temperatura" << endl;
            this_guiManager->graphic->hide();
            botao1TempInterna_ledON.hide();
            botao1TempInterna_ledOFF.show();
            if (this_guiManager->grafico1Baixo) {
                this_guiManager->grafico1Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico1Cima) {
                this_guiManager->grafico1Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            //cout << "entrou no ELSE da temperatura" << endl;
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico1_TempInterna();
                this_guiManager->grafico1Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao1TempInterna_ledON.show();
                botao1TempInterna_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico1_TempInterna();
                    this_guiManager->graphic->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico1Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao1TempInterna_ledON.show();
                    botao1TempInterna_ledOFF.hide();
                    ;
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao1TempInterna_ledOFF.hide();
        botao1TempInterna_ledON.show();
        vetorY = this_guiManager->vector->getVectorTemperaturaLagarto();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorTemperaturaSolo();
        legendaY = (string) "Temp interna";
        limiteInferiorY = 15;
        limiteSuperiorY = 55;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;
        this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

    }
}

void GuiManager::click_event_botao2_grafico_Hidratacao(const Event*, void* data) {

     PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico2Baixo || this_guiManager->grafico2Cima) {
            //cout << "entrou no IF da temperatura" << endl;
            this_guiManager->graphic2->hide();
            botao2Hidratcao_ledON.hide();
            botao2Hidratcao_ledOFF.show();
            if (this_guiManager->grafico2Baixo) {
                this_guiManager->grafico2Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico2Cima) {
                this_guiManager->grafico2Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            //cout << "entrou no ELSE da temperatura" << endl;
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico2_Hidratacao();
                this_guiManager->grafico2Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao2Hidratcao_ledON.show();
                botao2Hidratcao_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico2_Hidratacao();
                    this_guiManager->graphic2->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico2Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao2Hidratcao_ledON.show();
                    botao2Hidratcao_ledOFF.hide();
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao2Hidratcao_ledOFF.hide();
        botao2Hidratcao_ledON.show();
        vetorY = this_guiManager->vector->getVectorHidratacaoLagarto();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorHidratacaoLagarto();
        legendaY = (string) "Hidratacao";
        limiteInferiorY = 0;
        limiteSuperiorY = 100;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);
    }
}

void GuiManager::click_event_botao3_grafico_TempAr(const Event*, void* data) {

     PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico3Baixo || this_guiManager->grafico3Cima) {
            //cout << "entrou no IF da temperatura_ambiente" << endl;
            this_guiManager->graphic3->hide();
            botao3TempAr_ledON.hide();
            botao3TempAr_ledOFF.show();
            if (this_guiManager->grafico3Baixo) {
                this_guiManager->grafico3Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico3Cima) {
                this_guiManager->grafico3Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            //cout << "entrou no ELSE da temperatura_ambiente" << endl;
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico3_TempAr();
                this_guiManager->grafico3Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao3TempAr_ledON.show();
                botao3TempAr_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico3_TempAr();
                    this_guiManager->graphic3->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico3Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao3TempAr_ledON.show();
                    botao3TempAr_ledOFF.hide();
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao3TempAr_ledOFF.hide();
        botao3TempAr_ledON.show();
        vetorY = this_guiManager->vector->getVectorTemperaturaAr();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorTemperaturaAr();
        legendaY = (string) "Temp do ar";
        limiteInferiorY = 9;
        limiteSuperiorY = 45;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

    }
}

void GuiManager::click_event_botao4_grafico_Umidade(const Event*, void* data) {

     PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico4Baixo || this_guiManager->grafico4Cima) {
            botao4UmidadeAr_ledON.hide();
            botao4UmidadeAr_ledOFF.show();
            //cout << "entrou no IF da umidade" << endl;
            this_guiManager->graphic4->hide();
            if (this_guiManager->grafico4Baixo) {
                this_guiManager->grafico4Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico4Cima) {
                this_guiManager->grafico4Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            //cout << "entrou no ELSE da umidade" << endl;
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico4_Umidade();
                this_guiManager->grafico4Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao4UmidadeAr_ledON.show();
                botao4UmidadeAr_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico4_Umidade();
                    this_guiManager->graphic4->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico4Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao4UmidadeAr_ledON.show();
                    botao4UmidadeAr_ledOFF.hide();
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao4UmidadeAr_ledOFF.hide();
        botao4UmidadeAr_ledON.show();
        vetorY = this_guiManager->vector->getVectorUmidadeAmbiente();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorUmidadeAmbiente();
        legendaY = (string) "Umidade";
        limiteInferiorY = 0;
        limiteSuperiorY = 100;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);
    }
}

void GuiManager::click_event_botao5_grafico_TempSolo(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico5Baixo || this_guiManager->grafico5Cima) {
            //cout << "entrou no IF da temperatura" << endl;
            this_guiManager->graphic5->hide();
            botao5TempSolo_ledON.hide();
            botao5TempSolo_ledOFF.show();
            if (this_guiManager->grafico5Baixo) {
                this_guiManager->grafico5Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico5Cima) {
                this_guiManager->grafico5Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            //cout << "entrou no ELSE da temperatura" << endl;
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico5_TempSolo();
                this_guiManager->grafico5Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao5TempSolo_ledON.show();
                botao5TempSolo_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico5_TempSolo();
                    this_guiManager->graphic5->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico5Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao5TempSolo_ledON.show();
                    botao5TempSolo_ledOFF.hide();
                    ;
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao5TempSolo_ledOFF.hide();
        botao5TempSolo_ledON.show();
        vetorY = this_guiManager->vector->getVectorTemperaturaSolo();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorTemperaturaSolo();
        legendaY = (string) "Temp do solo";
        limiteInferiorY = 8;
        limiteSuperiorY = 70;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);
    }
}

void GuiManager::click_event_botao6_grafico_Alimentacao(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico6Baixo || this_guiManager->grafico6Cima) {
            this_guiManager->graphic6->hide();
            botao6Alimentacao_ledON.hide();
            botao6Alimentacao_ledOFF.show();
            if (this_guiManager->grafico6Baixo) {
                this_guiManager->grafico6Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico6Cima) {
                this_guiManager->grafico6Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico6_Alimentacao();
                this_guiManager->grafico6Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao6Alimentacao_ledON.show();
                botao6Alimentacao_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico6_Alimentacao();
                    this_guiManager->graphic6->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico6Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao6Alimentacao_ledON.show();
                    botao6Alimentacao_ledOFF.hide();
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao6Alimentacao_ledOFF.hide();
        botao6Alimentacao_ledON.show();
        vetorY = this_guiManager->vector->getVectorAlimentacao();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorAlimentacao();
        legendaY = (string) "Alimentacao";
        limiteInferiorY = 0;
        limiteSuperiorY = 5;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);
    }
}

void GuiManager::click_event_botao7_grafico_Energia(const Event*, void* data) {

     PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico7Baixo || this_guiManager->grafico7Cima) {
            //cout << "entrou no IF da temperatura_ambiente" << endl;
            this_guiManager->graphic7->hide();
            botao7Energia_ledON.hide();
            botao7Energia_ledOFF.show();
            if (this_guiManager->grafico7Baixo) {
                this_guiManager->grafico7Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico7Cima) {
                this_guiManager->grafico7Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            //cout << "entrou no ELSE da temperatura_ambiente" << endl;
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico7_Energia();
                this_guiManager->grafico7Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao7Energia_ledON.show();
                botao7Energia_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico7_Energia();
                    this_guiManager->graphic7->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico7Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao7Energia_ledON.show();
                    botao7Energia_ledOFF.hide();
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao7Energia_ledOFF.hide();
        botao7Energia_ledON.show();
        vetorY = this_guiManager->vector->getVectorEnergia();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorEnergia();
        legendaY = (string) "Energia";
        limiteInferiorY = 0;
        limiteSuperiorY = 100;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);
    }
}

void GuiManager::click_event_botao8_grafico_GastoEnergetico(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;

    if (grafico_tempo_ativo) {
        if (this_guiManager->grafico8Baixo || this_guiManager->grafico8Cima) {
            botao8GastoEnergetico_ledON.hide();
            botao8GastoEnergetico_ledOFF.show();
            //cout << "entrou no IF da umidade" << endl;
            this_guiManager->graphic8->hide();
            if (this_guiManager->grafico8Baixo) {
                this_guiManager->grafico8Baixo = false;
                this_guiManager->graficoPosicao2 = false;
            }
            if (this_guiManager->grafico8Cima) {
                this_guiManager->grafico8Cima = false;
                this_guiManager->graficoPosicao1 = false;
            }
        } else {
            //cout << "entrou no ELSE da umidade" << endl;
            if (!this_guiManager->graficoPosicao1) {
                this_guiManager->novo_grafico8_GastoEnergetico();
                this_guiManager->grafico8Cima = true;
                this_guiManager->graficoPosicao1 = true;
                botao8GastoEnergetico_ledON.show();
                botao8GastoEnergetico_ledOFF.hide();
            } else {
                if (!this_guiManager->graficoPosicao2) {
                    this_guiManager->novo_grafico8_GastoEnergetico();
                    this_guiManager->graphic8->set_Position_Graphic(0.4, 0.1);
                    this_guiManager->grafico8Baixo = true;
                    this_guiManager->graficoPosicao2 = true;
                    botao8GastoEnergetico_ledON.show();
                    botao8GastoEnergetico_ledOFF.hide();
                }
            }
        }
    } else {
        this_guiManager->desliga_leds_painel_tempo();
        botao8GastoEnergetico_ledOFF.hide();
        botao8GastoEnergetico_ledON.show();
        vetorY = this_guiManager->vector->getVectorTemperaturaSolo();
        tamanhoVetorY = this_guiManager->vector->getSizeVectorTemperaturaSolo();
        legendaY = (string) "Gasto energetico";
        limiteInferiorY = 0;
        limiteSuperiorY = 0.4;
        this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
        this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
        this_guiManager->graphicVariavel->set_scale(1.2);
        string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
        this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
        this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
        this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);
    }
}

void GuiManager::click_event_vBotao1_grafico_TempInterna(const Event*, void *data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao1TempInterna_ledOFF.hide();
    vBotao1TempInterna_ledON.show();
    vetorX = this_guiManager->vector->getVectorTemperaturaLagarto();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorTemperaturaSolo();
    legendaX = (string) "Temp interna";
    limiteInferiorX = 15;
    limiteSuperiorX = 55;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::click_event_vBotao2_grafico_Hidratacao(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao2Hidratcao_ledOFF.hide();
    vBotao2Hidratcao_ledON.show();
    vetorX = this_guiManager->vector->getVectorHidratacaoLagarto();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorHidratacaoLagarto();
    legendaX = (string) "Hidratacao";
    limiteInferiorX = 0;
    limiteSuperiorX = 100;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::click_event_vBotao3_grafico_TempAr(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao3TempAr_ledOFF.hide();
    vBotao3TempAr_ledON.show();
    vetorX = this_guiManager->vector->getVectorTemperaturaAr();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorTemperaturaAr();
    legendaX = (string) "Temp do ar";
    limiteInferiorX = 9;
    limiteSuperiorX = 45;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::click_event_vBotao4_grafico_Umidade(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao4UmidadeAr_ledOFF.hide();
    vBotao4UmidadeAr_ledON.show();
    vetorX = this_guiManager->vector->getVectorUmidadeAmbiente();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorUmidadeAmbiente();
    legendaX = (string) "Umidade";
    limiteInferiorX = 0;
    limiteSuperiorX = 100;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::click_event_vBotao5_grafico_TempSolo(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao5TempSolo_ledOFF.hide();
    vBotao5TempSolo_ledON.show();
    vetorX = this_guiManager->vector->getVectorTemperaturaSolo();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorTemperaturaSolo();
    legendaX = (string) "Temp do solo";
    limiteInferiorX = 8;
    limiteSuperiorX = 70;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::click_event_vBotao6_grafico_Alimentacao(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao6Alimentacao_ledOFF.hide();
    vBotao6Alimentacao_ledON.show();
    vetorX = this_guiManager->vector->getVectorAlimentacao();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorAlimentacao();
    legendaX = (string) "Alimentacao";
    limiteInferiorX = 0;
    limiteSuperiorX = 100;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::click_event_vBotao7_grafico_Energia(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao7Energia_ledOFF.hide();
    vBotao7Energia_ledON.show();
    vetorX = this_guiManager->vector->getVectorEnergia();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorEnergia();
    legendaX = (string) "Energia";
    limiteInferiorX = 0;
    limiteSuperiorX = 100;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::click_event_vBotao8_grafico_GastoEnergetico(const Event*, void* data) {

    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->desliga_leds_painel_variavel();
    vBotao8GastoEnergetico_ledOFF.hide();
    vBotao8GastoEnergetico_ledON.show();
    vetorX = this_guiManager->vector->getVectorTemperaturaSolo();
    tamanhoVetorX = this_guiManager->vector->getSizeVectorTemperaturaSolo();
    legendaX = (string) "Gasto energetico";
    limiteInferiorX = 0;
    limiteSuperiorX = 0.8;
    this_guiManager->graphicVariavel = new Graphics(&(this_guiManager->optionFrameNode), vetorX, vetorY, limiteSuperiorX, limiteInferiorX, limiteSuperiorY, limiteInferiorY, false);
    this_guiManager->graphicVariavel->set_Position_Graphic(0.2, 0.6);
    this_guiManager->graphicVariavel->set_scale(1.2);
    string titulo = legendaX + (string) " x " + legendaY;         this_guiManager->graphicVariavel->set_Titulo_Grafico(titulo);
    this_guiManager->graphicVariavel->set_Titulo_EixoX(legendaX);
    this_guiManager->graphicVariavel->set_Titulo_EixoY(legendaY);
    this_guiManager->graphicVariavel->create_Graphic(tamanhoVetorX, tamanhoVetorY);

}

void GuiManager::mostra_moldura_toca(const Event*, void *data) {
    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->molduraToca.show();
}

void GuiManager::esconde_moldura_toca(const Event*, void *data) {
    PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
    this_guiManager->molduraToca.hide();
}

void GuiManager::piscar_life() {

    if (flag_piscar) {
        conta = 0;
    } else {

        piscar.reparent_to(Simdunas::get_window()->get_aspect_2d());
        flag_piscar = true;
        Simdunas::get_evt_handler()->add_hook(TimeControl::EV_segundo_real, verifica_conta, this);
        Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame_gui_options, verifica_conta, this);
    }

}

void GuiManager::verifica_conta(const Event*, void* data) {

    PT(GuiManager) this_manager = (PT(GuiManager)) (GuiManager*) data;

    if (this_manager->conta <= 1) {//será um valor fixo de um segundo que ficará piscando

        this_manager->conta = conta + 1;

    } else {

        this_manager->conta = 0;
        this_manager->flag_piscar = false;
        this_manager->piscar.detach_node();
        Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_segundo_real, verifica_conta, this_manager);
        Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame_gui_options, verifica_conta, this_manager);
    }
}
