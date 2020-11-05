#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdint.h>

#include "Color.h"

__device__ CU_Color CU_Color_mix(CU_Color C1, CU_Color C2, double k)
{
    CU_Color res;
    k = k < 0 ? 0 : k > 1 ? 1 : k;
    res = { k * C1.red + (1 - k) * C2.red, k * C1.green + (1 - k) * C2.green, k * C1.blue + (1 - k) * C2.blue, k * C1.alpha + (1 - k) * C2.alpha };
    return res;
}

__device__ CU_Color CU_Color_overlay(CU_Color C1, CU_Color C2)
{
    CU_Color res;
    double alpha = 1 - (1 - C1.alpha) * (1 - C2.alpha);
    res = { (C1.alpha * C1.red + (1 - C1.alpha) * C2.alpha * C2.red) / alpha,
            (C1.alpha * C1.green + (1 - C1.alpha) * C2.alpha * C2.green) / alpha,
            (C1.alpha * C1.blue + (1 - C1.alpha) * C2.alpha * C2.blue) / alpha,
            alpha };
    return res;
}
