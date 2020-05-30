#include "automudae/discord_client.h"
#include "sleepy_discord/websocketpp_websocket.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <ctime>
#include <cstdlib>


void myDiscordListenerClient::onMessage(SleepyDiscord::Message msg) {
		if (this->username.size() == 0) {
			SleepyDiscord::User tmp_user = this->getCurrentUser();
			this->username = tmp_user.username;
		}
		time(&(this->now));
		//Lock engaged? Don't Care about the msg then
		if (difftime(this->lock, this->now) > 0) {
			return;
		}
		//Oh so you want a specific channel
		if (this->conf["optional_channel_id"] != "" && this->conf["optional_channel_id"] != msg.channelID.string()) {
			return;
		}
		//I really only care about what mudae is saything tho
		if (msg.author.ID.string() != this->conf["muda_id"]) {
			return;
		}
		//Different server? Who cares!
		if (msg.serverID.string() != this->conf["server_id"]) {
			return;
		}
		//Check for if marry notification and adjust locking mechanism
		if (msg.content.rfind("💖 **" + this->username, 0) == 0) {
			std::cout << "Marraige detected. Setting lock...\n";
			 //3 hrs each packed full with 60 min bringing 60 secs along with them
			struct tm* timeButAfterIAddTheTimeInterval = gmtime(&(this->now));

			timeButAfterIAddTheTimeInterval->tm_sec = 0;
			timeButAfterIAddTheTimeInterval->tm_min = this->reset_min;
			timeButAfterIAddTheTimeInterval->tm_hour = 3 * (timeButAfterIAddTheTimeInterval->tm_hour / 3);
			this->lock = mktime(timeButAfterIAddTheTimeInterval);
			std::cout << "Lock ENGAGED: " << lock << "\n";
			return;

			/*timeButAfterIAddTheTimeInterval->tm_sec = 0;
			if (timeButAfterIAddTheTimeInterval->tm_hour % 3 == this->reset_hr_offset && timeButAfterIAddTheTimeInterval->tm_min < this->reset_min) {
				timeButAfterIAddTheTimeInterval->tm_min = this->reset_min;
				this->lock = mktime(timeButAfterIAddTheTimeInterval);
				std::cout << "Lock ENGAGED: " << this->lock << "\n";
				return;
			}
			this->now += 3 * 60 * 60;
			timeButAfterIAddTheTimeInterval = localtime(&(this->now));
			timeButAfterIAddTheTimeInterval->tm_sec = 0;
			timeButAfterIAddTheTimeInterval->tm_hour = 3*(timeButAfterIAddTheTimeInterval->tm_hour / 3);
			timeButAfterIAddTheTimeInterval->tm_min = this->reset_min;
			this->lock = mktime(timeButAfterIAddTheTimeInterval);
			this->lock += this->reset_hr_offset * 60 * 60;
			std::cout << "Lock ENGAGED: " << this->lock << "\n";
			return;
/*			int modOfTime = timeButAfterIAddTheTimeInterval->tm_hour % 3;
			int adjustment;
			//Special Case applies when mod of time is 0
			if (modOfTime == 0) {
				adjustment = std::abs(3 - this->reset_hr_offset);
			}
			else {
				adjustment = std::abs(modOfTime - this->reset_hr_offset);
			}
			timeButAfterIAddTheTimeInterval->tm_sec = 0;
			int original_min = timeButAfterIAddTheTimeInterval->tm_min;
			timeButAfterIAddTheTimeInterval->tm_min = this->reset_min;
			time_t temp = mktime(timeButAfterIAddTheTimeInterval);
			temp -= adjustment * 60 * 60;
			if (adjustment == 0 && original_min >= this->reset_min) {
				temp += 3 * 60 * 60;
			}
			lock = temp;
			std::cout << "Lock ENGAGED: " << lock << "\n";
			return;
*/
		}
		//Actual Claiming Logic : seems pretty legit
		if (msg.embeds.empty()) {
			return;
		}
		std::cout << msg.embeds[0].author.name << "\n";
		if (this->chars.find(msg.embeds[0].author.name) != this->chars.end() && msg.embeds[0].footer.empty()) {
			this->interesting_msgs_id.insert(msg.ID.string());
		}
}


void myDiscordListenerClient::onReaction(SleepyDiscord::Snowflake<SleepyDiscord::User> userID, SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, SleepyDiscord::Emoji emoji) {
	if (this->interesting_msgs_id.find(messageID.string()) != this->interesting_msgs_id.end() && userID.string() == this->conf["muda_id"]) {
		this->interesting_msgs_id.erase(messageID.string());
		std::cout << "interesting size: " << this->interesting_msgs_id.size() << "\n";
		std::ostringstream per_enc;
		for (int i = 0; i < emoji.name.length(); ++i) {
			per_enc << '%' << std::hex << std::uppercase << (int)(unsigned char)emoji.name[i];
		}
		this->addReaction(channelID, messageID, per_enc.str());
	}
}

void myDiscordListenerClient::onError(SleepyDiscord::ErrorCode errorCode, std::string errorMessage) {
	#ifdef _DEBUG
		std::cout << errorMessage << "\n";
	#endif
	return;
}

void myDiscordListenerClient::autoMudae_init(int resethr, int resetmin, nlohmann::json config, std::unordered_set<std::string> chars) {
	this->conf = config;
	this->reset_hr_offset = resethr % 3; 
	this->reset_min = resetmin;
	this->chars = chars;
	this->interesting_msgs_id = {};
	std::cout << "autoMudae Initalised!\n";
	
	//So i just kinda set the lock to current time to begin with
	time(&(this->lock));
	
}
