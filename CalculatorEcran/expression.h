#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "calculatorhelper.h"
#include "error.h"
#include <list>
using std::list;

bool isDigit(const QString &);

enum ExpressionElementType
{
    num,
    constant,
    var,
    func,
    oper,
    factorial,
    sub,
    begin,
    end,
    point,
    nothing,
};

class ExpressionElement
{
    ExpressionElementType   type_name;

public:
    QString name;
    ExpressionElement(QString, ExpressionElementType);
    ExpressionElement(const ExpressionElement &);

    QString getName() const;
    ExpressionElementType   getType() const;

    //void name_push_back(const QString &);

};

enum ExpressionType
{
    constExpression,
    variableExpression,
};

class Expression
{
public:
    Expression(unsigned int = 500, ExpressionType = variableExpression);
    void push(const ExpressionElement &);       //+
    QString getExpression() const;              //+
    bool ended() const;                         //+
    void clear();                               //+
    void pop();                                 //+

    list<ExpressionElement>::const_iterator it_begin() const;
    list<ExpressionElement>::const_iterator it_end()   const;

private:

    ExpressionType expressiontype;              //+
    list<ExpressionElement> expression;         //+
    ExpressionElementType last;                 //+

    unsigned const int maxLength;               //+
    void trigger();                             //+
    void addElement(const ExpressionElement &); //+
    bool canAdd(ExpressionElementType) const;   //+
    bool ending;                                //+
    bool canAddPoint;                           //+
    bool canAddNumber() const;                  //+
    int countOfParentheses;                     //+
};



#endif // EXPRESSION_H
