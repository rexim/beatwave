include_directories(.)

add_executable(testset core/testset.cpp)
add_executable(testanimated core/testanimated.cpp)

add_test(NAME testset COMMAND testset)
add_test(NAME testanimated COMMAND testanimated)
