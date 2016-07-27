cmake_minimum_required(VERSION 2.6)
project(beatwave)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic")

set(HPPS
  animated.hpp
  animation.hpp
  lineartransition.hpp
  player.hpp
  tunnel.hpp
  captures.hpp
  game.hpp
  util.hpp
)

set(CPPS
  main.cpp
  tunnel.cpp
  captures.cpp
  game.cpp
  util.cpp
)

add_executable(beatwave ${CPPS} ${HPPS})
add_executable(tunnelgenerator tunnel.hpp tunnel.cpp captures.hpp captures.cpp tunnelgenerator.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(beatwave ${SFML_LIBRARIES})
endif()
