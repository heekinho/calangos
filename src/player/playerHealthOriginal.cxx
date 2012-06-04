#include "player.h"
#include "modelRepository.h"
#include "textureStageCollection.h"
#include "audioController.h"

#include "playerHealth.h"
#include "playerHealthSimulator.h"
#include "energySimulator.h"
#include "temperatureSimulator.h"
#include "morfologySimulator.h"
#include "hydrationSimulator.h"
#include "dietSimulator.h"

#include "microClima.h"
#include "guiManager.h"
#include "texturePool.h"

/* Bloco de constantes
 * ------------------------------------------------------------------------- */
/* Idade, em meses, na qual o lagarto poderá se reproduzir */
#define IDADE_REPRODUTIVA 12
/* Idade, em meses, em que o lagarto deve morrer */
#define IDADE_MORTE 36

/* Debugar */
#define DEBUG_PHEALTH 0
/* ------------------------------------------------------------------------- */

#include "load_prc_file.h"

/*! Carrega informações customizadas da saúde do lagarto (para fase 2) */
void Player::load_custom_health(){

	if(Session::get_instance()->get_level() > 1){
		/* Configurações para a fase 2 */
		/* Dá um valor de 0 a 1 para as possíveis escolhas de velocidade */
		velocity_factor = (properties.speed - properties.min_speed) /
								  (properties.max_speed - properties.min_speed);

		/* Configura a temperatura ideal */
//		set_temp_interna_ideal(properties.ideal_tempature);

		/* Configura a capacidade de se enterrar */
		/* Seria melhor deixar em properties ao invés de criar uma nova variável? */
		set_bury_ability(properties.bury_ability);
	}
}

void Player::load_health(){
	string lizard_name = get_species_name();

	/* Novo sistema */
	player_health = new PlayerHealth();
	/* if fase1 ... */
	player_health->load_health("config/lizard-" + lizard_name + ".prc");

	player_health_simulator = new PlayerHealthSimulator(player_health);

	load_custom_health();

//	//considera o lagarto parado no início do jogo
	gasto_movimento = 1;
	idade = 0;
	num_ovos = 0;

//	calculate_visual_size_factor();
//	set_scale(render, get_visual_size());
	set_length(get_size()*0.01);
}

/* EVENTOS
 * ------------------------------------------------------------------------- */

/* Evento chamado a cada minuto virtual para atualização dos valores */
void Player::event_gasto_energia(const Event*, void *data){
	player->get_achievements()->check_temperature(player->get_temperature());
	player->get_achievements()->check_hydration(player->get_hydration());
	player->get_achievements()->check_energy(player->get_energy());

	Player::PlayerDeathType death = player->check_death();
	if(death != Player::PDT_NOT_DEAD) Session::get_instance()->player_death(death);
}

/*! Verifica se o player morreu e retorna o tipo de morte.
 *  Se não morreu retorna Player::PDT_NOT_DEAD */
Player::PlayerDeathType Player::check_death() const {
	if(player->get_energy() <= player->get_min_energy())
		return Player::PDT_MALNUTRITION;
	if(player->get_temperature() >= player->get_max_temperature())
		return Player::PDT_HIGH_TEMPERATURE;
	if(player->get_temperature() <= player->get_min_temperature())
		return Player::PDT_LOW_TEMPERATURE;
	if(player->get_hydration() < player->get_min_hydration())
		return Player::PDT_DEHYDRATION;
	if (player->idade >= IDADE_MORTE)
		return Player::PDT_OLD_AGE;

	return Player::PDT_NOT_DEAD;
}

/*! TODO: Esse tipo de coisa não deveria ser estático */
float Player::calculate_lizards_relative_size(float lizard_size) const {
	return player_health_simulator->get_morfology_simulator()->calculate_relative_size(lizard_size);
}


/*! Na passagem do dia, faz a média diária de energia, e armazena a soma.
 *   Essa média servirá para determinar o quanto o lagarto irá crescer na passagem de um mês.*/
void Player::event_pday(const Event*, void *data){

}

/*! Na passagem do mês, faz a média de energia dos dias do mês que passou.
 *  Essa média servirá para determinar o quanto o lagarto irá crescer na passagem do mês.*/
void Player::event_pmonth(const Event*, void *data){
	/* Ajusta o novo tamanho do personagem */
	player->set_length(player->get_size() * 0.01);

	/* Aumenta a idade do lagarto */
	player->idade++;
	player->get_achievements()->inc_meses_sobrevivente();

	/* Só deve ser feita a mudança uma vez: Evento de borda */
	if(player->is_young() && player->get_estado_reprodutivo()){
		/* Deveria mandar evento */
		GuiManager::get_instance()->liga_led_estado_reprodutivo();

		if (!ModelRepository::get_instance()->get_lagarto_personalizado()) { //caso seja o lagarto personalizado não trocar a textura
			PT(TextureStage) ts = player->find_all_texture_stages().get_texture_stage(0);
			ts->set_mode(TextureStage::M_modulate);
			PT(Texture) tex = TexturePool::load_texture("models/lizards/"
					+ player->get_species_name()
					+ "/male/texture.jpg");
			player->set_texture(ts, tex, 2);
		}

		player->set_gender(LizardBase::LG_male);
	}
}

double Player::get_environment_temp(){
	if(in_toca){
		return MicroClima::get_instance()->get_temp_toca_sector();
	}else{
		return MicroClima::get_instance()->get_temp_solo_sector();
	}
}

int Player::get_idade(){
	return this->idade;
}

