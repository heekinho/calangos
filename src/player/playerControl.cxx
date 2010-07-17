#include "playerControl.h"

#include "player.h"
#include "pandaFramework.h"
#include "terrain.h"
#include "timeControl.h"
#include "objetoJogo.h"
#include "menu.h"

#include "femaleLizard.h"
#include "maleLizard.h"
#include "lizard.h"
#include "prey.h"


#define VEL_WALK 20.0
#define VEL_RUN 200.0
#define MAX_VEL_PLAYRATE 40.0

#define NORANG 1

#define DISTANCE_FEMALE 0.3
#define DISTANCE_MALE 0.2

// Inicializacao de non-integral type
const string PlayerControl::EV_player_move = "EV_PLAYERMOVE";
const string PlayerControl::EV_player_enter_toca = "EV_PLAYER_ENTER_TOCA";
const string PlayerControl::EV_player_outof_toca = "EV_PLAYER_OUTOF_TOCA";
const string PlayerControl::EV_player_bobbing = "EV_PLAYER_BOBBING";
const string PlayerControl::EV_player_reproducao = "EV_PLAYER_REPRODUCAO";

// Para Singleton
bool PlayerControl::instanceFlag = false;
PlayerControl* PlayerControl::single = NULL;

PlayerControl::~PlayerControl() {
	Simdunas::get_evt_handler()->remove_hooks_with(this);
	instanceFlag = false;
}

PlayerControl::PlayerControl() {
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, update, this);
	Simdunas::get_evt_handler()->add_hook(TimeControl::get_instance()->EV_segundo_real, event_female_next, this);

    indicator = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/indicator.png");
    indicator.set_scale(0.0005);
    indicator.set_billboard_point_eye(0);


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

	action = "mouse1";  	Simdunas::get_framework()->define_key("mouse1", "Player Bite", eat, this);
	action = "bite";  		Simdunas::get_framework()->define_key("space", "Player Bite", eat, this);
	action = "bobbing";  	Simdunas::get_framework()->define_key("b", "Bobbing", bobbing, this);
	action = "toca";   		Simdunas::get_framework()->define_key("t", "Toca Control", toca_control, this);
    action = "reproduzir";	Simdunas::get_framework()->define_key("r", "Reproduzir", reproducao, this);

	action = "pause"; 		Simdunas::get_framework()->define_key("escape", "Pause Game", chama_pause, this);

	//CHEATS
	action = "die";			Simdunas::get_framework()->define_key("control-m", "Easter Egg1", special_control, action);
	action = "grow-old";	Simdunas::get_framework()->define_key("control-o", "Easter Egg2", special_control, action);
	action = "info";		Simdunas::get_framework()->define_key("control-i", "Print Info", special_control, action);

}


void PlayerControl::special_control(const Event *theEvent, void *data){
	char *str=(char *)data;
	PT(Player) me=Player::get_instance();

	if(strcmp(str,"die")==0)
		me->set_energia(0);

	if(strcmp(str,"grow-old")==0)
		me->event_pmonth(NULL, me);

	if(strcmp(str,"info")==0){
		World::get_world()->get_terrain()->remove_all_edible_vegetals();
//		Vegetal::vegetals_placeholder.flatten_strong();
//		Simdunas::get_window()->get_render().analyze();
	}

	if(strcmp(str,"shift")==0) PlayerControl::get_instance()->key_map_player["shift"] = true;
	if(strcmp(str,"shift-up")==0) PlayerControl::get_instance()->key_map_player["shift"] = false;
}

void PlayerControl::reproducao(const Event*, void *data){
    Simdunas::get_evt_queue()->queue_event(new Event(PlayerControl::EV_player_reproducao));
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


void PlayerControl::calc_closest_object(){
	PT(Player) player = Player::get_instance();
	PT(Setor) player_sector = player->get_setor();
	if(!player_sector) return;

	/* Coloca os objetos em uma lista para comparar distâncias depois */
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
			if(current->get_distance_squared(ppos) < closest->get_distance_squared(ppos)){
				closest = current;
			}
		}
		if(!closest && current) closest = current;
	}

	/* Define o atributo para acesso futuro */
	this->closest_object = closest;
}

