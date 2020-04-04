#include "calculatorhelper.h"

one Get_one_arg_function(const QString & strone)
{
    auto it = OneArg.find(strone);
    if(it == OneArg.end())
    {
        throw FatalError("wrong function");
    }
    return (*it).second;
}


two Get_two_arg_function(const QString & strtwo)
{
    auto it = TwoArg.find(strtwo);
    if(it == TwoArg.end())
    {
        throw FatalError("wrong operator");
    }
    return (*it).second;
}

int getOperatorLevel(const QString & oper)
{
    auto it = OperatorLvl.find(oper);
    if(it == OperatorLvl.end())
    {
        throw  FatalError("wrong operator");
    }
    return (*it).second;
}

double Get_math_constant(const QString & c)
{
    //qDebug()<<"redy";
    if(c == Constants::pi)
    {
        return My_math::pi;
    }
    if(c == Constants::e)
    {
        return My_math::e;
    }
    throw FatalError("wrong constant");
}

double QStrToDouble(const QString & str)
{
    return str.toDouble();
}


QString DoubleToQStr(double x)
{
    return QString::number(x,'g',10);
}

