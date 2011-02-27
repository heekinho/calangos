/* 
 * File:   editorTexture.cxx
 * Author: tassalon
 * 
 * Created on 2 de Fevereiro de 2011, 15:44
 */

#include "editorTexture.h"
#include "nodePath.h"
#include "textNode.h"
#include "mouseButton.h"
#include "pgSliderBar.h"
#include "fontPool.h"
#include "eventQueue.h"
#include "guiManager.h"
#include "textureStageCollection.h"
#include "menu.h"


bool editorTexture::instanceFlag = false;
editorTexture* editorTexture::single = NULL;
string editorTexture::path_textura_personalizada = "models/lizards/custom/young/custom.jpg";
string editorTexture::path_mascara = "models/lizards/custom/young/teiu_mask.jpg";
string editorTexture::path_textura_original = "models/lizards/custom/young/teiu.jpg";


editorTexture::editorTexture() {
    lagartoPersonalizado = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/custom/young/model");
    lagartoPersonalizado.set_scale(0.08, 0.08, 0.08);
    lagartoPersonalizado.set_pos(0, 35, -2);
    lagartoPersonalizado.set_h(45);
    lagartoPersonalizado.set_p(20);

    //		 Animação
    Simdunas::get_window()->load_model(lagartoPersonalizado, "models/lizards/custom/young/walk");
    auto_bind(lagartoPersonalizado.node(), anims2, PartGroup::HMF_ok_part_extra |
    PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims2.loop_all(false);
    lagartoPersonalizado.hide();

}

editorTexture::editorTexture(const editorTexture& orig) {
}

editorTexture::~editorTexture() {
}
//singleTon
editorTexture* editorTexture::get_instance() {
	if(!instanceFlag) {
        single = new editorTexture();
        instanceFlag = true;
    }
    return single;
}

void editorTexture::hide_paleta_cores(){ //remove todos os botões da paleta de cores
    if(!botao_red_np.is_empty()){
    botao_red_np.remove_node();
    botao_blue_np.remove_node();
    botao_green_np.remove_node();
    botao_yellow_np.remove_node();
    botao_white_np.remove_node();
    botao_black_np.remove_node();
    botao_brown_np.remove_node();
    botao_green2_np.remove_node();
    botao2_red_np.remove_node();
    botao2_blue_np.remove_node();
    botao2_green_np.remove_node();
    botao2_yellow_np.remove_node();
    botao2_white_np.remove_node();
    botao2_black_np.remove_node();
    botao2_brown_np.remove_node();
    botao2_green2_np.remove_node();
    }
}

void editorTexture::hide_tela_personalizado(){
    lagartoPersonalizado.hide();
    marcador_camada1.remove_node();
    marcador_camada2.remove_node();
    hide_paleta_cores();
    title_color.remove_node();
    nod_bot_padrao_textura_1.remove_node();
    nod_bot_padrao_textura_2.remove_node();
    nod_bot_padrao_textura_3.remove_node();
    nod_bot_padrao_textura_4.remove_node();

}

//implementa método abstrato
void editorTexture::hide_screen(){
    hide_tela_personalizado();
}

void editorTexture::show_screen(){
    show_tela_personalizar(this);
}

void editorTexture::load_screen(){
      show_tela_personalizar(this);
}

void editorTexture::unload_screen(){
    hide_tela_personalizado();
     lagartoPersonalizado.remove_node();
}

void editorTexture::show_tela_personalizar(void *data) {
    editorTexture *c = (editorTexture*) data;
            //carregando o quadro (marcador) de cor selecionada da primeira coluna da paleta de cores/////////

        c->marcador_camada1 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        c->marcador_camada1.set_scale(0.17, 0.0, 0.17);
        c->marcador_camada1.hide();
      //  c->marcador_camada1.set_pos(4.0, 0.0, -4.7);

        c->marcador_camada2 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        c->marcador_camada2.set_scale(0.17, 0.0, 0.17);
        c->marcador_camada2.hide();
     //   c->marcador_camada2.set_pos(4.0, 0.0, -4.7);
    ///carregando titulo do editor de cores
        c->title_color = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/editorcores");
        c->title_color.set_scale(1, 2 ,0.4);
        c->title_color.set_pos(0, 0, 0.8);
        c->title_color.show();


       // Botão da textura 1 para o jogador poder editar a cor dessa textura
        NodePath padrao_textura_1 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura1");
        padrao_textura_1.detach_node();
        c->botao_padrao_textura_1 = new PGButton("textura1");
        c->botao_padrao_textura_1->setup(padrao_textura_1);
        c->nod_bot_padrao_textura_1 = Simdunas::get_window()->get_aspect_2d().attach_new_node(c->botao_padrao_textura_1);
        c->nod_bot_padrao_textura_1.set_scale(0.6, 0.1, 0.18);
        c->nod_bot_padrao_textura_1.set_pos(-0.8, 0.0, 0.6);
        c->botao_padrao_textura_1->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(c->botao_padrao_textura_1->get_click_event(MouseButton::one()), set_textura1, c); //fazer metodo   padra_textura_1_funcao

         // Botão da textura2 para o jogador poder editar a cor dessa textura
        NodePath padrao_textura_2 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura2");
        padrao_textura_2.detach_node();
        c->botao_padrao_textura_2 = new PGButton("textura2");
        c->botao_padrao_textura_2->setup(padrao_textura_2);
        c->nod_bot_padrao_textura_2 = Simdunas::get_window()->get_aspect_2d().attach_new_node(c->botao_padrao_textura_2);
        c->nod_bot_padrao_textura_2.set_scale(0.6, 0.1, 0.18);
        c->nod_bot_padrao_textura_2.set_pos(-0.2, 0.0, 0.6);
        c->botao_padrao_textura_2->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(c->botao_padrao_textura_2->get_click_event(MouseButton::one()), set_textura2, c); //fazer metodo   padra_textura_1_funcao

         // Botão da textura 3 para o jogador poder editar a cor dessa textura
        NodePath padrao_textura_3 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura3");
        padrao_textura_3.detach_node();
        c->botao_padrao_textura_3 = new PGButton("textura3");
        c->botao_padrao_textura_3->setup(padrao_textura_3);
        c->nod_bot_padrao_textura_3 = Simdunas::get_window()->get_aspect_2d().attach_new_node(c->botao_padrao_textura_3);
        c->nod_bot_padrao_textura_3.set_scale(0.6, 0.1, 0.18);
        c->nod_bot_padrao_textura_3.set_pos(0.4, 0.0, 0.6);
        c->botao_padrao_textura_3->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(c->botao_padrao_textura_3->get_click_event(MouseButton::one()), set_textura3, c); //fazer metodo   padra_textura_1_funcao

         // Botão da textura 4 para o jogador poder editar a cor dessa textura
        NodePath padrao_textura_4 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura4");
        padrao_textura_4.detach_node();
        c->botao_padrao_textura_4 = new PGButton("textura4");
        c->botao_padrao_textura_4->setup(padrao_textura_4);
        c->nod_bot_padrao_textura_4 = Simdunas::get_window()->get_aspect_2d().attach_new_node(c->botao_padrao_textura_4);
        c->nod_bot_padrao_textura_4.set_scale(0.6, 0.1, 0.18);
        c->nod_bot_padrao_textura_4.set_pos(1.0, 0.0, 0.6);
        c->botao_padrao_textura_4->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(c->botao_padrao_textura_4->get_click_event(MouseButton::one()), set_textura4, c); //fazer metodo   padra_textura_1_funcao



    c->Paleta_cores(c); //carrega a paleta de cores
    lagartoPersonalizado.show();  //mostra o lagarto personalizado

  //  nod_botao_voltar.show();
  //  button_np.show();
  //  showing_custom = true; //indica que a tela de personalizar lagarto está sendo exibida

}

void editorTexture::set_textura1(const Event*, void *data) {
    path_textura_original = "models/lizards/custom/young/teiu.jpg";
    path_mascara = "models/lizards/custom/young/teiu_mask.jpg";
     print_null(data);  // faz com que textura original = textura personalizada
}
void editorTexture::set_textura2(const Event*, void *data) {
    path_textura_original = "models/lizards/custom/young/eurolophosaurus.jpg";
    path_mascara = "models/lizards/custom/young/eurolophosaurus_mask.jpg";
     print_null(data); // faz com que textura original = textura personalizada
}
void editorTexture::set_textura3(const Event*, void *data) {
    path_textura_original = "models/lizards/custom/young/cnemidophorus.jpg";
    path_mascara = "models/lizards/custom/young/cnemidophorus_mask.jpg";
     print_null(data); // faz com que textura original = textura personalizada
}
void editorTexture::set_textura4(const Event*, void *data) {
    path_textura_original = "models/lizards/custom/young/tropidurus.jpg";
    path_mascara = "models/lizards/custom/young/tropidurus_mask.jpg";
    print_null(data); // faz com que textura original = textura personalizada
}



void editorTexture::Paleta_cores( void *data) {
   editorTexture * config = (editorTexture*) data;

   //linha 1
   //paleta vermelha
        config->botao_red = new PGButton("Red");
        config->botao_red->setup("");
        config->botao_red_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_red);
        config->botao_red_np.set_scale(0.1, 0.2, 0.1);
        config->botao_red_np.set_pos(-1.2, 0.0, 0.5);
        config->botao_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_red_np.set_color(0.69,0.64,0.61,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao_red->get_click_event(MouseButton::one()),  print_red2, config);


         //paleta verde
        config->botao_green = new PGButton("Green");
        config->botao_green->setup("");
        config->botao_green_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_green);
        config->botao_green_np.set_scale(0.1, 0.2, 0.1);
        config->botao_green_np.set_pos(-1.2, 0.0, 0.4);
        config->botao_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_green_np.set_color(0.4,0.49,0.46,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao_green->get_click_event(MouseButton::one()), print_green, config);


        //linha 2
         //paleta vermelha2
        config->botao_blue = new PGButton("red2");
        config->botao_blue->setup("");
        config->botao_blue_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_blue);
        config->botao_blue_np.set_scale(0.1, 0.2, 0.1);
        config->botao_blue_np.set_pos(-1.2, 0.0, 0.3);
        config->botao_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_blue_np.set_color(0.64,0.11,0.1,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao_blue->get_click_event(MouseButton::one()), print_red, config);


         //paleta branca
        config->botao_white = new PGButton("white");
        config->botao_white->setup("");
        config->botao_white_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_white);
        config->botao_white_np.set_scale(0.1, 0.2, 0.1);
        config->botao_white_np.set_pos(-1.2, 0.0, 0.2);
        config->botao_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_white_np.set_color(1,1,1,100,1);
        //evento ao clicar...
       Simdunas::get_evt_handler()->add_hook(config->botao_white->get_click_event(MouseButton::one()),print_white, config);

         //linha 3
         //paleta amarela
        config->botao_yellow = new PGButton("yellow");
        config->botao_yellow->setup("");
        config->botao_yellow_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_yellow);
        config->botao_yellow_np.set_scale(0.1, 0.2, 0.1);
        config->botao_yellow_np.set_pos(-1.2, 0.0, 0.1);
        config->botao_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_yellow_np.set_color(0.96,0.81,0.52,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao_yellow->get_click_event(MouseButton::one()), print_yellow, config);

         //paleta verde2
        config->botao_green2 = new PGButton("green2");
        config->botao_green2->setup("");
        config->botao_green2_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_green2);
        config->botao_green2_np.set_scale(0.1, 0.2, 0.1);
        config->botao_green2_np.set_pos(-1.2, 0.0, 0.0);
        config->botao_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_green2_np.set_color(0.23,0.39,0.32,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao_green2->get_click_event(MouseButton::one()), print_green2, config);

        //linha 4
         //paleta marrom
        config->botao_brown = new PGButton("brown");
        config->botao_brown->setup("");
        config->botao_brown_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_brown);
        config->botao_brown_np.set_scale(0.1, 0.2, 0.1);
        config->botao_brown_np.set_pos(-1.2, 0.0, -0.1);
        config->botao_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_brown_np.set_color(0.3,0.23,0.16,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao_brown->get_click_event(MouseButton::one()), print_brown, config);

         //paleta preto
        config->botao_black = new PGButton("black");
        config->botao_black->setup("");
        config->botao_black_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_black);
        config->botao_black_np.set_scale(0.1, 0.2, 0.1);
        config->botao_black_np.set_pos(-1.2, 0.0, -0.2);
        config->botao_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao_black_np.set_color(0.15,0.15,0.11,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao_black->get_click_event(MouseButton::one()), print_black, config);


                     // PALETA COLUNA 2

    //linha 1
   //paleta vermelha
        config->botao2_red = new PGButton("Red");
        config->botao2_red->setup("");
        config->botao2_red_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_red);
        config->botao2_red_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_red_np.set_pos(-1.05, 0.0, 0.5);
        config->botao2_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_red_np.set_color(0.69,0.64,0.61,100,1);
        //evento ao clicar...
         Simdunas::get_evt_handler()->add_hook(config->botao2_red->get_click_event(MouseButton::one()),  print2_red2, config);


         //paleta verde
        config->botao2_green = new PGButton("Green");
        config->botao2_green->setup("");
        config->botao2_green_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_green);
        config->botao2_green_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_green_np.set_pos(-1.05, 0.0, 0.4);
        config->botao2_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_green_np.set_color(0.4,0.49,0.46,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao2_green->get_click_event(MouseButton::one()), print2_green, config);


        //linha 2
         //paleta vermelha2
        config->botao2_blue = new PGButton("red2");
        config->botao2_blue->setup("");
        config->botao2_blue_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_blue);
        config->botao2_blue_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_blue_np.set_pos(-1.05, 0.0, 0.3);
        config->botao2_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_blue_np.set_color(0.64,0.11,0.1,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao2_blue->get_click_event(MouseButton::one()), print2_red, config);


         //paleta branca
        config->botao2_white = new PGButton("white");
        config->botao2_white->setup("");
        config->botao2_white_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_white);
        config->botao2_white_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_white_np.set_pos(-1.05, 0.0, 0.2);
        config->botao2_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_white_np.set_color(1,1,1,100,1);
        //evento ao clicar...
       Simdunas::get_evt_handler()->add_hook(config->botao2_white->get_click_event(MouseButton::one()),print2_white, config);

         //linha 3
         //paleta amarela
        config->botao2_yellow = new PGButton("yellow");
        config->botao2_yellow->setup("");
        config->botao2_yellow_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_yellow);
        config->botao2_yellow_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_yellow_np.set_pos(-1.05, 0.0, 0.1);
        config->botao2_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_yellow_np.set_color(0.96,0.81,0.52,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao2_yellow->get_click_event(MouseButton::one()), print2_yellow, config);

         //paleta verde2
        config->botao2_green2 = new PGButton("green2");
        config->botao2_green2->setup("");
        config->botao2_green2_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_green2);
        config->botao2_green2_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_green2_np.set_pos(-1.05, 0.0, 0.0);
        config->botao2_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_green2_np.set_color(0.23,0.39,0.32,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao2_green2->get_click_event(MouseButton::one()), print2_green2, config);

        //linha 4
         //paleta marrom
        config->botao2_brown = new PGButton("brown");
        config->botao2_brown->setup("");
        config->botao2_brown_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_brown);
        config->botao2_brown_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_brown_np.set_pos(-1.05, 0.0, -0.1);
        config->botao2_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_brown_np.set_color(0.3,0.23,0.16,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao2_brown->get_click_event(MouseButton::one()), print2_brown, config);

         //paleta preto
        config->botao2_black = new PGButton("black");
        config->botao2_black->setup("");
        config->botao2_black_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao2_black);
        config->botao2_black_np.set_scale(0.1, 0.2, 0.1);
        config->botao2_black_np.set_pos(-1.05, 0.0, -0.2);
        config->botao2_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao2_black_np.set_color(0.15,0.15,0.11,100,1);

        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao2_black->get_click_event(MouseButton::one()), print2_black, config);
}