/*! Chamado a cada ciclo, verifica se tem tecla ativa no map, e executa a a��o
 * associada. Basicamente realiza movimento */
void PlayerControl::update(const Event*, void *data){
	PlayerControl* this_control = (PlayerControl*)data;

	PT(Player) p = Player::get_instance();

	/* Test */
	World::get_world()->get_terrain()->update_prey();

	/* Verifica se tem femeas por perto */
	p->update_female_around();

	bool fastturn = this_control->key_map_player["fastleft"] || this_control->key_map_player["fastright"] || this_control->key_map_player["shift"];
	bool rotatingleft  = this_control->key_map_player["left"] || this_control->key_map_player["fastleft"];
	bool rotatingright = this_control->key_map_player["right"] || this_control->key_map_player["fastright"];
	bool rotating = rotatingleft || rotatingright;

	/* Verifica as rotações do lagarto */
	int direction = 0;
	if(rotating){
		/* Define a direção do giro */
		if(rotatingleft) direction = 1;
		else if(rotatingright) direction = -1;
		else direction = 0;

		/* Efetua o Giro */
		p->set_h(p->get_h() + 2 * NORANG * direction * (fastturn?2:1));

		/* FIX: Conserta giro sobre o próprio eixo */
		if(!this_control->key_map_player["forward"]){
			if(fastturn) this_control->move(VEL_WALK / 2);
			else this_control->move(VEL_WALK / 4);
		}
	}

	/* Concretiza movimentos e roda animações */
	if(this_control->key_map_player["fastforward"] || this_control->key_map_player["shift"]){
		this_control->move(VEL_RUN);
		if(!p->get_anim_control()->is_playing("run")) p->get_anim_control()->loop("run", false);
		p->set_lagarto_correndo();
	}
	else if(this_control->key_map_player["forward"]){
		// Se for soh caminhando
		this_control->move(VEL_WALK);
		p->get_anim_control()->stop("run");

		p->set_lagarto_andando();
	}
	else if(rotating){
		this_control->move(0); //Gambi para rodar a animação
	}
	else {
		/* Lagarto est� parado */
		p->get_anim_control()->stop("run");
		p->get_anim_control()->stop("walk");
		//p->get_anim_control()->stop_all();

		p->set_lagarto_parado();
	}



	this_control->calc_closest_object();
	if(this_control->closest_object != NULL){
		this_control->indicator.set_pos(this_control->closest_object->get_pos());
		LPoint3f max, min;
		/* TODO: NÃO É PRA CALCULAR TODA HORA!!! É PRA ARMAZENAR ESSA INFORMAÇÃO! */
		this_control->closest_object->calc_tight_bounds(min, max);
		this_control->indicator.set_z(max.get_z()+0.01);
	}
}


void PlayerControl::move(float velocity){
	Player *p = Player::get_instance();

	if(!p->get_anim_control()->is_playing("fast_bite")){
		if(!p->get_anim_control()->is_playing("walk")) p->get_anim_control()->loop("walk", false);
		p->set_control_effect("walk", 1.0);
		p->set_control_effect("fast_bite", 0);
		p->set_control_effect("bobbing", 0);

		if(velocity <= VEL_WALK) p->get_anim_control()->find_anim("walk")->set_play_rate(1.0);
		else if(velocity > VEL_WALK) p->get_anim_control()->find_anim("walk")->set_play_rate(4.0);

		/* A Letargia influencia na velocidade (decidiu-se por influenciar linearmente */
		velocity = velocity * (1 - p->get_letargia());
		p->set_velocity(velocity);

		p->move(velocity*100);

		// Lancar o evento que moveu...
		Simdunas::get_evt_queue()->queue_event(new Event(PlayerControl::EV_player_move));
	}
}

struct EdibleInfo {
	PT(ObjetoJogo) object;
	int type;
	PT(Setor) sector; /* Necessário pois o player se move por um tempo */
};

