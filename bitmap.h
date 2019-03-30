#pragma once

class BitMap
{
	unsigned char bmpFileHeader[14];
	size_t pixelArrayOffset;
	unsigned char bmpInfoHeader[40];

	int height;
	int width;
	int bitsPerPixel;

	int rowSize;
	size_t pixelArraySize;

	unsigned char* pixelData;

	char* copyname;
	const char* filename;
public:
	BitMap(const char* filename);
	~BitMap();

	std::vector<size_t> getPixel(int x, int y);

	//void dispPixelData();

	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
};

BitMap::BitMap(const char* filename)
{
	filename = filename;

	std::ifstream inf(filename);
	//FILE* inf = fopen(filename, "r");
	if (!inf.is_open())
	{
		printf("Unable to open file: %s", filename);
	}

	unsigned char a; //unsigned char m_bmpFileHeader[14];
	for (int i = 0; i < 14; i++)
	{
		//fwrite(&a, sizeof(a), 1, inf);
		inf >> std::hex >> a;
		bmpFileHeader[i] = a;
	}

	if (bmpFileHeader[0] != 'B' || bmpFileHeader[1] != 'M')
	{
		printf("Your info header might be different!\nIt should start with 'BM'.\n");
	}

	unsigned char* array_offset_ptr = (unsigned char*)(bmpFileHeader + 10);
	pixelArrayOffset = *array_offset_ptr;

	if (bmpFileHeader[11] != 0 || bmpFileHeader[12] != 0 || bmpFileHeader[13] != 0)
	{
		printf("You probably need to fix something. bmp.h(%d)\n", __LINE__);
	}

	for (int i = 0; i < 40; i++) //unsigned char m_bmpInfoHeader[40];
	{
		//fwrite(&a, sizeof(a), 1, inf);
		inf >> std::hex >> a;
		bmpInfoHeader[i] = a;
	}

	int* width_ptr = (int*)(bmpInfoHeader + 4);
	int* height_ptr = (int*)(bmpInfoHeader + 8);

	width = *width_ptr;
	height = *height_ptr;

	bitsPerPixel = bmpInfoHeader[14];
	if (bitsPerPixel != 24)
	{
		printf("This program is for 24bpp files. Your bmp is not that\n");
	}

	int compressionMethod = bmpInfoHeader[16];
	if (compressionMethod != 0)
	{
		printf("There some compression stuff going on that we might not be able to deal with.\n");
		printf("Comment out offending lines to continue anyways. bpm.h line: %d\n", __LINE__);
	}

	rowSize = int(floor((bitsPerPixel * width + 31.) / 32)) * 4;
	pixelArraySize = rowSize * abs(height);

	pixelData = new unsigned char[pixelArraySize];

	//fseek(inf, m_pixelArrayOffset, SEEK_SET);
	inf.seekg(pixelArrayOffset, std::ios::beg);
	for (size_t i = 0; i < pixelArraySize; i++)
	{
		//fwrite(&a, sizeof(a), 1, inf);
		inf >> std::hex >> a;
		pixelData[i] = a;
	}
}

BitMap::~BitMap()
{
	delete[] pixelData;
}

/*
void BitMap::dispPixelData()
{
	for (int i = 0; i < m_pixelArraySize; i++)
	{
		std::cout << (size_t)m_pixelData[i] << ' ';
	}
	std::cout << '\n';
}
*/

// output is in rgb order
std::vector<size_t> BitMap::getPixel(int x, int y)
{
	if (x < width && y < height)
	{
		std::vector<size_t> v;
		v.push_back(0);
		v.push_back(0);
		v.push_back(0);

		y = height - 1 - y; // to flip things
		v[0] = (size_t)(pixelData[rowSize*y + 3 * x + 2]); // red
		v[1] = (size_t)(pixelData[rowSize*y + 3 * x + 1]); // greed
		v[2] = (size_t)(pixelData[rowSize*y + 3 * x + 0]); // blue

		return v;
	}
	else
		printf("BAD INDEX\nX: %d Y: %d", x, y);
		//std::cerr << "BAD INDEX\n"; std::cerr << "X: " << x << " Y: " << y << "\n";
}