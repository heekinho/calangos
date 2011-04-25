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
#include "guiManager.h"
#include "textureStageCollection.h"
#include "screenManager.h"
#include "screen.h"
#include "modelRepository.h"
#include "calangosMenuManager.h"
#include "menu.h"


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
	np_btn_back.hide();
    npJogar.hide();
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
      
}

void editorTextureScreen::unload(){
    hide_tela_personalizado();
    lagartoPersonalizado.remove_node();
    npJogar.remove_node();
    np_btn_back.remove_node();
    btn_back = NULL;
}

void editorTextureScreen::show_tela_personalizar() {
	    //botões jogar e voltar ao menu anterior
	default_button_config(buttonJogar, npJogar, " Jogar ", LVecBase3f(0, 0, -0.8), jogo_action);
	npJogar.show();

	configure_default_back_button(((CalangosMenuManager*) manager.p())->get_character_editor());
    //carregando o quadro (marcador) de cor selecionada da primeira coluna da paleta de cores

        marcador_camada1 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        marcador_camada1.set_scale(0.17, 1.0, 0.17);
        marcador_camada1.hide();
      //  c->marcador_camada1.set_pos(4.0, 0.0, -4.7);

        marcador_camada2 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        marcador_camada2.set_scale(0.17, 1.0, 0.17);
        marcador_camada2.hide();
     //   c->marcador_camada2.set_pos(4.0, 0.0, -4.7);

        marcador_camada3 = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/quadro");
        marcador_camada3.set_scale(0.17, 1.0, 0.17);
        marcador_camada3.hide();
        
    ///carregando titulo do editor de cores
        title_color = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/editorcores");
        title_color.set_scale(1, 2 ,0.4);
        title_color.set_pos(0, 0, 0.8);
        title_color.show();



	default_button_config(botao_padrao_textura_1, nod_bot_padrao_textura_1, "Textura 1", -0.9, set_textura1);
	nod_bot_padrao_textura_1.set_scale(0.8, 1.0, 0.8);
        nod_bot_padrao_textura_1.set_pos(-0.8, 0.0, 0.6);
	nod_bot_padrao_textura_1.set_alpha_scale(0.5);
	
	default_button_config(botao_padrao_textura_2, nod_bot_padrao_textura_2, "Textura 2", -0.9, set_textura2);
	nod_bot_padrao_textura_2.set_scale(0.8, 1.0, 0.8);
        nod_bot_padrao_textura_2.set_pos(-0.2, 0.0, 0.6);
	nod_bot_padrao_textura_2.set_alpha_scale(0.5);

	default_button_config(botao_padrao_textura_3, nod_bot_padrao_textura_3, "Textura 3", -0.9, set_textura3);
	nod_bot_padrao_textura_3.set_scale(0.8, 1.0, 0.8);
        nod_bot_padrao_textura_3.set_pos(0.4, 0.0, 0.6);
	nod_bot_padrao_textura_3.set_alpha_scale(0.5);

	default_button_config(botao_padrao_textura_4, nod_bot_padrao_textura_4, "Textura 4", -0.9, set_textura4);
	nod_bot_padrao_textura_4.set_scale(0.8, 1.0, 0.8);
        nod_bot_padrao_textura_4.set_pos(1.0, 0.0, 0.6);
	nod_bot_padrao_textura_4.set_alpha_scale(0.5);

        set_textura1();  //coloca uma textura incial ao lagarto
	lagartoPersonalizado.show();  //mostra o lagarto personalizado
	
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

void editorTextureScreen::set_textura1() {
    marca_textura(1);
    hide_paleta_cores();
    Paleta_cores(2);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/teiu.jpg");
    mascara = PNMImage("models/lizards/custom/young/teiu_mask.jpg");
    print_standard();
}
void editorTextureScreen::set_textura2() {
  
     marca_textura(2);
     hide_paleta_cores();
     Paleta_cores(3);  //o numero é a quantidade de colunas que terá a paleta de cores
     textura_original = PNMImage("models/lizards/custom/young/eurolophosaurus.jpg");
     mascara = PNMImage("models/lizards/custom/young/eurolophosaurus_mask.jpg");
     print_standard();
}
void editorTextureScreen::set_textura3() {
     
     marca_textura(3);
     hide_paleta_cores();
     Paleta_cores(1);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/cnemidophorus.jpg");
    mascara = PNMImage("models/lizards/custom/young/cnemidophorus_mask.jpg");
    print_standard();
}
void editorTextureScreen::set_textura4() {
     
     marca_textura(4);
     hide_paleta_cores();
     Paleta_cores(1);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/tropidurus.jpg");
    mascara = PNMImage("models/lizards/custom/young/tropidurus_mask.jpg");
    print_standard();
}



void editorTextureScreen::Paleta_cores( int  qtde_coluna) {

   //linha 1
   //paleta vermelha
        botao_red = new PGButton("Red");
        botao_red->setup("");
        botao_red_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_red);
        botao_red_np.set_scale(0.1, 0.2, 0.1);
        botao_red_np.set_pos(-1.2, 0.0, 0.5);
        botao_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_red_np.set_color(0.69,0.64,0.61,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao_red->get_click_event(MouseButton::one()),  print_red2, this);


         //paleta verde
        botao_green = new PGButton("Green");
        botao_green->setup("");
        botao_green_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_green);
        botao_green_np.set_scale(0.1, 0.2, 0.1);
        botao_green_np.set_pos(-1.2, 0.0, 0.4);
        botao_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_green_np.set_color(0.4,0.49,0.46,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao_green->get_click_event(MouseButton::one()), print_green, this);


        //linha 2
         //paleta vermelha2
        botao_blue = new PGButton("red2");
        botao_blue->setup("");
        botao_blue_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_blue);
        botao_blue_np.set_scale(0.1, 0.2, 0.1);
        botao_blue_np.set_pos(-1.2, 0.0, 0.3);
        botao_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_blue_np.set_color(0.64,0.11,0.1,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao_blue->get_click_event(MouseButton::one()), print_red, this);


         //paleta branca
        botao_white = new PGButton("white");
        botao_white->setup("");
        botao_white_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_white);
        botao_white_np.set_scale(0.1, 0.2, 0.1);
        botao_white_np.set_pos(-1.2, 0.0, 0.2);
        botao_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_white_np.set_color(1,1,1,100,1);
        //evento ao clicar...
       Simdunas::get_evt_handler()->add_hook(botao_white->get_click_event(MouseButton::one()),print_white, this);

         //linha 3
         //paleta amarela
        botao_yellow = new PGButton("yellow");
        botao_yellow->setup("");
        botao_yellow_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_yellow);
	botao_yellow_np.set_scale(0.1, 0.2, 0.1);
        botao_yellow_np.set_pos(-1.2, 0.0, 0.1);
        botao_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_yellow_np.set_color(0.96,0.81,0.52,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao_yellow->get_click_event(MouseButton::one()), print_yellow,this);

         //paleta verde2
        botao_green2 = new PGButton("green2");
        botao_green2->setup("");
        botao_green2_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_green2);
        botao_green2_np.set_scale(0.1, 0.2, 0.1);
        botao_green2_np.set_pos(-1.2, 0.0, 0.0);
        botao_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_green2_np.set_color(0.23,0.39,0.32,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao_green2->get_click_event(MouseButton::one()), print_green2, this);

        //linha 4
         //paleta marrom
        botao_brown = new PGButton("brown");
        botao_brown->setup("");
        botao_brown_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_brown);
        botao_brown_np.set_scale(0.1, 0.2, 0.1);
        botao_brown_np.set_pos(-1.2, 0.0, -0.1);
        botao_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_brown_np.set_color(0.3,0.23,0.16,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao_brown->get_click_event(MouseButton::one()), print_brown, this);

         //paleta preto
        botao_black = new PGButton("black");
        botao_black->setup("");
        botao_black_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_black);
        botao_black_np.set_scale(0.1, 0.2, 0.1);
        botao_black_np.set_pos(-1.2, 0.0, -0.2);
        botao_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_black_np.set_color(0.15,0.15,0.11,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao_black->get_click_event(MouseButton::one()), print_black, this);


                     // PALETA COLUNA 2
        if(qtde_coluna > 1){
    //linha 1
   //paleta vermelha
        botao2_red = new PGButton("Red");
        botao2_red->setup("");
        botao2_red_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_red);
        botao2_red_np.set_scale(0.1, 0.2, 0.1);
        botao2_red_np.set_pos(-1.05, 0.0, 0.5);
        botao2_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_red_np.set_color(0.69,0.64,0.61,100,1);
        //evento ao clicar...
         Simdunas::get_evt_handler()->add_hook(botao2_red->get_click_event(MouseButton::one()),  print2_red2, this);


         //paleta verde
        botao2_green = new PGButton("Green");
        botao2_green->setup("");
        botao2_green_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_green);
        botao2_green_np.set_scale(0.1, 0.2, 0.1);
        botao2_green_np.set_pos(-1.05, 0.0, 0.4);
        botao2_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_green_np.set_color(0.4,0.49,0.46,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao2_green->get_click_event(MouseButton::one()), print2_green, this);


        //linha 2
         //paleta vermelha2
        botao2_blue = new PGButton("red2");
        botao2_blue->setup("");
        botao2_blue_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_blue);
        botao2_blue_np.set_scale(0.1, 0.2, 0.1);
        botao2_blue_np.set_pos(-1.05, 0.0, 0.3);
        botao2_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_blue_np.set_color(0.64,0.11,0.1,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao2_blue->get_click_event(MouseButton::one()), print2_red, this);


         //paleta branca
        botao2_white = new PGButton("white");
        botao2_white->setup("");
        botao2_white_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_white);
        botao2_white_np.set_scale(0.1, 0.2, 0.1);
        botao2_white_np.set_pos(-1.05, 0.0, 0.2);
        botao2_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_white_np.set_color(1,1,1,100,1);
        //evento ao clicar...
       Simdunas::get_evt_handler()->add_hook(botao2_white->get_click_event(MouseButton::one()),print2_white, this);

         //linha 3
         //paleta amarela
        botao2_yellow = new PGButton("yellow");
        botao2_yellow->setup("");
        botao2_yellow_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_yellow);
        botao2_yellow_np.set_scale(0.1, 0.2, 0.1);
        botao2_yellow_np.set_pos(-1.05, 0.0, 0.1);
        botao2_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_yellow_np.set_color(0.96,0.81,0.52,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao2_yellow->get_click_event(MouseButton::one()), print2_yellow, this);

         //paleta verde2
        botao2_green2 = new PGButton("green2");
        botao2_green2->setup("");
        botao2_green2_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_green2);
        botao2_green2_np.set_scale(0.1, 0.2, 0.1);
        botao2_green2_np.set_pos(-1.05, 0.0, 0.0);
        botao2_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_green2_np.set_color(0.23,0.39,0.32,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao2_green2->get_click_event(MouseButton::one()), print2_green2, this);

        //linha 4
         //paleta marrom
        botao2_brown = new PGButton("brown");
        botao2_brown->setup("");
        botao2_brown_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_brown);
        botao2_brown_np.set_scale(0.1, 0.2, 0.1);
        botao2_brown_np.set_pos(-1.05, 0.0, -0.1);
        botao2_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_brown_np.set_color(0.3,0.23,0.16,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao2_brown->get_click_event(MouseButton::one()), print2_brown, this);

         //paleta preto
        botao2_black = new PGButton("black");
        botao2_black->setup("");
        botao2_black_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao2_black);
        botao2_black_np.set_scale(0.1, 0.2, 0.1);
        botao2_black_np.set_pos(-1.05, 0.0, -0.2);
        botao2_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_black_np.set_color(0.15,0.15,0.11,100,1);

        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao2_black->get_click_event(MouseButton::one()), print2_black, this);
}//fim do if(qtde_coluna > 1)


        //botões da coluna 3
        if(qtde_coluna > 2){
             //paleta vermelha
        botao3_red = new PGButton("Red");
        botao3_red->setup("");
        botao3_red_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_red);
        botao3_red_np.set_scale(0.1, 0.2, 0.1);
        botao3_red_np.set_pos(-0.9, 0.0, 0.5);
        botao3_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_red_np.set_color(0.69,0.64,0.61,100,1);
        //evento ao clicar...
         Simdunas::get_evt_handler()->add_hook(botao3_red->get_click_event(MouseButton::one()),  print3_red2, this);


         //paleta verde
        botao3_green = new PGButton("Green");
        botao3_green->setup("");
        botao3_green_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_green);
        botao3_green_np.set_scale(0.1, 0.2, 0.1);
        botao3_green_np.set_pos(-0.9, 0.0, 0.4);
        botao3_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_green_np.set_color(0.4,0.49,0.46,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao3_green->get_click_event(MouseButton::one()), print3_green, this);


        //linha 2
         //paleta vermelha2
        botao3_blue = new PGButton("red2");
        botao3_blue->setup("");
        botao3_blue_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_blue);
        botao3_blue_np.set_scale(0.1, 0.2, 0.1);
        botao3_blue_np.set_pos(-0.9, 0.0, 0.3);
        botao3_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_blue_np.set_color(0.64,0.11,0.1,100,1);
        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao3_blue->get_click_event(MouseButton::one()), print3_red, this);


         //paleta branca
        botao3_white = new PGButton("white");
        botao3_white->setup("");
        botao3_white_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_white);
        botao3_white_np.set_scale(0.1, 0.2, 0.1);
        botao3_white_np.set_pos(-0.9, 0.0, 0.2);
        botao3_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_white_np.set_color(1,1,1,100,1);
        //evento ao clicar...
       Simdunas::get_evt_handler()->add_hook(botao3_white->get_click_event(MouseButton::one()),print3_white, this);

         //linha 3
         //paleta amarela
        botao3_yellow = new PGButton("yellow");
        botao3_yellow->setup("");
        botao3_yellow_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_yellow);
        botao3_yellow_np.set_scale(0.1, 0.2, 0.1);
        botao3_yellow_np.set_pos(-0.9, 0.0, 0.1);
        botao3_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_yellow_np.set_color(0.96,0.81,0.52,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao3_yellow->get_click_event(MouseButton::one()), print3_yellow, this);

         //paleta verde2
        botao3_green2 = new PGButton("green2");
        botao3_green2->setup("");
        botao3_green2_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_green2);
        botao3_green2_np.set_scale(0.1, 0.2, 0.1);
        botao3_green2_np.set_pos(-0.9, 0.0, 0.0);
        botao3_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_green2_np.set_color(0.23,0.39,0.32,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao3_green2->get_click_event(MouseButton::one()), print3_green2, this);

        //linha 4
         //paleta marrom
        botao3_brown = new PGButton("brown");
        botao3_brown->setup("");
        botao3_brown_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_brown);
        botao3_brown_np.set_scale(0.1, 0.2, 0.1);
        botao3_brown_np.set_pos(-0.9, 0.0, -0.1);
        botao3_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_brown_np.set_color(0.3,0.23,0.16,100,1);
        //evento ao clicar...

        Simdunas::get_evt_handler()->add_hook(botao3_brown->get_click_event(MouseButton::one()), print3_brown, this);

         //paleta preto
        botao3_black = new PGButton("black");
        botao3_black->setup("");
        botao3_black_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao3_black);
        botao3_black_np.set_scale(0.1, 0.2, 0.1);
        botao3_black_np.set_pos(-0.9, 0.0, -0.2);
        botao3_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_black_np.set_color(0.15,0.15,0.11,100,1);

        //evento ao clicar...
        Simdunas::get_evt_handler()->add_hook(botao3_black->get_click_event(MouseButton::one()), print3_black, this);
            
        }
}

