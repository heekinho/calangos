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

// Forward Declaration
class MicroClima;
class Vetores;


//typedef enum {tropidurus , eurolophosaurus, cnemidophorus} LizardEspecie;
//typedef enum {female, male, young} LizardGender;

/*! A classe Player � respons�vel por criar o Jogador que ser� controlado pelo
 * usu�rio.<br> Representada como objeto de jogo. Suas tarefas de controle, ficam
 * sob responsabilidade da classe playerControl */
class Player : public AnimatedObjetoJogo {

public:
	// Modelo singleton, ao iniciar utilizar os parametros
	static PT(Player) get_instance();

	~Player();

	void eat(ObjetoJogo *food);

	static void load_player();


	/* PlayerHealth - (playerHealth.cxx)
	 * Relacionado com as vari�veis de sa�de do lagarto.
	 * ------------------------------------------------------------------------- */

	/* Evento peri�dico de gasto de energia (� preciso criar) */
	static void event_gasto_energia(const Event *, void *data);

	/* Evento de ingest�o de alimento (� preciso criar).
	 * � necess�rio saber o qu�o energ�tico e hidratante � o alimento ingerido,
	 * para que se possa setar coerentemente as vari�veis relacionadas. */
	static void event_ingestao_alimento(const Event *, void *data);
	static void event_pday(const Event *, void *data);
	static void event_pmonth(const Event *, void *data);

	double get_energia();
	double get_energia_minlimite();
	double get_energia_alimento();

	double get_gasto_temp();
	double get_gasto_basal();
	double get_gasto_total();

	double get_temp_interna();
	double get_temp_interna_ideal();
	double get_temp_interna_maxlimite();
	double get_temp_interna_minlimite();
	double get_letargia();

	double get_hidratacao();
	double get_hidratacao_alimento();
	double get_hidratacao_minlimite();

	double get_velocity();

	double get_environment_temp();

	int get_num_atualizacoes_dia();
	int get_num_dias();
	int get_idade();
	float get_soma_energia_dia();
	float get_tamanho() {return tamanho_lagarto_base;};
	float get_taxa_crescimento();
	float get_soma_media_energia_diaria();
	float get_media_energia_mes();
	
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


	static void unload_player();

	/* TODO: Testando a inclina��o do lagarto */
	virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector);

	void set_lagarto_parado();
	void set_lagarto_andando();
	void set_lagarto_correndo();

	bool is_in_toca();
	void set_in_toca(bool is_in_toca);
	int get_toca_index();
	void set_toca_index(int toca_index);

	//recebe o tamanho do lagarto que mordeu, e calcula um gasto de energia e hidrataçao proporcionalmente
	void mordida_recebida(int tamanho_lagarto);

	/* BEGIN OF WORKAROUND */
	/* RECEBA ESSE GANCHO NA BOCA DO ESTÔMAGO */
	enum lizardEpecie {tropidurus , eurolophosaurus, cnemidophorus};
	static string get_specie_name(Player::lizardEpecie specie);

	enum lizardGender {female, male, young};
	static string get_gender_name(Player::lizardGender gender);

	//	static map<Player::lizardGender, string> lizard_genders;
	//	static map<Player::lizardEpecie, string> lizard_names;
	/* END OF WORKAROUND */

	static Player::lizardEpecie lizard_specie;
	static Player::lizardGender lizard_gender;

	void add_ovos();

