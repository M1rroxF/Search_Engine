cmake_minimum_required(VERSION 3.21)

####################################
# Project
####################################
add_executable(tests
        main.cpp

        ${SRC_DIR}/ConverterJSON.cpp
        ${INCLUDE_DIR}/ConverterJSON.h

        ${SRC_DIR}/InvertedIndex.cpp
        ${INCLUDE_DIR}/InvertedIndex.h
        test_InvertedIndex.cpp

        ${SRC_DIR}/SearchServer.cpp
        ${INCLUDE_DIR}/SearchServer.h
        test_SearchServer.cpp
)

target_link_libraries(
        tests PRIVATE

        nlohmann_json::nlohmann_json
        gtest_main
        gtest
)

####################################
# GoogleTest
####################################
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(FetchContent)

FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
gtest_discover_tests(tests)