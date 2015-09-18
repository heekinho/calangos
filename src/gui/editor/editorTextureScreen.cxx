/*
 * File:   editorTextureScreen.cxx
 * Author: tassalon
 *
 * Created on 2 de Fevereiro de 2011, 15:44
 */

#include "simdunas.h"
#include "session.h"

#include "editorTextureScreen.h"
#include "nodePath.h"
#include "player.h"
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



PNMImage editorTextureScreen::textura_personalizada = PNMImage("models/lizards/custom/young/teiu.jpg");
PNMImage editorTextureScreen::mascara = PNMImage("models/lizards/custom/young/teiu_mask.jpg");
PNMImage editorTextureScreen::textura_original = PNMImage("models/lizards/custom/young/teiu.jpg");


editorTextureScreen::editorTextureScreen(PT(ScreenManager) manager) : Screen(manager){
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
    np_lb_tela_cores.remove_node();
    //title_color.remove_node();
    nod_bot_padrao_textura_1.remove_node();
    nod_bot_padrao_textura_2.remove_node();
    nod_bot_padrao_textura_3.remove_node();
    nod_bot_padrao_textura_4.remove_node();
    //eu
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
           //eu

}

//implementa método abstrato herdados da classe screen
void editorTextureScreen::hide(){
    hide_tela_personalizado();
}

void editorTextureScreen::show(){
   show_tela_personalizar();
}

void editorTextureScreen::load(){

    lagartoPersonalizado = window->load_model(render, "models/lizards/custom/young/model");
    lagartoPersonalizado.set_scale(0.08, 0.08, 0.08);
    lagartoPersonalizado.set_pos(0, 35, -2);
    lagartoPersonalizado.set_h(45);
    lagartoPersonalizado.set_p(20);

    //		 Animação
    window->load_model(lagartoPersonalizado, "models/lizards/custom/young/walk");
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
	default_button_config(buttonJogar, npJogar, ConfigVariableString("msg-jogar1", " Jogar"), LVecBase3f(0, 0, -0.8), jogo_action);
	npJogar.show();
     
	configure_default_back_button(((CalangosMenuManager*) manager.p())->get_character_editor());

    //carregando o quadro (marcador) de cor selecionada da primeira coluna da paleta de cores
        marcador_camada1 = window->load_model(aspect2d, "models/buttons/quadro");
        marcador_camada1.set_scale(0.17, 1.0, 0.17);
        marcador_camada1.hide();
      //  c->marcador_camada1.set_pos(4.0, 0.0, -4.7);
       
        marcador_camada2 = window->load_model(aspect2d, "models/buttons/quadro");
        marcador_camada2.set_scale(0.17, 1.0, 0.17);
        marcador_camada2.hide();
     //   c->marcador_camada2.set_pos(4.0, 0.0, -4.7);

        marcador_camada3 = window->load_model(aspect2d, "models/buttons/quadro");
        marcador_camada3.set_scale(0.17, 1.0, 0.17);
        marcador_camada3.hide();

    ///carregando titulo do editor de cores
        //title_color = window->load_model(aspect2d, "models/buttons/editorcores");
        //title_color.set_scale(1, 2 ,0.4);
        //title_color.set_pos(0, 0, 0.8);
        //title_color.show();
        lb_tela_cores = new TextNode("lb_tela_cores");
        lb_tela_cores->set_text(ConfigVariableString("msg-telacores", "Editor de Cores"));
        lb_tela_cores->set_font(manager->get_default_font());
        np_lb_tela_cores = aspect2d.attach_new_node(lb_tela_cores);
        np_lb_tela_cores.set_pos(-0.5, 0, 0.8);
        np_lb_tela_cores.set_scale(0.2);
        np_lb_tela_cores.set_color(1, 1, 1, 1, 0);


	default_button_config(botao_padrao_textura_1, nod_bot_padrao_textura_1, ConfigVariableString("msg-textura1", "Textura 1"), -0.9, set_textura1);
	nod_bot_padrao_textura_1.set_scale(0.8, 1.0, 0.8);
        nod_bot_padrao_textura_1.set_pos(-0.8, 0.0, 0.6);
	nod_bot_padrao_textura_1.set_alpha_scale(0.5);

	default_button_config(botao_padrao_textura_2, nod_bot_padrao_textura_2, ConfigVariableString("msg-textura2", "Textura 2"), -0.9, set_textura2);
	nod_bot_padrao_textura_2.set_scale(0.8, 1.0, 0.8);
        nod_bot_padrao_textura_2.set_pos(-0.2, 0.0, 0.6);
	nod_bot_padrao_textura_2.set_alpha_scale(0.5);

	default_button_config(botao_padrao_textura_3, nod_bot_padrao_textura_3, ConfigVariableString("msg-textura3", "Textura 3"), -0.9, set_textura3);
	nod_bot_padrao_textura_3.set_scale(0.8, 1.0, 0.8);
        nod_bot_padrao_textura_3.set_pos(0.4, 0.0, 0.6);
	nod_bot_padrao_textura_3.set_alpha_scale(0.5);

	default_button_config(botao_padrao_textura_4, nod_bot_padrao_textura_4, ConfigVariableString("msg-textura3", "Textura 3"), -0.9, set_textura4);
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
    peso_lagarto_textura = 5;
    print_standard(2);
}
void editorTextureScreen::set_textura2() {

     marca_textura(2);
     hide_paleta_cores();
     Paleta_cores(3);  //o numero é a quantidade de colunas que terá a paleta de cores
     textura_original = PNMImage("models/lizards/custom/young/eurolophosaurus.jpg");
     mascara = PNMImage("models/lizards/custom/young/eurolophosaurus_mask.jpg");
     peso_lagarto_textura = 4;
     print_standard(3);
}
void editorTextureScreen::set_textura3() {

     marca_textura(3);
     hide_paleta_cores();
     Paleta_cores(1);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/cnemidophorus.jpg");
    mascara = PNMImage("models/lizards/custom/young/cnemidophorus_mask.jpg");
     peso_lagarto_textura = 3;
    print_standard(1); //o parâmetro é a quantidade de camadas da máscara para essa textura
}
void editorTextureScreen::set_textura4() {

     marca_textura(4);
     hide_paleta_cores();
     Paleta_cores(1);  //o numero é a quantidade de colunas que terá a paleta de cores
    textura_original = PNMImage("models/lizards/custom/young/tropidurus.jpg");
    mascara = PNMImage("models/lizards/custom/young/tropidurus_mask.jpg");
     peso_lagarto_textura= 3;
    print_standard(1);
}



