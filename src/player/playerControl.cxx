#include "playerControl.h"

#include "player.h"
#include "geoMipTerrain.h"
#include "pandaFramework.h"
#include "terrain.h"
#include "timeControl.h"
#include "objetoJogo.h"

#include "femaleLizard.h"
#include "maleLizard.h"
#include "lizard.h"
#include "prey.h"
#include "pStatTimer.h"
#include "screen.h"
#include "inGameScreenManager.h"
#include "audioRepository.h"
#include "audioController.h"
#include "world.h"
#include "guiManager.h"
//#include "playerHealthSimulator.h"

/*! Define velocidade de rotação do player em Graus/Segundos.
 * NOTA: Quando em modo turbo (w), efetua o dobro do giro. */
#define ROTATIONSPEED 180

#define DISTANCE_FEMALE 0.3

// Inicializacao de non-integral type
const string PlayerControl::EV_player_move = "EV_PLAYERMOVE";
const string PlayerControl::EV_player_enter_toca = "EV_PLAYER_ENTER_TOCA";
const string PlayerControl::EV_player_outof_toca = "EV_PLAYER_OUTOF_TOCA";
const string PlayerControl::EV_player_bobbing = "EV_PLAYER_BOBBING";
const string PlayerControl::EV_player_reproducao = "EV_PLAYER_REPRODUCAO";

// Para Singleton
bool PlayerControl::instanceFlag = false;
PlayerControl* PlayerControl::single = NULL;
bool PlayerControl::wire_frame_terrain = false;
bool PlayerControl::mouse_on_button = false;
bool PlayerControl::click_bite_active = true;

PlayerControl::~PlayerControl() {
	event_handler->remove_hooks_with(this);
	instanceFlag = false;

	indicator.remove_node();
	line_indicator.remove_node();
	_female_indicator.remove_node();
	_toca_indicator.remove_node();
}


