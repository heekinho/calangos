#ifndef PLAYER_H
#define PLAYER_H

#include "animatedObjetoJogo.h"
#include "edible.h"
#include "playerProperties.h"
#include "achievements.h"

#include "lizardBase.h"

// Forward Declaration
//class AnimatedObjetoJogo;
class MicroClima;
class Vetores;
class PlayerHealth;
class PlayerHealthSimulator;
class FemaleLizard;
class Predator;

/*! A classe Player é responsável por criar o Jogador que será controlado pelo
 * usuário.<br> Representada como objeto de jogo. Suas tarefas de controle, ficam
 * sob responsabilidade da classe playerControl */
class Player : public AnimatedObjetoJogo, public LizardBase {
public:
	enum PlayerDeathType {
		PDT_NOT_DEAD,
		PDT_MALNUTRITION,
		PDT_DEHYDRATION,
		PDT_HIGH_TEMPERATURE,
		PDT_LOW_TEMPERATURE,
		PDT_OLD_AGE
	};

	enum PlayerState {
		PA_idle,
		PA_walking,
		PA_running,
		PA_eating,
		PA_bobbing,
		PA_reproducing,
		PA_buried,
		PA_in_hole,
		PA_fighting,
		PA_died
	};

	PT(PlayerHealth) player_health;
	PT(PlayerHealthSimulator) player_health_simulator;

	static PlayerProperties properties;

	~Player();

	// Modelo singleton, ao iniciar utilizar os parametros
	static PT(Player) get_instance();

	static void load_player();
	void load_health();
	void load_custom_health();


	//Descarrega qualquer referência de objeto da classe player da memória, para que possa ser recriado
	static void unload_player();


	virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector);

	void eat(Edible* food, int type = 2);

	//static const float BITE_THR = 3.0;
	float get_eat_radius_thr();
	float get_toca_thr(){ return 0.3; };
	float get_female_thr(){ return 5.0; };

	bool reaches(PT(ObjetoJogo) object);

	bool was_captured() const;
	void be_captured();

	/*! PlayerHealth - (playerHealth.cxx)
	 *  Relacionado com as variáveis de saúde do lagarto.
	 *  ----------------------------------------------------- */
	/* Evento periódico de gasto de energia (é preciso criar) */
	static void event_gasto_energia(const Event *, void *data);

    /* No evento de passagem do dia, esse método será chamado */
	static void event_pday(const Event *, void *data);
	/* No evento de passagem do dia, esse método será chamado */
	static void event_pmonth(const Event *, void *data);

	double get_environment_temp();


	float get_speed_walking() const;
	float get_speed_running() const;
	/* Should be a vector */
	double get_velocity() const;

	float velocity_factor;


	int get_idade();
	PT(Achievements) get_achievements();

	Player::PlayerDeathType check_death() const;

	static void event_psegundo_camuflagem(const Event *, void *data);
	static void false_flag_under_vegetal(const Event *, void *data);

private:
	float visual_size_factor;
//	float max_size;

	// Armazena os níveis de camuflagem  do player editado para variadas situações:
	static float nivel_camuflagem_terreno_dia;
	static float nivel_camuflagem_terreno_noite;
	static float nivel_camuflagem_sombra;
	static float nivel_camuflagem_folhagem;

	PT(Achievements) achievements;


public:
	bool get_estado_reprodutivo();
	int get_num_ovos();
	/* ------------------------------------------------------------------------- */

	void set_velocity(double velocity);


	void set_lagarto_parado();
	void set_lagarto_andando();
	void set_lagarto_correndo();

	bool is_in_toca() const ;
	void set_in_toca(bool is_in_toca);

	PT(ObjetoJogo) get_toca(){ return _toca; };
	void set_toca(PT(ObjetoJogo) toca){ _toca = toca; };
private:
	PT(ObjetoJogo) _toca;
public:

	/* Recebe o tamanho do lagarto que mordeu, e calcula um gasto de energia e
	 * hidrataçao proporcionalmente */
	void mordida_recebida(int tamanho_lagarto_base);

	/* Incrementa em 1, a quantidade de ovos desse lagarto.
	 * Esse valor está associado ao sucesso do lagarto nas reproduções (quanto mais melhor).*/
	void add_eggs();

	/* Corrige a orientação dos modelos */
	virtual int is_inverted(){ return -1; };

private:
	/* Controle Singleton */
	Player();
	static bool instanceFlag;
	static PT(Player) single;

	bool _captured;

	/* Velocidade do lagarto */
	double velocity;

	/* Variável que será multiplicada ao gasto basal, e controlará o gasto
	 * adicional por movimentação */
	float gasto_movimento;

	/* Informa se o lagarto está na toca ou não */
	bool in_toca;

	/* Armazena a idade do lagarto, em meses */
	int idade;
	/* Número de ovos */
	int num_ovos;

	/* Armazena os valores das variáveis 'finais' (energia, hidratação, temperatura interna) no vetor
	 * da classe vector. Esses valores servirão para a geração dos gráficos no tempo. */
	void atualiza_vector();

	/* Guarda referencia para os vetores que armazenarão o histórico das variáveis de saúde do lagarto*/
	Vetores* vetores;

public:
	/* Procura fêmeas em um raio próximo */
	bool has_female_around() const;
	void update_female_around();
	PT(FemaleLizard) get_courted_female() const;
private:
	//bool female_around;
	PT(FemaleLizard) _courted_female;

	PT(Predator) predator;


public:
	void set_predator(PT(Predator) other);
	PT(Predator) get_predator();

	float get_indice_camuflagem() const;

	bool is_buried() const;
	void set_buried(bool is_buried);

	bool has_bury_ability() const;
	void set_bury_ability(bool bury_ability);

private:
	bool _bury_ability;
	bool _is_buried;




public:
	float get_mouth_size();
	//void set_mouth_size(float mouth_size);
private:
	float _mouth_size;



public:
	/*Verifica se o player está de baixo de um vegetal do seu setor ou dos setores adjacentes*/
	bool is_under_vegetal();

	/*Coloca como false o flag que verifica se o calculo de under_vegetal foi realizado em uma frama
	 * Utilizado pelo o event da passagem do frame*/
	void set_false_verify_under_vegetal();


private:
	bool flag_verify_under_vegetal;//Flag verifica se o método in_under_vegetal foi chamado em um frame
	bool player_is_under_vegetal;

public:
	void add_energy(float energy);
	void add_food_hydration(float food_hydration);
	void add_food_energy(float food_energy);

	float get_energy() const;
	float get_min_energy() const;
	float get_hydration() const;
	float get_min_hydration() const;
	float get_temperature() const;
	float get_ideal_temperature() const;
	float get_max_temperature() const;
	float get_min_temperature() const;
	float get_lethargy() const;

	/* Obtém o tamanho mínimo e máximo de lagartos permitidos. */
	static float get_min_lizards_size();
	static float get_max_lizards_size();
	float get_size() const;
	float get_max_size() const;
	float get_relative_size() const;
	float calculate_lizards_relative_size(float lizard_size) const;

private:

};

#endif
