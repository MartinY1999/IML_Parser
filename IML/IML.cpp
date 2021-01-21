#include <iostream>
#include "IMLParser.h"
#include "Mapper.h"
#include "DataParser.h"
#include <filesystem>
#include <fstream>

int main()
{
	std::string inputFile, outputFile;
	std::cin >> inputFile;
	std::cin >> outputFile;

	std::ofstream outputFileResult(outputFile);

	std::cout << std::filesystem::current_path().string() << std::endl;

	while (!std::filesystem::exists(inputFile))
	{
		std::cout << "Wrong File Name!" << std::endl;
		std::cin >> inputFile;
	}

	std::ifstream inFile(inputFile);
	std::string line;

	while (std::getline(inFile, line))
	{
		IMLParser* parser = new IMLParser(line);
		std::string result = parser->produceResult();

		outputFileResult << result << std::endl;
	}

	std::cout << "Successfully executed!" << std::endl;
	outputFileResult.close();
}