//métodos que pintam a area cinza da mascara
void editorTexture::print_green(const Event*, void *data) {

    RGBColord cor = RGBColord(0.4,0.49,0.46);
    change_texture(data, cor,1);
    mudar_marcador(-1.2, 0.0, 0.4, data);
}
void editorTexture::print_green2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    change_texture(data, cor, 1);
    mudar_marcador(-1.2, 0.0, 0.0, data);
}
void editorTexture::print_red2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    change_texture(data, cor,1);
    mudar_marcador(-1.2, 0.0, 0.5, data);
}
void editorTexture::print_red(const Event*, void *data) {
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    change_texture(data, cor, 1);
    mudar_marcador(-1.2, 0.0, 0.3, data);
}
void editorTexture::print_white(const Event*, void *data) {
    RGBColord cor = RGBColord(1,1,1);
    change_texture(data, cor,1);
    mudar_marcador(-1.2, 0.0, 0.2, data);
}
void editorTexture::print_brown(const Event*, void *data) {
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    change_texture(data, cor,1);
    mudar_marcador(-1.2, 0.0, -0.1, data);
}
void editorTexture::print_black(const Event*, void *data) {
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    change_texture(data, cor, 1);
    mudar_marcador(-1.2, 0.0, -0.2, data);
}
void editorTexture::print_yellow(const Event*, void *data) {
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    change_texture(data, cor, 1);
    mudar_marcador(-1.2, 0.0, 0.1, data); //posição que deverá ficar o marcador
}

