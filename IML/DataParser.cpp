#include "DataParser.h"
#include <sstream>
#include <iterator> 
#include <regex>


std::vector<double> DataParser::parseStringToVectorDouble(const std::string& stringElement)
{
	std::vector<double> result;
	std::istringstream iss(stringElement);
	double num;

	while (iss >> num)
	{
		result.push_back(num);
	}

	return result;
}

std::vector<std::string> DataParser::parseStringToVectorString(const std::string& stringElement)
{
	std::stringstream ss(stringElement);

	std::string element;
	std::vector<std::string> result;

	while (ss >> element)
		result.push_back(element);

	return result;
}

double DataParser::parseStringToDouble(const std::string& stringElement)
{
	double result = std::stod(stringElement);

	return result;
}

std::string DataParser::parseDoubleToString(double doubleElement)
{
	std::ostringstream oss;

	oss << doubleElement;

	std::string result = oss.str();

	return result;
}

std::string DataParser::parseVectorStringToString(const std::vector<std::string>& vectorElement)
{
	std::ostringstream oss;

	if (!vectorElement.empty())
	{
		std::copy(vectorElement.begin(), vectorElement.end() - 1,
			std::ostream_iterator<std::string>(oss, " "));

		oss << vectorElement.back();
	}

	return oss.str();
}

std::string DataParser::parseVectorDoubleToString(const std::vector<double>& vectorElement)
{
	std::ostringstream oss;

	if (!vectorElement.empty())
	{
		std::copy(vectorElement.begin(), vectorElement.end() - 1,
			std::ostream_iterator<double>(oss, " "));

		oss << vectorElement.back();
	}

	return oss.str();
}

std::string DataParser::removeQuationMarks(const std::string& stringElement)
{
	std::regex rgx("(\")([^\"]*)(\")");
	std::smatch match;

	std::string result = "";

	if (std::regex_search(stringElement.begin(), stringElement.end(), match, rgx))
		result = match[2];

	return result;
}

std::vector<std::string> DataParser::tagsContent(std::string line)
{
	std::regex rgx("(<)(.+?)(>)");
	std::smatch match;

	std::vector<std::string> tags;

	while (std::regex_search(line, match, rgx))
	{
		tags.push_back(match[2]);
		line = match.suffix();
	}
	return tags;
}

std::string DataParser::createRegexAndReturnTagCommand(const std::string& line, const std::string& frontTag, const std::string& backTag)
{
	std::regex rgx("(<" + frontTag + "[^>]*)(.*)(<" + backTag + ">)");
	std::smatch match;

	std::string resultTag;

	if (std::regex_search(line.begin(), line.end(), match, rgx))
	{
		resultTag = match[0];
	}

	return resultTag;
}

std::string DataParser::createRegexAndReturnElementsBetweenTags(const std::string& line)
{
	std::regex rgx("(>)([-0-9 ]+)(<)");
	std::smatch match;

	std::string elements;

	if (std::regex_search(line.begin(), line.end(), match, rgx))
		elements = match[2];

	return elements;
}

std::string DataParser::replaceStringSubstringWithAnother(std::string line, const std::string& toBeReplaced, std::string replacement)
{
	size_t index = line.find(toBeReplaced, 0);

	if (index - 1 >= 0 && index + 1 + toBeReplaced.length() < line.size())
	{
		if (line.at(index - 1) != '>')
			replacement = " " + replacement;
		if (line.at(index + toBeReplaced.length()) != '<')
			replacement += " ";
	}

	line = std::regex_replace(line, std::regex(toBeReplaced), replacement);

	return line;
}
