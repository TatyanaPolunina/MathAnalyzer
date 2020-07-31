#include "gtest/gtest.h"
#include "mathAnalyzer.h"

TEST(MathAnalyzerParsing, parseEmptyString)
{
    MathAnalyzer analyzer;
    EXPECT_FALSE(analyzer.parseValue(""));
}

