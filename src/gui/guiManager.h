#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "pandaFramework.h"
#include "eventQueue.h"
#include "eventHandler.h"
#include "timeControl.h"
#include "pgVirtualFrame.h"
#include "pgButton.h"
#include "imageBar.h"
#include "scrollBar.h"
#include "player.h"
#include "microClima.h"
#include "textNode.h"
#include "graphics.h"
#include "mouseWatcher.h"
#include "mouseWatcherGroup.h"
#include "vetores.h"

class Player;
class Graphics;

class GuiManager : public TypedReferenceCount {
public:
    static PT(GuiManager) get_instance();
    ~GuiManager();

    static TypeHandle get_class_type() {
        return _type_handle;
    }

    static void init_type() {
        register_type(_type_handle, "GuiManager");
    }
     void piscar_life();//método que ira controlar o calango piscante..
    static void verifica_conta(const Event*, void *data);
	void remove_hooks();//remove todos os hooks.......

    static void update_gui(const Event*, void *data);
    static void init_options(const Event*, void *data);
    static void mostra_moldura_toca(const Event*, void *data);
    static void esconde_moldura_toca(const Event*, void *data);
    static void unload_gui();
	void notifyGameOver();
    void build_options();
    void esconde_mostradores();
    void mostra_mostradores();
    void mostra_opcoes_dos_graficos();
    void esconde_opcoes_dos_graficos();
    void mostra_painel_grafico_tempo();
    void esconde_painel_grafico_tempo();
    void mostra_painel_grafico_variavel();
    void esconde_painel_grafico_variavel();
    void inicia_graficos();
    void esconde_graficos();
    void desliga_leds_painel_tempo();
    void desliga_leds_painel_variavel();
    void liga_led_estado_reprodutivo();
    void desliga_led_estado_reprodutivo();
    void novo_grafico1_TempInterna();
    void novo_grafico2_Hidratacao();
    void novo_grafico3_TempAr();
    void novo_grafico4_Umidade();
    void novo_grafico5_TempSolo();
    void novo_grafico6_Alimentacao();
    void novo_grafico7_Energia();
    void novo_grafico8_GastoEnergetico();
    static void click_event_botao_grafico(const Event*, void *data);
    static void click_event_botao_grafico_tempo(const Event*, void *data);
    static void click_event_botao_grafico_variavel(const Event*, void *data);
    static void click_event_botao1_grafico_TempInterna(const Event*, void *data);
    static void click_event_botao2_grafico_Hidratacao(const Event*, void *data);
    static void click_event_botao3_grafico_TempAr(const Event*, void *data);
    static void click_event_botao4_grafico_Umidade(const Event*, void *data);
    static void click_event_botao5_grafico_TempSolo(const Event*, void *data);
    static void click_event_botao6_grafico_Alimentacao(const Event*, void *data);
    static void click_event_botao7_grafico_Energia(const Event*, void *data);
    static void click_event_botao8_grafico_GastoEnergetico(const Event*, void *data);
    static void click_event_vBotao1_grafico_TempInterna(const Event*, void *data);
    static void click_event_vBotao2_grafico_Hidratacao(const Event*, void *data);
    static void click_event_vBotao3_grafico_TempAr(const Event*, void *data);
    static void click_event_vBotao4_grafico_Umidade(const Event*, void *data);
    static void click_event_vBotao5_grafico_TempSolo(const Event*, void *data);
    static void click_event_vBotao6_grafico_Alimentacao(const Event*, void *data);
    static void click_event_vBotao7_grafico_Energia(const Event*, void *data);
    static void click_event_vBotao8_grafico_GastoEnergetico(const Event*, void *data);

private:
    static TypeHandle _type_handle;
    GuiManager();
    static PT(GuiManager) instance;
    static bool instanceFlag;
    WindowFramework* window;
    PGVirtualFrame* testeFrame;
    NodePath frameNode;
    NodePath molduraToca;
    PGVirtualFrame* optionFrame;
    NodePath optionFrameNode;
    PGVirtualFrame* graficoVariavelFrame;
    NodePath graficoVariavelFrameNode;
    ImageBar life_bar;
    ScrollBar hidratacao_scrollBar;
    ScrollBar temperatura_scrollBar;
    ScrollBar tempAmbiente_scrollBar;
    ScrollBar umidade_scrollBar;
    TextNode* labelDamage;
    TextNode* labelCountEgg;
    TextNode* labelHidratacao;
    TextNode* labelTemperatura;
    TextNode* labelTemperaturaAmb;
    TextNode* labelUmidade;
    NodePath relogioDiaNoite;
    NodePath labelCountEgg_np;
    NodePath labelHidratacao_np;
    NodePath labelTemperatura_np;
    NodePath labelTemperaturaAmb_np;
    NodePath labelUmidade_np;
    NodePath estadoReprodutivo;
    NodePath led;
    NodePath egg;
    NodePath ledTemperatura;
    NodePath ledHidratacao;
    NodePath ledTempAmbiente;
    NodePath ledUmidade;
    NodePath botaoGrafico_np;
    NodePath ledTemperaturaAtivo;
    NodePath ledHidratacaoAtivo;
    NodePath ledTempAmbienteAtivo;
    NodePath ledUmidadeAtivo;
    NodePath botaoGrafico2;
    PGButton* botaoGrafico;
    //NodePath botaoGrafico_np;

   static NodePath piscar;//variável que será o nodepath da figura
   static bool flag_piscar;
   static int conta;
   /*static float controle_tempo_piscando;variável vai controlar o tempo que o calango vai ficar piscando, sem esse controle
                                         quando o tempo virtual demorar mais de passar vai ficar muito tempo piscando
                                         */


    PGButton* button;
    NodePath button_np;
    PGButton* button2;
    NodePath button2_np;
    PGButton* button3;
    NodePath button3_np;
    PGButton* button4;
    NodePath button4_np;
    //NodePath ledGray;
    //NodePath ledGreen;
    char stringHidratacao[10];
    char stringTemperatura[10];
    char stringTemperaturaAmb[10];
    char stringUmidade[10];
    char stringVida[10];
    char stringCountEgg[10];
    double cont_relogio;
    double cont_gui_options;
    //A flag gui_options_flag verifica se a janela de opções está aberta ou não.
    //gui_options_flag funciona com false pra fechado e true para aberto
    bool gui_options_flag;
    bool gui_options_flag2;
    bool ledTemperaturaON;
    bool ledHidratacaoON;
    bool ledTempAmbienteON;
    bool ledUmidadeON;
    PT(Graphics) graphic;
    PT(Graphics) graphic2;
    PT(Graphics) graphic3;
    PT(Graphics) graphic4;
    PT(Graphics) graphic5;
    PT(Graphics) graphic6;
    PT(Graphics) graphic7;
    PT(Graphics) graphic8;
    PT(Graphics) graphicVariavel;
    bool graficoPosicao1;
    bool graficoPosicao2;
    bool grafico1Cima;
    bool grafico1Baixo;
    bool grafico2Cima;
    bool grafico2Baixo;
    bool grafico3Cima;
    bool grafico3Baixo;
    bool grafico4Cima;
    bool grafico4Baixo;
    bool grafico5Cima;
    bool grafico5Baixo;
    bool grafico6Cima;
    bool grafico6Baixo;
    bool grafico7Cima;
    bool grafico7Baixo;
    bool grafico8Cima;
    bool grafico8Baixo;
    Vetores* vector;
    //NodePath graphic_np;

};

#endif
