#include "gameOverScreen.h"
#include "fontPool.h"

#include "mouseButton.h"

#include "simdunas.h"
#include "inGameScreenManager.h"
#include "session.h"


GameOverScreen::GameOverScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

GameOverScreen::~GameOverScreen() {
	unload();
}

void GameOverScreen::load(){
	//Tela de game over
	frame_tela = new PGVirtualFrame("fundo_tela");
	frame_tela->setup(1, 2);

	np_frame_tela = get_root().attach_new_node(frame_tela);
	np_frame_tela.set_pos(-0.5, 0, -1);
	np_frame_tela.set_transparency(TransparencyAttrib::M_alpha);
	np_frame_tela.set_alpha_scale(0.0);

	logo = window->load_model(get_root(), "models/buttons/fimdojogo.png");
	logo.set_scale(0.03);
	logo.set_pos(0.0, 0, 0.8);

	NodePath im_reiniciar = window->load_model(get_root(), "models/buttons/reiniciar");
	NodePath im_grafico = window->load_model(get_root(), "models/buttons/grafico");
	//NodePath im_sair = window->load_model(get_root(), "models/buttons/sair");
	NodePath pos_click = window->load_model(get_root(), "models/buttons/pos_click");

	pos_click.detach_node();
	im_reiniciar.detach_node();
	im_grafico.detach_node();
	//im_sair.detach_node();


	////////////////////////////botoes

	btn_restart = new Button("btn_restart", "Reiniciar");
	btn_restart->setup(im_reiniciar, pos_click);

	np_btn_restart = get_root().attach_new_node(btn_restart);
	np_btn_restart.set_scale(0.3);
	np_btn_restart.set_pos(0.0, 0.0, 0.0);
	btn_restart->set_frame(-0.4, 0.4, -0.4, 0.4);
	event_handler->add_hook(btn_restart->get_click_event(MouseButton::one()), restart, this);
	btn_graph = new PGButton("grafico");
	btn_graph->setup(im_grafico);
}

void GameOverScreen::unload() {
	np_frame_tela.remove_node();
	np_btn_restart.remove_node();
	logo.remove_node();
	indica_morte.remove_node();
	btn_graph = NULL;
	btn_restart = NULL;
	frame_tela = NULL;
}

void GameOverScreen::show() {
	Screen::show();
	Player::PlayerDeathType death = Session::get_instance()->get_player_death_status();

	/* Mostrando a causada da morte do player */
	switch (death) {
		case Player::PDT_MALNUTRITION:
			indica_morte = window->load_model(get_root(), "models/buttons/desnutricao.png");
			indica_morte.set_scale(0.065, 0.0, 0.09);
			indica_morte.set_pos(-0.05, 0.0, 0.45);
			break;

		case Player::PDT_HIGH_TEMPERATURE:
			cout<<"entrou aqui em temperatura alta. xD"<<endl;
			indica_morte = window->load_model(get_root(), "models/buttons/temperatura_alta.png");
			indica_morte.set_scale(0.065, 0.0, 0.09);
			indica_morte.set_pos(-0.1, 0.0, 0.45);
			break;

		case Player::PDT_LOW_TEMPERATURE:
			indica_morte = window->load_model(get_root(), "models/buttons/temperatura_baixa.png");
			indica_morte.set_scale(0.065, 0.0, 0.09);
			indica_morte.set_pos(-0.1, 0.0, 0.45);
			break;

		case Player::PDT_OLD_AGE:
			indica_morte = window->load_model(get_root(), "models/buttons/morte_idade.png");
			indica_morte.set_scale(0.065, 0.0, 0.09);
			indica_morte.set_pos(-0.1, 0.0, 0.45);
			break;

		case Player::PDT_DEHYDRATION:
			indica_morte = window->load_model(get_root(), "models/buttons/desidratacao.png");
			indica_morte.set_scale(0.065, 0.0, 0.09);
			indica_morte.set_pos(-0.05, 0.0, 0.45);
			break;
		default:
			break;
	}
}

void GameOverScreen::restart(const Event*, void* data) {
	GameOverScreen* _this = (GameOverScreen*) data;
	_this->np_frame_tela.remove_node();
	_this->np_btn_restart.remove_node();
	_this->logo.remove_node();
	_this->indica_morte.remove_node();
	//    m->nod_sair.hide();
	cout << "final r" << endl;

	cout << "PASSSOU RESTART" << endl;


	Session::get_instance()->receive_answer("r");
}
