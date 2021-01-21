#pragma once
#include <string>
class Mapper
{
private:
	Mapper() { }
public:
	static std::string increment(std::string elements, double number);
	static std::string multiply(std::string elements, double number);
};

