cmake_minimum_required(VERSION 3.10.2)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(MatrixProject CXX)

set(DCMAKE_CXX_CLANG_TIDY /usr/bin/clang-tidy-3.9 -checks=*)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Werror -Wall -Wextra")

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Build code coverage" ON)

find_package(GTest CONFIG)
if (NOT GTest_FOUND)
    hunter_add_package(GTest)
endif()
find_package(GTest CONFIG REQUIRED)


if (BUILD_TESTS)
    include(GoogleTest)
    enable_testing()
endif()

add_subdirectory(matrix)