PlayerControl::PlayerControl() {
	_closest_biteable = NULL;
	_closest_female = NULL;
	_closest_toca = NULL;

	event_handler->add_hook(TimeControl::EV_pass_frame, update, this);
	event_handler->add_hook(TimeControl::get_instance()->EV_segundo_real, event_female_next, this);

    indicator = window->load_model(render, "models/indicator.png");
    indicator.find_texture("*")->set_wrap_u(Texture::WM_clamp);
    indicator.find_texture("*")->set_wrap_v(Texture::WM_clamp);
    indicator.set_billboard_point_eye(0);

    _female_indicator = indicator.copy_to(render);
    _toca_indicator = indicator.copy_to(render);

    indicator.set_scale(0.0005);
    _toca_indicator.set_scale(0.003);
    _female_indicator.set_scale(0.0005);

	// Define a flag de movimento do PC, e define o set de teclas a usar para movimento.
	key_map_player["left"] = false;
	key_map_player["fastleft"] = false;
	key_map_player["right"] = false;
	key_map_player["fastright"] = false;
	key_map_player["forward"] = false;
	key_map_player["fastforward"] = false;


	// Ouve os eventos de teclado para realizar movimento.
	//char *data;
	char* action;
	action = "left"; 		Simdunas::get_framework()->define_key("a", "Rotate Player Left", set_key, (void *) action);
							Simdunas::get_framework()->define_key("arrow_left", "Rotate Player Left", set_key, (void *) action);
							Simdunas::get_framework()->define_key("shift-arrow_left", "Rotate Player Left", set_key, (void *) action);
	action = "fastleft";    Simdunas::get_framework()->define_key("q", "Rotate Player Fast-Left", set_key, (void *) action);
	action = "forward";   	Simdunas::get_framework()->define_key("s", "Move Player Forward", set_key, (void *) action);
							Simdunas::get_framework()->define_key("arrow_up", "Rotate Player Left", set_key, (void *) action);
							Simdunas::get_framework()->define_key("shift-arrow_up", "Rotate Player Left", set_key, (void *) action);
	action = "fastforward"; Simdunas::get_framework()->define_key("w", "Run Player Forward", set_key, (void *) action);
	action = "right";     	Simdunas::get_framework()->define_key("d", "Rotate Player Right", set_key, (void *) action);
							Simdunas::get_framework()->define_key("arrow_right", "Run Player Forward", set_key, (void *) action);
							Simdunas::get_framework()->define_key("shift-arrow_right", "Rotate Player Left", set_key, (void *) action);
	action = "fastright";   Simdunas::get_framework()->define_key("e", "Rotate Player Fast Right", set_key, (void *) action);


	action = "left"; 		Simdunas::get_framework()->define_key("a-up", "Rotate Player Left", unset_key, (void *) action);
							Simdunas::get_framework()->define_key("arrow_left-up", "Rotate Player Left", unset_key, (void *) action);
	action = "fastleft";    Simdunas::get_framework()->define_key("q-up", "Rotate Player Fast-Left", unset_key, (void *) action);
	action = "forward";   	Simdunas::get_framework()->define_key("s-up", "Move Player Forward", unset_key, (void *) action);
							Simdunas::get_framework()->define_key("arrow_up-up", "Move Player Forward", unset_key, (void *) action);
	action = "fastforward"; Simdunas::get_framework()->define_key("w-up", "Run Player Forward", unset_key, (void *) action);
	action = "right";     	Simdunas::get_framework()->define_key("d-up", "Rotate Player Right", unset_key, (void *) action);
							Simdunas::get_framework()->define_key("arrow_right-up", "Rotate Player Right", unset_key, (void *) action);
	action = "fastright";   Simdunas::get_framework()->define_key("e-up", "Rotate Player Fast Right", unset_key, (void *) action);

	action = "shift";		Simdunas::get_framework()->define_key("shift", "SHIFT", special_control, action);
	action = "shift-up";	Simdunas::get_framework()->define_key("shift-up", "SHIFTUP", special_control, action);

	action = "mouse1";  	Simdunas::get_framework()->define_key("mouse1", "Player Bite", click_bite, this);
	action = "bite";  		Simdunas::get_framework()->define_key("space", "Player Bite", eat, this);
	action = "bobbing";  	Simdunas::get_framework()->define_key("b", "Bobbing", bobbing, this);
	action = "toca";   		Simdunas::get_framework()->define_key("t", "Toca Control", toca_control, this);
	//teclas para Ativa e desativa o wireframe no terreno e na folhagem
//	action = "wireFrameTerrain";   		Simdunas::get_framework()->define_key("n", "wireFrameTerrain", root_control, this);
//	action = "wireFrameFolhagem";   		Simdunas::get_framework()->define_key("m", "wireFrameFolhagem", folhagem_control, this);
    action = "reproduzir";	Simdunas::get_framework()->define_key("r", "Reproduzir", reproducao, this);

//	action = "pause"; 		Simdunas::get_framework()->define_key("escape", "Pause Game", chama_pause, this);

	//CHEATS
	action = "die";			Simdunas::get_framework()->define_key("control-m", "Easter Egg1", special_control, action);
	action = "grow-old";	Simdunas::get_framework()->define_key("control-o", "Easter Egg2", special_control, action);
	action = "info";		Simdunas::get_framework()->define_key("control-i", "Print Info", special_control, action);


	/* Bury Actions. Sem necessidade de perguntar a fase. Pergunta se possui a habilidade */
	if(player->has_bury_ability()){
		/* Configura input */
	    action = "bury";		Simdunas::get_framework()->define_key("k", "Enterrar-se", bury_action, this);
//	    action = "unbury";		Simdunas::get_framework()->define_key("l", "Desenterrar-se", unbury, this);

	    /* Configura evento de ação completa */
	    event_handler->add_hook("calangos-unbury-action-complete", unbury_action_complete, this);
	}
}

