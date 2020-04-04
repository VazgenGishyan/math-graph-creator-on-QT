#ifndef POSTFIX_H
#define POSTFIX_H

#include "expression.h"
#include <stack>
using std::stack;

class Postfix
{
    void createPostfix(list<ExpressionElement>::const_iterator &, list<ExpressionElement>::const_iterator &);
    bool postfixCreated;
    list <ExpressionElement> postfix;
public:
    list<ExpressionElement>::const_iterator it_begin() const;
    list<ExpressionElement>::const_iterator it_end() const;
    void createPostfix(const Expression &);
    Postfix();
    void clear();
    bool created() const;
};

#endif // POSTFIX_H
