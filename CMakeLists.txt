cmake_minimum_required(VERSION 3.7.0)
project(autoMudae)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

option(BUILD_SHARED_LIBS "Build libraries as dlls" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)
option(BUILD_TESTING "Build tests" OFF)

# Options for curl build
option(CURL_STATICLIB "Set to ON to build libcurl with static linking." ON)
add_compile_definitions(CURL_STATICLIB)
option(BUILD_CURL_EXE "Set to ON to build curl executable." OFF)
IF (WIN32)
	option(CMAKE_USE_WINSSL "enable OPEN SSL/TLS" ON)
ENDIF ()

#Options for cpr build
option(BUILD_CPR_TESTS "Set to ON to build cpr tests." OFF)

#Options for json build
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory("deps/nlohmannjson")

add_subdirectory("deps/sleepydiscord/")

add_subdirectory("src/")
