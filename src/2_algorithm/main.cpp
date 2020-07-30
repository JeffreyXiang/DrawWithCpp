#include <Color/Color.h>
#include <Image/Image.h>
#include <algorithm/Bresenham.h>
#include <algorithm/ScanLine.h>
#include <algorithm/SDF.h>

#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    clock_t startTime = clock();
    Image image(1300, 1300);
    Color color;
    
    //径向条数
    int rNum = 64;
    //圈数
    int cNum = 5;
    //图像圆心
    double c = 650;

    //随意解除注释，看看会发生什么
    for (int j = 0; j < cNum; j++)
    {
        for (int i = 0; i < rNum; i++)
        {
            //BresenhamLine(c + 600 / (j + 1) * cos((i + 0.5 * j) / (rNum * 0.5) * 3.141592654), c + 600 / (j + 1) * sin((i + 0.5 * j) / (rNum * 0.5) * 3.141592654), c + 600 / (j + 2) * cos((i + 0.5 * j) / (rNum * 0.5) * 3.141592654), c + 600 / (j + 2) * sin((i + 0.5 * j) / (rNum * 0.5) * 3.141592654), image);
            //BresenhamCircle(c, c, 600 / (j + 1), image);
            //scanLineLine({ (double)(c + 600 / (j + 1) * cos((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)), (double)(c + 600 / (j + 1) * sin((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)) }, { (double)(c + 600 / (j + 2) * cos((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)), (double)(c + 600 / (j + 2) * sin((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)) }, 6 - j, image);
            //SDFLine({ (double)(c + 600 / (j + 1) * cos((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)), (double)(c + 600 / (j + 1) * sin((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)) }, { (double)(c + 600 / (j + 2) * cos((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)), (double)(c + 600 / (j + 2) * sin((i + 0.5 * j) / (rNum * 0.5) * 3.141592654)) }, 5.0 / (j + 1), image);
            //SDFRing({ c, c }, 600 / (j + 1), 15.0 / (j + 1), image);
        }
    }
    //scanLinePolygon({{ 297.33, 164.59 }, { 650, 1250 }, { 1002.67, 164.59 }, { 79.37, 835.41 }, { 1220.63, 835.41 }}, image);
    image.saveBMP("../data/output.bmp");
    clock_t endTime = clock();
    cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
