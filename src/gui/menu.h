#ifndef MENU_H
#define MENU_H

#include "pandaFramework.h"
#include "session.h"
#include "cardMaker.h"
#include "pgItem.h"
#include "loader.h"
#include "texture.h"
#include "texturePool.h"
#include "pgButton.h"
#include "textNode.h"
#include "nodePath.h"
#include "pgVirtualFrame.h"
#include "pgSliderBar.h"

#include "audioManager.h"
#include "audioSound.h"
#include "movieTexture.h"

#include "player.h"


class Menu {
public:
    PT(AnimatedObjetoJogo) test;
    AnimControlCollection anims;

    ~Menu();

    void start_Menu();
    void play_movie(string file); //método que irá carregar e tocas os videos
    NodePath constroi_botao(string file, PGButton *botao); //método para a construção de botões (vai modularizar o código e economizar linhas)

    static void informa_segundos(string aviso);
    static void event_clik(const Event*, void *data);
    static void event_voltar_funcao(const Event*, void *data);
    static void configure(const Event*, void *data); //evento de botão de configuração ira apresentar a configuração de tempo
    static void direita(const Event*, void *data); //evento do clique do botão para a direita
    static void esquerda(const Event*, void *data); //evento do clique do botão para a esquerda
    static void tropidurus_funcao(const Event*, void *data); //escolha da especie TROPIDURUS
    static void eurolophosaurus_funcao(const Event*, void *data); //escolha da especie EUROLOPHOSAURUS
    static void cnemidophorus_funcao(const Event*, void *data); //escolha da especie CNEMIDOPHORUS
    static void personalizar_funcao(const Event*, void *data); //escolha Personalizar Especie
    static void colisao_funcao(const Event*, void *data); //ativar/desativar colisão no jogo
    static void chama_pause_game(const Event*, void *data);
    static void instrucoes_teclas(const Event*, void *data);
    static void creditos(const Event*, void *data);
    static void back(const Event*, void *data);
    static void next(const Event*, void *data);
    static void stop_movie(const Event*, void *data);
    static void change_texture(void *data, RGBColord cor, int mask_x);
    static void print_green(const Event*, void *data);
    static void print_green2(const Event*, void *data);
    static void print_red(const Event*, void *data);
    static void print_red2(const Event*, void *data);
    static void print_brown(const Event*, void *data);
    static void print_black(const Event*, void *data);
    static void print_white(const Event*, void *data);
    static void print_yellow(const Event*, void *data);
    static void print2_green(const Event*, void *data);
    static void print2_green2(const Event*, void *data);
    static void print2_red(const Event*, void *data);
    static void print2_red2(const Event*, void *data);
    static void print2_brown(const Event*, void *data);
    static void print2_black(const Event*, void *data);
    static void print2_white(const Event*, void *data);
    static void print2_yellow(const Event*, void *data);
    ///////////eventos dos botoes dos videos

    static void lagartos_play(const Event*, void *data);
    static void predadores_play(const Event*, void *data);
    static void presas_play(const Event*, void *data);
    static void habitat_play(const Event*, void *data);
    static void clima_play(const Event*, void *data);

    static void slide(const Event*, void* data);

    int get_minuto_dia_virtual();
    Player::lizardEpecie get_especie();
    bool get_rodar();
    bool get_flag_stop_time_pause();
    static void restart(const Event*, void *data);
    static void out(const Event*, void *data);
    static void graph(const Event*, void *data);
    static void Paleta_cores( void *data);
    static Menu* get_instance();
    bool get_colisao();

    void tela_over(Session *nsession);
    void pause_game();
    void hide_tela_over();
    void hide_tela_principal(); //esconde a tela inicial mostrada
    void hide_tela_configuracao(); //escondendo tela de configuração
    void hide_tela_pause(); //esconde a tela de pausa quando chama o grafico
    void hide_tela_instrucoes();
    void hide_tela_marcadores();
    void show_tela_over();
    void show_tela_pause();
    void show_tela_principal();
    void show_tela_personalizar(void *data);
    void show_tela_configuracao();
    void show_tela_instrucoes();
    void show_tela_marcadores();
    void remove_tela_menu();
    void hide_paleta_cores();
    void hide_tela_personalizado();

