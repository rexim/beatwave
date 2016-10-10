include_directories(.)
add_executable(testset core/testset.cpp)
add_test(NAME testset COMMAND testset)
