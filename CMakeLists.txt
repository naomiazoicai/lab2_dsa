cmake_minimum_required(VERSION 3.24)
project(lab2_dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab2_dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        PriorityQueue.cpp
        PriorityQueue.h
        ShortTest.cpp
        ShortTest.h)
