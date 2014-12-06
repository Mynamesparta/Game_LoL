//#include "longint.h"
#include "../algorithm.h"

LongInt::LongInt():minus(0)
{
    number<<0;
}

LongInt::LongInt(const LongInt &b)
{
    if(this==&b)
    {
        return;
    }
    this->number=b.number;
    this->minus=b.minus;
}
/*/
LongInt::LongInt(LongInt b)
{
    this->number=b.number;
    this->minus=b.minus;
}
/*/
LongInt::LongInt(QString qs_number):minus(0)
{
    qs_number.replace(" ","");
    if(qs_number==""||qs_number==" ")
    {
        number.push_back(0);
        return;
    }
    QString numeral;
    if(!qs_number.isEmpty())
    {
        for(int i=qs_number.length()-1;i>=0;i--)
        {
            numeral=qs_number[i]+numeral;
            if(numeral.length()==_baza_for_initializatio)
            {
                number.push_front(numeral.toInt());
                numeral.clear();
                continue;
            }
            if(i==0)
            {
                number.push_front(numeral.toInt());
                numeral.clear();
            }
        }
    }
    normalization();
}

LongInt::LongInt(int num)//:minus(0)
{
    if(num>=0)
    {
        number.push_front(num);
        minus=0;
    }
    else
    {
        number.push_front(-num);
        minus=1;
    }
    normalization();
}

LongInt::~LongInt()
{

}

//=====================================static======================
void LongInt::setBaza(int new_baza)
{
    //baza_for_initializatio=new_baza;
    //_baza=1;
    for(int i=0;i<new_baza;i++)
      ;//  _baza*=10;
}

void LongInt::setAlgorithm(QString name)
{
    if(name=="Karatsuba")
    {
        current_algorithm=&Algorithm::Karatsuba;
        qDebug()<<"longint.h:current algorithm \"Karatsuba\"";
        return;
    }
    if(name=="Toom-Cook")
    {
        current_algorithm=&Algorithm::Toom_Cook;
        qDebug()<<"longint.h:current algorithm \"Toom_Cook\"";
        return;
    }
    if(name=="Schonhage")
    {
        current_algorithm=&Algorithm::Schonhage;
        qDebug()<<"longint.h:current algorithm \"Schönhage\"";
        return;
    }
    if(name=="Strassen")
    {
        current_algorithm=&Algorithm::Strassen;
        qDebug()<<"longint.h:current algorithm \"Strassen\"";
        return;
    }
}

int LongInt::baza_for_initializatio()
{
    return _baza_for_initializatio;
}

int LongInt::baza()
{
    return _baza;
}
LongInt LongInt::mod(const LongInt &a, const LongInt &b)
{
    //qDebug()<<"longint.cpp:mod-"<<a<<b;
    if(b==0&&b.minus)
    {
        qDebug()<<"longint.cpp:"<<a<<"% -0 = ...?";
        return a;
    }
    if(b.isEmpty()||b==0)
    {
        qDebug()<<"longint.cpp:Error "<<"\n"
                <<a<<"\%0 = BAMMMMMMMMMMMM!!!!";
        //QApplication::exit();
        exit(0);
        throw a;
        return (-LongInt(0));
    }
    bool _minus=(!a.minus)*b.minus+a.minus*(!b.minus);
    static LongInt _a,_b;
    _a=+a;_b=+b;
    if(_a < _b)
    {
        //qDebug()<<a<<"<"<<b;
        _a.minus=_minus;
        return _a;
    }
    int k;
    LongInt result_long_int;
    LongInt part;
    QVector<int>::const_iterator iter=_a.number.constBegin();
    for(;iter<_a.number.constEnd();iter++)
    {
        part.push_back(*iter);
        //qDebug()<<"longint.cpp:part="<<part;
        if(part<_b)
        {
            if(result_long_int.length())
            {
                result_long_int.push_back(0);
            }
            //qDebug()<<"longint.cpp:result_long_int="<<result_long_int;
            continue;
        }
        k=0;
        while(part >= _b)
        {
            //qDebug()<<part<<">="<<_b;
            k++;
            part-=_b;
        }
        //qDebug()<<part;
        result_long_int.push_back(k);
        //qDebug()<<"longint.cpp:result_long_int="<<result_long_int;
    }
    part.minus=_minus;
    part.normalization();
    return part;
}

