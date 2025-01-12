#include <cmath>
#include "Window.h"
#include "Nonogram.h"

// funkcionalnost stvaranja kodova

bool bin_space() {
	std::string spaces;
	std::cout << "Unesi binarni string za micanje razmaka" << std::endl;
    std::getline(std::cin, spaces); 
	if ((spaces.size() < 5))		//exit small input
		return false;

    std::string str;
    for (char c : spaces) {
        if (c != ' ') { 
            str += c; 
        }
    }
	std::cout << "String:\n" << str << std::endl;
	return true;
}

bool bin_pretvorba_string()	{
	std::string bin_str;
	std::cout << "Unesi binarni string za pretvorbu u kod" << std::endl;
	std::cin >> bin_str;
	if ((bin_str.size() % 5) != 0)	//exit small input
		return false;

	std::vector<int> bin_vec(bin_str.size());
	for (int i = 0; i < bin_str.size(); i++)
		bin_vec[i] = (int)bin_str[i] - 48;

	int temp;
	std::string str_kod;
	for (int i = 0; i * 5 < bin_str.size(); i++)
	{
		temp = 0;
		for (int j = 0; j < 5; j++)
		{
			temp += bin_vec[i * 5 + j] * pow(2, 4 - j);
		}
		if (temp > 15 && temp < 32)
			temp += 16;
		temp += 70;
		str_kod.push_back((char)temp);
	}
	std::cout << "Kod:\n" << str_kod << std::endl;
	return true;
}


int main()
{
//	while(bin_space());
//	while (bin_pretvorba_string());


	std::cout << "\nCreating Window\n";

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