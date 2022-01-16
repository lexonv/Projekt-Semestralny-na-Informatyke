cmake_minimum_required(VERSION 3.20)
project(Projekt_Semestralny_na_Informatyke)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp klasy.hpp)
add_executable(Projekt_Semestralny_na_Informatyke ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Projekt_Semestralny_na_Informatyke sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
