#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "token.h"
#include <iostream>
#include <optional>

class TokenStream
{
public:
    TokenStream(std::basic_iostream<char>& input_stream);

    Token get_next_token();

    void put_token_back(const Token& latest_token);

    int get_current_stream_pos() const;

    bool full_stream_parsed() const;
private:
    std::basic_iostream<char>& input_stream;
    std::optional<Token> latest_token;
};

#endif // TOKENSTREAM_H
