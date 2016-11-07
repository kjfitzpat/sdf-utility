# suppose you have created a ui file called MainWindow.ui
cmake_minimum_required (VERSION 2.6)

project(sdf_utility)

set (CMAKE_PREFIX_PATH "C:\\Qt\\5.7\\msvc2015_64")

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT5_WRAP_CPP(MainWindow_header MainWindow.h)
QT5_WRAP_UI(MainWindow_form MainWindow.ui)

add_library(MainWindow ${MainWindow_header} ${MainWindow_form})
qt5_use_modules(MainWindow Widgets)

add_executable(sdf_utility Main.cpp MainWindow.cpp MainWindow.h SdfGeneratorWidget.cpp SdfGeneratorWidget.h)
qt5_use_modules(sdf_utility Core Gui Widgets OpenGL)