cmake_minimum_required(VERSION 3.5)

project(task4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "C:/opencv/minwg-build/install/x64/mingw/lib")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        algorithms/optimal_thresholding.h
        algorithms/optimal_thresholding.cpp
        algorithms/spectral_thresholding.h
        algorithms/spectral_thresholding.cpp
        algorithms/region_growing.h
        algorithms/region_growing.cpp
        algorithms/otsu_thresholding.h
        algorithms/otsu_thresholding.cpp
        algorithms/agglomerative.h
        algorithms/agglomerative.cpp
        algorithms/kmean.h
        algorithms/kmean.cpp
        algorithms/mean_shift.h
        algorithms/mean_shift.cpp
        algorithms/local_thresholding.cpp
        algorithms/local_thresholding.h

        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(task4
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET task4 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(task4 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(task4
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(task4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})


set_target_properties(task4 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


install(TARGETS task4
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(task4)
endif()
