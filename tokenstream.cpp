#include "tokenstream.h"
#include "sstream"

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
    if (token_type == TokenType::UNDEFINED)
    {
        std::stringstream err_msg;
        err_msg << "Incorrect token input in expression " << ch;
        throw std::invalid_argument(err_msg.str());
    }
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
    if (this->latest_token)
    {
        throw  std::invalid_argument("Double buffer receiving. Looks like incorrect input");
    }
    this->latest_token = latest_token;
}

int TokenStream::get_current_stream_pos() const
{
    return input_stream.tellg();
}

bool TokenStream::full_stream_parsed() const
{
    return (!latest_token || latest_token->get_type() == TokenType::END) && !input_stream.rdbuf()->in_avail();
}
