cmake_minimum_required(VERSION 2.6)
project(beatwave)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -pedantic")
endif()

set(HPPS
  animated.hpp
  animation.hpp
  lineartransition.hpp
  player.hpp
)

set(CPPS
  main.cpp
)

add_executable(beatwave ${CPPS} ${HPPS})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(beatwave ${SFML_LIBRARIES})
endif()
