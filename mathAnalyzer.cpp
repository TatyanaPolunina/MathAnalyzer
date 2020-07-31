#include "mathAnalyzer.h"

MathAnalyzer::MathAnalyzer()
: string_parsed(false)
{
	
}

bool MathAnalyzer::is_string_correct() const
{
    return string_parsed;
}

double MathAnalyzer::parseValue(const std::string &strExpression)
{
    str_expression = std::stringstream(strExpression);
    auto expression = parseExpression();
    return  expression->value();
}


enum class TokenType
{
    NUMBER,
    OPEN_BRACKET,
    CLOSED_BRACKET,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    UNDEFINED
};

static TokenType  get_token_type(const char typeSym)
{
    switch (typeSym) {
        case '(': return TokenType::OPEN_BRACKET;
        case ')': return  TokenType::CLOSED_BRACKET;
        case '+': return TokenType::PLUS;
        case '-': return TokenType::MINUS;
        case '*': return TokenType::MULTIPLY;
        case '/': return TokenType::DIVIDE;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
                return TokenType::NUMBER;
        default: return TokenType::UNDEFINED;
    }

}

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
private:
    TokenType token_type;
    double value;
};


Token get_token(std::iostream& strExpr)
{
   char ch;
   strExpr >> ch;
   TokenType token_type = get_token_type(ch);
   if (token_type == TokenType::NUMBER)
   {
       strExpr.putback(ch);
       double val;
       strExpr >> val;
       return Token(TokenType::NUMBER, val);
   }
  return Token(token_type);
}

std::unique_ptr<Expression> MathAnalyzer::parseExpression()
{
        std::unique_ptr<Expression> left = parseTerm();      // read and evaluate a Term
        Token t = get_token(str_expression);

        while(true)
        {
            std::unique_ptr<Expression> right = nullptr;
            if (t.get_type() == TokenType::PLUS)
            {
                auto right = parseTerm();

            }
            else if (t.get_type() == TokenType::MINUS)
            {
                auto right = std::make_unique<NegativeExpression>(parseTerm());
            }

            if (right)
            {
                left = std::make_unique<SumExpression>(std::move(left), std::move(right));
                t = get_token(str_expression);
            }
            else
            {
                return left;
            }
        }
}

std::unique_ptr<Expression> MathAnalyzer::parsePrimary()
{
    Token t = get_token(str_expression);
    if (t.get_type() == TokenType::OPEN_BRACKET)
    {
        auto expr = parseExpression();
        t= get_token(str_expression);
        if (t.get_type() != TokenType::CLOSED_BRACKET)
        {
            throw std::logic_error("No closed bracket");
        }
        return expr;
    }
    if (t.get_type() == TokenType::NUMBER)
    {
        return std::make_unique<NumericExpression>(t.get_value());
    }
    return  nullptr;
}

std::unique_ptr<Expression> MathAnalyzer::parseTerm()
{
    auto left = parsePrimary();
    Token t = get_token(str_expression);        // get the next token from token stream

    while(true)
    {
        if (t.get_type() == TokenType::MULTIPLY)
        {
            left = std::make_unique<MultipleExpression>(std::move(left), parsePrimary());
             t = get_token(str_expression);
        } else
        if (t.get_type() == TokenType::DIVIDE)
        {
            left = std::make_unique<DivisionExpression>(std::move(left), parsePrimary());
            t = get_token(str_expression);
        }
        else
        {
            return  left;
        }
    }
}
