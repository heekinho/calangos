/* 
 * File:   editorTextureScreen.cxx
 * Author: tassalon
 * 
 * Created on 2 de Fevereiro de 2011, 15:44
 */

#include "editorTextureScreen.h"
#include "nodePath.h"
#include "textNode.h"
#include "mouseButton.h"
#include "pgSliderBar.h"
#include "fontPool.h"
#include "eventQueue.h"
#include "guiManager.h"
#include "textureStageCollection.h"
#include "screenManager.h"
#include "screen.h"
#include "modelRepository.h"
#include "calangosMenuManager.h"
#include "menu.h"



bool editorTextureScreen::instanceFlag = false;
editorTextureScreen* editorTextureScreen::single = NULL;

  PNMImage editorTextureScreen::textura_personalizada = PNMImage("models/lizards/custom/young/teiu.jpg");
  PNMImage editorTextureScreen::mascara = PNMImage("models/lizards/custom/young/teiu_mask.jpg");
  PNMImage editorTextureScreen::textura_original = PNMImage("models/lizards/custom/young/teiu.jpg");



editorTextureScreen::editorTextureScreen(PT(ScreenManager) manager) : Screen(manager){//construtor
    load();
}



editorTextureScreen::~editorTextureScreen() {
}



void editorTextureScreen::hide_paleta_cores(){ //remove todos os botões da paleta de cores
    if(!botao_red_np.is_empty()){
    botao_red_np.remove_node();
    botao_blue_np.remove_node();
    botao_green_np.remove_node();
    botao_yellow_np.remove_node();
    botao_white_np.remove_node();
    botao_black_np.remove_node();
    botao_brown_np.remove_node();
    botao_green2_np.remove_node();
    }
       if(!botao2_red_np.is_empty()){
    botao2_red_np.remove_node();
    botao2_blue_np.remove_node();
    botao2_green_np.remove_node();
    botao2_yellow_np.remove_node();
    botao2_white_np.remove_node();
    botao2_black_np.remove_node();
    botao2_brown_np.remove_node();
    botao2_green2_np.remove_node();
    }
       if(!botao3_red_np.is_empty()){
    botao3_red_np.remove_node();
    botao3_blue_np.remove_node();
    botao3_green_np.remove_node();
    botao3_yellow_np.remove_node();
    botao3_white_np.remove_node();
    botao3_black_np.remove_node();
    botao3_brown_np.remove_node();
    botao3_green2_np.remove_node();
    }
}

void editorTextureScreen::hide_tela_personalizado(){
    npJogar.hide();
    npVoltar.hide();
    lagartoPersonalizado.hide();
    marcador_camada1.remove_node();
    marcador_camada2.remove_node();
    marcador_camada3.remove_node();
    hide_paleta_cores();
    title_color.remove_node();
    nod_bot_padrao_textura_1.remove_node();
    nod_bot_padrao_textura_2.remove_node();
    nod_bot_padrao_textura_3.remove_node();
    nod_bot_padrao_textura_4.remove_node();
}

//implementa método abstrato herdados da classe screen 
void editorTextureScreen::hide(){
    hide_tela_personalizado();
}

void editorTextureScreen::show(){
   show_tela_personalizar();
}

void editorTextureScreen::load(){

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

    //botões jogar e voltar ao menu anterior
    default_button_config(buttonJogar, npJogar, " Jogar ", -0.8, jogo_action);
    npJogar.hide();
    
   default_button_config(buttonVoltar, npVoltar, "<< Voltar", -0.9, voltar_action);
   npVoltar.set_x(-0.9);
   npVoltar.hide();
   
}

void editorTextureScreen::unload(){
    hide_tela_personalizado();
    lagartoPersonalizado.remove_node();
    npJogar.remove_node();
    npVoltar.remove_node();
}

