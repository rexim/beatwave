include_directories(.)

add_executable(testset core/testset.cpp)
add_executable(testanimated core/testanimated.cpp)
add_executable(testseqcombinator core/testseqcombinator.cpp)
add_executable(testfloatcolor core/testfloatcolor.cpp)
add_executable(testmap core/testmap.cpp)
add_executable(testnil core/testnil.cpp)
add_executable(testforever core/testforever.cpp)
add_executable(testrepeat core/testrepeat.cpp)
add_executable(testsleep core/testsleep.cpp)
add_executable(testplayer 
  beatwave/testplayer.cpp
  ../src/beatwave/player.cpp
  ../src/beatwave/splat.cpp
  ../src/beatwave/drop.cpp
  ../src/beatwave/filledcircle.cpp
)

add_test(NAME testset COMMAND testset)
add_test(NAME testanimated COMMAND testanimated)
add_test(NAME testseqcombinator COMMAND testseqcombinator)
add_test(NAME testfloatcolor COMMAND testfloatcolor)
add_test(NAME testmap COMMAND testmap)
add_test(NAME testnil COMMAND testnil)
add_test(NAME testforever COMMAND testforever)
add_test(NAME testrepeat COMMAND testrepeat)
add_test(NAME testsleep COMMAND testsleep)
add_test(NAME testplayer COMMAND testplayer)

target_link_libraries(testfloatcolor ${SFML_LIBRARIES} core)
target_link_libraries(testplayer ${SFML_LIBRARIES} core)
