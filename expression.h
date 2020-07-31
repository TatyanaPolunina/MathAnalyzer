#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>

class Expression
{
public:
    double operator()()
    {
        return value();
    }
    virtual double value() = 0;
};

class NumericExpression : public Expression
{
public:
    NumericExpression(double value)
        : m_value (value)
    {
    }

    double value() override
    {
        return m_value;
    }
private:
    double m_value;
};


class BinaryExpression : public Expression
{
public:
    BinaryExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : m_left(std::move(left))
        , m_right(std::move(right))
    {}
protected:
    Expression& left() const
    {
        return *m_left;
    }

    Expression& right() const
    {
        return *m_right;
    }
private:
    std::unique_ptr<Expression> m_left;
    std::unique_ptr<Expression> m_right;
};


class SumExpression : public BinaryExpression
{
public:
    SumExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : BinaryExpression(std::move(left), std::move(right))
    {
    }

    double value() override
    {
        return left().value() + right().value();
    }
};


class MultipleExpression : public BinaryExpression
{
public:
    MultipleExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : BinaryExpression(std::move(left), std::move(right))
    {
    }

    double value() override
    {
        return left().value() * right().value();
    }
};


class DivisionExpression : public BinaryExpression
{
public:
    DivisionExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : BinaryExpression(std::move(left), std::move(right))
    {
    }

    double value() override
    {
        return left().value() / right().value();
    }
};

class NegativeExpression : public Expression
{
public:
    NegativeExpression(std::unique_ptr<Expression> expr)
        : m_expr(std::move(expr))
    {

    }

    double value()
    {
        return -m_expr->value();
    }
private:
    std::unique_ptr<Expression> m_expr;
};

#endif // EXPRESSION_H
