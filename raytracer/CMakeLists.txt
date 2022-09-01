# CMakeList.txt : CMake project for raytracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (raytracer "main.cpp" "main.hpp" "stb/stb_image_write.h" "geometry/vec3.hpp" "geometry/vec3.cpp" "geometry/ray.hpp" "geometry/ray.cpp" "camera.hpp" "camera.cpp" "raytracer.hpp" "raytracer.cpp" "geometry/hittable.hpp" "geometry/sphere.hpp" "geometry/sphere.cpp" "geometry/scene.hpp" "geometry/scene.cpp" "utils/math_utils.hpp" "geometry/plane.hpp" "geometry/plane.cpp" "materials/material.hpp" "materials/diffuse_lambert.cpp" "materials/diffuse_lambert.hpp" "materials/metal.hpp" "materials/metal.cpp" "materials/dielectric.hpp" "materials/dielectric.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET raytracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
