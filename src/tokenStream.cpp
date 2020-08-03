#include "tokenStream.h"
#include "sstream"

TokenStream::TokenStream(std::iostream& input_stream)
    : input_stream_(input_stream) {}

Token TokenStream::GetNextToken() {
  if (latest_token_) {
    Token result = *latest_token_;
    latest_token_.reset();
    return result;
  }

  char ch;
  input_stream_ >> ch;
  TokenType token_type = Token::ParseTokenType(ch);
  if (token_type == TokenType::UNDEFINED) {
    std::stringstream err_msg;
    err_msg << "Incorrect token input in expression " << ch;
    throw std::invalid_argument(err_msg.str());
  }
  if (token_type == TokenType::NUMBER) {
    input_stream_.putback(ch);
    double val;
    input_stream_ >> val;
    return Token(TokenType::NUMBER, val);
  }
  return Token(token_type);
}

void TokenStream::PutTokenBack(const Token& latest_token) {
  if (this->latest_token_) {
    throw std::invalid_argument(
        "Double buffer receiving. Looks like incorrect input");
  }
  this->latest_token_ = latest_token;
}

int TokenStream::GetCurrentStreamPos() const { return input_stream_.tellg(); }

bool TokenStream::FullStreamParsed() const {
  return (!latest_token_ || latest_token_->GetType() == TokenType::END) &&
         !input_stream_.rdbuf()->in_avail();
}