void editorTextureScreen::show_tela_personalizar() {
   
    //carregando o quadro (marcador) de cor selecionada da primeira coluna da paleta de cores

        marcador_camada1 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        marcador_camada1.set_scale(0.17, 0.0, 0.17);
        marcador_camada1.hide();
      //  c->marcador_camada1.set_pos(4.0, 0.0, -4.7);

        marcador_camada2 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        marcador_camada2.set_scale(0.17, 0.0, 0.17);
        marcador_camada2.hide();
     //   c->marcador_camada2.set_pos(4.0, 0.0, -4.7);

        marcador_camada3 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        marcador_camada3.set_scale(0.17, 0.0, 0.17);
        marcador_camada3.hide();
        
    ///carregando titulo do editor de cores
        title_color = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/editorcores");
        title_color.set_scale(1, 2 ,0.4);
        title_color.set_pos(0, 0, 0.8);
        title_color.show();



	default_button_config(botao_padrao_textura_1, nod_bot_padrao_textura_1, "Textura 1", -0.9, set_textura1);
	nod_bot_padrao_textura_1.set_scale(0.8, 0.0, 0.8);
        nod_bot_padrao_textura_1.set_pos(-0.8, 0.0, 0.6);
	nod_bot_padrao_textura_1.set_alpha_scale(0.5);
	
	default_button_config(botao_padrao_textura_2, nod_bot_padrao_textura_2, "Textura 2", -0.9, set_textura2);
	nod_bot_padrao_textura_2.set_scale(0.8, 0.0, 0.8);
        nod_bot_padrao_textura_2.set_pos(-0.2, 0.0, 0.6);
	nod_bot_padrao_textura_2.set_alpha_scale(0.5);

	default_button_config(botao_padrao_textura_3, nod_bot_padrao_textura_3, "Textura 3", -0.9, set_textura3);
	nod_bot_padrao_textura_3.set_scale(0.8, 0.0, 0.8);
        nod_bot_padrao_textura_3.set_pos(0.4, 0.0, 0.6);
	nod_bot_padrao_textura_3.set_alpha_scale(0.5);

	default_button_config(botao_padrao_textura_4, nod_bot_padrao_textura_4, "Textura 4", -0.9, set_textura4);
	nod_bot_padrao_textura_4.set_scale(0.8, 0.0, 0.8);
        nod_bot_padrao_textura_4.set_pos(1.0, 0.0, 0.6);
	nod_bot_padrao_textura_4.set_alpha_scale(0.5);

        // Botão da textura 1 para o jogador poder editar a cor dessa textura
	/*
        NodePath padrao_textura_1 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura1");
        padrao_textura_1.detach_node();
        botao_padrao_textura_1 = new PGButton("textura1");
        botao_padrao_textura_1->setup(padrao_textura_1);
        nod_bot_padrao_textura_1 = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_padrao_textura_1);
        nod_bot_padrao_textura_1.set_scale(0.6, 0.1, 0.18);
        nod_bot_padrao_textura_1.set_pos(-0.8, 0.0, 0.6);
	nod_bot_padrao_textura_1.set_color(0.5,0.5,0.5);
        botao_padrao_textura_1->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(botao_padrao_textura_1->get_click_event(MouseButton::one()), set_textura1, this); 
	
         // Botão da textura2 para o jogador poder editar a cor dessa textura
        NodePath padrao_textura_2 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura2");
        padrao_textura_2.detach_node();
        botao_padrao_textura_2 = new PGButton("textura2");
        botao_padrao_textura_2->setup(padrao_textura_2);
        nod_bot_padrao_textura_2 = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_padrao_textura_2);
        nod_bot_padrao_textura_2.set_scale(0.6, 0.1, 0.18);
        nod_bot_padrao_textura_2.set_pos(-0.2, 0.0, 0.6);
	nod_bot_padrao_textura_2.set_color(0.5,0.5,0.5);
        botao_padrao_textura_2->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(botao_padrao_textura_2->get_click_event(MouseButton::one()), set_textura2, this); 

         // Botão da textura 3 para o jogador poder editar a cor dessa textura
        NodePath padrao_textura_3 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura3");
        padrao_textura_3.detach_node();
        botao_padrao_textura_3 = new PGButton("textura3");
        botao_padrao_textura_3->setup(padrao_textura_3);
        nod_bot_padrao_textura_3 = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_padrao_textura_3);
        nod_bot_padrao_textura_3.set_scale(0.6, 0.1, 0.18);
        nod_bot_padrao_textura_3.set_pos(0.4, 0.0, 0.6);
	nod_bot_padrao_textura_3.set_color(0.5,0.5,0.5);
        botao_padrao_textura_3->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(botao_padrao_textura_3->get_click_event(MouseButton::one()), set_textura3, this);

         // Botão da textura 4 para o jogador poder editar a cor dessa textura
        NodePath padrao_textura_4 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/textura4");
        padrao_textura_4.detach_node();
        botao_padrao_textura_4 = new PGButton("textura4");
        botao_padrao_textura_4->setup(padrao_textura_4);
        nod_bot_padrao_textura_4 = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_padrao_textura_4);
        nod_bot_padrao_textura_4.set_scale(0.6, 0.1, 0.18);
        nod_bot_padrao_textura_4.set_pos(1.0, 0.0, 0.6);
	nod_bot_padrao_textura_4.set_color(0.5,0.5,0.5);
        botao_padrao_textura_4->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(botao_padrao_textura_4->get_click_event(MouseButton::one()), set_textura4, this);

	  */
	lagartoPersonalizado.show();  //mostra o lagarto personalizado
	npJogar.show();
	npVoltar.show();
}

