#include "mathAnalyzer.h"

class ExpressionParser
{
public:
    ExpressionParser(TokenStream& token_stream);
    std::unique_ptr<Expression> parse_expression_from_stream();
private:
    std::unique_ptr<Expression> parse_expression();
    std::unique_ptr<Expression> parse_primary();
    std::unique_ptr<Expression> parse_term();
private:
    TokenStream token_stream;
};


ExpressionParser::ExpressionParser(TokenStream& token_stream)
    : token_stream(token_stream)
{

}

std::unique_ptr<Expression> ExpressionParser::parse_expression_from_stream()
{
    return parse_expression();
}

std::unique_ptr<Expression> ExpressionParser::parse_expression()
{
        std::unique_ptr<Expression> left = parse_term();      // read and evaluate a Term
        Token t = token_stream.get_next_token();

        while(true)
        {
            std::unique_ptr<Expression> right = nullptr;
            if (t.get_type() == TokenType::PLUS)
            {
                right = parse_term();

            }
            else if (t.get_type() == TokenType::MINUS)
            {
                right = std::make_unique<NegativeExpression>(parse_term());
            }

            if (right)
            {
                left = std::make_unique<SumExpression>(std::move(left), std::move(right));
                t = token_stream.get_next_token();
            }
            else
            {
                token_stream.put_token_back(t);
                return left;
            }
        }
}

std::unique_ptr<Expression> ExpressionParser::parse_primary()
{
    Token t = token_stream.get_next_token();
    if (t.get_type() == TokenType::OPEN_BRACKET)
    {
        auto expr = parse_expression();
        t= token_stream.get_next_token();;
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

std::unique_ptr<Expression> ExpressionParser::parse_term()
{
    auto left = parse_primary();
    Token t = token_stream.get_next_token();        // get the next token from token stream

    while(true)
    {
        if (t.get_type() == TokenType::MULTIPLY)
        {
            left = std::make_unique<MultipleExpression>(std::move(left), parse_primary());
             t = token_stream.get_next_token();
        } else
        if (t.get_type() == TokenType::DIVIDE)
        {
            left = std::make_unique<DivisionExpression>(std::move(left), parse_primary());
            t = token_stream.get_next_token();
        }
        else
        {
            token_stream.put_token_back(t);
            return  left;
        }
    }
}

double MathAnalyzer::parseValue(const std::string &strExpression)
{
    std::stringstream expr_stream;
    expr_stream << strExpression;
    TokenStream token_stream(expr_stream);
    ExpressionParser parser(token_stream);
    auto expression = parser.parse_expression_from_stream();
    return  expression->value();
}
