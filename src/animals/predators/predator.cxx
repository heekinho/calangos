#include "predator.h"
#include "player.h"

#include "flyingPredator.h"
#include "modelRepository.h"

#include "collision.h"
#include "antialiasAttrib.h"
#include "audioController.h"
#include "animal.h"

bool Predator::pursuing = false;

float Predator::dist_player_hide = 3.5*3.5;
float Predator::dist_to_hunt = 10*10;
float Predator::dist_to_bite = 0.3;

/*! Constrói um Predador */



Predator::Predator(NodePath node, Predator::types_predator type) : Animal(node){
	set_velocity(350.0);
	//adiciona solido de colisão aos predadores (ficou legal esses valores para altura e raio)
	collision::get_instance()->collisionNpcFast(&node, 0, 0, 20, 10);

	//Tipo de predador
	type_predator = Predator::get_predator_type(type);
	set_tipo_predator_enum(type);

	//Presa
//	this->prey = NULL;

	//Estado inicial do predador
	act_state = Predator::walking;
	hunting_lizard = false;
	hunting_player = false;
	closest_to_player = false;

	event_handler->add_hook(TimeControl::EV_segundo_real, event_psegundo_change_state, this);


	/*TODO Ajustar a distancia para perserguir e para atacar a depender do tipo de predador*/
	// eat_thr original = 0.3
	//distance_pursuit original = 10
	switch(type){
		case(Predator::teiu):
										this->set_distance_pursuit(10);
		this->set_distance_bite(0.3);
		break;
		case(Predator::siriema):
										this->set_distance_pursuit(10);
		this->set_distance_bite(0.3);
		break;
		case(Predator::gato):
										this->set_distance_pursuit(10);
		this->set_distance_bite(0.3);
		break;
		case(Predator::raposa):
										this->set_distance_pursuit(10);
		this->set_distance_bite(0.3);
		break;
		case(Predator::jararaca):
										this->set_distance_pursuit(10);
		this->set_distance_bite(0.3);
		break;
		case(Predator::colubridae):
										this->set_distance_pursuit(10);
		this->set_distance_bite(0.3);
		break;
		case(Predator::coruja):
										this->set_distance_pursuit(10);
		this->set_distance_bite(0.3);
		break;

	}

	/* Debug Visibility Circle */
	float angle_degrees = 360, num_steps = 32;
	float angle_radians = deg_2_rad(angle_degrees);
	LineSegs circle = LineSegs();
	circle.set_color(0, 0, 1, 1);
	for(int i = 0; i <= num_steps; i++){
		float a = angle_radians * i / num_steps;
		float y = sin(a);
		float x = cos(a);

		circle.draw_to(x, 0, y);
	}

	/* Carrega apenas para a fase 2 para parar de irritar a equipe. =) */
	// Muito obrigado. by: Jubaz hehe =D
	if(Session::get_instance()->get_level() > 1){
		/* Debug Visibility Circle */
		debug_visibility_circle = NodePath(circle.create(false));
		debug_visibility_circle.set_p(90);
		debug_visibility_circle.flatten_light();
		debug_visibility_circle.set_bin("fixed", 40);
		debug_visibility_circle.set_depth_test(false);
		debug_visibility_circle.set_depth_write(false);
		debug_visibility_circle.reparent_to(render);
		debug_visibility_circle.show();
		debug_visibility_circle.set_antialias(AntialiasAttrib::M_line);
	}

}

Predator::~Predator(){}

/*! Carrega todos os predadores do jogo */
void Predator::load_predators(){
	ModelRepository::get_instance()->get_animated_model("teiu")->set_length(0.60);
	Predator::load_predator(Predator::teiu, 7, 0.004, -1);

	ModelRepository::get_instance()->get_animated_model("siriema")->set_height(0.60);
	Predator::load_predator(Predator::siriema, 7, 0.03, -1);

	ModelRepository::get_instance()->get_animated_model("raposa")->set_length(0.80);
	Predator::load_predator(Predator::raposa, 6, 0.01, -1, Animal::A_night); // Testing
//	Predator::load_predator(Predator::raposa, 20, 0.01, -1, Animal::A_night); // Testing

	ModelRepository::get_instance()->get_animated_model("gato")->set_length(0.40);
	Predator::load_predator(Predator::gato, 9, 0.01, -1);

//		ModelRepository::get_instance()->get_animated_model("jararaca")->set_length(0.60);
//	ModelRepository::get_instance()->get_animated_model("jararaca")->set_length(0.40);
//		Predator::load_predator(Predator::jararaca, 50, 0.01, -1);

//		ModelRepository::get_instance()->get_animated_model("colubridae")->set_length(0.50);
//		ModelRepository::get_instance()->get_animated_model("colubridae")->set_length(0.30);
//		Predator::load_predator(Predator::colubridae, 50, 0.01, -1 );


		//FlyingPredator::load_predators();
}


