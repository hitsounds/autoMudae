#include "automudae/files.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_set>

//Defaults to initalise file if it does not exist
const std::string default_chars = "Louise Fran�oise Le Blanc de La Valli�re\nArietta";
const nlohmann::json default_config = {
	{"default_warning", 1},
	{"reset_min", 0},
	{"first_reset_hr", 0},
	{"server_id", ""},
	{"optional_listener_token", ""},
	{"optional_user_token", ""},
	{"optional_channel_id", ""},
	{"muda_id", ""}
};

int get_chars(std::unordered_set<std::string>* output) {
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
		output->insert(line);
	}
	return 0;
}

void get_config(nlohmann::json* output) {
	#ifdef _DEBUG
		*output = {
		{"default_warning", 1},
		{"reset_min", 36},
		{"first_reset_hr", 19},
		{"server_id", "714222829121568868"},
		{"optional_listener_token", ""},
		{"optional_user_token", ""},
		{"optional_channel_id", "714222832648716378"},
		{"muda_id", "548984223592218634"}
		};
		return;
	#endif
	std::ifstream t("config.json");
	if (t.fail()) {
		std::ofstream o("config.json");
		o << std::setw(4) << default_config;
		o.close();
		t.open("config.json");
	}
	t >> *output;
	t.close();
}
