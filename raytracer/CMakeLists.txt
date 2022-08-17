# CMakeList.txt : CMake project for raytracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (raytracer "main.cpp" "main.h" "image_creation/stb_image.h" "image_creation/stb_image_write.h" "geometry/vec3.h" "geometry/vec3.cpp"   "geometry/ray.h" "geometry/ray.cpp" "raytracer.h" "raytracer.cpp"   "geometry/hittable.h" "geometry/sphere.h" "geometry/sphere.cpp" "geometry/scene.h" "geometry/scene.cpp" "utils/math_utils.h" "geometry/plane.h" "geometry/plane.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET raytracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
