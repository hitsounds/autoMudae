#include <windows.h>
#include <tlhelp32.h>
//#include <tchar.h>
//#include <stdio.h>

#include <vector>
#include <iostream>
#include <iterator>

#include "autoMudae/find_process.h"


std::vector<PROCESSENTRY32> SearchProcessList(const char* search_name)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	std::vector<PROCESSENTRY32> results;
	
	results.reserve(4);

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		std::cerr << "CreateToolhelp32Snapshot (of processes)";
		return results;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		std::cerr << "Process32First"; // show cause of failure
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return results;
	}

	//Find processes with name search_name
	do
	{
		if (!strcmp(pe32.szExeFile, search_name)) {
			results.push_back(pe32);
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return results;
}

/*void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}*/
