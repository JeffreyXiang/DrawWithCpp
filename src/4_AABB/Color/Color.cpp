#include "Color.h"

Color::Color()
{
    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
}

Color::Color(uint32_t data)
{
    this->red = data >> 16;
    this->green = data >> 8;
    this->blue = data;
    this->alpha = 1;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = 1;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, double alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

Color& Color::rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = 1;
    return *this;
}

Color& Color::rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
    return *this;
}