/*! Carrega uma quantidade de predadores com comportamento padrão, de determinado tipo */
void Predator::load_predator(Predator::types_predator type , int qtd, float scale,
		int orientation, Activity activity){
	//ModelRepository::get_instance()->get_animated_model(model)->set_scale(scale);

	string tipo_predador = Predator::get_predator_type(type);//Tipo de Predador

	PT(Terrain) terrain = World::get_world()->get_terrain();
	for(int i = 0; i < qtd; i++){
		/* Carrega e cria uma cópia (deep) do modelo */
		NodePath base_predator = ModelRepository::get_instance()->get_animated_model(tipo_predador)->copy_to(NodePath());
		PT(Predator) predator = new Predator(base_predator, type);

		predator->bind_anims(predator->node());

		/* Define localização e orientação aleatórias */
		predator->set_h(rand()%360);
		predator->set_pos(terrain->get_random_point());
		predator->set_orientation(orientation);

		/* Adiciona o predator ao terreno e ao render */
		terrain->add_predator(predator);
		predator->reparent_to(render);

		/* Roda a animação */
		predator->loop_anim("andar");

		predator->set_activity(activity);
	}
}

/*! Roda o comportamento de ações do predador.
 * O predador basicamente perambula, e ao encontrar o lagarto dentro de uma
 * certa distância ele parte para o ataque */
void Predator::act(){

	if(Session::get_instance()->get_level() == 1){
		//Se o predador não estiver nas proximidades do player, ele apenas andará
		if(!(this->get_setor()==player->get_setor() || this->get_setor()->get_is_closest_sector())){
			this->act_state = Predator::walking;
			play_anim("andar");
			Animal::act();

		}

		else{
			switch(act_state){
				case(Predator::walking):
						play_anim("andar");
						Animal::act();
						break;

				case(Predator::pursuing_act):
						if(this->prey != NULL){
						pursuit(*this->prey);
						}
					break;

				case(Predator::biting):
				bite();
			}

		}
	}

	else{
		//Nova ação para a fase 2
		act_fase_2();
	}

}


void Predator::event_psegundo_change_state(const Event *, void *data){
	Predator* _this = (Predator*) data;
	_this->change_state();
}
/*Verificação do estado do predador
 * Podem ser: caminhando, perseguindo, mordendo*/
