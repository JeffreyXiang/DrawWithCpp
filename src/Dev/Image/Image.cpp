#include "Image.h"

double Image::clamp(double x, double low, double high)
{
    return x < low ? low : x > high ? high : x;
}

//重采样函数，参数(x坐标，y坐标，重采样比率（小于1为缩小，大于1为放大），重采样类型（枚举中选择）)
Color Image::resample(double x, double y, double kx, double ky, resampling type)
{
    double r = 0, g = 0, b = 0, a = 0, h;
    int u, v;
    Color pc;

    //整数化 k
    if (kx > 1) kx = 1;
    kx = 1 / round(1 / kx);
    if (ky > 1) ky = 1;
    ky = 1 / round(1 / ky);

    //找到所用的卷积核
    const Kernel* kernel;
    switch (type)
    {
    case NEAREST: kernel = &nearest; break;
    case BILINEAR: kernel = &biLinear; break;
    case BICUBIC: kernel = &biCubic; break;
    case LANCZOS: kernel = &lanczos; break;
    }

    //遍历卷积核的非0区域
    for (int i = ceil(x - kernel->boundary / kx); i <= floor(x + kernel->boundary / kx); i++)
        for (int j = ceil(y - kernel->boundary / ky); j <= floor(y + kernel->boundary / ky); j++)
        {
            //最近取值法扩展取色
            if (i < 0) u = 0;
            else if (i >= width) u = width - 1;
            else u = i;
            if (j < 0) v = 0;
            else if (j >= height) v = height - 1;
            else v = j;
            pc = getPixel(u, v);

            //按公式进行重采样计算（颜色按透明度加权）
            h = kx * ky * kernel->h(kx * (i - x)) * kernel->h(ky * (j - y));
            r += pc.alpha * pc.red * h;
            g += pc.alpha * pc.green * h;
            b += pc.alpha * pc.blue * h;
            a += pc.alpha * h;
        }
    r /= a;
    g /= a;
    b /= a;

    //返回钳位过的颜色
    return {
        (uint8_t)clamp(r, 0, 255),
        (uint8_t)clamp(g, 0, 255),
        (uint8_t)clamp(b, 0, 255),
        clamp(a, 0, 1)
    };
}

void Image::plot(double* data, int points, double xMin, double xMax, double lwidth, Font& font, Color color)
{
    stringstream str;
    double yMax = data[0], yMin = data[0];
    for (int i = 1; i < points; i++)
    {
        yMax = max(yMax, data[i]);
        yMin = min(yMin, data[i]);
    }
    if (yMax - yMin < 2e-6)
    {
        yMax += 1e-6;
        yMin -= 1e-6;
    }
    double ys, yd;
    ys = 0.8 * height / (yMax - yMin);
    yd = -ys * yMin + 0.1 * height;
    double x1, y1, x2, y2;
    Capsule* cap;
    Figure::Attribute attr = { color, 0, -1 };
    Figure::Attribute lable = { color.rgb(0, 0, 0), 0, -1 };
    setBackgroundColor({ 0, 0, 0, 0 });

    cap = new Capsule({ width * 0.05 - 10, height * 0.05 }, { width * 0.95 + 10, height * 0.05 }, 1, lable);
    draw(*cap);
    delete cap;
    cap = new Capsule({ width * 0.05, height * 0.05 - 10 }, { width * 0.05, height * 0.95 + 10 }, 1, lable);
    draw(*cap);
    delete cap;
    int i = round(log10(yMax - yMin) - 1);
    double s = pow(10, i);
    double h;
    for (int y = round(yMin / s); y <= round(yMax / s); y++)
    {
        h = height * 0.1 + 0.8 * height * (y * s - yMin) / (yMax - yMin);
        if (h > 0.05 * height && h < 0.95 * height)
        {
            cap = new Capsule({ width * 0.05, h }, { width * 0.05 + 10, h }, 1, lable);
            draw(*cap);
            delete cap;
            str << fixed << setprecision(-i > 0 ? -i : 0) << y * s;
            addText(str.str(), { width * 0.05 + 15, h }, { 0, 0.5 }, 32, 0, font, { 0,0,0 });
            str.str("");
        }
    }

    i = round(log10(xMax - xMin) - 1);
    s = pow(10, i);
    for (int x = round(xMin / s); x <= round(xMax / s); x++)
    {
        h = width * 0.1 + 0.8 * width * (x * s - xMin) / (xMax - xMin);
        if (h > 0.05 * width && h < 0.95 * width)
        {
            cap = new Capsule({ h, height * 0.05 }, { h, height * 0.05 + 10 }, 1, lable);
            draw(*cap);
            delete cap;
            str << fixed << setprecision(-i > 0 ? -i : 0) << x * s;
            addText(str.str(), { h, height * 0.05 - 5 }, { 0.5, 1 }, 32, 0, font, { 0,0,0 });
            str.str("");
        }
    }

    for (int i = 0; i < points - 1; i++)
    {
        x1 = 0.1 * width + i * 0.8 * width / (points - 1);
        y1 = ys * data[i] + yd;
        x2 = 0.1 * width + (i + 1) * 0.8 * width / (points - 1);
        y2 = ys * data[i + 1] + yd;
        cap = new Capsule({ x1, y1 }, { x2, y2 }, lwidth / 2, attr);
        draw(*cap);
        delete cap;
    }
}
   
