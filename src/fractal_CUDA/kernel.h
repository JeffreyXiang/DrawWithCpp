#include "cuda_runtime.h"
#include "device_launch_parameters.h"


void Mandelbrot(unsigned char* img, int width, int height, double xMin, double yMin, double xMax, double yMax);
void Julia(unsigned char* img, int width, int height, double cx, double cy, double xMin, double yMin, double xMax, double yMax);