void Predator::change_state(){
	switch(act_state){
		case(Predator::walking):
				if(find_prey()){
					act_state = Predator::pursuing_act;
//					if(hunting_player){
//						pursuing = true;
//						AudioController::get_instance()->predator_pursuing();
//						GuiManager::get_instance()->activate_predator_alert(this);
//					}
					if(predator_to_prey < Predator::dist_to_bite){ act_state = Predator::biting; }
				}

			break;

		case(Predator::pursuing_act):
				if(hunting_player){//Presa é o player

					if(player->is_under_vegetal() || player->is_in_toca()){

						act_state = Predator::walking;
						hunting_player = false;
						player->set_hunted(false);
						player->set_predator(NULL);
//						AudioController::get_instance()->pursuit_finished();
//						pursuing = false;
						break;
					}

					if(get_distance_squared(*player) > 10*10){
						act_state = Predator::walking;
						hunting_player = false;
						player->set_hunted(false);
						player->set_predator(NULL);
//						AudioController::get_instance()->pursuit_finished();
//						pursuing = false;
						break;
					}

					if(!closest_to_player || player->get_predator() != this){//Se ele não for o mais próximo, verifica se o primeiro está muito próximo
						if(player->get_predator() != NULL){
						float distance_squared_player = this->get_distance_squared(*player);
						float dist_first_pred = player->get_distance_squared(player->get_predator()->get_pos());

						if(dist_first_pred < 5*5){//Closest_predator muito próximo
							act_state = Predator::walking;
							hunting_player = false;
							break;
							}

						if(distance_squared_player < dist_first_pred){//Este está  mais próximo, e acontece a mudança de predador no player
							player->get_predator()->set_closest_player(false);
							player->set_hunted(true);
							player->set_predator(this);
							this->closest_to_player = true;
							break;
							}
						}
						else{
							player->set_predator(this);
							player->set_hunted(true);
							player->set_predator(this);
							this->closest_to_player = true;
							break;
						}

					}
				}

				if(hunting_lizard){//Presa é um lizard
					Lizard* presa = (Lizard*) prey.p();
					if(presa->get_distance_squared(presa->get_arvore_da_sombra()->get_pos()) < Predator::dist_player_hide){
						act_state = Predator::walking;
						hunting_lizard = false;
						this->prey->set_hunted(false);

						break;
					}

					if(this->get_distance_squared(prey->get_pos()) > 10*10){//Verificar se a presa não está muito distante do predador
						act_state = Predator::walking;
						hunting_lizard = false;
						this->prey->set_hunted(false);

						break;

					}
				}
				//Atualizando distancia para a presa
				predator_to_prey = this->get_distance_squared(*prey);
				if(predator_to_prey < Predator::dist_to_bite){ act_state = Predator::biting; }
			break;

		case(Predator::biting):
				//Atualizando distancia para a presa
				predator_to_prey = this->get_distance_squared(*prey);
				if(predator_to_prey > Predator::dist_to_bite){
					act_state = Predator::pursuing_act;
				}
	}
}



/*Localize uma presa mais próxima para o predador, incluindo o player*/
bool Predator::find_prey(){

	SectorItems<PT(Lizard)>* lizard_list = this->get_setor()->lizards();
	SectorItems<PT(Lizard)>::iterator it;
	float distance_squared_lizard  = 0;
	float distance = this->get_distance_pursuit();

	predator_to_prey = 0;

	float distance_squared_player = this->get_distance_squared(*player);


	if(!player->is_under_vegetal() && !player->is_in_toca()){

		if(distance_squared_player < Predator::dist_to_hunt){

			if(player->get_hunted() && player->get_predator() != NULL){//Player está sendo caçado

				float dist_first_pred = player->get_distance_squared(player->get_predator()->get_pos());

				if (distance_squared_player < dist_first_pred){

					//Verificando se este é o predador mais próximo
								this->prey = player;
								player->set_hunted(true);
								//player->get_predator()->set_state(Predator::walking);
								player->get_predator()->set_closest_player(false);
								player->set_predator(this);
								this->closest_to_player = true;
								predator_to_prey = distance_squared_player;
								hunting_lizard = false;
								hunting_player = true;
				}
				else{//Caso não, ele verifica se o primeiro predador está muito próximo
						if(dist_first_pred < 5*5){//Desista
						this->act_state = Predator::walking;
						}
						else{//Continue
							this->prey = player;
							closest_to_player = false;
							predator_to_prey = distance_squared_player;
							hunting_lizard = false;
							hunting_player = true;
						}
				}


			}
			else{//Player sem nenhum predador
			this->prey = player;
			this->prey->set_hunted(true);
			player->set_predator(this);
			this->closest_to_player = true;
			predator_to_prey = distance_squared_player;
			hunting_lizard = false;
			hunting_player = true;
		}
			}
	}

//Verifica os outros calangos
	for(it = lizard_list->begin(); it!= lizard_list->end(); ++it){
		PT(Lizard) lizard = *it;
		distance_squared_lizard = get_distance_squared(*lizard);
		if(distance_squared_lizard < Predator::dist_to_hunt){//Verifica se a presa está próxima
			if(lizard->get_arvore_da_sombra() != NULL){
				if(lizard->get_distance_squared(lizard->get_arvore_da_sombra()->get_pos()) < Predator::dist_player_hide){continue;}
			}
				//Verifica se  a presa não está camuflada
			  if(predator_to_prey == 0 || distance_squared_lizard < predator_to_prey){
					//Verifica se esse lizard é o mais próximo do predador
				if(lizard->get_hunted() && lizard->get_predator()!=NULL){

					float dist_first_pred = lizard->get_distance_squared(lizard->get_predator()->get_pos());

									if(distance_squared_lizard < dist_first_pred){
										if(distance_squared_lizard < predator_to_prey){
											player->set_hunted(false);
											player->set_predator(NULL);
										}

										//Predador está mais próximo que o primeiro predador
										this->prey = lizard;
										lizard->get_predator()->set_state(Predator::walking);
										lizard->set_predator(this);
										this->prey->set_hunted(true);
										predator_to_prey = distance_squared_lizard;
										hunting_lizard = true;
										hunting_player = false;
					}
				}

				else{
				this->prey = lizard;
			lizard->set_predator(this);
			this->prey->set_hunted(true);
			predator_to_prey = distance_squared_lizard;
			hunting_lizard = true;
			hunting_player = false;
				}
		  }
		continue;

		}
		else{
			continue;
		}
	}




	if(predator_to_prey == 0){
		hunting_lizard = false;
		hunting_player = false;
		return false;
	}
	else{
		return true;
	}


}

