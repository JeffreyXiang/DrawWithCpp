#include <iostream>
#include <Image/Image.h>

#include "kernel.h"

Color palette[256];

void initPalette()
{
	for (int i = 0; i < 256; i++)
	{
		palette[(i) % 256].rgb(
			i % 256 / 64 == 0 ? i : i % 256 / 64 == 1 ? -128 + 3 * i : i % 256 / 64 == 2 ? 383 - i : 768 - 3 * i,
			i % 256 / 32 == 0 ? i : i % 256 / 32 == 1 || i % 256 / 32 == 2 ? -64 + 3 * i : i % 256 / 32 == 3 ? 128 + i : i % 256 / 32 == 4 ? 383 - i : i % 256 / 32 == 5 || i % 256 / 32 == 6 ? 703 - 3 * i : 255 - i,
			i % 256 / 64 == 0 ? 3 * i : i % 256 / 64 == 1 ? 128 + i : i % 256 / 64 == 2 ? -4 * i - 1 : 0
		);
	}
}

void main()
{
	int width;
	int height;
	int SSAA;
	double zoom;
	double cx;
	double cy;
	std::cout << "Draw Julia Set with CUDA\n";
	std::cout << "Width: ";
	std::cin >> width;
	std::cout << "Height: ";
	std::cin >> height;
	std::cout << "Zoom: ";
	std::cin >> zoom;
	std::cout << "Center: ";
	std::cin >> cx >> cy;
	std::cout << "SSAA: ";
	std::cin >> SSAA;

	int size = SSAA * SSAA * width * height;

	initPalette();
	Image image(width, height);

	unsigned char *img, *img_d;

	img = new unsigned char[size];
	cudaMalloc((void**)&img_d, size);

	double xMin = -zoom / 2;
	double xMax = zoom / 2;
	double yMin = -zoom / 2 * height / width;
	double yMax = zoom / 2 * height / width;

	Julia(img_d, SSAA * width, SSAA * height, cx, cy, xMin, yMin, xMax, yMax);

	// Check for any errors launching the kernel
	cudaError_t cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess)
	{
		std::cerr << "addKernel launch failed: " << cudaGetErrorString(cudaStatus) << endl;
		exit(-1);
	}

	cudaMemcpy(img, img_d, size, cudaMemcpyDeviceToHost);
	cout << endl;

	for (size_t y = 0; y < height; y++)
	for (size_t x = 0; x < width; x++)
	{
		int colorIdx = 0;
		for (size_t i = 0; i < SSAA; i++)
		for (size_t j = 0; j < SSAA; j++)
			colorIdx += img[(y * SSAA + i) * SSAA * width + (x * SSAA + j)];
		colorIdx /= SSAA * SSAA;
		image.setPixel(x, y, palette[colorIdx]);
	}

	image.saveBMP("../data/output.bmp");

	cudaFree(img_d);
	delete[] img;
}