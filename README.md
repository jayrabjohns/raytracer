# Ray tracing 
Based on: [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

## Local Setup
1. Install [cmake](https://cmake.org/install/), a [C++17 compiler](https://gcc.gnu.org/install/), and the [CUDA toolkit v12.1](https://developer.nvidia.com/cuda-downloads)
2. Build the project. 
    ```shell
    cmake -DCMAKE_BUILD_TYPE=Debug -B out/build
    cmake --build out/build --config Debug
    ```
    Or replace `Debug` with `Release` if you want a release build
3. Run the project. 
   ```shell
   ./out/build/raytrace
   ```
4. Alternatively, if you're using VS Code, there's quite a good [cmake extension](https://code.visualstudio.com/docs/cpp/cmake-linux) you can use for bulding and running the project.

### Discalimer
The CUDA SDK is tightly coupled system type and hardware specifications, meaning there is no guarantee of this project working on platforms which it hasn't been explicitly tested. 

The project has been tested on Ubuntu 22 with an Intel CPU, and a Geforce 1660ti.

If the project is incompatible with your machine, or if you'd prefer not to download the CUDA sdk, this project also contains an implementation for running on the CPU, which should hopefully be more consistent across platforms.

## Renders timeline

### 9. Big Scene
![Loads of spheres](/img/9_big_scene.png?raw=true "Loads of spheres")

### 8. Defocus blur

![Defocus blur](/img/8_defocus_blur.png?raw=true "Defocus blur")

### 7. Dielectrics (refraction) 

![Glass ball](/img/7_glass_ball.png?raw=true "Glass ball")

### 6. Fuzzy metals

![Fuzzy metal material](/img/6_fuzzy_metals.png?raw=true "Metal material")

### 5. Shiny metals

![Metal material](/img/5_metals.png?raw=true "Metal material")

### 4. Diffuse materials

![Diffuse material](/img/4_diffuse_materials.png?raw=true "Diffuse material")

### 3. Shading geometry with surface normals

![Shading normals](/img/3_shading_geomety_with_normals.png?raw=true "Shading normals")

### 2. Adding geometry

![Adding geometry](/img/2_adding_geometry.jpg?raw=true "Adding geometry")

### 1. Creating an Image

![Creating and image](/img/1_creating_an_image.jpg?raw=true "Creating an image")
