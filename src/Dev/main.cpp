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


class Layer
{
    private:
        Color* data;
        uint32_t width;
        uint32_t height;

    public:
        typedef enum BlendingMode
        {
            BACK 
        }BlendingMode;

        typedef struct CSGMixingParam
        {
            CSGObj csg;
            int8_t blendingMode;
        }CSGMixingParam;

        typedef struct layerMixingParam
        {
            Layer* layer;
            int8_t blendingMode;
        }layerMixingParam;

        Layer(uint32_t width, uint32_t height)
        {
            this->width = width;
            this->height = height;
            data = new Color[width * height];
        }

        Layer(const Layer& L)
        {
            data = L.data;
            width = L.width;
            height = L.height;
        }

        ~Layer()
        {
            delete[] data;
        }

        Layer& operator<<(CSGMixingParam param)
        {
            if (param.blendingMode > 0)
            {

            }
            else if (param.blendingMode < 0)
            {

            }
            else
            {

            }
        }
};


/*Figure::Attribute attr2 = {color, 10, -1};
    Figure::Attribute attr3 = {color, 0, -1};
    Circle circle({250, 250}, 150, attr3);
    Capsule capsule({450 ,100}, {750, 400}, 5, attr1);
    Rectangle rectangle({1050, 250}, {200, 100}, -30, attr3);
    UnevenCapsule unevenCapsule({1400, 100}, {1400, 400}, 20, 10, attr1);
    Triangle triangle({1550, 100}, {1850, 150}, {1650, 400}, attr2);
    Pie pie({2400, 250}, 150, -90, 45, attr3);
    Arc arc({2150, 250}, 50, 30, 45, 270, attr1);
    Polygon polygon({{471,271.88},{1000,1900},{1529,271.88},{144,1278.12},{1856,1278.12}}, attr1);
    Ellipse ellipse({2750, 250}, 200, 100, 60, attr1);
    QuadraticBezier bezier({1500, 500}, {2000, 2000}, {500, 500}, attr1);
    CSG csg;*/

    /*Capsule* cap;
    srand((int)time(NULL));
    double f1;
    double f2;
    for (int i = 0; i < 10000; i++)
    {
        f1 = f(0);
        for (int x = 1; x < 3000 - 1; x++)
        {
            f2 = f(x);
            cap = new Capsule({x, f1}, {x+1, f2}, 1, attr1);
            for (int u = x - 5; u < x + 5; u++)
                for (int v = min(f1, f2)-5; v < max(f1, f2) + 5; v++)
                {
                    double SDF = cap->tSDF({u, v});
                    if (SDF<0)
                    image.setPixel(u, v, Color::mix(color.rgb(0, 0, 0), image.getPixel(u, v), 0.001));
                }
            delete cap;
            f1 = f2;
        }
    }*/

    /*Arc* arc;
    double x, y, t1, t2;
    srand((int)time(NULL));
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            x = 100 * j + 50;
            y = 100 * i + 50;
            t1 = rand() % 360;
            t2 = t1 + rand() % 360;
            attr1.color = Color::mix(Color::mix({255,0,255},{0,255,255},x/3000),Color::mix({0,0,255},{0,255,0},x/3000),y/2000).max();
            //attr1.color = color.rgb(x * 128 / 3000 + y * 128 / 2000, 255 - x * 128 / 3000 - y * 128 / 2000, 127 + x * 128 / 3000 - y * 128 / 2000).max();
            arc = new Arc({x, y}, 40, 5, t1, t2, attr1);
            for (int u = x - 50; u < x + 50; u++)
                for (int v = y - 50; v < y + 50; v++)
                {
                    double SDF = arc->tSDF({u, v});
                    image.setPixel(u, v, Color::mix(arc->getAttribute().color, color.rgb(127, 127, 127), 0.5 - SDF));
                }
        }
    }*/

    /*for (int x = 0; x < 3000; x++)
        for (int y = 0; y < 2000; y++)
        {
            CSG::SDFData SDF = csg.SDF({x,y});
            if (SDF.distance > 0)
                image.setPixel(x, y, color.rgb(255 + SDF.distance * 255 / 32, 255 + SDF.distance * 255 / 32, 255));
            else
                image.setPixel(x, y, color.rgb(255, 255 + SDF.distance * 255 / 32, 255 + SDF.distance * 255 / 32));
        }*/
    /*int num = 64;
    int c = 1500;
    for (int j = 0; j < 20; j++)
    {
        SDFRing({c, c}, 1400 / (j + 1), 15.0 / (j+1), image);
        for (int i = 0; i < num; i++)
        {
            //BresenhamLine(c + 600 / (j + 1) * cos((i + 0.5 * j) / (num * 0.5) * 3.141592654), c + 600 / (j + 1) * sin((i + 0.5 * j) / (num * 0.5) * 3.141592654), c + 600 / (j + 2) * cos((i + 0.5 * j) / (num * 0.5) * 3.141592654), c + 600 / (j + 2) * sin((i + 0.5 * j) / (num * 0.5) * 3.141592654), image);
            //BresenhamCircle(c, c, 600 / (j + 1), image);
            //scanLineLine({(double)(c + 600 / (j + 1) * cos((i + 0.5 * j) / (num * 0.5) * 3.141592654)), (double)(c + 600 / (j + 1) * sin((i + 0.5 * j) / (num * 0.5) * 3.141592654))}, {(double)(c + 600 / (j + 2) * cos((i + 0.5 * j) / (num * 0.5) * 3.141592654)), (double)(c + 600 / (j + 2) * sin((i + 0.5 * j) / (num * 0.5) * 3.141592654))}, 6-j, image);
            SDFLine({(double)(c + 1400 / (j + 1) * cos((i + 0.5 * j) / (num * 0.5) * 3.141592654)), (double)(c + 1400 / (j + 1) * sin((i + 0.5 * j) / (num * 0.5) * 3.141592654))}, {(double)(c + 1400 / (j + 2) * cos((i + 0.5 * j) / (num * 0.5) * 3.141592654)), (double)(c + 1400 / (j + 2) * sin((i + 0.5 * j) / (num * 0.5) * 3.141592654))}, 5.0 / (j+1), image);
        }
    }
    //BresenhamCircle(1500, 1000, 10, image);
    //scanLinePolygon({{471,271.88},{1000,1900},{1529,271.88},{144,1278.12},{1856,1278.12}}, image);
    //scanLineLine({100,100},{1200,1200},2,image);
    //SDFRing({650,650}, 400, 10, image);
    //SDFLine({100,100},{1200,1200},100,image);*/

//sin(PI*x)/(PI*x)    abs(2*PI*x)<PI
//abs(x)<0.5    2*sin((x*2*PI)/2)/(x*2*PI)
//(abs(x)<1)*(1-abs(x))    pow(2*sin((x*2*PI)/2)/(x*2*PI),2);
//(abs(x)<1)?(1.5*pow(abs(x),3)-2.5*pow(abs(x),2)+1):(abs(x)<2)?(-0.5*pow(abs(x),3)+2.5*pow(abs(x),2)-4*abs(x)+2):0

double sinc(double x)
{
    return x == 0 ? 1 : sin(PI * x) / (PI * x);
}

double f(double x)
{
    double res = 0;
    res = (abs(x) < 3 ? sinc(x) * sinc(x / 3) : 0);
    return res;
}

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
