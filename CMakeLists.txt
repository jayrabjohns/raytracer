cmake_minimum_required(VERSION 3.8)
project(raytrace VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_LIST_DIR}/src/main/CMakeLists.txt)

add_executable(raytrace ${raytrace_SOURCES})

target_include_directories(raytrace 
  PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/external/include
)
