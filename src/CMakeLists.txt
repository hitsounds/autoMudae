add_executable(autoMudae
	Main.cpp
	find_process.cpp
	include/automudae/find_process.h
	get_discordToken.cpp
	include/automudae/discord_hook.h
	chars_file.cpp
	include/automudae/chars_file.h
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
)

SET_TARGET_PROPERTIES(autoMudae PROPERTIES LINK_FLAGS "/level='requireAdministrator' /uiAccess='false'")