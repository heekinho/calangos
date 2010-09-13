#include "lizard.h"

#include "world.h"
#include "terrain.h"

#include "modelRepository.h"
#include "femaleLizard.h"
#include "maleLizard.h"
#include "youngLizard.h"

#include "collision.h"

#define VEL_WALK 1000.0
#define VEL_RUN 5000.0

#define MAXDEGREE 100
#define PROBTHR 80


Lizard::Lizard(NodePath node) : Animal(node){
	bind_anims(this->node());
	init();
        //adiciona solido de colisão aos NPCs
       collision::get_instance()->collisionNpcSlow(&node, 0, 0, 0, 100.0);
}

Lizard::~Lizard(){
	Simdunas::get_evt_handler()->remove_hook(TimeControl::EV_pass_minute, check_temp, this);
}


void Lizard::init(){
	bind_anims(node());

//	set_blend(true, true, PartBundle::BT_normalized_linear);

	actions["fight"] = false;
	actions["fast_bite"] = false;
	actions["bob"] = false;
	actions["walk"] = true;
	actions["flee"] = false;
	actions["bobbing"] = false;


	Simdunas::get_evt_handler()->add_hook(TimeControl::EV_pass_minute, check_temp, this);
	tempo_no_sol_thr = 100;
	tempo_na_sombra_thr = 150;
	tempo_no_sol = 0;
	tempo_na_sombra = 0;
	ficar_na_sombra = false;

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

	/* Ter calangos do tipo do player */
	string player_specie = Player::get_specie_name(Player::lizard_specie);

	int qtd = 100;

	for(int i = 0; i < qtd; i++){
		LPoint3f point = World::get_world()->get_terrain()->get_random_point();

		/* Pronto... para criar instancias separadas, sem instancing... */
	
		PT(Lizard) lizard;
		string gender_name;
		int gender = rand()%3;


		if(gender == 0) {
			gender_name = "male";
			string lizard_name = player_specie + "/" + gender_name;
			NodePath base_lizard = (*ModelRepository::get_instance()->get_animated_model(lizard_name)).copy_to(NodePath());
			lizard = new MaleLizard(base_lizard);

			lizard->energia = ClimaTempo::get_instance()->random_normal(60, 20);
			//0.0021 = 0.0025 - 0.0004 => tamanho máximo - tamanho mínimo
			lizard->scale_temp = ((0.0021/100)* lizard->get_energia()) + 0.0004;
			lizard->set_tamanho_real(ClimaTempo::get_instance()->random_normal(lizard->scale_temp, 0.0001));
			lizard->set_tamanho_base(Player::get_instance()->calc_tamanho_base(lizard->get_tamanho_real()));
			//lizard->scale = ClimaTempo::get_instance()->random_normal(lizard->scale_temp, 0.0001);
		}
		else if(gender == 1){
			gender_name = "female";
			string lizard_name = player_specie + "/" + gender_name;
			NodePath base_lizard = (*ModelRepository::get_instance()->get_animated_model(lizard_name)).copy_to(NodePath());
			lizard = new FemaleLizard(base_lizard);

			lizard->energia = ClimaTempo::get_instance()->random_normal(60, 20);
			//0.0021 = 0.0025 - 0.0004 => tamanho máximo - tamanho mínimo
			lizard->scale_temp = ((0.0021/100)* lizard->get_energia()) + 0.0004;
			lizard->set_tamanho_real(ClimaTempo::get_instance()->random_normal(lizard->scale_temp, 0.0001));
			lizard->set_tamanho_base(Player::get_instance()->calc_tamanho_base(lizard->get_tamanho_real()));
			//lizard->scale = ClimaTempo::get_instance()->random_normal(lizard->scale_temp, 0.0001);
		}
		else {
			gender_name = "young";
			string lizard_name = player_specie + "/" + gender_name;
			NodePath base_lizard = (*ModelRepository::get_instance()->get_animated_model(lizard_name)).copy_to(NodePath());
			// TODO: Qual comportamento dos Youngs?
			lizard = new YoungLizard(base_lizard);

			//como os lagartos jovens não irão brigar, a energia serve apenas para determinar o tamanho
			lizard->energia = ClimaTempo::get_instance()->random_normal(10, 3);
			//0.0021 = 0.0025 - 0.0004 => tamanho máximo - tamanho mínimo
			lizard->scale_temp = ((0.0021/100)* lizard->get_energia()) + 0.0004;
			lizard->set_tamanho_real(ClimaTempo::get_instance()->random_normal(lizard->scale_temp, 0.0001));
			lizard->set_tamanho_base(Player::get_instance()->calc_tamanho_base(lizard->get_tamanho_real()));
			//lizard->scale = ClimaTempo::get_instance()->random_normal(lizard->scale_temp, 0.00001);
		}
		
		//cout << "Scale: " << lizard->tamanho_real << endl;
		lizard->set_pos(point);
		lizard->set_h(rand()%360);
		lizard->set_scale(lizard->tamanho_real);
		//lizard->set_scale(0.0003);
		//lizard->set_hpr(180,0,0);
		lizard->set_velocity(500);

		World::get_world()->get_terrain()->add_lizard(lizard);
		lizard->get_anim_control()->find_anim("walk")->loop(true);

lizard->wrt_reparent_to(Terrain::create_default_terrain()->no_setores[Terrain::create_default_terrain()->get_setor_from_pos(lizard->get_x(),lizard->get_y())->get_indice()].node());
                //lizard->reparent_to(Simdunas::get_window()->get_render());

		//lizard->tamanho = ClimaTempo::get_instance()->random_normal(60, 20);
		//lizard->energia = ClimaTempo::get_instance()->random_normal(60, 20);
                
		lizard->set_action("walk");
	}
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
	if(ficar_na_sombra && (arvore_da_sombra != NULL)){
		if(! World::get_world()->get_terrain()->get_shadows()->is_in_shadow(*this)){
			look_at(*arvore_da_sombra);
			move(get_velocity()*1.5);
			return;
		}
	}
	Animal::act();
}


void Lizard::flee(){
	PT(Player) player = Player::get_instance();

	if(!has_other_anim_active("walk")){
		if(!get_anim_control()->is_playing("walk")) get_anim_control()->play("walk");

		/* Comportamento */
		look_at(*player);  //TODO: Corrigir depois para não permitir muito giro.
		set_h(*this, 180); // Corrige modelo errado

		this->move(VEL_RUN);
	}
}



void Lizard::change_sector(PT(Setor) new_sector){
	get_setor()->lizards()->remove(this);
	new_sector->lizards()->push_back(this);

        SectorItems<PT(Lizard)>::iterator it;//MUDANDO OS PREYS PARA O NÓ DO SETOR
        for(it=get_setor()->lizards()->begin();it!=get_setor()->lizards()->end();it++){
           PT(Lizard) tem= *it;
           tem->reparent_to(Terrain::create_default_terrain()->no_setores[new_sector->get_indice()].node());

        }
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
				if(!ac->is_playing()){
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
	set_action("walk", true);
	if(!get_anim_control()->is_playing("walk")) get_anim_control()->play("walk");
}
