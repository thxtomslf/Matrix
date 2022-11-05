project(matrix_test)

set(SOURCES
        FirstPointTests.cpp
        SecondPointTests.cpp
        ThirdPointTest.cpp
        FourthPointTest.cpp
        SixthPointTests.cpp
        SeventhPointTests.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Matrix_lib GTest::gtest_main)

add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)
