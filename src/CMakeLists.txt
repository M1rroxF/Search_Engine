cmake_minimum_required(VERSION 3.21)

####################################
# Project
####################################
set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/test)

add_executable(SearchEngine
        main.cpp

        ConverterJSON.cpp
        ${INCLUDE_DIR}/ConverterJSON.h

        InvertedIndex.cpp
        ${INCLUDE_DIR}/InvertedIndex.h

        SearchServer.cpp
        ${INCLUDE_DIR}/SearchServer.h

        ${GTEST_DIR}/test_InvertedIndex.cpp
        ${GTEST_DIR}/test_SearchServer.cpp
)

####################################
# Libraries
####################################
target_link_libraries(SearchEngine PRIVATE
        nlohmann_json::nlohmann_json
        gtest_main
)
gtest_discover_tests(SearchEngine)