/*! Efetua acao de comer. Verifica se tem algum npc em volta e come */
void PlayerControl::eat(const Event*, void *data){
	PlayerControl* this_control = (PlayerControl*) data;
	PT(Player) player = Player::get_instance();
	PT(Setor) player_sector = player->get_setor();

	if(player->get_anim_control()->is_playing("fast_bite")) return;

	/* Falha na ação comer por baixa temperatura */
	bool eat_fail = false;

	int range = (int) (player->get_temp_interna_ideal() - player->get_temp_interna_minlimite());
	int sorteio = rand()%range + player->get_temp_interna_minlimite();

	if(sorteio > player->get_temp_interna()) {
		nout << "Temperatura baixa - falha na ação de comer..." << endl;
		eat_fail = true;
		return;
	}
	/* ----------------------------------------- */


	/* Verifica a posição do mouse... Se estiver sobre a interface não executa a ação de comer */
	MouseWatcher *mwatcher = DCAST(MouseWatcher, Simdunas::get_window()->get_mouse().node());
	if(mwatcher->has_mouse() && mwatcher->get_mouse_x() < 0.57 && !TimeControl::get_instance()->get_stop_time()){


		/* 0: prey; 1: vegetal; 2: lizard */
		int type_of_closest = -1;

		/*! HACK para obter o tipo de objeto de closest */
		PT(ObjetoJogo) closest = this_control->closest_object;
		if(closest){
			if(dynamic_cast<Prey*>((ObjetoJogo*) closest)) type_of_closest = 0;
			if(dynamic_cast<EdibleVegetal*>((ObjetoJogo*) closest)) type_of_closest = 1;
			if(dynamic_cast<Lizard*>((ObjetoJogo*) closest)) type_of_closest = 2;
		}

		/* Se o tipo não for reconhecido, cai fora. Era pra fazer if, mas... */
		if(type_of_closest == -1) return;

		/* Configuração de distância. Quando os objetos estaram no raio de ação do player.*/
		float act_dist_thr = 0.20 * player->get_sx() * 1350;
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
		float angle_to_npc = player_to_target.angle_deg(player_y_versor);

		/* Ação de comer! */
		bool eatsuccess = false;
		if (type_of_closest == 0 || type_of_closest == 1) {

			/* Fazendo as presas fugirem no ataque do player */
			if(type_of_closest == 0){
				SectorItems<PT(Prey)>::iterator it;
				for(it = player_sector->preys()->begin(); it != player_sector->preys()->end(); ++it){
					PT(Prey) prey = *it;
					if(prey != NULL){
						if((prey->get_pos() - player->get_pos()).length() < act_dist_thr * 3){
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
				player->eat(food);
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
				Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, eating, (void *) info);

				eatsuccess = true;
			}
		}
		/* Morder outro lagarto */
		if (type_of_closest == 2) {
			Lizard* lizard = dynamic_cast<Lizard*>((ObjetoJogo*) closest);
			if (lizard->get_gender() == LizardGender::male) {
				MaleLizard* male_lizard = (MaleLizard*) lizard;

				if (dist_to_target < act_dist_thr) {
					male_lizard->be_bited();
					male_lizard->set_energia(male_lizard->get_energia() - 10);
				}
			}
		}


		/* Animação roda independente de comer ou não */
		if(!player->get_anim_control()->is_playing("fast_bite")){
			player->get_anim_control()->play("fast_bite");
			player->set_control_effect("walk", 0);
			player->set_control_effect("bobbing", 0);
			player->set_control_effect("fast_bite", 1.0);

			/* Se for uma mordida sem sucesso: -0.1 de energia */
			if(!eatsuccess) Player::get_instance()->add_energia_alimento(-0.1);
		}
	}
}

/*! Fica esperando o frame certo para comer */
void PlayerControl::eating(const Event* evt, void *data){
	PT(Player) player = Player::get_instance();

	int frame = player->get_anim_control()->get_frame("fast_bite");

	/* last_eating_frame > frame -- Corrige o loop da animação */
	if(frame > 40 || PlayerControl::get_instance()->last_eating_frame > frame){
		PlayerControl::really_eat(evt, data);
		Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, eating, (void *) data);
	}

	PlayerControl::get_instance()->last_eating_frame = frame;
}

//consolide_eating();
#include "groupPrey.h"
void PlayerControl::really_eat(const Event*, void *data){
	EdibleInfo* the_data = (EdibleInfo*) data;

	/* Exclui de fato o "objeto" comido */
	if(the_data->type == 0) {
		PT(Prey) cprey = dynamic_cast<Prey*>((ObjetoJogo*) the_data->object);
		//if(cprey->group != NULL) cprey->group->remove_prey(cprey);
		World::get_world()->get_terrain()->realoc_prey(cprey, Player::get_instance()->get_pos());
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
	Simdunas::get_evt_handler()->remove_hooks("a");
	Simdunas::get_evt_handler()->remove_hooks("q");
	Simdunas::get_evt_handler()->remove_hooks("s");
	Simdunas::get_evt_handler()->remove_hooks("w");
	Simdunas::get_evt_handler()->remove_hooks("d");
	Simdunas::get_evt_handler()->remove_hooks("e");

	Simdunas::get_evt_handler()->remove_hooks("a-up");
	Simdunas::get_evt_handler()->remove_hooks("q-up");
	Simdunas::get_evt_handler()->remove_hooks("s-up");
	Simdunas::get_evt_handler()->remove_hooks("w-up");
	Simdunas::get_evt_handler()->remove_hooks("d-up");
	Simdunas::get_evt_handler()->remove_hooks("e-up");

	Simdunas::get_evt_handler()->remove_hooks("mouse1");
	Simdunas::get_evt_handler()->remove_hooks("space");
	Simdunas::get_evt_handler()->remove_hooks("t");
	Simdunas::get_evt_handler()->remove_hooks("escape");
	Simdunas::get_evt_handler()->remove_hooks("m");

	single = NULL;
	instanceFlag = false;
}

void PlayerControl::toca_control(const Event*, void *data){


	PlayerControl* this_control = (PlayerControl*)data;
	float dist_toca = 0.3;
	PT(Player) player = Player::get_instance();

	if (!player->is_in_toca()){
		// Pede ao setor, o vetor que guarda as tocas.
		SectorItems<PT(ObjetoJogo)>* sector_tocas = player->get_setor()->tocas();
		SectorItems<PT(ObjetoJogo)>::iterator it;
		for(it = sector_tocas->begin(); it != sector_tocas->end(); ++it){
			PT(ObjetoJogo) toca = *it;
			LVector3f player_to_toca = player->get_pos() - toca->get_pos();
			if(player_to_toca.length() < dist_toca){
				toca->hide();
				player->set_in_toca(true);
				player->set_toca(toca);
				Simdunas::get_evt_queue()->queue_event(new Event(PlayerControl::EV_player_enter_toca));
				Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, update, this_control);
				return;
			}
		}
	}
	else {
		if(player->get_toca()) player->get_toca()->show();

		player->set_in_toca(false);
		player->set_toca(NULL);
		Simdunas::get_evt_queue()->queue_event(new Event(PlayerControl::EV_player_outof_toca));
		Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, update, this_control);
	}
}

