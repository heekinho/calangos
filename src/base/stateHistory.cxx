
#include "stateHistory.h"
#include "TimeControl.h"
#include "player.h"
#include "algorithm"
#include "simdunas.h"
#include "microClima.h"
#include "energySimulator.h"


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
void stateHistory::output(stateHistory::SHistoryItem item, const string &name, ostream &out) const {
	cout << "--" << endl;
	cout << "Imprimindo histórico de " << name << ":" << endl;

	SHList::const_iterator it;
	int i;
	for(i = 0, (it = _shistory[item].begin()); it != _shistory[item].end(); it++, i++){
		//AJEITAR ESSE METODO
		//cout << "[" << i << "] " << (*it.) << endl;
	}
	cout << "--" << endl;
}

void stateHistory::event_add_states(){
	cout << "ALGUMA COISA: "<< endl;
	PT(TimeControl) time_control = TimeControl::get_instance();
	if(Player::get_instance()->changed_Shadow() == 1 || Player::get_instance()->changed_Shadow() == 2){
		
		state dataShadow;
		dataShadow.hour_event = time_control->get_hora_generica();
		dataShadow.occurrence = Player::get_instance()->changed_Shadow();
		add_element(stateHistory::SH_changed_shadow, dataShadow);
		
	}

	
}
void stateHistory::event_add_states(const Event*, void* data){
	((stateHistory*)data)->event_add_states();
}
