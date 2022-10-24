cmake_minimum_required(VERSION 3.10.2)
project(Matrix CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)

set(HEADERS
        src/include/Matrix.h
        src/include/Vector.h
        src/include/VectorRow.h
        src/include/VectorColumn.h

)

set(SOURCES
        src/cpp/Matrix.cpp
        src/cpp/Vector.cpp
        src/cpp/VectorColumn.cpp
        src/cpp/VectorRow.cpp
)

add_library(Matrix STATIC ${SOURCES} ${HEADERS})

add_subdirectory(test)

