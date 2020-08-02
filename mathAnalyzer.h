#include <string>
#include <memory>
#include "expression.h"
#include "tokenstream.h"
#include <sstream>

class MathAnalyzer
{
public:
    static double parseValue(const std::string& strExpression);
};
