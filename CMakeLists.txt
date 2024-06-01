cmake_minimum_required(VERSION 3.26)
project(CSFinal)

set(CMAKE_CXX_STANDARD 17)

add_executable(CSFinal main.cpp
        MonsterClass.cpp
        MonsterClass.hpp
        RandomGeneration.cpp
        RandomGeneration.hpp
)
