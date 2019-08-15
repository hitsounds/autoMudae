#include "automudae/files.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

//Defaults to initalise file if it does not exist
const std::string default_chars = "Louise Françoise Le Blanc de La Vallière\nArietta";
const nlohmann::json default_config = {
	{"default_warning", 1},
	{"reset_min", 0},
	{"first_reset_hr", 0},
	{"server_id", ""},
	{"optional_listener_token", ""},
	{"optional_user_token", ""},
	{"optional_channel_id", ""}
};

int get_chars(std::vector<std::string>* output) {
	output->reserve(2);
	std::ifstream t("character_list.txt");
	if (t.fail()) {
		std::ofstream o("character_list.txt");
		o << default_chars;
		o.close();
		t.open("character_list.txt");
	}
	std::string line;
	while (std::getline(t, line)) {
		output->push_back(line);
	}
	return 0;
}

void get_config(nlohmann::json* output) {
	std::ifstream t("config.json");
	if (t.fail()) {
		std::ofstream o("config.json");
		o << std::setw(4) << default_config;
		o.close();
		t.open("config.json");
	}
	output->parse(t);
	t.close();
}
