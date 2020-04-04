#ifndef ERROR_H
#define ERROR_H
#include <QString>
#include <QDebug>


class Error
{
    const QString error;
public:
    Error(QString);
    Error(const Error &);
    QString what() const;
    //~Error();
};

class FatalError : public Error
{
public:
    FatalError(QString);
    FatalError(const FatalError &);
};

#endif // ERROR_H
