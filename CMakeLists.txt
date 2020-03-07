cmake_minimum_required(VERSION 3.10)
project(memcachedbase)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

add_executable(test_getTimeofday test_getTimeofday.cpp)