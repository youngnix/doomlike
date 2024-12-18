cmake_minimum_required(VERSION 3.29.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

project(doomlike
	DESCRIPTION "A DOOM-like OpenGL-based renderer practice"
	VERSION 0.1.0
	LANGUAGES CXX)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/player.cpp src/kinematics.cpp src/tiles.cpp src/raycast.cpp src/input.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE vendor/SDL2/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2)
