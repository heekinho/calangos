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


#define VEL_WALK 20.0
#define VEL_RUN 200.0
#define MAX_VEL_PLAYRATE 40.0

#define NORANG 1

#define DISTANCE_FEMALE 0.2
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

	// Define a flag de movimento do PC, e define o set de teclas a usar para movimento.
	bool is_moving = false;
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

}

void PlayerControl::special_control(const Event *theEvent, void *data){
	char *str=(char *)data;
	PT(Player) me=Player::get_instance();

	if(strcmp(str,"die")==0)
		me->set_energia(0);

	if(strcmp(str,"grow-old")==0)
		me->event_pmonth(NULL, me);

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

/*! Chamado a cada ciclo, verifica se tem tecla ativa no map, e executa a a��o
 * associada. Basicamente realiza movimento */
void PlayerControl::update(const Event*, void *data){
	PlayerControl* this_control = (PlayerControl*)data;

	PT(Player) p = Player::get_instance();

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
}


void PlayerControl::move(float velocity){
	Player *p = Player::get_instance();
	float elapsed = TimeControl::get_instance()->get_elapsed_time();


	if(!p->get_anim_control()->is_playing("fast_bite")){
		if(!p->get_anim_control()->is_playing("walk")) p->get_anim_control()->loop("walk", false);
		p->set_control_effect("walk", 1.0);
		p->set_control_effect("fast_bite", 0);
		p->set_control_effect("bobbing", 0);

		if(velocity <= VEL_WALK) p->get_anim_control()->find_anim("walk")->set_play_rate(1.0);
		else if(velocity > VEL_WALK) p->get_anim_control()->find_anim("walk")->set_play_rate(4.0);



		//TODO: Consertar a maneira que � feita as altera��es de velocidade.
		/* A Letargia influencia na velocidade (decidiu-se por influenciar linearmente */
		velocity = velocity * (1 - p->get_letargia());
		p->set_velocity(velocity);
		//nout << "Letargia: " << p->get_letargia() << " - Velocidade: " << velocity << endl;

		p->move(velocity*100);

		// Lancar o evento que moveu...
		Simdunas::get_evt_queue()->queue_event(new Event(PlayerControl::EV_player_move));
	}
}


/*! Efetua acao de comer. Verifica se tem algum npc em volta e come */
void PlayerControl::eat(const Event*, void *data){
	PlayerControl* this_control = (PlayerControl*) data;
	PT(Player) player = Player::get_instance();

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
		/* Distancia em coordenadas "reais" */
		float dist_eat_thr = 0.20;
		/* Dire��o para ambos os lados a partir do versor y do transform do player */
		int direction_eat_thr = 45;

		/* Obtem uma referencia do player e obtem ser "versor y" */

		LVector3f player_y_versor = player->get_net_transform()->get_mat().get_row3(1);
		player_y_versor.normalize(); //Transformando em versor.
		//nout << "Player: " << player->get_pos() << endl;


		//TODO: Utilizar padrao STL.
		/* Pede ao setor, o vetor que guarda as presas. */
		vector<PT(Animal)> *sector_animals = player->get_setor()->get_animals();
		//nout << "Quantidade de animais: " << sector_animals.size() << endl;


		/* Se não obteve sucesso em comer tira 0.1 de energia */
		bool eatsuccess = false;

		for (int i = 0; i < sector_animals->size(); i++) {
			PT(Animal) npc = sector_animals->at(i);
			LVector3f player_to_npc = player->get_pos() - npc->get_pos();

			/* Obt�m a dist�ncia "real" do player ao npc e verifica se est� dentro do limiar */
			if ( player_to_npc.length() < dist_eat_thr ) {
				/* Normaliza o vetor para trabalhar com versores corretamente */
				player_to_npc.normalize();

				/* Verifica se o angulo esta dentro do limiar estabelecido, evitando os "já comidos" */
				if( player_to_npc.angle_deg(player_y_versor) < direction_eat_thr && npc->get_valor_nutricional() > 0){
					nout << player_to_npc.angle_deg(player_y_versor) << endl;


					//pisca life indicando que obteve sucesso!!
					GuiManager::get_instance()->piscar_life();

					/* Atualiza saúde */
					Player::get_instance()->eat(npc);
					nout << "Saude: " << Player::get_instance()->get_energia() << endl;
					nout << "Hidratação: " << Player::get_instance()->get_hidratacao() << endl;
					npc->set_valor_nutricional(0);
					npc->set_valor_hidratacao(0);

					LVecBase2f *mydata = new LVecBase2f(i, player->get_setor()->get_indice());
					//TimeControl::get_instance()->notify_after_n_frames(40, really_eat, (void*) mydata);

					this_control->last_eating_frame = 0;
					Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_frame, eating, (void *) mydata);

					eatsuccess = true;

				}
			}
		}

		if(!eatsuccess) {
			vector<PT(EdibleVegetal)> *sector_edible_vegetals = player->get_setor()->get_edible_vegetals();
			for (int i = 0; i < sector_edible_vegetals->size(); i++) {
				PT(EdibleVegetal) npc = sector_edible_vegetals->at(i);
				LVector3f player_to_npc = player->get_pos() - npc->get_pos();

				/* Obt�m a dist�ncia "real" do player ao npc e verifica se est� dentro do limiar */
				if ( player_to_npc.length() < dist_eat_thr ) {
					npc->hide();

					GuiManager::get_instance()->piscar_life();
					Player::get_instance()->eat(npc);
					nout << "Saude: " << Player::get_instance()->get_energia() << endl;
					nout << "Hidratação: " << Player::get_instance()->get_hidratacao() << endl;

					//destruir fruto
					sector_edible_vegetals->at(i) = NULL;
					sector_edible_vegetals->erase(sector_edible_vegetals->begin()+i);

				}

			}
		}

		/* Morder outro lagarto */
		if(!eatsuccess){
			vector<PT(Lizard)>* lizards = player->get_setor()->get_lizards();
			for(int i = 0; i < lizards->size(); i++){
				Lizard* lizard = lizards->at(i);
				if(lizard->get_gender() == LizardGender::male){
					MaleLizard* male_lizard = (MaleLizard*) lizard;

					/*TODO: Parametrizar e pegar o angulo depois */
					if((player->get_pos() - male_lizard->get_pos()).length() < 0.2){
						male_lizard->be_bited();
						male_lizard->set_energia(male_lizard->get_energia() - 3);
					}
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
void PlayerControl::really_eat(const Event*, void *data){
	LVecBase2f* the_pair = (LVecBase2f*) data;

	vector<PT(Animal)> *animals = World::get_default_world()->get_terrain()->get_setor(the_pair->get_y())->get_animals();
	animals->erase(animals->begin() + the_pair->get_x());
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

	if (!player->is_in_toca())
	{
		// Pede ao setor, o vetor que guarda as tocas.
		vector<PT(ObjetoJogo)> *sector_tocas = player->get_setor()->get_tocas();

		for(int i = 0; i < sector_tocas->size(); i++){
			PT(ObjetoJogo) toca = sector_tocas->at(i);
			LVector3f player_to_toca = player->get_pos() - toca->get_pos();
			if(player_to_toca.length() < dist_toca){
				toca->hide();
				player->set_in_toca(true);
				player->set_toca_index(i);
				Simdunas::get_evt_queue()->queue_event(new Event(PlayerControl::EV_player_enter_toca));
				Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_frame, update, this_control);
				return;
			}
		}
	}
	else
	{
		int toca_index = player->get_toca_index();
		if (toca_index != -1)
			player->get_setor()->get_tocas()->at(toca_index)->show();

		player->set_in_toca(false);
		player->set_toca_index(-1);
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

	if(Player::get_instance()->get_estado_reprodutivo()){

		PlayerControl *player_control = (PlayerControl*) data;
		vector<PT(Lizard)> *sector_lizards = Player::get_instance()->get_setor()->get_lizards();


		for (int i = 0; i < sector_lizards->size(); i++) {
			PT(Lizard) npcf = sector_lizards->at(i);
			//se for fêmea e estiver próxima
			if((npcf->get_gender() == 1) && ((Player::get_instance()->get_pos() - npcf->get_pos()) < DISTANCE_FEMALE)){
				for (int i = 0; i < sector_lizards->size(); i++) {
					PT(Lizard) npcm = sector_lizards->at(i);
					//se for macho e estiver próximo
					if((npcm->get_gender() == 0) && ((Player::get_instance()->get_pos() - npcm->get_pos()) < DISTANCE_MALE)){
						npcm->fight();
					}
				}
			}
		}
	}
}
