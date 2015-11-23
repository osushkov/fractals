
#include "MandelbrotKernel.hpp"
#include "CuVector.hpp"

// For the CUDA runtime routines (prefixed with "cuda_")
#include <cuda_runtime.h>
#include <iostream>

static int *deviceItersOut = NULL;
static int *hostItersOut = NULL;

static size_t itersDataSize = 0;

__global__ void mandelbrotIters(
    int samplesX, int samplesY,
    double pWidth, double pHeight,
    CuVector2 minPixel, int iterations,
    int *itersOut) {

  int index = blockDim.x * blockIdx.x + threadIdx.x;

  int x = index % samplesX;
  int y = index / samplesX;

  if (y < samplesY) {
    CuVector2 p;
    p.x = minPixel.x + x * pWidth;
    p.y = minPixel.y + y * pHeight;

    int result = 0;

    CuVector2 cv;
    cv.x = 0.0;
    cv.y = 0.0;

    for (int i = 1; i <= iterations; i++) {
      double nx = cv.x*cv.x - cv.y*cv.y + p.x;
      double ny = 2.0*cv.x*cv.y + p.y;

      cv.x = nx;
      cv.y = ny;

      double length2 = nx*nx + ny*ny;
      result = (result == 0 && length2 >= 4.0) ? i : result;
    }

    itersOut[index] = result;
  }
}


std::vector<int> MandelbrotKernel::calculateIterationsPerPixel(
    int samplesX, int samplesY,
    double pWidth, double pHeight, CuVector2 minPixel,
    int iters) {

  int numPoints = samplesX * samplesY;

  size_t newItersDataSize = numPoints * sizeof(int);

  if (newItersDataSize > itersDataSize) {
    if (hostItersOut != NULL) {
      cudaFree(deviceItersOut);
      free(hostItersOut);
    }

    itersDataSize = newItersDataSize;

    hostItersOut = (int *) malloc(itersDataSize);
    cudaMalloc((void **)&deviceItersOut, itersDataSize);
  }

  int threadsPerBlock = 64;
  int blocksPerGrid = (numPoints + threadsPerBlock - 1) / threadsPerBlock;

  mandelbrotIters<<<blocksPerGrid, threadsPerBlock>>>(
    samplesX, samplesY, pWidth, pHeight, minPixel, iters, deviceItersOut);

  cudaMemcpy(hostItersOut, deviceItersOut, itersDataSize, cudaMemcpyDeviceToHost);

  std::vector<int> result;
  for (int i = 0; i < numPoints; i++) {
    result.push_back(hostItersOut[i]);
  }

  return result;
}