private:
	/* Controle Singleton */
	Player();

	static bool instanceFlag;
	static PT(Player) single;

	/* Variaveis relacionadas a acoes do lagarto */
	double velocity;


	/* Vari�veis relacionadas a sa�de do lagarto:
	 * Sa�de e hidrata��o variam de 0 a 100.
	 * Segundo Pedro o lagarto sobrevive no m�ximo 1 dia sem se alimentar e
	 * submetido a altas temperaturas */
	double energia;
	double hidratacao;

	/* Valor nutricional proveniente da ingest�o de alimentos
	 * Necessario zera-la sempre que for usada */
	//TODO: Tirar essa vari�vel. Atualizar direto em energia.
	double energia_alimento;

	/* Valor nutricional acumulado proveniente da ingestao de alimentos
	 * Zerada quando adicionado ao vetor de amostragem para graficos */
	double energia_alimento_acumulada;

	/* Valor de hidrata��o presente no alimento ingerido
	 * Necess�rio zer�-la sempre que for usada */
	//TODO: Tirar essa vari�vel. Atualizar direto em hidrata��o.
	double hidratacao_alimento;

	/* UMIDADE */
	/* Armazena em quanto o valor da hidrata��o vai cair a cada atualiza��o de vari�veis
	 * com base no valor da umidade relativa da microregi�o em que o lagarto se encontra */
	double fator_umidade;
	/* Inclina��o da reta do c�lculo fator umidade, que depender� da constante: NUM_HORAS_HIDRATACAO */
	double a_fator_umidade;
	/* Offset */
	double b_fator_umidade;
	/* Valor de deca�mento caso as atualiza��es fossem de hora em hora */
	double y_fator_umidade;

	/* GASTO DE ENERGIA */
	/* Gasto total de energia */
	double gasto_total;
	/* Gasto de energia inerente ao lagarto */
	double gasto_basal;
	/* Gasto de energia por consequ�ncia da temperatura */
	double gasto_temp;

	/* TEMPERATURA INTERNA */
	/* Temperatura interna do lagarto */
	double temp_interna;
	/* Valor depender� da esp�cie de lagarto escolhido pelo jogador */
	double temp_interna_ideal;

	/* Letargia - Perda tempor�ria da sensibilidade e movimento por causa fisiol�gica */
	double letargia;

	/* Quantidade de atualiza��es que as vari�veis sofrem em uma hora virtual */
	double atualizacoes_phora;

	/* Limites extremos das vari�veis que podem causar a morte do personagem */
	double temp_interna_maxlimite;
	double temp_interna_minlimite;
	double hidratacao_minlimite;
	double energia_minlimite;

	void load_health();
	void load_health(int especie);

	/* C�lculos de Vari�veis */
	void calc_energia();
	void calc_gasto_temp();
	void calc_gasto_basal();
	void calc_gasto_total();
	void calc_temp_interna();
	void calc_letargia();
	void calc_hidratacao();
	void calc_fator_umidade();
	void calc_y_fator_umidade();

	void atualiza_vector();
	void calc_atualizacoes_phora();

	void calc_tamanho_lagarto_real(float media_energia_mensal);

	Vetores* vetores;

	//vari�vel que ser� multiplicada ao gasto basal, e controlar� o gasto adicional por movimenta��o
	float gasto_movimento;

	bool in_toca;
	int toca_index;


	/*ORDEM: 1 - Tempera interna ideal, 2 - Quantidade de horas sem se alimentar,
	*3 - Quantidade de horas com baixa hidratação, 4 - Umidade que afeta a hidratação,
	*5 - Umidade parametro, 6 - Temperatura interna de limite máximo, 7 - Temperatura interna de limite mínimo,
	*8 - Limite mínimo de hidratação, 9 - Limite mínimo de energia, 10 - Tolerancia de variação da temperatura interna,
	*11 - Gasto com baixa temperatura, por grau abaixo da ideal, a cada atualização,
	*12 - Gasto com alta temperatura, por grau abaixo da ideal, a cada atualização,
	*13 - Velocidade de equilíbrio térmico com o meio*/
	static float arrayTropidurus[13];
	static float arrayEurolophosaurus[13];
	static float arrayCnemidophorus[13];

	void init_tropidurus_lizard();
	void init_eurolophosaurus_lizard();
	void init_cnemidophorus_lizard();

	float variacao_temp_interna;
	float gasto_baixa_temp;
	float gasto_alta_temp;
	float equi_term;
	float equi_term_atual;
	float num_horas_alimento;

	//guarda o número de atualizações para se fazer a média diária de energia
	int num_atualizacoes_dia;
	//soma a quantidade de energia a cada atualização
	float soma_energia_dia;
	//guarda número de dias no mês, para fazer média de energia
	int num_dias;
	//armazena o tamanho do lagarto que será passado como parâmetro para o método set_scale
	float tamanho_lagarto_real;
	//valor que irá armazenar o tamanho do lagarto que servirá como base para cálculo de outros parâmetros. Poderá variar de 0 à 100
	float tamanho_lagarto_base;
	//inclinação da curva
	float a_tamanho_lagarto_base;
	//valor que irá armazenar as taxas de crescimento(como um temp)
	float taxa_crescimento;
	//vai armazenando a média de energia do lagarto, senddo calculada a média mensal e zerado, assim que passar o mÊs
	float soma_media_energia_diaria;
	//armazena a média da energia de determnado mês
	float media_energia_mes;
	//armazena a idade do lagarto, em meses
	int idade;
	//numero de ovos
	int num_ovos;
};

#endif