void editorTextureScreen::marca_textura(int botao){
    nod_bot_padrao_textura_1.set_alpha_scale(0.5);
    nod_bot_padrao_textura_2.set_alpha_scale(0.5);
    nod_bot_padrao_textura_3.set_alpha_scale(0.5);
    nod_bot_padrao_textura_4.set_alpha_scale(0.5);
    if(botao ==1){
	nod_bot_padrao_textura_1.set_alpha_scale(1);
    }else if(botao ==2){
	nod_bot_padrao_textura_2.set_alpha_scale(1);
    }else if(botao ==3){
	nod_bot_padrao_textura_3.set_alpha_scale(1);
    }else if(botao ==4){
	nod_bot_padrao_textura_4.set_alpha_scale(1);
    }
}

void editorTextureScreen::set_textura1(/*const Event*, void *data*/) {
   // editorTextureScreen *c = (editorTextureScreen*) data;
    marca_textura(1);
    hide_paleta_cores();
    Paleta_cores(this, 2);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/teiu.jpg");
    mascara = PNMImage("models/lizards/custom/young/teiu_mask.jpg");
    print_standard(this);
}
void editorTextureScreen::set_textura2() {
  //   editorTextureScreen *c = (editorTextureScreen*) data;
     marca_textura(2);
     hide_paleta_cores();
     Paleta_cores(this, 3);  //o numero é a quantidade de colunas que terá a paleta de cores
     textura_original = PNMImage("models/lizards/custom/young/eurolophosaurus.jpg");
     mascara = PNMImage("models/lizards/custom/young/eurolophosaurus_mask.jpg");
     print_standard(this);
}
void editorTextureScreen::set_textura3() {
     //editorTextureScreen *c = (editorTextureScreen*) data;
     marca_textura(3);
     hide_paleta_cores();
     Paleta_cores(this, 1);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/cnemidophorus.jpg");
    mascara = PNMImage("models/lizards/custom/young/cnemidophorus_mask.jpg");
    print_standard(this);
}
void editorTextureScreen::set_textura4() {
     //editorTextureScreen *c = (editorTextureScreen*) data;
     marca_textura(4);
     hide_paleta_cores();
     Paleta_cores(this, 1);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/tropidurus.jpg");
    mascara = PNMImage("models/lizards/custom/young/tropidurus_mask.jpg");
    print_standard(this);
}



