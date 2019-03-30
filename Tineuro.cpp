#include "Tineuro.h"
#include "bitmap.h"

// merge sections
#pragma comment(linker,"/SECTION:.text,ERW")
#pragma comment(linker,"/MERGE:.rdata=.text")
#pragma comment(linker,"/MERGE:.data=.text")

int main()
{
	BitMap pic("test.bmp"); // open image
	std::vector<std::vector<size_t>> vecColor = readColorPic(pic); // { (r g b), (r g b) }

	printf("Res %d\n", pic.getWidth() * pic.getHeight());
	printf("All opts %d\n", (pic.getWidth() * pic.getHeight()) << 1);

	Sensor* sensors = new Sensor; // number of sensors equals image resolution
	Assoc* assocs = new Assoc; // number of assocs equals to number all possible options
	React* reacts = new React; // number of reacts equals numbers patterns

	sensors->setColor(vecColor); // sensor perceives pixel color

	//std::cout << sensors.getColor()[0];

	printf("RGB: ");
	for (auto& rgb : sensors->getColor())
		for (auto& value : rgb)
			printf("%d ", value);

	delete sensors;
	delete assocs;
	delete reacts;

	return 0;
}
