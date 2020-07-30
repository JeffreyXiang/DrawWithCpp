#include <Color/Color.h>
#include <Image/Image.h>
#include <Figure/Figure.h>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    clock_t startTime = clock();
    Image image;
    image.readBMP("../data/test.bmp");
    image = image.resize(1000, Image::NEAREST);
    image.saveBMP("../data/output.bmp");
    clock_t endTime = clock();
    cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