void editorTextureScreen::Paleta_cores( void *data, int  qtde_coluna) {
   editorTextureScreen * config = (editorTextureScreen*) data;

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
        if(qtde_coluna > 1){
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
}//fim do if(qtde_coluna > 1)


        //botões da coluna 3
        if(qtde_coluna > 2){
             //paleta vermelha
        config->botao3_red = new PGButton("Red");
        config->botao3_red->setup("");
        config->botao3_red_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_red);
        config->botao3_red_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_red_np.set_pos(-0.9, 0.0, 0.5);
        config->botao3_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_red_np.set_color(0.69,0.64,0.61,100,1);
        //evento ao clicar...
         Simdunas::get_evt_handler()->add_hook(config->botao3_red->get_click_event(MouseButton::one()),  print3_red2, config);


         //paleta verde
        config->botao3_green = new PGButton("Green");
        config->botao3_green->setup("");
        config->botao3_green_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_green);
        config->botao3_green_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_green_np.set_pos(-0.9, 0.0, 0.4);
        config->botao3_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_green_np.set_color(0.4,0.49,0.46,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao3_green->get_click_event(MouseButton::one()), print3_green, config);


        //linha 2
         //paleta vermelha2
        config->botao3_blue = new PGButton("red2");
        config->botao3_blue->setup("");
        config->botao3_blue_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_blue);
        config->botao3_blue_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_blue_np.set_pos(-0.9, 0.0, 0.3);
        config->botao3_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_blue_np.set_color(0.64,0.11,0.1,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao3_blue->get_click_event(MouseButton::one()), print3_red, config);


         //paleta branca
        config->botao3_white = new PGButton("white");
        config->botao3_white->setup("");
        config->botao3_white_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_white);
        config->botao3_white_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_white_np.set_pos(-0.9, 0.0, 0.2);
        config->botao3_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_white_np.set_color(1,1,1,100,1);
        //evento ao clicar...
       Simdunas::get_evt_handler()->add_hook(config->botao3_white->get_click_event(MouseButton::one()),print3_white, config);

         //linha 3
         //paleta amarela
        config->botao3_yellow = new PGButton("yellow");
        config->botao3_yellow->setup("");
        config->botao3_yellow_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_yellow);
        config->botao3_yellow_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_yellow_np.set_pos(-0.9, 0.0, 0.1);
        config->botao3_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_yellow_np.set_color(0.96,0.81,0.52,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao3_yellow->get_click_event(MouseButton::one()), print3_yellow, config);

         //paleta verde2
        config->botao3_green2 = new PGButton("green2");
        config->botao3_green2->setup("");
        config->botao3_green2_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_green2);
        config->botao3_green2_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_green2_np.set_pos(-0.9, 0.0, 0.0);
        config->botao3_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_green2_np.set_color(0.23,0.39,0.32,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao3_green2->get_click_event(MouseButton::one()), print3_green2, config);

        //linha 4
         //paleta marrom
        config->botao3_brown = new PGButton("brown");
        config->botao3_brown->setup("");
        config->botao3_brown_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_brown);
        config->botao3_brown_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_brown_np.set_pos(-0.9, 0.0, -0.1);
        config->botao3_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_brown_np.set_color(0.3,0.23,0.16,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(config->botao3_brown->get_click_event(MouseButton::one()), print3_brown, config);

         //paleta preto
        config->botao3_black = new PGButton("black");
        config->botao3_black->setup("");
        config->botao3_black_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao3_black);
        config->botao3_black_np.set_scale(0.1, 0.2, 0.1);
        config->botao3_black_np.set_pos(-0.9, 0.0, -0.2);
        config->botao3_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        config->botao3_black_np.set_color(0.15,0.15,0.11,100,1);

        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(config->botao3_black->get_click_event(MouseButton::one()), print3_black, config);
            
        }
}

//métodos que pintam a area branca da mascara
void editorTextureScreen::print_green(const Event*, void *data) {

    RGBColord cor = RGBColord(0.4,0.49,0.46);
    change_texture(data, cor,2);
    mudar_marcador(-1.2, 0.0, 0.4, data);
}
void editorTextureScreen::print_green2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    change_texture(data, cor, 2);
    mudar_marcador(-1.2, 0.0, 0.0, data);
}
void editorTextureScreen::print_red2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    change_texture(data, cor,2);
    mudar_marcador(-1.2, 0.0, 0.5, data);
}
void editorTextureScreen::print_red(const Event*, void *data) {
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    change_texture(data, cor, 2);
    mudar_marcador(-1.2, 0.0, 0.3, data);
}
void editorTextureScreen::print_white(const Event*, void *data) {
    RGBColord cor = RGBColord(1,1,1);
    change_texture(data, cor,2);
    mudar_marcador(-1.2, 0.0, 0.2, data);
}
void editorTextureScreen::print_brown(const Event*, void *data) {
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    change_texture(data, cor,2);
    mudar_marcador(-1.2, 0.0, -0.1, data);
}
void editorTextureScreen::print_black(const Event*, void *data) {
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    change_texture(data, cor, 2);
    mudar_marcador(-1.2, 0.0, -0.2, data);
}
void editorTextureScreen::print_yellow(const Event*, void *data) {
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    change_texture(data, cor, 2);
    mudar_marcador(-1.2, 0.0, 0.1, data); //posição que deverá ficar o marcador
}

