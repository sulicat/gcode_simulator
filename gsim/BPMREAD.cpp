#include <iostream>
#include <fstream>
#include <vector>

#include <cstdio>



typedef unsigned char byte;

#pragma pack(2)
struct BITMAPHEADER
{
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffsetBits;
};
#pragma pack()

struct BITMAPINFOHEADER
{
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount; // Bits per pixel
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};

void printBITMAPHEADER(const BITMAPHEADER b)
{
	std::cout << "Signature:" << std::hex << b.bfType <<std::endl;

	std::cout << "File Size:" << std::dec<<b.bfSize << std::endl;

	std::cout << "Reserved:" << b.bfReserved1 << " " << b.bfReserved2 << std::endl;

	std::cout << "File Offset to PixelArray:" << b.bfOffsetBits <<std::endl;
}

void printBITMAPINFOHEADER(const BITMAPINFOHEADER b)
{
	std::cout << std::dec << "Size of Header: " << b.biSize << std::endl;
	std::cout << "Width: " << b.biWidth << std::endl;
	std::cout << "Height: " << b.biHeight << std::endl;
	std::cout << "Planes: " << b.biPlanes << std::endl;
	std::cout << "Bits per Pixel: " << b.biBitCount << std::endl;
	std::cout << "Compression: " << b.biCompression << std::endl;
	std::cout << "Size of Image Data: " << b.biSizeImage << std::endl;
	std::cout << "XPixels per metre: " << b.biXPelsPerMeter << std::endl;
	std::cout << "YPixels per metre: " << b.biYPelsPerMeter << std::endl;
	std::cout << "Number of Colors Used: " << b.biClrUsed << std::endl;
	std::cout << "Number of Important Colors: " << b.biClrImportant << std::endl;
}

#define BF_TYPE 0x424D

struct ColorARGB
{
	byte alpha;
	byte red;
	byte green;
	byte blue;
};

struct ColorRGB
{
	byte red;
	byte green;
	byte blue;
};

class BMPRGB
{
	std::vector<std::vector<ColorRGB> > colorarray;
public:
	BMPRGB(const char*,BITMAPHEADER, BITMAPINFOHEADER);
	BMPRGB(){}
	~BMPRGB(){}
	
};

class BMPARGB
{
	std::vector<std::vector<ColorARGB> > colorarray;
public:
	BMPARGB(const char*,BITMAPHEADER, BITMAPINFOHEADER);
	BMPARGB(){}
	~BMPARGB(){}
	ColorARGB get(int, int);
	void print();
};
enum COLORMODE
{
	ARGB = 32, RGB = 24
};

class BMP
{
	COLORMODE colormode;
	BMPARGB argbmode;
	BMPRGB rgbmode;
public:
	BMP(const char*);
	~BMP(){}
	void print();
	ColorARGB argbColorAt(int, int);
	ColorRGB rgbColorAt(int, int);
};



//Main.cpp



int main(int argc, char const *argv[])
{
	if(argc < 2)
	{
		std::cerr << "Input the file name.\n";
		return 0;
	}

	std::cout << "Reading " << argv[1] << std::endl;

	BMP bmp(argv[1]);
	
	bmp.print();


	return 0;
}

BMPARGB::BMPARGB(const char *name, BITMAPHEADER bf, BITMAPINFOHEADER bi)
{
	FILE *f = fopen(name, "rb");
	for (int i = 0; i < bf.bfOffsetBits; ++i)fgetc(f);

	char* pad = new char[5];

	for(int j = 0; j < bi.biHeight; ++j)
	{
		std::vector<ColorARGB> v;
		ColorARGB c;
		for (int i = 0; i < bi.biWidth; ++i)
		{
			fread(&c, sizeof(ColorARGB),1,f);
			v.push_back(c);
		}
		int padding = (4-((bi.biBitCount/8)%4))%4;
		fread(pad, padding, 1, f);
		colorarray.push_back(v);
	}
	fclose(f);
}

ColorARGB BMPARGB::get(int x, int y)
{
	return colorarray[x][y];
}

void BMPARGB::print()
{
	for (std::vector<std::vector<ColorARGB> >::iterator i = colorarray.begin(); i != colorarray.end(); ++i)
	{
		std::vector<ColorARGB> v = *i;
		for (std::vector<ColorARGB>::iterator j = v.begin(); j != v.end(); ++j)
		{
			ColorARGB c = *j;
			std::cout << std::hex << "A:" << (unsigned int)c.alpha << " R:" << (unsigned int)c.red << " G:" << (unsigned int)c.green << " B:" << (unsigned int)c.blue << std::endl;
		}
	}
}

BMPRGB::BMPRGB(const char *name, BITMAPHEADER bf, BITMAPINFOHEADER bi)
{
	FILE *f = fopen(name, "rb");
	for (int i = 0; i < bf.bfOffsetBits; ++i)fgetc(f);

	char* pad = new char[5];

	for(int j = 0; j < bi.biHeight; ++j)
	{
		std::vector<ColorRGB> v;
		ColorRGB c;
		for (int i = 0; i < bi.biWidth; ++i)
		{
			fread(&c, sizeof(ColorRGB),1,f);
			v.push_back(c);
		}
		int padding = (4-((bi.biBitCount/8)%4))%4;
		fread(pad, padding, 1, f);
		colorarray.push_back(v);
	}

	fclose(f);
}

BMP::BMP(const char *name)
{
	BITMAPHEADER bmp = *(new BITMAPHEADER);
	BITMAPINFOHEADER bi = *(new BITMAPINFOHEADER);

	FILE *f = fopen(name, "rb");

	fread(&bmp, sizeof(BITMAPHEADER), 1, f);
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, f);

	colormode = (COLORMODE)bi.biBitCount;

	switch(colormode)
	{
		case ARGB:
			argbmode = BMPARGB(name, bmp, bi);
			break;
		case RGB:
			rgbmode = BMPRGB(name, bmp, bi);
			break;
	}

	printBITMAPHEADER(bmp);
	printBITMAPINFOHEADER(bi);

	fclose(f);
}

ColorARGB BMP::argbColorAt(int x, int y)
{
	return argbmode.get(x,y);
}

ColorRGB BMP::rgbColorAt(int, int)
{

}

void BMP::print()
{
	if(colormode == ARGB)
	{
		argbmode.print();
	}
}