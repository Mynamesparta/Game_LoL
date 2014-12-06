#ifndef SYMMETRIC_H
#define SYMMETRIC_H
#include "algorithm.h"
class Symmetric:public Algorithm
{
    Symmetric();
    static int _lenght;
    static LongInt _private_key;
public:
    static void Generation();
    static QString Encryption(const QString&);
    static QString Decipherment(const QString&);
    static void setLenght(int);
    inline static const LongInt& private_key();
    inline static const LongInt& lenght();
};

#endif // SYMMETRIC_H