//métodos que pintam a area branca da mascara
void editorTextureScreen::print_green(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.4,0.49,0.46);
    config->change_texture(cor,2);
    config->mudar_marcador(-1.2, 0.0, 0.4);
}
void editorTextureScreen::print_green2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    config->change_texture( cor, 2);
    config->mudar_marcador(-1.2, 0.0, 0.0);
}
void editorTextureScreen::print_red2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    config->change_texture( cor,2);
    config->mudar_marcador(-1.2, 0.0, 0.5);
}
void editorTextureScreen::print_red(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    config->change_texture( cor, 2);
    config->mudar_marcador(-1.2, 0.0, 0.3);
}
void editorTextureScreen::print_white(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(1,1,1);
    config->change_texture( cor,2);
    config->mudar_marcador(-1.2, 0.0, 0.2);
}
void editorTextureScreen::print_brown(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    config->change_texture( cor,2);
    config->mudar_marcador(-1.2, 0.0, -0.1);
}
void editorTextureScreen::print_black(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    config->change_texture( cor, 2);
    config->mudar_marcador(-1.2, 0.0, -0.2);
}
void editorTextureScreen::print_yellow(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    config->change_texture(cor, 2);
    config->mudar_marcador(-1.2, 0.0, 0.1); //posição que deverá ficar o marcador
}

