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
	IspuniVektor();
}

void Nonogram::Ispis() const
{
	std::cout << size << " " << kod << std::endl;
}

int Nonogram::GetSize() const 
{
	return size;
}

void Nonogram::IspuniVektor()
{
	std::vector<int> tvec(size * size);
	int red, bin_len = 5;									//bin_len, svako slovo odvojeno na komad od 5 bitova
	for (int i = 0; i < kod.size(); i++)
	{
		red = (int)kod[i] - 70;				/////////////////////////////// UVATI DA SE NE BREAKA duzina bin veca od 5 za 5x5 i veca od 20 za 10x10
		if (red > 31 && red < 48)
			red -= 16;

		for (int j = 0; j < bin_len; j++)
		{
			tvec[size * size - (i * bin_len) + j - bin_len] = red % 2;			//ispunjava blokove po 5 obrnuti redoslijedom, od zada
			red /= 2;															// 1 -> 10000 -> reverse() -> 00001
		}																		// 13 -> 11000 10000 -> reverse() -> 00001 00011
	}
	std::reverse(tvec.begin(), tvec.end());
	vec = tvec;
}

void Nonogram::IspisiVektor() const		//test na konzoli
{
	for (int i = 0; i < size * size; i++)
	{
		std::cout << "[" << vec[i] << "]";
		if ((i + 1) % size == 0)
			std::cout << std::endl;
	}
}

std::vector<std::vector<int>> Nonogram::Puzzle()
{
	int vertcnt, horcnt;
	std::vector<int> vertpuzzle;
	std::vector<int> horpuzzle;
	std::vector<std::vector<int>> puzzle;
	for (int row = 0; row < size; row++)
	{
		vertcnt = 0, horcnt = 0;
		for (int col = 0; col < size; col++) 
		{
			if (vec[row * size + col] == 1)
				vertcnt++;
			else if (vertcnt != 0)
			{
				vertpuzzle.push_back(vertcnt);
				vertcnt = 0;
			}

			if(vec[col * size + row] == 1)
				horcnt++;
			else if(horcnt != 0)
			{
				horpuzzle.push_back(horcnt);
				horcnt = 0;
			}
		}
		if(vertcnt != 0)
			vertpuzzle.push_back(vertcnt);
		if(horcnt != 0)
			horpuzzle.push_back(horcnt);
		vertpuzzle.push_back(0);			// 0 = new row or col
		horpuzzle.push_back(0);
	}
	puzzle.push_back(vertpuzzle);
	puzzle.push_back(horpuzzle);
	std::cout << "rows ";							//console ispis
	for (int i = 0; i < puzzle.size(); i++) {
		for (int j = 0; j < puzzle[i].size(); j++) {
			std::cout << puzzle[i][j] << " ";
		}
		std::cout << std::endl << "cols ";
	}
	std::cout << std::endl;
	return puzzle;
}

bool Nonogram::CheckSolution(const std::vector<int>& playerState) const
{
	return vec == playerState;
}