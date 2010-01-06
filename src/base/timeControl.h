#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include "pandabase.h"
#include "eventQueue.h"
#include "eventHandler.h"

class TimeControl : public TypedReferenceCount{

  //char* return_month(int month);
  //void ShowInformation();
public:
	~TimeControl();

	//Singleton
	static PT(TimeControl) get_instance();

	/*M�todo que faz o controle da rela��o entre a passagem do tempo real e o tempo virtual,
	gerando eventos sempre a ocorre aluma mudan�a*/
	void update_time_control(float elapsed_time);

	int get_minuto();
	int get_hora();
	int get_dia();
	int get_mes();
	int get_ano();
	double get_hora_generica();
	bool get_stop_time();
	bool get_habilita_event_frame_gui();
	float get_seconds_min();

	void set_virtual_time_hour(float timeHour);
	void set_virtual_time_month(int timeMonth);
	void set_hour(int hour);
	void set_month(int month);
	void set_pass_time(float pass_time);
	void set_stop_time(bool stop_time);
	void set_habilita_event_frame_gui(bool habilita_event_frame_gui);

	typedef void EventCallbackFunction(const Event *, void *);
	void notify_after_n_frames(int after_n_frames, EventCallbackFunction *function, void *data);

	// Bloco de m�todos que processam os eventos relacionados a passagem do tempo virtual
	static void event_pframe_gui_options(const Event *, void *data);
	static void event_pframe(const Event *, void *data);
	static void event_psegundo_real(const Event *, void *data);
	static void event_pminute(const Event *, void *data);
	static void event_phour(const Event *, void *data);
	static void event_pday(const Event *, void *data);
	static void event_pmonth(const Event *, void *data);
	static void event_pyear(const Event *, void *data);

	// Inicializados no cxx por ser non-integral
	static const string EV_pass_frame_gui_options;
	static const string EV_pass_frame;
	static const string EV_pass_minute;
	static const string EV_pass_hour;
	static const string EV_pass_day;
	static const string EV_pass_month;
	static const string EV_pass_year;
	static const string EV_segundo_real;

	// M�todo Auxiliar para partes do c�digo que desejarem obter informa��es sobre
	// o tempo decorrido entre um frame e outro.
	float get_elapsed_time();

	static void unload_timeControl();

	// Typed Object
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "TimeControl"); }

	static float virtualTime;

private:
	// Controle do singleton
	static bool instanceFlag;
	static PT(TimeControl) single;

    TimeControl();
	//TimeControl(float pass_time, float virtual_time_hour, float virtual_time_month, int hour_p, int month_p);

	// Tempo decorrido entre o frame atual e o anterior
	float _elapsed_time;
	// Fator de divis�o do elapsed_time
	float passTime;
	// Soma dos elapsed_time's;
	float count_et;
	// Quantos minutos reais valer�o um dia
	int virtualTimeHour;
	// Com quantos dias passados mudar� o m�s
	int virtualTimeMonth;
	// Hora do dia
	int hour;
	// Armazena o m�s do ano
	int month;
	/* V�ri�veis de controle de tempo virtual */
	int minute;
	// Armazena o dia do m�s
	int day;
	// Armazena o ano desde o come�o do jogo
	// Pode ser os anos de vida do lagarto por exemplo
	int year;
	// Faz o controle da chamada da fun��o AmbientControl()
	int ambientControl;
	//Vari�vel que controla a parada do tempo
	bool stop_time;
	//Vari�vel que habilita o evento event_pframe_gui_options
	bool habilita_event_frame_gui;
	//quantos segundos reais equivalem a 1 minuto virtual
	float seconds_min;

	float count_second;
	/* Gera��o e controle de eventos */
	// Ponteiro para a fila de eventos
	EventQueue *p_queue;
	// Ponteiro para o processador de eventos
	EventHandler *p_handler;

	static TypeHandle _type_handle;
};

#endif
