#include <iostream>
#include "SFML.h"

int main(int argv, char **argc)
{
	if (!argc[1])
	{
		std::cout << "Invalid path\n";
		system("pause");
		return 1;
	}
	
	SFML pixel_viewer(argc[1]);

	while (pixel_viewer.window.isOpen())
	{
		pixel_viewer.user_input();
		pixel_viewer.render();
		pixel_viewer.update();
	}

	return 0;
}
