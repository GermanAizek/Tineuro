#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "bitmap.h"

class Sensor
{
	std::vector<size_t> vecColor; // (r g b)

public:
	std::vector<size_t> getColor()
	{
		return vecColor;
	}
};

class Assoc : public Sensor
{
	std::vector<std::vector<size_t>> vecPos; // (x y)

public:
	std::vector<std::vector<size_t>> getPos()
	{
		return vecPos;
	}
};

class React : public Sensor, Assoc
{
	std::vector<std::pair<std::vector<size_t>, std::vector<size_t>>> vecPattern; // (x y) (r g b)

public:
	std::vector<std::pair<std::vector<size_t>, std::vector<size_t>>> getPattern()
	{
		return vecPattern;
	}
};

std::vector<std::vector<size_t>> readColorPic(const char* namefile)
{
	BitMap pic(namefile);
	std::vector<std::vector<size_t>> vecColor;

	//std::cout << "width = " << pic.width() << ", height = " << pic.height() << '\n';

	for (size_t x = 0; x < pic.width(); ++x)
		for (size_t y = 0; y < pic.height(); ++y)
			vecColor.push_back(pic.getPixel(x, y));
	
	return vecColor;
}