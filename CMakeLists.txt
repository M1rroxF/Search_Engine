cmake_minimum_required(VERSION 3.21)

####################################
# Project
####################################
project(SearchEngine)
enable_testing()

####################################
# Subdirectory
####################################
add_subdirectory(nlohmann_json)
add_subdirectory(test)
add_subdirectory(src)
