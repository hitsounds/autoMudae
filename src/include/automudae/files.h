#pragma once
#include "nlohmann/json.hpp"
#include <string>
#include <vector>
#include <unordered_set>

int get_chars(std::unordered_set<std::string>* output);

void get_config(nlohmann::json* output);