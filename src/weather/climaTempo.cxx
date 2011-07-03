#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#include "climaTempo.h"

/*Inicializando constante que será utilizado em sorteio normal com um valor
* aleatório, situado entre 0 e 1*/
#define RAND_UNIFORME (double)rand()/(double)RAND_MAX

/*Quantidade maxima de chuvas no historico de 4 localidades proximas as
dunas, ocorrido em Morpara, marco de 1960*/
#define QT_CHUVA_MAX 624
#define PI 3.141592653589793

#define DEBUG_CTEMPO 0

TypeHandle ClimaTempo::_type_handle;

/*Inicializando informações do singleton*/
bool ClimaTempo::instanceFlag = false;
PT(ClimaTempo) ClimaTempo::single = NULL;

ClimaTempo::ClimaTempo() {

	/*inicializa o rand, para que a cada chamada do jogo, os valores
	*retornados por essas fun��es sejam diferentes*/
	srand(time(NULL));
	//Sinaliza que o jogo está começando
	initialization = 0;
	/*Chama o método responsável pelo controle dos valores das temperaturas, passando como parâmetros a hora
	*e o mês (virtuais) atuais*/
	this->ambient_control(TimeControl::get_instance()->get_hora(), TimeControl::get_instance()->get_mes());

	/*Se 'inscreve' para escutar o evento de passagem de hora virtual (Ev_pass_hour), gerado pela classe TimeControl.
	*Quando esse evento acontecer, o método event_phour_temp() será chamado.*/
	event_handler->add_hook(TimeControl::get_instance()->EV_pass_hour, event_phour_temp, this);
}

/*Isso e o TypeHandle garantem que todos as referências sejam eliminadas ao finalizar o jogo
e, ao reiniciá-lo, garante-se que um novo objeto da classe será gerado.*/
ClimaTempo::~ClimaTempo() {
	instanceFlag = false;
}

/*Método chamado quando o evento de passagem de hora é lançado.  
*Chama um método que atualiza os valores das temperaturas.*/
void ClimaTempo::event_phour_temp(const Event*, void *data){

	ClimaTempo::get_instance()->ambient_control(TimeControl::get_instance()->get_hora(), TimeControl::get_instance()->get_mes());
	#if(DEBUG_CTEMPO)
		cout << "\n Hora: " << TimeControl::get_instance()->get_hora() << "\n Temperatura do ar: " << ClimaTempo::get_instance()->tempArControl << "\n Temperatura do solo: " << ClimaTempo::get_instance()->tempSoloControl << "\n Temperatura das tocas: " << ClimaTempo::get_instance()->temTocaControl << "\n Chuva: " << ClimaTempo::get_instance()->qtChuva << endl;
	#endif
}

/*Método que recebe esperança (ou média) e variância (ou desvio padrão), e retorna um número
*gerado a partir de um sorteio normal (ou gaussiano)*/
double ClimaTempo::random_normal(double esp,double var)
{
	double u1=RAND_UNIFORME;
	double u2=RAND_UNIFORME;
	double z=sqrt(-2.0*log(u1))*cos(2*PI*u2);
	return esp+var*z;
};


/*Método que calcula e retorna a temperatura do ar na hora 'hour', de acordo com os outros argumenos recebidos pela função */
double ClimaTempo::temp_ar_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday){

	//armazena a temperatura do ar que será retornada
	double tempArSingle = 0;
	float tmin = tminToday;
    float tmax = tmaxToday;
	
	//ponto (hora do dia) onde a curva (temperatura) começa a declinar
	float ponto_inflecao = tmax - ((tmax - nextMin)/2);
	// variavel que define a inclinacao da reta.
	float a_reta = -(((tmax-nextMin)/2)/9);
	float b_reta = nextMin;
	/*constante que define onde sera o pico da fun�ao cos-seno (que horas sera a temperatura maxima do dia, esse valor coloca
	a temperatura maxima em 14:00 horas).*/
    double const1 = (PI/16);
	// constante que define como a fun�ao cos-seno deve decair apos a temperatura maxima, para que seu valor seja igual a b as 24:00h.
    double const2 = (PI/14);
	if (hour < 6 || hour > 21){
		/*reta que comeca em b, e cuja inclina�ao e definida por a. Ela vai de b ate a temperatura minima do dia seguinte,
		que definimos as 5:00h.*/
		if(hour < 6){
			tempArSingle = (a_reta * ((hour + 24) - 30)) + b_reta;
		}else{
			tempArSingle = (a_reta * (hour - 30)) + b_reta;
		}
	}else{
		//hora do dia entre 5:00h e 14:00h.
		if  (hour <= 14){
			//curva que varia entre a temperatura minima do dia atual, as 5:00h, e a temperatura maxima do dia atual, as 14:00h.
			tempArSingle = tmin + sin( ( hour - 6 ) * const1 )*(tmax-tmin);
		}else {
			//curva que varia da temperatura maxima do dia atual, as 14:00h, ate o valor b, que eh a temperatura minima do dia
			//seguinte somado com a varia�ao da temperatura entre 0:00h e 5:00h do dia seguinte, as 0:00h.
			tempArSingle = ponto_inflecao + ((tmax - nextMin)/2)*cos((hour - 14)*const2);
		}
	}
	
	return tempArSingle;
}

