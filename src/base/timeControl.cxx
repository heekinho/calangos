#include "timeControl.h"

#include "event.h"
#include "eventHandler.h"
#include "throw_event.h"

#include "clockObject.h"
#include "eventParameter.h"
#include "menu.h"


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

#define DEBUG false//true
#define INIT_HOUR 6

TypeHandle TimeControl::_type_handle;

// Inicializacao de non-integral type
const string TimeControl::EV_pass_frame_gui_options = "EV_PASSFRAME_GUIOPTIONS";
const string TimeControl::EV_pass_frame = "EV_PASSFRAME";
const string TimeControl::EV_segundo_real = "EV_SEGUNDO_REAL";
const string TimeControl::EV_pass_minute = "EV_PASSMINUTE";
const string TimeControl::EV_pass_hour = "EV_PASSHOUR";
const string TimeControl::EV_pass_day = "EV_PASSDAY";
const string TimeControl::EV_pass_month = "EV_PASSMONTH";
const string TimeControl::EV_pass_year = "EV_PASSYEAR";

bool TimeControl::instanceFlag = false;
PT(TimeControl) TimeControl::single = NULL;
float TimeControl::virtualTime = 3;

TimeControl::TimeControl() {

	passTime = 1;
	count_et = 0;
	count_second = 0;
	//MUDAR DE NOME
	virtualTimeHour = TimeControl::virtualTime;//Menu::get_instance()->get_minuto_dia_virtual();//
	virtualTimeMonth = 1; //numero de dias por mes
	minute = 0;
	hour = INIT_HOUR;
	day = 1;
	month = 12;
	year = 0;
	ambientControl = 0;
	stop_time = false;
	habilita_event_frame_gui = false;
	p_queue = EventQueue::get_global_event_queue();
	p_handler = EventHandler::get_global_event_handler(p_queue);

	if(DEBUG){
		cout << "hour = " << hour << " day = " << day << " month = " << month << " year = "<< year << endl;
	}
	// Adiciona os "listeners"
	p_handler->add_hook(EV_pass_frame_gui_options, event_pframe_gui_options, this);
	p_handler->add_hook(EV_pass_frame, event_pframe, this);
	p_handler->add_hook(EV_segundo_real, event_psegundo_real, this);
	p_handler->add_hook(EV_pass_minute, event_pminute, this);
	p_handler->add_hook(EV_pass_hour, event_phour, this);
	p_handler->add_hook(EV_pass_day, event_pday, this);
	p_handler->add_hook(EV_pass_month, event_pmonth, this);
	p_handler->add_hook(EV_pass_year, event_pyear, this);

	const Event *ev_hour = new Event(EV_pass_hour);
	(*p_queue).queue_event(ev_hour);
}

TimeControl::~TimeControl() {
	instanceFlag = false;
	
}

void TimeControl::event_pframe_gui_options(const Event *, void *data){
	PT(TimeControl) time = (PT(TimeControl))(TimeControl*)data;
}

void TimeControl::event_pframe(const Event *, void *data){
	PT(TimeControl) time = (PT(TimeControl))(TimeControl*)data;
	//cout << "\n passed an frame"  << "\nelapsed_time: " << time->especial_count << endl;

	/* Como diria o Angra: "Tempo que passou, não vai mais voltar, tudo que se foi..."
	 * Ou seja: Os seguintes hooks podem ser excluídos pois o tempo não volta... :P */
	std::stringstream this_frame;
	this_frame << EV_pass_frame << "_" << (ClockObject::get_global_clock()->get_frame_count() - 1);
	time->p_handler->remove_hooks(this_frame.str());
}

void TimeControl::event_psegundo_real(const Event *, void *data){
	if(DEBUG){
		cout << "\n passed an real second" << endl;
	}
}

void TimeControl::event_pminute(const Event *, void *data){
	PT(TimeControl) time = (PT(TimeControl))(TimeControl*)data;
	if(DEBUG){
		cout << "\n passed an minute"  << time->get_minuto() << endl;
	}
}

void TimeControl::event_phour(const Event *, void *data){
	PT(TimeControl) time = (PT(TimeControl))(TimeControl*)data;
	if(DEBUG){
		cout << "\n passed an hour = " << time->get_hora() << endl;
	}
}

void TimeControl::event_pday(const Event *, void *data){
	PT(TimeControl) time = (PT(TimeControl))(TimeControl*)data;
	if(DEBUG){
		cout << "\n passed a day = " << time->get_dia() << endl;
	}
}

void TimeControl::event_pmonth(const Event *, void *data){
	PT(TimeControl) time = (PT(TimeControl))(TimeControl*)data;
	if(DEBUG){
		cout << "\n passed a month = " << time->get_mes() << endl;
	}
}

void TimeControl::event_pyear(const Event *, void *data){
	PT(TimeControl) time = (PT(TimeControl))(TimeControl*)data;
	if(DEBUG){
		cout << "\n passed an year = " << time->get_ano() << endl;
	}
}

