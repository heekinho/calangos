#include "flyingPredator.h"

#include "modelRepository.h"

#include "character.h"
#include "world.h"

#include "cameraControl.h"
#include "flyingPredatorCamera.h"

PT(FlyingPredatorCamera) FlyingPredator::flying_predator_camera;

/*! Constrói um predador voador */
FlyingPredator::FlyingPredator(NodePath node) : Predator(node){
	find("**/+CollisionNode").remove_node();
	_player_captured = false;
	_chasing_player = false;
	set_two_sided(true);
}

/*! Destrutor de predador voador */
FlyingPredator::~FlyingPredator(){}


/*! Carrega todos os predadores voadores do jogo */
void FlyingPredator::load_predators(){
	/* Cria uma nova camera e adiciona ao controle de cameras */
	flying_predator_camera = new FlyingPredatorCamera(new Camera("Flying Predator Camera"));
	CameraControl::get_instance()->get_cameras()->push_back((PT(CameraNode)) flying_predator_camera);

	FlyingPredator::load_predator("coruja", 20, 0.03, -1);
}


/*! Carrega uma quantidade de predadores voadores, da espécie especificada */
void FlyingPredator::load_predator(const string &model, int qtd, float scale, int orientation){
	ModelRepository::get_instance()->get_animated_model(model)->set_scale(scale);

	PT(Terrain) terrain = World::get_world()->get_terrain();
	for(int i = 0; i < qtd; i++){
		/* Carrega e cria uma cópia (deep) do modelo */
		NodePath base_predator = ModelRepository::get_instance()->get_animated_model(model)->copy_to(NodePath());
		PT(FlyingPredator) predator = new FlyingPredator(base_predator);
		predator->bind_anims(predator->node());

		/* Define localização e orientação aleatórias */
		predator->set_h(rand()%360);
		predator->NodePath::set_pos(terrain->get_random_point());
		predator->set_offset_z(20);
		predator->set_orientation(orientation);

		/* Adiciona o predator ao terreno e ao render */
		terrain->add_predator((PT(Predator))predator);
		predator->reparent_to(render);

		/* Roda a animação */
		predator->loop_anim("voar");
	}
}


/*! Roda o comportamento de ações do predador.
 * O predador basicamente perambula, e ao encontrar o lagarto dentro de uma
 * certa distância ele parte para o ataque */
void FlyingPredator::act(){
	/* Se o player foi capturado por este predator, roda attack() */
	if(_player_captured) { attack(); return; }

	/* Se este predador estiver atrás do player, verifica se um outro predador
	 * mais esperto não o já capturou, e caso contrário rode chase() */
	if(_chasing_player) {
		if(player->was_captured()) _chasing_player = false;
		chase();
		return;
	}

	/* Se o predador não está caçando ou já capturou o player, ele vai rodar o
	 * comportamento de voar, fazendo testes para entrar nas outras condições. */
	loop_anim("voar");

	/* Calcula distância e coloca algumas variações de heading */
	float dist_xy = (get_pos().get_xy() - player->get_pos().get_xy()).length();
	if(rand()%120 == 34) set_h(*this, rand()%80 - (80/2));

	/* Ou começa a caçar ou apenas se move (voa) */
	if(!player->was_captured() && dist_xy < 5) start_chasing();
	else move(get_velocity());
}

/*! Método de transição (em uma FSM) */
void FlyingPredator::start_chasing(){
	_chasing_player = true;
	chase();

	/* Faz o setup da camera de acordo */
	flying_predator_camera->activate(this);
}

/*! Inicia a captura, indo de encontro ao player para o capturar */
void FlyingPredator::chase(){
	look_at(*player);
	move(get_velocity()*4);
	int z = World::get_world()->get_terrain()->get_elevation(get_x(), get_y());
	if(get_z() < z) set_z(z);

	/* Distância da qual se pode agarrar o player */
	if(get_distance(*player) < 1) capture_player();
}

/* Ação de captura do predador */
void FlyingPredator::capture_player(){
	/* Define as flags de comportamento */
	_chasing_player = false;
	_player_captured = true;
	player->be_captured();

	/* Este será o ponto controlado pela junta da animação */
	_beak = attach_new_node("bico");

	/* TODO: Precisa ser regulado */
	player->wrt_reparent_to(_beak);
	player->NodePath::set_pos(0.5, -0.75, 0);
	player->NodePath::set_hpr(0, 90, -135);

	/* Obtém a junta e dispara atualizações da matriz */
	PT(Character) character = DCAST(Character, find("character").node());
	_joint = character->find_joint("Bip01 Ponytail1Nub");

	_joint->add_net_transform(_beak.node());
}

/*! Ação de ataque. O player já foi capturado e está sendo levado */
void FlyingPredator::attack(){
	float cruising_altitude = 50;
	if(get_z() < cruising_altitude){
		set_p(-65);
		move(get_velocity()*5);
	}
	else {
		if(get_p() > 0) set_p(get_p() - get_velocity());
		if(get_p() < 0) set_p(0);

		/* Por enquanto o predador fica passeando com o player.
		 * Vai ter mais de um ataque? Poderia chamar game over? */
		_player_captured = false;
		//player->set_captured(false);
	}
}


/*! O movimento dos objetos voadores não tem influência do get_elevation do terreno */
void FlyingPredator::move(float velocity){
	LPoint3f desloc = calculate_pos(velocity, true);
	if(World::get_world()->get_terrain()->has_inside(desloc)) NodePath::set_pos(desloc);
	else set_h(*this, 20);
}