LongInt LongInt::Sqrt(const LongInt &a)
{
    LongInt cur(1);
    // максимальное количество разрядов в ответе
    int pos = (a.length() + 1) / 2;
    cur.resize(pos);
    pos--;
    int l = 0, r = LongInt::baza();
    int curDigit = 0;
    while (pos >= 0)
    {
        l = 0, r = LongInt::baza();
        curDigit = 0;
        while (l <= r)
        { // подбираем текущую цифру
            int m = (l+r)>>1;
            cur[pos] = m;
            if (cur * cur <= a){
                curDigit = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        cur[pos] = curDigit;
        pos--;
    }
    // избавляемся от лидирующих нулей
    cur.normalization();
    return cur;
}
LongInt LongInt::Sqrt_n(const LongInt &a, const LongInt &k)
{
    LongInt _a=0;
    LongInt a_=a-1;
    LongInt r,midle;
    while(1)
    {
        r=(a_+_a)/2;
        midle=(r)^k;
        if(midle==a)
        {
            qDebug()<<"algorithm.cpp:"<<a<<"="<<r<<"^"<<k;
            return r;
        }
        if(midle>a)  a_=r;
        if(midle<a)  _a=r;
        if((a_-_a)<=1) break;
    }
    return _a;
}

//=================================================================
void LongInt::clear(bool normalization)
{
    number.clear();
    if(normalization)
        number<<0;
    minus=0;
}

void LongInt::normalization()
{
    if(number.isEmpty())
    {
        number<<0;
        minus=0;
        return ;
    }
    if(number.length()==1&&number.first()==0)
    {
        minus=0;
        return;
    }
    while(number.length()>0)
    {
        if(number.first()==0)
        {
            number.removeFirst();
        }
        else
        {
            break;
        }
    }
    int k=0;
    QVector<int>::iterator iter=number.end();
    iter--;
    //qDebug()<<"*this="<<*this;
    for(;iter>=number.begin();iter--)
    {
        (*iter)+=k;
        k=(*iter)/_baza;
        (*iter)-=k*_baza;
        if((*iter)<0)
        {
            k--;
            (*iter)+=_baza;
        }
    }
    if(k)
    {
        //qDebug()<<*this;
        //qDebug()<<k;
        if(k<0)
        {
            minus=1;
            k=-k;
        }
        int _k;
        while(k>=_baza)
        {
            _k=k/_baza;
            number.push_front(k-_k*_baza);
            k=_k;
        }
        if(k)
        {
            number.push_front(k);
        }
    }
    while(number.length()>0)
    {
        if(number.first()==0)
        {
            number.removeFirst();
        }
        else
        {
            break;
        }
    }
}

void LongInt::_normalization()
{
    int k=0;
    QVector<int>::iterator iter=number.begin();
    for(;iter<number.end();iter++)
    {
        (*iter)+=k;
        k=(*iter)/_baza;
        (*iter)-=k*_baza;
    }
    if(k)
    {
        int _k;
        while(k>=_baza)
        {
            _k=k/_baza;
            number.push_back(k-_k*_baza);
            k=_k;
        }
        if(k)
        {
            number.push_back(k);
        }
    }
}

void LongInt::resize(int n)
{
    if(this->length()>n)
    {
        while(this->length()>n)
        {
            this->number.removeLast();
        }
    }
    else
    {
        while(this->length()<n)
        {
            number.push_back(0);
        }
    }
}

void LongInt::push_front(int num)
{
    /*/qDebug()<<"longint.cpp:push_front"<<*this;
    if(number.length()==1&&number.last()==0)
    {
        number.clear();
    }
    /*/
    number.push_front(num);
    //qDebug()<<"longint.cpp:push_front"<<*this;
    //qDebug()<<num;
}
void LongInt::push_back(int num)
{
    if(number.length()==1 && !number.first())
    {
        number.clear();
    }
    number.push_back(num);
}

bool LongInt::isEmpty()const
{
    return number.isEmpty();
}

int LongInt::length()const
{
    return number.length();
}

inline int  LongInt::length()
{
    return number.length();
}

inline int LongInt::last()const
{
    if(number.isEmpty())
    {
        return 0;
    }
    return number.last();
}

int LongInt::last()
{
    if(number.isEmpty())
    {
        return 0;
    }
    return number.last();
}

QString LongInt::toString()
{
    QString text;
    QVector<int>::iterator iter;
    if(!this->isEmpty())
    {
        iter=this->number.begin();
        int lenght;
        for(;iter<this->number.end();iter++)
        {

           if((*iter)<0||((*iter)>=(LongInt::baza()/10))||(iter==this->number.begin()))
           {
                text+=QString::number(*iter)+" ";
           }
           else
           {
               if(*iter==0)
               {
                   for(int i=0;i<LongInt::baza_for_initializatio();i++)
                       text+="0";
                   text+=" ";
                   continue;
               }
               lenght=LongInt::baza()/10;
               while((*iter)<lenght)
               {
                   text+="0";
                   lenght/=10;
               }
               text+=QString::number(*iter)+" ";
           }
        }
    }
    else
    {
       text+="null";
    }
    return text;
}

int LongInt::toInt()
{
    QVector<int>::iterator iter=number.begin();
    int numb=*iter;
    iter++;
    for(;iter<number.end();iter++)
    {
        numb*=_baza;
        numb+=*iter;
    }
    return numb;

}

QVector<int> LongInt::getVector_of_Number(int first, int renge, bool remove)
{
    QVector<int> vector;
    QVector<int>::iterator iter=number.begin();
    for(int i=0;i<number.length(),iter<number.end();i++,iter++)
    {
        if(i>=first)
        {
            vector<<*iter;
            if(renge)
            if(i+1==first+renge)break;
        }

    }
    if(remove)
    {
        if(renge)
            number.remove(first,renge);
        else
            number.remove(first,number.length()-first);
    }
    return vector;
}
//=============================operator=(+)======================================
LongInt LongInt::operator +(LongInt b)const//a=this;
{
    //qDebug()<<"test:"<<*this<<b;
    if(number.isEmpty()||number.first()==0)
    {
        return ((+b)==0?LongInt():b);
    }
    if(b.number.isEmpty()||b.number.first()==0)
    {
        return ((+(*this))==0?LongInt():*this);
    }
    LongInt a,c;
    //qDebug()<<*this<<b;
    if((+*this)<(+b))//
    {
        c=b;
        b=*this;
        a=c;
        c.clear();
    }
    else
    {
        a=*this;
    }

    c.clear(false);
    int sign=(!a.minus*b.minus+a.minus*!b.minus)?-1:1;
    c.minus=a.minus;
    //qDebug()<<a<<b<<sign;
    while(!b.isEmpty())
    {
        c.push_front(a.number.takeLast()+sign*b.number.takeLast());
        //qDebug()<<c;
    }
    //qDebug()<<c;
    while(!a.isEmpty())
    {
        c.push_front(a.number.takeLast());
    }
    //qDebug()<<"longint.cpp:operator + c"<<c;
    c.normalization();
    return c;
}
LongInt LongInt::operator +(int b)const
{
    if(!this->length())
    {
        return LongInt(b);
    }
    LongInt c=*this;
    c.number.push_back(c.number.takeLast()+b);
    c.normalization();
    return c;
}

LongInt  LongInt::operator +()const// return |*this|
{                             // +(x)~|x|
    LongInt b=*this;
    b.minus=0;
    return b;
}

//=============================operator=(-)======================================
LongInt LongInt::operator -(const LongInt& b)const
{
    LongInt c=*this + (-b);
    return c;
}

LongInt LongInt::operator -(int b)const
{
    if(number.last()-b>=0)
    {
        LongInt c=*this;
        int num=c.number.takeLast()-b;
        c.number.push_back(num);
        c.normalization();
        return c;
    }
    else
    {
        return *this-LongInt(b);
    }
}

LongInt  LongInt::operator -()const
{
    LongInt b=*this;
    b.minus=!b.minus;
    return b;
}

//=============================operator=(++/--)======================================
LongInt& LongInt::operator ++()
{
    *this +=1;
    return *this;
}

LongInt& LongInt::operator --()
{
    *this -=1;
    return *this;
}
//=============================operator=(=)======================================
LongInt& LongInt::operator =(const LongInt &b)
{
    if(&b==this)
    {
        return *this;
    }
    if(!b.number.length())
    {
        number.clear();
        return *this;
    }
    number=b.number;
    minus=b.minus;
    return *this;
}

LongInt& LongInt::operator =(const int b)
{
    number.clear();
    if(b>=0)
    {
        minus=0;
        number.push_front(b);
    }
    else
    {
        minus=1;
        number.push_front(-b);
    }
    normalization();
}

LongInt& LongInt::operator =(const QString qs_number)
{
    number.clear();
    qDebug()<<qs_number;
    minus=0;
    if(qs_number==""||qs_number==" ")
    {
        number.push_back(0);
        return *this;
    }
    QString numeral;
    if(!qs_number.isEmpty())
    {
        for(int i=qs_number.length()-1;i>=0;i--)
        {
            numeral=qs_number[i]+numeral;
            if(numeral.length()==_baza_for_initializatio)
            {
                number.push_front(numeral.toInt());
                numeral.clear();
                continue;
            }
            if(i==0)
            {
                number.push_front(numeral.toInt());
                numeral.clear();
            }
        }
    }
    return *this;
}

LongInt& LongInt::operator =(const char* num)
{
    qDebug()<<*num;
    return *this=QString(num);
}

//=============================operator=(+=)======================================
LongInt& LongInt::operator +=(const LongInt &b)
{
    *this=*this+b;
    return *this;
}
LongInt& LongInt::operator +=(const int b)
{
    *this=*this+b;
    return *this;
}
//=============================operator=(-=)======================================
LongInt& LongInt::operator -=(const LongInt &b)
{
    *this=*this-b;
    return *this;
}
LongInt& LongInt::operator -=(const int b)
{
    *this=*this-b;
    return *this;
}
//=============================operator=(<)======================================
bool  LongInt::operator <(LongInt b)const
{
    //----------------------------------------
    if(b!=0    &&   (!this->minus)*b.minus)
    {
        return false;
    }
    if(*this!=0&&   this->minus*(!b.minus))
    {
        return true;
    }
    //----------------------------------------
    if(!this->length())
    {
        //this->push_back(0);
    }
    if(!b.length())
    {
        b.push_back(0);
    }

    LongInt a;
    //--------------------
    if(this->minus*b.minus)
    {
        LongInt c=b;
        b=*this;
        a=c;
    }
    else
    {
        a=*this;
    }
    //--------------------
    if(a.length()<b.length())
    {
        return 1;
    }
    if(a.length()>b.length())
    {
        return 0;
    }
    //--------------------
    QVector<int>::const_iterator iter_for_a=a.number.constBegin();
    QVector<int>::const_iterator iter_for_b=b.number.constBegin();
    for(;iter_for_a<a.number.constEnd();iter_for_a++,iter_for_b++)
    {
        if((*iter_for_a)<(*iter_for_b))
        {
            return 1;
        }
        if((*iter_for_a)>(*iter_for_b))
        {
            return 0;
        }
    }
    return 0;
}

bool  LongInt::operator <(int b)
{
    if(!this->length())
    {
        this->push_back(0);
    }

    if(b<_baza)
    {
        if(length()>1)
        {
            return 0;
        }
        if(number.length()&&number.first() < b)
        {
            return 1;
        }
        else
        {
            if(!number.length()&&b<0)
                return 1;
            else
                return 0;
        }
    }
    else
    {
        return *this < LongInt(b);
    }
}

//=============================operator=(>)======================================
bool  LongInt::operator >(LongInt b)const
{
    //----------------------------------------
    if(b!=0    &&   (!this->minus)*b.minus)
    {
        return true;
    }
    if(*this!=0&&   this->minus*(!b.minus))
    {
        return false;
    }
    //----------------------------------------
    if(!this->length())
    {
        //this->push_back(0);
    }
    if(!b.length())
    {
        b.push_back(0);
    }

    LongInt a;
    //--------------------
    if(this->minus*b.minus)
    {
        LongInt c=b;
        b=*this;
        a=c;
    }
    else
    {
        a=*this;
    }
    //--------------------
    if(!a.isEmpty()&&a.length()>b.length())
    {
        return 1;
    }
    if(!b.isEmpty()&&a.length()<b.length())
    {
        return 0;
    }
    QVector<int>::const_iterator iter_for_a=a.number.constBegin();
    QVector<int>::const_iterator iter_for_b=b.number.constBegin();
    for(;iter_for_a<a.number.constEnd();iter_for_a++,iter_for_b++)
    {
        if((*iter_for_a)>(*iter_for_b))
        {
            return 1;
        }
        if((*iter_for_a)<(*iter_for_b))
        {
            return 0;
        }
    }
    return 0;
}

bool  LongInt::operator >(int b)
{
    if(!this->length())
    {
        this->push_back(0);
    }

    if(b<_baza)
    {
        if(length()>1)
        {
            return 1;
        }
        if(number.length()&&number.first() > b)
        {
            return 1;
        }
        else
        {
            if(!number.length()&&b>0)
                return 1;
            else
                return 0;
        }
    }
    else
    {
        return *this > LongInt(b);
    }
}

//=============================operator=(==)======================================
bool  LongInt::operator ==(LongInt b)const
{
    //----------------------------------------
    if(b!=0    &&   (!this->minus)*b.minus)
    {
        return false;
    }
    if(*this!=0&&   this->minus*(!b.minus))
    {
        return false;
    }
    //----------------------------------------
    if(!this->length())
    {
        //this->push_back(0);
    }
    if(!b.length())
    {
        b.push_back(0);
    }

    LongInt a=*this;
    a.normalization();
    b.normalization();
    //--------------------
    if( (a.length()<b.length()) || (a.length()>b.length()) )
    {
        return 0;
    }
    QVector<int>::const_iterator iter_for_a=a.number.constBegin();
    QVector<int>::const_iterator iter_for_b=b.number.constBegin();
    int i=-1;
    for(;iter_for_a<a.number.constEnd();iter_for_a++,iter_for_b++)
    {
        i++;
        if( ((*iter_for_a)<(*iter_for_b)) || ((*iter_for_a)>(*iter_for_b)) )
        {
            return 0;
        }
    }
    return 1;
}

bool  LongInt::operator ==(int b)
{
    if(!this->length())
    {
        this->push_back(0);
    }

    if(b<_baza)
    {
        if(length()>1)
        {
            return 0;
        }
        if(number.length()&&number.first() == b)
        {
            return 1;
        }
        else
        {
            if(!number.length()&&b==0)
                return 1;
            else
                return 0;
        }
    }
    else
    {
        return *this == LongInt(b);
    }
}
//=============================operator=(!=)======================================
bool  LongInt::operator !=(LongInt b)const
{
    //----------------------------------------
    if(b!=0    &&   (!this->minus)*b.minus)
    {
        return true;
    }
    if(*this!=0&&   this->minus*(!b.minus))
    {
        return true;
    }
    //----------------------------------------
    if(!this->length())
    {
        //this->push_back(0);
    }
    if(!b.length())
    {
        b.push_back(0);
    }

    LongInt a=*this;
    //--------------------

    if( (a.length()<b.length()) || (a.length()>b.length()) )
    {
        return 1;
    }

    QVector<int>::const_iterator iter_for_a=a.number.constBegin();
    QVector<int>::const_iterator iter_for_b=b.number.constBegin();
    for(;iter_for_a<a.number.constEnd();iter_for_a++,iter_for_b++)
    {
        if( ((*iter_for_a)<(*iter_for_b)) || ((*iter_for_a)>(*iter_for_b)))
        {
            return 1;
        }
    }
    return 0;
}

bool  LongInt::operator !=(int b)const
{
    if(!this->length())
    {
        //this->push_back(0);
    }

    if(b<_baza)
    {
        if(length()>1)
        {
            return 1;
        }
        if(number.length()&&number.first() != b)
        {
            return 1;
        }
        else
        {
            if(!number.length()&&b!=0)
                return 1;
            else
                return 0;
        }
    }
    else
    {
        return *this != LongInt(b);
    }
}

//=============================operator=(>=)======================================
bool  LongInt::operator >=(LongInt b)const
{
    //----------------------------------------
    if(b!=0    &&   (!this->minus)*b.minus)
    {
        return true;
    }
    if(*this!=0&&   this->minus*(!b.minus))
    {
        return false;
    }
    //----------------------------------------
    if(!this->length())
    {
        //this->push_back(0);
    }
    if(!b.length())
    {
        b.push_back(0);
    }

    LongInt a;
    //--------------------
    if(this->minus*b.minus)
    {
        LongInt c=b;
        b=*this;
        a=c;
    }
    else
    {
        a=*this;
    }
    //--------------------

    if(a.length()>b.length())
    {
        return 1;
    }
    if(a.length()<b.length())
    {
        return 0;
    }
    QVector<int>::const_iterator iter_for_a=a.number.constBegin();
    QVector<int>::const_iterator iter_for_b=b.number.constBegin();
    for(;iter_for_a<a.number.constEnd();iter_for_a++,iter_for_b++)
    {
        if((*iter_for_a)>(*iter_for_b))
        {
            return 1;
        }
        if((*iter_for_a)<(*iter_for_b))
        {
            return 0;
        }
    }
    return 1;
}

bool  LongInt::operator >=(int b)
{
    if(!this->length())
    {
        this->push_back(0);
    }

    if(b<_baza)
    {
        if(length()>1)
        {
            return 1;
        }
        if(number.length()&&number.first() >= b)
        {
            return 1;
        }
        else
        {
            if(!number.length()&&b>=0)
                return 1;
            else
                return 0;
        }
    }
    else
    {
        return *this >= LongInt(b);
    }
}

//=============================operator=(<=)======================================
bool  LongInt::operator <=(LongInt b)const
{
    //----------------------------------------
    if(b!=0    &&   (!this->minus)*b.minus)
    {
        return false;
    }
    if(*this!=0&&   this->minus*(!b.minus))
    {
        return true;
    }
    //----------------------------------------
    if(!this->length())
    {
        //this->push_back(0);
    }
    if(!b.length())
    {
        b.push_back(0);
    }

    LongInt a;
    //--------------------
    if(this->minus*b.minus)
    {
        LongInt c=b;
        b=*this;
        a=c;
    }
    else
    {
        a=*this;
    }
    //--------------------

    if(length()<b.length())
    {
        return 1;
    }
    if(length()>b.length())
    {
        return 0;
    }
    QVector<int>::const_iterator iter_for_a=a.number.constBegin();
    QVector<int>::const_iterator iter_for_b=b.number.constBegin();
    for(;iter_for_a<a.number.constEnd();iter_for_a++,iter_for_b++)
    {
        if((*iter_for_a)<(*iter_for_b))
        {
            return 1;
        }
        if((*iter_for_a)>(*iter_for_b))
        {
            return 0;
        }
    }
    return 1;
}

bool  LongInt::operator <=(int b)
{
    if(!this->length())
    {
        this->push_back(0);
    }

    if(b<_baza)
    {
        if(length()>1)
        {
            return 0;
        }
        if(number.length()&&number.first() <= b)
        {
            return 1;
        }
        else
        {
            if(!number.length()&&b<=0)
                return 1;
            else
                return 0;
        }
    }
    else
    {
        return *this <= LongInt(b);
    }
}

//=============================operator=(<<int)======================================
LongInt LongInt::operator <<(int num)
{
    LongInt c;
    c.number=number;
    for(int i=0;i<num;i++)
    {
        c.number.push_back(0);
    }
    //qDebug()<<"longint.cpp:"<<number;
    //( 15 144 259 495 171 174 249 475 116 923 756 )
    return c;
}
LongInt& LongInt::operator <<=(int num)
{
    *this=((*this)<<num);
    return *this;
}

//=============================operator=(QDebug<<)======================================
QDebug /*LongInt::*/operator<<(QDebug qd, LongInt a)
{
    QVector<int>::iterator iter=a.number.begin();
    QString text="( ";
    text+=(a.minus?"- ":" ");
    for(;iter<a.number.end();iter++)
    {
        text+=QString::number(*iter)+" ";
    }
    text+=" )";//\n";
    //text+="length:"+QString::number(a.number.length());
    qd<<text;
    return qd;
}
//
//=============================operator=(>>)======================================
LongInt LongInt::operator >>(int num)
{
    LongInt b=*this;
    for(int i=0;i<num;i++)
    {
        if(b.number.isEmpty())
        {
            return b;
        }
        b.number.removeLast();
    }
    return b;
}
//=============================operator=(*)==LongInt====================================
LongInt LongInt::operator *(const LongInt &b) const//a=this;
{
    //qDebug()<<"longint.cpp:operator * :"<<*this<<b;
    static bool inAlgorithm=false;
    if(!inAlgorithm&&current_algorithm!=NULL)
    {
        inAlgorithm=true;
        LongInt c=current_algorithm(*this,b);
        inAlgorithm=false;
        return c;
    }

    if(b.number.isEmpty()||b.number.first()==0)
    {
        //result_long_int.push_front(0);
        return LongInt();
    }
    if(this->number.isEmpty()||this->number.first()==0)
    {
        //result_long_int.push_front(0);
        return LongInt();
    }
    LongInt c;
    int k=0;
    int result;
    int i=0;
    QVector<int>::const_iterator iter_a,iter_for_a=number.constEnd(),iter_b=b.number.constEnd();
    iter_for_a--;
    iter_b--;
    LongInt result_long_int;
    c.clear(false);
    for(;iter_b>=b.number.constBegin();iter_b--)
    {
        if(*iter_b==0)
        {
            i++;
            continue;
        }
        iter_a=iter_for_a;
        for(;iter_a>=number.begin();iter_a--)
        {
            if(*iter_for_a==0)
            {
                i++;
                iter_for_a--;
                continue;
            }
            result=(*iter_a) * (*iter_b)+k;
            k=result/_baza;
            result-=_baza*k;
            c.push_front(result);
            /*/
            qDebug()<<"list_algorithm:new result="<<result+k*baza<<" k="<<k<<"\n"
                      <<"*iter_a="<<*iter_a<<" *iter_b="<<*iter_b;
            /*/
        }
        if(k)
        {
            c.push_front(k);
            k=0;
        }
        c.normalization();
        //c<<i++;
        //qDebug()<<(c<<i);
        result_long_int+=(c<<i++);
        c.clear(false);
    }
    result_long_int.minus=minus*!b.minus+!minus*b.minus;
    //qDebug()<<"longint.cpp:operator *:"<<result_long_int;
    return result_long_int;//<<i;
}
//=============================operator=(*)==int==================================
LongInt LongInt::operator *(int b)
{
    //qDebug()<<"longint:b="<<b;
    if(b==0)
    {
        //result_long_int.push_front(0);
        return LongInt(0);
    }
    if(number.isEmpty()||number.first()==0)
    {
        //result_long_int.push_front(0);
        return LongInt(0);
    }
    int k=0;
    if(b<_baza)
    {
        LongInt result_long_int;
        result_long_int.clear(false);
        QVector<int>::iterator iter=number.end();
        iter--;
        int i=0;
        int result;
        for(;iter>=number.begin();iter--)
        {
            result=(*iter)*b+k;
            k=result/_baza;
            result-=_baza*k;
            result_long_int.push_front(result);
            //qDebug<<"longint:result"<<result;
        }
        if(k)
        {
            result_long_int.push_front(k);
        }
        //qDebug()<<"longint:result_long_int1="<<result_long_int;
        return result_long_int;
    }
    else
    {
        return (*this)*LongInt(b);
    }
}

//=============================operator=(*=)======================================
LongInt& LongInt::operator *=(const LongInt &b)//a=this;
{
    *this=*this * b;
    return *this;
}
LongInt& LongInt::operator *=(int b)//a=this;
{
    *this=*this * b;
    return *this;
}

LongInt  LongInt::operator /(const LongInt &b) const//a=this;
{
    //qDebug()<<"longint.cpp:a="<<*this;
    //qDebug()<<"longint.cpp:b="<<b;
    if(b==0)
    {
        qDebug()<<"longint.cpp:Error "<<"\n"
                <<*this<<"\\0 = BAMMMMMMMMMMMM!!!!";
        exit(0);
    }
    if((*this) < b)
    {
        return LongInt(0);
    }
    int k;
    LongInt result_long_int;
    LongInt part;
    result_long_int.minus=!minus*b.minus+minus*!b.minus;
    //minus=b.minus=0;
    QVector<int>::const_iterator iter=number.constBegin();
    for(;iter<number.constEnd();iter++)
    {
        part.push_back(*iter);
        //qDebug()<<"longint.cpp:part="<<part;
        if(part<b)
        {
            if(result_long_int.length())
            {
                result_long_int.push_back(0);
            }
            //qDebug()<<"longint.cpp:result_long_int="<<result_long_int;
            continue;
        }
        k=0;
        //qDebug()<<part<<b;
        while(part>=b)
        {
            k++;
            part-=b;
        }
        result_long_int.push_back(k);
        //qDebug()<<"longint.cpp:result_long_int="<<result_long_int;
    }
    return result_long_int;
}

LongInt  LongInt::operator /(int b)//a=this;
{
    if(b==0)
    {
        qDebug()<<"longint.cpp:Error "<<"\n"
                <<*this<<"\0 = BAMMMMMMMMMMMM!!!!";
        QApplication::exit();
    }
    if(*this <b)
    {
        return LongInt(0);
    }
    if(b<_baza)
    {
        int k;
        LongInt result_long_int;
        LongInt part;
        QVector<int>::iterator iter=number.begin();
        for(;iter<number.end();iter++)
        {
            part.push_back(*iter);
            //qDebug()<<"longint.cpp:part="<<part;
            if(part<b)
            {
                if(result_long_int.length())
                {
                    result_long_int.push_back(0);
                }
                //qDebug()<<"longint.cpp:result_long_int="<<result_long_int;
                continue;
            }
            k=0;
            while(part>=b)
            {
                k++;
                part-=b;
            }
            result_long_int.push_back(k);
            //qDebug()<<"longint.cpp:result_long_int="<<result_long_int;
        }
        return result_long_int;
    }
    else
    {
        return *this/LongInt(b);
    }
}

LongInt& LongInt::operator /=(const LongInt &b)
{
    *this=(*this/b);
    return *this;
}

LongInt& LongInt::operator /=(int b)
{
    *this=(*this/b);
    return *this;
}

//=============================operator=(%)======================================
LongInt  LongInt::operator %(const LongInt &b) const
{
    return mod(*this,b);
}

LongInt  LongInt::operator %(int b)
{
    return mod(*this,LongInt(b));
}

//=============================operator=(^)======================================

LongInt  LongInt::operator ^(const LongInt &b) const
{
    LongInt c(1);
    static LongInt i;
    for(i=0;i<b;++i)
    {
        c*=*this;
    }
    return c;
}

LongInt  LongInt::operator ^(int b)
{
    LongInt c(1);
    for(;b>0;b--)
    {
        c*=*this;
    }
    return c;
}

//=============================operator=([])======================================

int& LongInt::operator [](int i)
{
    return this->number[i];
}
//
