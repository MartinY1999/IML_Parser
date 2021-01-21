#pragma once
#include <string>
#include <functional>
class Tag
{
private:
	std::string content;
	std::string name;
	std::string opposite;

	std::function<std::string(std::string)> functionWithStringParam = nullptr;
	std::function<std::string(std::string, double)> functionWithStringAndDoubleParam = nullptr;
	std::function<std::string(std::string, std::string)> functionWithTwoStringsParam = nullptr;

	std::string stringParameter = "";
	double doubleParameter = DBL_MIN;

	void copy(const Tag& other);
	void destroy();

	bool hasAParameter(const std::vector<std::string>& splitted);
public:
	Tag();
	Tag(std::string content);
	Tag(const Tag& other);
	~Tag();

	Tag& operator= (const Tag& other);

	double getArgDouble();
	const std::string& getArgString();
	const std::string& getName();
	const std::string& getOpposite();

	const std::function<std::string(std::string)>& getFuncWithStringParam();
	const std::function<std::string(std::string, double)>& getFuncWithStringAndDoubleParam();
	const std::function<std::string(std::string, std::string)>& getFuncWithTwoStringParam();

	bool hasAFuncWithStringParam();
	bool hasAFuncWithTwoStringParam();
	bool hasAFuncWithStringAndDoubleParam();
};

