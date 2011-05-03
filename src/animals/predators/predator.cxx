#include "predator.h"
#include "player.h"

#include "flyingPredator.h"
#include "modelRepository.h"

#include "collision.h"

/*! Constrói um Predador */
Predator::Predator(NodePath node) : Animal(node){
	set_velocity(350.0);
	//adiciona solido de colisão aos predadores (ficou legal esses valores para altura e raio)
	collision::get_instance()->collisionNpcFast(&node, 0, 0, 20, 10);

        //testando som
       AM = AudioManager::create_AudioManager();
       sound = AM->get_sound("models/sounds/pc_apanhando.wav") ;
}

Predator::~Predator(){}

/*! Carrega todos os predadores do jogo */
void Predator::load_predators(){
	ModelRepository::get_instance()->get_animated_model("teiu")->set_length(0.60);
	Predator::load_predator("teiu", 7, 0.004, -1);

	ModelRepository::get_instance()->get_animated_model("siriema")->set_height(0.60);
	Predator::load_predator("siriema", 7, 0.03, -1);

	ModelRepository::get_instance()->get_animated_model("raposa")->set_length(0.80);
	Predator::load_predator("raposa", 6, 0.01, -1);

	ModelRepository::get_instance()->get_animated_model("gato")->set_length(0.40);
	Predator::load_predator("gato", 9, 0.01, -1);

//	ModelRepository::get_instance()->get_animated_model("jararaca")->set_length(0.60);
//	Predator::load_predator("jararaca", 50, 0.01, -1);

//	ModelRepository::get_instance()->get_animated_model("colubridae")->set_length(0.50);
//	Predator::load_predator("colubridae", 50, 0.01, -1);


//	FlyingPredator::load_predators();
}


/*! Carrega uma quantidade de predadores com comportamento padrão, de determinado tipo */
void Predator::load_predator(const string &model, int qtd, float scale, int orientation){
	//ModelRepository::get_instance()->get_animated_model(model)->set_scale(scale);

	PT(Terrain) terrain = World::get_world()->get_terrain();
	for(int i = 0; i < qtd; i++){
		/* Carrega e cria uma cópia (deep) do modelo */
		NodePath base_predator = ModelRepository::get_instance()->get_animated_model(model)->copy_to(NodePath());
		PT(Predator) predator = new Predator(base_predator);
		predator->bind_anims(predator->node());

		/* Define localização e orientação aleatórias */
		predator->set_h(rand()%360);
		predator->set_pos(terrain->get_random_point());
		predator->set_orientation(orientation);

		/* Adiciona o predator ao terreno e ao render */
		terrain->add_predator(predator);
		predator->reparent_to(Simdunas::get_window()->get_render());

		/* Roda a animação */
		predator->loop_anim("andar");
	}
}


/*! Roda o comportamento de ações do predador.
 * O predador basicamente perambula, e ao encontrar o lagarto dentro de uma
 * certa distância ele parte para o ataque */
void Predator::act(){
	float distance = 10;
	PT(Player) player = Player::get_instance();

	if(get_distance(*player) < distance){
		if (get_distance(*player) < 0.3) bite();
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
			pursuit();
		}
	}
	else {
		play_anim("andar");
		Animal::act();
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

		PT(Player) player = Player::get_instance();
		look_at(*player);

		move(get_velocity());
	}
}

/*! Roda comportamento de mordida/comer */
void Predator::bite(){
	if(!this->get_anim_control()->is_playing("comer") && !Player::get_instance()->being_bited()){
		get_anim_control()->stop_all();
		play_anim("comer");

                sound->play();//testando som

		/* Diminui energia do player */
		Player::get_instance()->be_bited();
		Player::get_instance()->add_energia_alimento(-1.0);
		GuiManager::get_instance()->piscar_life();

                 
                
	}
}

/*! Pausa a nimação */
void Predator::pause_animation(){
	get_anim_control()->stop_all();
	get_anim_control()->pose("andar", 7);

	/* Apenas o teiu não tem stand */
	//play_anim("stand");
}

/*! Retoma a animação */
void Predator::continue_animation(){
	if(Simdunas::get_window()->get_render().is_ancestor_of(*this)) play_anim("andar");
}

float Predator::get_visibility_distance() const {
	return visibility_distance;
}

void Predator::set_visibility_distance(float visibility_distance){
	this->visibility_distance = visibility_distance;
}

/*! Obter grau de visibilidade do predador para o player
 * vis = 1 - (d / dmax)
 * dmax = dmax0 + dcontr * contraste + dtam * tam
 * onde:
 * dcontraste é o ganho de distância para quando o contraste for máximo (1)
 * dtam é o ganho de distância para quando o tamanho for máximo (1).
 * lembra-se que visibilidade pode continuar sendo negativo. Tem que fazer teste.
 *  */
float Predator::get_visibility(){
	PT(Player) player = Player::get_instance();
	bool is_night = TimeControl::get_instance()->is_night();

	/* Separado por legibilidade. Se não estiver no período ativo anula a visibilidade */
	if(is_night && (get_activity() == A_day)) return 0.0;
	if(!is_night && (get_activity() == A_night)) return 0.0;

	/* Calcula o fator exercido pela distância */
	float distance = get_distance(*player);
	float idist = 1.0 - (distance / get_visibility_distance());
//	idist = idist < 0 ? 0 : idist;
//	if(idist < 0) idist = 0;

	/* Obtém fator exercido pela camuflagem do player na visibilidade */
	float camuflagem = 1.0 - player->get_indice_camuflagem();

	/* Ver tamanho do player */
	/* TODO: Não utilizar tamanho base. Utilizar outra variável com base no
	 * menor tamanho de lagarto possível e o maior tamanho */
	float tamanho = player->get_tamanho_base() * 0.01;

	/* Retorna o conjunto dos fatores juntos */
	// Fazer com media
//	return (idist + camuflagem + tamanho)/3;
	return (idist * camuflagem * tamanho);
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