void PlayerControl::special_control(const Event *theEvent, void *data){
	char *str=(char *)data;
	PT(Player) me=player;

//	if(strcmp(str,"die")==0)
//		me->set_energy(0);

// crescer mais rápido
//	if(strcmp(str,"grow-old")==0)
//		me->event_pmonth(NULL, me);
		//me->player_health_simulator->event_pass_month(NULL, me);
		//PlayerHealthSimulator::event_pass_month(NULL, me);

	if(strcmp(str,"info")==0){
//		World::get_world()->get_terrain()->remove_all_edible_vegetals();
//		Vegetal::vegetals_placeholder.flatten_strong();
//		render.analyze();
//		render.ls();
//		me->get_anim_control()->write(simdunas_cat.debug());
//		render.ls();

		simdunas_cat.debug() << "Ideal Temperature: " << me->get_ideal_temperature() << endl;
	}

	if(strcmp(str,"shift")==0) PlayerControl::get_instance()->key_map_player["shift"] = true;
	if(strcmp(str,"shift-up")==0) PlayerControl::get_instance()->key_map_player["shift"] = false;
}

void PlayerControl::reproducao(const Event*, void *data){
    event_queue->queue_event(new Event(PlayerControl::EV_player_reproducao));
}

/*! Ativa determinada tecla no map */
void PlayerControl::set_key(const Event *theEvent, void *data) {
	char *key = (char *) data;
	PlayerControl::get_instance()->key_map_player[key] = true;
}

/*! Desativa determinada tecla no map */
void PlayerControl::unset_key(const Event *theEvent, void *data) {
	char *key = (char *) data;
	PlayerControl::get_instance()->key_map_player[key] = false;
}


/*! Verifica os objetos mais próximos do player */
void PlayerControl::calc_closest_objects(){
	/* Obtém as referencias do player e de seu setor */
	PT(Setor) player_sector = player->get_setor();
	if(!player_sector) return;

	/* Obtém o objeto "mordível" mais próximo */
	_closest_biteable = get_closest_biteable();
	_closest_toca = player_sector->tocas()->get_closest_to(player->get_pos());
	_closest_female = player->get_courted_female();
}

//PT(ObjetoJogo) PlayerControl::get_closest_f

PT(ObjetoJogo) PlayerControl::get_closest_biteable(){
	/* Obtém as referencias do player e de seu setor */
	PT(Setor) player_sector = player->get_setor();
	if(!player_sector) return NULL;

	/* Coloca os objetos em uma lista para comparar distâncias depois */
	/* TODO: Deveria iterar entre os setores vizinhos também, mas... */
	list<PT(ObjetoJogo)> action_objects;
	action_objects.push_back((PT(ObjetoJogo))player_sector->preys()->get_closest_to(player->get_pos()));
	action_objects.push_back((PT(ObjetoJogo))player_sector->edible_vegetals()->get_closest_to(player->get_pos()));
	action_objects.push_back((PT(ObjetoJogo))player_sector->lizards()->get_closest_to(player->get_pos()));

	/* Compara as distâncias */
	PT(ObjetoJogo) closest = NULL;
	list<PT(ObjetoJogo)>::iterator it;
	for(it = action_objects.begin(); it != action_objects.end(); ++it){
		PT(ObjetoJogo) current = *it;
		if(current && closest){
			LPoint3f ppos = player->get_pos();
			if(player->reaches(current) && current->get_distance_squared(ppos) < closest->get_distance_squared(ppos)){
				closest = current;
			}
		}
		if(!closest && current && player->reaches(current)) closest = current;
	}

	return closest;
}


/*! Apenas recebe o evento e encaminha para o método update (que não é estático) */
void PlayerControl::update(const Event*, void *data){
	((PlayerControl*)data)->update();
}

/*! Chamado a cada ciclo, verifica se tem tecla ativa no map, e executa a ação
 * associada. Basicamente realiza movimento */
