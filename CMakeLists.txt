cmake_minimum_required(VERSION 3.25)
project(ComputerClub LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(
    ComputerClub
    src/main.cpp
    )

target_include_directories(ComputerClub PRIVATE src/utilities src/events src/club)