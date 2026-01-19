cmake_minimum_required(VERSION 4.1)
project(momoDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(momoDB main.cpp
        walogger.h
        logentry.h
        walogger.cpp
        keystore.cpp
        keystore.h
        CommandProcessor.cpp
        CommandProcessor.h)
