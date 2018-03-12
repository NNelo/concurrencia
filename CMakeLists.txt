cmake_minimum_required(VERSION 3.6.3)
project(Concurrency)

set(CMAKE_CXX_STANDARD 11)




add_executable(Concurrency main.cpp timer.h)
TARGET_LINK_LIBRARIES( Concurrency pthread)