void editorTextureScreen::Paleta_cores( int  qtde_coluna) {

 
   //linha 1
   //paleta vermelha
        botao_red = new PGButton("Red");
        botao_red->setup("");
        botao_red_np = aspect2d.attach_new_node(botao_red);
        botao_red_np.set_scale(0.1, 0.2, 0.1);
        botao_red_np.set_pos(-1.2, 0.0, 0.5);
        botao_red->set_frame(-0.4, 0.4, -0.4, 0.4);

        //botao_red_np.set_color(0.69,0.64,0.61,100,1);

        botao_red_np.set_color(0.64,0.11,0.1,100,1);
        //evento ao clicar...
        event_handler->add_hook(botao_red->get_click_event(MouseButton::one()),  print_red2, this);


         //paleta verde
        botao_green = new PGButton("Green");
        botao_green->setup("");
        botao_green_np = aspect2d.attach_new_node(botao_green);
        botao_green_np.set_scale(0.1, 0.2, 0.1);
        botao_green_np.set_pos(-1.2, 0.0, 0.4);
        botao_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_green_np.set_color(0.4,0.38,0.19,100,1);
        //evento ao clicar...
        event_handler->add_hook(botao_green->get_click_event(MouseButton::one()), print_green, this);


        //linha 2
         //paleta vermelha2
        botao_blue = new PGButton("blue");
        botao_blue->setup("");
        botao_blue_np = aspect2d.attach_new_node(botao_blue);
        botao_blue_np.set_scale(0.1, 0.2, 0.1);
        botao_blue_np.set_pos(-1.2, 0.0, 0.3);
        botao_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_blue_np.set_color(0.16,0.4,0.77,100,1);
        //evento ao clicar...
        event_handler->add_hook(botao_blue->get_click_event(MouseButton::one()), print_red, this);


         //paleta branca
        botao_white = new PGButton("white");
        botao_white->setup("");
        botao_white_np = aspect2d.attach_new_node(botao_white);
        botao_white_np.set_scale(0.1, 0.2, 0.1);
        botao_white_np.set_pos(-1.2, 0.0, 0.2);
        botao_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_white_np.set_color(1,1,1,100,1);
        //evento ao clicar...
       event_handler->add_hook(botao_white->get_click_event(MouseButton::one()),print_white, this);

         //linha 3
         //paleta amarela
        botao_yellow = new PGButton("yellow");
        botao_yellow->setup("");
        botao_yellow_np = aspect2d.attach_new_node(botao_yellow);
	botao_yellow_np.set_scale(0.1, 0.2, 0.1);
        botao_yellow_np.set_pos(-1.2, 0.0, 0.1);
        botao_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_yellow_np.set_color(0.96,0.81,0.52,100,1);
        //evento ao clicar...

        event_handler->add_hook(botao_yellow->get_click_event(MouseButton::one()), print_yellow,this);

         //paleta verde2
        botao_green2 = new PGButton("green2");
        botao_green2->setup("");
        botao_green2_np = aspect2d.attach_new_node(botao_green2);
        botao_green2_np.set_scale(0.1, 0.2, 0.1);
        botao_green2_np.set_pos(-1.2, 0.0, 0.0);
        botao_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        //botao_green2_np.set_color(0.23,0.39,0.32,100,1);
        botao_green2_np.set_color(0.013,0.37,0.18,100,1);
        //evento ao clicar...

        event_handler->add_hook(botao_green2->get_click_event(MouseButton::one()), print_green2, this);

        //linha 4
         //paleta marrom
        botao_brown = new PGButton("brown");
        botao_brown->setup("");
        botao_brown_np = aspect2d.attach_new_node(botao_brown);
        botao_brown_np.set_scale(0.1, 0.2, 0.1);
        botao_brown_np.set_pos(-1.2, 0.0, -0.1);
        botao_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_brown_np.set_color(0.43,0.26,0.10,100,1);
        //evento ao clicar...

        event_handler->add_hook(botao_brown->get_click_event(MouseButton::one()), print_brown, this);

         //paleta preto
        botao_black = new PGButton("black");
        botao_black->setup("");
        botao_black_np = aspect2d.attach_new_node(botao_black);
        botao_black_np.set_scale(0.1, 0.2, 0.1);
        botao_black_np.set_pos(-1.2, 0.0, -0.2);
        botao_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao_black_np.set_color(0.15,0.15,0.11,100,1);
        //evento ao clicar...

        event_handler->add_hook(botao_black->get_click_event(MouseButton::one()), print_black, this);


                     // PALETA COLUNA 2
        if(qtde_coluna > 1){
    //linha 1
   //paleta vermelha
        botao2_red = new PGButton("Red");
        botao2_red->setup("");
        botao2_red_np = aspect2d.attach_new_node(botao2_red);
        botao2_red_np.set_scale(0.1, 0.2, 0.1);
        botao2_red_np.set_pos(-1.05, 0.0, 0.5);
        botao2_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_red_np.set_color(botao_red_np.get_color(),1);
        //evento ao clicar...
         event_handler->add_hook(botao2_red->get_click_event(MouseButton::one()),  print2_red2, this);


         //paleta verde
        botao2_green = new PGButton("Green");
        botao2_green->setup("");
        botao2_green_np = aspect2d.attach_new_node(botao2_green);
        botao2_green_np.set_scale(0.1, 0.2, 0.1);
        botao2_green_np.set_pos(-1.05, 0.0, 0.4);
        botao2_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_green_np.set_color(botao_green_np.get_color(),1);
        //evento ao clicar...
        event_handler->add_hook(botao2_green->get_click_event(MouseButton::one()), print2_green, this);


        //linha 2
         //paleta vermelha2
        botao2_blue = new PGButton("red2");
        botao2_blue->setup("");
        botao2_blue_np = aspect2d.attach_new_node(botao2_blue);
        botao2_blue_np.set_scale(0.1, 0.2, 0.1);
        botao2_blue_np.set_pos(-1.05, 0.0, 0.3);
        botao2_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_blue_np.set_color(botao_blue_np.get_color(),1);
        //evento ao clicar...
        event_handler->add_hook(botao2_blue->get_click_event(MouseButton::one()), print2_red, this);


         //paleta branca
        botao2_white = new PGButton("white");
        botao2_white->setup("");
        botao2_white_np = aspect2d.attach_new_node(botao2_white);
        botao2_white_np.set_scale(0.1, 0.2, 0.1);
        botao2_white_np.set_pos(-1.05, 0.0, 0.2);
        botao2_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_white_np.set_color(botao_white_np.get_color(),1);
        //evento ao clicar...
       event_handler->add_hook(botao2_white->get_click_event(MouseButton::one()),print2_white, this);

         //linha 3
         //paleta amarela
        botao2_yellow = new PGButton("yellow");
        botao2_yellow->setup("");
        botao2_yellow_np = aspect2d.attach_new_node(botao2_yellow);
        botao2_yellow_np.set_scale(0.1, 0.2, 0.1);
        botao2_yellow_np.set_pos(-1.05, 0.0, 0.1);
        botao2_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_yellow_np.set_color(botao_yellow_np.get_color(),1);
        //evento ao clicar...

        event_handler->add_hook(botao2_yellow->get_click_event(MouseButton::one()), print2_yellow, this);

         //paleta verde2
        botao2_green2 = new PGButton("green2");
        botao2_green2->setup("");
        botao2_green2_np = aspect2d.attach_new_node(botao2_green2);
        botao2_green2_np.set_scale(0.1, 0.2, 0.1);
        botao2_green2_np.set_pos(-1.05, 0.0, 0.0);
        botao2_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_green2_np.set_color(botao_green2_np.get_color(),1);
        //evento ao clicar...

        event_handler->add_hook(botao2_green2->get_click_event(MouseButton::one()), print2_green2, this);

        //linha 4
         //paleta marrom
        botao2_brown = new PGButton("brown");
        botao2_brown->setup("");
        botao2_brown_np = aspect2d.attach_new_node(botao2_brown);
        botao2_brown_np.set_scale(0.1, 0.2, 0.1);
        botao2_brown_np.set_pos(-1.05, 0.0, -0.1);
        botao2_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_brown_np.set_color(botao_brown_np.get_color(),1);
        //evento ao clicar...

        event_handler->add_hook(botao2_brown->get_click_event(MouseButton::one()), print2_brown, this);

         //paleta preto
        botao2_black = new PGButton("black");
        botao2_black->setup("");
        botao2_black_np = aspect2d.attach_new_node(botao2_black);
        botao2_black_np.set_scale(0.1, 0.2, 0.1);
        botao2_black_np.set_pos(-1.05, 0.0, -0.2);
        botao2_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao2_black_np.set_color(botao_black_np.get_color(),1);

        //evento ao clicar...
        event_handler->add_hook(botao2_black->get_click_event(MouseButton::one()), print2_black, this);
}//fim do if(qtde_coluna > 1)


        //botões da coluna 3
        if(qtde_coluna > 2){
             //paleta vermelha
        botao3_red = new PGButton("Red");
        botao3_red->setup("");
        botao3_red_np = aspect2d.attach_new_node(botao3_red);
        botao3_red_np.set_scale(0.1, 0.2, 0.1);
        botao3_red_np.set_pos(-0.9, 0.0, 0.5);
        botao3_red->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_red_np.set_color(botao_red_np.get_color(),1);
        //evento ao clicar...
         event_handler->add_hook(botao3_red->get_click_event(MouseButton::one()),  print3_red2, this);


         //paleta verde
        botao3_green = new PGButton("Green");
        botao3_green->setup("");
        botao3_green_np = aspect2d.attach_new_node(botao3_green);
        botao3_green_np.set_scale(0.1, 0.2, 0.1);
        botao3_green_np.set_pos(-0.9, 0.0, 0.4);
        botao3_green->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_green_np.set_color(botao_green_np.get_color(),1);
        //evento ao clicar...
        event_handler->add_hook(botao3_green->get_click_event(MouseButton::one()), print3_green, this);


        //linha 2
         //paleta vermelha2
        botao3_blue = new PGButton("red2");
        botao3_blue->setup("");
        botao3_blue_np = aspect2d.attach_new_node(botao3_blue);
        botao3_blue_np.set_scale(0.1, 0.2, 0.1);
        botao3_blue_np.set_pos(-0.9, 0.0, 0.3);
        botao3_blue->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_blue_np.set_color(botao_blue_np.get_color(),1);
        //evento ao clicar...
        event_handler->add_hook(botao3_blue->get_click_event(MouseButton::one()), print3_red, this);


         //paleta branca
        botao3_white = new PGButton("white");
        botao3_white->setup("");
        botao3_white_np = aspect2d.attach_new_node(botao3_white);
        botao3_white_np.set_scale(0.1, 0.2, 0.1);
        botao3_white_np.set_pos(-0.9, 0.0, 0.2);
        botao3_white->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_white_np.set_color(botao_white_np.get_color(),1);
        //evento ao clicar...
       event_handler->add_hook(botao3_white->get_click_event(MouseButton::one()),print3_white, this);

         //linha 3
         //paleta amarela
        botao3_yellow = new PGButton("yellow");
        botao3_yellow->setup("");
        botao3_yellow_np = aspect2d.attach_new_node(botao3_yellow);
        botao3_yellow_np.set_scale(0.1, 0.2, 0.1);
        botao3_yellow_np.set_pos(-0.9, 0.0, 0.1);
        botao3_yellow->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_yellow_np.set_color(botao_yellow_np.get_color(),1);
        //evento ao clicar...

        event_handler->add_hook(botao3_yellow->get_click_event(MouseButton::one()), print3_yellow, this);

         //paleta verde2
        botao3_green2 = new PGButton("green2");
        botao3_green2->setup("");
        botao3_green2_np = aspect2d.attach_new_node(botao3_green2);
        botao3_green2_np.set_scale(0.1, 0.2, 0.1);
        botao3_green2_np.set_pos(-0.9, 0.0, 0.0);
        botao3_green2->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_green2_np.set_color(botao_green2_np.get_color(),1);
        //evento ao clicar...

        event_handler->add_hook(botao3_green2->get_click_event(MouseButton::one()), print3_green2, this);

        //linha 4
         //paleta marrom
        botao3_brown = new PGButton("brown");
        botao3_brown->setup("");
        botao3_brown_np = aspect2d.attach_new_node(botao3_brown);
        botao3_brown_np.set_scale(0.1, 0.2, 0.1);
        botao3_brown_np.set_pos(-0.9, 0.0, -0.1);
        botao3_brown->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_brown_np.set_color(botao_brown_np.get_color(),1);
        //evento ao clicar...

        event_handler->add_hook(botao3_brown->get_click_event(MouseButton::one()), print3_brown, this);

         //paleta preto
        botao3_black = new PGButton("black");
        botao3_black->setup("");
        botao3_black_np = aspect2d.attach_new_node(botao3_black);
        botao3_black_np.set_scale(0.1, 0.2, 0.1);
        botao3_black_np.set_pos(-0.9, 0.0, -0.2);
        botao3_black->set_frame(-0.4, 0.4, -0.4, 0.4);
        botao3_black_np.set_color(botao_black_np.get_color(),1);

        //evento ao clicar...
        event_handler->add_hook(botao3_black->get_click_event(MouseButton::one()), print3_black, this);

        }
}

