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

	void Ispis();

	int GetSize() const;
};