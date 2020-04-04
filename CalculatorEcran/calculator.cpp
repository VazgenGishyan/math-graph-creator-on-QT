#include "calculator.h"

Calculator::Calculator(unsigned int size, ExpressionType et) : expression(size,et)
{
    clear();
}

Calculator::~Calculator()
{
    //qDebug()<<"calculator destructor";
}



void Calculator::clear()
{
    isCalculated = false;
    isConstExpression = true;
    expression.clear();
    postfix.clear();
    constValue = 0.0;
}

void Calculator::pop()
{
    isCalculated = false;
    isConstExpression = true; // it is normal
    expression.pop();
    postfix.clear();
    constValue = 0.0;
}

double Calculator::Calculate(double x)
{
    if(!redy())
    {
        throw Error("Expression not ended");
    }
    if(postfix.created() == false)
    {
        postfix.createPostfix(expression);
    }
    if(isCalculated && isConstExpression)
    {
        return constValue;
    }

    stack<double> st;

    list<ExpressionElement>::const_iterator it = postfix.it_begin();
    list<ExpressionElement>::const_iterator itend = postfix.it_end();

    for(; it != itend; ++it)
    {
        switch ((*it).getType()) {
        case num:
            {
                double d = QStrToDouble((*it).getName());
                st.push(d);
                break;
            }
        case var:
            isConstExpression = false;
            st.push(x);
            break;
        case constant:
            {

                double c = Get_math_constant((*it).getName());
                st.push(c);
                break;
            }
        case func:
        case factorial:
            {
                one f = Get_one_arg_function((*it).getName());
                double xx = st.top();
                st.top() = f(xx);
                break;
            }
        case sub:
        case oper:
            {
                two f = Get_two_arg_function((*it).getName());
                double x2 = st.top();
                st.pop();
                double x1 = st.top();
                st.top() = f(x1,x2);
                break;
            }
        default:
            throw FatalError("Somthing wrong in expression");
        }
    }

    double ret = st.top();

    if(isConstExpression)
    {
        clear();
        push(ExpressionElement(DoubleToQStr(ret),num));
        postfix.createPostfix(expression);
        constValue = ret;
    }
    isCalculated = true;
    return ret;
}

QString Calculator::getExpression() const
{
    return expression.getExpression();
}

void Calculator::push(const ExpressionElement & expel)
{
    //qDebug()<<"push on Calculator";
    isCalculated = false;
    expression.push(expel);
    postfix.clear();
    //qDebug()<<"expression = "<<getExpression()<<"  on Calculator";
    //qDebug()<<"pushed on Calculator";
}

bool Calculator::redy() const
{
    return expression.ended();
}

bool Calculator::isConst() const
{
    return isConstExpression;
}
