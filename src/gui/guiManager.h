#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "pandaFramework.h"
#include "eventHandler.h"
#include "mouseWatcher.h"
#include "mouseWatcherGroup.h"
#include "timeControl.h"
#include "pgVirtualFrame.h"
#include "pgButton.h"
#include "imageBar.h"
#include "scrollBar.h"
#include "player.h"
#include "microClima.h"
#include "textNode.h"
#include "graphics.h"
//#include "vetores.h"
#include "gameStatusBar.h"
#include "graphicsMenu.h"

class Player;
class GraphicsMenu;
//class Graphics;

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

    void make_frame();
     void piscar_life();//método que ira controlar o calango piscante..
    static void verifica_conta(const Event*, void *data);
	void remove_hooks();//remove todos os hooks.......

	bool is_status_seta();

    static void update_gui(const Event*, void *data);
    static void init_options(const Event*, void *data);
    static void mostra_moldura_toca(const Event*, void *data);
    static void esconde_moldura_toca(const Event*, void *data);
    static void unload_gui();
	void notifyGameOver();
    void liga_led_estado_reprodutivo();
    void desliga_led_estado_reprodutivo();
    void hide_frameNode();
    void show_frameNode();
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

    GameStatusBar* get_game_status_bar();
    void activate_predator_alert(Predator* pursuer);

private:
    static const int TEMP_INTERNA;
    static const int HIDRATACAO;
    static const int TEMP_AR;
    static const int UMIDADE;
    static const int TEMP_SOLO;
    static const int ALIMENTACAO;
    static const int ENERGIA;
    static const int GASTO_ENERGETICO;

    static const string NOME_TEMP_INTERNA;
	static const string NOME_HIDRATACAO;
	static const string NOME_TEMP_AR;
	static const string NOME_UMIDADE;
	static const string NOME_TEMP_SOLO;
	static const string NOME_ALIMENTACAO;
	static const string NOME_ENERGIA;
	static const string NOME_GASTO_ENERGETICO;

    static TypeHandle _type_handle;
    GuiManager();
    static PT(GuiManager) instance;
    static bool instanceFlag;
    PT(GameStatusBar) game_status_bar;
    PT(GraphicsMenu) graphics_menu;
    PGVirtualFrame* menu_frame;
    NodePath menu_frame_np;
    NodePath moldura_toca;

   static bool flag_piscar;
   static int conta;
   /*static float controle_tempo_piscando;variável vai controlar o tempo que o calango vai ficar piscando, sem esse controle
                                         quando o tempo virtual demorar mais de passar vai ficar muito tempo piscando
                                         */


    char string_hidratacao[10];
    char string_temperatura[10];
    char string_temp_amb[10];
    char string_umidade[10];
    char string_vida[10];
    char string_count_egg[10];
    char string_idade_numero[10];
    double cont_relogio;
    double cont_gui_options;
    //A flag gui_options_flag verifica se a janela de opções está aberta ou não.
    //gui_options_flag funciona com false pra fechado e true para aberto
    bool gui_options_flag;
    bool gui_options_flag2;
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

    bool status_seta;

    static NodePath img_arrow_predator_position;
    static bool is_showing_arrow_predator;
    static AsyncTask::DoneStatus showing_predator_location(GenericAsyncTask* task, void* data);
	static AsyncTask::DoneStatus arrow_predator_effect(GenericAsyncTask* task, void* data);
	void show_predator_location(void* data);
	void set_predator_location_img(string image_name);

	void print_queue_values(queue<double> qx, queue<double> qy);
	int var_x;
	int var_y;
	queue<double> x_values;
	queue<double> y_values;
};

#endif
