#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__device__ double2 complexPlus(double2 A, double2 B);
__device__ double2 complexMinus(double2 A, double2 B);
__device__ double2 complexMultiply(double2 A, double2 B);
__device__ double2 complexSquare(double2 A);
__device__ double complexLength2(double2 A);