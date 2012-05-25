#include "player.h"
#include "modelRepository.h"
#include "collision.h"
#include "audioRepository.h"
#include "textureStageCollection.h"
#include "simdunas.h"
#include "audioController.h"
#include "femaleLizard.h"

#include "world.h"
#include "setor.h"
#include "guiManager.h"

#include "playerHealth.h"
#include "playerHealthSimulator.h"

#define DEBUG_PLAYER 0

PlayerProperties Player::properties = PlayerProperties();
bool Player::instanceFlag = false;
PT(Player) Player::single = NULL;
float Player::nivel_camuflagem_terreno_dia = 0;
float Player::nivel_camuflagem_terreno_noite = 0;
float Player::nivel_camuflagem_sombra = 0;
float Player::nivel_camuflagem_folhagem = 0;

Player::lizardEpecie Player::lizard_specie = Player::eurolophosaurus;
Player::lizardGender Player::lizard_gender = Player::young;


Player::Player() : AnimatedObjetoJogo(*ModelRepository::get_instance()->get_animated_model(
		Player::get_specie_name(Player::lizard_specie) + "/" +
		Player::get_gender_name(lizard_gender))){
	in_toca = false;
	_toca = NULL;

	flag_verify_under_vegetal = false;
	player_is_under_vegetal = false;

	_courted_female = NULL;
	predator = NULL;
	_captured = false;
	_is_buried = false;
	hunted = false;

	achievements = new Achievements();

	//int especie = Menu::get_instance()->get_especie();
	load_health(lizard_specie);

	event_handler->add_hook(TimeControl::EV_segundo_real, event_gasto_energia, this);
	event_handler->add_hook(TimeControl::EV_pass_day, event_pday, this);
	event_handler->add_hook(TimeControl::EV_pass_month, event_pmonth, this);

	if(ModelRepository::get_instance()->get_lagarto_personalizado()){
		nout << "teste" << endl;
		PT(TextureStage) ts = find_all_texture_stages().get_texture_stage(0);
		ts->set_mode(TextureStage::M_modulate);
		set_texture(ts, ModelRepository::get_instance()->get_lagarto_personalizado(), 10);
		//		get_texture()->reload();
		//ativa método que provoca o efeito de camuflagem do player
		event_handler->add_hook("EV_SEGUNDO_REAL", event_psegundo_camuflagem, this);

	}

	event_handler->add_hook(TimeControl::EV_pass_frame, false_flag_under_vegetal, this);

}

/*! Obtem a instancia atual da classe Player. Observe que a classe ja deve ter
 * sido inicializada para que este metodo seja utilizado com seguranca.
 * @return single Referencia para o Player atual */
PT(Player) Player::get_instance() {
	if(!instanceFlag) {
		single = new Player();
		instanceFlag = true;
	}
	return single;
}

/* Destrutor da classe Player */
Player::~Player() {
	//this->~ObjetoJogo();
}

string Player::get_specie_name(Player::lizardEpecie specie){
	switch(specie){
		case(Player::tropidurus): return "tropidurus";
		case(Player::eurolophosaurus): return "eurolophosaurus";
		case(Player::cnemidophorus): return "cnemidophorus";
		case(Player::custom): return "custom";
	}
	return NULL;
}

string Player::get_gender_name(Player::lizardGender gender){
	switch(gender){
		case(Player::young): return "young";
		case(Player::male): return "male";
		case(Player::female): return "female";
	}
	return NULL;
}

/*! Ao comer um objeto, a respectiva hidratacao e energia eh adquirida */
/* type: 0:formiga   1:plantas 2:outros */
void Player::eat(Edible* food, int type){
	achievements->check_edible_specie(food->get_specie_value());

	nout << "type: " << type << " : ";
	nout << "ant: " << properties.ant_diet << " : " << properties.plant_diet << " : " << properties.general_diet << endl;

	float nutritional_value = food->get_nutritional_value();
	nout << "Valor nutricional antes da modulação: " << nutritional_value << endl;

	if(Session::get_instance()->get_level() > 1){
		if(type == 0) nutritional_value = food->get_nutritional_value() * properties.ant_diet * 0.01;
		else if(type == 1) nutritional_value = food->get_nutritional_value() * properties.plant_diet * 0.01;
		else nutritional_value = food->get_nutritional_value() * properties.general_diet * 0.01;
	}
	else {
		/* Se não for na segunda fase eu preciso modular também para não deixar injusto */
		nutritional_value = food->get_nutritional_value() / 3.0;
	}

	nutritional_value = nutritional_value * 3;

	nout << "Valor nutricional depois da modulação: " << nutritional_value << endl;
	add_food_energy(nutritional_value);
	add_food_hydration(food->get_hydration_value());
}



