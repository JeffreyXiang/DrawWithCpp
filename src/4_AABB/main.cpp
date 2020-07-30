#include <Color/Color.h>
#include <Image/Image.h>
#include <Figure/Figure.h>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    clock_t startTime = clock();
    Image image(3000, 500);
    Color color;
    color.rgb(0, 168, 243);
    Figure::Attribute attr1 = { color, 10, 3 };
    Figure::Attribute attr2 = { color, 10, -1 };
    Figure::Attribute attr3 = { color, 0, -1 };
    Circle circle({ 250, 250 }, 150, attr3);
    Capsule capsule({ 450 ,100 }, { 750, 400 }, 5, attr1);
    Rectangle rectangle({ 1050, 250 }, { 200, 100 }, -30, attr3);
    UnevenCapsule unevenCapsule({ 1400, 100 }, { 1400, 400 }, 20, 10, attr1);
    Triangle triangle({ 1550, 100 }, { 1850, 150 }, { 1650, 400 }, attr2);
    Pie pie({ 2400, 250 }, 150, -90, 45, attr3);
    Arc arc({ 2150, 250 }, 50, 30, 45, 270, attr1);
    Polygon polygon({ {471,271.88},{1000,1900},{1529,271.88},{144,1278.12},{1856,1278.12} }, attr1);
    Ellipse ellipse({ 2750, 250 }, 200, 100, 60, attr1);
    QuadraticBezier bezier({ 1500, 500 }, { 2000, 2000 }, { 500, 500 }, attr1);
    image.draw(circle).draw(capsule).draw(rectangle).draw(unevenCapsule).draw(triangle).draw(pie).draw(arc).draw(ellipse);
    image.saveBMP("../data/output.bmp");
    clock_t endTime = clock();
    cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
