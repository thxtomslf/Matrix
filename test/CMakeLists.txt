cmake_minimum_required(VERSION 3.10.2)

set(This MatrixTests)

set(SOURCES
        FirstPointTests.cpp
        SecondPointTests.cpp
        ThirdPointTest.cpp
        FourthPointTest.cpp
        SixthPointTests.cpp
        SeventhPointTests.cpp)

add_executable(${This} ${SOURCES})
target_link_libraries(MatrixTests PUBLIC
    gtest_main Matrix
)

add_test(
        NAME ${This}
        COMMAND ${This}
)