/*Calcula e retorna a temperatura do solo para a hora 'hour', de acordo com os outros argumentos recebidos.
* Essa temperatura toma como base a temperatura do ar, e tem mesmo formato de curva, tento porém uma amplitude maior, 
* e uma latência (atraso de fase) em relação a curva da temperatura do ar*/
double ClimaTempo::temp_solo_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday, float prevTmin, float prevTmax, float preVariaton){

	//Fator de atenuação da curva gerada pelo quadrado dos valores de temperatura do ar
	double alfa = 0.0425;
	//Deslocamento da curva para cima (shift), para que fique em  torno de valores razoavelmente reais
    double beta = 3.9;
	double lamp = 0;

	if(hour == 0){
		/*Para modelar o atraso de fase (0h = 24h, 24 - 1 = 23). Usa como parâmetros as temperaturas máximas e
		*mínimas do dia atual e do seguinte*/
		lamp = temp_ar_single((23),nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
	}else{
		if(hour == 6){
			/*Usa como parametros as temperaturas maximas e minimas do dia atual do dia anterior*/
			lamp = temp_ar_single((5), tminToday, tmaxToday, variationToday, prevTmin, prevTmax, preVariaton);
		}else{
			/*O parametro (hour-1) modela o atraso de fase, já que para os cálculos da temperatura do solo,
			* a base será  a temperatura do ar de um hora atrás. Usa como parâmetros as temperaturas maximas e mínimas 
			* do dia atual e do dia seguinte.*/
			lamp = temp_ar_single((hour-1), nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
		}
	}

	double tempSoloSingle = alfa*lamp*lamp + beta;
	return tempSoloSingle;
}

/*Calcula e retorna a temperatura das tocas (abaixo da superfície) para a hora 'hour', de acordo com os outros argumentos 
*recebidos. Essa temperatura toma como base a temperatura do ar, e tem mesmo formato de curva, tento, porém uma amplitude menor,
*e uma latência (atraso de fase) em relação a curva da temperatura do ar*/
double ClimaTempo::temp_toca_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday, float prevTmin, float prevTmax, float preVariaton){

	//Fator de atenuação da curva da temperatura do ar
	double alfa = 0.15;
	//Deslocamento para cima, para curva ter valores rozoavelmente realistas
	double beta = 26;
	double gama = 0;
	//Essa parte é semelhante ao que ocorre em temp_solo_single
	if(hour == 0){
		gama = temp_ar_single((23),nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
	}else{
		if(hour == 6){
			gama = temp_ar_single((5), tminToday, tmaxToday, variationToday, prevTmin, prevTmax, preVariaton);
		}else{
			gama = temp_ar_single((hour-1), nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
		}
	}
	double tempTocaSingle = gama*alfa + beta;
	return tempTocaSingle;
}

/*A principal caracteristica da umidade relativa do ar é a inversão de fase em relação às temperaturas, e sua variação,
*cujos valores podem ir de 0 a 100. Então esse método recebe a temperatura do ar, inverte a fase, e faz o ajuste 
*do valor correspondente da umidade relativa, referente ao valor de temperatura do ar passada*/
double ClimaTempo::umidade_relativa(double tempAr){

	double alfa = -3.9;
    double beta = 158;
	double umidadeRel;
	//Se estiver chuvendo, umidade relativa em 100% o dia todo
	if(qtChuva != 0){
		umidadeRel = 100;
	}else{
		umidadeRel = alfa*tempAr + beta;
	}

	if(umidadeRel > 100){
		return 100;
	}else{
		if(umidadeRel < 0){
			return 1;
		}
	}
	return umidadeRel;
	//return ((-3.9)*tempAr + 158);
}

/*Método que gerencia a geração dos parâmetros ambientais necessários para os cálculos de temperatura e umidade relativa do ar.
*No início de cada dia ele chama os métodos responsáveis pela geração desses parâmetros, e faz as aquisições levando em
consideração a época do ano.*/
void ClimaTempo::ambient_control(int hour, int month){

	//se for a primeira interação gera o cálculo
	if(hour == 2 || initialization==0){
		//verifica a quantidade de chuvas para esse dia
		qtChuva = prob_chuva(month);
		#if(DEBUG_CTEMPO)
			if((arquivo = fopen("Chuvas.txt", "a+")) != NULL){
				fprintf(arquivo, "%f\n", qtChuva);
				fclose(arquivo);
			}
		#endif
		
		//se for a primeira iteracao tem-se que gerar todas as variaveis
		if(initialization == 0){
			initialization = 1;

			//varia�ao do dia anterior
			this->variationPrev = random_normal(7 , 2);
			//variacao de hoje
			this->variationToday = random_normal(7 , 2);
			//variacao de amanha
			this->nextVariation = random_normal(7 , 2);
			// variacao daqui a dois dias
			this->nextVariation2 = random_normal(7 , 2);

			/* usa das medias e desvios padrao das temperaturas maximas e minimas dos meses de dezembro a abril, que sao iguais,
			para gerar numeros aleatorios que representarao temperaraturas maximas e minimas para esses meses*/
			if (month < 5 || month == 12){
				this->maxPrev = random_normal(31.5, 3);
				this->minPrev = random_normal(19.5, 3);
				this->tmaxToday = random_normal(31.5, 3);
				this->tminToday = random_normal(19.5, 3);
				this->nextMax = random_normal(31.5, 3);
				this->nextMin = random_normal(19.5, 3);
				this->nextMax2 = random_normal(31.5, 3);
				this->nextMin2 = random_normal(19.5, 3);
			}else {
				//para os meses de maio a agosto, a media da temperatura minima muda, entao eh necessario um outro tratamento
				if(month > 4 && month < 9){
					 this->maxPrev = random_normal(31.5, 3);
					 this->minPrev = random_normal(16.5, 3);
					 this->tmaxToday = random_normal(31.5, 3);
					 this->tminToday = random_normal(16.5, 3);
					 this->nextMax = random_normal(31.5, 3);
					 this->nextMin = random_normal(16.5, 3);
					 this->nextMax2 = random_normal(31.5, 3);
					 this->nextMin2 = random_normal(16.5, 3);

				}else {
					/*da mesma forma, para os meses de setembro a novembro, a media da temperatura maxima aumenta, sendo necessario
					outro tratamento.*/
					if(month > 8 && month < 12){
						this->maxPrev = random_normal(34.5, 3);
						this->minPrev = random_normal(19.5, 3);
						this->tmaxToday = random_normal(34.5, 3);
						this->tminToday = random_normal(19.5, 3);
						this->nextMax = random_normal(34.5, 3);
						this->nextMin = random_normal(19.5, 3);
						this->nextMax2 = random_normal(34.5, 3);
						this->nextMin2 = random_normal(19.5, 3);
					}
				}
			}
		//se ja nao for o primeiro dia, atualiza as variaveis, e gera apenas uma, com o mesmo criterio das anteriormente geradas
		}else {
			this->maxPrev = this->tmaxToday;
			this->minPrev = this->tminToday;
			this->tmaxToday = this->nextMax;
			this->tminToday = this->nextMin;
			this->nextMax = this->nextMax2;
			this->nextMin = this->nextMin2;
			this->variationPrev = this->variationToday;
			this->variationToday = this->nextVariation;
			this->nextVariation = this->nextVariation2;
			this->nextVariation2 = random_normal(7 , 2);
			if (month < 5 || month == 12){
				this->nextMax2 = random_normal(31.5, 3);
				this->nextMin2 = random_normal(19.5, 3);
			}else{
				if(month > 4 && month < 9){
					this->nextMax2 = random_normal(31.5, 3);
					this->nextMin2 = random_normal(16.5, 3);
				}else{
					if(month > 8 && month < 12){
						this->nextMax2 = random_normal(34.5, 3);
						this->nextMin2 = random_normal(19.5, 3);
					}
				}
			}
		}
	}

	#if(DEBUG_CTEMPO)
		cout << "\n TMaxToday = " <<  this->tmaxToday << "\n TMinToday = " << this->tminToday << "\n TMinNext = " << this->nextMin << "\n TMinPrev = " << this->minPrev << "\n VariationToday = " << this->variationToday << endl;
	#endif

	//Atualiza os valores das variáveis ambientais
	tempArControl = temp_ar_single(hour, this->nextMin, this->nextMax ,this->nextVariation , this->tminToday, this->tmaxToday ,this->variationToday);
	umidadeRel = umidade_relativa(tempArControl);
	tempSoloControl = temp_solo_single(hour, nextMin ,this->nextMax ,this->nextVariation , this->tminToday, this->tmaxToday ,this->variationToday, this->minPrev, this->maxPrev, this->variationPrev);
	temTocaControl = temp_toca_single(hour, nextMin ,this->nextMax ,this->nextVariation , this->tminToday, this->tmaxToday ,this->variationToday, this->minPrev, this->maxPrev, this->variationPrev);
	//vectorTempAr.push_back(tempArControl);

	#if(DEBUG_CTEMPO)
		if((arquivo = fopen("TempAr.txt", "a+")) != NULL){
			fprintf(arquivo, "%f\n", tempArControl);
			fclose(arquivo);
		}
		if((arquivo = fopen("UmidadeRelativa.txt", "a+")) != NULL){
			fprintf(arquivo, "%f\n", umidadeRel);
			fclose(arquivo);
		}
		/*if((arquivo = fopen("TempSoloGeral.txt", "a+")) != NULL){
			fprintf(arquivo, "%f\n", tempSoloControl);
			fclose(arquivo);
		}*/
		/*if((arquivo = fopen("TempToca.txt", "a+")) != NULL){
			fprintf(arquivo, "%f\n", temTocaControl);
			fclose(arquivo);
		}*/
	#endif
	
}

/*Calcula e retorna a quantidade de chuva em determinado dia.
*Esse método toma como base, o histórico de chuvas da região, com a média e o desvio padrão em cada mês,
*e o dia considerado o mais chuvoso do hitórico avaliado.*/
double ClimaTempo::prob_chuva(int mes){

	/*Nome inapropriado, na verdade é um vetor. Matrizes eram utilizadas no Matlab
	* As 12 primeiras posições são as médias de chuva (em mm) dos meses de Janeiro à Dezembro,
	* em ordem. As 12 últimas são os desvios padrão da precipitação, também dos meses de Janeiro
	* à Dezembro, em ordem.*/
	double matriz[24] = {129.28, 103.1, 105.83, 56.22, 11.49, 1.65, 0.6, 1.17, 8.2, 47.3, 123, 137.7, 107.1, 84, 113.7, 51.46, 19.36, 4, 2.17, 5.27, 17.17, 47, 74.4, 93.3};
    //Quantidade de chuva total que sera sorteada para aquele mes
    double qt_chuva_mes = 0;
	double qt_chuva_mes_temp = 0;
	//Quantidade de chuva no dia pedido, que podera ser = 0, ou nao
	double qt_chuva_dia_pedido = 0;
	//Probabilidade de ocorrencia de chuvas para qualquer dia naquele mes
	double prob_chuva_dia = 0;
	qt_chuva_mes_temp = random_normal(matriz[mes-1],matriz[mes+11]);
	//para evitar valores negativos do sorteio
	qt_chuva_mes = sqrt(qt_chuva_mes_temp*qt_chuva_mes_temp);
	prob_chuva_dia = qt_chuva_mes/QT_CHUVA_MAX;
	double count_temp = rand()%10000;
	//armazena um n�mero entre 0 e 1 com 4 casas decimais de precis�o
	double count = (count_temp/10000);

	//Se o a probabilidade de chuva for maior que o número sorteado
	if (prob_chuva_dia >= count){
		//Faz sorteio da quantidade de chuvas para o dia
		qt_chuva_dia_pedido = random_normal(matriz[mes-1],matriz[mes+11])/(prob_chuva_dia*30);
	}
	return sqrt(qt_chuva_dia_pedido*qt_chuva_dia_pedido);
}

double ClimaTempo::get_temp_ar(){
	return tempArControl;
}

double ClimaTempo::get_temp_solo(){
	return tempSoloControl;
}

double ClimaTempo::get_temp_toca(){
	return temTocaControl;
}

double ClimaTempo::get_umi_rel(){
	return umidadeRel;
}

double ClimaTempo::get_chuva_today(){
	return qtChuva;
}

//Descarregamento da memória, para permitir reinicialização
void ClimaTempo::unload_climaTempo(){
	ClimaTempo::instanceFlag = false;
	ClimaTempo::single = NULL;
}

//Implementação do singleton
PT(ClimaTempo) ClimaTempo::get_instance(){
	if(!instanceFlag) {
		#if(DEBUG_CTEMPO)
			cout << "\n single ctempo\n " << endl;
		#endif
		single = new ClimaTempo();
        instanceFlag = true;
    }
    return single;
}
