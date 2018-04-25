cmake_minimum_required(VERSION 3.7)
project(cube_solver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/solve.cpp include/cube_block.h include/cube_corner.h src/cube_block.cpp src/cube_corner.cpp include/cube_data.h src/cube_squares.cpp include/cube_squares.h include/color_operation.h src/color_operation.cpp src/cube_bound.cpp include/cube_bound.h include/file_resolution.h src/file_resolution.cpp include/servo.h src/servo.cpp include/video.h src/video.cpp)
add_executable(cube_solver ${SOURCE_FILES})
find_package(OpenCV REQUIRED)
target_link_libraries(cube_solver ${OpenCV_LIBS})
