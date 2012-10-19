/*
 * utils.cxx
 * Created on: 03/06/2012
 * Author: heekinho
 */

#include <stdlib.h>
#include <math.h>

#include "utils.h"

#include <iostream>
using namespace std;

/*! Macro de sorteio que retorna um valor de 0 e 1*/
#define RAND_UNIFORME ((double)rand()/(double)RAND_MAX)
#define PI 3.141592653589793

/*! Retornna um número aleatório de min a max */
double random(double min, double max){
	double range = max - min;
	return (double(rand())/double(RAND_MAX)) * range + min;
}

/*! Recebe esperança (ou média) e variância (ou desvio padrão),
 * e retorna um número gerado a partir de um sorteio normal (ou gaussiano) */
double gaussian_random(double expectation, double deviation){
	double u1 = RAND_UNIFORME;
	double u2 = RAND_UNIFORME;
	double z = sqrt(-2.0 * log(u1)) * cos(2 * PI * u2);
	return expectation + (deviation * z);
}


/*! Obtem x de 0 a 1 considerando o range (a,b)
 *  TODO: Mudar nome. */
double compress_range(double a, double b, double x){
	return (x - a)/(b - a);
}

/*! Obtem x clamped no range [a , b] */
double clamp(double a, double b, double x){
	if(x < a) return a;
	if(x > b) return b;
	return x;
}
