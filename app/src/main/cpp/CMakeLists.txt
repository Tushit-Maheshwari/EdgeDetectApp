cmake_minimum_required(VERSION 3.22.1)
project("edgedetect")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "$ENV{HOME}/opencv-android-sdk/sdk/native/jni")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(native-lib SHARED native-lib.cpp canny_processor.cpp)
target_link_libraries(native-lib ${OpenCV_LIBS} android log jnigraphics)

message(STATUS "OpenCV: ${OpenCV_VERSION}")
