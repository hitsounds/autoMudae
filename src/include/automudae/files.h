#pragma once
#include "nlohmann/json.hpp"
#include <string>
#include <vector>

int get_chars(std::vector<std::string>* output);

void get_config(nlohmann::json* output);