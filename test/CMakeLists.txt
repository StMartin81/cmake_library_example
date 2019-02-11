cmake_minimum_required(VERSION 3.1)

project(testCppLibrary)

add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )
target_sources(${PROJECT_NAME}
    PRIVATE
        src/testCppLibrary.cpp
    )
target_link_libraries(${PROJECT_NAME}
    PRIVATE CppLibrary::cppLibrary
    )