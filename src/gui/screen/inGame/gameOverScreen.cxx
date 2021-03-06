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
}

void GameOverScreen::load(){
	//Tela de game over
	frame_tela = new PGVirtualFrame("fundo_tela");
	frame_tela->setup(1, 2);

	np_frame_tela = get_root().attach_new_node(frame_tela);
	np_frame_tela.set_pos(-0.5, 0, -1);
	np_frame_tela.set_transparency(TransparencyAttrib::M_alpha);
	np_frame_tela.set_alpha_scale(0.0);

	lb_fim_do_jogo = new TextNode("lb_fim_de_jogo");
	lb_fim_do_jogo->set_text(ConfigVariableString("msg-fim","Fim do Jogo"));
	lb_fim_do_jogo->set_font(manager->get_default_font());
	lb_fim_do_jogo->set_shadow(0.05, 0.05);
	lb_fim_do_jogo->set_shadow_color(0, 0, 0, 1);
	lb_fim_do_jogo->set_align(TextNode::A_center);
	np_lb_fim_do_jogo = get_root().attach_new_node(lb_fim_do_jogo);
	np_lb_fim_do_jogo.set_scale(0.15);
	np_lb_fim_do_jogo.set_pos(0, 0, 0.6);
	np_lb_fim_do_jogo.set_color(1, 1, 1, 1, 0);

	lb_indica_morte = new TextNode("lb_indica_morte");
	lb_indica_morte->set_font(manager->get_default_font());
	lb_indica_morte->set_shadow(0.05, 0.05);
	lb_indica_morte->set_shadow_color(0, 0, 0, 1);
	lb_indica_morte->set_align(TextNode::A_center);
	np_lb_indica_morte = get_root().attach_new_node(lb_indica_morte);
	np_lb_indica_morte.set_scale(0.075);
	np_lb_indica_morte.set_pos(0, 0, 0.3);
	np_lb_indica_morte.set_color(1, 1, 1, 1, 0);

	//default_button_config(btn_restart, np_btn_restart, "Reiniciar", LVecBase3f(0, 0, 0), restart);
	default_button_config(btn_sair, np_btn_sair, ConfigVariableString("msg-sair","Sair"), LVecBase3f(0, 0, 0), sair_action);
}

void GameOverScreen::show() {
	Screen::show();
	Player::PlayerDeathType death = Session::get_instance()->get_player_death_status();

	/* Mostrando a causada da morte do player */
	switch (death) {
		case Player::PDT_MALNUTRITION:
			lb_indica_morte->set_text(ConfigVariableString("msg-causades", "Causa da Morte: Desnutrição."));
			break;

		case Player::PDT_HIGH_TEMPERATURE:
			lb_indica_morte->set_text(ConfigVariableString("msg-causata", "Causa da Morte: Temperatura Alta."));
			break;

		case Player::PDT_LOW_TEMPERATURE:
			lb_indica_morte->set_text(ConfigVariableString("msg-causatb", "Causa da Morte: Temperatura Baixa."));
			break;

		case Player::PDT_OLD_AGE:
			lb_indica_morte->set_text(ConfigVariableString("msg-zerou", "Parabéns! Jogo finalizado!"));
			break;

		case Player::PDT_DEHYDRATION:
			lb_indica_morte->set_text(ConfigVariableString("msg-causadesi", "Causa da Morte: Desidratação."));
			break;
		default:
			break;
	}
}

void GameOverScreen::restart(const Event*, void* data) {
	GameOverScreen* _this = (GameOverScreen*) data;
	_this->np_frame_tela.remove_node();
	_this->np_btn_restart.remove_node();
	_this->np_lb_fim_do_jogo.remove_node();
	_this->np_lb_indica_morte.remove_node();
	//    m->nod_sair.hide();
	simdunas_cat.debug() << "final r" << endl;

	simdunas_cat.debug() << "PASSSOU RESTART" << endl;


	Session::get_instance()->receive_answer("r");
}

void GameOverScreen::sair_action() {
	exit(0);
}
