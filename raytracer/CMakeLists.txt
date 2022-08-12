# CMakeList.txt : CMake project for raytracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (raytracer "main.cpp" "main.h" "stb_image.h" "stb_image_write.h" "vec3.h" "vec3.cpp"   "ray.h" "ray.cpp" "raytracer.h" "raytracer.cpp"  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET raytracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
