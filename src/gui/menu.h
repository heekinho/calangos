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

#include "player.h"

class Menu {

public:
	PT(AnimatedObjetoJogo) test;
	AnimControlCollection anims;

	~Menu();

       void start_Menu();

        static void informa_segundos(string aviso);
	static void event_clik(const Event*, void *data);
        static void event_voltar_funcao(const Event*, void *data);
        static void configure(const Event*, void *data);//evento de botão de configuração ira apresentar a configuração de tempo
        static void direita(const Event*, void *data);//evento do clique do botão para a direita
        static void esquerda(const Event*, void *data);//evento do clique do botão para a esquerda
        static void tropidurus_funcao(const Event*, void *data);//escolha da especie TROPIDURUS
        static void eurolophosaurus_funcao(const Event*, void *data);//escolha da especie EUROLOPHOSAURUS
        static void cnemidophorus_funcao(const Event*, void *data);//escolha da especie CNEMIDOPHORUS
        static void chama_pause_game(const Event*, void *data);

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
        void hide_tela_principal();//esconde a tela inicial mostrada
        void hide_tela_configuracao();//escondendo tela de configuração
		void hide_tela_pause();//esconde a tela de pausa quando chama o grafico
        void show_tela_over();
		void show_tela_pause();
        void show_tela_principal();
        void show_tela_configuracao();
        void remove_tela_menu();
	


private:
       
       
	Menu(WindowFramework *window);
        
        

	PandaFramework *_framework;
	PGButton *botao_iniciar, *botao_sair,*botao_restart, *botao_graph,
                 *botao_configuracoes,*botao_ok,*botao_voltar,*botao_mais,
                 *botao_menos,*botao_voltar_jogo;//botoes
	PGButton *botao_tropidurus, *botao_eurolophosaurus,*botao_cnemidophorus;//botoes de escolha das espécies
        NodePath button_np,nod_sair,nod_config_egg,nod_botao_ok,
                 nod_botao_voltar,nod_mais,nod_menos,nod_noid,nod_botao_voltar_jogo;//nodepaths dos botoes
        NodePath nod_bot_tropidurus, nod_bot_eurolophosaurus,nod_bot_cnemidophorus;//nodepaths dos botoes de escolha das especies
        NodePath marcador;//nodepath do marcador da especie escolhida
        NodePath lagarto,tropidurus,eurolophosasurus,cnemidophorus;//lagarto andando
        NodePath config_egg; //imagem para o botão de configurações
        NodePath title_config,escolha_especie,tempo,relogio_frase, indica_morte;//imagem com o título e frases que vão ser usados no menu de configurações
        int minuto_dia_virtual;//indica quantos minutos (REAL) será um dia virtual no jogo

        PGSliderBar  *slid;
        float ratio;
        static Menu *instance;

        static TextNode *tex;
        static NodePath node_texto,background_over;
        static bool rodar;
        static bool controle;

		//mudei de lugar
		static NodePath button_sair;
		static NodePath button_restart;
		static NodePath button_grafico;

        static char *tecla;

        PGVirtualFrame *frame_tela;
		Session *session;

		static NodePath logo;
                bool flag_stop_time_pause;//flag para controlar a pausa do jogo atraves da tecla esc
                //enum  {TROPIDURUS , EUROLOPHOSAURUS, CNEMIDOPHORUS};
                //static int especie;
				enum Causa_Mortis {DESNUTRICAO=1, DESIDRATACAO, ALTA_TEMPERATURA, BAIXA_TEMPERATURA, MORTE_IDADE};
                static Player::lizardEpecie especie;
};

#endif
