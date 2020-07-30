#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

using namespace std;

class Color
{
    public:
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        float alpha;

        //构造函数，初始值为(0, 0, 0, 0)
        Color();

        //#XXXXXX 构造
        Color(uint32_t data);
        Color(uint8_t red, uint8_t green, uint8_t blue);
        Color(uint8_t red, uint8_t green, uint8_t blue, double alpha);

        //用RGB设置颜色，alpha默认为1
        Color& rgb(uint8_t red, uint8_t green, uint8_t blue);

        //用RGBA设置颜色
        Color& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha);
};

#endif