#include "predator.h"
#include "player.h"

#include "flyingPredator.h"
#include "modelRepository.h"

#include "collision.h"
#include "antialiasAttrib.h"

bool Predator::pursuing = false;

/*! Constrói um Predador */



Predator::Predator(NodePath node, Predator::types_predator type) : Animal(node){
	set_velocity(350.0);
	//adiciona solido de colisão aos predadores (ficou legal esses valores para altura e raio)
	collision::get_instance()->collisionNpcFast(&node, 0, 0, 20, 10);

	//Tipo de predador
	type_predator = Predator::get_predator_type(type);
	set_tipo_predator_enum(type);

/*TODO Ajustar a distancia para perserguir a depender do tipo de predador*/
	switch(type){
		case(Predator::teiu): this->set_distance_pursuit(10.1); break;
		case(Predator::siriema):this->set_distance_pursuit(9.9);break;
		case(Predator::gato):this->set_distance_pursuit(9.8);break;
		case(Predator::raposa):this->set_distance_pursuit(10);break;
		case(Predator::jararaca):this->set_distance_pursuit(9.85);break;
		case(Predator::colubridae):this->set_distance_pursuit(10.2);break;
		case(Predator::coruja):this->set_distance_pursuit(10);break;

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

	ModelRepository::get_instance()->get_animated_model("gato")->set_length(0.40);
	Predator::load_predator(Predator::gato, 9, 0.01, -1);

//	ModelRepository::get_instance()->get_animated_model("jararaca")->set_length(0.60);
//	Predator::load_predator(Predator::tipos::jararaca, 50, 0.01, -1);

//	ModelRepository::get_instance()->get_animated_model("colubridae")->set_length(0.50);
//	Predator::load_predator(Predator::tipos::colubridae, 50, 0.01, -1);


//	FlyingPredator::load_predators();
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


	 float distance = this->get_distance_pursuit();

	static float eat_thr = 0.3;
	// eat_thr original = 0.3

	if(Session::get_instance()->get_level() == 1){
		if(get_distance(*player) < distance){
			if (get_distance(*player) < eat_thr) bite();
			else{
				PT(Setor) setor = World::get_world()->get_terrain()->get_setor_from_pos(player->get_x(), player->get_y());
				SectorItems<PT(Vegetal)>* vegetal_list = setor->vegetals();
				SectorItems<PT(Vegetal)>::iterator it;
				for (it = vegetal_list->begin(); it != vegetal_list->end(); ++it){
					PT(Vegetal) vegetal = *it;
					LVector3f player_to_vegetal = player->get_pos() - vegetal->get_pos();
					if (player_to_vegetal.length() < 3.5 || player->is_in_toca()){
						if(!this->get_anim_control()->is_playing("comer") && !get_anim_control()->is_playing("andar"))
							play_anim("andar");
						Animal::act();
						return;
					}
				}

				if (!pursuing) {
					pursuing = true;
					LVector3f right = player->get_net_transform()->get_quat().get_right();
					// continuar aqui com a lógica da posição (angulação)
				}

				pursuit();
			}
		}
		else {
			play_anim("andar");
			Animal::act();
		}
	}
	else {
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
}


/*! Muda o Predador de setor */
void Predator::change_sector(PT(Setor) new_sector){
	get_setor()->predators()->remove(this);
	new_sector->predators()->push_back(this);

	reparent_to(get_setor()->get_root());
}

/*! Roda comportamento de perseguição */
void Predator::pursuit(){
	if(!this->get_anim_control()->is_playing("comer")){
		play_anim("andar");

		look_at(*player);

		move(get_velocity());
	}
}

/*! Roda comportamento de mordida/comer */
void Predator::bite(){
	if(!this->get_anim_control()->is_playing("comer") && !player->being_bited()){
		get_anim_control()->stop_all();
		play_anim("comer");

//        sound->play();//testando som

		/* Diminui energia do player */
		player->be_bited();
		player->add_energia_alimento(-1.0);
		GuiManager::get_instance()->piscar_life();
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
	float size_factor = player->get_absolute_size_factor();

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

void Predator::set_tipo_predator_enum(Predator::types_predator type){
	this->tipo_predator_enum = type;
}

Predator::types_predator Predator::get_tipo_predator_enum(){
	return this->tipo_predator_enum;
}
