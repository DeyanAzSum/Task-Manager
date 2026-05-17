cmake_minimum_required(VERSION 3.16)
project(TaskManager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(taskmanager src/main.cpp)
