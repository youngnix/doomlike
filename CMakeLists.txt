cmake_minimum_required(VERSION 3.31.0)

project(doomlike
	DESCRIPTION "A DOOM-like OpenGL-based renderer practice"
	VERSION 0.1.0
	LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)
