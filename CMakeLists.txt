cmake_minimum_required(VERSION 3.5)

project(dualshock3_UI_1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Charts REQUIRED)

if(ANDROID)
  add_library(dualshock3_UI_1 SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mywidget.h
    mywidget.cpp
    reader.h
    reader.cpp
    scorewidget.h
    scorewidget.cpp
#    accelerometerwidget.h
#    accelerometerwidget.cpp
  )
else()
  add_executable(dualshock3_UI_1
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mywidget.h
    mywidget.cpp
    reader.h
    reader.cpp
    scorewidget.h
    scorewidget.cpp
#    accelerometerwidget.h
#    accelerometerwidget.cpp
  )
endif()

target_link_libraries(dualshock3_UI_1 PRIVATE Qt5::Widgets)
