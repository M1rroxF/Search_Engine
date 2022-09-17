cmake_minimum_required(VERSION 3.21)

add_executable(SearchEngine
        main.cpp

        ConverterJSON.cpp
        ${INCLUDE_DIR}/ConverterJSON.h

        InvertedIndex.cpp
        ${INCLUDE_DIR}/InvertedIndex.h

        SearchServer.cpp
        ${INCLUDE_DIR}/SearchServer.h
)

####################################
# Target link libraries
####################################
target_link_libraries(
        SearchEngine PRIVATE

        nlohmann_json::nlohmann_json
)


