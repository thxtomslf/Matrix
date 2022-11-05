project(Matrix)


set(HEADERS
        include/Matrix.h
        include/Vector.h)

set(SOURCES
        src/Matrix.cpp
        src/Vector.cpp)


add_library(${PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME} ${HEADERS} ./src/main.cpp )


target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()