cmake_minimum_required(VERSION 3.29.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build Type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(doomlike
    DESCRIPTION "A DOOM-like OpenGL-based renderer practice"
    VERSION 0.1.0
    LANGUAGES CXX)

# Copy resource directory
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
)

# Add SDL3
add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)

# Add exe and source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/player.cpp
    src/kinematics.cpp
    src/tiles.cpp
    src/raycast.cpp
    src/input.cpp
    src/graphics.cpp
)

# Add directories and libs
target_include_directories(${PROJECT_NAME} PRIVATE vendor/SDL3/include)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Config to Windows Compatibility
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)
endif()

# Copy directories and resources after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
