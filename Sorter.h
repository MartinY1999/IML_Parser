#pragma once
#include <string>
class Sorter
{
private:
	Sorter() { }
public:
	static std::string reverse(std::string elements);
	static std::string order(std::string elements, std::string orderWay);
	static std::string slice(std::string elements, double index);
	static std::string removeDuplicates(std::string elements);
};