void PlayerControl::bobbing(const Event*, void *data){
	Simdunas::get_evt_queue()->queue_event(new Event(PlayerControl::EV_player_bobbing));
	PT(Player) player = Player::get_instance();

	/* Roda animação Bobbing */
	if(!player->get_anim_control()->is_playing("bobbing")){
		player->get_anim_control()->play("bobbing");
		player->set_control_effect("walk", 0);
		player->set_control_effect("fast_bite", 0);
		player->set_control_effect("bobbing", 1.0);
	}
}

void PlayerControl::chama_pause(const Event*, void* data){

    Menu::get_instance()->pause_game();
}

void PlayerControl::morder(){
	//TODO: NPC piscar (ficar mais claro)
}

void PlayerControl::event_female_next(const Event *, void *data){
	PT(Player) player = Player::get_instance();

	if (Player::get_instance()->get_estado_reprodutivo()) {
		SectorItems<PT(Lizard)>* lizards = player->get_setor()->lizards();
		SectorItems<PT(Lizard)>::iterator it;
		for (it = lizards->begin(); it != lizards->end(); ++it) {
			PT(Lizard) npcf = *it;
			// e for fêmea e estiver próxima
			if((npcf->get_gender() == LizardGender::female) && (npcf->get_distance(player->get_pos()) < DISTANCE_FEMALE)){
				PT(FemaleLizard) female = (PT(FemaleLizard))((FemaleLizard*)(Lizard*) npcf);
				if(!female->reproduziu) female->set_frames_stopped(120);
			}
		}
	}
}