bool Player::get_estado_reprodutivo(){
	/*if(Session::get_instance()->get_level() > 1) return get_tamanho_real() > get_max_size() * 0.7;
	else */ return idade >= IDADE_REPRODUTIVA;
}

int Player::get_num_ovos(){
	return this->num_ovos;
}


/* Vai fazer o gasto do lagarto igual ao basal */
void Player::set_lagarto_parado(){
	this->gasto_movimento = 1;
}

const float min_mult = 1.2;	 /* Mínima velocidade andando  */
const float max_mult = 2.0;  /* Máxima velocidade correndo */

float get_cost_multiplier(float speed){
	float min_speed_walking = PlayerProperties::min_speed;
	float max_speed_running = PlayerProperties::max_speed * 10;

	float tgteta = (max_mult - min_mult) / (max_speed_running - min_speed_walking);
	return (tgteta * (speed - min_speed_walking) + min_mult);
}

/* Vai fazer o gasto do lagarto 20% maior que o basal */
void Player::set_lagarto_andando(){
	this->gasto_movimento = 1.2;

	if(Session::get_instance()->get_level() > 1){
		this->gasto_movimento = get_cost_multiplier(get_speed_walking());
		//nout << gasto_movimento << endl;
	}
}

/*! Vai fazer o gasto do lagarto 50% maior que o basal */
void Player::set_lagarto_correndo(){
	this->gasto_movimento = 1.5;

	if(Session::get_instance()->get_level() > 1){
		this->gasto_movimento = get_cost_multiplier(get_speed_running());
		//nout << gasto_movimento << endl;
		//this->gasto_movimento = (this->gasto_movimento * (1.0 + velocity_factor)) - (range * 0.5);
	}
}

void Player::add_eggs(){
	this->num_ovos++;
	this->achievements->inc_reprodutor();
}


/* ------------------------------------------------------------------------- */
/* Facade adders
 * ------------------------------------------------------------------------- */
/*! Adiciona um valor de energia relativo ao alimento em questão */

void Player::add_energy(float energy){
	player_health_simulator->get_energy_simulator()->add_energy(energy);
}

void Player::add_food_energy(float food_energy){
	if (food_energy < -0.1) {
		AudioController::get_instance()->heart_beat(get_energy(), get_min_energy());
		AudioController::get_instance()->only_play(AudioRepository::PREDATOR_HIT);
		cout << "Resetando contador intocavel!" << endl;
		player->get_achievements()->reset_count_secs_untouched();
	}

	player_health_simulator->get_energy_simulator()->add_food_energy(food_energy);
//	this->energia_alimento = this->energia_alimento + food_energy;
//	this->energia_alimento_acumulada+=food_energy;
}

/*! Adiciona um valor de hidratação relativo ao alimento em questão */
void Player::add_food_hydration(float food_hydration){
	player_health_simulator->get_hydration_simulator()->add_food_hydration(food_hydration);
}


/* ------------------------------------------------------------------------- */
/* Facade - getters
 * ------------------------------------------------------------------------- */
/*! Obtém o valor de energia do lagarto.
 *  @see EnergySimulator.get_energy() */
float Player::get_energy() const {
	return player_health_simulator->get_energy_simulator()->get_energy();
}

/*! Obtém o valor mínimo de energia que o lagarto pode ter antes de morrer.
 *  @see PlayerHealth.min_energy */
float Player::get_min_energy() const {
	return player_health->min_energy;
}

/*! Obtém o valor de hidratação do lagarto
 *  @see HydrationSimulator.get_hydration() */
float Player::get_hydration() const {
	return player_health_simulator->get_hydration_simulator()->get_hydration();
}

/*! Obtém o valor mínimo de hidratação que o lagarto pode ter antes de morrer
 *  @see PlayerHealth.min_hydration */
float Player::get_min_hydration() const {
	return player_health->min_hydration;
}

/*! Obtém o valor de temperatura interna do lagarto */
float Player::get_temperature() const {
	return player_health_simulator->get_temperature_simulator()->get_temperature();
}

/*! Obtém o valor ideal de temperatura interna do lagarto */
float Player::get_ideal_temperature() const {
	return player_health->ideal_temperature;
}

/*! Obtém o valor máximo aceitável de temperatura interna do lagarto */
float Player::get_max_temperature() const {
	return player_health->max_temperature;
}

/*! Obtém o valor mínimo aceitável de temperatura interna do lagarto */
float Player::get_min_temperature() const {
	return player_health->min_temperature;
}

/*! Obtém o valor mínimo aceitável de temperatura interna do lagarto */
float Player::get_lethargy() const {
	return player_health_simulator->get_temperature_simulator()->get_lethargy();
}

/*! Obtém o tamanho relativo do lagarto, de 0 a 1, sendo 0 o menor e 1 o maior */
float Player::get_relative_size() const {
	return player_health_simulator->get_morfology_simulator()->get_relative_size();
}

/*! Obtém o tamanho em centímentros do lagarto */
float Player::get_size() const {
	return player_health_simulator->get_morfology_simulator()->get_size();
}

/*! Obtém o tamanho máximo que o player poderá atingir. Este é o valor que deve
 *  ser especificado no editor de personagens */
float Player::get_max_size() const {
	return properties.body_size;
}

/*! Obtém o tamanho (comprimento) máximo de lagarto permitido. Em centímetros.
 * Este valor é especificado com o lagarto em sua idade máxima */
float Player::get_max_lizards_size() {
	return properties.max_body_size;
}

/*! Obtém o tamanho (comprimento) mínimo de lagarto permitido. Em centímetros.
 *  Este valor é especificado com o lagarto em sua idade máxima */
float Player::get_min_lizards_size() {
	return properties.min_body_size;
}
