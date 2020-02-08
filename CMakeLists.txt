cmake_minimum_required (VERSION 2.8)
project (core-SF2CS-interface)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -g -o2")


if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DGTEST_USE_OWN_TR1_TUPLE=1")
endif (CMAKE_SYSTEM_NAME MATCHES "Darwin")

add_definitions(${CMAKE_CXX_FLAGS_RELEASE})

set(SF2CS_INCLUDE_DIR  ${PROJECT_SOURCE_DIR}/include)
set(SEETAFACE2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/seeta)

include_directories(${SF2CS_INCLUDE_DIR})
include_directories(${SEETAFACE2_INCLUDE_DIR})


set(SEETAFACE2_LIB_DIR ${PROJECT_SOURCE_DIR}/lib/linux/x64)
link_directories(${SEETAFACE2_LIB_DIR})

add_library(SF2CS-Interface  SHARED include/interface.h src/interface.cpp)

target_link_libraries(SF2CS-Interface
        -lSeetaFaceDetector
        -lSeetaFaceRecognizer
        -lSeetaFaceLandmarker
        -lSeetaFaceTracker
        -lSeetaNet
        -lSeetaQualityAssessor)
target_link_libraries(SF2CS-Interface -lstdc++)

add_subdirectory(test)

