add_executable(autoMudae
	Main.cpp
	find_process.cpp
	include/automudae/find_process.h
	get_discordToken.cpp
	include/automudae/discord_hook.h
	files.cpp
	include/automudae/files.h
	discord_client.cpp
	include/automudae/discord_client.h
	res/autoMudae.rc
	res/app.ico
)

target_include_directories(autoMudae
	PRIVATE
		include/
)

target_link_libraries(autoMudae
	cpr
	sleepy-discord
	nlohmann_json::nlohmann_json
)

SET_TARGET_PROPERTIES(autoMudae PROPERTIES LINK_FLAGS "/level='requireAdministrator' /uiAccess='false'")