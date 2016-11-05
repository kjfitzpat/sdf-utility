# suppose you have created a ui file called mainwindow.ui
cmake_minimum_required (VERSION 2.6)

project(tst)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT5_WRAP_CPP(tst_hdr_moc mainwindow.h)
QT5_WRAP_UI(tst_form_hdr mainwindow.ui)

add_library(mainwindow ${tst_hdr_moc} ${tst_form_hdr})
qt5_use_modules(mainwindow Widgets)

add_executable(tst setting.cpp mainwindow)
qt5_use_modules(tst Core Gui Widgets)