//métodos que pintam a area branca da mascara
void editorTextureScreen::print_red2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    
    //LRGBColord cor = LRGBColord(0.31,0.556,0.58);
    LRGBColord cor = LRGBColord(config->botao_red_np.get_color().get_x(),config->botao_red_np.get_color().get_y(),config->botao_red_np.get_color().get_z());
    config->change_texture( cor,2);
    config->mudar_marcador(-1.2, 0.0, 0.5);
    //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 1;
    config->peso_cor1_sol = 0;
    config->peso_cor1_noite = 2;
    config->peso_cor1_sombra = 1;
}

void editorTextureScreen::print_green(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao_green_np.get_color().get_x(),config->botao_green_np.get_color().get_y(),config->botao_green_np.get_color().get_z());

    config->change_texture(cor,2);
    config->mudar_marcador(-1.2, 0.0, 0.4);
        //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 2;
    config->peso_cor1_sol = 1;
    config->peso_cor1_noite = 4;
    config->peso_cor1_sombra = 3;
}
void editorTextureScreen::print_red(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao_blue_np.get_color().get_x(),config->botao_blue_np.get_color().get_y(),config->botao_blue_np.get_color().get_z());

    config->change_texture( cor, 2);
    config->mudar_marcador(-1.2, 0.0, 0.3);
        //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 1;
    config->peso_cor1_sol = 0;
    config->peso_cor1_noite = 2;
    config->peso_cor1_sombra = 0;
}
void editorTextureScreen::print_white(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao_white_np.get_color().get_x(),config->botao_white_np.get_color().get_y(),config->botao_white_np.get_color().get_z());

    config->change_texture( cor,2);
    config->mudar_marcador(-1.2, 0.0, 0.2);
        //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 1;
    config->peso_cor1_sol = 2;
    config->peso_cor1_noite = 3;
    config->peso_cor1_sombra = 0;
}

