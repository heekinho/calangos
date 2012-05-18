/*
 * playerHealthSimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef PLAYERHEALTHSIMULATOR_H
#define PLAYERHEALTHSIMULATOR_H

#include "simdunas.h"
#include "playerHealth.h"
#include "referenceCount.h"

/*! Interface para rodar os simuladores de dinâmica */
class Simulator : public ReferenceCount {
public:
	Simulator(PT(PlayerHealth) health){
		this->health = health;
	}

	~Simulator(){
		health = NULL;
	}

	virtual void run_pass_second(){};
	virtual void run_pass_minute(){};
	virtual void run_pass_hour(){};
	virtual void run_pass_month(){};
	virtual void run_pass_year(){};
 // Tarefas de acumulação para os vetores.

protected:
	PT(PlayerHealth) health;
};

#include "microClima.h"
#include "player.h"

/*! Obtem x de 0 a 1 considerando o range (a,b) */
INLINE float compress_range(float a, float b, float x){
	return (x - a)/(b - a);
}

class PlayerHealthSimulator : public ReferenceCount {
public:
	PlayerHealthSimulator(PT(PlayerHealth) health);
	virtual ~PlayerHealthSimulator();

	void configure_events();
	static void event_pass_second(const Event *, void * data);
	static void event_pass_day(const Event *, void * data);
	static void event_pass_month(const Event *, void * data);


    double get_energy() const;
    void set_energy(double energy);

private:

    PT(PlayerHealth) _health;

    /* Simulators */
    //PT(EnergySimulator) _energy_simulator;

	/* Variaveis relacionadas a saude do lagarto:

	 * Saude e hidratacao variam de 0 a 100.
	 * Segundo Pedro o lagarto sobrevive no maximo (acho 7, confirmar) dias
	 * sem se alimentar e submetido a altas temperaturas */
	double _energy;


};

#endif /* PLAYERHEALTHSIMULATOR_H */
