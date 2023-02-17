cmake_minimum_required(VERSION 3.8)
project(raytrace VERSION 0.0.1)

include(CTest)
enable_testing()

include(src/main/CMakeLists.txt)

add_executable(raytrace ${raytrace_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
