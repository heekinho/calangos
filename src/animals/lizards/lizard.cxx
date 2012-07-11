#include "lizard.h"

#include "world.h"
#include "terrain.h"

#include "modelRepository.h"
#include "femaleLizard.h"
#include "maleLizard.h"
#include "youngLizard.h"

#include "collision.h"
#include "utils.h"
#include "climaTempo.h"

#define MAXDEGREE 100
#define PROBTHR 80


Lizard::Lizard(NodePath node) : Animal(node){
//	bind_anims(this->node());
	init();
	//adiciona solido de colisão aos NPCs
	//collision::get_instance()->collisionNpcSlow(&node, 0, 0, get_height()*0.5, /*100.0*/get_height()*0.25);
}

Lizard::~Lizard(){
	event_handler->remove_hook(TimeControl::EV_pass_minute, check_temp, this);
}


void Lizard::init(){
	bind_anims(node());

	/* TODO: Conferir */
	set_velocity(1);

//	set_blend(true, true, PartBundle::BT_normalized_linear);

	actions["fight"] = false;
	actions["fast_bite"] = false;
	actions["bob"] = false;
	actions["walk"] = true;
	actions["flee"] = false;
	actions["bobbing"] = false;


	event_handler->add_hook(TimeControl::EV_pass_minute, check_temp, this);
	tempo_no_sol_thr = 100;
	tempo_na_sombra_thr = 150;
	tempo_no_sol = 0;
	tempo_na_sombra = 0;
	ficar_na_sombra = false;


	this->predator =  NULL;
	this->hunted = false;

//	clear_actions();
//	config_anims_to_action();
//	play_action_anims();

//	get_anim_control()->loop("walk", false);
}

/*TODO (doing) ajustar idades, tamanhos, e energias diferentes entre os NPC's.
*Os tamanhos e a energia devem ser sorteados de forma proporcional à idade.
*Os jovens (considerados abaixo de um ano) não devem ter o símbolo em cima deles,
*para indicar que eles não podem fazer reprodução nem brigar.*/
void Lizard::load_lizards(){
	nout << "Loading Lizards... " << endl;

	/* Para a primeira fase continua o que estava.
	 * TODO: Existe um property padrão para não precisar fazer esse if? */
	float lizard_density = ConfigVariableInt("calangos-density-lizards", 30);

	/* A partir da segunda fase os valores são customizados */
	if(Session::get_instance()->get_level() > 1){
		lizard_density = Player::properties.lizards_density;
	}

	/* Ter calangos do tipo do player */
	string player_specie = Player::get_species_name(Player::properties.species);

	string lizard_names[] = {
			player_specie + "/" + get_gender_name((LizardGender) 0),
			player_specie + "/" + get_gender_name((LizardGender) 1),
			player_specie + "/" + get_gender_name((LizardGender) 2)
	};

	NodePath lizard_models[3];
	lizard_models[LG_female] = ModelRepository::get_instance()->get_animated_model(lizard_names[LG_female])->copy_to(NodePath());
	lizard_models[LG_male] = ModelRepository::get_instance()->get_animated_model(lizard_names[LG_male])->copy_to(NodePath());
	lizard_models[LG_young] = ModelRepository::get_instance()->get_animated_model(lizard_names[LG_young])->copy_to(NodePath());

	for(int i = 0; i < 3; i++){
		PT(Lizard) lizard = new Lizard(lizard_models[i]);
		lizard->set_length(1);
		lizard->clear_model_nodes();
		lizard->flatten_strong();
		lizard->calc_size_from_bounds();
		lizard->bind_anims(lizard->node());
	}

	for(int i = 0; i < lizard_density; i++){
		LPoint3f point = World::get_world()->get_terrain()->get_random_point();

		/* Pronto... para criar instancias separadas, sem instancing... */

		LizardGender gender = LizardGender(rand() % 3);

		NodePath base_lizard = lizard_models[gender].copy_to(NodePath());//(*ModelRepository::get_instance()->get_animated_model(lizard_names[gender])).copy_to(NodePath());

		/* Cria o lagarto baseado no gênero */
		PT(Lizard) lizard;
		if(gender == LG_male) lizard = new MaleLizard(base_lizard);
		else if(gender == LG_female) lizard = new FemaleLizard(base_lizard);
		else lizard = new Lizard(base_lizard);

		lizard->set_gender(gender); // Não precisa
		lizard->set_species(Player::properties.species);

		/* TODO: Rever como Angelo pediu. Sortear idade e energia e calcular o tamanho. */
		if(gender == LG_young) {
			lizard->set_energia(gaussian_random(25, 15));

			//Sorteio da idade
			int x =(int) gaussian_random(6, 2);
			if(x > 12){
				lizard->age = 11;
			}			else{lizard->age = x;}
			if(x < 1){
				lizard->age = 1;
			}			else{lizard->age = x;}
		}
		else {
			lizard->set_energia(gaussian_random(60, 20));

			//Sorteio da idade
			int x =(int) gaussian_random(24, 10);
			if(x > 36){
				lizard->age = 36;
			}			else{lizard->age = x;}
			if(x < 12){
				lizard->age = 12;
			}			else{lizard->age = x;}
		}

//		lizard->set_tamanho_real(random(PlayerProperties::min_body_size * 0.2, PlayerProperties::max_body_size) * 0.01);
		lizard->set_tamanho_real(lizard->calculate_inicial_size());
		lizard->set_tamanho_base(player->calculate_lizards_relative_size(lizard->get_tamanho_real()));
		lizard->set_length(lizard->get_tamanho_real());

		nout << lizard->_size << endl;
		nout << lizard->get_scale() << endl;

		lizard->set_pos(point);
		lizard->set_h(rand()%360);

		World::get_world()->get_terrain()->add_lizard(lizard);
		lizard->reparent_to(lizard->get_setor()->get_root());

		lizard->loop_anim("walk", true);
		lizard->set_action("walk");
	}
}


