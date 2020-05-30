#include "automudae/discord_client.h"
#include "automudae/discord_hook.h"
#include "automudae/files.h"

#include "nlohmann/json.hpp"

#include <windows.h>
#include <iostream>
#include <string>
#include <unordered_set>



int main()
{
	//Asthetic details
	//TODO: Check spellin of Asthetic
	SetConsoleTitle("Auto-Mudaeing!");
	SetConsoleOutputCP(CP_UTF8);

	//Find running discord process, and look for token within it's memory
	//You know this might make this program a sort of malware
	//But its just easier to have my program search for the token
	//So I'll deal with the ethical reprecussions
	std::cout << "Starting...\nExtracting discord token...\n";
	std::string token = getDiscordToken();
	if (token.size() == 0) {
		std::cerr << "ERORR: failed to extract user token\n";
		std::cin.get();
		return 1;
	}



	//Read config file and handle missing values
	nlohmann::json conf;
	get_config(&conf);
	if (conf["default_warning"] == 1) {
		if (conf["reset_min"] == 0) {
			std::cout << "WARNING: reset_min in config.json is default value (0). Please set this appropriately or set \"default_warning\" to 0 to silence\n";
		}
		if (conf["first_reset_hr"] == 0) {
			std::cout << "WARNING: first_reset_hr in config.json is default value (0). Please set this appropriately or set \"default_warning\" to 0 to silence\n";
		}
	}
	if (conf["server_id"] == "") {
		std::cout << "ERROR: server_id not set in config.json. This is REQUIRED.\n";
		std::cin.get();
		return 1;
	}
	if (conf["muda_id"] == "") {
		std::cout << "ERROR: muda_id not set in config.json. This is REQUIRED. This is the discord id for the mudamaid which serves your server\n";
		std::cin.get();
		return 1;
	}


	//Get anime characters to search for
	std::cout << "Reading character file...\n";
	std::unordered_set<std::string> characters;
	get_chars(&characters);
	std::cout << "Search items loaded: " << characters.size() << "\n";


	//Run client
	myDiscordListenerClient client(token, 2);
	client.autoMudae_init(23, 36, conf, characters);
	client.run();







	#ifdef _DEBUG
		//Debug report
		std::cout << "Extracted token: " << token << "\n";
		//Exit the program
		std::cout << "Press enter to exit...";
		std::cin.get();
	#endif // DEBUG


}
