/*
 * morfologySimulator.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "morfologySimulator.h"

MorfologySimulator::MorfologySimulator(PT(PlayerHealth) health) : Simulator(health) {
	_ideal_months_to_max_size = 36; //TODO: Configuração
}

MorfologySimulator::~MorfologySimulator(){

}
