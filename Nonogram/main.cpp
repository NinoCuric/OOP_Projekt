#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Window.h"
#include "Nonogram.h"

//to do
//Victory text between back button and submit, also all empty tiles fill X's/2nd color
//make .exe
// add X on right click, changes color to white and adds vector of X's
// TUtorial button and premade levels
//change background color and/or add image
//cleanup code if possible
//in main, bit to kod converter

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