//métodos que pintam a area cinza da mascara
void editorTextureScreen::print2_green(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.4,0.49,0.46);
    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.4);
}
void editorTextureScreen::print2_green2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.0);
}
void editorTextureScreen::print2_red2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.5);
}
void editorTextureScreen::print2_red(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.3);
}
void editorTextureScreen::print2_white(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(1,1,1);
    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.2);
}
void editorTextureScreen::print2_brown(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, -0.1);
}
void editorTextureScreen::print2_black(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, -0.2);
}
void editorTextureScreen::print2_yellow(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.1);
}

//métodos que pintam a area cinza escuro da mascara (botões da terceira coluna da palata de cores)
void editorTextureScreen::print3_green(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.4,0.49,0.46);
    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.4);
}
void editorTextureScreen::print3_green2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.23,0.39,0.32);
    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.0);
}
void editorTextureScreen::print3_red2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.69,0.64,0.61);
    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.5);
}
void editorTextureScreen::print3_red(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.64,0.11,0.1);
    config->change_texture( cor, 3);
     config->mudar_marcador3(-0.9, 0.0, 0.3);
}
void editorTextureScreen::print3_white(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(1,1,1);
    config->change_texture( cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.2);
}
void editorTextureScreen::print3_brown(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.3,0.23,0.16);
    config->change_texture( cor, 3);
    config->mudar_marcador3(-0.9, 0.0, -0.1);
}
void editorTextureScreen::print3_black(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.15,0.15,0.11);
    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, -0.2);
}
void editorTextureScreen::print3_yellow(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    RGBColord cor = RGBColord(0.96,0.81,0.52);
    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.1);
}