    AudioManager * get_audioManager();
    AudioSound * get_sound();
    bool get_playing_movie();

private:


    Menu(WindowFramework *window);



    PandaFramework *_framework;
    PGButton *botao_iniciar, *botao_sair, *botao_restart, *botao_graph,
    *botao_configuracoes, *botao_ok, *botao_voltar, *botao_mais,
    *botao_menos, *botao_voltar_jogo, *botao_instrucao, *botao_next, *botao_back,*botao_creditos, *botao_colisao; //botoes
    PGButton *botao_tropidurus, *botao_eurolophosaurus, *botao_cnemidophorus, *botao_personalizar, *botao_red, 
    *botao_green, *botao_blue, *botao_white, *botao_green2, *botao_yellow, *botao_brown, *botao_black, //botoes de escolha das espécies
    *botao2_red, *botao2_green, *botao2_blue, *botao2_white, *botao2_green2, *botao2_yellow, *botao2_brown, *botao2_black; //BOTÕES DA PALETA DE CORES

    PGButton *lagartos, *predadores, *presas, *habitat, *variacao_clima; //botoes dos videos
    NodePath button_np, nod_sair, nod_config_egg, nod_botao_ok,nod_bot_colisao,
    nod_botao_voltar, nod_mais, nod_menos, nod_noid, nod_botao_voltar_jogo, nod_botao_instrucao, nod_botao_next, nod_botao_back, nod_botao_creditos; //nodepaths dos botoes
    NodePath nod_bot_tropidurus, nod_bot_eurolophosaurus, nod_bot_cnemidophorus, nod_bot_personalizar, botao_red_np, botao_green_np,
    botao_blue_np, botao_white_np, botao_green2_np, botao_yellow_np, botao_brown_np, botao_black_np, //nodepaths dos botoes de escolha das especies
    botao2_red_np, botao2_green_np, botao2_blue_np, botao2_white_np, botao2_green2_np, botao2_yellow_np, botao2_brown_np, botao2_black_np;
   
    NodePath colisaoVerdade, colisaoFalso,marcador, credit; //nodepath do marcador da especie escolhida
    NodePath lagarto,lagartoPersonalizado, tropidurus, eurolophosasurus, cnemidophorus; //lagarto andando
    NodePath config_egg, videos; //imagem para o botão de configurações
    NodePath title_config, escolha_especie, tempo, relogio_frase, indica_morte, title_color; //imagem com o título e frases que vão ser usados no menu de configurações
    NodePath nod_bot_lagartos, nod_bot_predadores, nod_bot_presas, nod_bot_habitat, nod_bot_variacao_clima;
    int minuto_dia_virtual; //indica quantos minutos (REAL) será um dia virtual no jogo

    PGSliderBar *slid;
    float ratio;
    static Menu *instance;

    static TextNode *tex,*tex_obj;
    static NodePath node_texto, background_over, background_instrucoes, background_icones,node_tex_obj,frameNode;
    static bool rodar;
    static bool controle;
    static bool colisao;

    //mudei de lugar
    static NodePath button_sair;
    static NodePath button_restart;
    static NodePath button_grafico;

    static char *tecla;

    PGVirtualFrame *frame_tela, *frame_instrucoes;
    Session *session;

    static NodePath logo;
    bool flag_stop_time_pause; //flag para controlar a pausa do jogo atraves da tecla esc
    //enum  {TROPIDURUS , EUROLOPHOSAURUS, CNEMIDOPHORUS};
    //static int especie;

    enum Causa_Mortis {
        DESNUTRICAO = 1, DESIDRATACAO, ALTA_TEMPERATURA, BAIXA_TEMPERATURA, MORTE_IDADE
    };
    static Player::lizardEpecie especie;

    PT(MovieTexture) mov;
    CardMaker *cm;
    NodePath node_card;
    PT(AudioManager) AM;
    PT(AudioSound) ASound;

    bool showing_conf; //flag para saber qual tela ta sendo mostrada (Configurações ou Instruções)
    bool playing_movio; //flag para saber se o vídeio esta sendo tocado
    static bool showing_creditos;//flag para controlar a volta da tela de créditos
    static bool showing_custom;
};

#endif

