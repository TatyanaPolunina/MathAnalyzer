#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "token.h"
#include <iostream>
#include <optional>

class TokenStream
{
public:
    TokenStream(std::basic_iostream<char>& input_stream);

    Token GetNextToken();

    void PutTokenBack(const Token& latest_token);

    int GetCurrentStreamPos() const;

    bool FullStreamParsed() const;
private:
    std::basic_iostream<char>& input_stream_;
    std::optional<Token> latest_token_;
};

#endif // TOKENSTREAM_H
