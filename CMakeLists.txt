cmake_minimum_required(VERSION 2.6)
project(beatwave)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(src/)

set(HPPS
  src/animated.hpp
  src/animation.hpp
  src/lineartransition.hpp
  src/player.hpp
  src/tunnel.hpp
  src/captures.hpp
  src/game.hpp
  src/util.hpp
)

set(CPPS
  src/main.cpp
  src/tunnel.cpp
  src/captures.cpp
  src/game.cpp
  src/util.cpp
)

add_executable(beatwave ${CPPS} ${HPPS})
add_executable(tunnelgenerator 
  src/tunnel.hpp
  src/tunnel.cpp
  src/captures.hpp
  src/captures.cpp
  src/tunnelgenerator.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(beatwave ${SFML_LIBRARIES})
endif()
