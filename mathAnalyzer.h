#include <string>
#include <memory>
#include "expression.h"
#include <sstream>

class MathAnalyzer
{
	public:
        MathAnalyzer();
		bool is_string_correct() const;
        double parseValue(const std::string& strExpression);
	private:
        std::unique_ptr<Expression> parseExpression();
        std::unique_ptr<Expression> parsePrimary();
        std::unique_ptr<Expression> parseTerm();

		bool string_parsed;
        std::stringstream str_expression;

};
