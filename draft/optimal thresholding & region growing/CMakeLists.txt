cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR "C:/opencv/minwg-build/install/x64/mingw/lib")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(untitled main.cpp optimal_thresholding.cpp optimal_thresholding.h region_growing.cpp region_growing.h)

target_link_libraries(untitled ${OpenCV_LIBS})
