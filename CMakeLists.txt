cmake_minimum_required(VERSION 3.15)

project(Test VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)

add_executable(claw_game main.cpp)

target_link_libraries(claw_game PUBLIC src)

configure_file(Config.h.in Config.h)

target_include_directories(claw_game PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(claw_game PUBLIC "${PROJECT_BINARY_DIR}/src")

add_subdirectory(src)