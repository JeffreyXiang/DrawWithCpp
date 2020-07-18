#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <fstream>

using namespace std;

class Font
{
	public:
		typedef struct
		{
			uint16_t width;
			bool* data;
		}FontMatrix;

	private:
		int height;
		FontMatrix* fontData;

		FontMatrix getFontMatrix(char* data, char c);

	public:
		Font(const char* filename, int height);
		~Font();
		FontMatrix operator[](int idx);
		int getHeight();
};

#endif