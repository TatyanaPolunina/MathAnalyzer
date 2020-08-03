#include <memory>
#include <sstream>
#include <string>

class MathAnalyzer {
 public:
  /*
   * Parse value from string. Throws invalid_argument if  @str_expression is not
   * correct math expression
   */
  static double ParseExpression(const std::string& str_expression);
};
