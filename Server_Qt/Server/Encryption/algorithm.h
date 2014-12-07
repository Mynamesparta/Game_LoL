#ifndef LONGINT_H
#define LONGINT_H
#include <QDebug>
#include <QVector>
#include <QStack>
#include <QApplication>
//#include "algorithm.h"
//#include "longdouble.h"

#include "complex"
#include "math.h"
struct Table;

class Algorithm;
class LongInt;
class LongDouble;
//====================================================LongInt======================
static LongInt (*current_algorithm)(LongInt,LongInt);
class LongInt
{
protected:
    static LongInt mod(const LongInt&,const LongInt&);
    static const int _baza_for_initializatio=4;
    static const int _baza=10000;
    static bool is_Time_to_qDebug;
public:
    LongInt();
    LongInt(const LongInt&);
    //LongInt(LongInt);
    LongInt(QString);
    LongInt(int);
    virtual ~LongInt();

    static void setBaza(int new_baza=1);
    static void setAlgorithm(QString);
    static int baza_for_initializatio();
    static int baza();
    static LongInt Sqrt(const LongInt&);
    static LongInt Sqrt_n(const LongInt&,const LongInt&);

    void push_front(int num);
    void push_back(int num);
    void clear(bool normalization=true);
    void normalization();
    void _normalization();
    bool isEmpty() const;
    inline int  length()const;
    inline int  length();
    inline int last()const;
    int last();
    void resize(int); //Null

    virtual QString toString();
    int toInt();

    QVector<int> getVector_of_Number(int first=0, int renge=0 ,bool remove=1);
    //+++++++++++++++++++++++++++++operator+++++++++++++++++++++++++++++++++++++++
    LongInt  operator +(LongInt ) const;
    LongInt  operator +(int )const;
    LongInt  operator +()const;
    LongInt  operator -(const LongInt& )const;
    LongInt  operator -(int )const;
    LongInt  operator -() const;
    LongInt& operator --();
    LongInt& operator ++();
    LongInt& operator =(const LongInt& );
    LongInt& operator =(const int );
    LongInt& operator =(const QString);
    LongInt& operator =(const char*);
    LongInt& operator +=(const LongInt& );
    LongInt& operator +=(const int );
    LongInt& operator -=(const LongInt& );
    LongInt& operator -=(const int );
    bool  operator >( LongInt)const;
    bool  operator >(int);
    bool  operator <(LongInt)const;
    bool  operator <(int);
    bool  operator ==(LongInt)const;
    bool  operator ==(int);
    bool  operator !=(LongInt)const;
    bool  operator !=(int)const;
    bool  operator >=(LongInt)const;
    bool  operator >=(int);
    bool  operator <=(LongInt)const;
    bool  operator <=(int);
    LongInt  operator <<(int);
    LongInt& operator <<=(int);
    LongInt operator >>(int);
    LongInt  operator *(const LongInt&)const;
    LongInt  operator *(int);
    LongInt& operator *=(const LongInt&);
    LongInt& operator *=(int b);
    LongInt  operator /(const LongInt&)const;
    LongInt  operator /(int);
    LongInt& operator /=(const LongInt&);
    LongInt& operator /=(int);
    LongInt  operator %(const LongInt&)const;
    LongInt  operator %(int);
    LongInt  operator ^(const LongInt&)const;
    LongInt  operator ^(int);
    int &operator [](int);
    friend QDebug operator<<(QDebug,LongInt);
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    QVector<int> number;

    bool minus=0;
};
//====================================================LongDouble===================
class LongDouble:public LongInt
{
private:
    int _size=-1;
public:
    LongDouble();
    LongDouble(QString);
    LongDouble(int);
    ~LongDouble();

    virtual QString toString();
    void setSize(int);
    int size();

    LongDouble& operator =(const LongInt );
    LongDouble& operator =(const LongDouble );

};

struct Table;
//====================================================Algorithm====================
class Algorithm
{
public:
     static LongInt  Karatsuba(LongInt , LongInt );
     static LongInt  Toom_Cook(LongInt , LongInt );
     static LongInt  Schonhage(LongInt , LongInt );
     static LongInt  Strassen (LongInt , LongInt );

     static LongInt* Inverse_Number_Toom(LongInt,LongInt =0 );
     static LongInt* Toom(LongInt , LongInt );

     static bool Lehmer(LongInt, int =1);
     static bool Miller_Rabin(LongInt, int=1);
     static bool Solovay_Strassen(LongInt, int=1);
     static bool Agrawal_Kayal_Saxena(LongInt);

     static LongInt norm_Random(LongInt, LongInt);
     static LongInt norm_Random(LongInt, LongInt,bool);

     static int Modular_Multiplicative_Inverse(int,int);
     static LongInt Modular_exponentiation(LongInt a,LongInt m, LongInt r);
     static LongInt fast_Modular_exponentiation(LongInt a,LongInt r, LongInt m);
     static LongInt Modular_Multiplicative_Inverse(LongInt, LongInt, bool* search_bag=NULL);
     static LongInt  HelloWorldofTest(LongInt, LongInt );

protected:
     static LongInt Random(LongInt,LongInt);
     static void FFT(QVector< std::complex<double> >&,bool);
     static LongInt HCD(LongInt,LongInt);
     static LongInt Eulers_totient(LongInt );
     struct Table
     {
         int q,r;
     };
     static const int coef=8;
};
//==================================================================================
#endif // LONGINT_H