void editorTextureScreen::print_yellow(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
       LRGBColord cor = LRGBColord(config->botao_yellow_np.get_color().get_x(),config->botao_yellow_np.get_color().get_y(),config->botao_yellow_np.get_color().get_z());

    config->change_texture(cor, 2);
    config->mudar_marcador(-1.2, 0.0, 0.1); //posição que deverá ficar o marcador
        //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 4;
    config->peso_cor1_sol = 1;
    config->peso_cor1_noite = 3;
    config->peso_cor1_sombra = 1;
}

void editorTextureScreen::print_green2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
     LRGBColord cor = LRGBColord(config->botao_green2_np.get_color().get_x(),config->botao_green2_np.get_color().get_y(),config->botao_green2_np.get_color().get_z());
    config->change_texture( cor, 2);
    config->mudar_marcador(-1.2, 0.0, 0.0);
        //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 4;
    config->peso_cor1_sol = 1;
    config->peso_cor1_noite = 3;
    config->peso_cor1_sombra = 2;
}

void editorTextureScreen::print_brown(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao_brown_np.get_color().get_x(),config->botao_brown_np.get_color().get_y(),config->botao_brown_np.get_color().get_z());

    config->change_texture( cor,2);
    config->mudar_marcador(-1.2, 0.0, -0.1);
        //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 2;
    config->peso_cor1_sol = 1;
    config->peso_cor1_noite = 4;
    config->peso_cor1_sombra = 2;
}
void editorTextureScreen::print_black(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;

    LRGBColord cor = LRGBColord(config->botao_black_np.get_color().get_x(),config->botao_black_np.get_color().get_y(),config->botao_black_np.get_color().get_z());

    config->change_texture( cor, 2);
    config->mudar_marcador(-1.2, 0.0, -0.2);
        //atribuindo pesos para camuflagem
    config->peso_cor1_folhagem = 3;
    config->peso_cor1_sol = 2;
    config->peso_cor1_noite = 5;
    config->peso_cor1_sombra = 4;
}


