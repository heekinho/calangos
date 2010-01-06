#include "player.h"
#include "menu.h"

/* Bloco de constantes
 * ------------------------------------------------------------------------- */
//idade, em meses, na qual o lagarto poderá se reproduzir
#define IDADE_REPRODUTIVA 12
//idade, em meses, em que o lagarto deve morrer
#define IDADE_MORTE 36

#define ENERGIA_INIT 50.0
#define HIDRATACAO_INIT 50.0

#define TAMANHO_MAXIMO 0.0025
#define TAMANHO_INICIAL 0.0004
#define MESES_TAMANHO_MAXIMO 36
/* Debugar */
#define DEBUG false
/* ------------------------------------------------------------------------- */
/*! Carrega os atributos iniciais relacionados à saúde do lagarto*/

float Player::arrayTropidurus[13] = {38, 168, 48, 40, 10, 50, 15, 45, 5, 2, 0.05, 0.05, 0.1};
float Player::arrayEurolophosaurus[13] = {36, 190, 48, 40, 10, 45, 13, 40, 3, 1.5, 0.06, 0.08, 0.1};
float Player::arrayCnemidophorus[13] = {40, 168, 48, 40, 10, 50, 15, 45, 5, 2, 0.06, 0.06, 0.1};

void Player::load_health(int especie){

	calc_atualizacoes_phora();
	//int especie = Menu::get_instance()->get_especie();
	lizardEpecie lizard = lizardEpecie(especie);
	//lizard = Menu::get_instance()->get_especie();//lizardEpecie(especie);

	if(lizard == tropidurus){
		init_tropidurus_lizard();
	}else if(lizard == eurolophosaurus){
		init_eurolophosaurus_lizard();		
	}else{
		init_cnemidophorus_lizard();
	}
	
	equi_term_atual = equi_term;
	//valores que independem da espécie do lagarto	
	energia = ENERGIA_INIT;
	hidratacao = HIDRATACAO_INIT;
	energia_alimento = 0;
	energia_alimento_acumulada=0;
	y_fator_umidade = 0;
	fator_umidade = 0;
	letargia = 0;
	//considera o lagarto parado no início do jogo
	gasto_movimento = 1;

	num_atualizacoes_dia = 0;
	soma_energia_dia = 0;
	soma_media_energia_diaria = 0;
	num_dias = 0;
	media_energia_mes = 0;
							//LEMBRA DE COLOCAR TAMANHO_INICIL DE VOLTA
	tamanho_lagarto_real = TAMANHO_INICIAL-0.00001;//colocar um valor inicial default razoável (um valor para cada espécie?)
	a_tamanho_lagarto_base = (100/(TAMANHO_MAXIMO - TAMANHO_INICIAL));
	tamanho_lagarto_base = a_tamanho_lagarto_base*(tamanho_lagarto_real-TAMANHO_INICIAL);

	idade = 0;
	num_ovos = 0;
	//simples conferencia
	if(DEBUG){
		cout << endl << "A temperatura interna do lagarto eh: " << this->temp_interna << endl;
	}
}

void Player::load_health(){

	load_health(eurolophosaurus);
}

/*Inicializando lagartos*/

void Player::init_eurolophosaurus_lizard(){

	num_horas_alimento = Player::arrayEurolophosaurus[1];
	temp_interna_ideal = Player::arrayEurolophosaurus[0];
	gasto_basal = ENERGIA_INIT / (num_horas_alimento * atualizacoes_phora);
	a_fator_umidade = -(HIDRATACAO_INIT / Player::arrayEurolophosaurus[2]) / (Player::arrayEurolophosaurus[3] - Player::arrayEurolophosaurus[4]);
	b_fator_umidade = -(a_fator_umidade * (Player::arrayEurolophosaurus[3]));
	temp_interna =  Player::arrayEurolophosaurus[0];
	temp_interna_maxlimite =  Player::arrayEurolophosaurus[5];
	temp_interna_minlimite = Player::arrayEurolophosaurus[6];
	hidratacao_minlimite = Player::arrayEurolophosaurus[7];
	energia_minlimite = Player::arrayEurolophosaurus[8];
	variacao_temp_interna = Player::arrayEurolophosaurus[9];
	gasto_baixa_temp = Player::arrayEurolophosaurus[10];
	gasto_alta_temp = Player::arrayEurolophosaurus[11];
	equi_term = Player::arrayEurolophosaurus[12];
}