//métodos que pintam a area cinza da mascara
void editorTextureScreen::print2_green(const Event*, void *data) {
    RGBColord cor = RGBColord(0.4,0.49,0.46);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, 0.4, data);
}
void editorTextureScreen::print2_green2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, 0.0, data);
}
void editorTextureScreen::print2_red2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, 0.5, data);
}
void editorTextureScreen::print2_red(const Event*, void *data) {
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, 0.3, data);
}
void editorTextureScreen::print2_white(const Event*, void *data) {
    RGBColord cor = RGBColord(1,1,1);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, 0.2, data);
}
void editorTextureScreen::print2_brown(const Event*, void *data) {
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, -0.1, data);
}
void editorTextureScreen::print2_black(const Event*, void *data) {
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, -0.2, data);
}
void editorTextureScreen::print2_yellow(const Event*, void *data) {
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    change_texture(data, cor, 1);
     mudar_marcador2(-1.05, 0.0, 0.1, data);
}

//métodos que pintam a area cinza escuro da mascara (botões da terceira coluna da palata de cores)
void editorTextureScreen::print3_green(const Event*, void *data) {
    RGBColord cor = RGBColord(0.4,0.49,0.46);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, 0.4, data);
}
void editorTextureScreen::print3_green2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, 0.0, data);
}
void editorTextureScreen::print3_red2(const Event*, void *data) {
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, 0.5, data);
}
void editorTextureScreen::print3_red(const Event*, void *data) {
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, 0.3, data);
}
void editorTextureScreen::print3_white(const Event*, void *data) {
    RGBColord cor = RGBColord(1,1,1);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, 0.2, data);
}
void editorTextureScreen::print3_brown(const Event*, void *data) {
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, -0.1, data);
}
void editorTextureScreen::print3_black(const Event*, void *data) {
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, -0.2, data);
}
void editorTextureScreen::print3_yellow(const Event*, void *data) {
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    change_texture(data, cor, 3);
     mudar_marcador3(-0.9, 0.0, 0.1, data);
}

//Esse método coloca uma cor padrão (vermelho) na textura. É utilizado quando o padrão de textura é alterado
void editorTextureScreen::print_standard(void *data) {
        editorTextureScreen * config = (editorTextureScreen*) data;
        //apaga os marcadores da paleta de cores
       config->marcador_camada1.hide();
       config->marcador_camada2.hide();
       config->marcador_camada3.hide();
    RGBColord cor = RGBColord(0.23,0.39,0.32);//forma a cor vermelha
    change_texture(data, cor, 0); //pinta toda a textura inicialmente de vermelha
}

//muda a posição do marcador da primeira coluna da paleta de cores
void editorTextureScreen::mudar_marcador(float a,float b,float c,void *data){
 editorTextureScreen * config = (editorTextureScreen*) data;
 config->marcador_camada1.set_pos(a-0.005, b, c-0.005);
 config->marcador_camada1.show();
}

//muda a posição do marcador da segunda coluna da paleta de cores
void editorTextureScreen::mudar_marcador2(float a,float b,float c,void *data){
 editorTextureScreen * config = (editorTextureScreen*) data;
 config->marcador_camada2.set_pos(a -0.005, b, c  -0.005);
 config->marcador_camada2.show();
}
void editorTextureScreen::mudar_marcador3(float a,float b,float c,void *data){
 editorTextureScreen * config = (editorTextureScreen*) data;
 config->marcador_camada3.set_pos(a -0.005, b, c  -0.005);
 config->marcador_camada3.show();
}