//muda a posição do marcador da primeira coluna da paleta de cores
void editorTexture::mudar_marcador(float a,float b,float c,void *data){
 editorTexture * config = (editorTexture*) data;
 config->marcador_camada1.set_pos(a-0.005, b, c-0.005);
 config->marcador_camada1.show();
}

//muda a posição do marcador da segunda coluna da paleta de cores
void editorTexture::mudar_marcador2(float a,float b,float c,void *data){
 editorTexture * config = (editorTexture*) data;
 config->marcador_camada2.set_pos(a -0.005, b, c  -0.005);
 config->marcador_camada2.show();
}


//métodos que pintam a area branca da mascara
void editorTexture::print2_green(const Event*, void *data) {
    RGBColord cor = RGBColord(0.4,0.49,0.46);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, 0.4, data);
}
void editorTexture::print2_green2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, 0.0, data);
}
void editorTexture::print2_red2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, 0.5, data);
}
void editorTexture::print2_red(const Event*, void *data) {
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, 0.3, data);
}
void editorTexture::print2_white(const Event*, void *data) {
    RGBColord cor = RGBColord(1,1,1);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, 0.2, data);
}
void editorTexture::print2_brown(const Event*, void *data) {
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, -0.1, data);
}
void editorTexture::print2_black(const Event*, void *data) {
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, -0.2, data);
}
void editorTexture::print2_yellow(const Event*, void *data) {
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    change_texture(data, cor, 2);
     mudar_marcador2(-1.05, 0.0, 0.1, data);
}

