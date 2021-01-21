#include "pch.h"
#include "../IML/Aggregator.h"
#include "../IML/DataParser.h"
#include "../IML/IMLParser.h"
#include "../IML/Mapper.h"
#include "../IML/Sorter.h"
#include "../IML/Tag.h"
#include "../IML/Tag.cpp"
#include "../IML/Sorter.cpp"
#include "../IML/Mapper.cpp"
#include "../IML/IMLParser.cpp"
#include "../IML/Aggregator.cpp"
#include "../IML/DataParser.cpp"

class TestEnvironment : public testing::Environment
{
public:
	static Tag* getTag()
	{
		Tag* tag = new Tag("MAP-INC \"1\"");
		return tag;
	}
	
	static IMLParser* getIMLParser()
	{
		IMLParser* iml = new IMLParser("<SRT-DST><SRT-SLC \"3\">57 18 9<MAP-INC \"-3\">4 2 2</MAP-INC>5</SRT-SLC></SRT-DST>");
		return iml;
	}

	virtual void SetUp() {
		getTag();
		getIMLParser();
	}
};

class StructuresDataTest : public ::testing::Test
{
protected:
	Tag* tag;
	IMLParser* iml;

	virtual void SetUp()
	{
		tag = TestEnvironment::getTag();
		iml = TestEnvironment::getIMLParser();
	}
};

TEST_F(StructuresDataTest, tagHasTheCorrectFunction)
{
	bool testState = this->tag->hasAFuncWithStringAndDoubleParam();
	EXPECT_TRUE(testState);
}

TEST_F(StructuresDataTest, produceResultFunctionTest)
{
	std::string result = this->iml->produceResult();

	EXPECT_EQ("1 -1 5", result);
}

TEST_F(StructuresDataTest, aggregateSumFunctionTest)
{
	std::string result = Aggregator::aggregateSum("1 2 3 4 5");

	EXPECT_EQ("15", result);
}

TEST_F(StructuresDataTest, aggregateProductFunctionTest)
{
	std::string result = Aggregator::aggregateProduct("1 2 3 4 5");

	EXPECT_EQ("120", result);
}

TEST_F(StructuresDataTest, aggregateAverageFunctionTest)
{
	std::string result = Aggregator::aggregateAverage("1 2 3 4 5");

	EXPECT_EQ("3", result);
}

TEST_F(StructuresDataTest, aggregateFirstFunctionTest)
{
	std::string result = Aggregator::aggregateFirst("1 2 3 4 5");

	EXPECT_EQ("1", result);
}

TEST_F(StructuresDataTest, aggregateLastFunctionTest)
{
	std::string result = Aggregator::aggregateLast("1 2 3 4 5");

	EXPECT_EQ("5", result);
}

TEST_F(StructuresDataTest, parseStringToVectorDoubleFunctionTest)
{
	std::vector<double> test{ 1, 2, 3, 4, 5 };
	std::vector<double> result = DataParser::parseStringToVectorDouble("1 2 3 4 5");
	
	bool state = true;

	if (test.size() != result.size())
	{
		state = false;
	}
	else
	{
		for (size_t i = 0; i < result.size(); i++)
		{
			if (test[i] != result[i])
			{
				state = false;
				break;
			}
		}
	}

	EXPECT_TRUE(state);
}

TEST_F(StructuresDataTest, parseStringToVectorStringFunctionTest)
{
	std::vector<std::string> test{ "1", "2", "3", "4", "5" };
	std::vector<std::string> result = DataParser::parseStringToVectorString("1 2 3 4 5");

	bool state = true;

	if (test.size() != result.size())
	{
		state = false;
	}
	else
	{
		for (size_t i = 0; i < result.size(); i++)
		{
			if (test[i] != result[i])
			{
				state = false;
				break;
			}
		}
	}

	EXPECT_TRUE(state);
}

TEST_F(StructuresDataTest, parseStringToDoubleFunctionTest)
{
	double test = 10;
	double result = DataParser::parseStringToDouble("10");

	bool state = true;

	if (test != result)
	{
		state = false;
	}

	EXPECT_TRUE(state);
}

TEST_F(StructuresDataTest, parseVectorStringToStringFunctionTest)
{
	std::string test = "1 2 3 4 5";
	std::vector<std::string> testV{ "1", "2", "3", "4", "5" };
	std::string result = DataParser::parseVectorStringToString(testV);

	bool state = true;

	if (test.compare(result) != 0)
	{
		state = false;
	}

	EXPECT_TRUE(state);
}

TEST_F(StructuresDataTest, parseVectorDoubleToStringFunctionTest)
{
	std::string test = "1 2 3 4 5";
	std::vector<double> testV{ 1, 2, 3, 4, 5 };
	std::string result = DataParser::parseVectorDoubleToString(testV);

	bool state = true;

	if (test.compare(result) != 0)
	{
		state = false;
	}

	EXPECT_TRUE(state);
}

TEST_F(StructuresDataTest, removeQuationMarksFunctionTest)
{
	std::string test = "Test";
	std::string result = DataParser::removeQuationMarks("\"Test\"");

	bool state = true;

	if (test.compare(result) != 0)
	{
		state = false;
	}

	EXPECT_TRUE(state);
}

TEST_F(StructuresDataTest, tagsContentFunctionTest)
{
	std::string test = "<SRT-DST>3<AGG-AVG> -2 10</AGG-AVG></SRT-DST>";
	std::vector<std::string> expected = { "SRT-DST", "AGG-AVG", "/AGG-AVG", "/SRT-DST" };
	std::vector<std::string> result = DataParser::tagsContent(test);
	
	bool state = true;

	if (expected.size() != result.size())
	{
		state = false;
	}
	else
	{
		for (size_t i = 0; i < result.size(); i++)
		{
			if (expected[i].compare(result[i]) != 0)
			{
				state = false;
				break;
			}
		}
	}

	EXPECT_TRUE(state);
}

TEST_F(StructuresDataTest, replaceStringSubstringWithAnotherFunctionTest)
{
	std::string line = "<SRT-DST>3<AGG-AVG> -2 10</AGG-AVG></SRT-DST>";
	std::string replacement = "11 5 6";
	std::string tagCommand = "<AGG-AVG> -2 10</AGG-AVG>";
	std::string expected = "<SRT-DST>3 11 5 6</SRT-DST>";

	std::string result = DataParser::replaceStringSubstringWithAnother(line, tagCommand, replacement);

	EXPECT_EQ(expected, result);
}

//...few more should be added

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new TestEnvironment);

	return RUN_ALL_TESTS();
}