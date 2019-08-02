#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <iostream>

#include <string>
#include <algorithm>
#include <iterator>

#include "autoMudae/discord_hook.h"
#include "autoMudae/find_process.h"

std::string getDiscordToken() {
	std::vector<PROCESSENTRY32> results = SearchProcessList("Discord.exe");
	std::cout << "Discord.exe process(es) found : " << results.size() << "\n";
	if (results.size() == 0) {
		return "No process found to hook to. You may not have discord running or you are not running this elevated.\n";
	}
	std::string answer;
	std::for_each(results.begin(), results.end(), [&answer](PROCESSENTRY32& proc)
		{
			HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, proc.th32ProcessID);

			std::vector<void*> res = find_locs<std::vector<BYTE>>(phandle, std::vector<BYTE>({ 0x41,0x75,0x74,0x68,0x6F,0x72,0x69,0x7A,0x61,0x74,0x69,0x6F,0x6E,0x00,0x00,0x00,0x58,0x00,0x00,0x00 }), 20);
			if (int(res.size()) != 0) {
				std::for_each(res.begin(), res.end(), [phandle, &answer](void* resh) {
					std::string token = validate_data(phandle, resh);
					if (token != "") {
						*&answer = token;
						return;

					};
				}
				);
			};
			
			CloseHandle(phandle);
		}
	);
	return answer;
}

std::string validate_data(HANDLE process, void* address) {
	std::vector<char> buffer;
	buffer.resize(88); //tokens from the client are 88
	SIZE_T b_r;
	ReadProcessMemory(process, address, &buffer[0], SIZE_T(88), &b_r);
	
	if (!(buffer[0] == 'm')) return ""; 
	bool valid_ascii = 1; //Assumption
	std::for_each(buffer.begin(), buffer.end(), [&valid_ascii](char& test) {
		if (test >= 122 && test <= 33) *&valid_ascii = false; // Igiari!
	});
	if (valid_ascii) {
		return std::string(buffer.begin(), buffer.end());
	}
	return std::string("");


}
