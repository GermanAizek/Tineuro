#include "Tineuro.h"
#include "bitmap.h"

int main()
{
	std::vector<std::vector<size_t>> vecColor = readColorPic("test.bmp");
	for (auto& px : vecColor)
		for (auto& color : px)
			std::cout << color << ' '; // RGB

	return 0;
}
