cmake_minimum_required(VERSION 2.6)
project(beatwave)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(src/)

set(CORE_SOURCES
  src/core/tunnel.cpp
  src/core/captures.cpp
  src/core/util.cpp
)

add_library(core STATIC ${CORE_SOURCES})

set(BEATWAVE_SOURCES
  src/beatwave/main.cpp
  src/beatwave/game.cpp
  src/beatwave/player.cpp
)

add_executable(beatwave ${BEATWAVE_SOURCES})

set(TUNNELGENERATOR_SOURCES
  src/tunnelgenerator/main.cpp
)
add_executable(tunnelgenerator ${TUNNELGENERATOR_SOURCES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(beatwave ${SFML_LIBRARIES} core)
  target_link_libraries(tunnelgenerator core)
endif()
