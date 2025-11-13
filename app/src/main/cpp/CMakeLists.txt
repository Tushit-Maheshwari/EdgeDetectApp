cmake_minimum_required(VERSION 3.10)
project(edgedetect LANGUAGES C CXX)

# Use a modern, portable way to request C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Allow overriding OpenCV location via cache variable or environment variable.
# Usage examples:
#  - cmake -DOpenCV_DIR=/path/to/opencv-android-sdk/sdk/native/jni ...
#  - cmake -DOPENCV_ANDROID_SDK=/path/to/opencv-android-sdk ...
#  - export OPENCV_ANDROID_SDK=/path/to/opencv-android-sdk
option(OPENCV_ANDROID_SDK "Path to OpenCV Android SDK (root)" "")

if(OPENCV_ANDROID_SDK)
  set(OpenCV_DIR "${OPENCV_ANDROID_SDK}/sdk/native/jni" CACHE PATH "OpenCV CMake directory")
elseif(NOT DEFINED OpenCV_DIR)
  if(DEFINED ENV{OpenCV_DIR})
    set(OpenCV_DIR $ENV{OpenCV_DIR})
  elseif(DEFINED ENV{OPENCV_ANDROID_SDK})
    set(OpenCV_DIR "$ENV{OPENCV_ANDROID_SDK}/sdk/native/jni")
  elseif(DEFINED ENV{HOME})
    # fall back to common default used on many machines
    set(OpenCV_DIR "$ENV{HOME}/opencv-android-sdk/sdk/native/jni")
  endif()
endif()

if(OpenCV_DIR)
  message(STATUS "Attempting to use OpenCV_DIR = ${OpenCV_DIR}")
  # make sure OpenCV_DIR is a cache variable so users can override it later
  set(OpenCV_DIR "${OpenCV_DIR}" CACHE PATH "" FORCE)
endif()

# Try to find OpenCV (will use OpenCV_DIR if set).
# Request common components - adjust if you need more/less.
find_package(OpenCV REQUIRED COMPONENTS core imgproc)

if(NOT OpenCV_FOUND)
  message(FATAL_ERROR
    "OpenCV not found. Set -DOpenCV_DIR=/path/to/opencv-android-sdk/sdk/native/jni "
    "or -DOPENCV_ANDROID_SDK=/path/to/opencv-android-sdk, or set the OPENCV_ANDROID_SDK "
    "environment variable.")
endif()

message(STATUS "Found OpenCV ${OpenCV_VERSION} (include: ${OpenCV_INCLUDE_DIRS})")

# Create native library
add_library(native-lib SHARED
  native-lib.cpp
  canny_processor.cpp
)

# Prefer modern target-based properties
target_include_directories(native-lib
  PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

# Ensure C++ standard on the target
target_compile_features(native-lib PRIVATE cxx_std_17)

# link against OpenCV and required Android system libs
# On Android the 'log', 'android' and 'jnigraphics' libraries are commonly required.
find_library(log-lib log)
find_library(android-lib android)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(native-lib
  PRIVATE
    ${OpenCV_LIBS}
    ${log-lib}
    ${android-lib}
    ${jnigraphics-lib}
)

message(STATUS "Linked OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "native-lib target configured (C++17, PIC enabled)")
