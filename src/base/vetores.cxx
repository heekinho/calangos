#include "vetores.h"

#include <queue>
#include <algorithm>

bool Vetores::instanceFlag = false;
Vetores* Vetores::singleVector = NULL;


#define TAMANHO_VETOR_TEMPERATURA_LAGARTO 180.0
#define TAMANHO_VETOR_UMIDADE_LAGARTO 180.0
#define TAMANHO_VETOR_TEMPERATURA_AMBIENTE 180.0
#define TAMANHO_VETOR_HIDRATACAO_AMBIENTE 180.0
#define TAMANHO_VETOR_TEMPO 180.0


//Construtor
Vetores::Vetores() {
	//vectorTemperaturaLagarto = new queue<double>();
}

//Destrutor
Vetores::~Vetores() {
	instanceFlag = false;
}

/*! "Construtor" da classe Vetores na forma Singleton. Inicializa todas as

 * variáveis.

 * @return single Referencia para o Vetores recém-criado */
Vetores* Vetores::get_instance() {
    if (!instanceFlag) {
        singleVector = new Vetores();
        instanceFlag = true;
    }
    return singleVector;
}

void Vetores::unload_vetores() {
    delete singleVector;
    singleVector = NULL;
    instanceFlag = false;
}

//VETOR DE TEMPERATURA DO LAGARTO--------------------------------------
void Vetores::addElementVectorTemperaturaLagarto(double tempLagarto) {
    if (vectorTemperaturaLagarto.size() < 180) {
        vectorTemperaturaLagarto.push(tempLagarto);
    } else {
        vectorTemperaturaLagarto.pop();
        vectorTemperaturaLagarto.push(tempLagarto);
    }
}



double Vetores::getLastElementTemperaturaLagarto(){

	return vectorTemperaturaLagarto.back();

}



double Vetores::getSizeVectorTemperaturaLagarto(){

	return vectorTemperaturaLagarto.size();

}



queue<double> Vetores::getVectorTemperaturaLagarto(){

	return vectorTemperaturaLagarto;

}



//VETOR DE HIDRATACAO DO LAGARTO---------------------------------------

void Vetores::addElementVectorHidratacaoLagarto(double hidratacao){



	if(vectorHidratacaoLagarto.size() < 180){

		vectorHidratacaoLagarto.push(hidratacao);

	}

	else {

		vectorHidratacaoLagarto.pop();

		vectorHidratacaoLagarto.push(hidratacao);

	}

}



double Vetores::getLastElementHidratacaoLagarto(){

	return vectorHidratacaoLagarto.back();

}



double Vetores::getSizeVectorHidratacaoLagarto(){

	return vectorHidratacaoLagarto.size();

}



queue<double> Vetores::getVectorHidratacaoLagarto(){

	return vectorHidratacaoLagarto;

}



//VETOR DE TEMPERATURA DO AR----------------------------------------------------

void Vetores::addElementVectorTemperaturaAr(double tempAmbiente){



	if(vectorTemperaturaAr.size() < 180){

		vectorTemperaturaAr.push(tempAmbiente);

	}

	else {

		vectorTemperaturaAr.pop();

		vectorTemperaturaAr.push(tempAmbiente);

	}

}



double Vetores::getLastElementTemperaturaAr(){

	return vectorTemperaturaAr.back();

}



double Vetores::getSizeVectorTemperaturaAr(){

	return vectorTemperaturaAr.size();

}



queue<double> Vetores::getVectorTemperaturaAr(){

	return vectorTemperaturaAr;

}



//VETOR DE TEMPERATURA DO SOLO--------------------------------------------------

void Vetores::addElementVectorTemperaturaSolo(double tempSolo){



	if(vectorTemperaturaSolo.size() < 180){

		vectorTemperaturaSolo.push(tempSolo);

	}

	else {

		vectorTemperaturaSolo.pop();

		vectorTemperaturaSolo.push(tempSolo);

	}

}



double Vetores::getLastElementTemperaturaSolo(){

	return vectorTemperaturaSolo.back();

}



double Vetores::getSizeVectorTemperaturaSolo(){

	return vectorTemperaturaSolo.size();

}



queue<double> Vetores::getVectorTemperaturaSolo(){

	return vectorTemperaturaSolo;

}



