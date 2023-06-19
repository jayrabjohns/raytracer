#include <cuda_runtime.h>

#include "./cuda_accelerated_raytracer.hpp"

cudaError_t addWithCuda(int* c, const int* a, const int* b, unsigned int size);

__global__ void addKernel(int* c, const int* a, const int* b) {
  int i = threadIdx.x;
  c[i] = a[i] + b[i];
}

CudaAcceleratedRaytracer::CudaAcceleratedRaytracer() {}

void CudaAcceleratedRaytracer::render(ImageOptions img_ops, Scene scene, uint8_t* data) const {}

void CudaAcceleratedRaytracer::render_png(const ImageOptions& img_ops, const Scene& scene, const char* out_path) const {
  const int array_size = 5
    const int a[array_size] = { 1, 2, 3, 4, 5 };
  const int b[array_size] = { 10, 20, 30, 40, 50 };
  int c[array_size] = { 0 };

  int* cuda_a = 0;
  cudaMalloc(&cuda_a, sizeof(a));
  int* cuda_b = 0;
  cudaMalloc(&cuda_b, sizeof(b));
  int* cuda_c = 0;
  cudaMalloc(&cuda_c, sizeof(c));

  cudaMemcpy(cudaA, a, sizeof(a), cudaMemcpyHostToDevice);
  cudaMemcpy(cudaB, b, sizeof(b), cudaMemcpyHostToDevice);

  addKernel << < 1, array_size >> > (cuda_a, cuda_b, cuda_c);

  cudaMemcpy(c, cuda_c, sizeof(c), cudaMemcpyDeviceToHost);
  std::cout << c << std::endl;
}

Colour CudaAcceleratedRaytracer::get_background_colour(const Ray& ray) const {
  return Colour();
}

Colour CudaAcceleratedRaytracer::get_ray_colour(const Ray& ray, const Scene& scene, const int max_depth) const {
  return Colour();
}
