#include "player.h"
#include "menu.h"
#include "modelRepository.h"

#define DEBUG_PLAYER 0

bool Player::instanceFlag = false;
PT(Player) Player::single = NULL;

Player::lizardEpecie Player::lizard_specie = Player::eurolophosaurus;
Player::lizardGender Player::lizard_gender = Player::young;

Player::Player() : AnimatedObjetoJogo(*ModelRepository::get_instance()->get_animated_model(
	Player::get_specie_name(Player::lizard_specie) + "/" +
	Player::get_gender_name(lizard_gender))){
	in_toca = false;
	toca_index = -1;
	female_around = false;

	//int especie = Menu::get_instance()->get_especie();
	load_health(Menu::get_instance()->get_especie());

	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_segundo_real, event_gasto_energia, this);
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_day, event_pday, this);
	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_month, event_pmonth, this);
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
void Player::eat(Edible* food){
	add_energia_alimento(food->get_nutritional_value());
	add_hidratacao_alimento(food->get_hydration_value());
}

double Player::get_velocity(){
	return this->velocity;
}

void Player::set_velocity(double velocity){
	this->velocity = velocity;
}

void Player::display(PT(Player) player){
	#if(DEBUG_PLAYER)
	    cout << "\nHora: " << TimeControl::get_instance()->get_hora() << ":" << TimeControl::get_instance()->get_minuto() << "\nTemperatura interna do lagarto: " << player->get_temp_interna() <<
		"\nGasto com temperatura interna: " << Player::get_instance()->get_gasto_temp() << "\nGasto basal: " << Player::get_instance()->get_gasto_basal()
		<< "\nGasto total: " << Player::get_instance()->get_gasto_total() << "\nFatorUmidade: " << Player::get_instance()->fator_umidade << "\nHidrata��o: "
		<< Player::get_instance()->get_hidratacao() << "\nEnergia do lagarto: "
		<< Player::get_instance()->get_energia() << endl;
	#endif
}

/** Carrega o Player */
void Player::load_player(){
	/* Configurações do PC */
	//Player::get_instance("models/lizards/tropidurus/female/model.egg");
	//Player::get_instance(new Player(ModelRepository::get_instance()->get_animated_model("tropidurus/female"));

	/* [ATENCAO] Esta sendo chamado o primeiro Player::get_instance em ModelRepository */
	//Player::get_instance((PT(AnimatedObjetoJogo)) ModelRepository::get_instance()->get_animated_model("tropidurus/female"));

	Player::get_instance()->set_scale(Player::get_instance()->tamanho_lagarto_real);
	Player::get_instance()->set_pos(255,255, 0);

	/* Posicionamento inicial do Player */
	PT(Setor) setor = World::get_default_world()->get_terrain()->get_setor_from_pos(LPoint2d(256.0, 256.0));
	Player::get_instance()->set_setor(setor);
	World::get_default_world()->get_terrain()->update_adjacent_sectors(setor);

	/* Configuracoes das Animacoees */
	Player::get_instance()->set_blend(true, true, PartBundle::BT_normalized_linear);
	Player::get_instance()->set_control_effect("walk", 1.0);
	Player::get_instance()->get_anim_control()->get_anim(0)->set_play_rate(2.5);
	Player::get_instance()->set_control_effect("bobbing", 0);
	Player::get_instance()->set_control_effect("fast_bite", 0);
	PT(AnimControl) ac = Player::get_instance()->get_anim_control()->find_anim("fast_bite");
	if(ac != NULL) ac->set_play_rate(2);

	Player::get_instance()->reparent_to(Simdunas::get_window()->get_render());
}

/*! Muda de setor alem de atualizar os setores adjacentes */
void Player::change_sector(PT(Setor) new_sector){
	this->ObjetoJogo::change_sector(new_sector);
	World::get_default_world()->get_terrain()->update_adjacent_sectors(new_sector);

	/* Quando o player muda de setor é necessário uma redistribuição dos npcs. */
	Animal::redistribute_animals();
	
 	/* Quando o player muda de setor é necessário esconder alguns vegetais e mostrar outros*/
	Vegetal::update_show_hide();

 	//Vegetal::show_player_next_sector_vegetation();
 	//World::get_default_world()->get_terrain()->get_shadows()->update_active_shadows(new_sector);
}

void Player::has_moved(){
	this->ObjetoJogo::has_moved();
	update_pr();
}

bool Player::is_in_toca(){
	return in_toca;
}
void Player::set_in_toca(bool in_toca){
	this->in_toca = in_toca;
}

int Player::get_toca_index(){
	return toca_index;
}
void Player::set_toca_index(int toca_index){
	this->toca_index = toca_index;
}

void Player::unload_player(){

	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_segundo_real, event_gasto_energia, Player::get_instance());
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_day, event_pday, Player::get_instance());
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_month, event_pmonth, Player::get_instance());

	instanceFlag = false;
	single->remove_node();
	single = NULL;
	//single->~Player();
}

bool Player::has_female_around(){
	return female_around;
}

void Player::update_female_around(){
	float dist_thr = 5.0;

	vector<PT(Lizard)>* lizards = this->get_setor()->get_lizards();
	for(int i = 0; i < lizards->size(); i++){
		Lizard* lizard = lizards->at(i);
		if(lizard->get_gender() == LizardGender::female){
			float distance_player_to_female = (lizard->get_pos() - get_pos()).length();
			if(distance_player_to_female < dist_thr){
				this->female_around = true;
				return;
			}
		}
	}

	this->female_around = false;
}
