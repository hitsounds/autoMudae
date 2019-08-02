#include "automudae/chars_file.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Defaults to initalise file if it does not exist
const std::string defaults = "Louise Françoise Le Blanc de La Vallière\nArietta";


int get_chars(std::vector<std::string>* output) {
	output->reserve(2);
	std::ifstream t("character_list.txt");
	if (t.fail()) {
		std::ofstream o("character_list.txt");
		o << defaults;
		o.close();
		t.open("character_list.txt");
	}
	std::string line;
	while (std::getline(t, line)) {
		output->push_back(line);
	}
	return 0;
}