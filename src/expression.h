#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

/*
 * Base class for math expression
 */
class Expression {
 public:
  /*
   * throws logic_error in case expression is built incorrect, runtime_error in case
   * calculation is not possible
   */
  virtual double Value() = 0;
  virtual ~Expression() = default;
};

class NumericExpression : public Expression {
 public:
  NumericExpression(double value) : value_(value) {}

  double Value() override { return value_; }

 private:
  double value_;
};

class BinaryExpression : public Expression {
 public:
  BinaryExpression(std::unique_ptr<Expression> left,
                   std::unique_ptr<Expression> right)
      : left_(std::move(left)), right_(std::move(right)) {}

 protected:
  Expression& Left() const {
    if (!left_) {
      throw std::logic_error("Incorrect left part of binary expression");
    }
    return *left_;
  }

  Expression& Right() const {
    if (!right_) {
      throw std::logic_error("Incorrect right part of binary expression");
    }
    return *right_;
  }

 private:
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

class SumExpression : public BinaryExpression {
 public:
  SumExpression(std::unique_ptr<Expression> left,
                std::unique_ptr<Expression> right)
      : BinaryExpression(std::move(left), std::move(right)) {}

  double Value() override { return Left().Value() + Right().Value(); }
};

class MultipleExpression : public BinaryExpression {
 public:
  MultipleExpression(std::unique_ptr<Expression> left,
                     std::unique_ptr<Expression> right)
      : BinaryExpression(std::move(left), std::move(right)) {}

  double Value() override { return Left().Value() * Right().Value(); }
};

class DivisionExpression : public BinaryExpression {
 public:
  DivisionExpression(std::unique_ptr<Expression> left,
                     std::unique_ptr<Expression> right)
      : BinaryExpression(std::move(left), std::move(right)) {}

  double Value() override {
    auto divider = Right().Value();
    if (divider == 0) {
      throw std::runtime_error("Division by zero expression presented");
    }
    return Left().Value() / Right().Value();
  }
};

class NegativeExpression : public Expression {
 public:
  NegativeExpression(std::unique_ptr<Expression> expr)
      : base_expr_(std::move(expr)) {}

  double Value() {
    if (!base_expr_) {
      throw std::logic_error("Incorrect input for negative expression");
    }
    return -base_expr_->Value();
  }

 private:
  std::unique_ptr<Expression> base_expr_;
};

#endif  // EXPRESSION_H
