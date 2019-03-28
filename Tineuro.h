#pragma once

#include <iostream>
#include <vector>
#include "bitmap.h"

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