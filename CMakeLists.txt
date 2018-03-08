cmake_minimum_required(VERSION 3.7)
project(cube_solver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES solve.cpp cube_block.h cube_corner.h cube_block.cpp cube_corner.cpp cube_data.h cube_squares.cpp cube_squares.h color_operation.h color_operation.cpp cube_bound.cpp cube_bound.h)
add_executable(cube_solver ${SOURCE_FILES})
find_package(OpenCV REQUIRED)
target_link_libraries(cube_solver ${OpenCV_LIBS})
