# Project information
cmake_minimum_required(VERSION 3.15)
project(qhm LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ccache
find_program(CCACHE "ccache")
if(CCACHE)
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif(CCACHE)

# Binary dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/bin)

# X11
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

# SFML
option(SFML_BUILD_EXAMPLES "SFML examples" OFF)
option(SFML_BUILD_DOC "SFML doc" OFF)
option(SFML_BUILD_AUDIO "SFML audio" OFF)
option(SFML_BUILD_NETWORK "SFML network" OFF)
add_subdirectory(SFML)

# Add library
add_subdirectory(qhm)

# Add demo
add_subdirectory(demo)
