cmake_minimum_required (VERSION 2.8)
project (core-SF2CS-interface)

aux_source_directory(core CORE_SRC)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -g -o2")


if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DGTEST_USE_OWN_TR1_TUPLE=1")
endif (CMAKE_SYSTEM_NAME MATCHES "Darwin")

add_definitions(${CMAKE_CXX_FLAGS_RELEASE})

set(SF2CS_INCLUDE_DIR  ${PROJECT_SOURCE_DIR}/include)
set(SEETAFACE2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/core/seeta)
set(SF2CS_CORE_DIR ${PROJECT_SOURCE_DIR}/core)

include_directories(${SF2CS_INCLUDE_DIR})
include_directories(${SEETAFACE2_INCLUDE_DIR})
include_directories(${SF2CS_CORE_DIR})


set(SEETAFACE2_LIB_DIR ${PROJECT_SOURCE_DIR}/lib/linux/x64)

set(JDK_INCLUDE_DIR /usr/lib/jvm/java-11-openjdk/include)
include_directories(${JDK_INCLUDE_DIR})
include_directories(${JDK_INCLUDE_DIR}/linux)
link_directories(${SEETAFACE2_LIB_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(./src SRC_LIST)
add_library(SF2CS-Interface  SHARED  ${SRC_LIST}  ${CORE_SRC})

target_link_libraries(SF2CS-Interface
        -lSeetaFaceDetector
        -lSeetaFaceRecognizer
        -lSeetaFaceLandmarker
        -lSeetaFaceTracker
        -lSeetaNet
        -lSeetaQualityAssessor)
target_link_libraries(SF2CS-Interface -lstdc++)



