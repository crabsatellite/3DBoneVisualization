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

find_package(OpenGL REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(VTK_DIR $ENV{VTK_DIR})
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

#######################################################
# Set project specific source files
#######################################################
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
# Image Process Service
#######################################################
        image_process_service/image_processor.h
        image_process_service/image_processor.cpp

#######################################################
# OpenGL Shaders
#######################################################
        render_service/vertex_shader.vsh
        render_service/fragment_shader.fsh

#######################################################
# Project resources
#######################################################
        resources.qrc
)

#######################################################
# Add source files to project executable
#######################################################
add_executable(3DBoneVisualization ${PROJECT_SOURCES})

#######################################################
# Link 3rd party libraries to project executable
#######################################################
target_link_libraries(3DBoneVisualization PRIVATE
  Qt5::OpenGL
  Qt5::Xml
  Qt5::Widgets
  ${QT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${VTK_LIBRARIES}
)

target_include_directories(3DBoneVisualization PRIVATE
  ${VTK_INCLUDE_DIRS}
  ${INCLUDE_DIR}
  ${SOURCE_DIR}
)
