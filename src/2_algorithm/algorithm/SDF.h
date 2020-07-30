#ifndef SDF_H
#define SDF_H

#include <cmath>
#include <algorithm>
#include "Image/Image.h"
#include "Vector/Vector.h"

using namespace std;

//有符号距离场圆环填充算法
void SDFRing(Vector C, double r, double w, Image& image)
{
    Color color;
    Vector P;

    //不用遍历整个画布，只要遍历可能被填充的像素
    for (P.x = floor(C.x - r - w); P.x <= ceil(C.x + r + w); P.x++)
        for (P.y = floor(C.y - r - w); P.y <= ceil(C.y + r + w); P.y++)
            if (fabs((C - P).module() - r) - (w / 2) <= 0)
                image.setPixel(P.x, P.y, color.rgb(0, 0, 0));
}

//有符号距离场直线填充算法
void SDFLine(Vector E1, Vector E2, double w, Image& image)
{
    Color color;
    Vector P, t1, t2;
    int f;                  //SDF值

    //计算可能被填充的像素范围
    int xl = floor(min(E1.x, E2.x) - w / 2);
    int xh = ceil(max(E1.x, E2.x) + w / 2);
    int yl = floor(min(E1.y, E2.y) - w / 2);
    int yh = ceil(max(E1.y, E2.y) + w / 2);

    //不用遍历整个画布，只要遍历可能被填充的像素
    for (P.x = xl; P.x <= xh; P.x++)
        for (P.y = yl; P.y <= yh; P.y++)
        {
            t1 = E2 - E1;
            t2 = P - E1;
            if (t1 * t2 <= 0)
                f = t2.module() - w / 2;
            else if ((t2 = P - E2) * t1 >= 0)
                f = t2.module() - w / 2;
            else
                f = fabs(t1.normalVector() * t2) - w / 2;
            if (f <= 0)
                image.setPixel(P.x, P.y, color.rgb(0, 0, 0));
        }
}

#endif