//métodos que pintam a area cinza da mascara
void editorTextureScreen::print2_red2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao2_red_np.get_color().get_x(),config->botao2_red_np.get_color().get_y(),config->botao2_red_np.get_color().get_z());
    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.5);
 //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 2;
    config->peso_cor2_sol = 0;
    config->peso_cor2_noite = 3;
    config->peso_cor2_sombra = 1;

}

void editorTextureScreen::print2_green(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
     LRGBColord cor = LRGBColord(config->botao2_green_np.get_color().get_x(),config->botao2_green_np.get_color().get_y(),config->botao2_green_np.get_color().get_z());

    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.4);
        //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 2;
    config->peso_cor2_sol = 1;
    config->peso_cor2_noite = 4;
    config->peso_cor2_sombra = 3;
}
void editorTextureScreen::print2_red(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
        LRGBColord cor = LRGBColord(config->botao2_blue_np.get_color().get_x(),config->botao2_blue_np.get_color().get_y(),config->botao2_blue_np.get_color().get_z());

    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.3);
     //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 1;
    config->peso_cor2_sol = 0;
    config->peso_cor2_noite = 2;
    config->peso_cor2_sombra = 0;
}
void editorTextureScreen::print2_white(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao2_white_np.get_color().get_x(),config->botao2_white_np.get_color().get_y(),config->botao2_white_np.get_color().get_z());
    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.2);
      //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 1;
    config->peso_cor2_sol = 2;
    config->peso_cor2_noite = 3;
    config->peso_cor2_sombra = 0;
}

