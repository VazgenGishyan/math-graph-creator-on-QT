#include "expression.h"

ExpressionElement::ExpressionElement(QString str, ExpressionElementType type):
    type_name(type),
    name(str) {}

ExpressionElement::ExpressionElement(const ExpressionElement & ee):
    type_name(ee.type_name),
    name(ee.name) {}

QString ExpressionElement::getName() const
{
    return name;
}

ExpressionElementType ExpressionElement::getType() const
{
    return type_name;
}

Expression::Expression(unsigned int max, ExpressionType type):
    expressiontype(type),
    maxLength(max)
{
    clear();
}

QString Expression::getExpression() const
{
    QString ret = "";
    for(auto it = expression.begin(); it != expression.end(); ++it)
    {
        ret += it->getName();
    }
    return ret;
}

void Expression::clear()
{
    expression.clear();
    countOfParentheses = 0;
    last = ExpressionElementType::nothing;
    ending = false;
    canAddPoint = true;
}

bool isDigit(const QString & str)
{
    int index = 0;
    if(str[index] == Operators::sub)
    {
        ++index;
    }
    for(;index < str.size(); ++index)
    {
        if((str[index] < Numbers::num0 || str[index] > Numbers::num9) && str[index] != Other::point)
        {
            return false;
        }
    }
    return true;
}

bool isContainPoint(const QString & str)
{
    for(int i = 0; i<str.size(); ++i)
    {
        if(str[i] == Other::point)
        {
            return true;
        }
    }
    return false;
}

bool Expression::canAddNumber() const
{
    //qDebug()<<"canAddNumber begin";
    ExpressionElement el = expression.back();
    int index = 0;
    if(!isDigit(el.getName()))
    {
        return false;
    }

    if(el.getName()[0] == Operators::sub)
    {
        ++index;
    }

    if(!isContainPoint(el.getName()) && el.getName()[index] == Numbers::num0)
    {
        return false;
    }

    return true;

    //isContainPoint(el.getName(),canAddPoint);
    //if(isContainPoint(el.getName(),canAddPoint))

    /**/
    /*if()
    if(canAddPoint && el.getType() == num)
    {
        if((el.getName())[0] == (Numbers::num0)[0])
        {
            return false;
        }
    }
    return true;*/
}

bool Expression::canAdd(ExpressionElementType next) const
{
    switch (next)
    {
        case num:
        {
            switch (last)
            {
                case constant:
                case var:
                case factorial:
                case end:
                    return false;
            case nothing:
                    return true;
            case num:
            case point:
                    qDebug()<<"canAddNumber ? ";
                    return canAddNumber();
                default:
                    return true;
            }
        }
        case var:
            if(expressiontype == constExpression)
                return false;
        case constant:
        case func:
        case begin:
        {
            switch (last)
            {
                case func:
                case oper:
                case sub:
                case begin:
                case nothing:
                    return  true;
                default:
                    return false;
            }
        }
        case end:
            if(!countOfParentheses)
                return false;
        case oper:
        case factorial:
        {
            switch (last)
            {
                case num:
                case constant:
                case var:
                case factorial:
                case end:
                    return  true;
                default:
                    return false;
            }
        }
        case sub:
        {
            switch (last)
            {
                case oper:
                case sub:
                case point:
                    return  false;
                default:
                    return true;
            }
        }
        case point:
        {
            if (last == num &&
                    canAddPoint &&
                    isDigit(expression.back().getName()) &&
                    !isContainPoint(expression.back().getName()))
            {
                return true;
            }
            return false;
        }
    default:
        throw FatalError("Wrong element for expression");
        //return false;
    };
}

void Expression::addElement(const ExpressionElement & element)
{
    switch (element.getType())
    {
        case num:
            if (last == num || last == point)
            {
                expression.back().name += element.name;
            }
            else {
                expression.push_back(element);
            }
            return;
        case point:
            expression.back().name += element.name;
            return;
        default:
            expression.push_back(element);
            return;
    }
}

void Expression::trigger()
{
    ending = false;
    switch (last)
    {
    case end:
        --countOfParentheses;
    case factorial:
        ending = !countOfParentheses;
    case oper:
    case sub:
        {
            canAddPoint = true;
            break;
        }
    case func:
    case begin:
        {
            ++countOfParentheses;
            break;
        }
    case point:
        {
            canAddPoint = false;
            break;
        }
    case num:
    case constant:
    case var:
        ending = !countOfParentheses;
        break;
    default:
        break;
    }
}

void Expression::push(const ExpressionElement & element)
{
    //qDebug()<<"push on Expression";
    ExpressionElementType next = element.getType();
    if(!canAdd(next))
    {
        throw Error("cannot add element to expression");
    }

    if(element.getName().size() + getExpression().size() + countOfParentheses - (next == end) > maxLength)
    {
        throw Error("cannot add element to expression : no free space");
    }

    addElement(element);
    last = next;
    trigger();
}

bool Expression::ended() const
{
    return ending;
}

void Expression::pop()
{
    if(expression.empty())
    {
        return;
    }
    last = expression.back().getType();
    switch (last)
    {
        case num:
            canAddPoint = true;
            break;
        case func:
        case begin:
            --countOfParentheses;
            break;
        case end:
            ++countOfParentheses;
            break;
        default:
            break;
    }
    expression.pop_back();
    if(expression.empty())
    {
        last = nothing;
    }
    else {
        last = expression.back().getType();
    }

    switch (last) {
        case factorial:
        case num:
        case end:
        case var:
        case constant:
            ending = !countOfParentheses;
            break;
        default:
            ending = false;
    }

}

list<ExpressionElement>::const_iterator Expression::it_end() const
{
    list<ExpressionElement>::const_iterator ret = expression.end();
    return ret;
}

list<ExpressionElement>::const_iterator Expression::it_begin() const
{
    list<ExpressionElement>::const_iterator ret = expression.begin();
    return ret;
}
