cmake_minimum_required(VERSION 3.5)

project(test2 LANGUAGES CXX)
find_package(Threads REQUIRED)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test2 main.cpp)
