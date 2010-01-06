#include <iostream>
//#include <stdlib.h>
#include <stdio.h>
//#include <math.h>
#include <vector>
//#include <time.h>
using namespace std;

#include "climaTempo.h"

#define RAND_UNIFORME (double)rand()/(double)RAND_MAX
/*Quantidade maxima de chuvas no historico de 4 localidades proximas as
dunas, ocorrido em Morpara, marco de 1960*/
#define QT_CHUVA_MAX 624
#define PI 3.141592653589793

#define DEBUG false

TypeHandle ClimaTempo::_type_handle;

bool ClimaTempo::instanceFlag = false;
PT(ClimaTempo) ClimaTempo::single = NULL;

ClimaTempo::ClimaTempo() {

	/*inicializa o rand, para que a cada chamada do jogo, os valores
	*retornados por essa fun��es sejam diferentes*/
	srand(time(NULL));
	initialization = 0;
	this->ambient_control(TimeControl::get_instance()->get_hora(), TimeControl::get_instance()->get_mes());

	//initialization = this->initialization;
	Simdunas::get_evt_handler()->add_hook(TimeControl::get_instance()->EV_pass_hour, event_phour_temp, this);
}

ClimaTempo::~ClimaTempo() {
	instanceFlag = false;
}

void ClimaTempo::event_phour_temp(const Event*, void *data){

	ClimaTempo::get_instance()->ambient_control(TimeControl::get_instance()->get_hora(), TimeControl::get_instance()->get_mes());
	if(DEBUG){
		cout << "\n Hora: " << TimeControl::get_instance()->get_hora() << "\n Temperatura do ar: " << ClimaTempo::get_instance()->tempArControl << "\n Temperatura do solo: " << ClimaTempo::get_instance()->tempSoloControl << "\n Temperatura das tocas: " << ClimaTempo::get_instance()->temTocaControl << "\n Chuva: " << ClimaTempo::get_instance()->qtChuva << endl;
	}
}

double ClimaTempo::random_normal(double esp,double var)
{
	double u1=RAND_UNIFORME;
	double u2=RAND_UNIFORME;
	double z=sqrt(-2.0*log(u1))*cos(2*PI*u2);
	return esp+var*z;
};


//TODO:MUDAR PARA DECAIMENTO SER ENTRE 20 E 6 HORAS...
double ClimaTempo::temp_ar_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday){

	//armazena a temperatura do ar a ser retornada
	double tempArSingle = 0;
	float tmin = tminToday;
    float tmax = tmaxToday;

	float ponto_inflecao = tmax - ((tmax - nextMin)/2);
	// variavel que define a inclinacao da reta.
	float a_reta = -(((tmax-nextMin)/2)/9);
	float b_reta = nextMin;
	/*// define em que temperatura acima da minina a senoide acaba.
    float endSin = (tmin + variationToday);*/
	/*constante que define onde sera o pico da fun�ao cos-seno (que horas sera a temperatura maxima do dia, esse valor coloca
	a temperatura maxima em 14:00 horas).*/
    double const1 = (PI/16);
	// constante que define como a fun�ao cos-seno deve decair apos a temperatura maxima, para que seu valor seja igual a b as 24:00h.
    double const2 = (PI/14);
	if (hour < 6 || hour > 21){
		/*reta que come�a em b, e cuja inclina�ao e definida por a. Ela vai de b ate a temperatura minima do dia seguinte,
		que definimos que sera as 5:00h.*/
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
	/*if(qtChuva != 0){
		//TODO: continuidade de um dia para o outro
		//tempArSingle = tempArSingle*0.9;
	}*/
	return tempArSingle;
}

double ClimaTempo::temp_solo_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday, float prevTmin, float prevTmax, float preVariaton){

	//tentar explicar alfa e beta
	double alfa = 0.0425;
    double beta = 3.9;
	double lamp = 0;
	if(hour == 0){
		lamp = temp_ar_single((23),nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
		//lamp = temp_ar_single((23),tminToday, tmaxToday, variationToday, prevTmin, prevTmax, preVariaton);
	}else{
		if(hour == 6){
			lamp = temp_ar_single((5), tminToday, tmaxToday, variationToday, prevTmin, prevTmax, preVariaton);
		}else{
			lamp = temp_ar_single((hour-1), nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
		}
	}
	double tempSoloSingle = alfa*lamp*lamp + beta;
	return tempSoloSingle;
}

double ClimaTempo::temp_toca_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday, float prevTmin, float prevTmax, float preVariaton){

	double alfa = 0.15;
	double beta = 26;
	double gama = 0;
	if(hour == 0){
		gama = temp_ar_single((23),nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
	}else{
		if(hour == 6){
			gama = temp_ar_single((5), tminToday, tmaxToday, variationToday, prevTmin, prevTmax, preVariaton);
		}else{
			gama = temp_ar_single((hour-1), nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
		}
	}
	//double teste = temp_ar_single((hour-1), nextMin, nextMax, nextVariation, tminToday, tmaxToday, variationToday);
	double tempTocaSingle = gama*alfa + beta;
	//cout << "teste:" << teste << "\ngama: " <<gama << "\ntemptoca" << tempTocaSingle<< endl;
	return tempTocaSingle;
}


double ClimaTempo::umidade_relativa(double tempAr){

	double alfa = -3.9;
    double beta = 158;
	double umidadeRel;
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

void ClimaTempo::ambient_control(int hour, int month){
	if(hour == 2 || initialization==0){//se for a primeira interação gera o cálculo
		//verifica a quantidade de chuvas para esse dia
		qtChuva = prob_chuva(month);
		if(DEBUG){
			if((arquivo = fopen("Chuvas.txt", "a+")) != NULL){
				fprintf(arquivo, "%f\n", qtChuva);
				fclose(arquivo);
			}
		}
		
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

	if(DEBUG){
		cout << "\n TMaxToday = " <<  this->tmaxToday << "\n TMinToday = " << this->tminToday << "\n TMinNext = " << this->nextMin << "\n TMinPrev = " << this->minPrev << "\n VariationToday = " << this->variationToday << endl;
	}
	tempArControl = temp_ar_single(hour, this->nextMin, this->nextMax ,this->nextVariation , this->tminToday, this->tmaxToday ,this->variationToday);
	umidadeRel = umidade_relativa(tempArControl);
	tempSoloControl = temp_solo_single(hour, nextMin ,this->nextMax ,this->nextVariation , this->tminToday, this->tmaxToday ,this->variationToday, this->minPrev, this->maxPrev, this->variationPrev);
	temTocaControl = temp_toca_single(hour, nextMin ,this->nextMax ,this->nextVariation , this->tminToday, this->tmaxToday ,this->variationToday, this->minPrev, this->maxPrev, this->variationPrev);
	//vectorTempAr.push_back(tempArControl);

	if(DEBUG){
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
	}
	
}

double ClimaTempo::prob_chuva(int mes){

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

	if (prob_chuva_dia >= count)
		qt_chuva_dia_pedido = random_normal(matriz[mes-1],matriz[mes+11])/(prob_chuva_dia*30);
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

void ClimaTempo::unload_climaTempo(){
	ClimaTempo::instanceFlag = false;
	ClimaTempo::single = NULL;
}

PT(ClimaTempo) ClimaTempo::get_instance(){
	if(!instanceFlag) {
		if(DEBUG){
			cout << "\n single ctempo\n " << endl;
		}
		single = new ClimaTempo();
        instanceFlag = true;
    }
    return single;
}
