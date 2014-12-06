#include "symmetric.h"
Symmetric::Symmetric()
{
}
#define qS QString("symmetric.cpp:")
int Symmetric::_lenght=4;
LongInt Symmetric::_private_key;
void Symmetric::Generation()
{
    _private_key=norm_Random(_lenght,_lenght,false);
    qDebug()<<qS<<"generation private key-"<<_private_key;
}

QString Symmetric::Encryption(const QString& text)
{
    LongInt result;
    QString encryption_text;
    qDebug()<<qS<<"before encryption"<<text;
    qDebug()<<qS<<"lenght:"<<text.length();
    int i;
    for(i=0;i<text.length();i++)
    {
        result.push_back((int)text[i].toLatin1());
        if(_private_key<=result<<1)
        {

            encryption_text+= result.toString()+(i+1==text.length()?"":"|");
            result.clear();
        }
    }
    if(_private_key>(result<<1))
    {
        encryption_text+= result.toString();
    }
    return encryption_text;
}

QString Symmetric::Decipherment(const QString& encryption_text)
{
    return encryption_text;
}

const LongInt& Symmetric::private_key()
{
    return _private_key;
}

void Symmetric::setLenght(int l)
{
    if(l>=4)
    {
        _lenght=l;
    }
    else
    {
        qDebug()<<qS<<"l<4";
    }
}

inline const LongInt& Symmetric::lenght()
{
    return _lenght;
}