/*Act da fase 2*/
void Predator::act_fase_2(){
	/* Nova ação para a fase 2.
	 * Se a visibilidade for maior do que zero, significa que o predador é
	 * capaz de perceber a presença do player. Um range é especificado para
	 * se definir a chance do predador passar a atacar.
	 * Ex.: Visibilidade 0: Predador não percebe o player
	 * Ex.: Visibilidade 0.2: Predador tem 20% de chance de perceber o player
	 * Porém, se esta checagem for sendo realizada por frame, como está sendo,
	 * a visibilidade do predador sempre começa em 0 e vai aumentando a
	 * pequenos passos. Esta checagem deve ocorrer mesmo que o predador já
	 * tenha ativado a ação de ataque, pois o player pode se camuflar, certo? */

	/* Pergunta: A presa deve poder ser perseguida por mais de um predador?
	 * Além da questão biológica, precisa-se testar a questão de jogabilidade */
	float distance = this->get_distance_pursuit();
		float eat_thr = this->get_distance_bite();

	float dist = get_distance(*player);

	/* Se a distância for menor que o limiar para comer, sem conversa. morder! */
	if (dist < eat_thr) bite();

	/* Apenas verifica o que já foi definido pela checagem de tempos em tempos.
	 * Ao contrário da verificação essa parte é executada todos os frames para
	 * os predadores ativos */
	float dist_visibility = get_visibility();
	if(dist < dist_visibility){
		if(!this->get_anim_control()->is_playing("comer")) play_anim("andar");
		pursuit();
	}
	else {
		play_anim("andar");
		if(dist > 10.0) Animal::act();
		else Animal::move(get_velocity());
	}

	/* Atualiza o círculo para debug */
	debug_visibility_circle.set_pos(get_pos(render));
	debug_visibility_circle.set_quat(get_quat(render));
	if(dist_visibility == 0) debug_visibility_circle.hide();
	else debug_visibility_circle.set_scale(dist_visibility);

	bool is_night = TimeControl::get_instance()->is_night();
	if(is_night && (get_activity() == A_day) || (!is_night && (get_activity() == A_night))){
		debug_visibility_circle.hide();
	} else debug_visibility_circle.show();
}



/*! Muda o Predador de setor */
void Predator::change_sector(PT(Setor) new_sector){
	get_setor()->predators()->remove(this);
	new_sector->predators()->push_back(this);

	reparent_to(get_setor()->get_root());
}

/*! Roda comportamento de perseguição, alvo: player */
void Predator::pursuit(){
	pursuit(*player);
}

/*! Roda comportamento de perseguição, alvo: lizard */
void Predator::pursuit(const NodePath &other){
	if(!this->get_anim_control()->is_playing("comer")){
		play_anim("andar");

		look_at(other);

		move(get_velocity());
	}
}


/*! Roda comportamento de mordida/comer, alvo:player */
void Predator::bite(){
	if(!this->get_anim_control()->is_playing("comer") && !this->prey->being_bited()){
		get_anim_control()->stop_all();
		play_anim("comer");

		//        sound->play();//testando som

		if(hunting_player){
		/* Diminui energia do player */
		player->be_bited();
		player->add_food_energy(-1.0);
		GuiManager::get_instance()->piscar_life();
		}
	}
}

/*! Roda comportamento de mordida/comer, alvo: presa */
void Predator::bite_other(){
	if(!this->get_anim_control()->is_playing("comer") ){
		get_anim_control()->stop_all();
		play_anim("comer");
	}
}

