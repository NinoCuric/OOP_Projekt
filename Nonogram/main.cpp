#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Window.h"
#include "Nonogram.h"






int main()
{
	std::cout << "Creating Window\n";

	Window* pWindow = new Window();

	bool running = true;
	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			std::cout << "Closing Window\n";
			running = false;
		}

		Sleep(20);
	}

	delete pWindow;
	return 0;
}