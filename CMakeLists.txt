cmake_minimum_required(VERSION 4.0)
project(SearchEngineProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(SearchEngineProject
        src/core/Index5.cpp
        src/Main.cpp
        src/core/Index5.h
        src/core/interfaces.h
        src/core/Index6.h
        src/components/stores/BasicHashTable.cpp
)