void PlayerControl::update(){
	PT(Player) p = player;
	float dt = global_clock->get_dt();

#ifdef PSTATS
    PStatCollector ps=PStatCollector("Update_Play");
    PStatTimer t =PStatTimer(ps);
#endif

    /* Se o player estiver enterrado as ações seguintes não são executadas */
    if(p->is_buried()) return;

	/* Verifica se tem femeas por perto */
	p->update_female_around();

	/* Se o player foi capturado por algum animal não o deixa executar ações */
	if(p->was_captured()) return;

	bool fastturn = key_map_player["fastleft"] || key_map_player["fastright"] || key_map_player["shift"];
	bool rotatingleft  = key_map_player["left"] || key_map_player["fastleft"];
	bool rotatingright = key_map_player["right"] || key_map_player["fastright"];
	bool rotating = rotatingleft || rotatingright;

	/* Verifica as rotações do lagarto */
	int direction = 0;
	if(rotating && !p->get_anim_control()->is_playing("fast_bite")){
		/* Define a direção do giro */
		if(rotatingleft) direction = 1;
		else if(rotatingright) direction = -1;
		else direction = 0;

		/* Efetua o Giro */
		p->set_h(p->get_h() + direction*(dt * ROTATIONSPEED * (fastturn?2:1)));

		/* FIX: Conserta giro sobre o próprio eixo */
		if(!key_map_player["forward"]){
			if(fastturn) move(p->get_speed_walking() * 0.5);
			else move(p->get_speed_walking() * 0.25);
		}
	}

	/* Concretiza movimentos e roda animações */
	if(key_map_player["fastforward"] || key_map_player["shift"]){
		move(p->get_speed_running());
		p->set_lagarto_correndo();

		AudioController::get_instance()->running();
	}
	else if(key_map_player["forward"]){
		// Se for soh caminhando
		move(p->get_speed_walking());
		p->set_lagarto_andando();
		AudioController::get_instance()->stop_running();
	}
	else if(rotating){
		move(0); /* Gambi para rodar a animação */
		AudioController::get_instance()->stop_running();
	}
	else {
		/* Lagarto está parado */
		p->get_anim_control()->stop("walk");
		p->set_lagarto_parado();
		AudioController::get_instance()->stop_running();
	}


	//if(global_clock->get_frame_count()%10 == 0)
	calc_closest_objects();
	if(_closest_biteable){
		LPoint3f max, min;
		/* TODO: NÃO É PRA CALCULAR TODA HORA!!! É PRA ARMAZENAR ESSA INFORMAÇÃO! */
		//closest_object->calc_tight_bounds(min, max);
		_closest_biteable->calc_tight_bounds(min, max);

		indicator.set_pos(_closest_biteable->get_pos());
		indicator.set_z(max.get_z() + 0.01);
		indicator.unstash();
	}
	else indicator.stash();

	/* Condição deveria estar em um método comum com entrar na toca, mas... */
	if(_closest_toca && p->get_distance_squared(*_closest_toca) < p->get_toca_thr()*p->get_toca_thr()){
		_toca_indicator.set_pos(_closest_toca->get_pos());
		_toca_indicator.set_z(_toca_indicator.get_z() + 0.15);
		_toca_indicator.unstash();
	}
	else _toca_indicator.stash();


	if(_closest_female){
		_female_indicator.set_pos(_closest_female->get_pos());
		LPoint3f max, min;
		/* TODO: NÃO É PRA CALCULAR TODA HORA!!! É PRA ARMAZENAR ESSA INFORMAÇÃO! */
		//closest_object->calc_tight_bounds(min, max);
		_closest_female->calc_tight_bounds(min, max);
		_female_indicator.set_z(max.get_z() + 0.01);
		_female_indicator.unstash();
	}
        
	else _female_indicator.stash();

#ifdef PSTATS
        t.~PStatTimer();
#endif
       
}

