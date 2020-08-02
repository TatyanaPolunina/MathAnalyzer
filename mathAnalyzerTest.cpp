#include "gtest/gtest.h"
#include "mathAnalyzer.h"

TEST(MathAnalyzerParsing, parseSimpleSum)
{
    EXPECT_NEAR(4.0, MathAnalyzer::parseValue("2+2"), 0.01);
}


TEST(MathAnalyzerParsing, parseSimpleMultiply)
{
    EXPECT_NEAR(6.0, MathAnalyzer::parseValue("2*3"), 0.01);
}

TEST(MathAnalyzerParsing, parseSimpleMinus)
{
    EXPECT_NEAR(1.0, MathAnalyzer::parseValue("2-1"), 0.01);
}

TEST(MathAnalyzerParsing, parseSimpledDivide)
{
    EXPECT_NEAR(1.5, MathAnalyzer::parseValue("3.0/2.0"), 0.01);
}


TEST(MathAnalyzerParsing, parseSimpledBrackets)
{
    EXPECT_NEAR(1.0, MathAnalyzer::parseValue("(3.0-2.0)"), 0.01);
}


TEST(MathAnalyzerParsing, parseBracketsWithMultiply)
{
    EXPECT_NEAR(30.0, MathAnalyzer::parseValue("(6.0-1.0)*(2.0 + 4)"), 0.01);
}
