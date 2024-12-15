cmake_minimum_required(VERSION 3.29.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)

project(doomlike
	DESCRIPTION "A DOOM-like OpenGL-based renderer practice"
	VERSION 0.1.0
	LANGUAGES CXX)

add_subdirectory(vendor/SFML/)

add_executable(${PROJECT_NAME} src/main.cpp src/player.cpp src/kinematics.cpp src/tiles.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE vendor/SFML/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
