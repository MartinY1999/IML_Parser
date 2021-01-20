#include "Aggregator.h"
#include <vector>
#include "DataParser.h"

std::string Aggregator::aggregateSum(std::string elements)
{
	double sum = 0;
	std::string result;

	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	for (size_t i = 0; i < numbers.size(); i++)
	{
		sum += numbers[i];
	}

	result = DataParser::parseDoubleToString(sum);

	return result;
}

std::string Aggregator::aggregateProduct(std::string elements)
{
	double multiplication = 1;
	std::string result;

	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	for (size_t i = 0; i < numbers.size(); i++)
	{
		multiplication *= numbers[i];
	}

	result = DataParser::parseDoubleToString(multiplication);

	return result;
}

std::string Aggregator::aggregateAverage(std::string elements)
{
	double sum = 0;
	std::string result;

	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	for (size_t i = 0; i < numbers.size(); i++)
	{
		sum += numbers[i];
	}


	result = DataParser::parseDoubleToString(sum / numbers.size());

	return result;
}

std::string Aggregator::aggregateFirst(std::string elements)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);
	
	std::string result = DataParser::parseDoubleToString(numbers[0]);

	return result;
}

std::string Aggregator::aggregateLast(std::string elements)
{
	std::vector<double> numbers = DataParser::parseStringToVectorDouble(elements);

	std::string result = DataParser::parseDoubleToString(numbers[numbers.size() - 1]);

	return result;
}
