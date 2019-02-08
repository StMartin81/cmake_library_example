cmake_minimum_required(VERSION 3.1)

option(BUILD_TEST_EXECUTABLE "Build the test executable" OFF)

add_subdirectory(lib)
if(BUILD_TEST_EXECUTABLE)
    add_subdirectory(test)
endif()
