#ifndef MY_MATH_H
#define MY_MATH_H

#include <math.h>
#include "error.h"

typedef double(&one) (double);
typedef double(&two) (double, double);

namespace My_math
{
    static const double pi= 3.1415926535897932384626433832795028841971694;
    static const double e = 2.7182818284590452353602874713526624977572470937;
    static const double epsilon = 0.000000000000001;

    double add(double, double);
    double sub(double, double);
    double mul(double, double);
    double div(double, double);
    double my_pow(double, double);
    double ln(double);
    double lg(double);
    double my_sin(double);
    double my_cos(double);
    double my_tan(double);
    double ctg(double);
    double my_sqrt(double);
    double arcsin(double);
    double arccos(double);
    double arctan(double);
    double arcctg(double);
    double factorial(double);
}

int roundToInt(double);

#endif // MY_MATH_H
