/*
 * gameOptionsScreen.cxx
 *
 *  Created on: Mar 6, 2011
 *      Author: jonatas
 */

#include "gameOptionsScreen.h"
#include "simdunas.h"
#include "mouseButton.h"
#include "calangosMenuManager.h"
#include "fontPool.h"
#include "editorTextureScreen.h"
#include "collision.h"

//Player::lizardEpecie GameOptionsScreen::especie = Player::eurolophosaurus; //a especie default

GameOptionsScreen::GameOptionsScreen(PT(ScreenManager) manager) : Screen(manager) {
	load();
	hide();
}

GameOptionsScreen::~GameOptionsScreen() {
	unload();
}

void GameOptionsScreen::load() {
	ratio = 0;

    ////////////////////////Tropidurus////////////////////
    tropidurus = window->load_model(render, "models/lizards/tropidurus/male/model");
    tropidurus.set_scale(0.04, 0.04, 0.04);
    tropidurus.set_pos(4, 35, -3);
    tropidurus.set_h(45);
    tropidurus.set_p(20);
    /* Animação */
    window->load_model(tropidurus, "models/lizards/tropidurus/male/walk");
    auto_bind(tropidurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    tropidurus.hide();

    //////////////////////////Eurolophosauros/////////////////
    eurolophosasurus = window->load_model(render, "models/lizards/eurolophosaurus/male/model");
    eurolophosasurus.set_scale(0.04, 0.04, 0.04);
    eurolophosasurus.set_pos(4, 35, -3);
    eurolophosasurus.set_h(45);
    eurolophosasurus.set_p(20);
    /* Animação */
    window->load_model(eurolophosasurus, "models/lizards/eurolophosaurus/male/walk");
    auto_bind(eurolophosasurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    eurolophosasurus.hide();

    //////////////////Cnemidophorus////////////
    cnemidophorus = window->load_model(render, "models/lizards/cnemidophorus/male/model");
    cnemidophorus.set_scale(0.04, 0.04, 0.04);
    cnemidophorus.set_pos(4, 35, -3);
    cnemidophorus.set_h(45);
    cnemidophorus.set_p(20);
    //		/* Animação */
    window->load_model(cnemidophorus, "models/lizards/cnemidophorus/male/walk");
    auto_bind(cnemidophorus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    cnemidophorus.hide();

	///carregando titulo do menu de configurações
	img_titulo = window->load_model(get_root(), "models/config_jogo.png");
	img_titulo.set_scale(0.1);
	img_titulo.set_pos(0.0, 0, 0.8);

	//relogio virtual////////////////////
	img_tempo = window->load_model(get_root(), "models/buttons/tempo");
	img_tempo.set_scale(1, 0.0, 0.2);
	img_tempo.set_pos(-0.8, 0.0, 0.6);

	img_frase_relogio = window->load_model(get_root(), "models/buttons/relogio_frase");
	img_frase_relogio.set_scale(1.8, 0.0, 0.2);
	img_frase_relogio.set_pos(-0.1, 0.0, 0.4);

//	/////////////////////Mostrando botão jogar////////////////////////
//	default_button_config(btn_jogar, np_btn_jogar, "Jogar", -0.8, jogar_action);

	// Mostrando botão voltar
	configure_default_back_button(((CalangosMenuManager* ) manager.p())->get_options_screen());

	//////////////////////////////////////////Opção de configuração Tempo Virtual//////////
	slide = new PGSliderBar("slid");
	slide->set_range(1, 60);
	slide->setup_slider(false, 1.0, 0.06, 0.01);
	np_slide = get_root().attach_new_node(slide);
	np_slide.set_scale(0.5, 1.0, 1.0);
	np_slide.set_pos(-0.84, 0.0, 0.27);

	//criando o botão mais//////////////////////////////////////////////////////////
	img_btn_mais = window->load_model(get_root(), "models/buttons/mais");
	img_btn_mais.detach_node();
	btn_mais = new PGButton("mais");
	btn_mais->setup(img_btn_mais);
	np_btn_mais = get_root().attach_new_node(btn_mais);
	np_btn_mais.set_scale(0.12);
	np_btn_mais.set_pos(-0.53, 0.0, 0.28);
	btn_mais->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_mais->get_click_event(MouseButton::one()), slide_direita_action, this);

	////////o default será três? minutos então ja começa como se tivesse dado três clicks no +
//	for (int i = 0; i < TimeControl::get_instance()->get_virtual_time_hour(); i++) {
//		//                            const Event *ev_direita = new Event(btn_mais->get_click_event(MouseButton::one()));
//		//                            event_queue->queue_event(ev_direita);
//		//  cout<<"Minuto dia virtual: "<<config->minuto_dia_virtual<<endl;
//
//		//melhor que ficar enfileirando eventos!!!
//		slide_direita_action();
//	}

	//criando o botão menos///////////////////////////////
	img_btn_menos = window->load_model(get_root(), "models/buttons/menos");
	img_btn_menos.detach_node();

	btn_menos = new PGButton("menos");
	btn_menos->setup(img_btn_menos);
	np_btn_menos = get_root().attach_new_node(btn_menos);
	np_btn_menos.set_scale(0.12);
	np_btn_menos.set_pos(-1.15, 0.0, 0.28);
	btn_menos->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_menos->get_click_event(MouseButton::one()), slide_esquerda_action, this);

	///////opção de configuração de Escolha da Espécie/////////////
	img_escolha_especie = window->load_model(get_root(), "models/buttons/especie.png");
	img_escolha_especie.set_scale(0.06, 0.0, 0.06);
	img_escolha_especie.set_pos(-0.68, 0.0, 0.03);

	//carregando o marcador/////////
	marcador = window->load_model(img_escolha_especie, "models/buttons/marcador.png");
	marcador.set_scale(0.2, 0.0, 0.2);
	marcador.set_pos(4.0, 0.0, -4.7);

	///////Botões para escolha da especie/////////////////

	//botão TROPIDURUS///////////////
	img_btn_tropidurus = window->load_model(get_root(), "models/buttons/tropidurus");
	img_btn_tropidurus.detach_node();
	btn_tropidurus = new PGButton("tropidurus");
	btn_tropidurus->setup(img_btn_tropidurus);
	np_btn_tropidurus = get_root().attach_new_node(btn_tropidurus);
	np_btn_tropidurus.set_scale(0.5, 0.1, 0.18);
	np_btn_tropidurus.set_pos(-0.85, 0.0, -0.1);
	btn_tropidurus->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_tropidurus->get_click_event(MouseButton::one()), tropidurus_action, this);

	///////botão EUROLOPHOSAURUS //////////////////////////
	img_btn_eurolophosaurus = window->load_model(get_root(), "models/buttons/eurolophosaurus");
	img_btn_eurolophosaurus.detach_node();
	btn_eurolophosaurus = new PGButton("eurolophosaurus");
	btn_eurolophosaurus->setup(img_btn_eurolophosaurus);
	np_btn_eurolophosaurus = get_root().attach_new_node(btn_eurolophosaurus);
	np_btn_eurolophosaurus.set_scale(0.6, 0.1, 0.18);
	np_btn_eurolophosaurus.set_pos(-0.8, 0.0, -0.25);
	btn_eurolophosaurus->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_eurolophosaurus->get_click_event(MouseButton::one()), eurolophosaurus_action, this);

	///////botão CNEMIDOPHORUS //////////////////////////
	img_btn_cnemidophorus = window->load_model(get_root(), "models/buttons/cnemidophorus");
	img_btn_cnemidophorus.detach_node();
	btn_cnemidophorus = new PGButton("cnemidophorus");
	btn_cnemidophorus->setup(img_btn_cnemidophorus);
	np_btn_cnemidophorus = get_root().attach_new_node(btn_cnemidophorus);
	np_btn_cnemidophorus.set_scale(0.6, 0.1, 0.18);
	np_btn_cnemidophorus.set_pos(-0.8, 0.0, -0.4);
	btn_cnemidophorus->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_cnemidophorus->get_click_event(MouseButton::one()), cnemidophorus_action, this);

