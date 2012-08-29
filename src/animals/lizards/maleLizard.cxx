#include "maleLizard.h"
#include "simdunas.h"

#include "player.h"
#include "guiManager.h"

#define MAXDEGREE 100
#define PROBTHR 80

const double MaleLizard::BOBBING_WAITING_TIME = 3.0;

MaleLizard::MaleLizard(NodePath node) : Lizard(node) {
	init();
}


MaleLizard::~MaleLizard(){
	event_handler->remove_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this);
	male_symbol.remove_node();
}

void MaleLizard::init() {
    //Lizard::init();
    //bind_anims(node());
    last_bobbing_done = 0;
    waiting_player_decide = false;
    eat_thr = 0.3;

    PT(AnimControl) ac = get_anim_control()->find_anim("fast_bite");
    if(ac != NULL) ac->set_play_rate(1.5);

    male_symbol = window->load_model(*this, "models/lizards/symbols/male.png");
    male_symbol.set_scale(0.007);
    male_symbol.set_z(get_height() * 1.2);
    male_symbol.set_billboard_point_eye(0);

    set_gender(Lizard::LG_male);
}

void MaleLizard::act(){
	float bobbing_dist_thr = 3;
	float flee_max_dist = 10;
	//float distance = (player->get_pos() - get_pos()).length();
	float distance = get_distance_squared(*player);//Substituição ocorreu porque distance é utilizada em comparações
	//if(!player->has_female_around() && is_action_active("fight")) set_action("walk", true);

	/* Quando esperando a resposta do player... */
	if(waiting_player_decide == true){
		/* Se o player não respondeu dentro do tempo */
		if(global_clock->get_real_time() - last_bobbing_done > BOBBING_WAITING_TIME){
			waiting_player_decide = false;
			event_handler->remove_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this);

			/* Paciência tem limite... Parte para morder o player */
			// TODO: Consertar essa bagunça de enums.
			if(!player->is_young()){
				set_action("fight", true);

		}
	}

		}
	/*Se o player estiver sendo caçado por um predador, os lizards não irão atacar*/
	if(player->get_hunted()){
		set_action("walk", true);
		player->set_adversary(NULL);

		}
	/*Se o player se distânciar muito do lizard, a perseguição acaba*/
	if(distance > (1.25 * flee_max_dist)*(1.25 * flee_max_dist)){
		set_action("walk", true);

	}
/*------------------------------------------------------------------------------
 * Verificação de continuação de briga com o lagarto do jogador*/
	if(is_action_active("flee") || this->get_energia() < 20){
		if(distance < flee_max_dist*flee_max_dist) flee();
		else {
			energia = 50;
			set_action("walk", true);
			player->set_adversary(NULL);

		}

		waiting_player_decide = false;
	}
	else if(is_action_active("fight")){

		if(player->get_adversary() == NULL){
			/*Se o player já não estiver lutando com nenhum outro lizard, este pode ser o adversário*/
			player->set_adversary(this);
			/* Round One: FIGHT! */
			if(distance < eat_thr*eat_thr){
				bite();
			}
			else chase();
		}

		else{
			if(player->get_adversary() == this){
				/*Continua a luta, se o adversário do player ainda for este lizard*/

				if(distance < eat_thr*eat_thr){
					/*Se ele estiver próximo ao player*/
					bite();
				}

				else if(distance < (1.25 * flee_max_dist)*(1.25 * flee_max_dist)){
					/*Se ele estiver distante do player, mas ainda no raio de visão
					 * ele continua a perseguição*/
					chase();
				}

				if(distance > (1.25 * flee_max_dist)*(1.25 * flee_max_dist)){
					/*Se ele estiver muito distante, ele desiste da luta*/
					set_action("walk", true);

					player->set_adversary(NULL);
				}


			}

			else{
				set_action("walk", true);
			}
		}
	}
	else if(distance < bobbing_dist_thr*bobbing_dist_thr && !waiting_player_decide){
		/* Aqui se verifica as condições para começar uma briga */
		/* "Se o player tem femea próximo dele, e eu tow perto dele, logo tem femea perto de mim..."
		 * Evita-se assim ter que calcular toda santa hora as distâncias e etc. Só consulto a flag... */
		if(player->has_female_around() && !player->is_young()){
			bob();
			last_bobbing_done = global_clock->get_real_time();
			waiting_player_decide = true;

			event_handler->add_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this);
		}
	}
	else {
		set_action("walk");
		play_action_anims(true);

		Lizard::act();
	}
}


void MaleLizard::player_did_bobbing(const Event *theEvent, void *data){
	MaleLizard* this_lizard = (MaleLizard*) data;
	event_handler->remove_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this_lizard);

	this_lizard->waiting_player_decide = false;

	float fight_prob = (this_lizard->get_tamanho_base() - player->get_relative_size()) / 2 + 40.0;

	if (rand() % 100 < fight_prob) this_lizard->set_action("fight", true);
	else {
		player->get_achievements()->inc_reprodutor();
		this_lizard->set_action("flee", true);
	}
}

void MaleLizard::bob(){
	//set_action("bobbing");
	//play_action_anims();
	play_anim("bobbing");
}

void MaleLizard::wander(){
	if(!stay_quiet()){
		if(rand()%PROBTHR == 34) set_h(*this, rand()%MAXDEGREE - (MAXDEGREE/2));
		this->move(get_velocity());
	}
}

void MaleLizard::chase(){
	//float distance = (player->get_pos() - get_pos()).length();
	float distance = get_distance_squared(*player);
	if(!has_other_anim_active("walk")){
		play_anim("walk");

		/* Comportamento */
		look_at(*player);  //TODO: Corrigir depois para não permitir muito giro.

//		 if(distance > (eat_thr - (eat_thr / 10))*(eat_thr - (eat_thr / 10))) {
//			 move(VEL_RUN);
//
//		 }
		 if(distance > (eat_thr )*(eat_thr )) {
			 move(get_velocity()*3);
		 }
	}

}

void MaleLizard::be_bited(float relative_size){

	Lizard::be_bited();
	this->energia = this->energia - (relative_size * 5);
//	this->energia = this->energia - 15;
	set_action("fight", true);
//	GuiManager::get_instance()->piscar_life();
}


void MaleLizard::bite(){
	/* Manter simples por enquanto */
	if(!get_anim_control()->is_playing("fast_bite")){
		play_anim("fast_bite");

		player->be_bited();
        player->mordida_recebida(this->get_tamanho_base());
		//player->add_energia_alimento(-5.0);
		GuiManager::get_instance()->piscar_life();
	}
}
