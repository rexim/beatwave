cmake_minimum_required(VERSION 2.6)
project(beatwave)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(src/)

set(HPPS
  src/core/animated.hpp
  src/core/animation.hpp
  src/core/lineartransition.hpp
  src/core/player.hpp
  src/core/tunnel.hpp
  src/core/captures.hpp
  src/beatwave/game.hpp
  src/core/util.hpp
)

set(CPPS
  src/beatwave/main.cpp
  src/core/tunnel.cpp
  src/core/captures.cpp
  src/beatwave/game.cpp
  src/core/util.cpp
)

add_executable(beatwave ${CPPS} ${HPPS})
add_executable(tunnelgenerator 
  src/core/tunnel.hpp
  src/core/tunnel.cpp
  src/core/captures.hpp
  src/core/captures.cpp
  src/tunnelgenerator/main.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(beatwave ${SFML_LIBRARIES})
endif()
