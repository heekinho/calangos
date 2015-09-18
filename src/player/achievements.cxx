/*
 * achievements.cxx
 *
 *  Created on: Jan 2, 2012
 *      Author: jonatas
 */

#include "achievements.h"
#include "timeControl.h"
#include "pauseScreen.h"
#include "notificationManager.h"
#include "mouseButton.h"
#include "achievementsWindow.h"
#include "guiManager.h"

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
	lvl_intocavel = 0;
	count_secs_untouched = 0;
	count_guerreiro = 0;
	lvl_guerreiro = 0;
	if (Session::get_instance()->is_lizard_adult()) {
		adulto = 1;
	} else {
		adulto = 0;
	}
}

Achievements::~Achievements() {
	eaten_species.clear();
}

//Achievements::Achievements(PT(ScreenManager) manager) : Screen(manager) {
//	Achievements();
//	load();
//	hide();
//}

//void Achievements::load() {
//
//}
//
//void Achievements::hide() {
//
//}

void Achievements::inc_bites() {
	count_bites++;

	if (lvl_senhor_mordida == 0 && count_bites == 10) {
		clear_bites();
		inc_lvl_senhor_mordida();
	}
	else if (lvl_senhor_mordida == 1 && count_bites == 25) {
		clear_bites();
		inc_lvl_senhor_mordida();
	}
	else if (count_bites == 50) { // do lvl 2 para cima
		clear_bites();
		inc_lvl_senhor_mordida();
	}
	simdunas_cat.debug()<<"incrementando o contador de mordidas"<<endl;
}

void Achievements::inc_lvl_senhor_mordida() {
	lvl_senhor_mordida++;
	stringstream lvl_senhor_mordida_str;
	lvl_senhor_mordida_str<<lvl_sobrevivente;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-senhormordidap2"," da realização: Senhor Mordida Perfeita");
	NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_senhor_mordida_str.str() + msg2);
}

void Achievements::clear_bites() {
	count_bites = 0;
	simdunas_cat.debug()<<"zerando o contador de mordidas"<<endl;
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
		inc_lvl_sobrevivente();
	}
	else if (lvl_sobrevivente == 1 && count_sobrevivente == 7) {
		count_sobrevivente = 0;
		inc_lvl_sobrevivente();
	}
	else if (count_sobrevivente == 11) { // do lvl 2 para cima
		count_sobrevivente = 0;
		inc_lvl_sobrevivente();
	}
}

void Achievements::inc_lvl_sobrevivente() {
	if (Session::get_instance()->is_lizard_adult() == false && adulto == 1) {
		lvl_sobrevivente++;
		stringstream lvl_sobrevivente_str;
		lvl_sobrevivente_str<<lvl_sobrevivente;
		string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
		string msg2	= ConfigVariableString("msg-survivalp2", " da realização: O Sobrevivente");
		NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_sobrevivente_str.str() + msg2);
	}
	adulto = 0;
	//Last_Achievement_Message * lam;
	//PT(Last_Achievement_Message) lam;
	//lam->show_last_achievement(msg);

	//Last_Achievement_Message::show_last_achievement(msg);

	//default_button_config(btn_realizacoes, np_btn_realizacoes, msg, LVecBase3f(-0.5, 0, -0.5), show_achievements_window);
}

//void Achievements::show_achievements_window() {
//	wnd_realizacoes = new AchievementsWindow(get_root(), 1.5, 1.1, "Realizações", -0.8, -0.8);
//	wnd_realizacoes->set_pos_y(0);
//}

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

int Achievements::get_count_secs_untouched() {
	return count_secs_untouched;
}

int Achievements::get_lvl_intocavel() {
	return lvl_intocavel;
}

void Achievements::reset_count_secs_untouched() {
	count_secs_untouched = 0;
}

int Achievements::get_count_guerreiro() {
	return count_guerreiro;
}

int Achievements::get_lvl_guerreiro() {
	return lvl_guerreiro;
}

void Achievements::inc_reprodutor() {
	count_reprodutor++;

	if (lvl_reprodutor == 0 && count_reprodutor == 3) {
		count_reprodutor = 0;
		inc_lvl_reprodutor();
	}
	else if (lvl_reprodutor == 1 && count_reprodutor == 6) {
		count_reprodutor = 0;
		inc_lvl_reprodutor();
	}
	else if (count_reprodutor == 10) { // do lvl 2 para cima
		count_reprodutor = 0;
		inc_lvl_reprodutor();
	}
}

void Achievements::inc_lvl_reprodutor() {
	lvl_reprodutor++;
	stringstream lvl_reprodutor_str;
	lvl_reprodutor_str<<lvl_sobrevivente;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-reprodutorp2", " da realização: O Reprodutor");
	NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_reprodutor_str.str() + msg2);
}

// verifica a espécie do alimento ingerido
void Achievements::check_edible_specie(Edible::Specie specie) {
	bool is_new = true;
	for (unsigned int i = 0; i < eaten_species.size(); i++) {
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
				inc_lvl_bom_de_boca();
				count_species = 0;
				break;
		}
	}
}

