#include "Nonogram.h"

Nonogram::Nonogram(int size, std::string kod) : size(size){}

void Nonogram::LoadFromCode(const std::string& code)
{
	kod = code;
	if (size == 5)
	{
		if (kod.size() > 5) {
			for (int i = kod.size() - 5; i != 0; i--)
				kod.pop_back();
			std::cout << "Duljina kod-a prekoracena, ostatak izbacen" << std::endl;
		}
	}
	else if (size == 10)
	{
		if (kod.size() > 20) {
			for (int i = kod.size() - 20; i != 0; i--)
				kod.pop_back();
			std::cout << "Duljina kod-a prekoracena, ostatak izbacen" << std::endl;
		}
	}
	else if (size == 15)
	{
		if (kod.size() > 45) {
			for (int i = kod.size() - 45; i != 0; i--)
				kod.pop_back();
			std::cout << "Duljina kod-a prekoracena, ostatak izbacen" << std::endl;
		}
	}
	Ispis();
}

void Nonogram::Ispis()
{
	std::cout << size << " " << kod << std::endl;
}

int Nonogram::GetSize() const 
{
	return size;
}