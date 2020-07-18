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
        double alpha;

        Color();
        Color(uint32_t data);
        Color(uint8_t red, uint8_t green, uint8_t blue);
        Color(uint8_t red, uint8_t green, uint8_t blue, double alpha);
        Color(Color& C, double alpha);
        ~Color() {}
        Color& rgb(uint8_t red, uint8_t green, uint8_t blue);
        Color& rgba(uint8_t red, uint8_t green, uint8_t blue, double alpha);
        Color& ca(Color C, double alpha);
        Color operator*(double k);
        static Color mix(Color C1, Color C2, double k);
        static Color overlie(Color C1, Color C2);
};

#endif