/*! Retorna a velocidade do jogador */
/* TODO: Deveria ser speed e não velocity. Velocity é vetor */
double Player::get_velocity() const {
	return this->velocity;
}

/*! Define a velocidade do jogador */
void Player::set_velocity(double velocity){
	this->velocity = velocity;
}

/*! Obtém a velocidade do jogador quando andando */
float Player::get_speed_walking() const {
	if(Session::get_instance()->get_level() > 1) return properties.speed;
	else {
		Player *p = player;
		/* A Letargia influencia na velocidade (decidiu-se por influenciar linearmente */

		p->set_velocity((PlayerProperties::max_speed + PlayerProperties::min_speed) * 0.5);
		p->set_velocity(p->get_velocity() * (1 - p->get_lethargy()));
		p->set_velocity(p->get_velocity()*100);//Multiplicador de velocidade
		return p->get_velocity();

//		return (PlayerProperties::max_speed + PlayerProperties::min_speed) * 0.5;
	}
}

/*! Obtém a velocidade do jogador enquanto correndo */
float Player::get_speed_running() const {
//	return get_speed_walking() * 10;
	return get_speed_walking() * 7;
}

///*! Mostra algumas informações do player para Debug */
//void Player::display(){
//#if(DEBUG_PLAYER)
//	cout << "\nHora: " << TimeControl::get_instance()->get_hora() << ":" << TimeControl::get_instance()->get_minuto() << "\nTemperatura interna do lagarto: " << player->get_temp_interna() <<
//			"\nGasto com temperatura interna: " << player->gasto_temp << "\nGasto basal: " << player->gasto_basal
//			<< "\nGasto total: " << player->get_gasto_total() << "\nFatorUmidade: " << player->fator_umidade << "\nHidratação: "
//			<< player->get_hidratacao() << "\nEnergia do lagarto: "
//			<< player->get_energia() << endl;
//#endif
//}

/*! Carrega o Player */
void Player::load_player(){
	/* Cria nó de colisão para o player */
	collision::get_instance()->playerCollision(player);

	//obtendo os níveis de camuflagem do lagarto (valores entre 0 e 1) sendo que 1 representa mais camuflado
	player->nivel_camuflagem_folhagem = ModelRepository::get_instance()->get_nivel_camuflagem_folhagem();
	player->nivel_camuflagem_sombra = ModelRepository::get_instance()->get_nivel_camuflagem_sombra();
	player->nivel_camuflagem_terreno_dia = ModelRepository::get_instance()->get_nivel_camuflagem_terreno_dia();
	player->nivel_camuflagem_terreno_noite = ModelRepository::get_instance()->get_nivel_camuflagem_terreno_noite();

	/* Atualiza tamanho do player */
//	player->set_scale(player->get_visual_size());
	player->set_pos(255,255, 0);

	/* Posicionamento inicial do Player */
	PT(Setor) setor = World::get_world()->get_terrain()->get_setor_from_pos(LPoint2d(256.0, 256.0));
	player->set_setor(setor);
	World::get_world()->get_terrain()->update_adjacent_sectors(setor);

	/* Configuracoes das Animações */
	player->set_control_effect("walk", 1.0);
	player->get_anim_control()->get_anim(0)->set_play_rate(2.5);
	PT(AnimControl) ac = player->get_anim_control()->find_anim("fast_bite");
	if(ac != NULL) ac->set_play_rate(2);

	player->reparent_to(render);
}

/*! Muda de setor alem de atualizar os setores adjacentes */
void Player::change_sector(PT(Setor) new_sector){
	this->ObjetoJogo::change_sector(new_sector);
	World::get_world()->get_terrain()->update_adjacent_sectors(new_sector);

	/* Quando o player muda de setor é necessário uma redistribuição dos npcs. */
	Animal::redistribute_animals();

	/* Quando o player muda de setor é necessário esconder alguns vegetais e mostrar outros*/
	Vegetal::update_show_hide();

	//Vegetal::show_player_next_sector_vegetation();
	//World::get_world()->get_terrain()->get_shadows()->update_active_shadows(new_sector);
}

/*! Chamado quando o player se move */
void Player::has_moved(){
	this->ObjetoJogo::has_moved();
	/* Corrige inclinação do player no terreno */
	update_pr();
}

/*! Obtém o raio de ação do player: a partir de onde os objetos tornam-se passíveis de serem comidos */
float Player::get_eat_radius_thr(){
	return get_sx() * 270;
}

