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

#set(ITK_DIR ./itk/bin)
#find_package(ITK REQUIRED)
#include_directories (${ITK_USE_FILE})
#include_directories(${ITK_INCLUDE_DIRS})

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
# Add 3rd party libraries
#######################################################
#add_library(itkdouble-conversion)
#add_library(itksys)
#add_library(itkvnl_algo)
#add_library(itkvnl)
#add_library(itkv3p_netlib)
#add_library(itkvcl)
#add_library(ITKCommon)
#add_library(itkNetlibSlatec)
#add_library(ITKStatistics)
#add_library(ITKTransform)
#add_library(ITKMesh)
#add_library(zlib)
#add_library(ITKMetaIO)
#add_library(ITKSpatialObjects)
#add_library(ITKPath)
#add_library(ITKLabelMap)
#add_library(ITKMathematicalMorphology)
#add_library(ITKQuadEdgeMesh)
#add_library(ITKFastMarching)
#add_library(ITKIOImageBase)
#add_library(ITKFFT)
#add_library(ITKConvolution)
#add_library(ITKSmoothing)
#add_library(ITKImageFeature)
#add_library(ITKOptimizers)
#add_library(ITKPolynomials)
#add_library(ITKBiasCorrection)
#add_library(ITKColormap)
#add_library(ITKDICOMParser)
#add_library(ITKDeformableMesh)
#add_library(ITKDenoising)
#add_library(ITKDiffusionTensorImage)
#add_library(ITKEXPAT)
#add_library(gdcmDICT)
#add_library(gdcmMSFF)
#add_library(ITKznz)
#add_library(ITKniftiio)
#add_library(ITKgiftiio)
#add_library(ITKPDEDeformableRegistration)
#add_library(hdf5_cpp-static)
#add_library(hdf5-static)
#add_library(hdf5_hl-static)
#add_library(ITKIOBMP)
#add_library(ITKIOBioRad)
#add_library(ITKIOBruker)
#add_library(ITKIOCSV)
#add_library(ITKIOGDCM)
#add_library(ITKIOIPL)
#add_library(ITKIOGE)
#add_library(ITKIOGIPL)
#add_library(ITKIOHDF5)
#add_library(itkjpeg)
#add_library(ITKIOJPEG)
#add_library(itkopenjpeg)
#add_library(ITKIOJPEG2000)
#add_library(itktiff)
#add_library(ITKIOTIFF)
#add_library(ITKIOLSM)
#add_library(itkminc2)
#add_library(ITKIOMINC)
#add_library(ITKIOMRC)
#add_library(ITKIOMeshBase)
#add_library(ITKIOMeshBYU)
#add_library(ITKIOMeshFreeSurfer)
#add_library(ITKIOMeshGifti)
#add_library(ITKIOMeshOBJ)
#add_library(ITKIOMeshOFF)
#add_library(ITKIOMeshVTK)
#add_library(ITKIOMeta)
#add_library(ITKIONIFTI)
#add_library(ITKNrrdIO)
#add_library(ITKIONRRD)
#add_library(itkpng)
#add_library(ITKIOPNG)
#add_library(ITKIOSiemens)
#add_library(ITKIOXML)
#add_library(ITKIOSpatialObjects)
#add_library(ITKIOStimulate)
#add_library(ITKTransformFactory)
#add_library(ITKIOTransformBase)
#add_library(ITKIOTransformHDF5)
#add_library(ITKIOTransformInsightLegacy)
#add_library(ITKIOTransformMatlab)
#add_library(ITKIOVTK)
#add_library(ITKKLMRegionGrowing)
#add_library(itklbfgs)
#add_library(ITKMarkovRandomFieldsClassifiers)
#add_library(ITKOptimizersv4)
#add_library(ITKQuadEdgeMeshFiltering)
#add_library(ITKRegionGrowing)
#add_library(ITKRegistrationMethodsv4)
#add_library(ITKTestKernel)
#add_library(ITKVTK)
#add_library(ITKVideoCore)
#add_library(ITKVideoIO)
#add_library(ITKWatersheds)


#######################################################
# Link 3rd party libraries to project executable
#######################################################
target_link_libraries(3DBoneVisualization PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OPENGL_LIBRARIES})
