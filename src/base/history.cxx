/*
 * history.cxx
 * Created on: 29/05/2012
 * Author: heekinho
 */

#include "history.h"

#include "algorithm"

History::History(int max_items) {
	_max_items = max_items;
}

History::~History() {

}

History::HList* History::get_list(History::HistoryItem item) {
	return &_history[item];
}

/*! Obtém o tamanho do histórico do item especificado */
float History::get_size(History::HistoryItem item) const {
	return _history[item].size();
}

/*! Obtém o último elemento no histórico do item especificado */
float History::get_last_element(History::HistoryItem item) const {
	return _history[item].back();
}

float History::get_largest_element(History::HList* the_list) {
	if(the_list->empty()) return 0;
	return *max_element(the_list->begin(), the_list->end());
}

/*! Obtém o menor elemento no histórico do item especificado */
float History::get_smallest_element(History::HList* the_list) {
	if(the_list->empty()) return 0;
	return *min_element(the_list->begin(), the_list->end());
}

/*! Obtém o maior elemento no histórico do item especificado */
float History::get_largest_element(History::HistoryItem item) {
//	if(_history[item].empty()) return 0;
//	return *max_element(_history[item].begin(), _history[item].end());
	return History::get_largest_element(&_history[item]);
}

/*! Obtém o menor elemento no histórico do item especificado */
float History::get_smallest_element(History::HistoryItem item) {
//	if(_history[item].empty()) return 0;
//	return *min_element(_history[item].begin(), _history[item].end());
	return History::get_smallest_element(&_history[item]);
}

/*! Adiciona um elemento no histórico do item especificado */
void History::add_element(History::HistoryItem item, float value){
	//if(_history[item].size() == _max_items) _history[item].pop_front();
	_history[item].push_back(value);
}

/*! Limpa o histórico do item especificado */
void History::clear(History::HistoryItem item){
	_history[item].clear();
}

/*! Imprime o histórico do item especificado */
void History::output(History::HistoryItem item, const string &name, ostream &out) const {
	out << "--" << endl;
	out << "Imprimindo histórico de " << name << ":" << endl;

	HList::const_iterator it;
	int i;
	for(i = 0, (it = _history[item].begin()); it != _history[item].end(); it++, i++){
		cout << "[" << i << "] " << (*it) << endl;
	}
	out << "--" << endl;
}

/*! (JOHNNY) Imprime o histórico do item especificado em um arquivo */
#include <iostream>
#include <fstream>
void History::output_to_file(History::HistoryItem item, string filePath) const {
	ofstream file;
	file.open(filePath.c_str());
	HList::const_iterator it;
	int i;
	for (i = 0, (it = _history[item].begin()); it != _history[item].end(); it++, i++) {
		file << (*it);
		file << endl;
	}
	file.close();
}

/*(JOHNNY) chamar esse método pra gerar todo o calangosreport (chamar esse método apenas #if(PUPIL))*/
#include "nameScreen.h"
#include "calangosMenuManager.h"
#include "stateHistory.h"
void History::output_pupil() const {
	string nomeUsuario = ((NameScreen*)CalangosMenuManager::get_instance()->get_name_screen().p())->get_name();
	//Criando a pasta que irá armazenar os arquivos do usuário atual:
	CreateDirectory("calangosreport", NULL);
	string pathPasta = "calangosreport/" + nomeUsuario;
	CreateDirectory(pathPasta.c_str(), NULL);
	//paths de cada um dos arquivos a serem gerados (calangosreport/nomeJogador/-----.csv):
	string pathWT = pathPasta + "/worldTemperature.csv";
	string pathPT = pathPasta + "/playerTemperature.csv";
	string pathPH = pathPasta + "/playerHydration.csv";
	string pathST = pathPasta + "/soilTemperature.csv";
	string pathWH = pathPasta + "/worldHumidity.csv";
	string pathT = pathPasta + "/time.csv";
	string pathE = pathPasta + "/energy.csv";
	string pathF = pathPasta + "/feeding.csv";
	string pathTEC = pathPasta + "/totalEnergyCost.csv";
	string pathS = pathPasta + "/sombra.csv";
	string pathC = pathPasta + "/comeu.csv";
	string pathCr = pathPasta + "/correu.csv";
	//Gerando todos os arquivos csv:
	Session::get_instance()->history()->output_to_file(History::HI_world_temperature, pathWT);
	Session::get_instance()->history()->output_to_file(History::HI_player_temperature, pathPT);
	Session::get_instance()->history()->output_to_file(History::HI_player_hydration, pathPH);
	Session::get_instance()->history()->output_to_file(History::HI_soil_temperature, pathST);
	Session::get_instance()->history()->output_to_file(History::HI_world_humidity, pathWH);
	Session::get_instance()->history()->output_to_file(History::HI_time, pathT);
	Session::get_instance()->history()->output_to_file(History::HI_energy, pathE);
	Session::get_instance()->history()->output_to_file(History::HI_feeding, pathF);
	Session::get_instance()->history()->output_to_file(History::HI_total_energy_cost, pathTEC);
	Session::get_instance()->shistory()->output_to_file(stateHistory::SH_changed_shadow, pathS);
	Session::get_instance()->shistory()->output_to_file(stateHistory::SH_eating, pathC);
	Session::get_instance()->shistory()->output_to_file(stateHistory::SH_running, pathCr);
}

#include "simdunas.h"
#include "player.h"
#include "microClima.h"
#include "energySimulator.h"
CalangosHistory::CalangosHistory(int max_items) : History (max_items) {
	event_handler->add_hook(TimeControl::EV_segundo_real, update, this);
	//event_handler->add_hook(TimeControl::EV_pass_ten_minutes, update, this);
}

void CalangosHistory::update(const Event*, void* data){
	((CalangosHistory*)data)->update();
}

void CalangosHistory::update(){
	
	//simdunas_cat.debug() << "CalangosHistory Update" << endl;
	PT(TimeControl) time_control = TimeControl::get_instance();
	add_element(History::HI_time, time_control->get_hora_generica());

	//PT(Player) player = Player::get_instance();
	add_element(History::HI_player_temperature, player->get_temperature());
	add_element(History::HI_player_hydration, player->get_hydration());
	add_element(History::HI_energy, player->get_energy());

	PT(EnergySimulator) energy_simulator = player->player_health_simulator->get_energy_simulator();
	add_element(History::HI_feeding, energy_simulator->get_food_energy_buffer());
	add_element(History::HI_total_energy_cost, energy_simulator->get_total_cost());

	PT(MicroClima) micro_clima = MicroClima::get_instance();
	add_element(History::HI_world_temperature, micro_clima->get_temp_ar_sector());
	add_element(History::HI_world_humidity, micro_clima->get_umidade_relativa_sector());
	add_element(History::HI_soil_temperature, player->get_environment_temp());
}
