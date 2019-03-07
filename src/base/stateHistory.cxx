
#include "stateHistory.h"
#include "TimeControl.h"
#include "player.h"
#include "algorithm"
#include "simdunas.h"
#include "microClima.h"
#include "energySimulator.h"
#include "world.h"


int anterior_correndo = 0;

stateHistory::stateHistory()
{
	event_handler->add_hook(TimeControl::EV_segundo_real, event_add_states , this);
}

stateHistory::~stateHistory()
{

}

stateHistory::SHList* stateHistory::get_list(stateHistory::SHistoryItem item) {
	return &_shistory[item];
}

/*! Obtém o tamanho do histórico do item especificado */
float stateHistory::get_size(stateHistory::SHistoryItem item) const {
	return _shistory[item].size();
}



/*! Adiciona um elemento no histórico do item especificado */
void stateHistory::add_element(stateHistory::SHistoryItem item, state data){
	//if(_history[item].size() == _max_items) _history[item].pop_front();
	_shistory[item].push_back(data);
}

/*! Limpa o histórico do item especificado */
void stateHistory::clear(stateHistory::SHistoryItem item){
	_shistory[item].clear();
}

/*! Imprime o histórico do item especificado */
void stateHistory::output(stateHistory::SHistoryItem item, const string &name) const {
	cout << "--" << endl;
	cout << "IMPRIMINDO LISTA DE:    " << name << ":" << endl;

	SHList::const_iterator it;
	state evento;
	int i;
	for(i = 0, (it = _shistory[item].begin()); it != _shistory[item].end(); it++, i++){
		evento = (*it);
		//AJEITAR ESSE METODO
		cout << "[" << i << "] "<< "  HORA DO EVENTO: " << evento.hour_event<< "  ACONTECIMENTO: " << evento.occurrence << endl;
	}
	cout << "--" << endl;
}

/*! (JOHNNY) Imprime o histórico do item especificado em um arquivo */
#include <iostream>
#include <fstream>
void stateHistory::output_to_file(stateHistory::SHistoryItem item, string filePath) const {
	ofstream file;
	file.open(filePath.c_str());
	SHList::const_iterator it;
	int i;
	for (i = 0, (it = _shistory[item].begin()); it != _shistory[item].end(); it++, i++) {
		state acontecimento = (*it);
		file << acontecimento.occurrence << " ; " << acontecimento.hour_event << " ; " << acontecimento.event_day << endl;
	}
	file.close();
}

void stateHistory::event_add_states(){
	
	state dataShadow;
	state dataComeu;
	state dataCorrendo;
	state dataSendoPerseguido;
	state dataSendoAtacado;


	PT(TimeControl) time_control = TimeControl::get_instance();
	dataShadow.occurrence = Player::get_instance()->changed_Shadow();
	
	if(dataShadow.occurrence != 0){
		
		dataShadow.event_day = time_control->get_dia_passado();
		dataShadow.hour_event = time_control->get_hora_generica();
		add_element(stateHistory::SH_changed_shadow, dataShadow);
		//stateHistory::output(stateHistory::SH_changed_shadow,"SOMBRA");
		
	}
	dataComeu.occurrence = Player::get_instance()->ate();

	if(dataComeu.occurrence == 1){
		dataComeu.event_day = time_control->get_dia_passado();
		dataComeu.hour_event = time_control->get_hora_generica();
		add_element(stateHistory::SH_eating, dataComeu);
		//stateHistory::output(stateHistory::SH_eating,"COMEU");
		
	}

	dataCorrendo.occurrence = PlayerControl::get_instance()->get_running();
	if(dataCorrendo.occurrence == 0 || dataCorrendo.occurrence == 1 || dataCorrendo.occurrence == 2){
		dataCorrendo.event_day = time_control->get_dia_passado();
		dataCorrendo.hour_event = time_control->get_hora_generica();
		add_element(stateHistory::SH_running, dataCorrendo);
		//stateHistory::output(stateHistory::SH_running,"CORRENDO");
	}

	dataSendoPerseguido.occurrence = Player::get_instance()->is_being_chased();
	dataSendoPerseguido.event_day = time_control->get_dia_passado();
	dataSendoPerseguido.hour_event = time_control->get_hora_generica();
	add_element(stateHistory::SH_being_chased, dataSendoPerseguido);


	dataSendoAtacado.occurrence = Player::get_instance()->is_being_bited();
	if (dataSendoAtacado.occurrence == 1) {
		dataSendoAtacado.event_day = time_control->get_dia_passado();
		dataSendoAtacado.hour_event = time_control->get_hora_generica();
		add_element(stateHistory::SH_being_attacked, dataSendoAtacado);
	}


	//resetando o flag de ate, stateShadow, flag_is_being_chased, flag_is_being_bited em player. (Johnny)
	Player::get_instance()->reset_flags(World::get_world()->get_terrain()->get_shadows()->is_in_shadow(*player, 0.1));
	
}
void stateHistory::event_add_states(const Event*, void* data){
	((stateHistory*)data)->event_add_states();
}