//Esse método coloca uma cor padrão (verde) na textura. É utilizado quando o padrão de textura é alterado
void editorTextureScreen::print_standard() {
       
        //apaga os marcadores da paleta de cores
       marcador_camada1.hide();
       marcador_camada2.hide();
       marcador_camada3.hide();
	RGBColord cor = RGBColord(0.23,0.39,0.32);//forma a cor verde
	change_texture(cor, 0); //pinta toda a textura inicialmente de verde
}

//muda a posição do marcador da primeira coluna da paleta de cores
void editorTextureScreen::mudar_marcador(float a,float b,float c){
 marcador_camada1.set_pos(a-0.005, b, c-0.005);
 marcador_camada1.show();
}

//muda a posição do marcador da segunda coluna da paleta de cores
void editorTextureScreen::mudar_marcador2(float a,float b,float c){
 marcador_camada2.set_pos(a -0.005, b, c  -0.005);
 marcador_camada2.show();
}
void editorTextureScreen::mudar_marcador3(float a,float b,float c){
    marcador_camada3.set_pos(a -0.005, b, c  -0.005);
    marcador_camada3.show();
}

void editorTextureScreen::change_texture(RGBColord cor, int mask_x) {
   
  //  PNMImage image = PNMImage(path_textura_original);   //textura original
  //  PNMImage mask = PNMImage(path_mascara);    //mascara da textura
  //  PNMImage custom = PNMImage(path_textura_personalizada);    //textura personalizada

      //esse int mask_x representa a parte da mascara que o jogador deseja pintar (1 = cinza,
      //2 = branca, 3 = cinza escuro, 0 = todas (branco, cinza e cinza escuro)
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
                textura_personalizada = result_image;
                swap_texture(); //faz a mudança da textura

          /*      sobrescreve textura personalizada com o resultado da edição (EM ARQUIVO)
                 result_image.write(path_textura_personalizada);
                swap_texture(data); //faz a mudança da textura

               editorTexture *config = (editorTexture*) data;
               troca textura, entre 2 texturas diferentes
               PT(TextureStage) ts = config->lagartoPersonalizado.find_all_texture_stages().get_texture_stage(0);
                ts->set_mode(TextureStage::M_modulate);
               PT(Texture) t = new Texture();//instancia um Texture
                t->load(result_image); //cria um textura a partir de um PNMImage
		config->lagartoPersonalizado.set_texture(ts, t, 1);
                config->lagartoPersonalizado.get_texture()->reload();
        */
}

void editorTextureScreen::swap_texture() {//recarregar a textura personalizada do lagarto
                
                 //troca textura, entre 2 texturas diferentes
               PT(TextureStage) ts = lagartoPersonalizado.find_all_texture_stages().get_texture_stage(0);
		ts->set_mode(TextureStage::M_modulate);
                PT(Texture) t = new Texture();//instancia um Texture
                t->load(textura_personalizada); //cria um textura a partir de um PNMImage		
		lagartoPersonalizado.set_texture(ts, t, 1);
                lagartoPersonalizado.get_texture()->reload();
		ModelRepository::get_instance()->set_lagarto_personalizado(t);
}


void editorTextureScreen::jogo_action(){

	nout << "Carregando Jogo..." << endl;

	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());

	Simdunas::set_play_clicked(true);
}




