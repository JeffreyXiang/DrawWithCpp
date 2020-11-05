#include "kernel.h"
#include "stdio.h"
#include "stdlib.h"

#include "complex.h"

__device__ int max_Interations = 1024;

__global__ void MandelbrotKernel(unsigned char* img, int width, int height, double xMin, double yMin, double xMax, double yMax)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index >= width * height) return;
    int xIdx = index % width;
    int yIdx = index / width;
    double x = xMin * (width - xIdx) / width + xMax * xIdx / width;
    double y = yMin * (height - yIdx) / height + yMax * yIdx / height;
    double2 z = { 0, 0 };
    double2 c = { x, y };
    for (int i = 0; i < max_Interations; i++)
    {
        z = complexPlus(complexSquare(z), c);
        if (complexLength2(z) > 4.0)
        {
            img[index] = i % 256;
            break;
        }
    }
    if (index % (int)(width * height / 100) == 0)
    {
        printf(".");
    }
}

__global__ void JuliaKernel(unsigned char* img, int width, int height, double cx, double cy, double xMin, double yMin, double xMax, double yMax)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int xIdx = index % width;
    int yIdx = index / width;
    double x = xMin * (width - xIdx) / width + xMax * xIdx / width;
    double y = yMin * (height - yIdx) / height + yMax * yIdx / height;
    double2 z = { x, y };
    double2 c = { cx, cy };
    for (int i = 0; i < max_Interations; i++)
    {
        z = complexPlus(complexSquare(z), c);
        if (complexLength2(z) > 4.0)
        {
            img[index] = i % 256;
            break;
        }
    }
    if (index % (int)(width * height / 100) == 0)
    {
        printf(".");
    }
}

void Mandelbrot(unsigned char* img, int width, int height, double xMin, double yMin, double xMax, double yMax)
{
    MandelbrotKernel << <ceil(width * height / 1024), 1024 >> > (img, width, height, xMin, yMin, xMax, yMax);

}

void Julia(unsigned char* img, int width, int height, double cx, double cy, double xMin, double yMin, double xMax, double yMax)
{
    JuliaKernel << <ceil(width * height / 1024), 1024 >> > (img, width, height, cx, cy, xMin, yMin, xMax, yMax);
}
