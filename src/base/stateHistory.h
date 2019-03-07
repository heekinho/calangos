#pragma once
#include "referenceCount.h"
#include <list>

using namespace std;


class Event;
class stateHistory : public ReferenceCount {
public:
	stateHistory(void);
	virtual ~stateHistory(void);


	enum SHistoryItem {
		
		SH_changed_shadow,
		SH_eating,
		SH_running,

		//(Johnny)
		SH_being_chased,
		SH_being_attacked,
		
		SHI_enum_size
	};


	struct state{
		float hour_event;
		int occurrence;
		int event_day;
	};
	
	typedef list<state> SHList;
	SHList* get_list(stateHistory::SHistoryItem item);
	float get_size(stateHistory::SHistoryItem item) const;
	
	static void event_add_states(const Event *, void* data);
	void event_add_states();

    void add_element(stateHistory::SHistoryItem item, state data);
	void clear(stateHistory::SHistoryItem item);

	void output(stateHistory::SHistoryItem item, const string &name) const;
	void output_to_file(stateHistory::SHistoryItem item, string filePath) const;


private:
	SHList _shistory[SHI_enum_size];

};
