#include "../include/mathAnalyzer.h"
#include "expression.h"
#include "tokenStream.h"

class ExpressionParser {
 public:
  ExpressionParser(TokenStream &token_stream);
  /*
   * Throw invalid_argument in case expression is not valid
   */
  std::unique_ptr<Expression> ParseExpressionFromStream();

 private:
  std::unique_ptr<Expression> ParseExpression();
  std::unique_ptr<Expression> ParsePrimary();
  std::unique_ptr<Expression> ParseTerm();
  /// for highest priority operation: like power
  std::unique_ptr<Expression> ParsePriorityTerm();
  void ThrowInvalidArgException(const std::string &msg, int stream_pos);

 private:
  TokenStream token_stream_;
};

ExpressionParser::ExpressionParser(TokenStream &token_stream)
    : token_stream_(token_stream) {}

std::unique_ptr<Expression> ExpressionParser::ParseExpressionFromStream() {
  auto expression = ParseExpression();
  if (!token_stream_.FullStreamParsed()) {
    ThrowInvalidArgException("Unexpected end of expression",
                             token_stream_.GetCurrentStreamPos());
  }
  return expression;
}

std::unique_ptr<Expression> ExpressionParser::ParseExpression() {
  std::unique_ptr<Expression> left = ParseTerm();
  Token t = token_stream_.GetNextToken();

  while (true) {
    std::unique_ptr<Expression> right = nullptr;
    if (t.GetType() == TokenType::PLUS) {
      right = ParseTerm();

    } else if (t.GetType() == TokenType::MINUS) {
      right = std::make_unique<NegativeExpression>(ParseTerm());
    }

    if (right) {
      left = std::make_unique<SumExpression>(std::move(left), std::move(right));
      t = token_stream_.GetNextToken();
    } else {
      token_stream_.PutTokenBack(t);
      return left;
    }
  }
}

std::unique_ptr<Expression> ExpressionParser::ParsePrimary() {
  Token t = token_stream_.GetNextToken();
  if (t.GetType() == TokenType::OPEN_BRACKET) {
    auto brackets_position = token_stream_.GetCurrentStreamPos() - 1;
    auto expr = ParseExpression();
    t = token_stream_.GetNextToken();
    if (t.GetType() != TokenType::CLOSED_BRACKET) {
      ThrowInvalidArgException(
          "Your expression contains no closed bracket, open bracket",
          brackets_position);
    }
    return expr;
  }
  if (t.GetType() == TokenType::NUMBER) {
    return std::make_unique<NumericExpression>(t.GetValue());
  }
  if (t.GetType() == TokenType::MINUS) {
    return std::make_unique<NegativeExpression>(ParsePrimary());
  }

  auto err_pos = std::max(0, token_stream_.GetCurrentStreamPos() - 1);
  ThrowInvalidArgException(
      "Your string is not valid math expression. Incorrect sym.", err_pos);
  return nullptr;
}

std::unique_ptr<Expression> ExpressionParser::ParseTerm() {
  auto left = ParsePriorityTerm();
  Token t = token_stream_.GetNextToken();

  while (true) {
    if (t.GetType() == TokenType::MULTIPLY) {
      left = std::make_unique<MultipleExpression>(std::move(left),
                                                  ParsePriorityTerm());
      t = token_stream_.GetNextToken();
    } else if (t.GetType() == TokenType::DIVIDE) {
      left = std::make_unique<DivisionExpression>(std::move(left),
                                                  ParsePriorityTerm());
      t = token_stream_.GetNextToken();
    } else {
      token_stream_.PutTokenBack(t);
      return left;
    }
  }
}

std::unique_ptr<Expression> ExpressionParser::ParsePriorityTerm() {
  auto left = ParsePrimary();
  Token t = token_stream_.GetNextToken();
  while (true) {
    if (t.GetType() == TokenType::POWER) {
      left = std::make_unique<PowerExpression>(std::move(left), ParsePrimary());
      t = token_stream_.GetNextToken();
    } else {
      token_stream_.PutTokenBack(t);
      return left;
    }
  }
}

void ExpressionParser::ThrowInvalidArgException(const std::string &msg,
                                                int stream_pos) {
  std::stringstream error_msg;
  error_msg << msg << " Pos: " << stream_pos;
  throw std::invalid_argument(error_msg.str());
}

double MathAnalyzer::ParseExpression(const std::string &strExpression) {
  std::stringstream expr_stream;
  expr_stream << strExpression << '\0';
  TokenStream token_stream(expr_stream);
  ExpressionParser parser(token_stream);
  auto expression = parser.ParseExpressionFromStream();
  return expression->Value();
}
