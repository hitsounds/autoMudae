#include "automudae/discord_client.h"
#include "sleepy_discord/websocketpp_websocket.h"
#include <cpr/cpr.h>
#include <string>

void myDiscordListenerClient::onMessage(SleepyDiscord::Message msg) {
	std::cout << msg.serverID << ": " << msg.content << "\n";
	}

void myDiscordListenerClient::autoMudae_init(std::string resethr, std::string resetmin, std::string) {
	this->reset_hr = resethr;
	this->reset_min = resetmin;
}
