/*
 * history.h
 * Created on: 29/05/2012
 * Author: heekinho
 */

#ifndef HISTORY_H
#define HISTORY_H

#include <list>
using namespace std;
#include "referenceCount.h"
#define MAXITENS 144

class History : public ReferenceCount {
public:
	History(int max_items = MAXITENS);
	virtual ~History();

	enum HistoryItem {
		HI_player_temperature = 0,
		HI_player_hydration,
		HI_world_temperature,
		HI_soil_temperature,
		HI_world_humidity,
		HI_time,
		HI_energy,
		HI_feeding,
		HI_total_energy_cost,

		//(Johnny)
		HI_system_seconds,
		HI_shadow,
		HI_ate,
		HI_running,

		HI_enum_size		
	};

	typedef list<float> HList;

	/* TODO: load_from_file, save_to_file, update */

	HList* get_list(History::HistoryItem item);
	float get_size(History::HistoryItem item) const;
	float get_last_element(History::HistoryItem item) const;

	float get_largest_element(History::HistoryItem item);
	float get_smallest_element(History::HistoryItem item);
	static float get_largest_element(History::HList* the_list);
	static float get_smallest_element(History::HList* the_list);

	void add_element(History::HistoryItem item, float value);
	void clear(History::HistoryItem item);

	void output(History::HistoryItem item, const string &name, ostream &out) const;
	void output_to_file(History::HistoryItem item, string path) const;
	void History::output_pupil() const;


private:
	int _max_items;
	HList _history[HI_enum_size];
};


class Event;
class CalangosHistory : public History {
public:

	CalangosHistory(int max_items = MAXITENS);

	static void update(const Event*, void* data);
	void update();
};

#endif /* HISTORY_H */
