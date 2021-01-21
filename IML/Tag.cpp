#include "Tag.h"
#include <vector>
#include "DataParser.h"
#include "Mapper.h"
#include "Aggregator.h"
#include "Sorter.h"

void Tag::copy(const Tag& other)
{
	this->content = other.content;
	this->name = other.name;
	this->opposite = other.opposite;
}

void Tag::destroy()
{
}

bool Tag::hasAParameter(const std::vector<std::string>& splitted)
{
	if (splitted.size() == 1)
		return false;
	
	std::string textBetweenQuationMarks = DataParser::removeQuationMarks(splitted[1]);

	char* p;
	double converted = std::strtod(textBetweenQuationMarks.c_str(), &p);

	if (splitted.size() == 2)
	{
		if (*p)
			this->stringParameter = textBetweenQuationMarks;
		else
			this->doubleParameter = converted;

		return true;
	}

	return false;
}

Tag::Tag()
{

}

Tag::Tag(std::string content)
{
	this->content = content;
	std::vector<std::string> splitted = DataParser::parseStringToVectorString(content);

	if (hasAParameter(splitted))
	{

		if (splitted[0] == "MAP-INC")
		{
			this->name = "MAP-INC";
			this->opposite = "/MAP-INC";
			this->functionWithStringAndDoubleParam = Mapper::increment;
		}
		else if (splitted[0] == "MAP-MLT")
		{
			this->name = "MAP-MLT";
			this->opposite = "/MAP-MLT";
			this->functionWithStringAndDoubleParam = Mapper::multiply;
		}
		else if (splitted[0] == "SRT-SLC")
		{
			this->name = "SRT-SLC";
			this->opposite = "/SRT-SLC";
			this->functionWithStringAndDoubleParam = Sorter::slice;
		}
		else
		{
			this->name = "SRT-ORD";
			this->opposite = "/SRT-ORD";
			this->functionWithTwoStringsParam = Sorter::order;
		}
	}
	else
	{
		if (content == "AGG-SUM")
		{
			this->name = "AGG-SUM";
			this->opposite = "/AGG-SUM";
			this->functionWithStringParam = Aggregator::aggregateSum;
		}
		else if (content == "AGG-PRO")
		{
			this->name = "AGG-PRO";
			this->opposite = "/AGG-PRO";
			this->functionWithStringParam = Aggregator::aggregateProduct;
		}
		else if (content == "AGG-AVG")
		{
			this->name = "AGG-AVG";
			this->opposite = "/AGG-AVG";
			this->functionWithStringParam = Aggregator::aggregateAverage;
		}
		else if (content == "AGG-FST")
		{
			this->name = "AGG-FST";
			this->opposite = "/AGG-FST";
			this->functionWithStringParam = Aggregator::aggregateFirst;
		}
		else if (content == "AGG-LST")
		{
			this->name = "AGG-LST";
			this->opposite = "/AGG-LST";
			this->functionWithStringParam = Aggregator::aggregateLast;
		}
		else if (content == "SRT-REV")
		{
			this->name = "SRT-REV";
			this->opposite = "/SRT-REV";
			this->functionWithStringParam = Sorter::reverse;
		}
		else if (content == "SRT-DST")
		{
			this->name = "SRT-DST";
			this->opposite = "/SRT-DST";
			this->functionWithStringParam = Sorter::removeDuplicates;
		}
		else if (content == "/AGG-SUM")
		{
			this->name = "/AGG-SUM";
			this->opposite = "AGG-SUM";
		}
		else if (content == "/AGG-PRO")
		{
			this->name = "/AGG-PRO";
			this->opposite = "AGG-PRO";
		}
		else if (content == "/AGG-AVG")
		{
			this->name = "/AGG-AVG";
			this->opposite = "AGG-AVG";
		}
		else if (content == "/AGG-FST")
		{
			this->name = "/AGG-FST";
			this->opposite = "AGG-FST";
		}
		else if (content == "/AGG-LST")
		{
			this->name = "/AGG-LST";
			this->opposite = "AGG-LST";
		}
		else if (content == "/SRT-REV")
		{
			this->name = "/SRT-REV";
			this->opposite = "SRT-REV";
		}
		else if (content == "/SRT-DST")
		{
			this->name = "/SRT-DST";
			this->opposite = "SRT-DST";
		}
		else if (content == "/MAP-INC")
		{
			this->name = "/MAP-INC";
			this->opposite = "MAP-INC";
		}
		else if (content == "/MAP-MLT")
		{
			this->name = "/MAP-MLT";
			this->opposite = "MAP-MLT";
		}
		else if (content == "/SRT-SLC")
		{
			this->name = "/SRT-SLC";
			this->opposite = "SRT-SLC";
		}
		else
		{
			this->name = "/SRT-ORD";
			this->opposite = "SRT-ORD";
		}
	}
}

Tag::Tag(const Tag& other)
{
	this->copy(other);
}

Tag::~Tag()
{

}

Tag& Tag::operator=(const Tag& other)
{
	if (this != &other)
	{
		this->destroy();
		this->copy(other);
	}

	return *this;
}

double Tag::getArgDouble()
{
	return this->doubleParameter;
}

const std::string& Tag::getArgString()
{
	return this->stringParameter;
}

const std::string& Tag::getName()
{
	return this->name;
}

const std::string& Tag::getOpposite()
{
	return this->opposite;
}

const std::function<std::string(std::string)>& Tag::getFuncWithStringParam()
{
	return this->functionWithStringParam;
}

const std::function<std::string(std::string, double)>& Tag::getFuncWithStringAndDoubleParam()
{
	return this->functionWithStringAndDoubleParam;
}

const std::function<std::string(std::string, std::string)>& Tag::getFuncWithTwoStringParam()
{
	return this->functionWithTwoStringsParam;
}

bool Tag::hasAFuncWithStringParam()
{
	return this->functionWithStringParam != nullptr;
}

bool Tag::hasAFuncWithTwoStringParam()
{
	return this->functionWithTwoStringsParam != nullptr;
}

bool Tag::hasAFuncWithStringAndDoubleParam()
{
	return this->functionWithStringAndDoubleParam != nullptr;
}