void PlayerControl::move(float velocity){
	Player *p = player;

	if(!p->get_anim_control()->is_playing("fast_bite")){
		p->loop_anim("walk");

		/* A Letargia influencia na velocidade (decidiu-se por influenciar linearmente */
//		velocity = velocity * (1 - p->get_letargia());
//		p->set_velocity(velocity);
//		p->move(velocity*100);

		/*Multiplicador (*100) retirado desse método e acrescentado no método Player::get_speed_walking
		 * Porém, playrate  é calculado com velocity sem o multiplicador*/
		p->move(velocity);

		/* O playrate deve variar de acordo com a velocidade final*/
//		if(velocity <= VEL_WALK) p->get_anim_control()->find_anim("walk")->set_play_rate(1.0);
//		else if(velocity > VEL_WALK) p->get_anim_control()->find_anim("walk")->set_play_rate(4.0);

		float playrate = velocity; //Velocity dividida pelo multiplicador
		if(playrate > 5) playrate = 5;
		if(velocity <= 0) playrate = 2;
		p->get_anim_control()->find_anim("walk")->set_play_rate(playrate);

		/* Lancar o evento que moveu... */
		event_queue->queue_event(new Event(PlayerControl::EV_player_move));
	}
}

struct EdibleInfo {
	PT(ObjetoJogo) object;
	int type;
	PT(Setor) sector; /* Necessário pois o player se move por um tempo */
};

void PlayerControl::set_click_bite_active(bool active) {
	click_bite_active = active;
}

void PlayerControl::click_bite(const Event *evt, void *data){
	if (click_bite_active || !Session::get_instance()->mouse_on_screen) {
		Session::get_instance()->mouse_on_screen = true;
		eat(evt, data);
	}
}

