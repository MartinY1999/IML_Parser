#pragma once
#include <string>
class Aggregator
{
private:
	Aggregator() { }
public:
	static std::string aggregateSum(std::string elements);
	static std::string aggregateProduct(std::string elements);
	static std::string aggregateAverage(std::string elements);
	static std::string aggregateFirst(std::string elements);
	static std::string aggregateLast(std::string elements);
};

