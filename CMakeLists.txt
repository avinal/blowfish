cmake_minimum_required(VERSION 3.1)
project(blowfish VERSION 1.0.0 LANGUAGES CXX)


if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
elseif (CMAKE_CXX_STANDARD LESS 11)
    message(WARNING "CMAKE_CXX_STANDARD has been set to '${CMAKE_CXX_STANDARD}' which is lower than the minimum required standard (c++14).")
endif ()

message(STATUS "Using C++ standard c++${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message (STATUS "CMake version: ${CMAKE_VERSION}")
message (STATUS "Project version: ${PROJECT_VERSION}")

set(BLOWFISH_SRC ${PROJECT_SOURCE_DIR}/src/blowfish.cc)
source_group(src FILES ${BLOWFISH_SRC})

set(BLOWFISH_TEST ${PROJECT_SOURCE_DIR}/tests/Main.cpp)
source_group(tests FILES ${BLOWFISH_TEST})

set(BLOWFISH_INC ${PROJECT_SOURCE_DIR}/include/blowfish/blowfish.h)
source_group(include FILES ${BLOWFISH_INC})

set(BLOWFISH_DOC 
    README.md
    LICENSE
)
source_group(doc FILES ${BLOWFISH_DOC})

set(BLOWFISH_SCRIPTS
    .gitattributes
    .gitignore
    build.sh
)
source_group(scripts FILES ${BLOWFISH_SCRIPTS})

add_library(blowfish ${BLOWFISH_SRC} ${BLOWFISH_INC} ${BLOWFISH_SCRIPTS} ${BLOWFISH_DOC})
add_executable(bf_test ${BLOWFISH_TEST} ${BLOWFISH_SRC} ${BLOWFISH_INC} )
target_include_directories(bf_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(blowfish PUBLIC ${PROJECT_SOURCE_DIR}/include)
