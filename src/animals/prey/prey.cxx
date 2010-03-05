#include "prey.h"

#include "spider.h"
#include "world.h"
#include "terrain.h"
#include "modelRepository.h"

#define MAXDEGREE 100
#define VELOCITY 0.085
#define PROBTHR 80

Prey::Prey(NodePath node) : Animal(node) {};

void Prey::load_prey(){
		nout << "Carregando Aranhas..." << endl;
		Spider::load_spiders(100);

		nout << "Carregando Besouros..." << endl;
		load_prey_specie("besouro", 100, 0.0002);

		nout << "Carregando Cupins..." << endl;
		load_prey_specie("cupim", 100, 0.0001);

		nout << "Carregando Formigas..." << endl;
		load_prey_specie("formiga", 100, 0.0002);

		nout << "Carregando Grilo..." << endl;
		load_prey_specie("grilo", 100, 0.0002);

		nout << "Carregando Larvas..." << endl;
		load_prey_specie("larva", 100, 0.0002);
}


/*! Carrega cada tipo diferente de presa: aranha, grilo... */
void Prey::load_prey_specie(const string name, int qtd, double scale){
	// Define alguma características do modelo fixo (e não das instâncias). Obs.: Talvez isso mude de lugar mais tarde.
	ModelRepository::get_instance()->get_animated_model(name)->get_anim_control()->loop("character", false);
	ModelRepository::get_instance()->get_animated_model(name)->set_scale(scale);
	ModelRepository::get_instance()->get_model(name)->set_scale(scale);

	for(int i = 0; i < qtd; i++){
		/* Cria nova instância de cada Presa. */
		PT(Prey) current_prey = new Prey(NodePath("Prey PlaceHolder"));
		ModelRepository::get_instance()->get_animated_model(name)->instance_to(*current_prey);

		/* Guarda a informação para uso na troca de modelo animado/não-animado */
		current_prey->set_tag("model_name", name);

		/* Gera localização aleatória. */
		LPoint3f point = World::get_default_world()->get_terrain()->get_random_point();
		current_prey->set_pos(point);

		/* Adiciona os animais ao mundo. */
		World::get_default_world()->get_terrain()->add_animal( (PT(Animal)) current_prey);

		/* Finalmente o torna disponível pra visualização. */
		current_prey->reparent_to(Simdunas::get_window()->get_render());
	}
}


/*! Define o comportamento padrão das presas. */
void Prey::act(){
	float elapsed = TimeControl::get_instance()->get_elapsed_time();

	if(acting && !stay_quiet()){
		if(rand()%PROBTHR == 34) set_h(*this, rand()%MAXDEGREE - (MAXDEGREE/2));

		move(VELOCITY);
	}
}


/*! Pausa a animação, neste caso fazendo o link com o modelo não-animado */
void Prey::pause_animation(){
	node()->remove_all_children();
	ModelRepository::get_instance()->get_model(get_tag("model_name"))->instance_to(*this);
}

/*! Continua a animação, neste caso fazendo o link com o modelo animado */
void Prey::continue_animation(){
	node()->remove_all_children();
	ModelRepository::get_instance()->get_animated_model(get_tag("model_name"))->instance_to(*this);
}
