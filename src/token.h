#ifndef TOKEN_H
#define TOKEN_H

enum class TokenType {
  NUMBER,
  OPEN_BRACKET,
  CLOSED_BRACKET,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  POWER,
  END,
  UNDEFINED
};

class Token {
 public:
  Token(const TokenType token_type, double value = 0)
      : token_type_(token_type), value_(value) {}

  bool IsNumber() const { return token_type_ == TokenType::NUMBER; }

  TokenType GetType() const { return token_type_; }
  double GetValue() const { return value_; }

  static TokenType ParseTokenType(const char typeSym);

 private:
  TokenType token_type_;
  double value_;
};

#endif  // TOKEN_H
