cmake_minimum_required(VERSION 3.10)
project(test) 

set(CMAKE_CXX_STANDARD 14)

include_directories(
    src
)

add_executable(write src/write.cpp src/SharedMemory.cpp) 
add_executable(read src/read.cpp src/SharedMemory.cpp) 