//	// ###########  Botão PERSONALIZAR (Leva o jogador para o editor de cores de lagartos) ##############################
//	img_btn_personalizar = window->load_model(get_root(), "models/buttons/personalizar");
//	img_btn_personalizar.detach_node();
//	btn_personalizar = new PGButton("Personalizar");
//	btn_personalizar->setup(img_btn_personalizar);
//	np_btn_personalizar = get_root().attach_new_node(btn_personalizar);
//	np_btn_personalizar.set_scale(0.6, 0.1, 0.18);
//	np_btn_personalizar.set_pos(-0.8, 0.0, -0.55);
//	btn_personalizar->set_frame(-0.4, 0.4, -0.4, 0.4);
//
//	event_handler->add_hook(btn_personalizar->get_click_event(MouseButton::one()), personalizar_action, this);

	//botão de ativar/desativar colisão
	img_btn_colisao = window->load_model(get_root(), "models/buttons/colisao");
	img_btn_colisao.detach_node();
	btn_colisao = new PGButton("colisao");
	btn_colisao->setup(img_btn_colisao);
	np_btn_colisao = get_root().attach_new_node(btn_colisao);
	np_btn_colisao.set_scale(0.6, 0.1, 0.18);
	np_btn_colisao.set_pos(0.6, 0.0, 0.03);
	btn_colisao->set_frame(-0.4, 0.4, -0.4, 0.4);

	event_handler->add_hook(btn_colisao->get_click_event(MouseButton::one()), colisao_action, this);

	//carregando botão V (de ativar colisão)
	img_colisao_ativada = window->load_model(img_escolha_especie, "models/buttons/v.png");
	img_colisao_ativada.set_scale(0.2, 0.0, 0.2);
	img_colisao_ativada.set_pos(28.0, 0.0, 0.0);
     
	//carregando botão x (de desativar colisão)
	img_colisao_desativada = window->load_model(img_escolha_especie, "models/buttons/x.png");
	img_colisao_desativada.set_scale(0.2, 0.0, 0.2);
	img_colisao_desativada.set_pos(28.0, 0.0, 0.0);
	
	if (collision::get_instance()->get_colisao()) {
		img_colisao_ativada.show();
		img_colisao_desativada.hide();
	}
	else {
		img_colisao_desativada.show();
		img_colisao_ativada.hide();
	}


	event_handler->add_hook(slide->get_adjust_event(), slide_action, this);
	//o lagarto default é o eurolophosaurus
	eurolophosaurus_action();


	/* Configuração de NumMinutos */
	lb_num_minutos = new TextNode("inicio");
	lb_num_minutos->set_font(FontPool::load_font("models/ExpletiveDeleted.ttf"));

	np_lb_num_minutos = get_root().attach_new_node(lb_num_minutos);
	np_lb_num_minutos.set_scale(0.17);
	np_lb_num_minutos.set_pos(-1.2, 0, 0.35);
	np_lb_num_minutos.set_color(0.87, 0.72, 0.52);
	np_lb_num_minutos.show();

	ostringstream letra; //convertendo minuto dia virtual em string
	letra << TimeControl::get_instance()->get_virtual_time_hour();
	std::string st(letra.str());
	informa_segundos(st);
}

