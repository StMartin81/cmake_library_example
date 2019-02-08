cmake_minimum_required(VERSION 3.1)

project(testCppLibrary)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        src/testCppLibrary.cpp
    )
target_link_libraries(${PROJECT_NAME}
    PRIVATE CppLibrary::cppLibrary
    )
