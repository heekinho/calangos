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
#include "menu.h"
#include "fontPool.h"
#include "editorTextureScreen.h"
#include "collision.h"

Player::lizardEpecie GameOptionsScreen::especie = Player::eurolophosaurus; //a especie default

GameOptionsScreen::GameOptionsScreen(PT(ScreenManager) manager) : Screen(manager) {
	load();
	hide();
}

GameOptionsScreen::~GameOptionsScreen() {}

void GameOptionsScreen::load() {
	ratio = 0;

    ////////////////////////Tropidurus////////////////////
    tropidurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/tropidurus/male/model");
    tropidurus.set_scale(0.04, 0.04, 0.04);
    tropidurus.set_pos(4, 35, -3);
    tropidurus.set_h(45);
    tropidurus.set_p(20);
    /* Animação */
    Simdunas::get_window()->load_model(tropidurus, "models/lizards/tropidurus/male/walk");
    auto_bind(tropidurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    tropidurus.hide();

    //////////////////////////Eurolophosauros/////////////////
    eurolophosasurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/eurolophosaurus/male/model");
    eurolophosasurus.set_scale(0.04, 0.04, 0.04);
    eurolophosasurus.set_pos(4, 35, -3);
    eurolophosasurus.set_h(45);
    eurolophosasurus.set_p(20);
    /* Animação */
    Simdunas::get_window()->load_model(eurolophosasurus, "models/lizards/eurolophosaurus/male/walk");
    auto_bind(eurolophosasurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    eurolophosasurus.hide();

    //////////////////Cnemidophorus////////////
    cnemidophorus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/cnemidophorus/male/model");
    cnemidophorus.set_scale(0.04, 0.04, 0.04);
    cnemidophorus.set_pos(4, 35, -3);
    cnemidophorus.set_h(45);
    cnemidophorus.set_p(20);
    //		/* Animação */
    Simdunas::get_window()->load_model(cnemidophorus, "models/lizards/cnemidophorus/male/walk");
    auto_bind(cnemidophorus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    cnemidophorus.hide();

	///carregando titulo do menu de configurações
	img_titulo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/config_jogo.png");
	img_titulo.set_scale(0.1);
	img_titulo.set_pos(0.0, 0, 0.8);

	//relogio virtual////////////////////
	img_tempo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/tempo");
	img_tempo.set_scale(1, 0.0, 0.2);
	img_tempo.set_pos(-0.8, 0.0, 0.6);

	img_frase_relogio = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/relogio_frase");
	img_frase_relogio.set_scale(1.8, 0.0, 0.2);
	img_frase_relogio.set_pos(-0.1, 0.0, 0.4);

	/////////////////////Mostrando botão jogar////////////////////////
	default_button_config(btn_jogar, np_btn_jogar, "Jogar", -0.8, jogar_action);

	// Mostrando botão voltar
	default_button_config(btn_voltar, np_btn_voltar, "<< Voltar", -0.9, voltar_action);
	np_btn_voltar.set_x(-0.9);

	//////////////////////////////////////////Opção de configuração Tempo Virtual//////////
	slide = new PGSliderBar("slid");
	slide->set_range(1, 60);
	slide->setup_slider(false, 1.0, 0.06, 0.01);
	np_slide = Simdunas::get_window()->get_aspect_2d().attach_new_node(slide);
	np_slide.set_scale(0.5, 1.0, 1.0);
	np_slide.set_pos(-0.84, 0.0, 0.27);

	//criando o botão mais//////////////////////////////////////////////////////////
	img_btn_mais = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/mais");
	img_btn_mais.detach_node();
	btn_mais = new PGButton("mais");
	btn_mais->setup(img_btn_mais);
	np_btn_mais = Simdunas::get_window()->get_aspect_2d().attach_new_node(btn_mais);
	np_btn_mais.set_scale(0.12);
	np_btn_mais.set_pos(-0.53, 0.0, 0.28);
	btn_mais->set_frame(-0.4, 0.4, -0.4, 0.4);
	Simdunas::get_evt_handler()->add_hook(btn_mais->get_click_event(MouseButton::one()), slide_direita_action, this);

	////////o default será três? minutos então ja começa como se tivesse dado três clicks no +
	for (int i = 0; i < TimeControl::virtualTime; i++) {
		//                            const Event *ev_direita = new Event(btn_mais->get_click_event(MouseButton::one()));
		//                            Simdunas::get_evt_queue()->queue_event(ev_direita);
		//  cout<<"Minuto dia virtual: "<<config->minuto_dia_virtual<<endl;

		//melhor que ficar enfileirando eventos!!!
		slide_direita_action();
	}

	//criando o botão menos///////////////////////////////
	img_btn_menos = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/menos");
	img_btn_menos.detach_node();

	btn_menos = new PGButton("menos");
	btn_menos->setup(img_btn_menos);
	np_btn_menos = Simdunas::get_window()->get_aspect_2d().attach_new_node(btn_menos);
	np_btn_menos.set_scale(0.12);
	np_btn_menos.set_pos(-1.15, 0.0, 0.28);
	btn_menos->set_frame(-0.4, 0.4, -0.4, 0.4);
	Simdunas::get_evt_handler()->add_hook(btn_menos->get_click_event(MouseButton::one()), slide_esquerda_action, this);

	///////opção de configuração de Escolha da Espécie/////////////
	img_escolha_especie = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/especie.png");
	img_escolha_especie.set_scale(0.06, 0.0, 0.06);
	img_escolha_especie.set_pos(-0.68, 0.0, 0.03);

	//carregando o marcador/////////
	marcador = Simdunas::get_window()->load_model(img_escolha_especie, "models/buttons/marcador.png");
	marcador.set_scale(0.2, 0.0, 0.2);
	marcador.set_pos(4.0, 0.0, -4.7);

	///////Botões para escolha da especie/////////////////

	//botão TROPIDURUS///////////////
	img_btn_tropidurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/tropidurus");
	img_btn_tropidurus.detach_node();
	btn_tropidurus = new PGButton("tropidurus");
	btn_tropidurus->setup(img_btn_tropidurus);
	np_btn_tropidurus = Simdunas::get_window()->get_aspect_2d().attach_new_node(btn_tropidurus);
	np_btn_tropidurus.set_scale(0.5, 0.1, 0.18);
	np_btn_tropidurus.set_pos(-0.85, 0.0, -0.1);
	btn_tropidurus->set_frame(-0.4, 0.4, -0.4, 0.4);

	Simdunas::get_evt_handler()->add_hook(btn_tropidurus->get_click_event(MouseButton::one()), tropidurus_action, this);

	///////botão EUROLOPHOSAURUS //////////////////////////
	img_btn_eurolophosaurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/eurolophosaurus");
	img_btn_eurolophosaurus.detach_node();
	btn_eurolophosaurus = new PGButton("eurolophosaurus");
	btn_eurolophosaurus->setup(img_btn_eurolophosaurus);
	np_btn_eurolophosaurus = Simdunas::get_window()->get_aspect_2d().attach_new_node(btn_eurolophosaurus);
	np_btn_eurolophosaurus.set_scale(0.6, 0.1, 0.18);
	np_btn_eurolophosaurus.set_pos(-0.8, 0.0, -0.25);
	btn_eurolophosaurus->set_frame(-0.4, 0.4, -0.4, 0.4);

	Simdunas::get_evt_handler()->add_hook(btn_eurolophosaurus->get_click_event(MouseButton::one()), eurolophosaurus_action, this);

	///////botão CNEMIDOPHORUS //////////////////////////
	img_btn_cnemidophorus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/cnemidophorus");
	img_btn_cnemidophorus.detach_node();
	btn_cnemidophorus = new PGButton("cnemidophorus");
	btn_cnemidophorus->setup(img_btn_cnemidophorus);
	np_btn_cnemidophorus = Simdunas::get_window()->get_aspect_2d().attach_new_node(btn_cnemidophorus);
	np_btn_cnemidophorus.set_scale(0.6, 0.1, 0.18);
	np_btn_cnemidophorus.set_pos(-0.8, 0.0, -0.4);
	btn_cnemidophorus->set_frame(-0.4, 0.4, -0.4, 0.4);

	Simdunas::get_evt_handler()->add_hook(btn_cnemidophorus->get_click_event(MouseButton::one()), cnemidophorus_action, this);

	// ###########  Botão PERSONALIZAR (Leva o jogador para o editor de cores de lagartos) ##############################
	img_btn_personalizar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/personalizar");
	img_btn_personalizar.detach_node();
	btn_personalizar = new PGButton("Personalizar");
	btn_personalizar->setup(img_btn_personalizar);
	np_btn_personalizar = Simdunas::get_window()->get_aspect_2d().attach_new_node(btn_personalizar);
	np_btn_personalizar.set_scale(0.6, 0.1, 0.18);
	np_btn_personalizar.set_pos(-0.8, 0.0, -0.55);
	btn_personalizar->set_frame(-0.4, 0.4, -0.4, 0.4);

	Simdunas::get_evt_handler()->add_hook(btn_personalizar->get_click_event(MouseButton::one()), personalizar_action, this);

	//botão de ativar/desativar colisão
	img_btn_colisao = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/colisao");
	img_btn_colisao.detach_node();
	btn_colisao = new PGButton("colisao");
	btn_colisao->setup(img_btn_colisao);
	np_btn_colisao = Simdunas::get_window()->get_aspect_2d().attach_new_node(btn_colisao);
	np_btn_colisao.set_scale(0.6, 0.1, 0.18);
	np_btn_colisao.set_pos(0.6, 0.0, 0.03);
	btn_colisao->set_frame(-0.4, 0.4, -0.4, 0.4);

	Simdunas::get_evt_handler()->add_hook(btn_colisao->get_click_event(MouseButton::one()), colisao_action, this);

	//carregando botão V (de ativar colisão)
	img_colisao_ativada = Simdunas::get_window()->load_model(img_escolha_especie, "models/buttons/v.png");
	img_colisao_ativada.set_scale(0.2, 0.0, 0.2);
	img_colisao_ativada.set_pos(28.0, 0.0, 0.0);
     
	//carregando botão x (de desativar colisão)
	img_colisao_desativada = Simdunas::get_window()->load_model(img_escolha_especie, "models/buttons/x.png");
	img_colisao_desativada.set_scale(0.2, 0.0, 0.2);
	img_colisao_desativada.set_pos(28.0, 0.0, 0.0);
	

	Simdunas::get_evt_handler()->add_hook(slide->get_adjust_event(), slide_action, this);
	//o lagarto default é o eurolophosaurus
	eurolophosaurus_action();
	np_lb_num_minutos.show();
}

void GameOptionsScreen::unload() {
	img_btn_cnemidophorus.remove_node();
	img_btn_colisao.remove_node();
	img_btn_eurolophosaurus.remove_node();
	img_btn_mais.remove_node();
	img_btn_menos.remove_node();
	img_btn_personalizar.remove_node();
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
	np_btn_jogar.remove_node();
	np_btn_mais.remove_node();
	np_btn_menos.remove_node();
	np_btn_personalizar.remove_node();
	np_btn_tropidurus.remove_node();
	np_btn_voltar.remove_node();
	np_lb_num_minutos.remove_node();
	np_slide.remove_node();
	np_btn_voltar.remove_node();
	marcador.remove_node();
	tropidurus.remove_node();
	eurolophosasurus.remove_node();
	cnemidophorus.remove_node();
	slide = NULL;
	lb_num_minutos = NULL;
	btn_cnemidophorus = NULL;
	btn_colisao = NULL;
	btn_eurolophosaurus = NULL;
	btn_jogar = NULL;
	btn_mais = NULL;
	btn_menos = NULL;
	btn_personalizar = NULL;
	btn_tropidurus = NULL;
	btn_voltar = NULL;
}

/*! Configura um botão dado os parametros para este menu */
void GameOptionsScreen::default_button_config(PT(Button) button, NodePath &np,
		const string &text, float z, EventCallbackFunction *action) {

	/* Cria um botão padrão, coloca no nó root e define o z */
	button = new Button(text + "-button", text, manager->get_default_font());
	np = get_root().attach_new_node(button);
	np.set_z(z);

	/* Cadastrando o evento */
	string event_name = button->get_click_event(MouseButton::one());
	manager->get_event_handler()->add_hook(event_name, action, this);
}

void GameOptionsScreen::show() {
	ostringstream letra; //convertendo minuto dia virtual em string
	letra << Menu::get_instance()->get_minuto_dia_virtual();
	std::string st(letra.str());
	informa_segundos(st);

	img_btn_cnemidophorus.show();
	img_btn_colisao.show();
	img_btn_eurolophosaurus.show();
	img_btn_mais.show();
	img_btn_menos.show();
	img_btn_personalizar.show();
	img_btn_tropidurus.show();
	img_colisao_ativada.show();
	img_escolha_especie.show();
	img_frase_relogio.show();
	img_tempo.show();
	img_titulo.show();
	np_btn_cnemidophorus.show();
	np_btn_colisao.show();
	np_btn_eurolophosaurus.show();
	np_btn_jogar.show();
	np_btn_mais.show();
	np_btn_menos.show();
	np_btn_personalizar.show();
	np_btn_tropidurus.show();
	np_lb_num_minutos.show();
	np_slide.show();
	np_btn_voltar.show();
	marcador.show();
	np_btn_voltar.show();

	switch (especie) {//mostrando especie q tava selecionada
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
	img_btn_cnemidophorus.hide();
	img_btn_colisao.hide();
	img_btn_eurolophosaurus.hide();
	img_btn_mais.hide();
	img_btn_menos.hide();
	img_btn_personalizar.hide();
	img_btn_tropidurus.hide();
	img_colisao_ativada.hide();
	img_escolha_especie.hide();
	img_frase_relogio.hide();
	img_tempo.hide();
	img_titulo.hide();
	np_btn_cnemidophorus.hide();
	np_btn_colisao.hide();
	np_btn_eurolophosaurus.hide();
	np_btn_jogar.hide();
	np_btn_mais.hide();
	np_btn_menos.hide();
	np_btn_personalizar.hide();
	np_btn_tropidurus.hide();
	np_lb_num_minutos.hide();
	np_slide.hide();
	np_btn_voltar.hide();
	marcador.hide();
	np_btn_voltar.hide();

	switch (especie) {//mostrando especie q tava selecionada
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

Player::lizardEpecie GameOptionsScreen::get_especie() {
	return especie;
}

void GameOptionsScreen::slide_direita_action() {
	int minuto_dia_virtual = Menu::get_instance()->get_minuto_dia_virtual();
	if (minuto_dia_virtual < 60) {
		Menu::get_instance()->set_minuto_dia_virtual(++minuto_dia_virtual);

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
	int minuto_dia_virtual = Menu::get_instance()->get_minuto_dia_virtual();
	if (minuto_dia_virtual > 1) {
		Menu::get_instance()->set_minuto_dia_virtual(--minuto_dia_virtual);

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
	if (lb_num_minutos == NULL) {
		lb_num_minutos = new TextNode("inicio");
		lb_num_minutos->set_font(FontPool::load_font("models/ExpletiveDeleted.ttf"));
		lb_num_minutos->set_text(aviso);

		np_lb_num_minutos = Simdunas::get_window()->get_aspect_2d().attach_new_node(lb_num_minutos);
	} else {
		lb_num_minutos->set_text(aviso);
	}
	np_lb_num_minutos.set_scale(0.17);
	np_lb_num_minutos.set_pos(-1.2, 0, 0.35);
	np_lb_num_minutos.set_color(0.87, 0.72, 0.52);
}

void GameOptionsScreen::tropidurus_action() {
	switch (especie) {
		case Player::cnemidophorus :
			cnemidophorus.hide();
			break;
		case Player::eurolophosaurus :
			eurolophosasurus.hide();
			break;
	}
	especie = Player::tropidurus;
	marcador.set_pos(4.0, 0.0, -2.2); //movendo o marcador
	tropidurus.set_scale(0.04, 0.04, 0.04);
	tropidurus.set_pos(4, 35, -2);
	tropidurus.show();
}

void GameOptionsScreen::eurolophosaurus_action() {
	switch (especie) {
		case Player::tropidurus :
			tropidurus.hide();
			break;
		case Player::cnemidophorus :
			cnemidophorus.hide();
			break;
	}

	especie = Player::eurolophosaurus;
	marcador.set_pos(4.0, 0.0, -4.7); //movendo o marcador
	eurolophosasurus.set_scale(0.04, 0.04, 0.04);
	eurolophosasurus.set_pos(4, 35, -2);
	eurolophosasurus.show();
}

void GameOptionsScreen::cnemidophorus_action() {
	switch (especie) {
		case Player::tropidurus :
			tropidurus.hide();
			break;
		case Player::eurolophosaurus :
			eurolophosasurus.hide();
			break;
	}
	especie = Player::cnemidophorus;
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
    Menu::get_instance()->set_minuto_dia_virtual(minuto_dia_virtual);
    ostringstream letra; //convertendo float em string
    letra << minuto_dia_virtual;
    std::string st(letra.str());

    informa_segundos(st);
}

void GameOptionsScreen::personalizar_action() {
	marcador.set_pos(4.0, 0.0, -9.5); //movendo o marcador

	hide();  //limpa o menu de configuração

	especie = Player::custom;  //determina que o jogador irá jogar com o lagarto personalizado

	// show_tela_personalizar(c); //apresenta o menu de edição de cores do lagarto
	//apresenta os botões jogar e voltar
	showing_custom = true;
	//editorTextureScreen::get_instance()->load_screen();
        manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_editor_texture_screen());


}

void GameOptionsScreen::jogar_action() {
	nout << "Carregando Jogo..." << endl;

	if (Menu::get_instance()->get_minuto_dia_virtual() == 0) {
		Menu::get_instance()->set_minuto_dia_virtual(TimeControl::virtualTime);
	}

	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_loading_screen());

	Simdunas::set_play_clicked(true);
}

void GameOptionsScreen::voltar_action() {
	CalangosMenuManager* menu_manager = (CalangosMenuManager*) manager.p();
	menu_manager->open_screen(menu_manager->get_options_screen());
}
