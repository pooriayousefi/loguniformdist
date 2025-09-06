cmake_minimum_required(VERSION 3.20)
project(loguniformdist VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

# Create header from source
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/loguniformdist/src.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/loguniformdist.hpp
    COPYONLY
)

# Header-only library target
add_library(loguniformdist INTERFACE)
add_library(loguniformdist::loguniformdist ALIAS loguniformdist)

target_include_directories(loguniformdist
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(loguniformdist INTERFACE cxx_std_20)

# Example executable
add_executable(loguniformdist_example ${CMAKE_CURRENT_SOURCE_DIR}/loguniformdist/src.cpp)
target_link_libraries(loguniformdist_example PRIVATE loguniformdist::loguniformdist)

# Install rules
include(GNUInstallDirs)

install(TARGETS loguniformdist
        EXPORT loguniformdistTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/loguniformdist.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT loguniformdistTargets
        FILE loguniformdistTargets.cmake
        NAMESPACE loguniformdist::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/loguniformdist)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    loguniformdistConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/loguniformdistConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/loguniformdistConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/loguniformdist
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/loguniformdistConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/loguniformdistConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/loguniformdist
)
