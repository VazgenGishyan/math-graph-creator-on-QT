#ifndef CALCULATORHELPER_H
#define CALCULATORHELPER_H


#include <map>
#include "my_math.h"
using std::map;


namespace Functions {
    static const QString sin = "sin(";
    static const QString cos = "cos(";

    static const QString tan = "tan(";
    static const QString ctg = "ctg(";


    static const QString asin = "asin(";
    static const QString acos = "acos(";


    static const QString atan = "atan(";
    static const QString actg = "actg(";

    static const QString ln = "ln(";
    static const QString lg = "lg(";

    static const QString abs = "abs(";
    static const QString sqrt = "√(";

    static const QString factorial = "!";
}

namespace Operators {
    static const QString sum = "+";
    static const QString sub = "-";
    static const QString mul = "*";
    static const QString div = "/";
    static const QString pow = "^";
}

namespace Constants {
    static const QString e = "e";
    static const QString pi = "π";
}

double Get_math_constant(const QString &);

namespace Numbers {
    static const QString num0 = "0";
    static const QString num1 = "1";
    static const QString num2 = "2";
    static const QString num3 = "3";
    static const QString num4 = "4";
    static const QString num5 = "5";
    static const QString num6 = "6";
    static const QString num7 = "7";
    static const QString num8 = "8";
    static const QString num9 = "9";
}

namespace Variables {
    static const QString parametric = "t";
    static const QString ordinary = "x";
}

namespace Other {
    static const QString point = ".";
    static const QString begin = "(";
    static const QString end = ")";
}

static const map<QString,one> OneArg =
{
    std::pair<QString,one>(Functions::ln,My_math::ln),
    std::pair<QString,one>(Functions::lg,My_math::lg),
    std::pair<QString,one>(Functions::sin,My_math::my_sin),
    std::pair<QString,one>(Functions::cos,My_math::my_cos),
    std::pair<QString,one>(Functions::tan,My_math::my_tan),
    std::pair<QString,one>(Functions::ctg,My_math::ctg),
    std::pair<QString,one>(Functions::abs,fabs),
    std::pair<QString,one>(Functions::sqrt,My_math::my_sqrt),
    std::pair<QString,one>(Functions::asin,My_math::arcsin),
    std::pair<QString,one>(Functions::acos,My_math::arccos),
    std::pair<QString,one>(Functions::atan,My_math::arctan),
    std::pair<QString,one>(Functions::actg,My_math::arcctg),
    std::pair<QString,one>(Functions::factorial,My_math::factorial),
};
static const map<QString, two> TwoArg =
{
    std::pair<QString,two>(Operators::sum,My_math::add),
    std::pair<QString,two>(Operators::sub,My_math::sub),
    std::pair<QString,two>(Operators::mul,My_math::mul),
    std::pair<QString,two>(Operators::div,My_math::div),
    std::pair<QString,two>(Operators::pow,My_math::my_pow),
};

static const map<QString,int> OperatorLvl =
{
    std::pair<QString,int>(Operators::sum,0),
    std::pair<QString,int>(Operators::sub,0),
    std::pair<QString,int>(Operators::mul,1),
    std::pair<QString,int>(Operators::div,1),
    std::pair<QString,int>(Operators::pow,2),
};

one Get_one_arg_function(const QString &);
two Get_two_arg_function(const QString &);
int getOperatorLevel(const QString &);

double QStrToDouble(const QString &);
QString DoubleToQStr(double);



#endif // CALCULATORHELPER_H