/*! Pausa a animação */
void Predator::pause_animation(){
	get_anim_control()->stop_all();
	get_anim_control()->pose("andar", 7);

	/* Apenas o teiu não tem stand */
	//play_anim("stand");
}

/*! Retoma a animação */
void Predator::continue_animation(){
	if(render.is_ancestor_of(*this)) play_anim("andar");
}

float Predator::get_visibility_distance() const {
	return visibility_distance;
}

void Predator::set_visibility_distance(float visibility_distance){
	this->visibility_distance = visibility_distance;
}

float Predator::get_distance_pursuit(){
	return distance_pursuit;
}

void Predator::set_distance_pursuit(float distance){
	this->distance_pursuit = distance;
}

float Predator::get_distance_bite(){
	return distance_bite;
}


void Predator::set_distance_bite(float distance){
	this->distance_bite = distance;
}
/*! Obter grau de visibilidade do predador para o player.
 * Retorna distância de visibilidade do predador.
 * dmax = dmax0 + (dcontr * contraste) + (dtam * tam)
 * onde:
 * - dcontraste é o ganho de distância para quando o contraste for máximo (1)
 * - dtam é o ganho de distância para quando o tamanho for máximo (1). */
float Predator::get_visibility(){
	bool is_night = TimeControl::get_instance()->is_night();

	/* Separado por legibilidade. Se não estiver no período ativo anula a visibilidade */
	if(is_night && (get_activity() == A_day)) return 0.0;
	if(!is_night && (get_activity() == A_night)) return 0.0;

	/* Calcula o fator exercido pela distância */
	float distance = get_distance(*player);

	/* Obtém fator exercido pela camuflagem do player na visibilidade */
	float contrast = 1.0 - (player->get_indice_camuflagem() * get_visibility_factor());

	/* Fator de 0 a 1 do tamanho do player em relação ao maior/menor lagartos */
	float size_factor = player->get_relative_size();

	/* A distância de visibilidade aumenta com os fatores */
	float dmax = 3 + (contrast * 2) + (size_factor * 2);

	return dmax;
}

/*! Obtém o fator de visibilidade do predador, verificando se é dia ou noite */
float Predator::get_visibility_factor() const {
	return TimeControl::get_instance()->is_night() ? night_visibility : day_visibility;
}

/*! Obtém o nível de visibilidade do predador durante o dia */
float Predator::get_day_visibility() const {
	return day_visibility;
}

/*! Define o nível de visibilidade do predador durante o dia */
void Predator::set_day_visibility(float day_visibility){
	this->day_visibility = day_visibility;
}

/*! Obtém o nível de visibilidade do predador durante a noite */
float Predator::get_night_visibility() const {
	return night_visibility;
}

/*! Define o nível de visibilidade do predador durante a noite */
void Predator::set_night_visibility(float night_visibility){
	this->night_visibility = night_visibility;
}

/*!Define o tipo de predador*/
string Predator::get_type_predator() const{
	return type_predator;
}

/*!Obtém o tipo de predador*/
void Predator::set_type_predator(string type){
	this->type_predator = type;
}


string Predator::get_predator_type(Predator::types_predator type){
	switch(type){
		case(Predator::teiu):return"teiu";
		case(Predator::siriema):return"siriema";
		case(Predator::gato):return"gato";
		case(Predator::raposa):return"raposa";
		case(Predator::jararaca):return"jararaca";
		case(Predator::colubridae):return"colubridae";
		case(Predator::coruja):return"coruja";
	}
	return NULL;
}

/*Define se o predador é o mais próximo do player*/
void Predator::set_closest_player(bool closest){
	this->closest_to_player = closest;
}

/*obtém se o predaor é o mais próximo do player*/
bool Predator::get_closest_player(){
	return this->closest_to_player;
}

/*Define o estado de ação do predador*/
void Predator::set_state(Predator::act_states state){
	this->act_state = state;
}

Predator::act_states Predator::get_state(){
	return act_state;
}
/*Obtém o estado de ação do predador*/

void Predator::set_tipo_predator_enum(Predator::types_predator type){
	this->tipo_predator_enum = type;
}

Predator::types_predator Predator::get_tipo_predator_enum(){
	return this->tipo_predator_enum;
}
