#include "Font.h"

Font::FontMatrix Font::getFontMatrix(char* data, char c)
{
	FontMatrix res;
	res.width = ((uint16_t)*(data + (2 + height * height / 8) * (c - 32)) << 8) | ((uint8_t)*(data + (2 + height * height / 8) * (c - 32) + 1));
	res.data = new bool[res.width * height];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < res.width; j++)
		{
			res.data[i * res.width + j] = *(data + (2 + height * height / 8) * (c - 32) + 2 + height / 8 * i + j / 8) & (0x80 >> j % 8);
		}
	return res;
}

Font::Font(const char* filename, int height)
{

	this->height = height;
	ifstream f(filename, ios::binary); 
	if (!f.is_open())
	{
		cout<<"Error: no such file.\n";
		exit(0);
	}
	int length;  
	f.seekg(0, ios::end);
	length = f.tellg(); 
	f.seekg(0, ios::beg);
	char* data = new char[length];
	f.read(data, length);
	f.close();
	fontData = new FontMatrix[96];
	for (int i = 32; i < 128; i++)
	{
		fontData[i - 32] = getFontMatrix(data, i);
	}
	delete[] data;
}

Font::~Font()
{
	delete[] fontData;
}

Font::FontMatrix Font::operator[](int idx)
{
	return fontData[idx - 32];
}

int Font::getHeight()
{
	return height;
}
