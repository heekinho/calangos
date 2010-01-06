#ifndef VETORES_H

#define VETORES_H



#include <vector>

#include <queue>



#include "player.h"



/*! A classe Vetores é responsável por criar e controlar os vetores que serão

 * passados como argumentos para a geração dos graficos pela classe GuiManager.*/

class Vetores {

public:

	// Modelo singleton, ao iniciar utilizar os parametros

	static Vetores* get_instance();

	~Vetores();
	static void unload_vetores();
	

	queue<double> getVectorTemperaturaLagarto();

	queue<double> getVectorHidratacaoLagarto();

	queue<double> getVectorTemperaturaAr();

        queue<double> getVectorTemperaturaSolo();

	queue<double> getVectorUmidadeAmbiente();

        queue<double> getVectorTempo();

        queue<double> getVectorEnergia();

        queue<double> getVectorAlimentacao();

        queue<double> getVectorGastoEnergeticoTotal();

	

	//funções para pegar os ultimos elementos dos vetores.

	double getLastElementTemperaturaLagarto();

	double getLastElementHidratacaoLagarto();

	double getLastElementTemperaturaAr();

        double getLastElementTemperaturaSolo();

	double getLastElementUmidadeAmbiente();

        double getLastElementTempo();

        double getLastElementEnergia();

        double getLastElementAlimentacao();

        double getLastElementGastoEnergeticoTotal();

	

	//funções para pegar o tamanho dos vetores.

	double getSizeVectorTemperaturaLagarto();

	double getSizeVectorHidratacaoLagarto();

	double getSizeVectorTemperaturaAr();

        double getSizeVectorTemperaturaSolo();

	double getSizeVectorUmidadeAmbiente();

        double getSizeVectorTempo();

        double getSizeVectorEnergia();

        double getSizeVectorAlimentacao();

        double getSizeVectorGastoEnergiticoTotal();

	

	//funções para pegar o maior elemento dos vetores.

        double getLargestElementTemperaturaLagarto();



        //funções para pegar o menor elemento dos vetores.

        double getSmallestElementTemperaturaLagarto();



        //por default os elementos serão adicionadas no final do vetor

	void addElementVectorTemperaturaLagarto(double tempLagarto);

	void addElementVectorHidratacaoLagarto(double hidratacao);

	void addElementVectorTemperaturaAr(double tempAr);

        void addElementVectorTemperaturaSolo(double tempSolo);

	void addElementVectorUmidadeAmbiente(double umidade);

        void addElementVectorTempo(double tempo);

        void addElementVectorEnergia(double energia);

        void addElementVectorAlimentacao(double alimentacao);

        void addElementVectorGastoEnergeticoTotal(double gastoEnergeticoTotal);


private:

	//Construtor privado por causa do singleton.

	Vetores();

	

	// Controle do Singleton

	static bool instanceFlag;

	static Vetores *singleVector;

	

	queue<double> vectorTemperaturaLagarto;

	queue<double> vectorHidratacaoLagarto;

	queue<double> vectorTemperaturaAr;

        queue<double> vectorTemperaturaSolo;

	queue<double> vectorUmidadeAmbiente;

        queue<double> vectorTempo;

        queue<double> vectorEnergia;

        queue<double> vectorAlimentacao;

        queue<double> vectorGastoEnergeticoTotal;





	

};



#endif

