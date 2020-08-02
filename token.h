#ifndef TOKEN_H
#define TOKEN_H

enum class TokenType
{
    NUMBER,
    OPEN_BRACKET,
    CLOSED_BRACKET,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    END,
    UNDEFINED
};


class Token
{
public:
    Token(const TokenType token_type, double value = 0)
        : token_type(token_type)
        , value(value)
    {

    }

    bool is_number() const
    {
        return  token_type == TokenType::NUMBER;
    }

    TokenType get_type() const
    {
        return token_type;
    }
    double get_value() const
    {
        return value;
    }

    static TokenType  parse_token_type(const char typeSym);
private:
    TokenType token_type;
    double value;
};


#endif // TOKEN_H