//Esse método não faz nenhuma alteração na textura original. É utilizado quando o padrão de textura é alterado
void editorTexture::print_null(void *data) {
        editorTexture * config = (editorTexture*) data;
        //apaga os marcadores da paleta de cores
       config->marcador_camada1.hide();
       config->marcador_camada2.hide();
     // faz com que textura original = textura personalizada.
    RGBColord cor = RGBColord(0.0,0.0,0.0);
    change_texture(data, cor, 0);
}

void editorTexture::change_texture(void *data, RGBColord cor, int mask_x) {
    int print_mask = mask_x; //esse int representa a parte da mascara que o jogador deseja pintar (1 = cinza e 2 = branca)
   // Menu *config = (Menu*) data;
 /* Aqui começa o teste */
// RGBColord c = RGBColord(1,0,0);

    //string path = "models/lizards/custom/young/";
  //  nout << "Aqui começa o teste" << endl;
    PNMImage image = PNMImage(path_textura_original);   //textura original
    PNMImage mask = PNMImage(path_mascara);    //mascara da textura
    PNMImage custom = PNMImage(path_textura_personalizada);    //textura personalizada

    int x = image.get_x_size();  //tamanho da textura na horizontal
    int y = image.get_y_size();  //tamanho da textura na vertical

    PNMImage result_image = PNMImage(x, y);  //criando nova textura com o mesmo tamanho da original

    for(int i = 0; i < x; i++){  //percorre pixels na horizontal
    	for(int j = 0; j < y; j++){//percorre pixels na vertical
    		float bright = mask.get_bright(i, j); //pega o brilho da mascara a cada pixel

                if(bright > 0.1 && bright <= 0.85 && print_mask == 1){  //se for cinza claro
    			//RGBColord c = RGBColord(0, 0, 1);
    			result_image.set_xel(i, j, RGBColord(cor.get_x()*image.get_red(i, j),
											   cor.get_y()*image.get_green(i, j) ,
											   cor.get_z()*image.get_blue(i, j)));
    		}
                else if(bright > 0.85 && print_mask == 2){ //se for branco
                    result_image.set_xel(i, j, RGBColord(cor.get_x()*image.get_red(i, j),
											   cor.get_y()*image.get_green(i, j),
											   cor.get_z()*image.get_blue(i, j)));

                }
                else if(bright > 0.1 && bright <= 0.85 && print_mask == 2){ //matém a textura personalizada
    			result_image.set_xel(i, j, custom.get_xel(i, j));

    		}
                 else if(bright > 0.85 && print_mask == 1){//matém a textura personalizada
                     result_image.set_xel(i, j, custom.get_xel(i, j));
                 }
                 else{ //coloca pixels da textura original
                     result_image.set_xel(i, j, image.get_xel(i, j));
                 }
            }

        }
                //sobrescreve textura personalizada com o resultado da edição
                result_image.write(path_textura_personalizada);
                swap_texture(data); //faz a mudança da textura

}

void editorTexture::swap_texture(void *data) {//recarregar a textura personalizada do lagarto
                editorTexture *config = (editorTexture*) data;
                //troca textura, entre 2 texturas diferentes
               PT(TextureStage) ts = config->lagartoPersonalizado.find_all_texture_stages().get_texture_stage(0);
		ts->set_mode(TextureStage::M_modulate);

		PT(Texture) t = TexturePool::load_texture(path_textura_personalizada);
		config->lagartoPersonalizado.set_texture(ts, t, 1);
                config->lagartoPersonalizado.get_texture()->reload();

            //     nout << "Aqui termina o teste" << endl;
}



