
#include "stateHistory.h"
#include "TimeControl.h"
#include "player.h"
#include "algorithm"
#include "simdunas.h"
#include "microClima.h"
#include "energySimulator.h"


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

void stateHistory::event_add_states(){
	state dataShadow;
	state dataComeu;
	state dataCorrendo;

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
		
	
	
}
void stateHistory::event_add_states(const Event*, void* data){
	((stateHistory*)data)->event_add_states();
}