Image::Image(uint32_t width, uint32_t height)
{
    this->width = width;
    this->height = height;
    data = new Color[width * height];
    for (int i = 0; i < width * height; i++)
        data[i].rgba(0, 0, 0, 0);
}

Image::Image(string str, Font& font, Color color)
{
    width = 0;
    this->height = font.getHeight();
    for (int i = 0; i < str.length(); i++)
        width += font[str[i]].width;
    data = new Color[width * height];
    for (int i = 0; i < width * height; i++)
        data[i].rgba(0, 0, 0, 0);
    int temp = 0;
    for (int i = 0; i < str.length(); i++)
    {
        for (int j = 0; j < height; j++)
            for (int k = 0; k < font[str[i]].width; k++)
                if (font[str[i]].data[j * font[str[i]].width + k])
                    overliePixel(k + temp, height - j - 1, color);
        temp += font[str[i]].width;
    }
}

Image::Image(Image& I)
{
    width = I.width;
    height = I.height;
    data = new Color[width * height];
    for (int i = 0; i < width * height; i++)
        data[i] = I.data[i];
}

Image::Image(Image&& I)
{
    width = I.width;
    height = I.height;
    data = I.data;
    I.data = NULL;
}

Image::~Image()
{
    delete[] data;
}

Image& Image::operator=(Image& I)
{
    delete[] data;
    width = I.width;
    height = I.height;
    data = new Color[width * height];
    for (int i = 0; i < width * height; i++)
        data[i] = I.data[i];
    return *this;
}

Image& Image::operator=(Image&& I)
{
    delete[] data;
    width = I.width;
    height = I.height;
    data = I.data;
    I.data = NULL;
    return *this;
}

void Image::setBackgroundColor(Color color)
{
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            setPixel(x, y, color);
}

void Image::setPixel(uint32_t x, uint32_t y, Color color)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    data[y * width + x] = color;
}

Color Image::getPixel(uint32_t x, uint32_t y)
{
    return data[y * width + x];
}

void Image::overliePixel(uint32_t x, uint32_t y, Color color)
{
    setPixel(x, y, Color::overlie(color, getPixel(x, y)));
}

Image& Image::draw(Figure& s)
{
    Figure::AABBdata b = s.tAABB();
    int xMin = max((int)floor(b.xMin), 0);
    int yMin = max((int)floor(b.yMin), 0);
    int xMax = min((int)ceil(b.xMax), (int)width - 1);
    int yMax = min((int)ceil(b.yMax), (int)height - 1);
    /*for (int u = xMin; u <= xMax; u++)
    {
        setPixel(u, yMin, {0, 255, 0});
        setPixel(u, yMax, {0, 255, 0});
    }
    for (int v = yMin; v <= yMax; v++)
    {
        setPixel(xMin, v, {0, 255, 0});
        setPixel(xMax, v, {0, 255, 0});
    }*/
    Color final;
    double alpha;
    for (int u = xMin; u <= xMax; u++)
        for (int v = yMin; v <= yMax; v++)
        {
            alpha = -s.tSDF({ (double)u, (double)v }) + 0.5;
            alpha = clamp(alpha, 0, 1);
            final.ca(s.getAttribute().color, alpha);
            overliePixel(u, v, final);
        }
    return *this;
}

void Image::plot(double* data, int points, double lwidth, Font& font, Color color)
{
    plot(data, points, 0, points - 1, lwidth, font, color);
}

void Image::plot(function<double(double)> f, double min, double max, int points, double lwidth, Font& font, Color color)
{
    double* data = new double[points];
    for (int i = 0; i < points; i++)
    {
        data[i] = f(min + (max - min) * i / (points - 1));
    }
    plot(data, points, min, max, lwidth, font, color);
    delete[] data;
}

//按宽高缩放图片（可变形）
Image Image::resize(int width, int height, resampling type)
{
    double kx = (double)this->width / width;
    double ky = (double)this->height / height;
    Image res(width, height);
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            res.setPixel(i, j, resample(kx * i + (kx - 1) / 2, ky * j + (ky - 1) / 2, 1 / kx, 1 / ky, type));
    return res;
}

//只按高度缩放图片（不变形）
Image Image::resize(int height, resampling type)
{
    int width = this->width * height / this->height;
    return resize(width, height, type);
}