void editorTextureScreen::print2_yellow(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
       LRGBColord cor = LRGBColord(config->botao2_yellow_np.get_color().get_x(),config->botao2_yellow_np.get_color().get_y(),config->botao2_yellow_np.get_color().get_z());

    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.1);
      //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 4;
    config->peso_cor2_sol = 1;
    config->peso_cor2_noite = 3;
    config->peso_cor2_sombra = 1;
}


void editorTextureScreen::print2_green2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao2_green2_np.get_color().get_x(),config->botao2_green2_np.get_color().get_y(),config->botao2_green2_np.get_color().get_z());

    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, 0.0);
        //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 4;
    config->peso_cor2_sol = 1;
    config->peso_cor2_noite = 3;
    config->peso_cor2_sombra = 2;
}


void editorTextureScreen::print2_brown(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao2_brown_np.get_color().get_x(),config->botao2_brown_np.get_color().get_y(),config->botao2_brown_np.get_color().get_z());

    config->change_texture(cor, 1);
    config->mudar_marcador2(-1.05, 0.0, -0.1);
       //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 2;
    config->peso_cor2_sol = 1;
    config->peso_cor2_noite = 4;
    config->peso_cor2_sombra = 2;
}
void editorTextureScreen::print2_black(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
        LRGBColord cor = LRGBColord(config->botao2_black_np.get_color().get_x(),config->botao2_black_np.get_color().get_y(),config->botao2_black_np.get_color().get_z());

    config->change_texture( cor, 1);
    config->mudar_marcador2(-1.05, 0.0, -0.2);
        //atribuindo pesos para camuflagem
    config->peso_cor2_folhagem = 3;
    config->peso_cor2_sol = 2;
    config->peso_cor2_noite = 5;
    config->peso_cor2_sombra = 4;
}


