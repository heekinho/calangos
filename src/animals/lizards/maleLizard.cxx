#include "maleLizard.h"
#include "simdunas.h"

#include "player.h"
#include "guiManager.h"

#define PLAYERWAITING 60
#define VEL_WALK 5.0
#define VEL_RUN 50.0

#define MAXDEGREE 100
#define PROBTHR 80

MaleLizard::MaleLizard(NodePath node) : Lizard(node){ init(); }

MaleLizard::MaleLizard(const string &model) : Lizard(model){ init();
}

MaleLizard::~MaleLizard(){
	Simdunas::get_evt_handler()->remove_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this);
}

void MaleLizard::init() {
    Lizard::init();
    //bind_anims(node());
    player_decision_counter = PLAYERWAITING;
    waiting_player_decide = false;

    PT(AnimControl) ac = get_anim_control()->find_anim("fast_bite");
    if(ac != NULL) ac->set_play_rate(1.5);

    maleSymbol = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/lizards/symbols/male.png");
    maleSymbol.reparent_to(*this);
    maleSymbol.set_scale(2.0);
    float posZ = maleSymbol.get_z();
    maleSymbol.set_z(posZ + 100);
    maleSymbol.set_billboard_point_eye(0);

    set_gender(LizardGender::male);


}

void MaleLizard::act(){
	PT(Player) player = Player::get_instance();

	float bobbing_dist_thr = 3;
	float eat_thr = 0.05;
	float distance = (player->get_pos() - get_pos()).length();

	if(player_decision_counter > 0) player_decision_counter--;
	//if(player_decision_counter > 0) nout << player_decision_counter-- << endl;


	if(is_action_active("flee") || (player_decision_counter == 0 && waiting_player_decide == true) || energia < 20){
		flee();
		waiting_player_decide = false;
	}
	else if(is_action_active("fight")){
		/* Round One: FIGHT! */
		if(distance < eat_thr) bite();
		else chase();
	}
	else if(distance < bobbing_dist_thr && player_decision_counter == 0){
		bob();
		/* Espera o bobbing do player por X frames */
		waiting_player_decide = true;
		player_decision_counter = PLAYERWAITING;
		Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this);
	}
	else {
		set_action("walk");
		play_action_anims(true);

		Animal::act();
	}
}


void MaleLizard::player_did_bobbing(const Event *theEvent, void *data){
	MaleLizard* this_lizard = (MaleLizard*) data;
	PT(Player) player = Player::get_instance();

	Simdunas::get_evt_handler()->remove_hook(PlayerControl::EV_player_bobbing, player_did_bobbing, (void *) this_lizard);

	this_lizard->waiting_player_decide = false;
	this_lizard->player_decision_counter = 0;

	float fight_prob = (this_lizard->get_tamanho_base() - player->get_tamanho_base())/2 + 40.0;

	if(rand()%100 < fight_prob){
            this_lizard->set_action("fight", true);
    }
	else{
            this_lizard->set_action("flee", true);
     }

}

void MaleLizard::flee(){
	PT(Player) player = Player::get_instance();

	if(!has_other_anim_active("walk")){
		if(!get_anim_control()->is_playing("walk")) get_anim_control()->play("walk");

		/* Comportamento */
		look_at(*player);  //TODO: Corrigir depois para não permitir muito giro.
		set_h(*this,0); // Corrige modelo errado

		//move(0.02);
		this->move(VEL_RUN);
	}

}

void MaleLizard::bob(){
	//set_action("bobbing");
	//play_action_anims();
	if(!get_anim_control()->is_playing("bobbing")) get_anim_control()->play("bobbing");
}

void MaleLizard::wander(){
	float elapsed = TimeControl::get_instance()->get_elapsed_time();
	if(acting && !stay_quiet()){
		if(rand()%PROBTHR == 34) set_h(*this, rand()%MAXDEGREE - (MAXDEGREE/2));
		this->move(VEL_WALK);
	}

}

void MaleLizard::chase(){
	PT(Player) player = Player::get_instance();

	if(!has_other_anim_active("walk")){

		if(!get_anim_control()->is_playing("walk")){
			//set_action("walk");
			//play_action_anims();
			get_anim_control()->play("walk");
		}

		/* Comportamento */
		look_at(*player);  //TODO: Corrigir depois para não permitir muito giro.
		set_h(*this, 180); // Corrige modelo errado

		move(VEL_RUN);
	}

}

void MaleLizard::bite(){
	/* Manter simples por enquanto */
	if(!get_anim_control()->is_playing("fast_bite")){
		//set_action("fast_bite");
		//play_action_anims();
		//get_anim_control()->stop_all();
		get_anim_control()->play("fast_bite");

		Player::get_instance()->be_bited();
                Player::get_instance()->mordida_recebida(this->get_tamanho_base());
		//Player::get_instance()->add_energia_alimento(-5.0);
		//GuiManager::get_instance()->piscar_life();
	}
}
