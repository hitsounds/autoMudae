#include "automudae/discord_client.h"
#include "automudae/discord_hook.h"
#include "automudae/files.h"

#include "nlohmann/json.hpp"

#include <windows.h>
#include <iostream>
#include <string>



int main()
{
	SetConsoleTitle("Auto-Mudaeing!");
	SetConsoleOutputCP(CP_UTF8);

	//Find running discord process, and look for token within it's memory
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
		if (conf["server_id"].size() == 0) {
			std::cout << "ERROR: server_id not set in config.json. This is REQUIRED.\n";
			std::cin.get();
			return 1;
		}

	}


	//Get anime characters to search for
	std::cout << "Reading character file...\n";
	std::vector<std::string> characters;
	get_chars(&characters);


	//Run client
	myDiscordListenerClient client(token, 2);
	client.autoMudae_init();
	client.run();







	#ifdef _DEBUG
		//Debug report
		std::cout << "Extracted token: " << token << "\n";
		std::cout << "Search items loaded: " << characters.size() << "\n";
		//Exit the program
		std::cout << "Press enter to exit...";
		std::cin.get();
	#endif // DEBUG


}
