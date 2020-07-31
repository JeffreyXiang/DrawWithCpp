#include <cmath>
#include <cstring>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <Figure/Figure.h>
#include <Image/Image.h>
#include <Font/Font.h>
#include <Plot/Plot.h>

using namespace std;

int main()
{
	clock_t startTime = clock();
	Font font("../font/DengXian_Light_ASCII_512x.bin", 512);

	Plot plot;
	plot.setDefaultFont(font);
	plot.setTitle("Three-Phase AC");
	plot.setHorName("t(s)");
	plot.setVerName("U(V)");
	//plot.setHorScaleEnabled(false);
	//plot.setVerScaleEnabled(false);
	
	vector<Plot::Continuous> funcs = {
		{ [](double x) {return 311.127 * sin(100 * PI * x + 0 * PI / 3);}, { 255, 0, 0 }, 4 },
		{ [](double x) {return 311.127 * sin(100 * PI * x + 2 * PI / 3);}, { 0, 255, 0 }, 4 },
		{ [](double x) {return 311.127 * sin(100 * PI * x + 4 * PI / 3);}, { 0, 0, 255 }, 4 }
	};

	Image image = plot.plot(0, 0.04, 1024, funcs);
	image.saveBMP("../data/output.bmp");

	clock_t endTime = clock();
	cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s\n";
	return 0;
}
