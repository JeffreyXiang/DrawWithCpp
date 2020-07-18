#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <string>
#include <functional>
#include <algorithm>
#include <Figure/Figure.h>
#include <Color/Color.h>
#include <Font/Font.h>

using namespace std;

class Image
{
    public:
        enum resampling {NEAREST, BILINEAR, BICUBIC, LANCZOS};

    private:
        Color* data;
        uint32_t width;
        uint32_t height;

        typedef struct
        {
             function<double(double)> h;
             double boundary;
        }Kernel;

        const Kernel nearest = {
            [](double x)->double{return 1;},
            0.5
        };

        const Kernel biLinear = {
            [](double x)->double{return 1 - abs(x);},
            1
        };

        const Kernel biCubic = {
            [](double x)->double{
                x = abs(x);
                return (x < 1) ? (1.5 * x * x * x - 2.5 * x * x + 1) :
                                (-0.5 * x * x * x + 2.5 * x * x - 4 * x + 2);
            },
            2
        };

        const Kernel lanczos = {
            [](double x)->double{return x == 0 ? 1 : (3 * sin(PI * x) * sin(PI * x / 3)) / (PI * PI * x * x);},
            3
        };

        double clamp(double x, double low, double high);

        //重采样函数，参数(x坐标，y坐标，重采样比率（小于1为缩小，大于1为放大），重采样类型（枚举中选择）)
        Color resample(double x, double y, double kx, double ky, resampling type);

        void plot(double* data, int points, double xMin, double xMax, double lwidth, Font& font, Color color);

    public:
        Image() : width(0), height(0), data(NULL) {}

        Image(uint32_t width, uint32_t height);
        Image(string str, Font& font, Color color);
        Image(Image& I);
        Image(Image&& I);
        ~Image();
        Image& operator=(Image& I);
        Image& operator=(Image&& I);
        void setBackgroundColor(Color color);
        void setPixel(uint32_t x, uint32_t y, Color color);
        Color getPixel(uint32_t x, uint32_t y);
        void overliePixel(uint32_t x, uint32_t y, Color color);
        Image& draw(Figure& s);
        void plot(double* data, int points, double lwidth, Font& font, Color color);
        void plot(function<double(double)> f, double min, double max, int points, double lwidth, Font& font, Color color);

        //按宽高缩放图片（可变形）
        Image resize(int width, int height, resampling type);

        //只按高度缩放图片（不变形）
        Image resize(int height, resampling type);

        Image& insert(Image& src, Vector pos, Vector center, double height, double theta, resampling type);
        Image& addText(string str, Vector pos, Vector center, double size, double theta, Font& font, Color color);
        Image& addTitle(string str, double size, Font& font, Color color);

        //BMP文件头结构体
        #pragma pack(2)     //按2字节对齐，避免结构体中空位
        typedef struct
        {
            uint16_t bfType;
            uint32_t bfSize;
            uint16_t bfReserved1;
            uint16_t bfReserved2;
            uint32_t bfOffBits;
            uint32_t biSize;
            uint32_t biWidth;
            uint32_t biHeight;
            uint16_t biPlanes;
            uint16_t biBitCount;
            uint32_t biCompression;
            uint32_t biSizeImage;
            uint32_t biXPelsPerMeter;
            uint32_t biYPelsPerMeter;
            uint32_t biClrUsed;
            uint32_t biClrImportant;
        }BMPHead;
        #pragma pack()      //取消自定义对齐设置

        //读取BMP文件
        Image& readBMP(const char* filename);

        //保存BMP文件
        void saveBMP(const char* filename);
};

#endif