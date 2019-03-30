#include "Tineuro.h"
#include "bitmap.h"

int main()
{
	BitMap pic("test.bmp"); // open image
	std::vector<std::vector<size_t>> vecColor = readColorPic(pic); // { (r g b), (r g b) }

	std::cout << "Res " << pic.width() * pic.height() << '\n';
	std::cout << "All opts " << ((pic.width() * pic.height()) << 1) << '\n';

	Sensor sensors; // number of sensors equals image resolution
	Assoc assocs; // number of assocs equals to number all possible options
	React reacts; // number of reacts equals numbers patterns

	sensors.setColor(vecColor); // sensor perceives pixel color

	//std::cout << sensors.getColor()[0];

	std::cout << "RGB: ";
	for (auto& rgb : sensors.getColor())
		for (auto& value : rgb)
			std::cout << value << ' ';

	return 0;
}