/*! Efetua acao de comer. Verifica se tem algum npc em volta e come */
void PlayerControl::eat(const Event *evt, void *data){
	/* Verifica a posição do mouse... Se estiver sobre a interface não executa a ação de comer */
	//MouseWatcher *mwatcher = DCAST(MouseWatcher, window->get_mouse().node());
	//if(!(mwatcher->has_mouse() && mwatcher->get_mouse_x() < 0.57 && !TimeControl::get_instance()->get_stop_time())) return;

	if (!evt->get_name().compare("mouse1") && PlayerControl::mouse_on_button) return;

	if (TimeControl::get_instance()->get_stop_time()) return;

	PlayerControl* this_control = (PlayerControl*) data;
	PT(Setor) player_sector = player->get_setor();

	/* Animação roda independente de comer ou não */
	if(!player->get_anim_control()->is_playing("fast_bite")) player->play_anim("fast_bite");
	else return;

	/* Falha na ação comer por baixa temperatura */
	bool eat_fail = false;

	int range = (int) (player->get_ideal_temperature() - player->get_min_temperature());
	int sorteio = rand()%range + player->get_min_temperature();

	if(sorteio > player->get_temperature()) {
		simdunas_cat.debug() << "Temperatura baixa - falha na ação de comer..." << endl;
		event_handler->add_hook(TimeControl::EV_pass_frame, missed_bite, NULL);
		eat_fail = true;
		player->add_food_energy(-0.1);
		player->get_achievements()->clear_bites();
		return;
	}
	/* ----------------------------------------- */

	/* 0: prey; 1: vegetal; 2: lizard */
	int type_of_closest = -1;

	/*! HACK para obter o tipo de objeto de closest */
	//PT(ObjetoJogo) closest = this_control->closest_object;
	PT(ObjetoJogo) closest = this_control->_closest_biteable;
	if(closest){
		if(dynamic_cast<Prey*>((ObjetoJogo*) closest)) type_of_closest = 0;
		if(dynamic_cast<EdibleVegetal*>((ObjetoJogo*) closest)) type_of_closest = 1;
		if(dynamic_cast<Lizard*>((ObjetoJogo*) closest)) type_of_closest = 2;
	}

	/* Se o tipo não for reconhecido, cai fora. Era pra fazer if, mas... */
	if(type_of_closest == -1) {
		event_handler->add_hook(TimeControl::EV_pass_frame, missed_bite, NULL);
		simdunas_cat.debug()<<"tipo de alimento não reconhecido?"<<endl;
		player->get_achievements()->clear_bites();
		return;
	}

	/* Configuração de distância. Quando os objetos estaram no raio de ação do player.*/
	float act_dist_thr = player->get_eat_radius_thr();
	int direction_eat_thr = 45;

	/* Obtem o "versor y" do player */
	LVector3f player_y_versor = player->get_net_transform()->get_mat().get_row3(1);
	player_y_versor.normalize();

	/* Obtem distancia para o npc */
	/* HACK para consertar um offset maluco dos frutos */
	LVector3f player_to_target = LPoint3f(player->get_x(), player->get_y(), 0) - LPoint3f(closest->get_x(), closest->get_y(), 0);
	float dist_to_target = player_to_target.length();

	/* Obtem angulo para o npc */
	player_to_target.normalize();
	float angle_to_npc = fabs(player_to_target.angle_deg(player_y_versor));

	/* Ação de comer! */
	bool eatsuccess = false;
	if (type_of_closest == 0 || type_of_closest == 1) {

		/* Fazendo as presas fugirem no ataque do player */
		if(type_of_closest == 0){
			SectorItems<PT(Prey)>::iterator it;
			for(it = player_sector->preys()->begin(); it != player_sector->preys()->end(); ++it){
				PT(Prey) prey = *it;
				if(prey != NULL){
					//if((prey->get_pos() - player->get_pos()).length() < act_dist_thr * 3){
					if(prey->get_distance_squared(*player)<(act_dist_thr*3)*(act_dist_thr*3)){
						prey->set_fleing(true);
						TimeControl::get_instance()->notify_after_n_vminutes(50, Prey::stop_flee, prey);
					}
				}
			}
		}


		Edible* food = dynamic_cast<Edible*>((ObjetoJogo*) closest);
		/* Verifica se o ângulo esta dentro do limiar estabelecido, evitando os "já comidos" */
		if (dist_to_target < act_dist_thr && angle_to_npc < direction_eat_thr && food->get_nutritional_value() > 0) {

			// Pisca life indicando que obteve sucesso!!
			GuiManager::get_instance()->piscar_life();

			/* Come o alvo saúde */
			if(type_of_closest == 0 && dynamic_cast<Prey*>((ObjetoJogo*)closest)->get_tag("model_name").compare("formiga") == 0){
				player->eat(food, 0);
			}
			else if(type_of_closest == 1) player->eat(food, 1);
			else player->eat(food, 2);

			/* Com a redistribuição dos animais não pode zera-los */
			if(type_of_closest == 1){
				food->set_nutritional_value(0);
				food->set_hydration_value(0);
			}

			/* Monta a informação do objeto comestível */
			EdibleInfo* info = new EdibleInfo();
			info->object = closest;
			info->type = type_of_closest;
			info->sector = player->get_setor();

			//LVecBase3f *mydata = new LVecBase3f(index_of_closest, player->get_setor()->get_indice(), type_of_closest);
			//TimeControl::get_instance()->notify_after_n_frames(40, really_eat, (void*) mydata);

			this_control->last_eating_frame = 0;
			event_handler->add_hook(TimeControl::EV_pass_frame, eating, (void *) info);

			eatsuccess = true;
			player->get_achievements()->inc_bites();
		}
	}

	/* Morder outro lagarto */
	if (type_of_closest == 2) {
		Lizard* lizard = dynamic_cast<Lizard*>((ObjetoJogo*) closest);
		if (lizard->is_male()) {
			MaleLizard* male_lizard = (MaleLizard*) lizard;

//			if (dist_to_target < act_dist_thr) {
			/*Multiplicação por um fator de 3 como é feito com  a presas, somente o act_dist_thr
			 * dificilmente o player acertava um ataque*/
			if (dist_to_target < act_dist_thr*3) {

				male_lizard->be_bited(player->get_relative_size());
				simdunas_cat.debug()<<"Relative: "<<player->get_relative_size()<<endl;
			}
		}
	}

	/* Se for uma mordida sem sucesso: -0.1 de energia */
	if(!eatsuccess) player->add_food_energy(-0.1);
}

