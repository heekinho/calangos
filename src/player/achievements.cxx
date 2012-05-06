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
	hyd_min = 70;
	lvl_hidratacao = 0;
	count_secs_hyd = 0;
	counting_secs_hyd = false;
	energy_min = 70;
	lvl_energia = 0;
	count_secs_energy = 0;
	counting_secs_energy = false;
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

int Achievements::get_count_secs_hyd() {
	return count_secs_hyd;
}

int Achievements::get_lvl_hidratacao() {
	return lvl_hidratacao;
}

int Achievements::get_count_secs_energy() {
	return count_secs_energy;
}

int Achievements::get_lvl_energia() {
	return lvl_energia;
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

void Achievements::check_temperature(double temperature) {
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

void Achievements::check_hydration(double hydration) {
	if (!counting_secs_hyd) {
		if (hydration >= hyd_min) {
			TimeControl::get_instance()->notify("count_seconds_hydration", count_seconds_hydration, this, 1);
			counting_secs_hyd = true;
		}
	}
	else if (hydration < hyd_min) {
		counting_secs_hyd = false;
	}
}

AsyncTask::DoneStatus Achievements::count_seconds_hydration(GenericAsyncTask* task, void* data) {
	Achievements* _this = (Achievements*) data;
	if (!_this->counting_secs_hyd) {
		_this->count_secs_hyd = 0;
		return AsyncTask::DS_done;
	}

	_this->count_secs_hyd++;

	if (_this->lvl_hidratacao == 0 && _this->count_secs_hyd == 60) {
		_this->lvl_hidratacao++;
		_this->hyd_min = 80;
		_this->count_secs_hyd = 0;
	}
	else if (_this->lvl_hidratacao == 1 && _this->count_secs_hyd == 120) {
		_this->lvl_hidratacao++;
		_this->hyd_min = 90;
		_this->count_secs_hyd = 0;
	}
	else if (_this->count_secs_hyd == 180) {
		_this->lvl_hidratacao++;
		_this->count_secs_hyd = 0;
	}

	return AsyncTask::DS_again;
}

void Achievements::check_energy(double energy) {
	if (!counting_secs_energy) {
		if (energy >= energy_min) {
			TimeControl::get_instance()->notify("count_seconds_energy", count_seconds_energy, this, 1);
			counting_secs_energy = true;
		}
	}
	else if (energy < energy_min) {
		counting_secs_energy = false;
	}
}

AsyncTask::DoneStatus Achievements::count_seconds_energy(GenericAsyncTask* task, void* data) {
	Achievements* _this = (Achievements*) data;
	if (!_this->counting_secs_energy) {
		_this->count_secs_energy = 0;
		return AsyncTask::DS_done;
	}

	_this->count_secs_energy++;

	if (_this->lvl_energia == 0 && _this->count_secs_energy == 60) {
		_this->lvl_energia++;
		_this->energy_min = 80;
		_this->count_secs_energy = 0;
	}
	else if (_this->lvl_energia == 1 && _this->count_secs_energy == 120) {
		_this->lvl_energia++;
		_this->energy_min = 90;
		_this->count_secs_energy = 0;
	}
	else if (_this->count_secs_energy == 180) {
		_this->lvl_energia++;
		_this->count_secs_energy = 0;
	}

	return AsyncTask::DS_again;
}
