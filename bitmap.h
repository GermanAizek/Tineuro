#pragma once

#include <iostream>
#include <vector>
#include <fstream>

class BitMap
{
	unsigned char m_bmpFileHeader[14];
	size_t m_pixelArrayOffset;
	unsigned char m_bmpInfoHeader[40];

	int m_height;
	int m_width;
	int m_bitsPerPixel;

	int m_rowSize;
	int m_pixelArraySize;

	unsigned char* m_pixelData;

	char * m_copyname;
	const char * m_filename;
public:
	BitMap(const char * filename);
	~BitMap();

	std::vector<size_t> getPixel(int x, int y);

	void dispPixelData();

	int width()
	{
		return m_width;
	}
	int height()
	{
		return m_height;
	}
};

BitMap::BitMap(const char* filename)
{
	m_filename = filename;

	std::ifstream inf(filename);
	if (!inf)
	{
		std::cerr << "Unable to open file: " << filename << "\n";
	}

	//unsigned char m_bmpFileHeader[14];
	unsigned char a;
	for (int i = 0; i < 14; i++)
	{
		inf >> std::hex >> a;
		m_bmpFileHeader[i] = a;
	}

	if (m_bmpFileHeader[0] != 'B' || m_bmpFileHeader[1] != 'M')
	{
		std::cerr << "Your info header might be different!\nIt should start with 'BM'.\n";
	}

	size_t* array_offset_ptr = (size_t*)(m_bmpFileHeader + 10);
	m_pixelArrayOffset = *array_offset_ptr;

	if (m_bmpFileHeader[11] != 0 || m_bmpFileHeader[12] != 0 || m_bmpFileHeader[13] != 0)
	{
		std::cerr << "You probably need to fix something. bmp.h(" << __LINE__ << ")\n";
	}

	//unsigned char m_bmpInfoHeader[40];
	for (int i = 0; i < 40; i++)
	{
		inf >> std::hex >> a;
		m_bmpInfoHeader[i] = a;
	}

	int * width_ptr = (int*)(m_bmpInfoHeader + 4);
	int * height_ptr = (int*)(m_bmpInfoHeader + 8);

	m_width = *width_ptr;
	m_height = *height_ptr;

	m_bitsPerPixel = m_bmpInfoHeader[14];
	if (m_bitsPerPixel != 24)
	{
		std::cerr << "This program is for 24bpp files. Your bmp is not that\n";
	}

	int compressionMethod = m_bmpInfoHeader[16];
	if (compressionMethod != 0)
	{
		std::cerr << "There some compression stuff going on that we might not be able to deal with.\n";
		std::cerr << "Comment out offending lines to continue anyways. bpm.h line: " << __LINE__ << "\n";
	}

	m_rowSize = int(floor((m_bitsPerPixel * m_width + 31.) / 32)) * 4;
	m_pixelArraySize = m_rowSize * abs(m_height);

	m_pixelData = new unsigned char[m_pixelArraySize];

	inf.seekg(m_pixelArrayOffset, std::ios::beg);
	for (int i = 0; i < m_pixelArraySize; i++)
	{
		inf >> std::hex >> a;
		m_pixelData[i] = a;
	}
}

BitMap::~BitMap()
{
	delete[] m_pixelData;
}

void BitMap::dispPixelData()
{
	for (int i = 0; i < m_pixelArraySize; i++)
	{
		std::cout << (size_t)m_pixelData[i] << ' ';
	}
	std::cout << '\n';
}

// output is in rgb order
std::vector<size_t> BitMap::getPixel(int x, int y)
{
	if (x < m_width && y < m_height)
	{
		std::vector<size_t> v;
		v.push_back(0);
		v.push_back(0);
		v.push_back(0);

		y = m_height - 1 - y; // to flip things
		v[0] = (size_t)(m_pixelData[m_rowSize*y + 3 * x + 2]); // red
		v[1] = (size_t)(m_pixelData[m_rowSize*y + 3 * x + 1]); // greed
		v[2] = (size_t)(m_pixelData[m_rowSize*y + 3 * x + 0]); // blue

		return v;
	}
	else
		std::cerr << "BAD INDEX\n"; std::cerr << "X: " << x << " Y: " << y << "\n";
}