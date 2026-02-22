cmake_minimum_required(VERSION 4.1)
project(momoDB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# jemalloc
find_package(PkgConfig REQUIRED)
pkg_check_modules(JEMALLOC REQUIRED jemalloc)
include_directories(${JEMALLOC_INCLUDE_DIRS})

add_executable(momoDB main.cpp
        walogger.h
        logentry.h
        walogger.cpp
        keystore.cpp
        keystore.h
        CommandProcessor.cpp
        CommandProcessor.h)

target_link_libraries(momoDB ${JEMALLOC_LIBRARIES})