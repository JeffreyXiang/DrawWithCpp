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

        //���캯������ʼֵΪ(0, 0, 0, 0)
        Color();

        //��RGB������ɫ��alphaĬ��Ϊ1
        Color& rgb(uint8_t red, uint8_t green, uint8_t blue);

        //��RGBA������ɫ
        Color& rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha);
};

#endif