void Player::init_tropidurus_lizard(){

	num_horas_alimento = Player::arrayTropidurus[1];
	temp_interna_ideal = Player::arrayTropidurus[0];
	gasto_basal = ENERGIA_INIT / (num_horas_alimento * atualizacoes_phora);
	a_fator_umidade = -(HIDRATACAO_INIT / Player::arrayTropidurus[2]) / (Player::arrayTropidurus[3] - Player::arrayTropidurus[4]);
	b_fator_umidade = -(a_fator_umidade * (Player::arrayTropidurus[3]));
	temp_interna =  Player::arrayTropidurus[0];
	temp_interna_maxlimite =  Player::arrayTropidurus[5];
	temp_interna_minlimite = Player::arrayTropidurus[6];
	hidratacao_minlimite = Player::arrayTropidurus[7];
	energia_minlimite = Player::arrayTropidurus[8];
	variacao_temp_interna = Player::arrayTropidurus[9];
	gasto_baixa_temp = Player::arrayTropidurus[10];
	gasto_alta_temp = Player::arrayTropidurus[11];
	equi_term = Player::arrayTropidurus[12];
}

void Player::init_cnemidophorus_lizard(){

	num_horas_alimento = Player::arrayCnemidophorus[1];
	temp_interna_ideal = Player::arrayCnemidophorus[0];
	gasto_basal = ENERGIA_INIT / (num_horas_alimento * atualizacoes_phora);
	a_fator_umidade = -(HIDRATACAO_INIT / Player::arrayCnemidophorus[2]) / (Player::arrayCnemidophorus[3] - Player::arrayCnemidophorus[4]);
	b_fator_umidade = -(a_fator_umidade * (Player::arrayCnemidophorus[3]));
	temp_interna =  Player::arrayCnemidophorus[0];
	temp_interna_maxlimite =  Player::arrayCnemidophorus[5];
	temp_interna_minlimite = Player::arrayCnemidophorus[6];
	hidratacao_minlimite = Player::arrayCnemidophorus[7];
	energia_minlimite = Player::arrayCnemidophorus[8];
	variacao_temp_interna = Player::arrayCnemidophorus[9];
	gasto_baixa_temp = Player::arrayCnemidophorus[10];
	gasto_alta_temp = Player::arrayCnemidophorus[11];
	equi_term = Player::arrayCnemidophorus[12];
}


/* EVENTOS
 * ------------------------------------------------------------------------- */
//TODO: Acho que esse evento não será mais necessário
void Player::event_ingestao_alimento(const Event*, void *data){
}

/* Evento chamado a cada minuto virtual para atualização dos valores */
void Player::event_gasto_energia(const Event*, void *data){

	PT(Player) player = (Player*) data;
		
	/* Chama as funções para atualizar a saúde do lagarto */
	//WARNING: Ordem é importante
	player->calc_temp_interna();
	player->calc_letargia();
	player->calc_gasto_temp();
	player->calc_gasto_basal();
	player->calc_gasto_total();
	player->calc_y_fator_umidade();
	player->calc_fator_umidade();
	player->calc_hidratacao();
	player->calc_energia();
	player->display(player);
	player->atualiza_vector();

	/* Verificação de morte do personagem por energia*/
	if(player->energia < player->energia_minlimite){
		//Informa morte do personagem por desnutrição.
		Session::get_instance()->player_death(1);
	}else{
		/* Verificação de morte do personagem por temperatura interna */
		if(player->temp_interna >= player->temp_interna_maxlimite){
			Session::get_instance()->player_death(3);
		}else {
			if(player->temp_interna < player->temp_interna_minlimite){
				Session::get_instance()->player_death(4);
			}else{
				/* Verificação de morte do lagarto por desidratação */
				if(player->hidratacao < player->hidratacao_minlimite){
					Session::get_instance()->player_death(2);
				}
			}
		}
	}
	player->num_atualizacoes_dia++;
	player->soma_energia_dia = player->soma_energia_dia + player->energia;
}

