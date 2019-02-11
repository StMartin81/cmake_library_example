cmake_minimum_required(VERSION 3.1)

project(cppLibrary)
set(NAMESPACE_NAME "CppLibrary")

option(BUILD_SHARED_LIBS "Build the shared library" ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

set(CPP_LIBRARY_VERSION_MAJOR 0)
set(CPP_LIBRARY_VERSION_MINOR 1)
set(CPP_LIBRARY_VERSION_PATCH 0)
set(CPP_LIBRARY_VERSION_STRING ${CPP_LIBRARY_VERSION_MAJOR}.${CPP_LIBRARY_VERSION_MINOR}.${CPP_LIBRARY_VERSION_PATCH})

add_library(${PROJECT_NAME})
add_library(${NAMESPACE_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME ${PROJECT_NAME}/${PROJECT_NAME}_export.h
    )
set(public_header_files
    include/cppLibrary/library_wrapper.h
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}_export.h
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION ${CPP_LIBRARY_VERSION_STRING}
    SOVERSION ${CPP_LIBRARY_VERSION_MAJOR}
    PUBLIC_HEADER "${public_header_files}"
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )
target_sources(${PROJECT_NAME}
    PRIVATE
        src/library_wrapper.cpp
        src/library.h
        src/library.cpp
    )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

# adjust this path depending where cmake searches for the target files
set(ConfigPackageLocation "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  COMPONENT Library # This is for Windows
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} COMPONENT Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

install(EXPORT ${PROJECT_NAME}Targets
  FILE
    ${PROJECT_NAME}Targets.cmake
  NAMESPACE
    ${NAMESPACE_NAME}::
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Development
)

configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in
    ${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION "${ConfigPackageLocation}"
    PATH_VARS CMAKE_INSTALL_PREFIX
    )

write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${CPP_LIBRARY_VERSION_STRING}
    COMPATIBILITY AnyNewerVersion
    )

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Development
)
