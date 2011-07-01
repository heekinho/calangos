#ifndef PLAYER_H
#define PLAYER_H

#include "pandaFramework.h"
#include "windowFramework.h"
#include "simdunas.h"
#include "objetoJogo.h"
#include "playerControl.h"
#include "setor.h"
#include "microClima.h"
#include "vetores.h"
#include "femaleLizard.h"
#include "edible.h"

#include "playerProperties.h"

// Forward Declaration
class MicroClima;
class Vetores;


//typedef enum {tropidurus , eurolophosaurus, cnemidophorus} LizardEspecie;
//typedef enum {female, male, young} LizardGender;

/*! A classe Player é responsável por criar o Jogador que será controlado pelo
 * usuário.<br> Representada como objeto de jogo. Suas tarefas de controle, ficam
 * sob responsabilidade da classe playerControl */
class Player : public AnimatedObjetoJogo {

public:
	// Modelo singleton, ao iniciar utilizar os parametros
	static PT(Player) get_instance();

	static PlayerProperties properties;

	~Player();

	void eat(Edible* food, int type = 2);

	static void load_player();
	void load_custom_health();

	//static const float BITE_THR = 3.0;
	float get_eat_radius_thr();
	float get_toca_thr(){ return 0.3; };
	float get_female_thr(){ return 5.0; };

	bool reaches(PT(ObjetoJogo) object);

	bool was_captured();
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

	double get_energia();
	double get_energia_minlimite();
	double get_energia_alimento();

	double get_gasto_temp();
	double get_gasto_basal();
	double get_gasto_total();

	double get_environment_temp();

	double get_temp_interna();
	double get_temp_interna_ideal();
	double get_temp_interna_maxlimite();
	double get_temp_interna_minlimite();
	double get_letargia();

	double get_hidratacao();
	double get_hidratacao_alimento();
	double get_hidratacao_minlimite();


	float get_speed_walking();
	float get_speed_running();
	/* Should be a vector */
	double get_velocity();

	float velocity_factor;


	int get_num_atualizacoes_dia();
	int get_num_dias();
	int get_idade();

	float get_soma_energia_dia();
	float get_media_energia_mes();
	float get_soma_media_energia_diaria();

/* FEATURE: Tamanho do lagarto */
public:
	/* Obtém o tamanho mínimo e máximo de lagartos permitidos. */
	static float get_min_lizards_size();
	static float get_max_lizards_size();
	/*static*/ float get_absolute_size_factor();

	float get_max_size();
	float get_min_size();
	/*static*/ float get_relative_size_factor();

	/* Obtém a porcentagem do tamanho do lagarto */
	float get_tamanho_base();
	/* Recebe o tamanho real e retorna em uma escala de 0 a 100 */
	float calc_tamanho_base(float tamanho_real);

	float get_tamanho_real();
	float get_taxa_crescimento();

	void calc_visual_size_factor();
	float get_visual_size();

private:
	float visual_size_factor;
	float max_size;

	/* Armazena o tamanho do lagarto que será passado como parâmetro para o
	 * método set_scale */
	float tamanho_lagarto_real;
	/* Armazena o tamanho do lagarto que servirá como base para cálculo de
	 * outros parâmetros. Poderá variar de 0 à 100 */
	float tamanho_lagarto_base;
	/* Valor que irá armazenar as taxas de crescimento (como um temp) */
	float taxa_crescimento;


public:

	bool get_estado_reprodutivo();
	int get_num_ovos();
	/* ------------------------------------------------------------------------- */

	/* Setters */
	void set_energia_alimento(double nova_energia_alimento);
	void set_hidratacao_alimento(double nova_hidratacao_alimento);
	void set_hidratacao(double nova_hidratacao);

	void set_temp_interna(double nova_temp_interna);
	void set_temp_interna_ideal(double nova_temp_interna_ideal);
	void set_temp_interna_maxlimite(double nova_temp_interna_maxlimite);
	void set_temp_interna_minlimite(double nova_temp_interna_minlimite);
	void set_hidratacao_minlimite(double nova_hidratacao_minlimite);
	void set_energia_minlimite(double nova_energia_minlimite);
	void set_energia(double nova_energia);

	void set_velocity(double velocity);

	/* "Adders" */
	void add_energia_alimento(double ganho_energia_alimento);
	void add_hidratacao_alimento(double ganho_hidratacao_alimento);

	void display(PT(Player) player);
	/* ------------------------------------------------------------------------- */

	//Descarrega qualquer referência de objeto da classe player da memória, para que possa ser recriado
	static void unload_player();

	virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector);

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

	/* Enum que corresponde as espécies dos lagartos com os quais o jogador pode jogar */
	enum lizardEpecie {
		tropidurus,
		eurolophosaurus,
		cnemidophorus,
		custom
	};

	/*Enum que corresponde as grandezas armazenadas no vetor de variáveis de saúde dos lagartos*/
	enum lizard_variables{
		TEMP_INTER_IDEAL,//0
		QNT_H_SEM_ALIMENTO,//1
		QNT_H_BAIXA_HIDRAT,//2
		UMID_AFETA_HIDRAT,//3
		UMID_PARAM,//4
		TEMP_INT_MAX,//5
		TEMP_INT_MIN,//6
		HIDT_MIN,//7
		ENER_MIN,//8
		TOLER_TEMP_INTER,//9
		GASTO_BAIXA_TEMP,//10
		GASTO_ALTA_TEMP,//11
		VEL_EQUI_TERM//12
	};

	static string get_specie_name(Player::lizardEpecie specie);
	enum lizardGender {female, male, young};
	static string get_gender_name(Player::lizardGender gender);

	/* Variáveis que armazenarão espécie e sexo/idade da lagarto */
	static Player::lizardEpecie lizard_specie;
	static Player::lizardGender lizard_gender;

	/* Incrementa em 1, a quantidade de ovos desse lagarto.
	 * Esse valor está associado ao sucesso do lagarto nas reproduções (quanto mais melhor).*/
	void add_ovos();

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


	/* Variaveis relacionadas a saude do lagarto:
	 * Saude e hidratacao variam de 0 a 100.
	 * Segundo Pedro o lagarto sobrevive no maximo 1(acho que são 7, confirmar) dia sem se alimentar e
	 * submetido a altas temperaturas */
	double energia;
	double hidratacao;

	/* Valor nutricional proveniente da ingestao de alimentos
	 * Necessario zera-la sempre que for usada */
	//TODO: Tirar essa variável. Atualizar direto em energia.
	double energia_alimento;

	/* Valor nutricional acumulado proveniente da ingestao de alimentos
	 * Zerada quando adicionado ao vetor de amostragem para graficos */
	double energia_alimento_acumulada;

	/* Valor de hidratacao presente no alimento ingerido
	 * Necessário zera-la sempre que for usada */
	//TODO: Tirar essa variavel. Atualizar direto em hidratacao.
	double hidratacao_alimento;

	/* UMIDADE */
	/* Armazena em quanto o valor da hidratacao vai cair a cada atualizacao de variaveis
	 * com base no valor da umidade relativa da microregiao em que o lagarto se encontra */
	double fator_umidade;
	/* Inclinacao da reta do calculo fator umidade, que dependera da constante: NUM_HORAS_HIDRATACAO */
	double a_fator_umidade;
	/* Offset  da reta*/
	double b_fator_umidade;
	/* Valor de decaimento caso as atualizações fossem de hora em hora */
	double y_fator_umidade;

	/* Gasto total de energia */
	double gasto_total;
	/* Gasto de energia inerente ao lagarto */
	double gasto_basal;
	/* Foator de aumento ou diminuição do gasto de energia por consequencia da temperatura */
	double gasto_temp;

	/* Temperatura interna do lagarto */
	double temp_interna;
	/* Temperatura ideal do lagarto. Valor dependerá da espécie de lagarto escolhido pelo jogador */
	double temp_interna_ideal;

	/* Limites extremos das variáveis que podem causar a morte do personagem */
	double temp_interna_maxlimite;
	double temp_interna_minlimite;
	double hidratacao_minlimite;
	double energia_minlimite;

	/* Faixa de variação em torno da temperatura ideal do lagarto,
	 * dentro da qual será considerado como se ele estivesse na sua temperatura ideal*/
	float variacao_temp_interna;
	/* Fator de atenuação no gasto de energia quando a temperatura está baixa */
	float gasto_baixa_temp;
	/* Fator de acréscimo no gasto de energia quando a temperatura está alta */
	float gasto_alta_temp;
	/* Fator que regula o tempo que o lagarto gastará para chegar ao equilíbrio
	 * térmico com o meio no qual está, a depender da diferença entre as
	 * temperaturas interna e externa.*/
	float equi_term;
	/* Valor da diferença entre as temperaturas interna e externa (diferente a cada atualização) */
	float equi_term_atual;


	/* Letargia - Perda temporária da sensibilidade e movimento por causa fisiológica */
	double letargia;

	/* Quantidade de atualizações que as variáveis sofrem em uma hora virtual */
	double atualizacoes_phora;


	/* Variável que será multiplicada ao gasto basal, e controlará o gasto
	 * adicional por movimentação */
	float gasto_movimento;

	/* Informa se o lagarto está na toca ou não */
	bool in_toca;

	/* Quantas horas sem se alimentar o lagarto consegue se sobreviver (cosiderando outros fatores ideais). */
	float num_horas_alimento;

	/* Guarda o número de atualizações para se fazer a média diária de energia */
	int num_atualizacoes_dia;
	/* Soma a quantidade de energia a cada atualização */
	float soma_energia_dia;
	/* Guarda número de dias no mês, para fazer média de energia */
	int num_dias;
	/* Vai armazenando a média de energia do lagarto, senddo calculada a média
	 * mensal e zerado, assim que passar o mês */
	float soma_media_energia_diaria;
	/* Armazena a média da energia de determinado mês */
	float media_energia_mes;

	/* Armazena a idade do lagarto, em meses */
	int idade;
	/* Número de ovos */
	int num_ovos;

	/* Carrega os parâmetros iniciais de saúde do lagarto. O lagarto default
	 * para carregar a saúde é o Eurolophosaurus */
	void load_health();

	/* Carrega os parâmetros iniciais de saúde do lagarto, cuja espécie foi
	 * passada como parâmetro. */
	void load_health(int especie);

	/* Cálculos de Variáveis */
	void calc_energia();
	void calc_gasto_temp();
	void calc_gasto_basal();
	void calc_gasto_total();
	void calc_temp_interna();
	void calc_letargia();
	void calc_hidratacao();
	void calc_fator_umidade();
	void calc_y_fator_umidade();

	/* Armazena os valores das variáveis 'finais' (energia, hidratação, temperatura interna) no vetor
	 * da classe vector. Esses valores servirão para a geração dos gráficos no tempo. */
	void atualiza_vector();

	/* Calcula o número de atualizações por hora (virtual), para que a quantidade
	 * de atualizações dentro de um mesmo espaço de tempo (real) seja sempre a mesma */
	void calc_atualizacoes_phora();

	/* Calcula o novo tamanho do lagarto. Esse método é chamado a cada passagem
	 * do mês, e recebe a média de energia diária daquele mês. A partir desse
	 * valor calcula o quanto o lagarto crescerá.*/
	void calc_tamanho_lagarto_real(float media_energia_mensal);

	/* Guarda referencia para os vetores que armazenarão o histórico das variáveis de saúde do lagarto*/
	Vetores* vetores;

	/*ORDEM: 1 - Tempera interna ideal, 2 - Quantidade de horas sem se alimentar,
	*3 - Quantidade de horas com baixa hidratação, 4 - Umidade que afeta a hidratação,
	*5 - Umidade parametro, 6 - Temperatura interna de limite máximo, 7 - Temperatura interna de limite mínimo,
	*8 - Limite mínimo de hidratação, 9 - Limite mínimo de energia, 10 - Tolerancia de variação da temperatura interna,
	*11 - Gasto com baixa temperatura, por grau abaixo da ideal, a cada atualização,
	*12 - Gasto com alta temperatura, por grau abaixo da ideal, a cada atualização,
	*13 - Velocidade de equilíbrio térmico com o meio */

	/* Variáveis do Tropidurus */
	static const float temperatura_interna_ideal_trop;
	static const float qnt_h_sem_alimento_trop;
	static const float qnt_h_baixa_hidrat_trop;
	static const float umidade_afeta_hidrat_trop;
	static const float umidade_param_trop;
	static const float temp_interna_max_trop;
	static const float temp_interna_min_trop;
	static const float hidrat_min_trop;
	static const float energia_min_trop;
	static const float faixa_tolerancia_tem_interna_trop;
	static const float gasto_baixa_temp_trop;
	static const float gasto_alta_temp_trop;
	static const float vel_equi_termico_trop;

	/* Variáveis do Eurolophosaurus */
	static const float temperatura_interna_ideal_euro;
	static const float qnt_h_sem_alimento_euro;
	static const float qnt_h_baixa_hidrat_euro;
	static const float umidade_afeta_hidrat_euro;
	static const float umidade_param_euro;
	static const float temp_interna_max_euro;
	static const float temp_interna_min_euro;
	static const float hidrat_min_euro;
	static const float energia_min_euro;
	static const float faixa_tolerancia_tem_interna_euro;
	static const float gasto_baixa_temp_euro;
	static const float gasto_alta_temp_euro;
	static const float vel_equi_termico_euro;

	/* Variáveis do Cnemidophorus */
	static const float temperatura_interna_ideal_cnem;
	static const float qnt_h_sem_alimento_cnem;
	static const float qnt_h_baixa_hidrat_cnem;
	static const float umidade_afeta_hidrat_cnem;
	static const float umidade_param_cnem;
	static const float temp_interna_max_cnem;
	static const float temp_interna_min_cnem;
	static const float hidrat_min_cnem;
	static const float energia_min_cnem;
	static const float faixa_tolerancia_tem_interna_cnem;
	static const float gasto_baixa_temp_cnem;
	static const float gasto_alta_temp_cnem;
	static const float vel_equi_termico_cnem;

	/* Vetores que guardarão os valores das variáveis apresentadas acima para cada espécie */
	static float arrayTropidurus[13];
	static float arrayEurolophosaurus[13];
	static float arrayCnemidophorus[13];

	/* Carrega os valores inicias das variáveis para cada espécie */
	void init_tropidurus_lizard();
	void init_eurolophosaurus_lizard();
	void init_cnemidophorus_lizard();

public:
	/* Procura fêmeas em um raio próximo */
	bool has_female_around();
	void update_female_around();
	PT(FemaleLizard) get_courted_female();
private:
	//bool female_around;
	PT(FemaleLizard) _courted_female;


public:
	float get_indice_camuflagem() const;

	bool has_bury_ability() const;
	void set_bury_ability(bool bury_ability);

private:
	bool bury_ability;
};

#endif
