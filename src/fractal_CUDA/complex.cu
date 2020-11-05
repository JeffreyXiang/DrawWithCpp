#include "complex.h"

__device__ double2 complexPlus(double2 A, double2 B)
{
    return { A.x + B.x, A.y + B.y };
}

__device__ double2 complexMinus(double2 A, double2 B)
{
    return { A.x - B.x, A.y - B.y };
}

__device__ double2 complexMultiply(double2 A, double2 B)
{
    return { A.x * B.x - A.y * B.y, A.x * B.y + A.y * B.x };
}

__device__ double2 complexSquare(double2 A)
{
    return { A.x * A.x - A.y * A.y, 2 * A.x * A.y };
}

__device__ double complexLength2(double2 A)
{
    return A.x * A.x + A.y * A.y;
}