void GameOptionsScreen::unload() {
	img_btn_cnemidophorus.remove_node();
	img_btn_colisao.remove_node();
	img_btn_eurolophosaurus.remove_node();
	img_btn_mais.remove_node();
	img_btn_menos.remove_node();
//	img_btn_personalizar.remove_node();
	img_btn_tropidurus.remove_node();
	img_colisao_ativada.remove_node();
	img_colisao_desativada.remove_node();
	img_escolha_especie.remove_node();
	img_frase_relogio.remove_node();
	img_tempo.remove_node();
	img_titulo.remove_node();
	np_btn_cnemidophorus.remove_node();
	np_btn_colisao.remove_node();
	np_btn_eurolophosaurus.remove_node();
//	np_btn_jogar.remove_node();
	np_btn_mais.remove_node();
	np_btn_menos.remove_node();
//	np_btn_personalizar.remove_node();
	np_btn_tropidurus.remove_node();
	np_lb_num_minutos.remove_node();
	np_slide.remove_node();
	marcador.remove_node();
	tropidurus.remove_node();
	eurolophosasurus.remove_node();
	cnemidophorus.remove_node();
	np_btn_back.remove_node();
	slide = NULL;
	lb_num_minutos = NULL;
	btn_cnemidophorus = NULL;
	btn_colisao = NULL;
	btn_eurolophosaurus = NULL;
//	btn_jogar = NULL;
	btn_mais = NULL;
	btn_menos = NULL;
//	btn_personalizar = NULL;
	btn_tropidurus = NULL;
	btn_back = NULL;
}

void GameOptionsScreen::show() {
	Screen::show();

	switch (Player::lizard_specie) {//mostrando especie q tava selecionada
		case Player::tropidurus :
			tropidurus.show();
			break;
		case Player::eurolophosaurus :
			eurolophosasurus.show();
			break;

		case Player::cnemidophorus :
			cnemidophorus.show();
			break;
	}
}

void GameOptionsScreen::hide() {
	Screen::hide();

	switch (Player::lizard_specie) {//mostrando especie q tava selecionada
		case Player::tropidurus :
			tropidurus.hide();
			break;
		case Player::eurolophosaurus :
			eurolophosasurus.hide();
			break;

		case Player::cnemidophorus :
			cnemidophorus.hide();
			break;
	}
}

//Player::lizardEpecie GameOptionsScreen::get_especie() {
//	return especie;
//}

