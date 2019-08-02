#include "automudae/discord_client.h"
#include "sleepy_discord/websocketpp_websocket.h"
#include <cpr/cpr.h>

//using SleepyDiscord::DiscordClient::DiscordClient;

void myDiscordListenerClient::onMessage(SleepyDiscord::Message message) {
		std::cout << message.author.username << "\n";
	}