void Player::event_pday(const Event*, void *data){

	PT(Player) player = (Player*) data;

	player->num_dias++;

	float media_energia_hoje = player->soma_energia_dia/player->num_atualizacoes_dia;
	player->soma_media_energia_diaria = player->soma_media_energia_diaria + media_energia_hoje;

	player->num_atualizacoes_dia = 0;
	player->soma_energia_dia = 0;
}

void Player::event_pmonth(const Event*, void *data){
	PT(Player) player = (Player*) data;

	player->media_energia_mes = player->soma_media_energia_diaria/player->num_dias;
	
	player->num_dias = 0;
	player->soma_media_energia_diaria = 0;

	player->calc_tamanho_lagarto_real(player->media_energia_mes);
	player->set_scale(player->tamanho_lagarto_real);
	//cout << "Novo Tamanho: " << player->tamanho_lagarto_real << endl;

	player->idade++;
	if(player->idade>=IDADE_REPRODUTIVA){
		GuiManager::get_instance()->liga_led_estado_reprodutivo();
	}
	if(player->idade>=IDADE_MORTE){
		Session::get_instance()->player_death(5);
	}
}

/* ------------------------------------------------------------------------- */
/* CÁLCULOS
 * ------------------------------------------------------------------------- */

/*! Calcula o valor de energia do lagarto
 * A energia do lagarto é dada por:
 * Energia Atual - Gasto Total + Energia Adquirida por ingestão de alimentos */
void Player::calc_energia(){

	double energia_temp = 0;
	/* Calcula a energia e faz o corte se necessário */
	energia_temp = this->energia - this->gasto_total + this->energia_alimento;

	if(energia_temp < 100) this->energia = energia_temp;
	else this->energia = 100;

	/* Energia do alimento já consumida */
	this->energia_alimento = 0;

}

/*! Calcula o gasto de energia por temperatura do lagarto. */
void Player::calc_gasto_temp(){

	/* Se a temperatura interna estiver abaixo da faixa de tolerância */
	if(temp_interna < (this->temp_interna_ideal  - this->variacao_temp_interna)) {
		this->gasto_temp = 1/(1+((this->temp_interna_ideal  - this->variacao_temp_interna) - (this->temp_interna))*this->gasto_baixa_temp);
	}
	else {
		/* Se a temperatura interna estiver acima da faixa de tolerância */
		if(temp_interna > (this->temp_interna_ideal  + this->variacao_temp_interna)){
			this->gasto_temp = 1+(this->temp_interna - (this->temp_interna_ideal  + this->variacao_temp_interna))*this->gasto_alta_temp;
		}
		else {
			/* Temperatura na faixa de tolerância */
			this->gasto_temp = 1;
		}
	}
}

/*! Calcula o gasto de energia do lagarto.
 * O gasto de energia do lagarto é dado por:
 * Gasto Total = Gasto Basal * Gasto por Temperatura */
void Player::calc_gasto_total(){
	this->gasto_total = this->gasto_basal*this->gasto_temp*this->gasto_movimento;
}

/*! Calcula o gasto de energia inerente ao lagarto */
void Player::calc_gasto_basal(){
	this->gasto_basal = (ENERGIA_INIT/(num_horas_alimento*atualizacoes_phora))*(1+(5*this->tamanho_lagarto_base/100));
}

/*! Calcula a temperatura interna do lagarto */
void Player::calc_temp_interna(){

	if(in_toca){
		this->temp_interna = this->temp_interna + this->equi_term_atual*(MicroClima::get_instance()->get_temp_toca_sector() - this->temp_interna);
	}else{
		this->temp_interna = this->temp_interna + this->equi_term_atual*(MicroClima::get_instance()->get_temp_solo_sector() - this->temp_interna);
	}
}