void GameOptionsScreen::slide_direita_action() {
	int minuto_dia_virtual = TimeControl::get_instance()->get_virtual_time_hour();
	if (minuto_dia_virtual < 60) {
		TimeControl::get_instance()->set_virtual_time_hour(++minuto_dia_virtual);

		ostringstream letra; //convertendo float em string

		//TimeControl::virtualTime = d->minuto_dia_virtual;

		letra << minuto_dia_virtual;
		std::string st(letra.str());

		informa_segundos(st);

		/*cout<<"Valor :"<<(int)d->slid->get_value()<<endl;
            cout<<"Valor Minuto_dia_Virtual Direita:"<<d->minuto_dia_virtual<<endl;*/

		slide->set_value(minuto_dia_virtual);
	}
}

void GameOptionsScreen::slide_esquerda_action() {
	int minuto_dia_virtual = TimeControl::get_instance()->get_virtual_time_hour();
	if (minuto_dia_virtual > 1) {
		TimeControl::get_instance()->set_virtual_time_hour(--minuto_dia_virtual);

		ostringstream letra; //convertendo float em string

		//TimeControl::virtualTime = d->minuto_dia_virtual;

		letra << minuto_dia_virtual;
		std::string st(letra.str());

		informa_segundos(st);

		/*cout<<"Valor :"<<(int)d->slid->get_value()<<endl;
            cout<<"Valor Minuto_dia_Virtual Esquerda:"<<d->minuto_dia_virtual<<endl;*/
		slide->set_value(minuto_dia_virtual);
	}
}

void GameOptionsScreen::informa_segundos(string aviso) {
	lb_num_minutos->set_text(aviso);
}

void GameOptionsScreen::tropidurus_action() {
	switch (Player::lizard_specie) {
		case Player::cnemidophorus :
			cnemidophorus.hide();
			break;
		case Player::eurolophosaurus :
			eurolophosasurus.hide();
			break;
	}
	Player::lizard_specie = Player::tropidurus;
	marcador.set_pos(4.0, 0.0, -2.2); //movendo o marcador
	tropidurus.set_scale(0.04, 0.04, 0.04);
	tropidurus.set_pos(4, 35, -2);
	tropidurus.show();
}

void GameOptionsScreen::eurolophosaurus_action() {
	switch (Player::lizard_specie) {
		case Player::tropidurus :
			tropidurus.hide();
			break;
		case Player::cnemidophorus :
			cnemidophorus.hide();
			break;
	}

	Player::lizard_specie = Player::eurolophosaurus;
	marcador.set_pos(4.0, 0.0, -4.7); //movendo o marcador
	eurolophosasurus.set_scale(0.04, 0.04, 0.04);
	eurolophosasurus.set_pos(4, 35, -2);
	eurolophosasurus.show();
}

void GameOptionsScreen::cnemidophorus_action() {
	switch (Player::lizard_specie) {
		case Player::tropidurus :
			tropidurus.hide();
			break;
		case Player::eurolophosaurus :
			eurolophosasurus.hide();
			break;
	}
	Player::lizard_specie = Player::cnemidophorus;
	marcador.set_pos(4.0, 0.0, -7.2); //movendo o marcador
	cnemidophorus.set_scale(0.04, 0.04, 0.04);
	cnemidophorus.set_pos(4, 35, -2);
	cnemidophorus.show();
}

void GameOptionsScreen::colisao_action() {
    //se a colisão tiver ativada, então desativa agora
    if(collision::get_instance()->get_colisao()){
        img_colisao_ativada.hide();
        img_colisao_desativada.show();
        collision::get_instance()->set_colisao(false);
    }else
    { //se estiver desativada então ativa.
    	img_colisao_ativada.show();
    	img_colisao_desativada.hide();
        collision::get_instance()->set_colisao(true);
    }
}

void GameOptionsScreen::slide_action() {
    int minuto_dia_virtual = (int) slide->get_value();
    TimeControl::get_instance()->set_virtual_time_hour(minuto_dia_virtual);
    ostringstream letra; //convertendo float em string
    letra << minuto_dia_virtual;
    std::string st(letra.str());

    informa_segundos(st);
}

//void GameOptionsScreen::personalizar_action() {
//	marcador.set_pos(4.0, 0.0, -9.5); //movendo o marcador
//
//	hide();  //limpa o menu de configuração
//
//	Player::lizard_specie = Player::custom;  //determina que o jogador irá jogar com o lagarto personalizado
//
//	// show_tela_personalizar(c); //apresenta o menu de edição de cores do lagarto
//	//apresenta os botões jogar e voltar
//	showing_custom = true;
//	//editorTextureScreen::get_instance()->load_screen();
//        manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_editor_texture_screen());
//
//
//}
//
//void GameOptionsScreen::jogar_action() {
//	nout << "Carregando Jogo..." << endl;
//
//	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());
//
//	Simdunas::set_play_clicked(true);
//}
