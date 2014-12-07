//#include "longdouble.h"
#include "../algorithm.h"
LongDouble::LongDouble():LongInt()
{
}

LongDouble::LongDouble(int num):LongInt(num)
{
}

LongDouble::LongDouble(QString num):LongInt(num)
{
}

LongDouble::~LongDouble()
{

}

QString LongDouble::toString()
{
    QString text;
    QVector<int>::iterator iter;
    int i=_size,j=0;
    if(i<0)
    {
        text="0 . ";
        i++;
        while(i<0)
        {
            while(j<_baza_for_initializatio)
            {
                text+="0";
                j++;
            }
            j=0;
            text+=" ";
            i++;
        }
        i--;
    }
    if(!this->isEmpty())
    {
        iter=this->number.begin();
        int lenght;
        for(;iter<this->number.end();iter++)
        {

           if((*iter)<0||((*iter)>=(_baza/10))||(iter==this->number.begin()&&i>=0))
           {
                text+=QString::number(*iter)+" ";
                if((!i)&&iter==this->number.begin()&&number.length()!=1)
                {
                    text+=". ";
                }
           }
           else
           {
               if(*iter==0)
               {
                   for(int i=0;i<_baza_for_initializatio;i++)
                       text+="0";
                   text+=" ";
               }
               else
               {
                   lenght=_baza/10;
                   while((*iter)<lenght)
                   {
                       text+="0";
                       lenght/=10;
                   }
                   text+=QString::number(*iter)+" ";
               }
           }
           if(i>0)
           {
               i--;
               if((!i)&&_size<number.length())
               {
                   text+=". ";
               }
           }
        }
    }
    else
    {
       text+="null";
    }
    return text;
}

void LongDouble::setSize(int s)
{
    _size=s;
}

int LongDouble::size()
{
    return _size;
}
//===========================operator=(=)================================================

LongDouble& LongDouble::operator =(LongInt b)
{
    if(this==&b)
    {
        return *this;
    }
    this->number=b.number;
    this->setSize(b.length()-1);
    return *this;
}

LongDouble& LongDouble::operator =(LongDouble b)
{
    if(this==&b)
    {
        return *this;
    }
    this->number=b.number;
    this->_size=b._size;
    return *this;
}