/*! Calcula a letargia do lagarto
 * 0 - Nenhuma letargia (temperatura interna maior que a ideal)
 * 1 - Total letargia - culmina na morte do lagarto */
void Player::calc_letargia(){
	double menor_temp_ideal = this->temp_interna_ideal - this->variacao_temp_interna;

	//TODO: Chamar morte do lagarto quando a letargia for = 1?
	if(this->temp_interna > menor_temp_ideal) letargia = 0;
	else if(this->temp_interna < temp_interna_minlimite) letargia = 1;
	else letargia = 1 - ( (this->temp_interna - temp_interna_minlimite) / (menor_temp_ideal - temp_interna_minlimite) );
}



/*! Calcula a hidratação do lagarto
 * A hidratação do lagarto é dada por:
 * Hidratação = Hidratação - Fator Umidade + Hidratação adquirida */
void Player::calc_hidratacao(){

	double hidratacao_temp = this->hidratacao - this->fator_umidade + this->hidratacao_alimento;
	if(hidratacao_temp < 100) this->hidratacao = hidratacao_temp;
	else this->hidratacao = 100;

	/* Hidratação já consumida */
	this->hidratacao_alimento = 0;

}

/*! Calcula o valor de decaímento caso as atualizações fossem de hora em hora */
void Player::calc_y_fator_umidade(){

	double umidade_temp = MicroClima::get_instance()->get_umidade_relativa_sector();
	if(umidade_temp < 40) this->y_fator_umidade = a_fator_umidade*umidade_temp + b_fator_umidade;
	else this->y_fator_umidade = 0;
}

/*! Calcula o fator umidade
 * Armazena em quanto o valor da hidratação vai cair a cada atualização de variáveis
 * com base no valor da umidade relativa da microregião em que o lagarto se encontra */
void Player::calc_fator_umidade(){
	this->fator_umidade = this->y_fator_umidade/this->atualizacoes_phora;
}

void Player::calc_atualizacoes_phora(){
	this->atualizacoes_phora = 60*((3*60.0)/(24*60)); //3 min por dia
	//this->atualizacoes_phora = 60*(TimeControl::get_instance()->get_seconds_min());
}

void Player::calc_tamanho_lagarto_real(float media_energia_mensal){
	
	if(media_energia_mensal < 90){
		this->taxa_crescimento = media_energia_mensal/100;
	}else{
		this->taxa_crescimento = 1;
	}

	float add_tamanho = ((TAMANHO_MAXIMO - TAMANHO_INICIAL)/MESES_TAMANHO_MAXIMO)*this->taxa_crescimento;

	this->tamanho_lagarto_real = this->tamanho_lagarto_real + add_tamanho;
	if(this->tamanho_lagarto_real > TAMANHO_MAXIMO){
		this->tamanho_lagarto_real = TAMANHO_MAXIMO;
	}
	this->tamanho_lagarto_base = this->a_tamanho_lagarto_base*(this->tamanho_lagarto_real-TAMANHO_INICIAL);

	this->equi_term_atual = this->equi_term-(this->equi_term*(this->tamanho_lagarto_base/100)*0.8);
}

