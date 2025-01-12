#pragma once
#include <string>
#include <vector>
#include <iostream>

class Nonogram {
private:
	int size;
	std::string kod;
	std::vector<int> vec;
public:
	Nonogram(int size, std::string kod);

	void LoadFromCode(const std::string& code);

	void Ispis() const;				//Nonogram na konzoli

	int GetSize() const;

	void IspuniVektor();
	void IspisiVektor() const;		//test na konzoli

	std::vector<std::vector<int>> Puzzle();

	bool CheckSolution(const std::vector<int>& playerState) const;
};