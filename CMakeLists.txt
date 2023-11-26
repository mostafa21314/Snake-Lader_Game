cmake_minimum_required(VERSION 3.26)
project(Snake_and_Ladder)

set(CMAKE_CXX_STANDARD 17)

add_executable(Snake_and_Ladder main.cpp
        Board.cpp
        Board.h
        Dice.cpp
        Dice.h
        Players.cpp
        Players.h
)
