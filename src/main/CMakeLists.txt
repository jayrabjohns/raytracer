include(${CMAKE_CURRENT_LIST_DIR}/geometry/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/materials/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/raytracer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/scene/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/utils/CMakeLists.txt)

list(APPEND raytrace_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)