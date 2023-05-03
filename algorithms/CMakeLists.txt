cmake_minimum_required(VERSION 3.25)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR "C:/opencv/minwg-build/install/x64/mingw/lib")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(algorithms main.cpp optimal_thresholding.cpp optimal_thresholding.h region_growing.cpp region_growing.h spectral_thresholding.cpp spectral_thresholding.h agglomerative.cpp agglomerative.h agglomerative.h otsu_thresholding.cpp otsu_thresholding.h kmean.cpp kmean.h)

target_link_libraries(algorithms ${OpenCV_LIBS})