Image& Image::insert(Image& src, Vector pos, Vector center, double height, double theta, resampling type)
{
    double xMin, xMax, yMin, yMax, u, v;
    double k = src.height / height;
    double width = src.width / k;
    double xL = -center.x * width;
    double xR = (1 - center.x) * width;
    double yT = (1 - center.y) * height;
    double yB = -center.y * height;
    theta = (theta - 360 * floor(theta / 360)) * PI / 180;
    double cos_ = cos(theta);
    double sin_ = sin(theta);
    if (theta < PI / 2)
    {
        xMin = pos.x + xL * cos_ - yT * sin_;
        xMax = pos.x + xR * cos_ - yB * sin_;
        yMin = pos.y + xL * sin_ + yB * cos_;
        yMax = pos.y + xR * sin_ + yT * cos_;
    }
    else if (theta < PI)
    {
        xMin = pos.x + xR * cos_ - yT * sin_;
        xMax = pos.x + xL * cos_ - yB * sin_;
        yMin = pos.y + xL * sin_ + yT * cos_;
        yMax = pos.y + xR * sin_ + yB * cos_;
    }
    else if (theta < 3 * PI / 2)
    {
        xMin = pos.x + xR * cos_ - yB * sin_;
        xMax = pos.x + xL * cos_ - yT * sin_;
        yMin = pos.y + xR * sin_ + yT * cos_;
        yMax = pos.y + xL * sin_ + yB * cos_;
    }
    else
    {
        xMin = pos.x + xL * cos_ - yB * sin_;
        xMax = pos.x + xR * cos_ - yT * sin_;
        yMin = pos.y + xR * sin_ + yB * cos_;
        yMax = pos.y + xL * sin_ + yT * cos_;
    }
    xMin = max(xMin, 0.0);
    yMin = max(yMin, 0.0);
    xMax = min(xMax, this->width - 1.0);
    yMax = min(yMax, this->height - 1.0);
    for (int i = floor(xMin); i <= ceil(xMax); i++)
        for (int j = floor(yMin); j <= ceil(yMax); j++)
        {
            u = center.x * src.width + k * ((i - pos.x) * cos_ + (j - pos.y) * sin_);
            v = center.y * src.height + k * (-(i - pos.x) * sin_ + (j - pos.y) * cos_);
            if (u >= 0 && u < src.width && v >= 0 && v < src.height)
                overliePixel(i, j, src.resample(u, v, 1 / k, 1 / k, type));
        }
    return *this;
}

Image& Image::addText(string str, Vector pos, Vector center, double size, double theta, Font& font, Color color)
{
    Image* text = new Image(str, font, color);
    insert(*text, pos, center, size, theta, NEAREST);
    delete text;
    return *this;
}

Image& Image::addTitle(string str, double size, Font& font, Color color)
{
    addText(str, { width / 2.0, (double)height }, { 0.5, 1 }, size, 0, font, color);
    return *this;
}

//读取BMP文件
Image& Image::readBMP(const char* filename)
{
    delete[] data;
    fstream file(filename, ios::in | ios::binary);
    BMPHead head;
    file.read((char*)&head, 54);

    //暂时支持24位深度不压缩
    if (head.biBitCount != 24 || head.biCompression != 0)
    {
        cout << "Error: unsupported file.\n";
        exit(0);
    }

    //按文件头部的信息创建空间
    this->width = head.biWidth;
    this->height = head.biHeight;
    data = new Color[width * height];

    //读取数据
    int fillNum = (4 - (3 * width) % 4) % 4;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            file.read((char*)&data[i * width + j].blue, 1);
            file.read((char*)&data[i * width + j].green, 1);
            file.read((char*)&data[i * width + j].red, 1);
            data[i * width + j].alpha = 1;
        }
        file.seekg(fillNum, ios::cur);
    }
    file.close();
    return *this;
}

//保存BMP文件
void Image::saveBMP(const char* filename)
{
    //构造文件头
    uint32_t size = width * height * 3 + 54;
    BMPHead head = {
        0x4D42,             //bfType("BM")
        size,               //bfSize
        0x0000,0x0000,      //bfReserved1,2(0)
        0x00000036,         //bfOffBits(54)
        0x00000028,         //biSize(40)
        width,              //biWidth
        height,             //biHeight
        0x0001,             //biPlanes(1)
        0x0018,             //biBitCount(24)
        0x00000000,         //biCompression(0, 无压缩)
        0x00000000,         //biSizeImage(缺省)
        0x00000000,         //biXPelsPerMeter(缺省)
        0x00000000,         //biYPelsPerMeter(缺省)
        0x00000000,         //biClrUsed(0,全部颜色)
        0x00000000          //biClrImportant(0,全部颜色)
    };

    //打开文件
    cout << "Exporting...\n";
    fstream file(filename, ios::out | ios::binary);
    if (!file)
    {
        cout << "Error: File open failed.\n";
        return;
    }

    //写入文件头
    file.write((char*)&head, 54);

    //写入数据
    uint8_t fillBytes[3] = { 0 };
    int fillNum = (4 - (3 * width) % 4) % 4;
    Color final;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            final = Color::overlie(data[i * width + j], { 255, 255, 255 });
            file.write((char*)&final.blue, 1);
            file.write((char*)&final.green, 1);
            file.write((char*)&final.red, 1);
        }
        file.write((char*)fillBytes, fillNum);
    }
    file.close();
}
