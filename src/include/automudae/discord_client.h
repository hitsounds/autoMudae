#pragma once
#include <winsock2.h>
#include "sleepy_discord/websocketpp_websocket.h"
#include <cpr/cpr.h>
#include <string>

class myDiscordListenerClient : public SleepyDiscord::DiscordClient {
	public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	std::string reset_min;
	std::string reset_hr;


	void autoMudae_init(std::string resethr, std::string resetmin);
	void onMessage(SleepyDiscord::Message message);

};