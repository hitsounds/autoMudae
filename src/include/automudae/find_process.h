#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

//Searches for processes with matching name
std::vector<PROCESSENTRY32> SearchProcessList(const char* search_name);

//Locate patterns within process memory
template <class inVec>
std::vector<void*> find_locs(HANDLE process, inVec pattern, int offset);

#include "find_process.inl"