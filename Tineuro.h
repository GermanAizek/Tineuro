#pragma once

#include <vector>
#include <fstream>
#include "bitmap.h"

using Vector2_SizeT = std::vector<std::vector<size_t>>;
using VectorPair2_SizeT = std::vector<std::pair<std::vector<size_t>, std::vector<size_t>>>;

class Sensor
{
	Vector2_SizeT vecColor; // (r g b)
	std::vector<Sensor> elements;

public:
	Vector2_SizeT getColor()
	{
		return vecColor;
	}
	void setColor(Vector2_SizeT color)
	{
		vecColor = std::move(color);
	}

	/*
	std::vector<Sensor> get()
	{
		return elements;
	}

	size_t getSize()
	{
		return elements.size();
	}
	*/
};

class Assoc : public Sensor
{
	Vector2_SizeT vecPos; // (x y)
	std::vector<Assoc> elements;

public:
	Vector2_SizeT getPos()
	{
		return vecPos;
	}
	void setPos(Vector2_SizeT pos)
	{
		vecPos = std::move(pos);
	}

	/*
	std::vector<Assoc> get()
	{
		return elements;
	}
	*/
};

class React : public Sensor, Assoc
{
	VectorPair2_SizeT vecPattern; // (x y) (r g b)
	std::vector<React> elements;

public:
	VectorPair2_SizeT getPattern()
	{
		return vecPattern;
	}
	void setPattern(VectorPair2_SizeT pattern)
	{
		vecPattern = std::move(pattern);
	}

	/*
	std::vector<React> get()
	{
		return elements;
	}
	*/
};

Vector2_SizeT readColorPic(BitMap& pic)
{
	Vector2_SizeT vecColor;
	for (size_t x = 0; x < pic.width(); ++x)
		for (size_t y = 0; y < pic.height(); ++y)
			vecColor.push_back(pic.getPixel(x, y));
	
	return vecColor;
}