void TimeControl::update_time_control(float elapsed_time){
	_elapsed_time = elapsed_time;

	if(stop_time == false){
		/*cria uma vari?vel event constante, pois o m?todo de enfileirar eventos da classe
		EventQueue s? aceita vari?veis constantes*/
		//evento de passagem de frame
		//const Event *ev_frame = new Event(EV_pass_frame);
		const Event *ev_frame = new Event(EV_pass_frame);
		 //enfileira o evento
		(*p_queue).queue_event(ev_frame);

		/* --------------------------------------------------------------------------- */
		//TODO: Colocar EV_... como atributo.
		std::stringstream pass_frame_numbered;
		pass_frame_numbered << EV_pass_frame << "_" << ClockObject::get_global_clock()->get_frame_count();
		const Event *ev_frame_numbered = new Event(pass_frame_numbered.str());
		(*p_queue).queue_event(ev_frame_numbered);
		/* --------------------------------------------------------------------------- */
		//quantos segundos reais equivalerão a 1 minuto virtual
		seconds_min = (virtualTimeHour*60.0)/(24*60);
		//quantos minutos virtuais equivalem a 1 segundo real
		float minuto_virtual = 24*60.0/(virtualTimeHour*60);
		
		count_et += elapsed_time;
        count_second += elapsed_time;
          
		if(ambientControl == TimeControl::hour){
			ambientControl += 1;
			if(ambientControl == 24){
				ambientControl = 0;
			}
		}
		if(count_second >= 1){ //passou 1 seg real
			const Event *ev_segundo_real = new Event(EV_segundo_real);
			(*p_queue).queue_event(ev_segundo_real);
			count_second -=1;
		}
		
		//considerando que recebe-se o elapsed_time em segundos.
		if(count_et >= seconds_min){
			minute += count_et / seconds_min;
			count_et = count_et - seconds_min * (int) (count_et / seconds_min);

			const Event *ev_minute = new Event(EV_pass_minute);
			(*p_queue).queue_event(ev_minute);

			if(minute >= 60){
				TimeControl::hour += (minute/60);
				minute = minute % 60;
         
                const Event *ev_hour = new Event(EV_pass_hour);
				(*p_queue).queue_event(ev_hour);

				if(hour >= 24){
					hour = 0;
					day += 1;
					const Event *ev_day = new Event(EV_pass_day);
					(*p_queue).queue_event(ev_day);

					if(day == (virtualTimeMonth+1)){
						month += 1;
						day = 1;
						const Event *ev_month = new Event(EV_pass_month);
						(*p_queue).queue_event(ev_month);

						if(month == 13){
							month = 1;
							year += 1;
							const Event *ev_year = new Event(EV_pass_year);
							(*p_queue).queue_event(ev_year);
						}
					}
				}
			}
		}
	}
	else{
		if(habilita_event_frame_gui == true){
			//evento de passagem de frame
			const Event *ev_frame_gui_options = new Event(EV_pass_frame_gui_options);
			//enfileira o evento
			(*p_queue).queue_event(ev_frame_gui_options);
		}
	}
}

int TimeControl::get_minuto(){
	return minute;
}

int TimeControl::get_hora(){
	return hour;
}

int TimeControl::get_dia(){
	return day;
}

int TimeControl::get_mes(){
	return month;
}

int TimeControl::get_ano(){
	return year;
}

double TimeControl::get_hora_generica(){

	int min = TimeControl::get_instance()->get_minuto();
	int hora = TimeControl::get_instance()->get_hora();
	double hora_generica = hora + min*0.01667;
	return hora_generica;
}

float TimeControl::get_elapsed_time(){
	return _elapsed_time;
}

bool TimeControl::get_stop_time(){
	return this->stop_time;
}

bool TimeControl::get_habilita_event_frame_gui(){
	return this->habilita_event_frame_gui;
}

float TimeControl::get_seconds_min(){
	return this->seconds_min;
}

void TimeControl::set_virtual_time_hour(float timeHour){
	//TODO: virtualTimeHour -> virtualTimeMinInHour
	virtualTimeHour = timeHour;
}

void TimeControl::set_virtual_time_month(int timeMonth){
	//TODO: virtualTimeMonth -> virtualTimeDaysInMonth
	virtualTimeMonth = timeMonth;
}

void TimeControl::set_hour(int hour_p){
	hour = hour_p;
}

void TimeControl::set_month(int month_p){
	month = month_p;
}

void TimeControl::set_pass_time(float pass_time){
	passTime = pass_time;
}

void TimeControl::set_stop_time(bool stop_time){
	this->stop_time = stop_time;
}

void TimeControl::set_habilita_event_frame_gui(bool habilita_event_frame_gui){
	this->habilita_event_frame_gui = habilita_event_frame_gui;
}


//IMPORTANTE: Não esquecer de retirar SEMPRE os hooks com frame_numbered.
void TimeControl::notify_after_n_frames(int after_n_frames, EventCallbackFunction *function, void *data){
	int target_frame = ClockObject::get_global_clock()->get_frame_count() + after_n_frames;

	std::stringstream listen_frame;
	listen_frame << EV_pass_frame << "_" << target_frame;

	p_handler->add_hook(listen_frame.str(), function, data);
}


PT(TimeControl) TimeControl::get_instance(){
	if(!instanceFlag) {
		if(DEBUG){
			cout << "\n single tcontrol\n " << endl;
		}
		single = new TimeControl();
        instanceFlag = true;
    }
    return single;
}

void TimeControl::unload_timeControl(){
cout<<"Unload time control"<<endl;
	
	//Retiranda os hooks adicionados
	TimeControl::get_instance()->p_handler->remove_hooks(TimeControl::get_instance()->EV_pass_day);
	TimeControl::get_instance()->p_handler->remove_hooks(TimeControl::get_instance()->EV_pass_frame);
	TimeControl::get_instance()->p_handler->remove_hooks(TimeControl::get_instance()->EV_pass_frame_gui_options);
	TimeControl::get_instance()->p_handler->remove_hooks(TimeControl::get_instance()->EV_pass_hour);
	TimeControl::get_instance()->p_handler->remove_hooks(TimeControl::get_instance()->EV_pass_minute);
	TimeControl::get_instance()->p_handler->remove_hooks(TimeControl::get_instance()->EV_pass_month);
	TimeControl::get_instance()->p_handler->remove_hooks(TimeControl::get_instance()->EV_pass_year);

	TimeControl::instanceFlag = false;
	TimeControl::single = NULL;
}


