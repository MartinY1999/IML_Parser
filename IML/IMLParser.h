#pragma once
#include <list>
#include <string>
#include <stack>
#include "Tag.h"
class IMLParser
{
private:
	std::string line;
	std::list<Tag*> tagsHolder;
	std::vector<Tag*> commandsTags;
	std::vector<std::string> commands;

	void copy(const IMLParser& other);
	void destroy();

	void fillList();
	std::string fillStack();
public:
	static const std::string errorMessage;

	IMLParser();
	IMLParser(const std::string line);
	IMLParser(const IMLParser& other);
	~IMLParser();

	IMLParser& operator= (const IMLParser& other);

	std::string produceResult();
};