/*! Fica esperando o frame certo para comer */
void PlayerControl::eating(const Event* evt, void *data){
	int frame = player->get_anim_control()->get_frame("fast_bite");

	/* last_eating_frame > frame -- Corrige o loop da animação */
	if(frame > 40 || PlayerControl::get_instance()->last_eating_frame > frame){
		PlayerControl::really_eat(evt, data);
		event_handler->remove_hook(TimeControl::EV_pass_frame, eating, (void *) data);
	}

	PlayerControl::get_instance()->last_eating_frame = frame;
}

void PlayerControl::missed_bite(const Event* evt, void *data){
	int frame = player->get_anim_control()->get_frame("fast_bite");

	/* last_eating_frame > frame -- Corrige o loop da animação */
	if(frame > 40 || PlayerControl::get_instance()->last_eating_frame > frame){
		AudioController::get_instance()->only_play(AudioRepository::BITE_FAIL);
		event_handler->remove_hook(TimeControl::EV_pass_frame, missed_bite, data);
	}

}

//consolide_eating();
#include "groupPrey.h"
void PlayerControl::really_eat(const Event*, void *data){
	AudioController::get_instance()->only_play(AudioRepository::BITE);

	EdibleInfo* the_data = (EdibleInfo*) data;

	/* Exclui de fato o "objeto" comido */
	if(the_data->type == 0) {
		PT(Prey) cprey = dynamic_cast<Prey*>((ObjetoJogo*) the_data->object);
		if(cprey->_group) cprey->_group->remove_prey(cprey);
		Prey::redistributer->realoc_prey(cprey, player->get_pos());
	}
	else if(the_data->type == 1) {
		PT(EdibleVegetal) vegetal = dynamic_cast<EdibleVegetal*>((ObjetoJogo*) the_data->object);
		the_data->object->get_setor()->edible_vegetals()->remove(vegetal);
//		objects->at(index) = NULL;
//		objects->erase(objects->begin() + index);
	}

	delete the_data;
}


PlayerControl* PlayerControl::get_instance() {
	if(!instanceFlag) {
        single = new PlayerControl();
        instanceFlag = true;
    }
    return single;
}

void PlayerControl::unload_player_control(){

	// TODO: Consertar isso, por enquanto para testes.
	event_handler->remove_hooks("a");
	event_handler->remove_hooks("q");
	event_handler->remove_hooks("s");
	event_handler->remove_hooks("w");
	event_handler->remove_hooks("d");
	event_handler->remove_hooks("e");

	event_handler->remove_hooks("a-up");
	event_handler->remove_hooks("q-up");
	event_handler->remove_hooks("s-up");
	event_handler->remove_hooks("w-up");
	event_handler->remove_hooks("d-up");
	event_handler->remove_hooks("e-up");

	event_handler->remove_hooks("mouse1");
	event_handler->remove_hooks("space");
	event_handler->remove_hooks("t");
	//event_handler->remove_hooks("escape");
	event_handler->remove_hooks("m");

	single = NULL;
	instanceFlag = false;
}