//métodos que pintam a area cinza escuro da mascara (botões da terceira coluna da palata de cores)
void editorTextureScreen::print3_red2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
        LRGBColord cor = LRGBColord(config->botao3_red_np.get_color().get_x(),config->botao3_red_np.get_color().get_y(),config->botao3_red_np.get_color().get_z());

    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.5);
    //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 2;
    config->peso_cor3_sol = 0;
    config->peso_cor3_noite = 3;
    config->peso_cor3_sombra = 1;
}

void editorTextureScreen::print3_green(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao3_green_np.get_color().get_x(),config->botao3_green_np.get_color().get_y(),config->botao3_green_np.get_color().get_z());
    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.4);
         //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 2;
    config->peso_cor3_sol = 1;
    config->peso_cor3_noite = 4;
    config->peso_cor3_sombra = 3;
}


void editorTextureScreen::print3_red(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao3_blue_np.get_color().get_x(),config->botao3_blue_np.get_color().get_y(),config->botao3_blue_np.get_color().get_z());

    config->change_texture( cor, 3);
     config->mudar_marcador3(-0.9, 0.0, 0.3);
      //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 1;
    config->peso_cor3_sol = 0;
    config->peso_cor3_noite = 2;
    config->peso_cor3_sombra = 0;
}
void editorTextureScreen::print3_white(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao3_white_np.get_color().get_x(),config->botao3_white_np.get_color().get_y(),config->botao3_white_np.get_color().get_z());

    config->change_texture( cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.2);
      //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 1;
    config->peso_cor3_sol = 2;
    config->peso_cor3_noite = 3;
    config->peso_cor3_sombra = 0;
}
void editorTextureScreen::print3_yellow(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
   LRGBColord cor = LRGBColord(config->botao3_yellow_np.get_color().get_x(),config->botao3_yellow_np.get_color().get_y(),config->botao3_yellow_np.get_color().get_z());

    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.1);
      //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 4;
    config->peso_cor3_sol = 1;
    config->peso_cor3_noite = 3;
    config->peso_cor3_sombra = 1;
}
void editorTextureScreen::print3_green2(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao3_green2_np.get_color().get_x(),config->botao3_green2_np.get_color().get_y(),config->botao3_green2_np.get_color().get_z());

    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, 0.0);
        //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 4;
    config->peso_cor3_sol = 1;
    config->peso_cor3_noite = 3;
    config->peso_cor3_sombra = 2;
}
void editorTextureScreen::print3_brown(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao3_brown_np.get_color().get_x(),config->botao3_brown_np.get_color().get_y(),config->botao3_brown_np.get_color().get_z());

    config->change_texture( cor, 3);
    config->mudar_marcador3(-0.9, 0.0, -0.1);
       //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 2;
    config->peso_cor3_sol = 1;
    config->peso_cor3_noite = 4;
    config->peso_cor3_sombra = 2;
}
void editorTextureScreen::print3_black(const Event*, void *data) {
    editorTextureScreen * config = (editorTextureScreen*) data;
    LRGBColord cor = LRGBColord(config->botao3_black_np.get_color().get_x(),config->botao3_black_np.get_color().get_y(),config->botao3_black_np.get_color().get_z());

    config->change_texture(cor, 3);
    config->mudar_marcador3(-0.9, 0.0, -0.2);
        //atribuindo pesos para camuflagem
    config->peso_cor3_folhagem = 3;
    config->peso_cor3_sol = 2;
    config->peso_cor3_noite = 5;
    config->peso_cor3_sombra = 4;
}


