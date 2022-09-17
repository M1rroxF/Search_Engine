cmake_minimum_required(VERSION 3.21)

####################################
# Project
####################################
project(SearchEngine VERSION 2.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/test)

####################################
# Subdirectory
####################################
add_subdirectory(nlohmann_json)
add_subdirectory(test)
add_subdirectory(src)

####################################
# Project dirs
####################################
target_include_directories(SearchEngine PUBLIC include)
target_include_directories(tests PUBLIC include)