void PlayerControl::toca_control(const Event*, void *data){
	PlayerControl* this_control = (PlayerControl*)data;

	if (!player->is_in_toca()){
		// Pede ao setor, o vetor que guarda as tocas.
		SectorItems<PT(ObjetoJogo)>* sector_tocas = player->get_setor()->tocas();
		SectorItems<PT(ObjetoJogo)>::iterator it;
		for(it = sector_tocas->begin(); it != sector_tocas->end(); ++it){
			PT(ObjetoJogo) toca = *it;
			LVector3f player_to_toca = player->get_pos() - toca->get_pos();
			if(player_to_toca.length() < player->get_toca_thr()){
				toca->stash();
				player->set_in_toca(true);
				player->set_toca(toca);
				event_queue->queue_event(new Event(PlayerControl::EV_player_enter_toca));
				event_handler->remove_hook(TimeControl::EV_pass_frame, update, this_control);
				return;
			}
		}
	}
	else {
		if(player->get_toca()) player->get_toca()->unstash();

		player->set_in_toca(false);
		player->set_toca(NULL);
		event_queue->queue_event(new Event(PlayerControl::EV_player_outof_toca));
		event_handler->add_hook(TimeControl::EV_pass_frame, update, this_control);
	}
}



void PlayerControl::root_control(const Event*, void *data){


    if(wire_frame_terrain){
	World::get_world()->get_terrain()->get_root().clear_render_mode();
	wire_frame_terrain = false;
    }else{
	World::get_world()->get_terrain()->get_root().set_render_mode_wireframe();
	wire_frame_terrain = true;
    }

}

void PlayerControl::bobbing(const Event*, void *data){
	event_queue->queue_event(new Event(PlayerControl::EV_player_bobbing));
	if(Session::get_instance()->get_player_death_status() == Player::PDT_NOT_DEAD ){
		/* Roda animação Bobbing */
		player->play_anim("bobbing");

		AudioController::get_instance()->bobbing();

	}

}

void PlayerControl::event_female_next(const Event *, void *data){
	if (player->get_estado_reprodutivo()) {
		SectorItems<PT(Lizard)>* lizards = player->get_setor()->lizards();
		SectorItems<PT(Lizard)>::iterator it;
		for (it = lizards->begin(); it != lizards->end(); ++it) {
			PT(Lizard) npcf = *it;
			// e for fêmea e estiver próxima
			if((npcf->is_female()) && (npcf->get_distance_squared(player->get_pos()) < DISTANCE_FEMALE*DISTANCE_FEMALE)){
				PT(FemaleLizard) female = (PT(FemaleLizard))((FemaleLizard*)(Lizard*) npcf);
				if(!female->reproduziu) female->set_frames_stopped(120);
			}
		}
	}
}

/*! Completa a ação de desenterrar do lagarto, invertendo o estado */
void PlayerControl::unbury_action_complete(const Event*, void* data){
	player->set_buried(false);
}

/*! Faz com que o lagarto se enterre na areia */
void PlayerControl::fadeout(){
	_bury_interval = new CLerpNodePathInterval("bury interval", 1, CLerpInterval::BT_no_blend, true, false, *player, NodePath());
	_bury_interval->set_end_pos(player->get_pos(render) - LVecBase3f(0, 0, player->get_height() * 0.55));
	_bury_interval->start();
}

/*! Faz com que o lagarto se desenterre da areia */
void PlayerControl::fadein(){
	/* Cria um interval para fazer o fading da ação de se enterrar */
	_bury_interval = new CLerpNodePathInterval("bury interval", 1, CLerpInterval::BT_no_blend, true, false, *player, NodePath());
	_bury_interval->set_done_event("calangos-unbury-action-complete");
	_bury_interval->set_end_pos(player->get_pos(render) + LVecBase3f(0, 0, player->get_height() * 0.55));
	_bury_interval->start();
}

void PlayerControl::bury_action(const Event*, void* data){
	((PlayerControl*)data)->bury_action();
}

void PlayerControl::bury_action(){
	/* Se já está executando o interval, não permitir nova execução */
	if(_bury_interval && _bury_interval->is_playing()) return;

	if(!player->is_buried()){
		/* Parar animações */
		player->get_anim_control()->stop_all();

		/* Fade out */
		fadeout();

		/* Já pode considerar o player enterrado */
		player->set_buried(true);
	}
	else {
		/* Faz o fading e só considera o player desenterrado quando acabar o fading */
		fadein();
	}
}
