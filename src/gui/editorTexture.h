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
    static void set_textura1(const Event*, void *data);
    static void set_textura2(const Event*, void *data);
    static void set_textura3(const Event*, void *data);
    static void set_textura4(const Event*, void *data);
    static void swap_texture(void *data);
    static void print_null(void *data);
    static void Paleta_cores( void *data);
    static void mudar_marcador(float a,float b,float c,void *data);
    static void mudar_marcador2(float a,float b,float c,void *data);
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

    NodePath  marcador_camada1, marcador_camada2,lagartoPersonalizado, nod_bot_personalizar, botao_red_np, botao_green_np,
    nod_bot_padrao_textura_1,nod_bot_padrao_textura_2,nod_bot_padrao_textura_3,nod_bot_padrao_textura_4,
    botao_blue_np, botao_white_np, botao_green2_np, botao_yellow_np, botao_brown_np, botao_black_np,
    botao2_red_np, botao2_green_np, botao2_blue_np, botao2_white_np, botao2_green2_np, botao2_yellow_np, botao2_brown_np,
    botao2_black_np, title_color;

     PGButton *botao_padrao_textura_1,*botao_padrao_textura_2, *botao_padrao_textura_3,*botao_padrao_textura_4, *botao_personalizar,
     *botao_red,*botao_green, *botao_blue, *botao_white, *botao_green2, *botao_yellow, *botao_brown, *botao_black,
    *botao2_red, *botao2_green, *botao2_blue, *botao2_white, *botao2_green2, *botao2_yellow, *botao2_brown, *botao2_black; //BOTÕES DA PALETA DE CORES

     static bool instanceFlag;
    static editorTexture *single;
};

#endif	/* _editorTexture_H */

