#include "Sorter.h"
#include "DataParser.h"
#include <vector>
#include <algorithm>
#include <set>

std::string Sorter::reverse(std::string elements)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	for (size_t i = 0; i < numbers.size() / 2; i++)
	{
		double temp = numbers[i];
		numbers[i] = numbers[numbers.size() - i - 1];
		numbers[numbers.size() - i - 1] = temp;
	}

	std::string result = DataParser::parseVectorDoubleToString(numbers);

	return result;
}

std::string Sorter::order(std::string elements, std::string orderWay)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	if (orderWay.compare("ASC") == 0)
		std::sort(numbers.begin(), numbers.end());
	else
		std::sort(numbers.begin(), numbers.end(), std::greater<double>());

	std::string result = DataParser::parseVectorDoubleToString(numbers);

	return result;
}

std::string Sorter::slice(std::string elements, double index)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);
	std::vector<double> slicedResult;

	for (size_t i = index; i < numbers.size(); i++)
	{
		slicedResult.push_back(numbers[i]);
	}

	std::string result = DataParser::parseVectorDoubleToString(slicedResult);

	return result;
}

std::string Sorter::removeDuplicates(std::string elements)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);
	
	std::set<double> seen;

	auto newEnd = std::remove_if(numbers.begin(), numbers.end(), [&seen](const double& value)
		{
			if (seen.find(value) != std::end(seen))
				return true;

			seen.insert(value);
			return false;
		});

	numbers.erase(newEnd, numbers.end());

	std::string result = DataParser::parseVectorDoubleToString(numbers);

	return result;
}
