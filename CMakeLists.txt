cmake_minimum_required(VERSION 3.5.1)
project(Nova)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include
                    D:/dev/lib/glew/src/include
                    D:/dev/lib/glfw/src/include
                    D:/dev/lib/glm
                    /mingw64/include)
link_directories(D:/dev/lib/glfw/glfw-mingw/src
                 D:/dev/lib/glew/glew-mingw/lib
                 /mingw64/lib)

set(LIB_FILES
    src/shader.cpp
    src/window.cpp)

set(TEST_FILES
    tests/test.cpp)

add_library(nova ${LIB_FILES})

add_executable(example ${TEST_FILES})
target_link_libraries(example
                      nova
                      libboost_thread-mt.a
                      libboost_system-mt.a
                      glew32
                      glfw3
                      gdi32
                      opengl32)