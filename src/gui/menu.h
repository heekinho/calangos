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
    static void chama_pause_game(const Event*, void *data);
    static void instrucoes_teclas(const Event*, void *data);
    static void back(const Event*, void *data);
    static void next(const Event*, void *data);
    static void stop_movie(const Event*, void *data);

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
    static Menu* get_instance();


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
    void show_tela_configuracao();
    void show_tela_instrucoes();
    void show_tela_marcadores();
    void remove_tela_menu();


    AudioManager * get_audioManager();
    AudioSound * get_sound();
    bool get_playing_movie();

private:


    Menu(WindowFramework *window);



    PandaFramework *_framework;
    PGButton *botao_iniciar, *botao_sair, *botao_restart, *botao_graph,
    *botao_configuracoes, *botao_ok, *botao_voltar, *botao_mais,
    *botao_menos, *botao_voltar_jogo, *botao_instrucao, *botao_next, *botao_back,*botao_creditos; //botoes
    PGButton *botao_tropidurus, *botao_eurolophosaurus, *botao_cnemidophorus; //botoes de escolha das espécies
    PGButton *lagartos, *predadores, *presas, *habitat, *variacao_clima; //botoes dos videos
    NodePath button_np, nod_sair, nod_config_egg, nod_botao_ok,
    nod_botao_voltar, nod_mais, nod_menos, nod_noid, nod_botao_voltar_jogo, nod_botao_instrucao, nod_botao_next, nod_botao_back, nod_botao_creditos; //nodepaths dos botoes
    NodePath nod_bot_tropidurus, nod_bot_eurolophosaurus, nod_bot_cnemidophorus; //nodepaths dos botoes de escolha das especies
    NodePath marcador; //nodepath do marcador da especie escolhida
    NodePath lagarto, tropidurus, eurolophosasurus, cnemidophorus; //lagarto andando
    NodePath config_egg, videos; //imagem para o botão de configurações
    NodePath title_config, escolha_especie, tempo, relogio_frase, indica_morte; //imagem com o título e frases que vão ser usados no menu de configurações
    NodePath nod_bot_lagartos, nod_bot_predadores, nod_bot_presas, nod_bot_habitat, nod_bot_variacao_clima;
    int minuto_dia_virtual; //indica quantos minutos (REAL) será um dia virtual no jogo

    PGSliderBar *slid;
    float ratio;
    static Menu *instance;

    static TextNode *tex,*tex_obj;
    static NodePath node_texto, background_over, background_instrucoes, background_icones,node_tex_obj,frameNode;
    static bool rodar;
    static bool controle;

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

};

#endif

