#include "Mapper.h"
#include <vector>
#include "DataParser.h"

std::string Mapper::increment(std::string elements, double number)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	for (size_t i = 0; i < numbers.size(); i++)
		numbers[i] += number;

	std::string result = DataParser::parseVectorDoubleToString(numbers);

	return result;
}

std::string Mapper::multiply(std::string elements, double number)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	for (size_t i = 0; i < numbers.size(); i++)
		numbers[i] *= number;

	std::string result = DataParser::parseVectorDoubleToString(numbers);

	return result;
}
