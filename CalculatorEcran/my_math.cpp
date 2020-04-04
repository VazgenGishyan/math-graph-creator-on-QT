#include "my_math.h"

int roundToInt(double x)
{
    int xx = static_cast<int>(x);
    if(fabs(x - xx) >= 0.5)
    {
        ++xx;
    }
    return xx;
}


double My_math::add(double x1, double x2)
{
    return x1 + x2;
}

double My_math::sub(double x1, double x2)
{
    return x1 - x2;
}

double My_math::mul(double x1, double x2)
{
    return x1 * x2;
}

double My_math::div(double x1, double x2)
{
    return x1 / x2;
}

double My_math::my_pow(double x1, double x2)
{
    if(x1 < 0 && x2 < 1)
    {
        throw Error("Wrong arguments for operator <pow>");
    }
    return pow(x1, x2);
}

double My_math::my_sin(double x)
{
    double sinx = sin(x);
    if(fabs(sinx) <= epsilon)
        sinx = 0;
    return sinx;
}


double My_math::my_cos(double x)
{
    double cosx = my_sin(x + pi/2);
    return cosx;

}


double My_math::my_tan(double x)
{
    return My_math::my_sin(x) / My_math::my_cos(x);
}

double My_math::ctg(double x)
{
    return 1/My_math::my_tan(x);
}

double My_math::ln(double x)
{
    if (x < 0.0)
    {
        //qDebug()<<"ln throw  x = "<<x;
        throw Error("wrong argument for <log> function");
    }
    if (x == 1.0)
    {
        return 0;
    }
    return log(x);
}

double My_math::lg(double x)
{
    return ln(x) / ln(10.0);
}

double My_math::my_sqrt(double x)
{
    if (x < 0.0)
    {
        //qDebug()<<"sqrt throw";
        throw Error("wrong argument for <sqrt> function");
    }
    return sqrt(x);
}

double My_math::arcsin(double x)
{
    if (fabs(x) > 1)
    {
        throw Error("wrong argument for <arcsin> function");
    }
    return asin(x);
}

double My_math::arccos(double x)
{
    if (fabs(x) > 1)
    {
        throw Error("wrong argument for <arccos> function");
    }
    return acos(x);
}

double My_math::arctan(double x)
{
    return atan(x);
}

double My_math::arcctg(double x)
{
    return -atan(x) + My_math::pi / 2;
}
double My_math::factorial(double x)
{
    static double factorial[171];
    factorial[0] = 1;
    static int count = 1;

    if (x < 0 || x>170)
    {
        throw Error("wrong argument for <factorial>");
    }

    int q = static_cast<int>(x);
    if (q != x)
    {
        throw Error("wrong argument for <factorial>");
    }

    if (q < count)
    {
        return factorial[q];
    }

    double p = factorial[count-1];

    for (int i = count; i <= q; ++i)
    {
        p *= i;
        factorial[i] = p;
        ++count;
    }
    return p;
}
