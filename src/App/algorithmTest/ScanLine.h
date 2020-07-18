#ifndef SCANLINE_H
#define SCANLINE_H

#include <cmath>
#include <initializer_list>
#include <Image/Image.h>

using namespace std;

//扫描线多边形填充算法
void scanLinePolygon(std::initializer_list<Vector> vertexes, Image& image)
{
    //initializer_list是C++11的新特性，本质上就是一个能表示其长度的数组
    //它有3个成员函数：size()、begin()和end()，意义与一般数组一致

    Color color;

    //交点链表类型定义
    typedef struct intersection
    {
        double x;
        struct intersection* next;
    }intersection;

    //寻找所有扫描线纵坐标的极大极小值
    int yMax = floor(vertexes.begin()->y), yMin = yMax;
    for (Vector* p = (Vector*)vertexes.begin() + 1; p < vertexes.end(); p++)
    {
        if (p->y > yMax + 1)
            yMax = floor(p->y);
        else if (p->y < yMin)
            yMin = floor(p->y);
    }

    //计算有多少条扫描线会穿过（可以验证这满足“上闭下开”）
    int scanLineNum = yMax - yMin;

    //初始化交点表
    intersection* intersections = new intersection[scanLineNum];
    memset(intersections, 0, scanLineNum * sizeof(intersection));

    //计算交点表
    int yh, yl;
    double delta, x, x0, y0;
    Vector* q;
    intersection *r, *s;
    for (Vector* p = (Vector*)vertexes.begin(); p < vertexes.end(); p++)
    {
        //以循环方式确定下一个顶点
        if (p != vertexes.end() - 1)
            q = p + 1;
        else
            q = (Vector*)vertexes.begin();

        //准备递推参数
        delta = (q->x - p->x) / (q->y - p->y);  //增量
        if (p->y > q->y)
        {
            yh = floor(p->y);
            yl = floor(q->y);
            x0 = p->x;
            y0 = p->y;
        }
        else
        {
            yl = floor(p->y);
            yh = floor(q->y);
            x0 = q->x;
            y0 = q->y;
        }                                       //扫描线上下限
        if (yl == yh) continue;                 //若无交点，扫描下一条边

        //开始扫描
        x = x0 - (y0 - yh) * delta;             //计算x初值
        r = intersections + (yMax - yh);        //对应扫描线交点链表头
        while (r->next != NULL && r->next->x < x) r = r->next;
        s = r->next;
        r->next = new intersection;
        r->next->x = x;
        r->next->next = s;                      //按序插入链表
        for (int i = yh - 1; i > yl; i--)       //遍历扫描线
        {
            x -= delta;                         //递推
            r = intersections + (yMax - i);     //对应扫描线交点链表头
            while (r->next != NULL && r->next->x < x) r = r->next;
            s = r->next;
            r->next = new intersection;
            r->next->x = x;
            r->next->next = s;                  //按序插入链表
        }
    }

    //根据交点表填色
    for (int i = yMax; i > yMin; i--)
    {
        r = (intersections + (yMax - i))->next;
        while (r != NULL)
        {
            for (int j = round(r->x); j < round(r->next->x); j++)
                image.setPixel(j, i, color.rgb(0, 0, 0));
            r = r->next->next;
        }//两两一组，“左闭右开”填色
    }

    //释放交点表空间
    for (int i = 0; i < scanLineNum; i++)
    {
        r = (intersections + i)->next;
        while (r != NULL)
        {
            s = r;
            r = r->next;
            delete s;
        }
    }
    delete[] intersections;
}

//扫描线直线填充算法
void scanLineLine(Vector E1, Vector E2, double width, Image& image)
{
    //利用之前定义的向量与其运算，求得对应矩形，调用多边形填充绘制
    scanLinePolygon({E1 + (E2 - E1).normalVector() * (width / 2), E2 + (E2 - E1).normalVector() * (width / 2), 
                    E2 - (E2 - E1).normalVector() * (width / 2), E1 - (E2 - E1).normalVector() * (width / 2)}, image);
}

#endif