float Lizard::calculate_inicial_size(){
	/* Obtem a taxa de crescimento de 0 a 1 */
	float growing_rate = this->energia * 0.01;

	/* Acima de 90% já deixamos 100% de crescimento */
	if(growing_rate >= 0.9) growing_rate = 1.0;

	/* Obtem o crescimento ideal e real */

	float min_size = PlayerProperties::max_body_size * 0.2; //Max_Size * Child_size_factor
	float ideal_grow_size = (PlayerProperties::max_body_size - min_size) / 36;//_ideal_months_to_max_size = 36
	float real_grow_size = ideal_grow_size * growing_rate;

	/* Enfim atualiza o valor do tamanho */
	float size = min_size  +(real_grow_size * this->age);
	return size/100; //Tamanho inicial

}

void Lizard::check_temp(const Event *theEvent, void *data){
	Lizard* this_lizard = (Lizard*) data;

	float temp_solo_thr = 45;
	double temp_solo = ClimaTempo::get_instance()->get_temp_solo();
	bool in_shadow = World::get_world()->get_terrain()->get_shadows()->is_in_shadow(*this_lizard);

	if(in_shadow){ this_lizard->tempo_na_sombra++; this_lizard->tempo_no_sol = 0; }
	else if(temp_solo > temp_solo_thr) { this_lizard->tempo_no_sol++; this_lizard->tempo_na_sombra = 0; }

	if(this_lizard->tempo_no_sol > this_lizard->tempo_no_sol_thr){
		this_lizard->ficar_na_sombra = true;
		this_lizard->arvore_da_sombra = this_lizard->get_setor()->vegetals()->get_closest_to(this_lizard->get_pos());
	}
	if(this_lizard->tempo_na_sombra > this_lizard->tempo_na_sombra_thr) this_lizard->ficar_na_sombra = false;
}

void Lizard::act(){
	/*Se o lizard estiver sendo caçado, ele não caminhará para a sombra inicialmente
	 * primeiro, ele fugirá, e somente depois, procurará por um novo vegetal para se
	 * esconder do predador*/

	if(ficar_na_sombra && (arvore_da_sombra != NULL) && !hunted){
		if(! World::get_world()->get_terrain()->get_shadows()->is_in_shadow(*this)){
			look_at(*arvore_da_sombra);
			move(get_velocity()*1.5);
//			cout<<"Tamanho"<<this->get_scale().get_x()<<endl;
			return;
		}
	}
	else{
		Animal::act();
	}
	//Se o lizard estiver sendo caçado
	if(hunted){
			//flee(*predator);
		if(this->hide_from_predator()){
			flee(*predator);
		}


	}
	else{
		Animal::act();
	}

}



void Lizard::flee(){
	flee(*player);

}

void Lizard::flee(const NodePath &other){
//	if(!has_other_anim_active("walk")){
		play_anim("walk");

		/* Comportamento */
		look_at(other);  //TODO: Corrigir depois para não permitir muito giro.
		set_h(*this, 180); // Corrige modelo errado

		this->move(get_velocity()*4);

//	}
}

