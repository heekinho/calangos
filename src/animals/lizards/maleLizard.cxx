#include "maleLizard.h"
#include "simdunas.h"

#include "player.h"
#include "guiManager.h"

#define VEL_WALK 1000.0
#define VEL_RUN 5000.0

#define MAXDEGREE 100
#define PROBTHR 80

MaleLizard::MaleLizard(NodePath node) : Lizard(node){ init(); }
const double MaleLizard::BOBBING_WAITING_TIME = 3.0;

MaleLizard::~MaleLizard(){
	event_handler->remove_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this);
}

void MaleLizard::init() {
    Lizard::init();
    //bind_anims(node());
    last_bobbing_done = 0;
    waiting_player_decide = false;

    PT(AnimControl) ac = get_anim_control()->find_anim("fast_bite");
    if(ac != NULL) ac->set_play_rate(1.5);

    maleSymbol = window->load_model(*this, "models/lizards/symbols/male.png");
    maleSymbol.set_scale(2.0);
    float posZ = maleSymbol.get_z();
    maleSymbol.set_z(posZ + 100);
    maleSymbol.set_billboard_point_eye(0);

    set_gender(LizardGender::male);



    this->eat_thr = 0.3;
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
			if(player->lizard_gender != Player::young) set_action("fight", true);
		}
	}

	if(distance > (1.25 * flee_max_dist)*(1.25 * flee_max_dist)){
		set_action("walk", true);
	}
	if(is_action_active("flee") || this->get_energia() < 20){
		if(distance < flee_max_dist*flee_max_dist) flee();
		else {
			energia = 50;
			set_action("walk", true);
		}

		waiting_player_decide = false;
	}
	else if(is_action_active("fight")){
		/* Round One: FIGHT! */
		if(distance < eat_thr*eat_thr) bite();
		else chase();
	}
	else if(distance < bobbing_dist_thr*bobbing_dist_thr && !waiting_player_decide){
		/* Aqui se verifica as condições para começar uma briga */
		/* "Se o player tem femea próximo dele, e eu tow perto dele, logo tem femea perto de mim..."
		 * Evita-se assim ter que calcular toda santa hora as distâncias e etc. Só consulto a flag... */
		if(player->has_female_around() && player->lizard_gender != Player::young){
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

	float fight_prob = (this_lizard->get_tamanho_base() - (player->get_relative_size()*100)) / 2 + 40.0;

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
		this->move(VEL_WALK);
	}
}

void MaleLizard::chase(){
	//float distance = (player->get_pos() - get_pos()).length();
	float distance = get_distance_squared(*player);
	if(!has_other_anim_active("walk")){
		play_anim("walk");

		/* Comportamento */
		look_at(*player);  //TODO: Corrigir depois para não permitir muito giro.

		 if(distance > (eat_thr - (eat_thr / 10))*(eat_thr - (eat_thr / 10))) {
			 move(VEL_RUN);

		 }
	}

}

void MaleLizard::be_bited(){
	Lizard::be_bited();
	set_action("fight", true);
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
