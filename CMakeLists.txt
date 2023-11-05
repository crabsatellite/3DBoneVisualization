#######################################################
# Define CMake version
#######################################################
cmake_minimum_required(VERSION 3.5)

#######################################################
# Define project name
#######################################################
project(3DBoneVisualization VERSION 0.1 LANGUAGES CXX)

#######################################################
# Set CMake specific configurations
#######################################################
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#######################################################
# Find 3rd party libraries
#######################################################
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(OpenGL REQUIRED)

#######################################################
# Set project specific source files
#######################################################
set(TS_FILES 3DBoneVisualization_en_US.ts)
set(PROJECT_SOURCES

#######################################################
# Main
#######################################################
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

#######################################################
# GUI Service
#######################################################
        gui_service/toolbar.h
        gui_service/toolbar.cpp
        gui_service/view.h
        gui_service/view.cpp
        gui_service/controlpanel.h
        gui_service/controlpanel.cpp

#######################################################
# Render Service
#######################################################
        render_service/renderproxy.h
        render_service/renderproxy.cpp
        render_service/camera.h
        render_service/camera.cpp

#######################################################
# Event Handle Service
#######################################################
        event_handle_service/eventhandler.h
        event_handle_service/eventhandler.cpp

#######################################################
# OpenGL Shaders
#######################################################
        render_service/vertex_shader.vsh
        render_service/fragment_shader.fsh

#######################################################
# Project resources
#######################################################
        resources.qrc
        ${TS_FILES}
)

#######################################################
# Add source files to project executable
#######################################################
add_executable(3DBoneVisualization ${PROJECT_SOURCES})

#######################################################
# 3rd party libraries header includes
#######################################################
#include_directories( ${OPENGL_INCLUDE_DIRS} )

#######################################################
# Link 3rd party libraries to project executable
#######################################################
target_link_libraries(3DBoneVisualization PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OPENGL_LIBRARIES})
