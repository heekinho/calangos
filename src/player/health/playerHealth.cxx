/*
 * playerHealth.cxx
 * Created on: 18/05/2012
 * Author: heekinho
 */

#include "playerHealth.h"
#include "load_prc_file.h"

PlayerHealth::PlayerHealth() {
	nout << "Construindo PlayerHealth" << endl;

}

PlayerHealth::~PlayerHealth() {
	// TODO Auto-generated destructor stub
}

/*! Carrega as informações do lagarto a partir de um arquivo de configuração */
void PlayerHealth::load_health(const Filename &path){
	ConfigPage* config_page = load_prc_file(path);
	string prefix = "calangos-lizard-";
	ideal_temperature = ConfigVariableDouble(prefix + "ideal-temperature", 36);
	max_temperature = ConfigVariableDouble(prefix + "max-temperature", 45);
	min_temperature = ConfigVariableDouble(prefix + "min-temperature", 15);
	temperature_tolerance = ConfigVariableDouble(prefix + "temperature-tolerance", 2);
	max_hours_without_food = ConfigVariableDouble(prefix + "max-hours-without-food", 160);
	max_hours_with_low_hidration = ConfigVariableDouble(prefix + "max-hours-with-low-hidration", 40);
	humidity_affects_hidration = ConfigVariableDouble(prefix + "humidity-affects-hidration", 40);
	humidity_param = ConfigVariableDouble(prefix + "humidity-param", 40);
	min_hydration = ConfigVariableDouble(prefix + "min-hydration", 40);
	min_energy = ConfigVariableDouble(prefix + "min-energy", 4);
	energy_cost_low_temperature = ConfigVariableDouble(prefix + "energy-cost-low-temperature", 10);
	energy_cost_high_temperature = ConfigVariableDouble(prefix + "energy-cost-high-temperature", 10);
	thermal_equilibrium_speed = ConfigVariableDouble(prefix + "thermal-equilibrium-speed", 10);

	config_page->write(nout);
	unload_prc_file(config_page);
}
