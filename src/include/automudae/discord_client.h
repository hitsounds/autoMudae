#pragma once
#include <winsock2.h>
#include "sleepy_discord/websocketpp_websocket.h"
#include <cpr/cpr.h>

class myDiscordListenerClient : public SleepyDiscord::DiscordClient {
	public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	void onMessage(SleepyDiscord::Message message);

};