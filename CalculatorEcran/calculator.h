#ifndef CALCULATOR_H
#define CALCULATOR_H

//#include "clalculatorhelper.h"
#include "postfix.h"
//#include <stack>
//using std::stack;

class Calculator
{
    double constValue;
    Expression expression;
    Postfix postfix;
    bool isConstExpression;
    bool isCalculated;
public:
    QString getExpression() const;
    Calculator(unsigned int = 500, ExpressionType = variableExpression);
    ~Calculator();
    double Calculate(double = 0.0);
    void clear();
    void push(const ExpressionElement &);
    void setValue(double);
    void pop();
    bool redy() const;
    bool isConst() const;
};

#endif // CALCULATOR_H
