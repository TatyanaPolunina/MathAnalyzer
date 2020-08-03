#include "gtest/gtest.h"
#include "../include/mathAnalyzer.h"

TEST(MathAnalyzerParsing, parseSimpleSum) {
  EXPECT_NEAR(4.0, MathAnalyzer::ParseExpression("2+2"), 0.01);
}

TEST(MathAnalyzerParsing, parseSimpleMultiply) {
  EXPECT_NEAR(6.0, MathAnalyzer::ParseExpression("2*3"), 0.01);
}

TEST(MathAnalyzerParsing, parseIncorrectSameSigns) {
  EXPECT_THROW(MathAnalyzer::ParseExpression("2++3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("2**3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("2//3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2)++3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2++3)"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2++)3"), std::invalid_argument);
}

TEST(MathAnalyzerParsing, parseIncorrectDifferentSigns) {
  EXPECT_THROW(MathAnalyzer::ParseExpression("2+*3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("2*+3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("2/*3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2-+3"), std::invalid_argument);
  EXPECT_THROW(MathAnalyzer::ParseExpression("2-*3"), std::invalid_argument);
}

TEST(MathAnalyzerParsing, parseSimpleMinus) {
  EXPECT_NEAR(1.0, MathAnalyzer::ParseExpression("2-1"), 0.01);
}

TEST(MathAnalyzerParsing, parseSimpledDivide) {
  EXPECT_NEAR(1.5, MathAnalyzer::ParseExpression("3.0 / 2.0"), 0.01);
}

TEST(MathAnalyzerParsing, parseSimpledBrackets) {
  EXPECT_NEAR(1.0, MathAnalyzer::ParseExpression("(3.0-2.0)"), 0.01);
}

TEST(MathAnalyzerParsing, parseBracketsWithMultiply) {
  EXPECT_NEAR(30.0, MathAnalyzer::ParseExpression("(6.0-1.0)*(2.0 + 4)"), 0.01);
}

TEST(MathAnalyzerParsing, parseBracketsWithSum) {
  EXPECT_NEAR(10.0, MathAnalyzer::ParseExpression("(6.0*2.0)-(4.0 / 2)"), 0.01);
}

TEST(MathAnalyzerParsing, parseIncorrectBracketsWithSum) {
  EXPECT_THROW(MathAnalyzer::ParseExpression("(6.0*2.0)-4.0() / 2"),
               std::invalid_argument);
}

TEST(MathAnalyzerParsing, parseExpressionWithCorrectTrim) {
  EXPECT_NEAR(1.5, MathAnalyzer::ParseExpression("   3.0 / 2.0  "), 0.01);
}

TEST(MathAnalyzerParsing, parseUnaryMinus) {
  EXPECT_NEAR(-5.0, MathAnalyzer::ParseExpression("-2-3"), 0.01);
}

TEST(MathAnalyzerParsing, parseUnaryMinusWithBinary) {
  EXPECT_NEAR(1, MathAnalyzer::ParseExpression("-2--3"), 0.01);
}

TEST(MathAnalyzerParsing, parseUnaryMinusWithBrackets) {
  EXPECT_NEAR(-5.0, MathAnalyzer::ParseExpression("-(6.0-1.0)"), 0.01);
}

TEST(MathAnalyzerParsing, parseDoubleBrackets) {
  EXPECT_NEAR(125, MathAnalyzer::ParseExpression("(65 + (32*2) -4)"), 0.01);
}

TEST(MathAnalyzerParsing, parseBracketsIncorrectNumber) {
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2+((6.0-1.0))"),
               std::invalid_argument);
}

TEST(MathAnalyzerParsing, parseBracketsIncorrectNumberAtTheEnd) {
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2+6.0-1.0))"),
               std::invalid_argument);
}

TEST(MathAnalyzerParsing, parseIncorrectInput) {
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2+fd"), std::invalid_argument);
}

TEST(MathAnalyzerParsing, parseEmptyString) {
  EXPECT_THROW(MathAnalyzer::ParseExpression(""), std::invalid_argument);
}

TEST(MathAnalyzerParsing, parseExpressionWithSpaces) {
  EXPECT_NEAR(-5.0, MathAnalyzer::ParseExpression("-( 6.0 - 1.0)"), 0.01);
}

TEST(MathAnalyzerParsing, parseExpressionWithSpacesAndSeveralTypesOfExpr) {
  EXPECT_NEAR(
      -26.0, MathAnalyzer::ParseExpression("-( 6.0 - 1.0 ) * 4 - 2 * 3"), 0.01);
}

TEST(MathAnalyzerParsing, parseDevisionByZeroCase) {
  EXPECT_THROW(MathAnalyzer::ParseExpression("(2+5) / (9 - 3 * 3)"),
               std::runtime_error);
}
