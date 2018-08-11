cmake_minimum_required(VERSION 2.6)
project(poolofconstantblocksmemorymanager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories( includes/ )

file(GLOB CLASSES_SRC
    sources/*.cpp
)

add_library(memorymanagersforconstblock STATIC ${CLASSES_SRC})

add_subdirectory(Tests)