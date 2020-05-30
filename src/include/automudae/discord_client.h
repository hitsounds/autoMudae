#pragma once
#include <winsock2.h>
#include "sleepy_discord/websocketpp_websocket.h"
#include "nlohmann/json.hpp"
#include <cpr/cpr.h>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_set>

class myDiscordListenerClient : public SleepyDiscord::DiscordClient {
	public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	int reset_min;
	int reset_hr_offset;
	nlohmann::json conf;
	time_t lock;
	time_t now;
	std::unordered_set<std::string> chars;
	std::unordered_set<std::string> interesting_msgs_id;
	std::string username;

	void onMessage(SleepyDiscord::Message msg);

	void onReaction(SleepyDiscord::Snowflake<SleepyDiscord::User> userID, SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, SleepyDiscord::Emoji emoji);

	void onError(SleepyDiscord::ErrorCode errorCode, std::string errorMessage);

	void autoMudae_init(int resethr, int resetmin, nlohmann::json config, std::unordered_set<std::string> chars);

};