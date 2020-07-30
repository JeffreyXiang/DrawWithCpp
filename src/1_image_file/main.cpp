#include <Color/Color.h>
#include <Image/Image.h>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    clock_t startTime = clock();
    Image image(512, 128);
    Color color;
    for (int x = 0; x < 512; x++)
        for (int y = 0; y < 128; y++)
        {
            image.setPixel(x, y, color.rgb(x / 4 + y, 255 - x / 4 - y, 127 + x / 4 - y));
        }
    image.saveBMP("../data/output.bmp");
    clock_t endTime = clock();
    cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