void editorTextureScreen::change_texture(void *data, RGBColord cor, int mask_x) {
   // Menu *config = (Menu*) data;
  //  PNMImage image = PNMImage(path_textura_original);   //textura original
  //  PNMImage mask = PNMImage(path_mascara);    //mascara da textura
  //  PNMImage custom = PNMImage(path_textura_personalizada);    //textura personalizada


      //esse int representa a parte da mascara que o jogador deseja pintar (1 = cinza,
      //2 = branca, 3 = cinza escuro, 0 = branco a cinza escuro)
    int print_mask = mask_x;

    PNMImage image = textura_original;
    PNMImage mask = mascara;
    PNMImage custom = textura_personalizada;

    int x = image.get_x_size();  //tamanho da textura na horizontal
    int y = image.get_y_size();  //tamanho da textura na vertical

    PNMImage result_image = PNMImage(x, y);  //criando nova textura com o mesmo tamanho da original

    for(int i = 0; i < x; i++){  //percorre pixels na horizontal
    	for(int j = 0; j < y; j++){//percorre pixels na vertical
    		float bright = mask.get_bright(i, j); //pega o brilho da mascara a cada pixel

                if(print_mask == 0){ //se for pra pintar todo o lagarto...
                    result_image.set_xel(i, j, RGBColord(cor.get_x()*image.get_red(i, j),
											   cor.get_y()*image.get_green(i, j) ,
											   cor.get_z()*image.get_blue(i, j)));
                }
               else if(bright > 0.6 && bright <= 0.85 && print_mask == 1){  //se for cinza claro
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
                else if(bright > 0.1 && bright <= 0.6 && print_mask == 3){ //se for cinza escuro
                    result_image.set_xel(i, j, RGBColord(cor.get_x()*image.get_red(i, j),
											   cor.get_y()*image.get_green(i, j),
											   cor.get_z()*image.get_blue(i, j)));

                }
                else if(bright > 0.6 && bright <= 0.85 && print_mask != 1){ //matém a textura personalizada
    			result_image.set_xel(i, j, custom.get_xel(i, j));

    		}
                 else if(bright > 0.85 && print_mask != 2){//matém a textura personalizada
                     result_image.set_xel(i, j, custom.get_xel(i, j));
                 }
                 else if(bright > 0.1 && bright <= 0.6 && print_mask != 3){//matém a textura personalizada
                     result_image.set_xel(i, j, custom.get_xel(i, j));
                 }
                 else{ //coloca pixels da textura original
                     result_image.set_xel(i, j, image.get_xel(i, j));
                 }
            }

        }
                //sobrescreve textura personalizada com o resultado da edição (EM ARQUIVO)
               //  result_image.write(path_textura_personalizada);
               // swap_texture(data); //faz a mudança da textura
                textura_personalizada = result_image;
                swap_texture(data); //faz a mudança da textura

         //       editorTexture *config = (editorTexture*) data;
                //troca textura, entre 2 texturas diferentes
              // PT(TextureStage) ts = config->lagartoPersonalizado.find_all_texture_stages().get_texture_stage(0);
	//	ts->set_mode(TextureStage::M_modulate);
         //       PT(Texture) t = new Texture();//instancia um Texture
          //      t->load(result_image); //cria um textura a partir de um PNMImage
//		config->lagartoPersonalizado.set_texture(ts, t, 1);
 //               config->lagartoPersonalizado.get_texture()->reload();
              
}

void editorTextureScreen::swap_texture(void *data) {//recarregar a textura personalizada do lagarto
                editorTextureScreen *config = (editorTextureScreen*) data;
                 //troca textura, entre 2 texturas diferentes
               PT(TextureStage) ts = config->lagartoPersonalizado.find_all_texture_stages().get_texture_stage(0);
		ts->set_mode(TextureStage::M_modulate);
                PT(Texture) t = new Texture();//instancia um Texture
                t->load(textura_personalizada); //cria um textura a partir de um PNMImage		
		config->lagartoPersonalizado.set_texture(ts, t, 1);
                config->lagartoPersonalizado.get_texture()->reload();
		ModelRepository::get_instance()->set_lagarto_personalizado(config->lagartoPersonalizado);
}

/*! Configura um botão dado os parametros para este menu */

void editorTextureScreen::default_button_config(PT(Button) button, NodePath &np,
		const string &text, float z, EventCallbackFunction *action) {

	PT(TextFont) font = manager->get_default_font();
	button = new Button(text + "-button", text, font);
	np = get_root().attach_new_node(button);
	np.set_z(z);

	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
	
}

void editorTextureScreen::jogo_action(){

	nout << "Carregando Jogo..." << endl;

	if (Menu::get_instance()->get_minuto_dia_virtual() == 0) {
		Menu::get_instance()->set_minuto_dia_virtual(TimeControl::virtualTime);
	}

	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());

	Simdunas::set_play_clicked(true);
}

void editorTextureScreen::voltar_action(){
	CalangosMenuManager* menu_manager = (CalangosMenuManager*) manager.p();
	menu_manager->open_screen(menu_manager->get_game_options_screen());
}




