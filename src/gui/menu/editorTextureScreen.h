/* 
 * File:   editorTexture.h
 * Author: tassalon
 *
 * Created on 2 de Fevereiro de 2011, 15:44
 */

#ifndef _editorTextureScreen_H
#define	_editorTextureScreen_H


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
#include "screenManager.h"
#include "screen.h"
//#include "audioManager.h"
//#include "audioSound.h"
#include "movieTexture.h"
#include "button.h"
#include "player.h"


#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(editorTextureScreen))(editorTextureScreen*)d)->mn(); }


class editorTextureScreen : public Screen{
public:

    AnimControlCollection anims2;
    editorTextureScreen(PT(ScreenManager) manager);

    virtual ~editorTextureScreen();

    void change_texture(RGBColord cor, int mask_x); //altera a textura inicial de um lagarto
    //eventos dos botões da primeira coluna da paleta de cores
    static void print_green(const Event*, void *data);
    static void print_green2(const Event*, void *data);
    static void print_red(const Event*, void *data);
    static void print_red2(const Event*, void *data);
    static void print_brown(const Event*, void *data);
    static void print_black(const Event*, void *data);
    static void print_white(const Event*, void *data);
    static void print_yellow(const Event*, void *data);
      //eventos dos botões da segunda coluna da paleta de cores
    static void print2_green(const Event*, void *data);
    static void print2_green2(const Event*, void *data);
    static void print2_red(const Event*, void *data);
    static void print2_red2(const Event*, void *data);
    static void print2_brown(const Event*, void *data);
    static void print2_black(const Event*, void *data);
    static void print2_white(const Event*, void *data);
    static void print2_yellow(const Event*, void *data);
  //eventos dos botões da terceira coluna da paleta de cores
    static void print3_green(const Event*, void *data);
    static void print3_green2(const Event*, void *data);
    static void print3_red(const Event*, void *data);
    static void print3_red2(const Event*, void *data);
    static void print3_brown(const Event*, void *data);
    static void print3_black(const Event*, void *data);
    static void print3_white(const Event*, void *data);
    static void print3_yellow(const Event*, void *data);

   // static void set_textura1(const Event*, void *data);
   // static void set_textura2(const Event*, void *data);
   // static void set_textura3(const Event*, void *data);
  //  static void set_textura4(const Event*, void *data);
    void marca_textura(int textura);
    void swap_texture();//faz a troca da textura atual pela personalizada
    void print_standard(); //definindo um cor inicial para as texturas a serem modificadas
    void Paleta_cores(int qtde_coluna);
    void mudar_marcador(float a,float b,float c);
    void mudar_marcador2(float a,float b,float c);
    void mudar_marcador3(float a,float b,float c);
    void hide_paleta_cores();
    void hide_tela_personalizado();
    void show_tela_personalizar();

    //métodos que serão implementados classe abstrata screen
    void load();
    void unload();
    void show();
    void hide();
  
    void default_button_config(PT(Button) button, NodePath &np,
			const string &text, float z, EventCallbackFunction *action);


private:

static   PNMImage textura_original;
static   PNMImage mascara;
static   PNMImage textura_personalizada;

    NodePath  marcador_camada1, marcador_camada2,marcador_camada3,lagartoPersonalizado, nod_bot_personalizar, botao_red_np, botao_green_np,
    nod_bot_padrao_textura_1,nod_bot_padrao_textura_2,nod_bot_padrao_textura_3,nod_bot_padrao_textura_4,
    botao_blue_np, botao_white_np, botao_green2_np, botao_yellow_np, botao_brown_np, botao_black_np,
    botao2_red_np, botao2_green_np, botao2_blue_np, botao2_white_np, botao2_green2_np, botao2_yellow_np, botao2_brown_np,
    botao2_black_np, title_color,npJogar, npVoltar,
    //NodePaths da terceira coluna da paleta de cores
    botao3_red_np, botao3_green_np, botao3_blue_np, botao3_white_np, botao3_green2_np, botao3_yellow_np, botao3_brown_np,
    botao3_black_np;

     PT(PGButton)  botao_personalizar,
     //BOTÕES DA PALETA DE CORES coluna 1
     botao_red,botao_green, botao_blue, botao_white, botao_green2, botao_yellow, botao_brown, botao_black,
     //BOTÕES DA PALETA DE CORES coluna 2
    botao2_red, botao2_green, botao2_blue, botao2_white, botao2_green2, botao2_yellow, botao2_brown, botao2_black,
    //BOTÕES DA PALETA DE CORES coluna 3
    botao3_red, botao3_green, botao3_blue, botao3_white, botao3_green2, botao3_yellow, botao3_brown, botao3_black;

     //botão voltar e jogar
    PT(Button) buttonJogar, buttonVoltar,botao_padrao_textura_1,botao_padrao_textura_2,
    botao_padrao_textura_3,botao_padrao_textura_4;

    ACTION(voltar_action);
    ACTION(jogo_action);
    ACTION(set_textura1);
    ACTION(set_textura2);
    ACTION(set_textura3);
    ACTION(set_textura4);
};

#undef ACTION
#endif	/* _editorTextureScreen_H */

