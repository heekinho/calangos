/*
 * playerHealthSimulator.h
 * Created on: 18/05/2012
 * Author: heekinho
 */

#ifndef PLAYERHEALTHSIMULATOR_H
#define PLAYERHEALTHSIMULATOR_H

#include "simdunas.h"
#include "referenceCount.h"

class PlayerHealth;
class Player;
class EnergySimulator;
class TemperatureSimulator;
class MorfologySimulator;
class HydrationSimulator;
class DietSimulator;

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


/*! Obtem x de 0 a 1 considerando o range (a,b)
 *  TODO: Mudar nome. */
INLINE float compress_range(float a, float b, float x){
	return (x - a)/(b - a);
}

/*! Obtem x clamped no range [a , b] */
INLINE float clamp(float a, float b, float x){
	if(x < a) return a;
	if(x > b) return b;
	return x;
}


#include "notifyCategoryProxy.h"
NotifyCategoryDecl(player_health, EXPCL_PANDA_EVENT, EXPTP_PANDA_EVENT);

/* TODO: Mudar nome para PlayerHealthManager para não ficar ambiguo com outros simuladores? */
class PlayerHealthSimulator : public ReferenceCount {
public:
	PlayerHealthSimulator(PT(PlayerHealth) health);
	virtual ~PlayerHealthSimulator();

//	void configure_events();

	void pass_second();
	static void event_pass_second(const Event *, void * data);

	void pass_day();
	static void event_pass_day(const Event *, void * data);

	void pass_month();
	static void event_pass_month(const Event *, void * data);


	PT(EnergySimulator) get_energy_simulator() const;
	PT(TemperatureSimulator) get_temperature_simulator() const;
	PT(MorfologySimulator) get_morfology_simulator() const;
    PT(HydrationSimulator) get_hydration_simulator() const;
    PT(DietSimulator) get_diet_simulator() const;

protected:
	float get_num_updates_per_hour();
private:

    PT(PlayerHealth) _health;

    /* Simulators. Poderia ser genérico. Mas melhor ser explícito mesmo, certo? */
    PT(EnergySimulator) _energy_simulator;
    PT(TemperatureSimulator) _temperature_simulator;
    PT(MorfologySimulator) _morfology_simulator;
    PT(HydrationSimulator) _hydration_simulator;
    PT(DietSimulator) _diet_simulator;

    float _num_updates_per_hour;
};

#endif /* PLAYERHEALTHSIMULATOR_H */