/*! se esconder na árvore mais próxima dele */
bool Lizard::hide_from_predator(){
//	cout << this->get_setor()->vegetals()->size() << endl;

	//Atualização de árvore mais proxima
	this->arvore_da_sombra = this->get_setor()->vegetals()->get_closest_to(this->get_pos());
//	if(this->arvore_da_sombra == NULL){
//		flee(*predator);
//		return false;
//	}
//Verifica se o lizard está mais próximo da árvore que o predador
	float predator_arvore = predator->get_distance_squared(arvore_da_sombra->get_pos());
	float lizard_arvore = this->get_distance(arvore_da_sombra->get_pos());
	if(lizard_arvore < predator_arvore){
		if(!has_other_anim_active("walk")){

				play_anim("walk");
				look_at(*arvore_da_sombra);
				this->move(get_velocity()*4);
				return true;
			}
	}
	else{
//		flee(*predator);
		return false;
	}
}

PT(Vegetal) Lizard::get_arvore_da_sombra(){
	return this->arvore_da_sombra;
}

void Lizard::change_sector(PT(Setor) new_sector){
	get_setor()->lizards()->remove(this);
	new_sector->lizards()->push_back(this);

//Se o novo setor do lizard não estiver próximo do player, ele deixará de ser perseguido.
//	if(!new_sector->get_is_closest_sector()){
//		this->predator->get_prey() = NULL;
//
//		this->predator->set_huntig(false);
//		this->predator = NULL;
//
//	}

	reparent_to(get_setor()->get_root());
         //mudando de nodepath
        //this->reparent_to(Terrain::create_default_terrain()->no_setores[new_sector->get_indice()]);
}

void Lizard::set_predator(PT(Predator) other){
	this->predator = other;
}

PT(Predator) Lizard::get_predator(){
	return this->predator;
}


float Lizard::get_tamanho_base(){
	return this->tamanho_base;
}

float Lizard::get_tamanho_real(){
	return this->tamanho_real;
}

void Lizard::set_tamanho_base(float novo_tamanho_base){
	this->tamanho_base = novo_tamanho_base;
}

void Lizard::set_tamanho_real(float novo_tamanho_real){
	this->tamanho_real = novo_tamanho_real;
}

/*! Aciona alguma ação */
void Lizard::set_action(string action, bool turn_off_others){
	if(turn_off_others) clear_actions();
	actions[action] = true;
}

/*! Verifica se tem outra ação ativa além da própria action passada */
bool Lizard::has_other_action_active(string action){
	map<string, bool>::iterator it;
	for(it = actions.begin(); it != actions.end(); it++){
		if(actions[action] == true && action != it->first) return true;
	}
	return false;
}

bool Lizard::has_other_anim_active(string action){
	map<string, bool>::iterator it;
	for(it = actions.begin(); it != actions.end(); it++){
		PT(AnimControl) ac = get_anim_control()->find_anim(it->first);
		if(ac != NULL){
			if(ac->is_playing() && it->first != action) return true;
		}
	}
	return false;
}

/*! Seta todas as ações para false */
void Lizard::clear_actions(){
	map<string, bool>::iterator it;
	for(it = actions.begin(); it != actions.end(); it++){
		it->second = false;
	}
}

void Lizard::config_anims_to_action(){
	map<string, bool>::iterator it;
	for(it = actions.begin(); it != actions.end(); it++){
		/* Sem "blend gradiente" ainda */
//		if(it->second) set_control_effect(it->first, 1.0);
//		else set_control_effect(it->first, 0.0);
		if(it->second) set_control_effect(it->first, 1.0);
		else set_control_effect(it->first, 0.0);
	}
}


void Lizard::play_action_anims(bool loop){
	map<string, bool>::iterator it;
	for(it = actions.begin(); it != actions.end(); it++){
		PT(AnimControl) ac = get_anim_control()->find_anim(it->first);
		/* Sem "blend gradiente" ainda */
		if(ac != NULL && !get_anim_control()->is_playing()){
			if(it->second){
				if(!ac->is_playing() && is_activated()){
					if(loop) ac->loop(false);
					else ac->play();
				}
			}
			else ac->stop();
		}
	}
}


void Lizard::pause_animation(){
	clear_actions();
	get_anim_control()->stop_all();
}

void Lizard::continue_animation(){
	if(render.is_ancestor_of(*this)){
		set_action("walk", true);
		play_anim("walk");
	}
}
