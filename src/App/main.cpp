#include <cmath>
#include <cstring>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <Figure/Figure.h>
#include <CSGObj/CSGObj.h>
#include <Image/Image.h>
#include <Font/Font.h>

using namespace std;

int main()
{
    clock_t startTime = clock();
    Color colorList[] = {
        0xef2b35,
        0x00f0d3,
        0xffef00,
        0xff2bd8,
        0x832dff,
        0x1c66ff,
        0x43ff36,
        0xff9804,
    };
    //Font font("font/Dengxian_Light_ASCII_512x.bin", 512);
    Image image(3000, 500);
    image.readBMP("../data/20200616142640.bmp");
    image = image.resize(250, Image::BICUBIC);
    //image.plot(f,-4,4,4096,3,font,{0,128,192});
    //image.addTitle("x'(t)",72,font,{0,0,0});
    image.saveBMP("../data/output.bmp");
    clock_t endTime = clock();
    cout<<"Elapsed time: "<<(double)(endTime - startTime) / CLOCKS_PER_SEC<<"s\n";
    return 0;
}
