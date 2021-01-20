#include "IMLParser.h"
#include "DataParser.h"
#include <vector>

const std::string IMLParser::errorMessage = "Error Processing Line!";

void IMLParser::copy(const IMLParser& other)
{
	this->line = other.line;
	
	for (auto const& element : other.tagsHolder)
		this->tagsHolder.push_back(element);

	for (size_t i = 0; i < other.commandsTags.size(); i++)
	{
		Tag* current = new Tag();
		*current = *other.commandsTags[i];
	}

	for (size_t i = 0; i < other.commands.size(); ++i)
		this->commands.push_back(other.commands[i]);
}

void IMLParser::destroy()
{
	while (!this->tagsHolder.empty())
	{
		delete this->tagsHolder.front();
		this->tagsHolder.pop_front();
	}

	for (size_t i = 0; i < this->commandsTags.size(); i++)
		delete this->commandsTags[i];
}

void IMLParser::fillList()
{
	std::vector<std::string> tagsContent = DataParser::tagsContent(this->line);

	if (tagsContent.size() == 0)
		return;
	else
	{
		for (size_t i = 0; i < tagsContent.size(); i++)
		{
			Tag* currentTag = new Tag(tagsContent[i]);

			this->tagsHolder.push_back(currentTag);
		}
	}
}

std::string IMLParser::fillStack()
{
	if (this->tagsHolder.size() == 0)
		return " Line is empty!";
	else 
	{
		std::list<Tag*>::const_iterator it = this->tagsHolder.begin();

		for (size_t i = 0; i < this->tagsHolder.size() / 2; i++)
			++it;

		std::string lastTagName = (*it)->getName();
		std::string tagCommand = "";

		while (this->tagsHolder.size() != 0)
		{
			if (this->tagsHolder.front()->getName().compare(lastTagName) == 0)
				tagCommand = DataParser::createRegexAndReturnTagCommand(this->line, this->tagsHolder.front()->getName(), this->tagsHolder.front()->getOpposite(), true);
			if (this->tagsHolder.front()->getOpposite().compare(this->tagsHolder.back()->getName()) == 0)
				tagCommand = DataParser::createRegexAndReturnTagCommand(this->line, this->tagsHolder.front()->getName(), this->tagsHolder.front()->getOpposite(), false);
			else
				return " Tags are not in the right order!";

			this->commands.push_back(tagCommand);

			Tag* front = this->tagsHolder.front();
			Tag* back = this->tagsHolder.back();

			this->commandsTags.push_back(front);

			this->tagsHolder.pop_front();
			this->tagsHolder.pop_back();

			//delete front, back;
		}
	}

	return "";
}

IMLParser::IMLParser()
{

}

IMLParser::IMLParser(const std::string line)
{
	this->line = line;
}

IMLParser::IMLParser(const IMLParser& other)
{
	this->copy(other);
}

IMLParser::~IMLParser()
{
	this->destroy();
}

IMLParser& IMLParser::operator=(const IMLParser& other)
{
	if (this != &other)
	{
		this->destroy();
		this->copy(other);
	}

	return *this;
}

std::string IMLParser::produceResult()
{
	//go throug each command Tag (looping)
	//create something like C# Func so you can call the action by the tag name
	//replace the original command string in the next command with the result string 
	//repeat until the stack has zero elements
	//return the final command string refactored to the final result
	fillList();
	std::string message = fillStack();

	if (message != "")
	{
		return this->errorMessage + message;
	}

	std::string result;

	while (!this->commands.empty())
	{
		std::string currentCommand = this->commands.back();
		std::string elements = DataParser::createRegexAndReturnElementsBetweenTags(currentCommand);

		Tag* currentTag = this->commandsTags.back();

		if (currentTag->hasAFuncWithTwoStringParam())
		{
			std::string parameter = currentTag->getArgString();

			elements = currentTag->getFuncWithTwoStringParam()(elements, parameter);
		}
		else if (currentTag->hasAFuncWithStringAndDoubleParam())
		{
			double parameter = currentTag->getArgDouble();

			elements = currentTag->getFuncWithStringAndDoubleParam()(elements, parameter);
		}
		else
			elements = currentTag->getFuncWithStringParam()(elements);

		this->commands.pop_back();
		this->commandsTags.pop_back();

		delete currentTag;

		if (!this->commands.empty())
		{
			for (size_t i = 0; i < this->commands.size(); i++)
			{
				this->commands[i] = DataParser::replaceStringSubstringWithAnother(this->commands[i], currentCommand, elements);
			}
		}
		else
			result = elements;
	}

	return result;
}