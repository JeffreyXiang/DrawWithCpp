#ifndef IMAGE_H
#define IMAGE_H

#include "Color/Color.h"
#include "Figure/Figure.h"

class Image
{
    private:
        uint8_t* data;
        uint32_t width;
        uint32_t height;

    public:
        //构造函数，以图像的宽度与高度（以像素计）创建对象
        Image(uint32_t width, uint32_t height);

        //析构函数，释放图像数据分配的空间
        ~Image();

        //将一像素点（以坐标(x, y)表示）设为特定颜色
        void setPixel(uint32_t x, uint32_t y, Color color);

        //绘制 Figure
        Image& draw(Figure& s);

        //保存为BMP
        void saveBMP(const char* filename);
};

#endif