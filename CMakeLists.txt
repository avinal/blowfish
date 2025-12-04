cmake_minimum_required(VERSION 3.30)
project(blowfish VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "Project version: ${PROJECT_VERSION}")

# ===== compiler settings =====
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Using C++ standard c++${CMAKE_CXX_STANDARD}")

set(BF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# ===== blowfish library =====
add_library(blowfish)
target_compile_features(blowfish PUBLIC cxx_std_17)

target_sources(blowfish
    PRIVATE
        src/blowfish.cc
    PUBLIC FILE_SET HEADERS
        BASE_DIRS ${BF_INCLUDE_DIR}
        FILES include/blowfish/blowfish.h
)

target_include_directories(blowfish PUBLIC ${BF_INCLUDE_DIR})

# ===== blowfish2 library =====
add_library(blowfish2)
target_compile_features(blowfish2 PUBLIC cxx_std_14)

target_sources(blowfish2
    PRIVATE
        src/blowfish2.cc
    PUBLIC FILE_SET HEADERS
        BASE_DIRS ${BF_INCLUDE_DIR}
        FILES include/blowfish/blowfish2.h
)

target_include_directories(blowfish2 PUBLIC ${BF_INCLUDE_DIR})

# ===== Tests =====
include(CTest)
if(BUILD_TESTING)
    add_executable(bf_test tests/Main.cpp)
    target_link_libraries(bf_test PRIVATE blowfish)
    add_test(NAME bf_test COMMAND bf_test)

    add_executable(bf2_test tests/Main2.cpp)
    target_link_libraries(bf2_test PRIVATE blowfish2)
    add_test(NAME bf2_test COMMAND bf2_test)
endif()
