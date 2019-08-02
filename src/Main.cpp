#include "automudae/discord_client.h"
#include "automudae/discord_hook.h"
#include "automudae/chars_file.h"

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
	
	//Get anime characters to search for
	std::cout << "Reading character file...\n";
	std::vector<std::string> characters;
	get_chars(&characters);

	myDiscordListenerClient client(token, 2);
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