//Esse método coloca uma cor padrão (verde) na textura. É utilizado quando o padrão de textura é alterado
void editorTextureScreen::print_standard(int camadas) {
    
       mudar_marcador(-1.2, 0.0, 0.0);
       marcador_camada2.hide();
       marcador_camada3.hide();
	
       LRGBColord cor = LRGBColord(botao_green2_np.get_color().get_x(),botao_green2_np.get_color().get_y(),botao_green2_np.get_color().get_z());
	change_texture(cor, 0); //pinta toda a textura inicialmente de verde


	peso_cor2_folhagem = -1;
	peso_cor2_sol = -1;
	peso_cor2_noite = -1;
	peso_cor2_sombra = -1;

	peso_cor3_folhagem = -1;
	peso_cor3_sol = -1;
	peso_cor3_noite = -1;
	peso_cor3_sombra = -1;

	peso_cor1_folhagem = 4;
	peso_cor1_sol = 1;
	peso_cor1_noite = 3;
	peso_cor1_sombra = 2;


	if (camadas >= 2){
        mudar_marcador2(-1.05, 0.0, 0.0);
	peso_cor2_folhagem = 4;
	peso_cor2_sol = 1;
	peso_cor2_noite = 3;
	peso_cor2_sombra = 2;
	}
	if (camadas >= 3){
        mudar_marcador3(-0.9, 0.0, 0.0);
	peso_cor3_folhagem = 4;
	peso_cor3_sol = 1;
	peso_cor3_noite = 3;
	peso_cor3_sombra = 2;
	}
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

void editorTextureScreen::change_texture(LRGBColord cor, int mask_x) {

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

                if(bright > 0.1 && print_mask == 0){ //se for pra pintar todo o lagarto...
                    result_image.set_xel(i, j, LRGBColord(cor.get_x()*image.get_red(i, j),
											   cor.get_y()*image.get_green(i, j) ,
											   cor.get_z()*image.get_blue(i, j)));
                }
               else if(bright > 0.6 && bright <= 0.85 && print_mask == 1){  //se for cinza claro
    			//LRGBColord c = LRGBColord(0, 0, 1);
    			result_image.set_xel(i, j, LRGBColord(cor.get_x()*image.get_red(i, j),
											   cor.get_y()*image.get_green(i, j) ,
											   cor.get_z()*image.get_blue(i, j)));
    		}
                else if(bright > 0.85 && print_mask == 2){ //se for branco
                    result_image.set_xel(i, j, LRGBColord(cor.get_x()*image.get_red(i, j),
											   cor.get_y()*image.get_green(i, j),
											   cor.get_z()*image.get_blue(i, j)));

                }
                else if(bright > 0.1 && bright <= 0.6 && print_mask == 3){ //se for cinza escuro
                    result_image.set_xel(i, j, LRGBColord(cor.get_x()*image.get_red(i, j),
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


void editorTextureScreen::calcula_nivel_camuflagem(){
//colocando pesos para camuflagem
    if(peso_cor2_folhagem == -1 && peso_cor3_folhagem == -1){ //se o lagarto tiver apenas uma camada de cor
	peso_lagarto_folhagem = peso_cor1_folhagem;
	peso_lagarto_sol = peso_cor1_sol;
	peso_lagarto_noite = peso_cor1_noite;
	peso_lagarto_sombra = peso_cor1_sombra;
    }else if(peso_cor2_folhagem != -1 && peso_cor3_folhagem == -1){ //se o lagarto tiver duas camadas de cor
	    peso_lagarto_folhagem = (peso_cor1_folhagem + peso_cor2_folhagem)/2 ;
	    peso_lagarto_sol = (peso_cor1_sol + peso_cor2_sol)/2;
	    peso_lagarto_noite = (peso_cor1_noite + peso_cor2_noite)/2;
	    peso_lagarto_sombra = (peso_cor1_sombra + peso_cor2_sombra)/2 ;
	  }else{						    //se tiver 3 camadas de cor...
		peso_lagarto_folhagem = (peso_cor1_folhagem + peso_cor2_folhagem + peso_cor3_folhagem)/3 ;
		peso_lagarto_sol = (peso_cor1_sol + peso_cor2_sol+ peso_cor3_sol)/3;
		peso_lagarto_noite = (peso_cor1_noite + peso_cor2_noite + peso_cor3_noite)/3;
		peso_lagarto_sombra = (peso_cor1_sombra + peso_cor2_sombra + peso_cor3_sombra)/3 ;
	  }

	//aplica o peso da camuflagem da textura ao final da edição. O valor total não passa de 10
	peso_lagarto_folhagem += peso_lagarto_textura ;
	peso_lagarto_sol += peso_lagarto_textura;
	peso_lagarto_noite += peso_lagarto_textura;
	peso_lagarto_sombra += peso_lagarto_textura;
       //envia para o modelRepository os parâmetros de camuflagem na escala de 0 a 1
    ModelRepository::get_instance()->set_nivel_camuflagem(peso_lagarto_sol/10,peso_lagarto_noite/10, peso_lagarto_sombra/10, peso_lagarto_folhagem/10);
}


#include "characterEditor.h"
void editorTextureScreen::jogo_action(){
    //Atribui os valores para a camuflagem do lagarto antes de inciar o jogo.
	calcula_nivel_camuflagem();
		
	PT(CalangosMenuManager) cmanager = ((CalangosMenuManager*)(manager.p()));
     
	manager->open_screen(cmanager->get_loading_screen());
	Simdunas::set_play_clicked(true);
        
	/* Aqui o jogador clicou em jogar. Define a segunda fase */
	Session::get_instance()->set_level(2);
     
	((CharacterEditor*)cmanager->get_character_editor().p())->collect_player_properties();
}




