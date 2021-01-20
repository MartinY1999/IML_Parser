#pragma once
#include <vector>
#include <string>
#include <set>

class DataParser
{
private:
	DataParser() { }
public:
	static std::vector<double> parseStringToVectorDouble(const std::string& stringElement);
	static std::vector<std::string> parseStringToVectorString(const std::string& stringElement);
	static double parseStringToDouble(const std::string& stringElement);
	static std::string parseDoubleToString(double doubleElement);
	static std::string parseVectorStringToString(const std::vector<std::string>& vectorElement);
	static std::string parseVectorDoubleToString(const std::vector<double>& vectorElement);

	static std::string removeQuationMarks(const std::string& stringElement);
	static std::vector<std::string> tagsContent(std::string line);
	static std::string createRegexAndReturnTagCommand(const std::string& line, const std::string& frontTagContent,
													  const std::string& backTagContent, bool isLast);
	static std::string createRegexAndReturnElementsBetweenTags(const std::string& line);
	static std::string replaceStringSubstringWithAnother(std::string line, const std::string& toBeReplaced, 
													     std::string replacement);
};

