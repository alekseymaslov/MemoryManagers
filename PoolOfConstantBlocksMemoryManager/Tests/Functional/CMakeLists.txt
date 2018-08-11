cmake_minimum_required(VERSION 2.6)

project(Functional)

include_directories( ${CMAKE_SOURCE_DIR}/includes )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(BUILD_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_executable(Functional functional.cpp)

target_link_libraries(Functional ${BUILD_DIRECTORY}/libmemorymanagersforconstblock.a)

install(TARGETS Functional RUNTIME DESTINATION bin)
