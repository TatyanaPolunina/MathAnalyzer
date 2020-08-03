#include "token.h"

TokenType Token::ParseTokenType(const char typeSym) {
  switch (typeSym) {
    case '(':
      return TokenType::OPEN_BRACKET;
    case ')':
      return TokenType::CLOSED_BRACKET;
    case '+':
      return TokenType::PLUS;
    case '-':
      return TokenType::MINUS;
    case '*':
      return TokenType::MULTIPLY;
    case '/':
      return TokenType::DIVIDE;
    case '^':
      return TokenType::POWER;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return TokenType::NUMBER;
    case '\0':
      return TokenType::END;
    default:
      return TokenType::UNDEFINED;
  }
}