//VETOR DE UMIDADE DO AMBIENTE-----------------------------------------

void Vetores::addElementVectorUmidadeAmbiente(double umidadeAmbiente){



	if(vectorUmidadeAmbiente.size() < 180){

		vectorUmidadeAmbiente.push(umidadeAmbiente);

	}

	else {

		vectorUmidadeAmbiente.pop();

		vectorUmidadeAmbiente.push(umidadeAmbiente);

	}

}



double Vetores::getLastElementUmidadeAmbiente(){

	return vectorUmidadeAmbiente.back();

}



double Vetores::getSizeVectorUmidadeAmbiente(){

	return vectorUmidadeAmbiente.size();

}



queue<double> Vetores::getVectorUmidadeAmbiente(){

	return vectorUmidadeAmbiente;

}



//VETOR DO TEMPO ---------------------------------------------------------------

void Vetores::addElementVectorTempo(double tempo){



	if(vectorTempo.size() < 180){

		vectorTempo.push(tempo);

	}

	else {

		vectorTempo.pop();

		vectorTempo.push(tempo);

	}

}



double Vetores::getLastElementTempo(){

	return vectorTempo.back();

}



double Vetores::getSizeVectorTempo(){

	return vectorTempo.size();

}



queue<double> Vetores::getVectorTempo(){

	return vectorTempo;

}



//VETOR DE ENERGIA--------------------------------------------------------------

void Vetores::addElementVectorEnergia(double energia){



	if(vectorEnergia.size() < 180){

		vectorEnergia.push(energia);

	}

	else {

		vectorEnergia.pop();

		vectorEnergia.push(energia);

	}

}



double Vetores::getLastElementEnergia(){

	return vectorEnergia.back();

}



double Vetores::getSizeVectorEnergia(){

	return vectorEnergia.size();

}



queue<double> Vetores::getVectorEnergia(){

	return vectorEnergia;

}



//VETOR DE ALIMENTACAO----------------------------------------------------------

void Vetores::addElementVectorAlimentacao(double alimentacao){



	if(vectorAlimentacao.size() < 180){

		vectorAlimentacao.push(alimentacao);

	}

	else {

		vectorAlimentacao.pop();

		vectorAlimentacao.push(alimentacao);

	}

}



double Vetores::getLastElementAlimentacao(){

	return vectorAlimentacao.back();

}



double Vetores::getSizeVectorAlimentacao(){

	return vectorAlimentacao.size();

}



queue<double> Vetores::getVectorAlimentacao(){

	return vectorAlimentacao;

}



//VETOR DE GASTO TOTAL ENERGICO-------------------------------------------------

void Vetores::addElementVectorGastoEnergeticoTotal(double gastoEnergeticoTotal){



	if(vectorGastoEnergeticoTotal.size() < 180){

		vectorGastoEnergeticoTotal.push(gastoEnergeticoTotal);

	}

	else {

		vectorGastoEnergeticoTotal.pop();

		vectorGastoEnergeticoTotal.push(gastoEnergeticoTotal);

	}

}



double Vetores::getLastElementGastoEnergeticoTotal(){

	return vectorGastoEnergeticoTotal.back();

}



double Vetores::getSizeVectorGastoEnergiticoTotal(){

	return vectorGastoEnergeticoTotal.size();

}



queue<double> Vetores::getVectorGastoEnergeticoTotal(){

	return vectorGastoEnergeticoTotal;

}

double Vetores::getLargestElement(queue<double> fila) {
    queue<double> filaTemp(fila);
    double maior = filaTemp.front();
    int tamanhoFor = filaTemp.size();

    for (int i = 1; i < tamanhoFor; i++) {
        if (filaTemp.front() > maior)
            maior = filaTemp.front();
        filaTemp.pop();
    }
    return maior;
}

double Vetores::getSmallestElement(queue<double> fila) {
    queue<double> filaTemp(fila);
    double menor = filaTemp.front();
    int tamanhoFor = filaTemp.size();

    for (int i = 0; i < tamanhoFor; i++) {
        if (filaTemp.front() < menor)
            menor = filaTemp.front();
        filaTemp.pop();
    }
    return menor;
}
