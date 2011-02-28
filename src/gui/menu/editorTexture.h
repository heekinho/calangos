/* 
 * File:   editorTexture.h
 * Author: tassalon
 *
 * Created on 2 de Fevereiro de 2011, 15:44
 */

#ifndef _editorTexture_H
#define	_editorTexture_H


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

//#include "audioManager.h"
//#include "audioSound.h"
#include "movieTexture.h"

#include "player.h"

class editorTexture {
public:

    AnimControlCollection anims2;
    editorTexture();
    editorTexture(const editorTexture& orig);
    virtual ~editorTexture();

    static void change_texture(void *data, RGBColord cor, int mask_x); //altera a textura inicial de um lagarto
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

    static void set_textura1(const Event*, void *data);
    static void set_textura2(const Event*, void *data);
    static void set_textura3(const Event*, void *data);
    static void set_textura4(const Event*, void *data);
    static void swap_texture(void *data);//faz a troca da textura atual pela personalizada
    static void print_standard(void *data); //definindo um cor inicial para as texturas a serem modificadas
    static void Paleta_cores( void *data, int qtde_coluna);
    static void mudar_marcador(float a,float b,float c,void *data);
    static void mudar_marcador2(float a,float b,float c,void *data);
    static void mudar_marcador3(float a,float b,float c,void *data);
    void hide_paleta_cores();
    void hide_tela_personalizado();
    void show_tela_personalizar(void *data);
    //métodos virtuais que serão usados para implementar os métodos abstratos da classe screen
    void load_screen();
    void unload_screen();
    void show_screen();
    void hide_screen();
    //SingleTon
    static editorTexture* get_instance();

private:

      //caminhos para definir uma textura incial para edição.
    static string path_textura_original;
    static string path_mascara;
    static string  path_textura_personalizada;

    NodePath  marcador_camada1, marcador_camada2,marcador_camada3,lagartoPersonalizado, nod_bot_personalizar, botao_red_np, botao_green_np,
    nod_bot_padrao_textura_1,nod_bot_padrao_textura_2,nod_bot_padrao_textura_3,nod_bot_padrao_textura_4,
    botao_blue_np, botao_white_np, botao_green2_np, botao_yellow_np, botao_brown_np, botao_black_np,
    botao2_red_np, botao2_green_np, botao2_blue_np, botao2_white_np, botao2_green2_np, botao2_yellow_np, botao2_brown_np,
    botao2_black_np, title_color,
    //NodePaths da terceira coluna da paleta de cores
    botao3_red_np, botao3_green_np, botao3_blue_np, botao3_white_np, botao3_green2_np, botao3_yellow_np, botao3_brown_np,
    botao3_black_np;

     PGButton *botao_padrao_textura_1,*botao_padrao_textura_2, *botao_padrao_textura_3,*botao_padrao_textura_4, *botao_personalizar,
     //BOTÕES DA PALETA DE CORES coluna 1
     *botao_red,*botao_green, *botao_blue, *botao_white, *botao_green2, *botao_yellow, *botao_brown, *botao_black,
     //BOTÕES DA PALETA DE CORES coluna 2
    *botao2_red, *botao2_green, *botao2_blue, *botao2_white, *botao2_green2, *botao2_yellow, *botao2_brown, *botao2_black,
    //BOTÕES DA PALETA DE CORES coluna 3
    *botao3_red, *botao3_green, *botao3_blue, *botao3_white, *botao3_green2, *botao3_yellow, *botao3_brown, *botao3_black;

     static bool instanceFlag;
    static editorTexture *single;
};

#endif	/* _editorTexture_H */