void Achievements::inc_lvl_bom_de_boca() {
	lvl_bom_de_boca++;
	stringstream lvl_bom_de_boca_str;
	lvl_bom_de_boca_str<<lvl_bom_de_boca;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-bomdebocap2", " da realização: O Bom de Boca");
	NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_bom_de_boca_str.str() + msg2);
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

	if (!PauseScreen::is_opened) {
		_this->count_secs_temp++;

		if (_this->lvl_temperatura == 0 && _this->count_secs_temp == 45) {
			_this->inc_lvl_temperatura();
			_this->count_secs_temp = 0;
		}
		else if (_this->lvl_temperatura == 1 && _this->count_secs_temp == 60) {
			_this->inc_lvl_temperatura();
			_this->count_secs_temp = 0;
		}
		else if (_this->count_secs_temp == 90) {
			_this->inc_lvl_temperatura();
			_this->count_secs_temp = 0;
		}
	}

	return AsyncTask::DS_again;
}

void Achievements::inc_lvl_temperatura() {
	lvl_temperatura++;
	stringstream lvl_temperatura_str;
	lvl_temperatura_str<<lvl_temperatura;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-temperaturap2", " da realização: Temperatura");
	NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_temperatura_str.str() + msg2);
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

	if (!PauseScreen::is_opened) {
		_this->count_secs_hyd++;

		if (_this->lvl_hidratacao == 0 && _this->count_secs_hyd == 60) {
			_this->inc_lvl_hidratacao();
			_this->hyd_min = 80;
			_this->count_secs_hyd = 0;
		}
		else if (_this->lvl_hidratacao == 1 && _this->count_secs_hyd == 120) {
			_this->inc_lvl_hidratacao();
			_this->hyd_min = 90;
			_this->count_secs_hyd = 0;
		}
		else if (_this->count_secs_hyd == 180) {
			_this->inc_lvl_hidratacao();
			_this->count_secs_hyd = 0;
		}
	}

	return AsyncTask::DS_again;
}

void Achievements::inc_lvl_hidratacao() {
	lvl_hidratacao++;
	stringstream lvl_hidratacao_str;
	lvl_hidratacao_str<<lvl_hidratacao;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-hidratacaop2", " da realização: Hidratação");
	NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_hidratacao_str.str() + msg2);
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

	if (!PauseScreen::is_opened) {
		_this->count_secs_energy++;

		if (_this->lvl_energia == 0 && _this->count_secs_energy == 60) {
			_this->inc_lvl_energia();
			_this->energy_min = 80;
			_this->count_secs_energy = 0;
		}
		else if (_this->lvl_energia == 1 && _this->count_secs_energy == 120) {
			_this->inc_lvl_energia();
			_this->energy_min = 90;
			_this->count_secs_energy = 0;
		}
		else if (_this->count_secs_energy == 180) {
			_this->inc_lvl_energia();
			_this->count_secs_energy = 0;
		}
	}

	return AsyncTask::DS_again;
}

void Achievements::inc_lvl_energia() {
	lvl_energia++;
	stringstream lvl_energia_str;
	lvl_energia_str<<lvl_energia;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-energiap2", " da realização: Energia");
	NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_energia_str.str() + msg2);
}

AsyncTask::DoneStatus Achievements::count_seconds_untouched(GenericAsyncTask* task, void* data) {
	Achievements* _this = (Achievements*) data;

	if (!PauseScreen::is_opened) {
		_this->count_secs_untouched++;

		if (_this->lvl_intocavel == 0 && _this->count_secs_untouched == 60) {
			_this->inc_lvl_intocavel();
			_this->count_secs_untouched = 0;
		}
		else if (_this->lvl_intocavel == 1 && _this->count_secs_untouched == 120) {
			_this->inc_lvl_intocavel();
			_this->count_secs_untouched = 0;
		}
		else if (_this->count_secs_untouched == 180) {
			_this->inc_lvl_intocavel();
			_this->count_secs_untouched = 0;
		}
	}

	return AsyncTask::DS_again;
}

void Achievements::inc_lvl_intocavel() {
	lvl_intocavel++;
	stringstream lvl_intocavel_str;
	lvl_intocavel_str<<lvl_intocavel;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-intocavelp2", " da realização: O Intocável");
	NotificationManager::get_instance()->show_notification(msg1 + " " + lvl_intocavel_str.str() + msg2);
}

void Achievements::inc_guerreiro() {
	count_guerreiro++;
	simdunas_cat.debug()<<"count_guerreiro = "<<count_guerreiro<<endl;

	if (lvl_guerreiro == 0 && count_guerreiro == 2) {
		count_guerreiro = 0;
		inc_lvl_guerreiro();
	}
	else if (lvl_guerreiro == 1 && count_guerreiro == 5) {
		count_guerreiro = 0;
		inc_lvl_guerreiro();
	}
	else if (count_guerreiro == 10) { // do lvl 2 para cima
		count_guerreiro = 0;
		inc_lvl_guerreiro();
	}
}

void Achievements::inc_lvl_guerreiro() {
	lvl_guerreiro++;
	stringstream lvl_guerreiro_str;
	lvl_guerreiro_str<<lvl_guerreiro;
	string msg1 = ConfigVariableString("msg-conquistap1", "Foi alcançado o nível ");
	string msg2 = ConfigVariableString("msg-guerreirop2", " da realização: Guerreiro");
	NotificationManager::get_instance()->show_notification(msg1 + " " +lvl_guerreiro_str.str() + msg2);
}
