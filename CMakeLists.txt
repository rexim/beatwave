cmake_minimum_required(VERSION 2.6)
project(beatwave)

add_executable(beatwave main.cpp state.hpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(beatwave ${SFML_LIBRARIES})
endif()
