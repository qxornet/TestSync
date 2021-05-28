cmake_minimum_required(VERSION 3.5)

project(TestSync LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestSync main.cpp sync.cpp sync.hpp)
