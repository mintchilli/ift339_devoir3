cmake_minimum_required(VERSION 3.9)
project(ift339_devoir3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        map.h
        mapImpl.h
        unordered_set.h
        unordered_setImpl.h)
add_executable(ift339_devoir3 ${SOURCE_FILES})
