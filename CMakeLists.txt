# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define project name
project(face_detector)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

find_package( Boost REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
link_directories(boostbin)

# Declare the executable target built from your sources
add_library(face_detector_lib SHARED library_source/FaceDetector.cpp library_source/FaceDetector.h)
target_link_libraries(face_detector_lib ${OpenCV_LIBS})

ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add test cpp file
add_executable( runUnitTests tests/test.cpp )
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main ${OpenCV_LIBS})
add_test( runUnitTests runUnitTests )


add_executable(face_detector source/main.cpp source/FaceRecogniser.cpp source/FaceRecogniser.h)

# Link your application with OpenCV libraries
target_link_libraries(face_detector ${OpenCV_LIBS})
target_link_libraries(face_detector ${Boost_LIBS})

message(STATUS "    current dir: ${CMAKE_CURRENT_BINARY_DIR}")