/*! Verifica se o objeto passado é alcançavel pelo player (ex.: para comer ou morder) */
bool Player::reaches(PT(ObjetoJogo) object){
	if(!object || !player->get_setor()) return false;

	/* Obtem os vetores para fazer as comparações de distância e angulo */
	LVector3f player_to_target = LPoint3f(player->get_x(), player->get_y(), 0) - LPoint3f(object->get_x(), object->get_y(), 0);
	player_to_target.normalize();
	LVector3f player_y_versor = player->get_net_transform()->get_mat().get_row3(1);
	player_y_versor.normalize();

	/* Flags que definem se o objeto é alcançável tanto pela distância quanto pelo ângulo */
	bool is_reachable = object->get_distance(*player) < player->get_eat_radius_thr();
	bool is_ang_reachable = fabs(player_to_target.angle_deg(player_y_versor)) < 45;

	if(is_reachable && is_ang_reachable) return true;
	return false;
}

/*! Retorna se o player foi capturado por algum predador */
bool Player::was_captured() const {
	return _captured;
}

/*! Ação executada quando o player é capturado por um predador */
void Player::be_captured(){
	_captured = true;
	get_anim_control()->stop_all();
	nout << "Player foi capturado" << endl;
}

/*! Verifica se o player encontra-se em uma toca */
bool Player::is_in_toca() const {
	return in_toca;
}

/*! Define se o player encontra-se em uma toca */
void Player::set_in_toca(bool in_toca){
	this->in_toca = in_toca;
}

/*! Descarrega o player */
void Player::unload_player(){
	/*! Descadastra todos os hooks cadastrados */
	event_handler->remove_hook(TimeControl::EV_segundo_real, event_gasto_energia, player);
	event_handler->remove_hook(TimeControl::EV_pass_day, event_pday, player);
	event_handler->remove_hook(TimeControl::EV_pass_month, event_pmonth, player);

	instanceFlag = false;
	single->remove_node();
	single = NULL;
	//single->~Player();
}

/*! Verifica se existe alguma fêmea por perto */
bool Player::has_female_around() const {
	return _courted_female != NULL;
}

/*! Obtém qual fêmea está sendo cortejada */
PT(FemaleLizard) Player::get_courted_female() const {
	return _courted_female;
}

/*! Recalcula qual a fêmea próxima do player para interação */
void Player::update_female_around(){
	SectorItems<PT(Lizard)>* lizards = get_setor()->lizards();
	SectorItems<PT(Lizard)>::iterator it;
	for (it = lizards->begin(); it != lizards->end(); ++it) {
		PT(Lizard) lizard = *it;
		if(lizard->get_gender() == LizardGender::female){
			//float distance_player_to_female = (lizard->get_pos() - get_pos()).length();
			float distance_player_to_female = lizard->get_distance_squared(*player);
			if(distance_player_to_female < get_female_thr()*get_female_thr()){
				_courted_female = dynamic_cast<FemaleLizard*>((Lizard*) lizard);
				return;
			}
		}
	}

	_courted_female = NULL;
}

/*! Retorna o indíce de camuflagem (0 a 1) do player */
float Player::get_indice_camuflagem() const {
	float camuflagem = 0.0;

	if(is_in_toca()) camuflagem += 1.0; /* 100% camuflado */

	/* Como o índice de visão do predador é considerado se enterrado ou não, então
	 * podemos levar o fator em consideração aqui e não em predador */
	if(is_buried()) camuflagem += 1.0; /* 100% camuflado. A verificar */

	/* TODO: Distância de vegetal + Folhagem */

	if(camuflagem > 1.0) camuflagem = 1.0;

	return camuflagem;
}

/*! Retorna true se o player tem a capacidade de se enterrar.
 *  Com a capacidade de se enterrar o player se esconde melhor dos predadores,
 *  mas enquanto enterrado o lagarto tem menor inércia térmica (esquenta rápido) */
bool Player::has_bury_ability() const {
	return _bury_ability;
}

/*! Define a capacidade do player se enterrar no terreno */
void Player::set_bury_ability(bool bury_ability){
	this->_bury_ability = bury_ability;
}

/*! Retorna true se o player está atualmente enterrado */
bool Player::is_buried() const {
	return _is_buried;
}

/*! Enterra ou desenterra o player */
void Player::set_buried(bool is_buried){
	if(!_bury_ability && is_buried){
		/* Informa que o player não possui a capacidade de se enterrar */
		nout << "Player não possui capacidade de se enterrar!" << endl;
	}
	else if(_bury_ability && is_buried && !_is_buried){
		/* O player pode ser enterrado. Define o player como tal */
		_is_buried = true;

		/* TODO: Executa outras taferas (ação visual de se enterrar) */
	}
	else if(!is_buried && _is_buried){
		/* O player estava enterrado e precisa se desenterrar agora */
		/* TODO: Executa outras taferas (ação visual de se desenterrar) */
		_is_buried = false;
	}
}


/*! Obtém o tamanho da boca do lagarto */
float Player::get_mouth_size() {
	//	return _mouth_size;

//	float real_head_size = properties.head_size * get_tamanho_real() * 0.2;
//	return real_head_size * 0.8;
}

