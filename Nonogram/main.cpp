#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Window.h"

class Nonogram {
private:
	int size;
//	int matr[10][10];
	std::string kod;
	std::vector<int> vec;
public:

	void velicina(Nonogram& nono)
	{
		size = 0;
		while (size != 5 && size != 10 && size != 15)
		{
			std::cout << "Unesi velicinu, 5 / 10 / 15" << std::endl;
			std::cin >> size;
		}
	}

	void unos_kod(Nonogram& nono)
	{
		if (size == 5)
		{
			std::cout << "Unesi 5x5 kod:" << std::endl;
			std::cin >> kod;
			if (kod.size() > 5) {
				for (int i = kod.size() - 5; i != 0; i--)		
					kod.pop_back();
				std::cout << "Duljina kod-a prekoracena, ostatak izbacen" << std::endl;
			}
		}
		if (size == 10) 
		{
			std::cout << "Unesi 10x10 kod:" << std::endl;
			std::cin >> kod;
			if (kod.size() > 20) {
				for (int i = kod.size() - 20; i != 0; i--)
					kod.pop_back();
				std::cout << "Duljina kod-a prekoracena, ostatak izbacen" << std::endl;
			}
		}
		if (size == 15)
		{
			std::cout << "Unesi 15x15 kod:" << std::endl;
			std::cin >> kod;
			if (kod.size() > 45) {
				for (int i = kod.size() - 45; i != 0; i--)
					kod.pop_back();
				std::cout << "Duljina kod-a prekoracena, ostatak izbacen" << std::endl;
			}
		}
	}

/*	void unoskod5(Nonogram& nono)
	{
		int tkod = kod;
		int col, row;
		for (row = 0; row < nono.size; row++)
		{
			for (col = 0; col < nono.size; col++)
			{
				if (tkod % 2 == 0)
					nono.matr[row][col] = 1;
				else
					nono.matr[row][col] = 0;
				tkod=tkod*2/3;
			}
		}
	}*/

/*	void ispuni_matr(Nonogram& nono)
	{
		
		if (nono.size == 5)		{
			std::cout << "Unesi 5x5 kod:" << std::endl;
			std::cin >> nono.kod;
			unoskod5(nono);
		}
		if (nono.size == 10)	{
			std::cout << "Unesi 10x10 kod:" << std::endl;
			std::cin >> nono.kod;
			unoskod10(nono);
		}
	}*/

/*	void testmatrispuni(Nonogram& nono)
	{
		int col, row, t = 0;
		for (row = 0; row < nono.size; row++)
		{
			for (col = 0; col < nono.size; col++)
			{
				if (t % 2 == 0)
					nono.matr[row][col] = 1;
				else
					nono.matr[row][col] = 0;
				t++;
			}
		}
	}*/

/*	void ispisi_matr(Nonogram nono)
	{
		int col, row, t = 0;
		for (row = 0; row < nono.size; row++)
		{
			for (col = 0; col < nono.size; col++)
			{
				std::cout << "[" << nono.matr[row][col] << "]";
			}
			std::cout << std::endl;
		}
	}*/

	void ispuni_vektor(Nonogram& nono)
	{
		std::vector<int> vec(size * size);
		int red, bin_len = 5;									//bin_len, svako slovo odvojeno na komad od 5 bitova
		for (int i = 0; i < kod.size(); i++)
		{
			red = (int)kod[i] - 70;				/////////////////////////////// UVATI DA SE NE BREAKA duzina bin veca od 5 za 5x5 i veca od 20 za 10x10
			if (red > 31 && red < 48)
				red -= 16;

			for (int j = 0; j < bin_len; j++)
			{
				vec[size * size - (i * bin_len) + j - bin_len] = red % 2;			//ispunjava blokove po 5 obrnuti redoslijedom, od zada
				red /= 2;									// 1 -> 10000 -> reverse() -> 00001
			}											// 13 -> 11000 10000 -> reverse() -> 00001 00011
		}
		std::reverse(vec.begin(), vec.end());
		nono.vec = vec;
	}

	void ispisi_vektor(Nonogram nono) const
	{
		
		for (int i = 0; i < size * size; i++)
		{
			std::cout << "[" << vec[i] << "]";
			if ((i + 1) % size == 0)
				std::cout << std::endl;
		}
	}

};


std::string bin_pretvorba_string()
{
	std::string bin_str;
	std::cout << "Unesi binarni string za pretvorbu u kod" << std::endl;
	std::cin >> bin_str;
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
	return str_kod;
}



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

		//Render

		Sleep(20);
	}

	delete pWindow;


	/*
	Nonogram Nono;
	Nono.velicina(Nono);
	Nono.unos_kod(Nono);
	Nono.ispuni_vektor(Nono);
	Nono.ispisi_vektor(Nono);

	*/
	


	return 0;
}
