#include <cmath>
#include <cstring>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <Figure/Figure.h>
#include <Image/Image.h>
#include <Font/Font.h>

using namespace std;

int main()
{
	clock_t startTime = clock();
	Font font("../font/DengXian_ASCII_128x.bin", 128);

	//ASCII艺术输出'@'
	/*Font::FontMatrix dots = font['@'];
	for (size_t i = 0; i < font.getHeight(); i+=2)
	{
		for (size_t j = 0; j < dots.width; j++)
			cout << (dots.data[i * dots.width + j] ? '@' : '.');
		cout << endl;
	}*/

	//测试文字原图
	/*Image test("(@_@)", font, { 255, 255, 255 });
	test.saveBMP("../data/output.bmp");*/

	//测试插入图片
	/*Image test("(@_@)", font, { 255, 255, 255 });
	Image image;
	image.readBMP("../data/test2.bmp");
	image.insert(test, { 600, 300 }, { 0.5, 0.5 }, 200, -15, Image::BICUBIC);
	image.insert(test, { 1200, 850 }, { 0.5, 0.5 }, 200, 200, 30, Image::BICUBIC);
	image.saveBMP("../data/output.bmp");*/

	clock_t endTime = clock();
	cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
	return 0;
}