///*! Define o tamanho da boca do lagarto */
//void Player::set_mouth_size(float mouth_size){
//	_mouth_size = mouth_size;
//}

/*! Verifica se o player pode comer determinado alimento */
//bool Player::can_eat(float food_size){
//}



//exemplo de como utilizar o nivel de camuflagem para aplicar um efeito de transparência no lagarto
//Neste método o nível de camuflagem do lagarto editado vai provocar um efeito de transparência na
//textura caso ele entre na sombra.
void Player::event_psegundo_camuflagem(const Event *, void *data){
	//verifica se player está na sombra
	if(World::get_world()->get_terrain()->get_shadows()->is_in_shadow(*player, 0.1)){
		//aplica alpha - provocando efeito visual de camuflagem
		player->set_alpha_scale(1 - nivel_camuflagem_sombra/3,1); //A depender do nível de camuflagem
		//do lagarto  a intensidade do alpha muda.
	}else{//caso não esteja na sombra
		//sem alpha
		player->set_alpha_scale(1,1);
	}
}

/*Método que seta atributo como false a cada mudança de frame*/
void  Player::false_flag_under_vegetal(const Event *, void *data){
	player->set_false_verify_under_vegetal();
}
/*Quando acontece a chamada de método que verifica se player esta embaixo de uma arvore,
 *  este flag é setado falso, assim, outros predadores não chamarão o mesmo método novamente*/
void Player::set_false_verify_under_vegetal(){
	flag_verify_under_vegetal = false;
}

void Player::set_predator(PT(Predator) other){
	this->predator = other;

	if(other == NULL){//Se não houver predador, termina a música
		AudioController::get_instance()->pursuit_finished();
	}
	else if(!GuiManager::get_instance()->is_status_seta()){//Se já existir um seta criada, não se cria outra
		AudioController::get_instance()->predator_pursuing();
		GuiManager::get_instance()->activate_predator_alert(other);
	}


}

/* ------------------------------------------------------------------------- */
/* "OUTROS"
 * ------------------------------------------------------------------------- */

void Player::mordida_recebida(int lizard_relative_size){
	//TODO: Corrigir o lizard_relative_size
	float lost_energy = lizard_relative_size * 0.05;
	if(lost_energy <= 0) return;

	add_energy(-lost_energy);
	AudioController::get_instance()->heart_beat(get_energy(), get_min_energy());
	GuiManager::get_instance()->piscar_life();
}

PT(Predator) Player::get_predator(){
	return this->predator;
}

bool Player::is_under_vegetal(){
	//Verifica se o player está de baixo de um vegetal

	if(flag_verify_under_vegetal){
		/*Caso a verificação já tenha ocorrido em um frame, não ocorrerá novamente no mesmo frame,
		 *o método retorna o que já foi calculado */

		//cout<<"Calculado no mesmo frame"<<endl;
		return player_is_under_vegetal;
	}
	flag_verify_under_vegetal = true;
	//Primeiramente, verifica-se se o player está de baixo de um dos vegetais do do setor em que ele está.

	PT(Setor) setor = World::get_world()->get_terrain()->get_setor_from_pos(player->get_x(), player->get_y());
	SectorItems<PT(Vegetal)>* vegetal_list = setor->vegetals();
	SectorItems<PT(Vegetal)>::iterator it;


	for (it = vegetal_list->begin(); it != vegetal_list->end(); ++it){
		PT(Vegetal) vegetal = *it;
		LVector3f player_to_vegetal = player->get_pos() - vegetal->get_pos();
		if (player_to_vegetal.length_squared() < Predator::dist_player_hide){
			//					cout<<"Vegetal no mesmo setor"<<endl;
			player_is_under_vegetal =true;
			return player_is_under_vegetal;
		}

	}

	//Caso o player não esteja sob nenhum vegetal de seu setor, procura-se nos vegetais dos setores adjacentes


	PT(Terrain) terrain = World::get_world()->get_terrain();
	vector<PT(Setor)>* neighborhood = terrain->get_adjacent_sectors();

	for(unsigned int i = 0; i < neighborhood->size(); i++){
		vegetal_list = neighborhood->at(i)->vegetals();

		for (it = vegetal_list->begin(); it != vegetal_list->end(); ++it){
			PT(Vegetal) vegetal = *it;
			LVector3f player_to_vegetal = player->get_pos() - vegetal->get_pos();

			if (player_to_vegetal.length_squared() < Predator::dist_player_hide){
				player_is_under_vegetal = true;
				return player_is_under_vegetal;
			}
		}
	}

	player_is_under_vegetal = false;
	return player_is_under_vegetal;
}

PT(Achievements) Player::get_achievements() {
	return achievements;
}