/*!Atualiza os valores dos vetores utiliazados para geração dos gráfico*/
void Player::atualiza_vector(){

	Vetores::get_instance()->addElementVectorTemperaturaLagarto(this->temp_interna);
	Vetores::get_instance()->addElementVectorHidratacaoLagarto(this->hidratacao);
	Vetores::get_instance()->addElementVectorEnergia(this->energia);
	Vetores::get_instance()->addElementVectorAlimentacao(this->energia_alimento_acumulada);
	this->energia_alimento_acumulada=0;
	Vetores::get_instance()->addElementVectorGastoEnergeticoTotal(this->gasto_total);

	Vetores::get_instance()->addElementVectorTemperaturaAr(MicroClima::get_instance()->get_temp_ar_sector());
	if(in_toca){
		Vetores::get_instance()->addElementVectorTemperaturaSolo(MicroClima::get_instance()->get_temp_solo_sector());
	} else {
		Vetores::get_instance()->addElementVectorTemperaturaSolo(MicroClima::get_instance()->get_temp_toca_sector());
	}
	Vetores::get_instance()->addElementVectorUmidadeAmbiente(MicroClima::get_instance()->get_umidade_relativa_sector());

	Vetores::get_instance()->addElementVectorTempo(TimeControl::get_instance()->get_hora_generica());

	if(DEBUG){
		cout << endl << "A temperatura interna do lagarto eh: " << this->temp_interna << endl;
		cout << endl << "A temperatura interna do lagarto adicionada ao vetor foi: " << vetores->getLastElementTemperaturaLagarto() << endl;
		cout << endl << "O tamanho do vetor de temperatura interna do lagarto eh: " << vetores->getSizeVectorTemperaturaLagarto() << endl;

		cout << endl << "A temperatura do ambiente eh: " << MicroClima::get_instance()->get_temp_ar_sector() << endl;
		cout << endl << "A temperatura do ambiente adicionada ao vetor foi: " << vetores->getLastElementTemperaturaAr() << endl;
		cout << endl << "O tamanho do vetor de temperatura do ambiente eh: " << vetores->getSizeVectorTemperaturaAr() << endl;
	}
}

/* ------------------------------------------------------------------------- */
/* GETTERS
 * ------------------------------------------------------------------------- */

//TODO: Realmente precisa disso aqui? */

/*! Obtém o valor de energia do alimento */
double Player::get_energia_alimento(){
	return this->energia_alimento;
}

/*! Obtém o valor de hidratação do alimento */
double Player::get_hidratacao_alimento(){
	return this->hidratacao_alimento;
}

/*! Obtém o valor de hidratação do lagarto */
double Player::get_hidratacao(){
	return this->hidratacao;
}

/*! Obtém o valor de gasto de energia inerente ao lagarto */
double Player::get_gasto_basal(){
	return this->gasto_basal;
}

/*! Obtém o valor de gasto de energia relativo à temperatura */
double Player::get_gasto_temp(){
	return this->gasto_temp;
}

/*! Obtém o valor total em gastos */
double Player::get_gasto_total(){
	return this->gasto_total;
}

/*! Obtém o valor de energia do lagarto */
double Player::get_energia(){
	return this->energia;
}

/*! Obtém o valor de temperatura interna do lagarto */
double Player::get_temp_interna(){
	return this->temp_interna;
}

/*! Obtém o valor ideal de temperatura interna do lagarto */
double Player::get_temp_interna_ideal(){
	return this->temp_interna_ideal;
}

/*! Obtém o valor máximo aceitável de temperatura interna do lagarto */
double Player::get_temp_interna_maxlimite(){
	return this->temp_interna_maxlimite;
}

/*! Obtém o valor mínimo aceitável de temperatura interna do lagarto */
double Player::get_temp_interna_minlimite(){
	return this->temp_interna_minlimite;
}

/*! Obtém o valor mínimo aceitável de temperatura interna do lagarto */
double Player::get_letargia(){
	return this->letargia;
}

/*! Obtém o valor mínimo aceitável de hidratação do lagarto */
double Player::get_hidratacao_minlimite(){
	return this->hidratacao_minlimite;
}

/*! Obtém o valor mínimo aceitável de energia do lagarto */
double Player::get_energia_minlimite(){
	return this->energia_minlimite;
}


double Player::get_environment_temp(){
	if(in_toca){
		return MicroClima::get_instance()->get_temp_toca_sector();
	}else{
		return MicroClima::get_instance()->get_temp_solo_sector();
	}
}

int Player::get_num_atualizacoes_dia(){
	return this->num_atualizacoes_dia;
}

int Player::get_num_dias(){
	return this->num_dias;
}

float Player::get_soma_energia_dia(){
	return this->soma_energia_dia;
}


float Player::get_taxa_crescimento(){
	return taxa_crescimento;
}

float Player::get_soma_media_energia_diaria(){
	return this->soma_media_energia_diaria;
}

float Player::get_media_energia_mes(){
	return this->media_energia_mes;
}

