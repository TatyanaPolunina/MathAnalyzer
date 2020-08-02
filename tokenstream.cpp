#include "tokenstream.h"

TokenStream::TokenStream(std::iostream& input_stream)
    : input_stream(input_stream)
{

}

Token TokenStream::get_next_token()
{
    if (latest_token)
    {
        Token result = *latest_token;
        latest_token.reset();
        return result;
    }

    char ch;
    input_stream >> ch;
    TokenType token_type = Token::parse_token_type(ch);
    if (token_type == TokenType::NUMBER)
    {
        input_stream.putback(ch);
        double val;
        input_stream >> val;
        return Token(TokenType::NUMBER, val);
    }
    return Token(token_type);
}

void TokenStream::put_token_back(const Token &latest_token)
{
    this->latest_token = latest_token;
}
