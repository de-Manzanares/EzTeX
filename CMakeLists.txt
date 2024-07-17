cmake_minimum_required(VERSION 3.28)
project(EzTeX)

set(CMAKE_CXX_STANDARD 23)

add_executable(eztex
        src/main.cpp
        src/Token.cpp
        src/Lexer.cpp)
target_include_directories(eztex PRIVATE include)
