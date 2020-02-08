cmake_minimum_required(VERSION 3.10)
project(TestSharedLib)

# C++11 编译
set(CMAKE_CXX_STANDARD 11)

# 头文件路径
set(INC_DIR ../include)
# 库文件路径
set(LIB_DIR ../build)

include_directories(${INC_DIR})
link_directories(${LIB_DIR})
link_libraries(SF2CS-Interface)

add_executable(TestSharedLib main.cpp)

# 链接 MySharedLib 库

target_link_libraries(TestSharedLib -lSF2CS-Interface )

target_link_libraries(TestSharedLib
        -lSF2CS-Interface)
target_link_libraries(TestSharedLib -lstdc++)