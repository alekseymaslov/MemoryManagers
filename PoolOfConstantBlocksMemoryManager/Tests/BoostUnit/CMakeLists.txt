cmake_minimum_required(VERSION 2.6)

project(BoostUnit)

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

include_directories( ${CMAKE_SOURCE_DIR}/includes )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(Boost_USE_STATIC_LIBS        ON)

set(BUILD_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

find_package(Boost 1.58.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(BoostUnit BoostUnit.cpp)
  target_link_libraries(BoostUnit ${BUILD_DIRECTORY}/libmemorymanagersforconstblock.a ${Boost_LIBRARIES})
endif()

install(TARGETS BoostUnit RUNTIME DESTINATION bin)