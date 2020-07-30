#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <cmath>
#include <Image/Image.h>

using namespace std;

//Bresenham 直线算法
void BresenhamLine(int x1, int y1, int x2, int y2, Image& image)
{
    int dx = abs(x1 - x2);              //计算Δx
    int dy = abs(y1 - y2);              //计算Δy
    int x = x1;                         //初始化x,对应公式中变量x
    int y = y1;                         //初始化y,对应公式中变量y
    int xStep, yStep, f;                //x步长，y步长，判据
    Color color;

    if (dy <= dx)                       //若斜率绝对值小于等于1
    {
        if (x2 < x1)
            xStep = -1;                 //若终点在起点左边，x每次向左走一格
        else
            xStep = 1;                  //若终点在起点右边，x每次向右走一格
        if (y2 < y1)
            yStep = -1;                 //若终点在起点下边，y每次向下走一格
        else
            yStep = 1;                  //若终点在起点上边，y每次向上走一格

        f = - dx;                       //f_{x_1}=-Δx
        image.setPixel(x, y, color.rgb(0, 0, 0));
        while (x != x2)                 //若x还未走到终点
        {
            x += xStep;                 //x走一格
            f += 2 * dy;                //根据递推，更新判据
            if (f > 0)                  //若满足y进一格的条件
            {
                y += yStep;             //y走一格
                f -= 2*dx;              //根据递推，更新判据
            }
            image.setPixel(x, y, color.rgb(0, 0, 0));
        }
    }
    else                                //若斜率绝对值大于1，则交换x,y即可
    {
        if (x2 < x1)
            xStep = -1;
        else
            xStep = 1;
        if (y2 < y1)
            yStep = -1;
        else
            yStep = 1;

        f = - dy;
        image.setPixel(x, y, color.rgb(0, 0, 0));
        while (y != y2)
        {
            y += yStep;
            f += 2 * dx;
            if (f > 0)
            {
                x += xStep;
                f -= 2*dy;
            }
            image.setPixel(x, y, color.rgb(0, 0, 0));
        }
    }
}

//Bresenham 画圆算法
void BresenhamCircle(int xc, int yc, int r, Image& image)
{
    int xr = 0;                         //初始化横向相对xc偏移距离
    int yr = r;                         //初始化纵向相对yc偏移距离
    //因为是从上方开始顺时针填充，所以这样初始化
    int f = 4 * r - 1;                  //初始化判据
    Color color;

    image.setPixel(xc + r, yc, color.rgb(0, 0, 0));
    image.setPixel(xc - r, yc, color.rgb(0, 0, 0));
    image.setPixel(xc, yc + r, color.rgb(0, 0, 0));
    image.setPixel(xc, yc - r, color.rgb(0, 0, 0));
    //上下左右四个起点上色
    while (xr <= yr)
    {
        f += -8 * xr - 4;               //根据递推式，更新判据
        xr++;                           //xr走一格
        if (f < 0)                      //若满足y走一格条件
        {
            f += 8 * yr;                //根据递推式，更新判据
            yr--;                       //yr走一格
        } 
        image.setPixel(xc + xr, yc + yr, color.rgb(0, 0, 0));
        image.setPixel(xc + xr, yc - yr, color.rgb(0, 0, 0));
        image.setPixel(xc - xr, yc + yr, color.rgb(0, 0, 0));
        image.setPixel(xc - xr, yc - yr, color.rgb(0, 0, 0));
        image.setPixel(xc + yr, yc + xr, color.rgb(0, 0, 0));
        image.setPixel(xc + yr, yc - xr, color.rgb(0, 0, 0));
        image.setPixel(xc - yr, yc + xr, color.rgb(0, 0, 0));
        image.setPixel(xc - yr, yc - xr, color.rgb(0, 0, 0));
        //依据8等分对称性填充
    }
}

#endif