int Player::get_idade(){
	return this->idade;
}

bool Player::get_estado_reprodutivo(){
	if(this->idade >= IDADE_REPRODUTIVA){
		return true;
	}else{
		return false;
	}
}

int Player::get_num_ovos(){
	return this->num_ovos;
}
/* ------------------------------------------------------------------------- */
/* SETTERS
 * ------------------------------------------------------------------------- */

/*! Define o valor de energia do alimento */
void Player::set_energia_alimento(double nova_energia_alimento){
	this->energia_alimento = nova_energia_alimento;
}

/*! Define o valor de hidratação do alimento */
void Player::set_hidratacao_alimento(double nova_hidratacao_alimento){
	this->hidratacao_alimento = nova_hidratacao_alimento;
}

/*! Define o valor de hidratação do lagarto */
void Player::set_hidratacao(double nova_hidratacao){
	this->hidratacao = nova_hidratacao;
}

/*! Define o valor de energia do lagarto */
void Player::set_energia(double nova_energia){
	this->energia = nova_energia;
}

/*! Define o valor de temperatura interna do lagarto */
void Player::set_temp_interna(double nova_temp_interna){
	this->temp_interna = nova_temp_interna;
}

/*! Define o valor ideal de temperatura interna do lagarto */
void Player::set_temp_interna_ideal(double nova_temp_interna_ideal){
	this->temp_interna_ideal = nova_temp_interna_ideal;
}

/*! Define o valor máximo aceitável de temperatura interna do lagarto */
void Player::set_temp_interna_maxlimite(double nova_temp_interna_maxlimite){
	this->temp_interna_maxlimite = nova_temp_interna_maxlimite;
}

/*! Define o valor mínimo aceitável de temperatura interna do lagarto */
void Player::set_temp_interna_minlimite(double nova_temp_interna_minlimite){
	this->temp_interna_minlimite = nova_temp_interna_minlimite;
}

/*! Define o valor mínimo aceitável de hidratação do lagarto */
void Player::set_hidratacao_minlimite(double nova_hidratacao_minlimite){
	this->hidratacao_minlimite = nova_hidratacao_minlimite;
}

/*! Define o valor mínimo aceitável de energia do lagarto */
void Player::set_energia_minlimite(double nova_energia_minlimite){
	this->energia_minlimite = nova_energia_minlimite;
}

//vai fazer o gasto do lagarto igual ao basal
void Player::set_lagarto_parado(){
	this->gasto_movimento = 1;
}

//vai fazer o gasto do lagarto 20% maior que o basal
void Player::set_lagarto_andando(){
	this->gasto_movimento = 1.2;
}

//vai fazer o gasto do lagarto 50% maior que o basal
void Player::set_lagarto_correndo(){
	this->gasto_movimento = 1.5;
}

/* ------------------------------------------------------------------------- */
/* "ADDERS"
 * ------------------------------------------------------------------------- */

/*! Adiciona um valor de energia relativo ao alimento em questão */

void Player::add_energia_alimento(double ganho_energia_alimento){
	this->energia_alimento = this->energia_alimento + ganho_energia_alimento;
	this->energia_alimento_acumulada+=ganho_energia_alimento;
}

/*! Adiciona um valor de hidratação relativo ao alimento em questão */
void Player::add_hidratacao_alimento(double ganho_hidratacao_alimento){
	this->hidratacao_alimento = this->hidratacao_alimento + ganho_hidratacao_alimento;
}

void Player::add_ovos(){
	this->num_ovos++;
}
/* ------------------------------------------------------------------------- */
/* "OUTROS"
 * ------------------------------------------------------------------------- */

void Player::mordida_recebida(int tamanho_lagarto){
	//energia e hidratação que o lagarto retira do outro em uma mordida é igual a 5% do seu temanho(0-100)
	float ener_hidr_perdida = tamanho_lagarto/20;
	this->energia = this->energia - ener_hidr_perdida;
	this->hidratacao = this->hidratacao - ener_hidr_perdida;
	GuiManager::get_instance()->piscar_life();
}
