#include "nameScreen.h"
#include "fontPool.h"

#include "string.h"
#include "mouseButton.h"
#include "textNode.h"
#include "nodePath.h"
#include "simdunas.h"
#include <iostream>
#include <fstream>
#include "calangosMenuManager.h"

NameScreen::NameScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

NameScreen::~NameScreen() {

}

void NameScreen::load(){
	window->set_background_type(WindowFramework::BT_black);

	//carregando animação inicial da Tela principal
	np_lagarto = window->load_model(render, "models/lizards/cnemidophorus/male/model");
	np_lagarto.set_scale(0.08, 0.08, 0.08);
	np_lagarto.set_pos(0, 35, -2);
	np_lagarto.set_h(45);
	np_lagarto.set_p(20);

	//Animação
	window->load_model(np_lagarto, "models/lizards/cnemidophorus/male/walk");
	auto_bind(np_lagarto.node(), anims, PartGroup::HMF_ok_part_extra |
			PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
	anims.loop_all(false);

	//Auxilio do nome
	name_label = new TextNode("name_label");
	name_label->set_text(ConfigVariableString("msg-name", "Escreva seu nome abaixo"));
	name_label->set_font(manager->get_default_font());
	np_name_label = get_root().attach_new_node(name_label);
	np_name_label.set_pos(-0.7, 0.0, 0);
	np_name_label.set_scale(0.12);
	np_name_label.set_color(1, 1, 1, 1, 0);
	
	//Entrada do nome
	name_box = new PGEntry("name_box");
	name_box->setup(15, 1);
	name_box->set_overflow_mode(true);
	np_name_box = get_root().attach_new_node(name_box);
	np_name_box.set_pos(-0.6, 0.0, -0.2);
	np_name_box.set_scale(0.08);

	
	///Imagem do logo
	np_logo = window->load_model(get_root(), "models/calangos.png");
    np_logo.set_scale(0.1);
    np_logo.set_pos(0.0, 0, 0.6);
	default_button_config(btn_avancar, np_btn_avancar, ConfigVariableString("msg-avan", "Avançar >>"), LVecBase3f(0.7, 0, -0.9), jogar_action);


    //botões de escolha da linguagem e mudança para o menu principal  by:Crystal
   }
void NameScreen::show(){
	Screen::show();
	np_lagarto.unstash();

}
void NameScreen::hide(){
	Screen::hide();
	np_lagarto.stash();

}

void NameScreen::set_name(string name){
	name_send = name;
}

string NameScreen::get_name(){
	return name_send;
}

void NameScreen::jogar_action() {
	
	nome_jogador = name_box->get_text();
	if(nome_jogador == ""){
	
	}
	else{
	set_name(nome_jogador);
	//char c;	
	//char nome[1024];
	//strncpy(nome, nome_jogador.c_str(), sizeof(nome));
	//nome[sizeof(nome) - 1] = 0;
	//FILE *arq;
	//arq = fopen("config/nome_temp.txt", "w");
	//if (arq == NULL)
//{
//    printf("Problemas na CRIACAO do arquivo\n");
//    return;
//} 
//	else
//	{
//	fputs(nome,arq);
//	fclose(arq);
//	}
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());
	Simdunas::set_play_clicked(true);
	Session::get_instance()->set_level(1);
	}
	
}
