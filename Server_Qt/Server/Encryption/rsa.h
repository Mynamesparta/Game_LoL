#ifndef RSA_H
#define RSA_H
#include <QString>
#include "algorithm.h"
class Algorithm;
class LongInt;
class RSA:public Algorithm
{
    RSA();
    static LongInt p_1,p_2;
    static LongInt _public_key_mod;
    static LongInt _public_key_e;
    static LongInt _private_key_d;
    static LongInt _min_key;
public:
    static void Generation();
    static LongInt& public_key_mod();
    static LongInt& public_key_e();
    static LongInt& private_key_d();
    static void setPublicKey(LongInt,LongInt);
    static void setPrivateKey(LongInt);
    //static void setMinLenght(int);
    static QString Encryption(const QString&);
    static QString Decipherment(const QString&);

};

#endif // RSA_H
