/*
 * achievements.cxx
 *
 *  Created on: Jan 2, 2012
 *      Author: jonatas
 */

#include "achievements.h"
#include "timeControl.h"

Achievements::Achievements() {
	count_bites = 0;
	lvl_senhor_mordida = 0;
	lvl_bom_de_boca = 0;
	count_species = 0;
	count_sobrevivente = 0;
	lvl_sobrevivente = 0;
	count_reprodutor = 0;
	lvl_reprodutor = 0;
	temp_min = 35;
	temp_max = 40;
	lvl_temperatura = 0;
	count_secs_temp = 0;
	counting_secs_temp = false;
}

Achievements::~Achievements() {}

void Achievements::inc_bites() {
	count_bites++;

	if (lvl_senhor_mordida == 0 && count_bites == 10) {
		clear_bites();
		lvl_senhor_mordida++;
	}
	else if (lvl_senhor_mordida == 1 && count_bites == 25) {
		clear_bites();
		lvl_senhor_mordida++;
	}
	else if (count_bites == 50) { // do lvl 2 para cima
		clear_bites();
		lvl_senhor_mordida++;
	}
	cout<<"incrementando o contador de mordidas"<<endl;
}

void Achievements::clear_bites() {
	count_bites = 0;
	cout<<"zerando o contador de mordidas"<<endl;
}

int Achievements::get_count_bites() {
	return count_bites;
}

int Achievements::get_lvl_senhor_mordida() {
	return lvl_senhor_mordida;
}

int Achievements::get_lvl_bom_de_boca() {
	return lvl_bom_de_boca;
}

int Achievements::get_count_species() {
	return count_species;
}

void Achievements::inc_meses_sobrevivente() {
	count_sobrevivente++;

	if (lvl_sobrevivente == 0 && count_sobrevivente == 4) {
		count_sobrevivente = 0;
		lvl_sobrevivente++;
	}
	else if (lvl_sobrevivente == 1 && count_sobrevivente == 7) {
		count_sobrevivente = 0;
		lvl_sobrevivente++;
	}
	else if (count_sobrevivente == 11) { // do lvl 2 para cima
		count_sobrevivente = 0;
		lvl_sobrevivente++;
	}
}

int Achievements::get_count_sobrevivente() {
	return count_sobrevivente;
}

int Achievements::get_lvl_sobrevivente() {
	return lvl_sobrevivente;
}

int Achievements::get_count_reprodutor() {
	return count_reprodutor;
}

int Achievements::get_lvl_reprodutor() {
	return lvl_reprodutor;
}

int Achievements::get_count_secs_temp() {
	return count_secs_temp;
}

int Achievements::get_lvl_temperatura() {
	return lvl_temperatura;
}

void Achievements::inc_reprodutor() {
	count_reprodutor++;

	if (lvl_reprodutor == 0 && count_reprodutor == 3) {
		count_reprodutor = 0;
		lvl_reprodutor++;
	}
	else if (lvl_reprodutor == 1 && count_reprodutor == 6) {
		count_reprodutor = 0;
		lvl_reprodutor++;
	}
	else if (count_reprodutor == 10) { // do lvl 2 para cima
		count_reprodutor = 0;
		lvl_reprodutor++;
	}
}

// verifica a espécie do alimento ingerido
void Achievements::check_edible_specie(Edible::Specie specie) {
	bool is_new = true;
	for (int i = 0; i < eaten_species.size(); i++) {
		if (specie == eaten_species.at(i)) {
			is_new = false;
			break;
		}
	}

	if (is_new) {
		eaten_species.push_back(specie);
		count_species++;

		switch (eaten_species.size()) {
			case 4:
			case 9:
			case 14:
				lvl_bom_de_boca++;
				count_species = 0;
				break;
		}
	}
}

void Achievements::checkTemperature(double temperature) {
	if (!counting_secs_temp) {
		if (temperature >= temp_min && temperature <= temp_max) {
			TimeControl::get_instance()->notify("count_seconds_temperature", count_seconds_temperature, this, 1);
			counting_secs_temp = true;
		}
	}
	else if (temperature < temp_min || temperature > temp_max) {
		counting_secs_temp = false;
	}
}

AsyncTask::DoneStatus Achievements::count_seconds_temperature(GenericAsyncTask* task, void* data) {
	Achievements* _this = (Achievements*) data;
	if (!_this->counting_secs_temp) {
		_this->count_secs_temp = 0;
		return AsyncTask::DS_done;
	}

	_this->count_secs_temp++;

	if (_this->lvl_temperatura == 0 && _this->count_secs_temp == 45) {
		_this->lvl_temperatura++;
		_this->count_secs_temp = 0;
	}
	else if (_this->lvl_temperatura == 1 && _this->count_secs_temp == 60) {
		_this->lvl_temperatura++;
		_this->count_secs_temp = 0;
	}
	else if (_this->count_secs_temp == 90) {
		_this->lvl_temperatura++;
		_this->count_secs_temp = 0;
	}

	return AsyncTask::DS_again;
}
