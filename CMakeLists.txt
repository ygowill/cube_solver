cmake_minimum_required(VERSION 3.7)
project(cube_solver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(cube_solver ${SOURCE_FILES})
find_package(OpenCV REQUIRED)
target_link_libraries(cube_solver ${OpenCV_LIBS})
