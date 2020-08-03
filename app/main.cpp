#include <iostream>
#include <string>
#include "mathAnalyzer.h"

int main(int, char**) {
  std::string math_expession;

  while (true) {
    std::cout << "Enter the math expression or \'q\' to exit: ";
    std::getline(std::cin, math_expession);
    if (math_expession == "q" or math_expession == "quit") {
      return 0;
    }
    try {
      double value = MathAnalyzer::ParseExpression(math_expession);
      std::cout << "Result: " << value << "\n";
    } catch (const std::invalid_argument& e) {
      std::cout << "Expression is wrong: " << e.what() << "\n";
    } catch (const std::runtime_error& r) {
      std::cout << "Calculation is wrong: " << r.what() << "\n";
    }
  }

  return 0;
}
