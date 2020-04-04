#include "error.h"

Error::Error(QString str) : error(str) {}

Error::Error(const Error & err) : error(err.error) {}

QString Error::what() const
{
    return error;
}


FatalError::FatalError(QString str):Error (str){}

FatalError::FatalError(const FatalError & ferr) : Error (ferr){}
