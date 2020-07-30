#include "Image.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Image::Image(uint32_t width, uint32_t height)
{
    this->width = width;
    this->height = height;
    data = new uint8_t[3 * width * height];         //����ͼ�����ݿռ� 
    memset(data, 255, 3 * width * height);          //������������Ϊ(255, 255, 255)������ɫ
}

Image::~Image()
{
    delete[] data;
}

void Image::setPixel(uint32_t x, uint32_t y, Color color)
{
    *(data + 3 * (y * width + x)) = color.blue;
    *(data + 3 * (y * width + x) + 1) = color.green;
    *(data + 3 * (y * width + x) + 2) = color.red;
}

Image& Image::draw(Figure& s)
{
    Figure::AABBdata b = s.tAABB();
    int xMin = max((int)floor(b.xMin), 0);
    int yMin = max((int)floor(b.yMin), 0);
    int xMax = min((int)ceil(b.xMax), (int)width - 1);
    int yMax = min((int)ceil(b.yMax), (int)height - 1);

    //��ʾAABB
    for (int u = xMin; u <= xMax; u++)
    {
        setPixel(u, yMin, {0, 255, 0});
        setPixel(u, yMax, {0, 255, 0});
    }
    for (int v = yMin; v <= yMax; v++)
    {
        setPixel(xMin, v, {0, 255, 0});
        setPixel(xMax, v, {0, 255, 0});
    }

    for (int u = xMin; u <= xMax; u++)
        for (int v = yMin; v <= yMax; v++)
            if (s.tSDF({ (double)u, (double)v }) < 0)
                setPixel(u, v, s.getAttribute().color);
    return *this;
    return *this;
}

void Image::saveBMP(const char* filename)
{
    uint32_t size = (3 * width + 3) / 4 * 4 * height + 54;
    uint16_t head[54] = {
        0x4D42,                                     //bfType("BM")
        (uint16_t)size,(uint16_t)(size >> 16),        //bfSize
        0x0000,0x0000,                              //bfReserved1,2(0)
        0x0036,0x0000,                              //bfOffBits(54)
        0x0028,0x0000,                              //biSize(40)
        (uint16_t)width,(uint16_t)(width >> 16),      //biWidth
        (uint16_t)height,(uint16_t)(height >> 16),    //biHeight
        0x0001,                                     //biPlanes(1)
        0x0018,                                     //biBitCount(24)
        0x0000,0x0000,                              //biCompression(0, ��ѹ��)
        0x0000,0x0000,                              //biSizeImage(ȱʡ)
        0x0000,0x0000,                              //biXPelsPerMeter(ȱʡ)
        0x0000,0x0000,                              //biYPelsPerMeter(ȱʡ)
        0x0000,0x0000,                              //biClrUsed(0,ȫ����ɫ)
        0x0000,0x0000                               //biClrImportant(0,ȫ����ɫ)
    };
    cout << "Exporting...\n";
    fstream file(filename, ios::out | ios::binary);             //�½�����ļ�
    if (!file)
    {
        cout << "Error: File open failed.\n";
        return;
    }
    file.write((char*)head, 54);                                //����ļ�ͷ��
    uint8_t fillBytes[3] = { 0 };
    int fillNum = (4 - (3 * width) % 4) % 4;                    //����ĩβ��0��
    for (int i = 0; i < height; i++)
    {
        file.write((char*)(data + 3 * width * i), width * 3);    //���һ��λͼ����
        file.write((char*)fillBytes, fillNum);                 //ĩβ��0������4�ֽڶ���
    }
    file.close();
}
