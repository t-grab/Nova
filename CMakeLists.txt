cmake_minimum_required(VERSION 3.5.1)
project(Nova)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_USE_STATIC_LIBS ON)
set(GLEW_GLEW_STATIC ON)

find_package(BOOST REQUIRED)
find_package(PNG REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

include_directories(include
                    ${BOOST_INCLUDE_DIR}
                    ${GLFW_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}
                    ${GLM_INCLUDE_DIR})

if (WIN32)
    link_directories(${BOOST_LIBRARY_DIR})
endif ()

set(LIB_FILES
    src/nova.cpp
    src/std.cpp
    src/shader.cpp
    src/window.cpp
    src/program.cpp
    src/colour.cpp
    src/points.cpp)

set(EXAMPLE_FILES
    example/main.cpp
    example/read.cpp
    example/prog.cpp)
add_library(nova ${LIB_FILES})
add_executable(example ${EXAMPLE_FILES})
target_link_libraries(example
                      nova
                      libboost_thread-mt.a
                      libboost_system-mt.a
                      ${GLEW_LIBRARY}
                      ${GLFW_LIBRARY}
                      gdi32
                      opengl32)
