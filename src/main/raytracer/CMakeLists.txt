list(APPEND raytrace_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/multi_threaded_cpu_raytracer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/single_threaded_cpu_raytracer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cuda_accelerated_raytracer.cu
)