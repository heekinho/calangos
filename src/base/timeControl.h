#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include "pandabase.h"
#include "eventQueue.h"
#include "eventHandler.h"

#include "genericAsyncTask.h"

typedef void EventCallbackFunction(const Event *, void *);

class TimeControl : public TypedReferenceCount{
public:
	/*! Tipo de período de tempo */
	enum PeriodType {
		PT_frame,
		PT_real_second,
		PT_real_minute,
		PT_virtual_minute,
		PT_virtual_hour,
		PT_virtual_day
	};

	//Singleton
	static PT(TimeControl) get_instance();
	static void unload_timeControl();
	~TimeControl();

	/* Método que faz o controle da relação entre a passagem do tempo real e o tempo virtual,
	 * gerando eventos sempre a ocorre aluma mudança */
	void update_time_control(float elapsed_time);

	bool is_night();

	float get_virtual_time_hour();
	int get_minuto();
	int get_hora();
	int get_dia();
	int get_mes();
	int get_ano();
	double get_hora_generica();
	bool get_stop_time();
	bool get_habilita_event_frame_gui();
	float get_seconds_min();
	EventHandler* get_p_handler();

	void set_virtual_time_hour(float timeHour);
	void set_virtual_time_month(int timeMonth);
	void set_hour(int hour);
	void set_month(int month);
	void set_pass_time(float pass_time);
	void set_stop_time(bool stop_time);
	void set_habilita_event_frame_gui(bool habilita_event_frame_gui);

	void update_real_seconds();
	float get_vminute_count();

	void notify(const string &task_name, GenericAsyncTask::TaskFunc *function, void* data, double delay = 0.0);
	void notify_after_n_frames(int after_n_frames, EventCallbackFunction *function, void *data);
	void notify_after_n_seconds(int after_n_secs, EventCallbackFunction *function, void *data);
	void notify_after_n_vminutes(int after_n_vmins, EventCallbackFunction *function, void *data);
	void notify(float time_after, EventCallbackFunction *function, void *data, PeriodType period_type);
	void notify_real_time(float time_after, EventCallbackFunction *function, void *data);

	void throw_real_second_event(int second);

	// Bloco de métodos que processam os eventos relacionados a passagem do tempo virtual
	static void event_pframe_gui_options(const Event *, void *data);
	static void event_pframe(const Event *, void *data);
	static void event_psegundo_real(const Event *, void *data);
	static void event_pminute(const Event *, void *data);
	static void event_ptenminutes(const Event *, void *data);
	static void event_phour(const Event *, void *data);
	static void event_pday(const Event *, void *data);
	static void event_pmonth(const Event *, void *data);
	static void event_pyear(const Event *, void *data);

	// Inicializados no cxx por ser non-integral
	static const string EV_pass_frame_gui_options;
	static const string EV_pass_frame;
	static const string EV_pass_second;
	static const string EV_pass_minute;
	static const string EV_pass_ten_minutes;
	static const string EV_pass_hour;
	static const string EV_pass_day;
	static const string EV_pass_month;
	static const string EV_pass_year;
	static const string EV_segundo_real;
	static const string EV_pass_vminute;

	float get_elapsed_time();

private:
	// Controle do singleton
	static bool instanceFlag;
	static PT(TimeControl) single;

    TimeControl();

	// Tempo decorrido entre o frame atual e o anterior
	float _elapsed_time;
	// Fator de divisão do elapsed_time
	float passTime;
	// Soma dos elapsed_time's;
	float count_et;
	// Quantos minutos reais valerão um dia
	int virtualTimeHour;
	// Com quantos dias passados mudará o mês
	int virtualTimeMonth;
	// Hora do dia
	int hour;
	// Armazena o mês do ano
	int month;
	/* Variáveis de controle de tempo virtual */
	int minute;
	// Armazena o dia do mês
	int day;
	// Armazena o ano desde o começo do jogo
	// Pode ser os anos de vida do lagarto por exemplo
	int year;
	// Faz o controle da chamada da função AmbientControl()
	int ambientControl;
	//Variável que controla a parada do tempo
	bool stop_time;
	//Variável que habilita o evento event_pframe_gui_options
	bool habilita_event_frame_gui;
	//quantos segundos reais equivalem a 1 minuto virtual
	float seconds_min;

	float vminute_count;

	float last_second;

	/* Geração e controle de eventos */
	// Ponteiro para a fila de eventos
	EventQueue *p_queue;
	// Ponteiro para o processador de eventos
	EventHandler* p_handler;


public:
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "TimeControl"); }
private:
	static TypeHandle _type_handle;
};

#endif
