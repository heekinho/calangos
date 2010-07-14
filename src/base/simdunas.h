#ifndef SIMDUNAS_H
#define SIMDUNAS_H

#define DEBUG 1

#include <iostream>
#include <string>
using namespace std;

#include "pandaFramework.h"
#include "session.h"

class Session;

class Simdunas {
public:
	static PandaFramework* get_framework();
	static void set_framework(PandaFramework *framework);

	static WindowFramework* get_window();
	static void set_window(WindowFramework* window);

	static EventHandler* get_evt_handler();
	static void set_evt_handler(EventHandler *evt_handler);

	static EventQueue* get_evt_queue();
	static void set_evt_queue(EventQueue *evt_queue);

	static void init_types();

private:
	static PandaFramework *framework;
	static WindowFramework *window;
	static EventQueue *evt_queue;
	static EventHandler *evt_handler;
};

#endif
